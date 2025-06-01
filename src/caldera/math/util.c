#include "util.h"

#include "types.h"

float rad(const float deg) {
    return deg * (float) PI / 180.0f;
}

float deg(const float rad) {
    return rad * (float) (180.0f / PI);
}