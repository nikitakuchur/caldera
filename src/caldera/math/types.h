#ifndef MATH_TYPES_H
#define MATH_TYPES_H

#include <stdint.h>

#define PI 3.14159265358979323846264338327950288

typedef float vec2[2];
typedef float vec3[3];
typedef float vec4[4];
typedef vec4 mat4[4];

typedef int32_t ivec2[2];

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

#endif //MATH_TYPES_H
