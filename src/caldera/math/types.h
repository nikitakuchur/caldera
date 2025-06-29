#ifndef MATH_TYPES_H
#define MATH_TYPES_H

#include "caldera/defines.h"

#define PI 3.14159265358979323846264338327950288

typedef union vec2 {
    struct {
        f32 x;
        f32 y;
    };
    f32 raw[2];
} vec2;

typedef union vec3 {
    struct {
        f32 x;
        f32 y;
        f32 z;
    };
    struct {
        f32 r;
        f32 g;
        f32 b;
    };
    f32 raw[3];
} vec3;

typedef union vec4 {
    struct {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    };
    struct {
        f32 r;
        f32 g;
        f32 b;
        f32 a;
    };
    f32 raw[4];
} vec4;

typedef union ivec2 {
    struct {
        i32 x;
        i32 y;
    };
    i32 raw[2];
} ivec2;

typedef union mat4 {
    struct {
        f32 m00, m01, m02, m03;
        f32 m10, m11, m12, m13;
        f32 m20, m21, m22, m23;
        f32 m30, m31, m32, m33;
    };
    vec4 raw[4]; // columns
} mat4;

typedef union rect {
    struct {
        vec2 bottom_left;
        vec2 bottom_right;
        vec2 top_right;
        vec2 top_left;
    };
    vec2 raw[4];
} rect;

typedef union irect {
    struct {
        ivec2 bottom_left;
        ivec2 bottom_right;
        ivec2 top_right;
        ivec2 top_left;
    };
    ivec2 raw[4];
} irect;

#endif //MATH_TYPES_H
