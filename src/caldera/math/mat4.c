#include "mat4.h"

#include "vec4.h"

mat4 mat4_identity() {
    return (mat4){MAT4_IDENTITY_INIT};
}

mat4 mat4_zero() {
    return (mat4){
        {
            vec4_zero(),
            vec4_zero(),
            vec4_zero(),
            vec4_zero()
        }
    };
}

mat4 mat4_mul(mat4 a, mat4 b) {
    mat4 r;

    for (int i = 0; i < 4; ++i) {
        vec4 col = b.raw[i];  // b's i-th column
        r.raw[i].x = a.m00 * col.x + a.m01 * col.y + a.m02 * col.z + a.m03 * col.w;
        r.raw[i].y = a.m10 * col.x + a.m11 * col.y + a.m12 * col.z + a.m13 * col.w;
        r.raw[i].z = a.m20 * col.x + a.m21 * col.y + a.m22 * col.z + a.m23 * col.w;
        r.raw[i].w = a.m30 * col.x + a.m31 * col.y + a.m32 * col.z + a.m33 * col.w;
    }

    return r;
}

vec4 mat4_mulv(mat4 m, vec4 v) {
    vec4 r;
    r.x = m.m00 * v.x + m.m10 * v.y + m.m20 * v.z + m.m30 * v.w;
    r.y = m.m01 * v.x + m.m11 * v.y + m.m21 * v.z + m.m31 * v.w;
    r.z = m.m02 * v.x + m.m12 * v.y + m.m22 * v.z + m.m32 * v.w;
    r.w = m.m03 * v.x + m.m13 * v.y + m.m23 * v.z + m.m33 * v.w;
    return r;
}
