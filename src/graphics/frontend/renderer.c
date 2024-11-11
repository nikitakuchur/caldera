#include "renderer.h"

#include <stdio.h>
#include <graphics/backend/graphics_context.h>
#include <graphics/backend/renderer_backend.h>
#include <math/cam.h>
#include <math/mat4.h>

void renderer_init() {
    graphics_context_init();
    renderer_backend_init();
}

void renderer_set_size(int width, int height, float size) {
    float ratio = (float) width / (float) height;

    float w_px = size;
    float h_px = size;

    if (width < height) {
        h_px /= ratio;
    } else {
        w_px *= ratio;
    }

    mat4 proj_mat;
    ortho(-w_px / 2, w_px / 2, -h_px / 2, h_px / 2, 0, 1, proj_mat);

    renderer_backend_set_proj_mat(proj_mat);
    renderer_backend_set_screen_size(width, height);
    renderer_backend_set_pixel_size((int) w_px, (int) h_px);
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

    return b;
}

void renderer_batch_begin(batch *b) {
    b->vertex_count = 0;
    b->index_count = 0;
}

void renderer_batch_submit(batch *b, sprite s) {
    if (b->vertex_count > VERTEX_MAX_COUNT) {
        printf("Failed to draw a sprite! Maximum number of sprites reached! (%d)", SPRITE_MAX_COUNT);
    }

    uint32_t index_offset = b->vertex_count;

    rect r = sprite_to_rect(s);

    b->vertices[b->vertex_count++] = (vertex){
        .pos = {r.bottom_left[0], r.bottom_left[1]},
        .color = {s.color[0], s.color[1], s.color[2], s.color[3]}
    };
    b->vertices[b->vertex_count++] = (vertex){
        .pos = {r.bottom_right[0], r.bottom_right[1]},
        .color = {s.color[0], s.color[1], s.color[2], s.color[3]}
    };
    b->vertices[b->vertex_count++] = (vertex){
        .pos = {r.top_right[0], r.top_right[1]},
        .color = {s.color[0], s.color[1], s.color[2], s.color[3]}
    };
    b->vertices[b->vertex_count++] = (vertex){
        .pos = {r.top_left[0], r.top_left[1]},
        .color = {s.color[0], s.color[1], s.color[2], s.color[3]}
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

    renderer_backend_submit(b->vb, b->ib, b->index_count);
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
