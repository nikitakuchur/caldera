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

typedef struct animation {
    int32_t x_offset;
    int32_t y_offset;

    int32_t frame_num;
    float speed;
} animation;

typedef struct sprite_animator {
    animation animation;
    float frame;
} sprite_animator;

enum component_type {
    TRANSFORM = 0,
    SPRITE_RENDERER,
    SPRITE_ANIMATOR
};

#endif //COMPONENTS_H
