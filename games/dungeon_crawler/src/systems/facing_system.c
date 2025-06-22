#include "facing_system.h"

#include "../custom_components.h"
#include "caldera/ecs/components.h"

void facing_system_update(registry *r) {
    const view v = ecs_get_entities(r, FACING_DIRECTION);

    for (int i = 0; i < v.components.size; i++) {
        const size_t *entity_id = darray_get(&v.entity_ids, i);
        const facing_direction *direction = darray_get(&v.components, i);

        sprite_renderer *renderer = ecs_get_component(r, *entity_id, SPRITE_RENDERER);
        if (renderer == nullptr) continue;

        uint32_t row_offset = direction->direction * 32;
        int height = (int) renderer->size[1];

        renderer->texture_rect.bottom_left[1] = row_offset;
        renderer->texture_rect.bottom_right[1] = row_offset;
        renderer->texture_rect.top_right[1] = height + row_offset;
        renderer->texture_rect.top_left[1] = height + row_offset;
    }
}
