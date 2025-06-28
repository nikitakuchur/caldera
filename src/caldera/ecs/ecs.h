#ifndef ECS_H
#define ECS_H

#include "caldera/containers/bitset.h"
#include "caldera/containers/sparse_set.h"

#define MAX_COMPONENTS 100

typedef struct world {
    size_t entity_count;

    // Each entity can have up to 'MAX_COMPONENTS' components.
    // We store this information in one large bitset.
    // To access the next entity, add an offset of MAX_COMPONENTS.
    bitset component_masks;

    bool registered_components[MAX_COMPONENTS];
    sparse_set component_sets[MAX_COMPONENTS];
} world;

typedef struct view {
    darray entity_ids;
    darray components;
} view;

void ecs_init(world *w);

void ecs_free(world *w);

void ecs_register_component(world *w, size_t component_type, size_t component_size);

size_t ecs_create_entity(world *w);

void *ecs_add_component(world *w, size_t entity_id, size_t component_type);

bool ecs_has_component(const world *w, size_t entity_id, size_t component_type);

void *ecs_get_component(const world *w, size_t entity_id, size_t component_type);

view ecs_get_entities(const world *w, size_t component_type);

#endif //ECS_H
