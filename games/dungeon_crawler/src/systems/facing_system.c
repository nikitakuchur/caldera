#include "facing_system.h"

#include "../custom_components.h"
#include "caldera/ecs/components.h"

void facing_system_update(const world *r) {
    const view v = ecs_get_entities(r, FACING_DIRECTION);

    for (size_t i = 0; i < v.components.size; i++) {
        const size_t *entity_id = darray_get(&v.entity_ids, i);
        const facing_direction *direction = darray_get(&v.components, i);

        sprite_renderer *renderer = ecs_get_component(r, *entity_id, SPRITE_RENDERER);
        if (renderer == nullptr) continue;

        uint32_t row_offset = direction->direction * 32;
        int32_t height = (int32_t) renderer->size.y;

        renderer->texture_rect.bottom_left.y = (int32_t) row_offset;
        renderer->texture_rect.bottom_right.y = (int32_t) row_offset;
        renderer->texture_rect.top_right.y = (int32_t) (height + row_offset);
        renderer->texture_rect.top_left.y = (int32_t) (height + row_offset);
    }
}
