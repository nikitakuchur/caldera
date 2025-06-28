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
    vec2 pos;           // 8 bytes
    vec4 color;         // 16 bytes
    vec2 tex_coords;    // 8 bytes
    int32_t tex_index;  // 4 bytes
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

void renderer_free();

/**
* Updates the projection matrix based on the screen dimensions and a reference size.
*
* @param width  the width of the screen in pixels
* @param height the height of the screen in pixels
*/
void renderer_set_size(int width, int height, float size);

/**
* Sets the color that will be used to clear the screen.
*
* @param color the color that needs to be set
*/
void renderer_set_clear_color(vec4 color);

void renderer_frame_begin();

void renderer_frame_end();

void renderer_batch_init(batch *b);

void renderer_batch_free(batch *b);

void renderer_batch_begin(batch *b);

void renderer_batch_end(batch *b);

void renderer_batch_submit(batch *b, sprite s);

vec2 renderer_screen_to_world(vec2 position);

#endif //RENDERER_H
