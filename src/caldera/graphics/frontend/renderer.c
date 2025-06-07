#include "renderer.h"

#include <stdio.h>
#include <math.h>
#include <caldera/graphics/backend/graphics_context.h>
#include <caldera/graphics/backend/renderer_backend.h>
#include <caldera/math/cam.h>
#include <caldera/math/mat4.h>

#include "caldera/window/window.h"

static struct {
    float ortho_left;
    float ortho_right;
    float ortho_bottom;
    float ortho_top;
} context;

void renderer_init() {
    graphics_context_init();
    renderer_backend_init();
}

void renderer_set_size(int width, int height, float size) {
    const float ratio = (float) width / (float) height;

    const float ortho_height = size * 2;
    const float ortho_width = ortho_height * ratio;

    const float half_width = (float) ortho_width / 2;
    const float half_height = (float) ortho_height / 2;

    // saving this for later use (see renderer_screen_to_world)
    context.ortho_left = -half_width;
    context.ortho_right = half_width;
    context.ortho_bottom = -half_height;
    context.ortho_top = half_height;

    mat4 proj_mat;
    ortho(
        context.ortho_left,
        context.ortho_right,
        context.ortho_bottom,
        context.ortho_top,
        0,
        1,
        proj_mat
    );

    renderer_backend_set_proj_mat(proj_mat);
    renderer_backend_set_screen_size(width, height);
    renderer_backend_set_pixel_size(width, height);
}

void renderer_set_clear_color(vec4 color) {
    renderer_backend_set_clear_color(color);
}

void renderer_frame_begin() {
    renderer_backend_begin();
}

batch renderer_batch_create() {
    batch b = {};

    b.vb = vertex_buffer_create(VERTEX_MAX_COUNT * sizeof(vertex));
    b.ib = index_buffer_create(INDEX_MAX_COUNT);

    b.vertex_count = 0;
    b.index_count = 0;
    b.texture_count = 0;

    return b;
}

void renderer_batch_begin(batch *b) {
    b->vertex_count = 0;
    b->index_count = 0;
    b->texture_count = 0;
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

    int tex_index = -1;
    if (s.texture.id != -1) {
        for (int i = 0; i < b->texture_count; i++) {
            if (b->textures[i].id == s.texture.id) {
                tex_index = i;
                break;
            }
        }
        if (tex_index == -1) {
            tex_index = b->texture_count++;
            b->textures[tex_index] = s.texture;
        }
    }

    uint32_t index_offset = b->vertex_count;

    rect r = sprite_to_rect(&s);

    b->vertices[b->vertex_count++] = (vertex){
        .pos = {r.bottom_left[0], r.bottom_left[1]},
        .color = {s.color[0], s.color[1], s.color[2], s.color[3]},
        .tex_coords = {s.texture_rect.bottom_left[0], s.texture_rect.bottom_left[1]},
        .tex_index = tex_index
    };
    b->vertices[b->vertex_count++] = (vertex){
        .pos = {r.bottom_right[0], r.bottom_right[1]},
        .color = {s.color[0], s.color[1], s.color[2], s.color[3]},
        .tex_coords = {s.texture_rect.bottom_right[0], s.texture_rect.bottom_right[1]},
        .tex_index = tex_index
    };
    b->vertices[b->vertex_count++] = (vertex){
        .pos = {r.top_right[0], r.top_right[1]},
        .color = {s.color[0], s.color[1], s.color[2], s.color[3]},
        .tex_coords = {s.texture_rect.top_right[0], s.texture_rect.top_right[1]},
        .tex_index = tex_index
    };
    b->vertices[b->vertex_count++] = (vertex){
        .pos = {r.top_left[0], r.top_left[1]},
        .color = {s.color[0], s.color[1], s.color[2], s.color[3]},
        .tex_coords = {s.texture_rect.top_left[0], s.texture_rect.top_left[1]},
        .tex_index = tex_index
    };

    b->indices[b->index_count++] = index_offset + 0;
    b->indices[b->index_count++] = index_offset + 1;
    b->indices[b->index_count++] = index_offset + 2;
    b->indices[b->index_count++] = index_offset + 2;
    b->indices[b->index_count++] = index_offset + 3;
    b->indices[b->index_count++] = index_offset + 0;
}

void renderer_batch_end(batch *b) {
    vertex_buffer_set(b->vb, b->vertices, b->vertex_count * sizeof(vertex));
    index_buffer_set(b->ib, b->indices, b->index_count);

    mat4 identity_mat;
    mat4_identity(identity_mat);

    renderer_backend_submit(b->vb, b->ib, b->index_count, b->textures, b->texture_count);
}

void renderer_batch_destroy(batch *b) {
    vertex_buffer_destroy(b->vb);
    index_buffer_destroy(b->ib);
}

void renderer_frame_end() {
    renderer_backend_end();
}

void renderer_destroy() {
    renderer_backend_destroy();
    graphics_context_destroy();
}

void renderer_screen_to_world(const vec2 source, vec2 dest) {
    int screen_width, screen_height;
    window_get_size(&screen_width, &screen_height);

    const float left = context.ortho_left;
    const float right = context.ortho_right;
    const float bottom = context.ortho_bottom;
    const float top = context.ortho_top;

    dest[0] = left + (right - left) * (source[0] / (float) screen_width);
    dest[1] = bottom + (top - bottom) * (1.f - source[1] / (float) screen_height);
}
