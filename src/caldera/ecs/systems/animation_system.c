#include "animation_system.h"

#include "caldera/ecs/components.h"

void animation_system_update(const world *w, f32 delta_time) {
    const view v = ecs_get_entities(w, SPRITE_ANIMATOR);

    for (u32 i = 0; i < v.components.size; i++) {
        const u32 *entity_id = darray_get(&v.entity_ids, i);
        sprite_animator *animator = darray_get(&v.components, i);

        sprite_renderer *renderer = ecs_get_component(w, *entity_id, SPRITE_RENDERER);
        if (renderer == nullptr) continue;

        animation animation = animator->animation;
        i32 actual_frame = (i32) animator->current_frame % animation.frame_num;

        i32 width = renderer->size.x;
        i32 height = renderer->size.y;

        renderer->texture_rect = (irect){
            .bottom_left = {animation.offset.x + actual_frame * width, animation.offset.y},
            .bottom_right = {animation.offset.x + (actual_frame + 1) * width, animation.offset.y},
            .top_right = {animation.offset.x + (actual_frame + 1) * width, animation.offset.y + height},
            .top_left = {animation.offset.x + actual_frame * width, animation.offset.y + height}
        };

        animator->current_frame += animation.speed * delta_time;
    }
}
