#include "facing_system.h"

#include "../custom_components.h"
#include "caldera/ecs/components.h"

void facing_system_update(const world *w) {
    const view v = ecs_get_entities(w, FACING_DIRECTION);

    for (u32 i = 0; i < v.components.size; i++) {
        const u32 *entity_id = darray_get(&v.entity_ids, i);
        const facing_direction *direction = darray_get(&v.components, i);

        sprite_renderer *renderer = ecs_get_component(w, *entity_id, SPRITE_RENDERER);
        if (renderer == nullptr) continue;

        u32 row_offset = direction->direction * 32;
        i32 height = renderer->size.y;

        renderer->texture_rect.bottom_left.y = (i32) row_offset;
        renderer->texture_rect.bottom_right.y = (i32) row_offset;
        renderer->texture_rect.top_right.y = (i32) (height + row_offset);
        renderer->texture_rect.top_left.y = (i32) (height + row_offset);
    }
}
