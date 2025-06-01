#include "mat4.h"

#include "vec4.h"

void mat4_copy(const mat4 m, mat4 dest) {
    dest[0][0] = m[0][0];
    dest[1][0] = m[1][0];
    dest[0][1] = m[0][1];
    dest[1][1] = m[1][1];
    dest[0][2] = m[0][2];
    dest[1][2] = m[1][2];
    dest[0][3] = m[0][3];
    dest[1][3] = m[1][3];

    dest[2][0] = m[2][0];
    dest[3][0] = m[3][0];
    dest[2][1] = m[2][1];
    dest[3][1] = m[3][1];
    dest[2][2] = m[2][2];
    dest[3][2] = m[3][2];
    dest[2][3] = m[2][3];
    dest[3][3] = m[3][3];
}

void mat4_zero(mat4 m) {
    vec4_zero(m[0]);
    vec4_zero(m[1]);
    vec4_zero(m[2]);
    vec4_zero(m[3]);
}

void mat4_identity(mat4 m) {
    mat4 im = MAT4_IDENTITY_INIT;
    mat4_copy(im, m);
}

void mat4_mul(const mat4 m1, const mat4 m2, mat4 dest) {
    float a00 = m1[0][0], a01 = m1[0][1], a02 = m1[0][2], a03 = m1[0][3],
            a10 = m1[1][0], a11 = m1[1][1], a12 = m1[1][2], a13 = m1[1][3],
            a20 = m1[2][0], a21 = m1[2][1], a22 = m1[2][2], a23 = m1[2][3],
            a30 = m1[3][0], a31 = m1[3][1], a32 = m1[3][2], a33 = m1[3][3],

            b00 = m2[0][0], b01 = m2[0][1], b02 = m2[0][2], b03 = m2[0][3],
            b10 = m2[1][0], b11 = m2[1][1], b12 = m2[1][2], b13 = m2[1][3],
            b20 = m2[2][0], b21 = m2[2][1], b22 = m2[2][2], b23 = m2[2][3],
            b30 = m2[3][0], b31 = m2[3][1], b32 = m2[3][2], b33 = m2[3][3];

    dest[0][0] = a00 * b00 + a10 * b01 + a20 * b02 + a30 * b03;
    dest[0][1] = a01 * b00 + a11 * b01 + a21 * b02 + a31 * b03;
    dest[0][2] = a02 * b00 + a12 * b01 + a22 * b02 + a32 * b03;
    dest[0][3] = a03 * b00 + a13 * b01 + a23 * b02 + a33 * b03;
    dest[1][0] = a00 * b10 + a10 * b11 + a20 * b12 + a30 * b13;
    dest[1][1] = a01 * b10 + a11 * b11 + a21 * b12 + a31 * b13;
    dest[1][2] = a02 * b10 + a12 * b11 + a22 * b12 + a32 * b13;
    dest[1][3] = a03 * b10 + a13 * b11 + a23 * b12 + a33 * b13;
    dest[2][0] = a00 * b20 + a10 * b21 + a20 * b22 + a30 * b23;
    dest[2][1] = a01 * b20 + a11 * b21 + a21 * b22 + a31 * b23;
    dest[2][2] = a02 * b20 + a12 * b21 + a22 * b22 + a32 * b23;
    dest[2][3] = a03 * b20 + a13 * b21 + a23 * b22 + a33 * b23;
    dest[3][0] = a00 * b30 + a10 * b31 + a20 * b32 + a30 * b33;
    dest[3][1] = a01 * b30 + a11 * b31 + a21 * b32 + a31 * b33;
    dest[3][2] = a02 * b30 + a12 * b31 + a22 * b32 + a32 * b33;
    dest[3][3] = a03 * b30 + a13 * b31 + a23 * b32 + a33 * b33;
}

void mat4_mulv(const mat4 m, const vec4 v, vec4 dest) {
    vec4 res;
    res[0] = m[0][0] * v[0] + m[1][0] * v[1] + m[2][0] * v[2] + m[3][0] * v[3];
    res[1] = m[0][1] * v[0] + m[1][1] * v[1] + m[2][1] * v[2] + m[3][1] * v[3];
    res[2] = m[0][2] * v[0] + m[1][2] * v[1] + m[2][2] * v[2] + m[3][2] * v[3];
    res[3] = m[0][3] * v[0] + m[1][3] * v[1] + m[2][3] * v[2] + m[3][3] * v[3];
    vec4_copy(res, dest);
}

void mat4_inv(mat4 mat, mat4 dest) {
    float a = mat[0][0], b = mat[0][1], c = mat[0][2], d = mat[0][3],
            e = mat[1][0], f = mat[1][1], g = mat[1][2], h = mat[1][3],
            i = mat[2][0], j = mat[2][1], k = mat[2][2], l = mat[2][3],
            m = mat[3][0], n = mat[3][1], o = mat[3][2], p = mat[3][3],

            c1 = k * p - l * o, c2 = c * h - d * g, c3 = i * p - l * m,
            c4 = a * h - d * e, c5 = j * p - l * n, c6 = b * h - d * f,
            c7 = i * n - j * m, c8 = a * f - b * e, c9 = j * o - k * n,
            c10 = b * g - c * f, c11 = i * o - k * m, c12 = a * g - c * e,

            idt = 1.0f / (c8 * c1 + c4 * c9 + c10 * c3 + c2 * c7 - c12 * c5 - c6 * c11), ndt = -idt;

    dest[0][0] = (f * c1 - g * c5 + h * c9) * idt;
    dest[0][1] = (b * c1 - c * c5 + d * c9) * ndt;
    dest[0][2] = (n * c2 - o * c6 + p * c10) * idt;
    dest[0][3] = (j * c2 - k * c6 + l * c10) * ndt;

    dest[1][0] = (e * c1 - g * c3 + h * c11) * ndt;
    dest[1][1] = (a * c1 - c * c3 + d * c11) * idt;
    dest[1][2] = (m * c2 - o * c4 + p * c12) * ndt;
    dest[1][3] = (i * c2 - k * c4 + l * c12) * idt;

    dest[2][0] = (e * c5 - f * c3 + h * c7) * idt;
    dest[2][1] = (a * c5 - b * c3 + d * c7) * ndt;
    dest[2][2] = (m * c6 - n * c4 + p * c8) * idt;
    dest[2][3] = (i * c6 - j * c4 + l * c8) * ndt;

    dest[3][0] = (e * c9 - f * c11 + g * c7) * ndt;
    dest[3][1] = (a * c9 - b * c11 + c * c7) * idt;
    dest[3][2] = (m * c10 - n * c12 + o * c8) * ndt;
    dest[3][3] = (i * c10 - j * c12 + k * c8) * idt;
}
