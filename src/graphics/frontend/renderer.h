#ifndef RENDERER_H
#define RENDERER_H

#include <graphics/backend/index_buffer.h>
#include <graphics/backend/vertex_buffer.h>
#include <math/types.h>

#define SPRITE_MAX_COUNT 8192
#define VERTEX_MAX_COUNT (SPRITE_MAX_COUNT * 4)
#define INDEX_MAX_COUNT (SPRITE_MAX_COUNT * 6)

typedef struct sprite {
    vec2 position;
    vec2 origin;
    vec2 scale;
    vec4 color;
} sprite;

typedef struct vertex {
    vec2 pos;
    vec4 color;
} vertex;

typedef struct batch {
    vertex vertices[VERTEX_MAX_COUNT];
    uint32_t vertex_count;

    uint32_t indices[INDEX_MAX_COUNT];
    uint32_t index_count;

    vertex_buffer vb;
    index_buffer ib;
} batch;

void renderer_init();

void renderer_set_size(int width, int height);

void renderer_frame_begin();

batch renderer_batch_create();

void renderer_batch_begin(batch *b);

void renderer_batch_submit(batch *b, sprite s);

void renderer_batch_end(batch *b);

void renderer_batch_destroy(batch *b);

void renderer_frame_end();

void renderer_destroy();

#endif //RENDERER_H
