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
    irect texture_rect;
} sprite;

void sprite_init(sprite *s, vec2 size, texture t);

rect sprite_to_rect(sprite *s);

#endif //SPRITE_H
