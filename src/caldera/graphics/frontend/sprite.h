#ifndef SPRITE_H
#define SPRITE_H

#include <caldera/math/types.h>
#include <caldera/graphics/backend/texture.h>

typedef struct sprite {
    vec2 size;
    vec4 color;

    vec2 position;
    float rotation;
    vec2 scale;

    vec2 origin;

    texture texture;
} sprite;

typedef struct rect {
    vec2 bottom_left;
    vec2 bottom_right;
    vec2 top_right;
    vec2 top_left;
} rect;

rect sprite_to_rect(sprite s);

#endif //SPRITE_H
