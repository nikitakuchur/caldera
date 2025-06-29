#include "vec2.h"

#include <math.h>

vec2 vec2_new(f32 x, f32 y) {
    return (vec2){x, y};
}

vec2 vec2_zero() {
    return vec2_new(0.f, 0.f);
}

vec2 vec2_add(vec2 a, vec2 b) {
    return vec2_new(a.x + b.x, a.y + b.y);
}

vec2 vec2_sub(vec2 a, vec2 b) {
    return vec2_new(a.x - b.x, a.y - b.y);
}

vec2 vec2_scale(vec2 v, f32 s) {
    return vec2_new(v.x * s, v.y * s);
}

vec2 vec2_mul(vec2 a, vec2 b) {
    return vec2_new(a.x * b.x, a.y * b.y);
}

f32 vec2_dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}

f32 vec2_len(vec2 v) {
    return sqrtf(vec2_dot(v, v));
}

vec2 vec2_normalize(vec2 v) {
    f32 len = vec2_len(v);
    if (len == 0.f) {
        return vec2_zero();
    }
    return vec2_scale(v, 1.f / len);
}

vec2 vec2_rotate(vec2 v, f32 angle) {
    f32 c = cosf(angle);
    f32 s = sinf(angle);

    return vec2_new(
        c * v.x - s * v.y,
        s * v.x + c * v.y
    );
}
