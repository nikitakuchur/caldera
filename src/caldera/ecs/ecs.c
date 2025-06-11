#include "ecs.h"
#include "components.h"
#include <mach/mach.h>

static void register_default_components(registry *registry) {
    ecs_register_component(registry, TRANSFORM, sizeof(transform));
    ecs_register_component(registry, SPRITE_RENDERER, sizeof(sprite_renderer));
    ecs_register_component(registry, SPRITE_ANIMATOR, sizeof(sprite_animator));
}

void ecs_init(registry *registry) {
    darray_init(&registry->entity_masks, sizeof(bool) * MAX_COMPONENTS, 8);
    for (int i = 0; i < MAX_COMPONENTS; i++) {
        registry->registered_components[i] = false;
    }
    register_default_components(registry);
}

void ecs_free(registry *registry) {
    darray_free(&registry->entity_masks);
    for (int i = 0; i < MAX_COMPONENTS; i++) {
        if (registry->registered_components[i]) {
            sparse_set_free(&registry->components[i]);
        }
        registry->registered_components[i] = false;
    }
}

void ecs_register_component(registry *registry, const size_t component_type, const size_t component_size) {
    sparse_set_init(&registry->components[component_type], component_size);
    registry->registered_components[component_type] = true;
}

size_t ecs_create_entity(registry *registry) {
    const size_t entity_id = registry->entity_masks.size;
    bool *mask = darray_add(&registry->entity_masks);
    for (int i = 0; i < MAX_COMPONENTS; i++) {
        mask[i] = false;
    }
    return entity_id;
}

void* ecs_add_component(registry *registry, const size_t entity_id, const size_t component_type) {
    if (!registry->registered_components[component_type]) {
        panic("the given component has not been registered");
    }
    bool *mask = darray_get(&registry->entity_masks, entity_id);
    if (mask[component_type]) {
        panic("the entity already has the given component");
    }
    mask[component_type] = true;
    return sparse_set_add(&registry->components[component_type], entity_id);
}

bool ecs_has_component(const registry *registry, const size_t entity_id, const size_t component_type) {
    if (!registry->registered_components[component_type]) {
        panic("the given component has not been registered");
    }
    const bool *mask = darray_get(&registry->entity_masks, entity_id);
    return mask[component_type];
}

void* ecs_get_component(const registry *registry, const size_t entity_id, const size_t component_type) {
    if (!registry->registered_components[component_type]) {
        panic("the given component has not been registered");
    }
    const bool *mask = darray_get(&registry->entity_masks, entity_id);
    if (!mask[component_type]) {
        return nullptr;
    }
    return sparse_set_get(&registry->components[component_type], entity_id);
}

view ecs_get_entities(const registry *registry, const size_t component_type) {
    if (!registry->registered_components[component_type]) {
        panic("the given component has not been registered");
    }
    const sparse_set set = registry->components[component_type];
    return (view){
        .entity_ids = set.dense_array,
        .components = set.data
    };
}
