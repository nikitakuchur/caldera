#include "ecs.h"

#include "components.h"
#include "caldera/utils/panic.h"

static void register_default_components(world *w) {
    ecs_register_component(w, TRANSFORM, sizeof(transform));
    ecs_register_component(w, SPRITE_RENDERER, sizeof(sprite_renderer));
    ecs_register_component(w, SPRITE_ANIMATOR, sizeof(sprite_animator));
}

b8 ecs_init(world *w) {
    w->entity_count = 0;

    b8 success = bitset_init(&w->component_masks, MAX_COMPONENTS * SPARSE_MAX_SIZE);
    if (!success) {
        panic("failed to initialize ecs component masks");
    }

    success = bitset_init(&w->registered_components, MAX_COMPONENTS);
    if (!success) {
        panic("failed to initialize ecs registered components");
    }

    register_default_components(w);
    return true;
}

void ecs_free(world *w) {
    w->entity_count = 0;
    bitset_free(&w->component_masks);
    bitset_free(&w->registered_components);
}

void ecs_register_component(world *w, u32 component_type, u32 component_size) {
    sparse_set_init(&w->component_sets[component_type], component_size);
    bitset_set(&w->registered_components, component_type, true);
}

u32 ecs_create_entity(world *w) {
    u32 entity_id = w->entity_count;
    w->entity_count++;
    return entity_id;
}

static u32 calculate_bitset_index(u32 entity_id, u32 component_type) {
    u32 bitset_offset = entity_id * MAX_COMPONENTS;
    return bitset_offset + component_type;
}

void *ecs_add_component(world *w, u32 entity_id, u32 component_type) {
    if (!bitset_get(&w->registered_components, component_type)) {
        panic("the given component has not been registered");
    }

    u32 index = calculate_bitset_index(entity_id, component_type);
    if (bitset_get(&w->component_masks, index)) {
        panic("the entity already has the given component");
    }

    bitset_set(&w->component_masks, index, true);
    return sparse_set_add(&w->component_sets[component_type], entity_id);
}

b8 ecs_has_component(const world *w, u32 entity_id, u32 component_type) {
    if (!bitset_get(&w->registered_components, component_type)) {
        panic("the given component has not been registered");
    }
    u32 index = calculate_bitset_index(entity_id, component_type);
    return bitset_get(&w->component_masks, index);
}

void *ecs_get_component(const world *w, u32 entity_id, u32 component_type) {
    if (!bitset_get(&w->registered_components, component_type)) {
        panic("the given component has not been registered");
    }
    u32 index = calculate_bitset_index(entity_id, component_type);
    if (!bitset_get(&w->component_masks, index)) {
        return nullptr;
    }
    return sparse_set_get(&w->component_sets[component_type], entity_id);
}

view ecs_get_entities(const world *w, u32 component_type) {
    if (!bitset_get(&w->registered_components, component_type)) {
        panic("the given component has not been registered");
    }
    sparse_set set = w->component_sets[component_type];
    return (view){
        .entity_ids = set.dense_array,
        .components = set.data
    };
}
