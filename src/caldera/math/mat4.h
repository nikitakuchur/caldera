#ifndef MATH_MAT4_H
#define MATH_MAT4_H

#include "types.h"

#define MAT4_IDENTITY_INIT  {{1.f, 0.f, 0.f, 0.f},\
                             {0.f, 1.f, 0.f, 0.f},\
                             {0.f, 0.f, 1.f, 0.f},\
                             {0.f, 0.f, 0.f, 1.f}}

mat4 mat4_identity();

mat4 mat4_zero();

mat4 mat4_mul(mat4 a, mat4 b);

vec4 mat4_mulv(mat4 m, vec4 v);

#endif //MATH_MAT4_H
