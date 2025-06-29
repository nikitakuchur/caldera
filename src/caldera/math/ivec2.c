#include "ivec2.h"

ivec2 ivec2_new(i32 x, i32 y) {
    return (ivec2){x, y};
}

ivec2 ivec2_zero() {
    return ivec2_new(0, 0);
}

ivec2 ivec2_add(ivec2 a, ivec2 b) {
    return ivec2_new(a.x + b.x, a.y + b.y);
}

ivec2 ivec2_sub(ivec2 a, ivec2 b) {
    return ivec2_new(a.x - b.x, a.y - b.y);
}
