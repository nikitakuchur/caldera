#ifndef MATH_VEC4_H
#define MATH_VEC4_H

#include "types.h"

vec4 vec4_new(f32 x, f32 y, f32 z, f32 w);

vec4 vec4_zero();

vec4 vec4_add(vec4 a, vec4 b);

vec4 vec4_scale(vec4 v, f32 s);

#endif //MATH_VEC4_H
