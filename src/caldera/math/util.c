#include "util.h"

#include "types.h"

float rad(float deg) {
    return deg * (float) PI / 180.0f;
}

float deg(float rad) {
    return rad * (float) (180.0f / PI);
}
