#include "ecs.h"
#include "components.h"
#include <mach/mach.h>

static void register_default_components(world *w) {
    ecs_register_component(w, TRANSFORM, sizeof(transform));
    ecs_register_component(w, SPRITE_RENDERER, sizeof(sprite_renderer));
    ecs_register_component(w, SPRITE_ANIMATOR, sizeof(sprite_animator));
}

void ecs_init(world *w) {
    w->entity_count = 0;
    bitset_init(&w->component_masks, MAX_COMPONENTS * SPARSE_MAX_SIZE);
    for (size_t i = 0; i < MAX_COMPONENTS; i++) {
        w->registered_components[i] = false;
    }
    register_default_components(w);
}

void ecs_free(world *w) {
    w->entity_count = 0;
    bitset_free(&w->component_masks);
    for (size_t i = 0; i < MAX_COMPONENTS; i++) {
        if (w->registered_components[i]) {
            sparse_set_free(&w->component_sets[i]);
        }
        w->registered_components[i] = false;
    }
}

void ecs_register_component(world *w, size_t component_type, size_t component_size) {
    sparse_set_init(&w->component_sets[component_type], component_size);
    w->registered_components[component_type] = true;
}

size_t ecs_create_entity(world *w) {
    size_t entity_id = w->entity_count;
    w->entity_count++;
    return entity_id;
}

static size_t calculate_bitset_index(size_t entity_id, size_t component_type) {
    size_t bitset_offset = entity_id * MAX_COMPONENTS;
    return bitset_offset + component_type;
}

void *ecs_add_component(world *w, size_t entity_id, size_t component_type) {
    if (!w->registered_components[component_type]) {
        panic("the given component has not been registered");
    }

    size_t index = calculate_bitset_index(entity_id, component_type);
    if (bitset_get(&w->component_masks, index)) {
        panic("the entity already has the given component");
    }

    bitset_set(&w->component_masks, index, true);
    return sparse_set_add(&w->component_sets[component_type], entity_id);
}

bool ecs_has_component(const world *w, size_t entity_id, size_t component_type) {
    if (!w->registered_components[component_type]) {
        panic("the given component has not been registered");
    }
    size_t index = calculate_bitset_index(entity_id, component_type);
    return bitset_get(&w->component_masks, index);
}

void *ecs_get_component(const world *w, size_t entity_id, size_t component_type) {
    if (!w->registered_components[component_type]) {
        panic("the given component has not been registered");
    }
    size_t index = calculate_bitset_index(entity_id, component_type);
    if (!bitset_get(&w->component_masks, index)) {
        return nullptr;
    }
    return sparse_set_get(&w->component_sets[component_type], entity_id);
}

view ecs_get_entities(const world *w, size_t component_type) {
    if (!w->registered_components[component_type]) {
        panic("the given component has not been registered");
    }
    const sparse_set set = w->component_sets[component_type];
    return (view){
        .entity_ids = set.dense_array,
        .components = set.data
    };
}
