#ifndef MATH_VEC4_H
#define MATH_VEC4_H

#include "types.h"

void vec4_zero(vec4 v);

void vec4_copy(vec4 v1, const vec4 v2);

void vec4_add(const vec4 a, const vec4 b, vec4 dest);

void vec4_scale(const vec4 v, float s, vec4 dest);

#endif //MATH_VEC4_H
