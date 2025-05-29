#ifndef RENDERER_H
#define RENDERER_H

#include <caldera/graphics/backend/index_buffer.h>
#include <caldera/graphics/backend/vertex_buffer.h>
#include <caldera/math/types.h>

#include "sprite.h"

#define SPRITE_MAX_COUNT 8192
#define VERTEX_MAX_COUNT (SPRITE_MAX_COUNT * 4)
#define INDEX_MAX_COUNT (SPRITE_MAX_COUNT * 6)
#define TEXTURE_MAX_COUNT 10

typedef struct vertex {
    vec2 pos;
    vec4 color;
    vec2 tex_coords;
    int32_t tex_index;
} vertex;

typedef struct batch {
    vertex vertices[VERTEX_MAX_COUNT];
    uint32_t vertex_count;

    uint32_t indices[INDEX_MAX_COUNT];
    uint32_t index_count;

    vertex_buffer vb;
    index_buffer ib;

    texture textures[TEXTURE_MAX_COUNT];
    uint32_t texture_count;
} batch;

void renderer_init();

/**
* Updates the projection matrix based on the screen dimensions and a reference size.
*
* @param width  the width of the screen in pixels
* @param height the height of the screen in pixels
* @param size   the reference dimension in pixels (applies to the smaller of width or height)
*/
void renderer_set_size(int width, int height, float size);

/**
* Sets the color that will be used to clear the screen.
*
* @param color the color that needs to be set
*/
void renderer_set_clear_color(vec4 color);

void renderer_frame_begin();

batch renderer_batch_create();

void renderer_batch_begin(batch *b);

void renderer_batch_submit(batch *b, sprite s);

void renderer_batch_end(batch *b);

void renderer_batch_destroy(batch *b);

void renderer_frame_end();

void renderer_destroy();

#endif //RENDERER_H
