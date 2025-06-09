#include "animator.h"

void animator_update_frame(animator *animator, sprite* sprite, const float delta_time) {
    const animation animation = animator->animation;
    const int actual_frame = (int) animator->frame % animation.frame_num;

    const int width = (int) sprite->size[0];
    sprite->texture_rect.bottom_left[0] = actual_frame * width;
    sprite->texture_rect.bottom_right[0] = (actual_frame + 1) * width;
    sprite->texture_rect.top_right[0] = (actual_frame + 1) * width;
    sprite->texture_rect.top_left[0] = actual_frame * width;

    animator->frame += animation.speed * delta_time;
}
