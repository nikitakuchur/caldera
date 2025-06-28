#ifndef MATH_VEC2_H
#define MATH_VEC2_H

#include "types.h"

vec2 vec2_new(float x, float y);

vec2 vec2_zero();

vec2 vec2_add(vec2 a, vec2 b);

vec2 vec2_sub(vec2 a, vec2 b);

vec2 vec2_scale(vec2 v, float s);

vec2 vec2_mul(vec2 a, vec2 b);

float vec2_dot(vec2 a, vec2 b);

float vec2_len(vec2 v);

vec2 vec2_normalize(vec2 v);

vec2 vec2_rotate(vec2 v, float angle);

#endif //MATH_VEC2_H
