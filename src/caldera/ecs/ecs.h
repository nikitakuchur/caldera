#ifndef ENTITY_REGISTRY_H
#define ENTITY_REGISTRY_H

#include "caldera/containers/bitset.h"
#include "caldera/containers/sparse_set.h"

#define MAX_COMPONENTS 100

typedef struct registry {
    size_t entity_count;

    // Each entity can have up to 'MAX_COMPONENTS' components.
    // We store this information in one large bitset.
    // To access the next entity, add an offset of MAX_COMPONENTS.
    bitset component_masks;

    bool registered_components[MAX_COMPONENTS];
    sparse_set component_sets[MAX_COMPONENTS];
} registry;

typedef struct view {
    darray entity_ids;
    darray components;
} view;

void ecs_init(registry *registry);

void ecs_free(registry *registry);

void ecs_register_component(registry *registry, size_t component_type, size_t component_size);

size_t ecs_create_entity(registry *registry);

void *ecs_add_component(registry *registry, size_t entity_id, size_t component_type);

bool ecs_has_component(const registry *registry, size_t entity_id, size_t component_type);

void *ecs_get_component(const registry *registry, size_t entity_id, size_t component_type);

view ecs_get_entities(const registry *registry, size_t component_type);

#endif //ENTITY_REGISTRY_H
