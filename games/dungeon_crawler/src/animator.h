#ifndef ANIMATOR_H
#define ANIMATOR_H

#include "caldera/graphics/frontend/sprite.h"

typedef struct animation {
    int x_offset;
    int y_offset;

    int frame_num;
    float speed;
} animation;

typedef struct animator {
    float frame;
    animation animation;
} animator;

void animator_update_frame(animator *animator, sprite* sprite, float delta_time);

#endif //ANIMATOR_H
