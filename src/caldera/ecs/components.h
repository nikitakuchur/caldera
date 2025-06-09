#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "caldera/graphics/backend/texture.h"
#include "caldera/math/types.h"

typedef struct transform {
    vec2 position;
    float rotation;
    vec2 scale;

    vec2 origin;
} transform;

typedef struct sprite_renderer {
    texture texture;
    vec2 size;
    irect texture_rect;
    vec4 color;
} sprite_renderer;

enum component_type {
    TRANSFORM = 0,
    SPRITE_RENDERER
};

#endif //COMPONENTS_H
