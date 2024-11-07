#include "vec2.h"

#include <math.h>

void vec2_zero(vec2 v) {
    v[0] = v[1] = 0.0f;
}

void vec2_copy(vec2 v1, const vec2 v2) {
    v1[0] = v2[0];
    v1[1] = v2[1];
}

float vec2_dot(const vec2 a, const vec2 b) {
    return a[0] * b[0] + a[1] * b[1];
}

float vec2_norm(const vec2 v) {
    return sqrtf(vec2_dot(v, v));
}

void vec2_add(const vec2 a, const vec2 b, vec2 dest) {
    dest[0] = a[0] + b[0];
    dest[1] = a[1] + b[1];
}

void vec2_sub(const vec2 a, const vec2 b, vec2 dest) {
    dest[0] = a[0] - b[0];
    dest[1] = a[1] - b[1];
}

void vec2_scale(const vec2 v, float s, vec2 dest) {
    dest[0] = v[0] * s;
    dest[1] = v[1] * s;
}

void vec2_mul(const vec2 a, const vec2 b, vec2 dest) {
    dest[0] = a[0] * b[0];
    dest[1] = a[1] * b[1];
}
