#include "vec2.h"

#include <math.h>

vec2 vec2_new(float x, float y) {
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

vec2 vec2_scale(vec2 v, float s) {
    return vec2_new(v.x * s, v.y * s);
}

vec2 vec2_mul(vec2 a, vec2 b) {
    return vec2_new(a.x * b.x, a.y * b.y);
}

float vec2_dot(vec2 a, vec2 b) {
    return a.x * b.x + a.y * b.y;
}

float vec2_len(vec2 v) {
    return sqrtf(vec2_dot(v, v));
}

vec2 vec2_normalize(vec2 v) {
    float len = vec2_len(v);
    if (len == 0.f) {
        return vec2_zero();
    }
    return vec2_scale(v, 1.f / len);
}

vec2 vec2_rotate(vec2 v, float angle) {
    float c = cosf(angle);
    float s = sinf(angle);

    return vec2_new(
        c * v.x - s * v.y,
        s * v.x + c * v.y
    );
}
