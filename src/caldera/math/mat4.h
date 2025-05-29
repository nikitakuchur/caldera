#ifndef MATH_MAT4_H
#define MATH_MAT4_H

#include "types.h"

#define MAT4_IDENTITY_INIT  {{1.0f, 0.0f, 0.0f, 0.0f},\
                             {0.0f, 1.0f, 0.0f, 0.0f},\
                             {0.0f, 0.0f, 1.0f, 0.0f},\
                             {0.0f, 0.0f, 0.0f, 1.0f}}

void mat4_copy(const mat4 m, mat4 dest);

void mat4_zero(mat4 m);

void mat4_identity(mat4 m);

void mat4_mul(const mat4 m1, const mat4 m2, mat4 dest);

#endif //MATH_MAT4_H
