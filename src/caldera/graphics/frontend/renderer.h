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
    i32 tex_index;  // 4 bytes
} vertex;

typedef struct batch {
    vertex vertices[VERTEX_MAX_COUNT];
    u32 vertex_count;

    u32 indices[INDEX_MAX_COUNT];
    u32 index_count;

    vertex_buffer vb;
    index_buffer ib;

    texture textures[TEXTURE_MAX_COUNT];
    u32 texture_count;
} batch;

typedef struct frame_info {
    f32 delta_time;
    u32 fps;
} frame_info;

void renderer_init();

void renderer_free();

/**
* Updates the orthographic projection matrix based on the screen dimensions
* and a reference vertical size.
*
* This function sets up an orthographic camera where the `size` parameter
* defines half of the vertical viewing area in world units. The horizontal
* extent is automatically calculated based on the screen's aspect ratio.
*
* @param width  the width of the screen in pixels
* @param height the height of the screen in pixels
* @param size   the vertical half-size of the orthographic view in world units
*/
void renderer_set_size(u32 width, u32 height, f32 size);

/**
* Sets the color that will be used to clear the screen.
*
* @param color the color that needs to be set
*/
void renderer_set_clear_color(vec4 color);

void renderer_frame_begin();

frame_info renderer_frame_end();

void renderer_batch_init(batch *b);

void renderer_batch_free(batch *b);

void renderer_batch_begin(batch *b);

void renderer_batch_end(batch *b);

void renderer_batch_submit(batch *b, sprite s);

vec2 renderer_screen_to_world(vec2 position);

#endif //RENDERER_H
