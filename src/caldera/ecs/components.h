#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "caldera/graphics/backend/texture.h"
#include "caldera/graphics/frontend/font.h"
#include "caldera/math/types.h"

typedef struct ec_transform {
    vec2 position;
    f32 rotation;
    vec2 scale;

    vec2 origin;
} ec_transform;

typedef struct ec_sprite {
    texture texture;
    ivec2 size;
    irect texture_rect;
    vec4 color;
} ec_sprite;

typedef struct animation {
    ivec2 offset;

    i32 frame_num;
    f32 speed;
} animation;

typedef struct ec_animator {
    animation animation;
    f32 current_frame;
} ec_animator;

typedef struct ec_text {
    font font;
    char *str;
    vec4 color;
} ec_text;

enum component_type {
    EC_TRANSFORM = 0,
    EC_SPRITE,
    EC_ANIMATOR,
    EC_TEXT,
};

#endif //COMPONENTS_H
