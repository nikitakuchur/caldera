#include "renderer.h"

#include <stdio.h>
#include <graphics/backend/graphics_context.h>
#include <graphics/backend/renderer_backend.h>
#include <math/cam.h>
#include <math/mat4.h>
#include <math/vec2.h>

#define SPRITE_MAX_COUNT 1024
#define VERTEX_MAX_COUNT (1024 * 4)
#define INDEX_MAX_COUNT (1024 * 6)

typedef struct vertex {
    vec2 pos;
    vec4 color;
} vertex;

static struct {
    vertex vertices[VERTEX_MAX_COUNT];
    uint32_t vertex_count;

    uint32_t indices[INDEX_MAX_COUNT];
    uint32_t index_count;

    vertex_buffer vb;
    index_buffer ib;
} context;

void renderer_init() {
    graphics_context_init();
    renderer_backend_init();

    context.vb = vertex_buffer_create(VERTEX_MAX_COUNT * sizeof(vertex));
    context.ib = index_buffer_create(INDEX_MAX_COUNT);
}

void renderer_begin() {
    context.vertex_count = 0;
    context.index_count = 0;

    renderer_backend_begin();
}

void renderer_set_size(int width, int height) {
    mat4 proj_mat;
    ortho(
        -(float) width / 2,
        (float) width / 2,
        -(float) height / 2,
        (float) height / 2,
        0, 1,
        proj_mat
    );
    renderer_backend_set_proj_mat(proj_mat);
}

void renderer_draw_sprite(sprite s) {
    if (context.vertex_count > VERTEX_MAX_COUNT) {
        printf("Failed to draw a sprite! Maximum number of sprites reached! (%d)", SPRITE_MAX_COUNT);
    }

    vec2 bottom_left = {
        s.position[0] - s.origin[0] * s.scale[0],
        s.position[1] - s.origin[1] * s.scale[1]
    };

    float w = s.scale[0];
    float h = s.scale[1];

    vec2 bottom_right = {bottom_left[0] + w, bottom_left[1]};
    vec2 top_right = {bottom_left[0] + w, bottom_left[1] + h};
    vec2 top_left = {bottom_left[0], bottom_left[1] + h};

    uint32_t index_offset = context.vertex_count;

    context.vertices[context.vertex_count++] = (vertex){
        .pos = {bottom_left[0], bottom_left[1]},
        .color = {s.color[0], s.color[1], s.color[2], s.color[3]}
    };
    context.vertices[context.vertex_count++] = (vertex){
        .pos = {bottom_right[0], bottom_right[1]},
        .color = {s.color[0], s.color[1], s.color[2], s.color[3]}
    };
    context.vertices[context.vertex_count++] = (vertex){
        .pos = {top_right[0], top_right[1]},
        .color = {s.color[0], s.color[1], s.color[2], s.color[3]}
    };
    context.vertices[context.vertex_count++] = (vertex){
        .pos = {top_left[0], top_left[1]},
        .color = {s.color[0], s.color[1], s.color[2], s.color[3]}
    };

    context.indices[context.index_count++] = index_offset + 0;
    context.indices[context.index_count++] = index_offset + 1;
    context.indices[context.index_count++] = index_offset + 2;
    context.indices[context.index_count++] = index_offset + 2;
    context.indices[context.index_count++] = index_offset + 3;
    context.indices[context.index_count++] = index_offset + 0;
}

void renderer_end() {
    vertex_buffer_set(context.vb, context.vertices, context.vertex_count * sizeof(vertex));
    index_buffer_set(context.ib, context.indices, context.index_count);

    mat4 identity_mat;
    mat4_identity(identity_mat);

    renderer_backend_submit(context.vb, context.ib, context.index_count);
    renderer_backend_end();
}

void renderer_destroy() {
    vertex_buffer_destroy(context.vb);
    index_buffer_destroy(context.ib);

    renderer_backend_destroy();
    graphics_context_destroy();
}
