#include "ecs.h"

#include <stdio.h>

#include "components.h"
#include "caldera/utils/log.h"

static void register_default_components(world *w) {
    ecs_register_component(w, EC_TRANSFORM, sizeof(ec_transform), nullptr);
    ecs_register_component(w, EC_SPRITE, sizeof(ec_sprite), nullptr);
    ecs_register_component(w, EC_ANIMATOR, sizeof(ec_animator), nullptr);
    ecs_register_component(w, EC_TEXT, sizeof(ec_text), ec_text_free);
}

b8 ecs_init(world *w) {
    w->entity_count = 0;

    b8 success = bitset_init(&w->component_masks, MAX_COMPONENTS * SPARSE_MAX_SIZE);
    if (!success) {
        fatalf("failed to initialize ecs component masks");
    }

    success = bitset_init(&w->registered_components, MAX_COMPONENTS);
    if (!success) {
        fatalf("failed to initialize ecs registered components");
    }

    for (u32 i = 0; i < MAX_COMPONENTS; i++) {
        w->component_destructors[i] = nullptr;
    }

    register_default_components(w);
    return true;
}

static void call_destructors(world *w, u32 component_type) {
    ec_destructor_fn destructor = w->component_destructors[component_type];
    if (destructor != nullptr) {
        darray components = w->component_sets[component_type].data;
        for (u32 i = 0; i < components.size; i++) {
            void *component = darray_get(&components, i);
            destructor(component);
            printf("the component has been freed!");
        }
    }
}

void ecs_free(world *w) {
    w->entity_count = 0;
    bitset_free(&w->component_masks);

    for (u32 i = 0; i < MAX_COMPONENTS; i++) {
        if (bitset_get(&w->registered_components, i)) {
            // call destructors
            call_destructors(w, i);
            sparse_set_free(&w->component_sets[i]);
        }
    }

    bitset_free(&w->registered_components);
}

void ecs_register_component(world *w, u32 component_type, u32 component_size, ec_destructor_fn destructor) {
    sparse_set_init(&w->component_sets[component_type], component_size);
    bitset_set(&w->registered_components, component_type, true);
    w->component_destructors[component_type] = destructor;
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
        fatalf("the given component has not been registered");
    }

    u32 index = calculate_bitset_index(entity_id, component_type);
    if (bitset_get(&w->component_masks, index)) {
        fatalf("the entity already has the given component");
    }

    bitset_set(&w->component_masks, index, true);
    return sparse_set_add(&w->component_sets[component_type], entity_id);
}

b8 ecs_has_component(const world *w, u32 entity_id, u32 component_type) {
    if (!bitset_get(&w->registered_components, component_type)) {
        fatalf("the given component has not been registered");
    }
    u32 index = calculate_bitset_index(entity_id, component_type);
    return bitset_get(&w->component_masks, index);
}

void *ecs_get_component(const world *w, u32 entity_id, u32 component_type) {
    if (!bitset_get(&w->registered_components, component_type)) {
        fatalf("the given component has not been registered");
    }
    u32 index = calculate_bitset_index(entity_id, component_type);
    if (!bitset_get(&w->component_masks, index)) {
        return nullptr;
    }
    return sparse_set_get(&w->component_sets[component_type], entity_id);
}

view ecs_get_entities(const world *w, u32 component_type) {
    if (!bitset_get(&w->registered_components, component_type)) {
        fatalf("the given component has not been registered");
    }
    sparse_set set = w->component_sets[component_type];
    return (view){
        .entity_ids = set.dense_array,
        .components = set.data
    };
}
