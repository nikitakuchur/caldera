#ifndef MATH_VEC4_H
#define MATH_VEC4_H

#include "types.h"

vec4 vec4_new(float x, float y, float z, float w);

vec4 vec4_zero();

vec4 vec4_add(vec4 a, vec4 b);

vec4 vec4_scale(vec4 v, float s);

#endif //MATH_VEC4_H
