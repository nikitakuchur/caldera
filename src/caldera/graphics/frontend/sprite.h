#ifndef SPRITE_H
#define SPRITE_H

#include <caldera/math/types.h>
#include <caldera/graphics/backend/texture.h>

typedef struct rect {
    vec2 bottom_left;
    vec2 bottom_right;
    vec2 top_right;
    vec2 top_left;
} rect;

typedef struct irect {
    ivec2 bottom_left;
    ivec2 bottom_right;
    ivec2 top_right;
    ivec2 top_left;
} irect;

typedef struct sprite {
    vec2 size;
    vec4 color;

    vec2 position;
    float rotation;
    vec2 scale;

    vec2 origin;

    texture texture;
    irect texture_rect;
} sprite;

void sprite_init(sprite *s, vec2 size, texture t);

rect sprite_to_rect(sprite *s);

#endif //SPRITE_H
