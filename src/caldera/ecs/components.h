#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "caldera/graphics/backend/texture.h"
#include "caldera/math/types.h"

typedef struct transform {
    vec2 position;
    f32 rotation;
    vec2 scale;

    vec2 origin;
} transform;

typedef struct sprite_renderer {
    texture texture;
    ivec2 size;
    irect texture_rect;
    vec4 color;
} sprite_renderer;

typedef struct animation {
    ivec2 offset;

    i32 frame_num;
    f32 speed;
} animation;

typedef struct sprite_animator {
    animation animation;
    f32 current_frame;
} sprite_animator;

enum component_type {
    TRANSFORM = 0,
    SPRITE_RENDERER,
    SPRITE_ANIMATOR
};

#endif //COMPONENTS_H
