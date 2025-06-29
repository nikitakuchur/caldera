#include "vec4.h"

vec4 vec4_new(f32 x, f32 y, f32 z, f32 w) {
    return (vec4){x, y, z, w};
}

vec4 vec4_zero() {
    return vec4_new(0.f, 0.f, 0.f, 0.f);
}

vec4 vec4_add(vec4 a, vec4 b) {
    return vec4_new(a.x + b.x, a.y + b.y, a.z + b.z, a.w + b.w);
}

vec4 vec4_scale(vec4 v, f32 s) {
    return vec4_new(v.x * s, v.y * s, v.z * s, v.w * s);
}
