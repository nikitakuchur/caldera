#include "cam.h"

#include "mat4.h"

void ortho(
    float left,
    float right,
    float bottom,
    float top,
    float nearZ,
    float farZ,
    mat4 dest
) {
    mat4_zero(dest);

    float rl = 1.0f / (right - left);
    float tb = 1.0f / (top - bottom);
    float fn = 1.0f / (farZ - nearZ);

    dest[0][0] = 2.0f * rl;
    dest[1][1] = 2.0f * tb;
    dest[2][2] = fn;
    dest[3][0] = -(right + left) * rl;
    dest[3][1] = -(top + bottom) * tb;
    dest[3][2] = -nearZ * fn;
    dest[3][3] = 1.0f;
}
