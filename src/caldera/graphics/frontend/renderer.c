#include "renderer.h"

#include <stdio.h>
#include <caldera/graphics/backend/graphics_context.h>
#include <caldera/graphics/backend/renderer_backend.h>
#include <caldera/math/cam.h>

#include "caldera/math/vec2.h"
#include "caldera/utils/time.h"
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

    // finalise rendering and poll events
    renderer_backend_end();
    window_poll_events();

    f64 current_frame_time = get_current_time();

    f32 delta_time = 0.f;
    if (!is_first_frame) {
        delta_time = (f32)(current_frame_time - last_frame_time);
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

void renderer_batch_submit(batch *b, sprite s) {
    if (b->vertex_count >= VERTEX_MAX_COUNT) {
        printf("Failed to draw a sprite! Maximum number of sprites reached! (%d)", SPRITE_MAX_COUNT);
        return;
    }
    if (b->texture_count >= TEXTURE_MAX_COUNT) {
        printf("Failed to draw a sprite! Maximum number of textures reached! (%d)", TEXTURE_MAX_COUNT);
        return;
    }

    i32 tex_index = -1;
    if (s.texture.id != -1) {
        for (i32 i = 0; i < b->texture_count; i++) {
            if (b->textures[i].id == s.texture.id) {
                tex_index = i;
                break;
            }
        }
        if (tex_index == -1) {
            tex_index = (i32) b->texture_count++;
            b->textures[tex_index] = s.texture;
        }
    }

    u32 index_offset = b->vertex_count;

    rect r = sprite_to_rect(&s);

    b->vertices[b->vertex_count++] = (vertex){
        .pos = {r.bottom_left.x, r.bottom_left.y},
        .color = {s.color.r, s.color.g, s.color.b, s.color.a},
        .tex_coords = {(f32) s.texture_rect.bottom_left.x, (f32) s.texture_rect.bottom_left.y},
        .tex_index = tex_index
    };
    b->vertices[b->vertex_count++] = (vertex){
        .pos = {r.bottom_right.x, r.bottom_right.y},
        .color = {s.color.r, s.color.g, s.color.b, s.color.a},
        .tex_coords = {(f32) s.texture_rect.bottom_right.x, (f32) s.texture_rect.bottom_right.y},
        .tex_index = tex_index
    };
    b->vertices[b->vertex_count++] = (vertex){
        .pos = {r.top_right.x, r.top_right.y},
        .color = {s.color.r, s.color.g, s.color.b, s.color.a},
        .tex_coords = {(f32) s.texture_rect.top_right.x, (f32) s.texture_rect.top_right.y},
        .tex_index = tex_index
    };
    b->vertices[b->vertex_count++] = (vertex){
        .pos = {r.top_left.x, r.top_left.y},
        .color = {s.color.r, s.color.g, s.color.b, s.color.a},
        .tex_coords = {(f32) s.texture_rect.top_left.x, (f32) s.texture_rect.top_left.y},
        .tex_index = tex_index
    };

    b->indices[b->index_count++] = index_offset + 0;
    b->indices[b->index_count++] = index_offset + 1;
    b->indices[b->index_count++] = index_offset + 2;
    b->indices[b->index_count++] = index_offset + 2;
    b->indices[b->index_count++] = index_offset + 3;
    b->indices[b->index_count++] = index_offset + 0;
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
