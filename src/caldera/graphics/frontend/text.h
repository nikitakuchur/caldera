#ifndef TEXT_H
#define TEXT_H

#include "caldera/math/types.h"

typedef struct text {
    char *str;
    vec4 color;

    vec2 position;
    f32 rotation;
    vec2 scale;

    vec2 origin;
} text;

#endif //TEXT_H
