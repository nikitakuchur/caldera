#include "renderer.h"

#include <caldera/graphics/backend/graphics_context.h>
#include <caldera/graphics/backend/renderer_backend.h>
#include <caldera/math/cam.h>

#include "caldera/containers/darray.h"
#include "caldera/math/util.h"
#include "caldera/math/vec2.h"
#include "caldera/utils/log.h"
#include "caldera/utils/time.h"
#include "caldera/utils/utf8.h"
#include "caldera/window/window.h"

static struct {
    f32 ortho_left;
    f32 ortho_right;
    f32 ortho_bottom;
    f32 ortho_top;
} context;

void renderer_init() {
    graphics_context_init();
    renderer_backend_init();
}

void renderer_free() {
    renderer_backend_free();
    graphics_context_free();
}

void renderer_set_size(u32 width, u32 height, f32 size) {
    f32 ratio = (f32) width / (f32) height;

    f32 ortho_height = size * 2;
    f32 ortho_width = ortho_height * ratio;

    f32 half_width = ortho_width / 2;
    f32 half_height = ortho_height / 2;

    // saving this for later use (see renderer_screen_to_world)
    context.ortho_left = -half_width;
    context.ortho_right = half_width;
    context.ortho_bottom = -half_height;
    context.ortho_top = half_height;

    mat4 proj_mat = ortho(
        context.ortho_left,
        context.ortho_right,
        context.ortho_bottom,
        context.ortho_top,
        0.f,
        1.f
    );

    renderer_backend_set_proj_mat(&proj_mat);
    renderer_backend_set_screen_size(width, height);
    renderer_backend_set_pixel_size(width, height);
}

void renderer_set_clear_color(vec4 color) {
    renderer_backend_set_clear_color(color);
}

void renderer_frame_begin() {
    renderer_backend_begin();
}

frame_info renderer_frame_end() {
    static b8 is_first_frame = true;
    static f64 last_frame_time = 0.f;

    static u32 frame_count = 0;
    static f32 elapsed_time = 0.f;
    static u32 fps = 0;

    // finalize rendering and poll events
    renderer_backend_end();
    window_poll_events();

    f64 current_frame_time = get_current_time();

    f32 delta_time = 0.f;
    if (!is_first_frame) {
        delta_time = (f32) (current_frame_time - last_frame_time);
        if (delta_time < 0.0f) {
            delta_time = 0.0f; // safety clamp
        }
    } else {
        is_first_frame = false;
    }

    last_frame_time = current_frame_time;

    frame_count++;
    elapsed_time += delta_time;

    // update FPS every second
    if (elapsed_time >= 1.f) {
        fps = frame_count;
        frame_count = 0;
        elapsed_time = 0.f;
    }

    return (frame_info){
        .delta_time = delta_time,
        .fps = fps,
    };
}

void renderer_batch_init(batch *b) {
    vertex_buffer_init(&b->vb, VERTEX_MAX_COUNT * sizeof(vertex));
    index_buffer_init(&b->ib, INDEX_MAX_COUNT);

    b->vertex_count = 0;
    b->index_count = 0;
    b->texture_count = 0;
}

void renderer_batch_free(batch *b) {
    vertex_buffer_free(&b->vb);
    index_buffer_free(&b->ib);
}


void renderer_batch_begin(batch *b) {
    b->vertex_count = 0;
    b->index_count = 0;
    b->texture_count = 0;
}

void renderer_batch_end(batch *b) {
    vertex_buffer_set(&b->vb, b->vertices, b->vertex_count * sizeof(vertex));
    index_buffer_set(&b->ib, b->indices, b->index_count);

    renderer_backend_submit(b->vb, b->ib, b->index_count, b->textures, b->texture_count);
}

static i32 resolve_texture_index(batch *b, texture texture) {
    if (texture.id == -1) {
        return -1;
    }
    for (i32 i = 0; i < b->texture_count; i++) {
        if (b->textures[i].id == texture.id) {
            return i;
        }
    }
    i32 texture_index = (i32) b->texture_count++;
    b->textures[texture_index] = texture;
    return texture_index;
}

static void submit_quad(batch *b, vertex *v) {
    u32 index_offset = b->vertex_count;

    b->vertices[b->vertex_count++] = v[0];
    b->vertices[b->vertex_count++] = v[1];
    b->vertices[b->vertex_count++] = v[2];
    b->vertices[b->vertex_count++] = v[3];

    b->indices[b->index_count++] = index_offset + 0;
    b->indices[b->index_count++] = index_offset + 1;
    b->indices[b->index_count++] = index_offset + 2;
    b->indices[b->index_count++] = index_offset + 2;
    b->indices[b->index_count++] = index_offset + 3;
    b->indices[b->index_count++] = index_offset + 0;
}

static void move_vertices(vertex *vertex, u32 size, vec2 v) {
    for (u32 i = 0; i < size; i++) {
        vertex[i].pos = vec2_add(vertex[i].pos, v);
    }
}

static void scale_vertices(vertex *vertex, u32 size, vec2 v) {
    for (u32 i = 0; i < size; i++) {
        vertex[i].pos = vec2_mul(vertex[i].pos, v);
    }
}

static void rotate_vertices(vertex *vertex, u32 size, f32 angle) {
    for (u32 i = 0; i < size; i++) {
        vertex[i].pos = vec2_rotate(vertex[i].pos, rad(angle));
    }
}

void renderer_batch_submit_sprite(batch *b, sprite s) {
    if (b->vertex_count >= VERTEX_MAX_COUNT) {
        fatalf("Failed to draw a sprite! Maximum number of sprites reached! (%d)", SPRITE_MAX_COUNT);
    }
    if (b->texture_count >= TEXTURE_MAX_COUNT) {
        fatalf("Failed to draw a sprite! Maximum number of textures reached! (%d)", TEXTURE_MAX_COUNT);
    }

    i32 texture_index = resolve_texture_index(b, s.texture);

    vertex quad[4] = {
        {
            .pos = {0.f, 0.f},
            .color = {s.color.r, s.color.g, s.color.b, s.color.a},
            .tex_coords = {(f32) s.texture_rect.bottom_left.x, (f32) s.texture_rect.bottom_left.y},
            .tex_index = texture_index
        },
        {
            .pos = {(f32) s.size.x, 0.f},
            .color = {s.color.r, s.color.g, s.color.b, s.color.a},
            .tex_coords = {(f32) s.texture_rect.bottom_right.x, (f32) s.texture_rect.bottom_right.y},
            .tex_index = texture_index
        },
        {
            .pos = {(f32) s.size.x, (f32) s.size.y},
            .color = {s.color.r, s.color.g, s.color.b, s.color.a},
            .tex_coords = {(f32) s.texture_rect.top_right.x, (f32) s.texture_rect.top_right.y},
            .tex_index = texture_index
        },
        {
            .pos = {0.f, (f32) s.size.y},
            .color = {s.color.r, s.color.g, s.color.b, s.color.a},
            .tex_coords = {(f32) s.texture_rect.top_left.x, (f32) s.texture_rect.top_left.y},
            .tex_index = texture_index
        }
    };

    // apply transformations
    vec2 v = vec2_scale(s.origin, -1);
    move_vertices(quad, 4, v);
    scale_vertices(quad, 4, s.scale);
    rotate_vertices(quad, 4, s.rotation);
    move_vertices(quad, 4, s.position);

    submit_quad(b, quad);
}

static char_set *find_char_set(font f, u32 codepoint) {
    for (u32 i = 0; i < CHAR_SETS_COUNT; ++i) {
        char_set *set = &f.char_sets[i];
        if (codepoint >= set->first && codepoint < set->first + set->range) {
            return set;
        }
    }
    return nullptr;
}

void renderer_batch_submit_text(batch *b, font f, text text) {
    i32 texture_index = resolve_texture_index(b, f.atlas);

    char *p = text.str;
    vec2 glyph_position = vec2_zero();

    darray vertices;
    darray_init(&vertices, sizeof(vertex), 32);

    while (*p) {
        u32 len = utf8_char_len(*p);

        u32 codepoint;
        if (len > 0) {
            codepoint = utf8_to_codepoint(p, len);
        } else {
            len = 1;
            codepoint = 0xFFFD;
        }

        char_set *set = find_char_set(f, codepoint);
        if (set == nullptr) {
            // failed to find the char set
            codepoint = 0xFFFD;
            set = &f.specials;
        }

        packed_char pc = set->packed_chars[codepoint - set->first];
        aligned_quad aq = set->aligned_quads[codepoint - set->first];

        // we have to denormalize texture coordinates
        ivec2 texture_tl = {(i32) ((f32) f.size.x * aq.s0), (i32) ((f32) f.size.y * aq.t0)};
        ivec2 texture_br = {(i32) ((f32) f.size.x * aq.s1), (i32) ((f32) f.size.y * aq.t1)};

        ivec2 glyph_size = ivec2_new(texture_br.x - texture_tl.x, texture_br.y - texture_tl.y);

        glyph_position.x += pc.xoff;

        vec2 quad_position = vec2_sub(glyph_position, vec2_new(0.f, (f32) glyph_size.y + pc.yoff));

        vertex *v = darray_add(&vertices);
        *v = (vertex){
            .pos = quad_position,
            .color = text.color,
            .tex_coords = {(f32) texture_tl.x, (f32) texture_br.y},
            .tex_index = texture_index
        };
        v = darray_add(&vertices);
        *v = (vertex){
            .pos = {quad_position.x + (f32) glyph_size.x, quad_position.y},
            .color = text.color,
            .tex_coords = {(f32) texture_br.x, (f32) texture_br.y},
            .tex_index = texture_index
        };
        v = darray_add(&vertices);
        *v = (vertex){
            .pos = {quad_position.x + (f32) glyph_size.x, quad_position.y + (f32) glyph_size.y},
            .color = text.color,
            .tex_coords = {(f32) texture_br.x, (f32) texture_tl.y},
            .tex_index = texture_index
        };
        v = darray_add(&vertices);
        *v = (vertex){
            .pos = {quad_position.x, quad_position.y + (f32) glyph_size.y},
            .color = text.color,
            .tex_coords = {(f32) texture_tl.x, (f32) texture_tl.y},
            .tex_index = texture_index
        };

        glyph_position.x += pc.xadvance;

        p += len;
    }

    // apply transformations
    vec2 v = vec2_scale(text.origin, -1);
    move_vertices(vertices.array, vertices.size, v);
    scale_vertices(vertices.array, vertices.size, text.scale);
    rotate_vertices(vertices.array, vertices.size, text.rotation);
    move_vertices(vertices.array, vertices.size, text.position);

    // submit all the vertices
    for (u32 i = 0; i < vertices.size / 4; i++) {
        submit_quad(b, &((vertex*)vertices.array)[i * 4]);
    }
}

vec2 renderer_screen_to_world(vec2 position) {
    ivec2 window_size = window_get_size();

    f32 left = context.ortho_left;
    f32 right = context.ortho_right;
    f32 bottom = context.ortho_bottom;
    f32 top = context.ortho_top;

    return vec2_new(
        left + (right - left) * (position.x / (f32) window_size.x),
        bottom + (top - bottom) * (1.f - position.y / (f32) window_size.y)
    );
}
