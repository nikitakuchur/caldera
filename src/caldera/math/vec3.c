#include "vec3.h"

#include <math.h>

vec3 vec3_new(f32 x, f32 y, f32 z) {
    return (vec3){x, y, z};
}

vec3 vec3_zero() {
    return vec3_new(0.f, 0.f, 0.f);
}

vec3 vec3_add(vec3 a, vec3 b) {
    return vec3_new(a.x + b.x, a.y + b.y, a.z + b.z);
}

vec3 vec3_sub(vec3 a, vec3 b) {
    return vec3_new(a.x - b.x, a.y - b.y, a.z - b.z);
}

vec3 vec3_scale(vec3 v, f32 s) {
    return vec3_new(v.x * s, v.y * s, v.z * s);
}

vec3 vec3_mul(vec3 a, vec3 b) {
    return vec3_new(a.x * b.x, a.y * b.y, a.z * b.z);
}

vec3 vec3_cross(vec3 a, vec3 b) {
    return vec3_new(
        a.y * b.z - a.z * b.y,
        a.z * b.x - a.x * b.z,
        a.x * b.y - a.y * b.x
    );
}

f32 vec3_dot(vec3 a, vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

f32 vec3_len(vec3 v) {
    return sqrtf(vec3_dot(v, v));
}

vec3 vec3_normalize(vec3 v) {
    f32 len = vec3_len(v);
    if (len == 0.f) {
        return vec3_zero();
    }
    return vec3_scale(v, 1.f / len);
}

vec3 vec3_rotate(vec3 v, f32 angle, vec3 axis) {
    vec3 k = vec3_normalize(axis);

    f32 c = cosf(angle);
    f32 s = sinf(angle);

    vec3 v1 = vec3_scale(v, c);

    vec3 v2 = vec3_cross(k, v);
    v2 = vec3_scale(v2, s);

    v1 = vec3_add(v1, v2);

    v2 = vec3_scale(k, vec3_dot(k, v) * (1.f - c));
    return vec3_add(v1, v2);
}
