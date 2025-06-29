#include "cam.h"

#include "mat4.h"

mat4 ortho(f32 left, f32 right, f32 bottom, f32 top, f32 near_z, f32 far_z) {
    f32 rl = 1.f / (right - left);
    f32 tb = 1.f / (top - bottom);
    f32 fn = 1.f / (far_z - near_z);

    mat4 r = mat4_zero();
    r.m00 = 2.f * rl;
    r.m11 = 2.f * tb;
    r.m22 = fn;
    r.m30 = -(right + left) * rl;
    r.m31 = -(top + bottom) * tb;
    r.m32 = -near_z * fn;
    r.m33 = 1.f;

    return r;
}
