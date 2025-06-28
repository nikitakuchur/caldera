#include "animation_system.h"

#include "caldera/ecs/components.h"

void animation_system_update(const world *r, float delta_time) {
    const view v = ecs_get_entities(r, SPRITE_ANIMATOR);

    for (size_t i = 0; i < v.components.size; i++) {
        const size_t *entity_id = darray_get(&v.entity_ids, i);
        sprite_animator *animator = darray_get(&v.components, i);

        sprite_renderer *renderer = ecs_get_component(r, *entity_id, SPRITE_RENDERER);
        if (renderer == nullptr) continue;

        animation animation = animator->animation;
        int32_t actual_frame = (int32_t) animator->frame % animation.frame_num;

        int32_t width = (int32_t) renderer->size.x;
        int32_t height = (int32_t) renderer->size.y;

        renderer->texture_rect = (irect) {
            .bottom_left = {animation.x_offset + actual_frame * width, animation.y_offset},
            .bottom_right = {animation.x_offset + (actual_frame + 1) * width, animation.y_offset},
            .top_right = {animation.x_offset + (actual_frame + 1) * width, animation.y_offset + height},
            .top_left = {animation.x_offset + actual_frame * width, animation.y_offset + height}
        };

        animator->frame += animation.speed * delta_time;
    }
}
