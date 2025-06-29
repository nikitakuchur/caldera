#ifndef MATH_VEC3_H
#define MATH_VEC3_H

#include "types.h"

vec3 vec3_new(f32 x, f32 y, f32 z);

vec3 vec3_zero();

vec3 vec3_add(vec3 a, vec3 b);

vec3 vec3_sub(vec3 a, vec3 b);

vec3 vec3_scale(vec3 v, f32 s);

vec3 vec3_mul(vec3 a, vec3 b);

vec3 vec3_cross(vec3 a, vec3 b);

f32 vec3_dot(vec3 a, vec3 b);

f32 vec3_len(vec3 v);

vec3 vec3_normalize(vec3 v);

vec3 vec3_rotate(vec3 v, f32 angle, vec3 axis);

#endif //MATH_VEC3_H
