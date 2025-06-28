#ifndef MATH_TYPES_H
#define MATH_TYPES_H

#include <stdint.h>

#define PI 3.14159265358979323846264338327950288

typedef union vec2 {
    float raw[2];
    struct {
        float x;
        float y;
    };
} vec2;

typedef union vec3 {
    float raw[3];
    struct {
        float x;
        float y;
        float z;
    };
    struct {
        float r;
        float g;
        float b;
    };
} vec3;

typedef union vec4 {
    float raw[4];
    struct {
        float x;
        float y;
        float z;
        float w;
    };
    struct {
        float r;
        float g;
        float b;
        float a;
    };
} vec4;

typedef union ivec2 {
    int32_t raw[2];
    struct {
        int32_t x;
        int32_t y;
    };
} ivec2;

typedef union mat4 {
    vec4 raw[4]; // columns
    struct {
        float m00, m01, m02, m03;
        float m10, m11, m12, m13;
        float m20, m21, m22, m23;
        float m30, m31, m32, m33;
    };
} mat4;

typedef union rect {
    vec2 raw[4];
    struct {
        vec2 bottom_left;
        vec2 bottom_right;
        vec2 top_right;
        vec2 top_left;
    };
} rect;

typedef union irect {
    ivec2 raw[4];
    struct {
        ivec2 bottom_left;
        ivec2 bottom_right;
        ivec2 top_right;
        ivec2 top_left;
    };
} irect;

#endif //MATH_TYPES_H
