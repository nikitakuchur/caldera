#include "ecs.h"
#include "components.h"
#include <mach/mach.h>

static void register_default_components(registry *registry) {
    ecs_register_component(registry, TRANSFORM, sizeof(transform));
    ecs_register_component(registry, SPRITE_RENDERER, sizeof(sprite_renderer));
    ecs_register_component(registry, SPRITE_ANIMATOR, sizeof(sprite_animator));
}

void ecs_init(registry *registry) {
    registry->entity_count = 0;
    bitset_init(&registry->component_masks, MAX_COMPONENTS * SPARSE_MAX_SIZE);
    for (size_t i = 0; i < MAX_COMPONENTS; i++) {
        registry->registered_components[i] = false;
    }
    register_default_components(registry);
}

void ecs_free(registry *registry) {
    registry->entity_count = 0;
    bitset_free(&registry->component_masks);
    for (size_t i = 0; i < MAX_COMPONENTS; i++) {
        if (registry->registered_components[i]) {
            sparse_set_free(&registry->component_sets[i]);
        }
        registry->registered_components[i] = false;
    }
}

void ecs_register_component(registry *registry, size_t component_type, size_t component_size) {
    sparse_set_init(&registry->component_sets[component_type], component_size);
    registry->registered_components[component_type] = true;
}

size_t ecs_create_entity(registry *registry) {
    size_t entity_id = registry->entity_count;
    registry->entity_count++;
    return entity_id;
}

static size_t calculate_bitset_index(size_t entity_id, size_t component_type) {
    size_t bitset_offset = entity_id * MAX_COMPONENTS;
    return bitset_offset + component_type;
}

void *ecs_add_component(registry *registry, size_t entity_id, size_t component_type) {
    if (!registry->registered_components[component_type]) {
        panic("the given component has not been registered");
    }

    size_t index = calculate_bitset_index(entity_id, component_type);
    if (bitset_get(&registry->component_masks, index)) {
        panic("the entity already has the given component");
    }

    bitset_set(&registry->component_masks, index, true);
    return sparse_set_add(&registry->component_sets[component_type], entity_id);
}

bool ecs_has_component(const registry *registry, size_t entity_id, size_t component_type) {
    if (!registry->registered_components[component_type]) {
        panic("the given component has not been registered");
    }
    size_t index = calculate_bitset_index(entity_id, component_type);
    return bitset_get(&registry->component_masks, index);
}

void *ecs_get_component(const registry *registry, size_t entity_id, size_t component_type) {
    if (!registry->registered_components[component_type]) {
        panic("the given component has not been registered");
    }
    size_t index = calculate_bitset_index(entity_id, component_type);
    if (!bitset_get(&registry->component_masks, index)) {
        return nullptr;
    }
    return sparse_set_get(&registry->component_sets[component_type], entity_id);
}

view ecs_get_entities(const registry *registry, size_t component_type) {
    if (!registry->registered_components[component_type]) {
        panic("the given component has not been registered");
    }
    const sparse_set set = registry->component_sets[component_type];
    return (view){
        .entity_ids = set.dense_array,
        .components = set.data
    };
}
