#include "util.h"

#include "types.h"

f32 rad(f32 deg) {
    return deg * (f32) PI / 180.0f;
}

f32 deg(f32 rad) {
    return rad * (f32) (180.0f / PI);
}
