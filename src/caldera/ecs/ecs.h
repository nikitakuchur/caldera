#ifndef ECS_H
#define ECS_H

#include "caldera/containers/bitset.h"
#include "caldera/containers/sparse_set.h"

#define MAX_COMPONENTS 64

typedef struct world {
    u32 entity_count;

    // Each entity can have up to 'MAX_COMPONENTS' components.
    // We store this information in one large bitset.
    // To access the next entity, add an offset of MAX_COMPONENTS.
    bitset component_masks;

    bitset registered_components;
    sparse_set component_sets[MAX_COMPONENTS];
} world;

typedef struct view {
    darray entity_ids;
    darray components;
} view;

b8 ecs_init(world *w);

void ecs_free(world *w);

void ecs_register_component(world *w, u32 component_type, u32 component_size);

u32 ecs_create_entity(world *w);

void *ecs_add_component(world *w, u32 entity_id, u32 component_type);

b8 ecs_has_component(const world *w, u32 entity_id, u32 component_type);

void *ecs_get_component(const world *w, u32 entity_id, u32 component_type);

view ecs_get_entities(const world *w, u32 component_type);

#endif //ECS_H
