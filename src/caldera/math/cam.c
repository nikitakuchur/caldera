#include "cam.h"

#include "mat4.h"

mat4 ortho(float left, float right, float bottom, float top, float near_z, float far_z) {
    float rl = 1.f / (right - left);
    float tb = 1.f / (top - bottom);
    float fn = 1.f / (far_z - near_z);

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
