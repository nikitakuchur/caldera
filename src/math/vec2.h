#ifndef MATH_VEC2_H
#define MATH_VEC2_H

#include "types.h"

void vec2_zero(vec2 v);

void vec2_copy(vec2 v1, const vec2 v2);

float vec2_dot(const vec2 a, const vec2 b);

float vec2_norm(const vec2 v);

void vec2_add(const vec2 a, const vec2 b, vec2 dest);

void vec2_scale(const vec2 v, float s, vec2 dest);

void vec2_rotate(const vec2 v, float angle, vec2 dest);

void vec2_mul(const vec2 a, const vec2 b, vec2 dest);

#endif //MATH_VEC2_H
