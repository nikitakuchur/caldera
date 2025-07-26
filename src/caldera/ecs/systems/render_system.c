#include "render_system.h"

#include "caldera/ecs/components.h"
#include "caldera/graphics/frontend/renderer.h"
#include "caldera/graphics/frontend/text.h"
#include "caldera/window/window.h"

static batch b;

static void resize_callback(u32 width, u32 height) {
    renderer_set_size(width, height, 100.f);
}

static void update_render_size() {
    ivec2 window_size = window_get_size();
    renderer_set_size(window_size.x, window_size.y, 100.f);
    window_set_resize_callback(&resize_callback);
}

void render_system_init() {
    renderer_init();
    update_render_size();
    renderer_batch_init(&b);
}

void render_system_free() {
    renderer_batch_free(&b);
    renderer_free();
}

static void render_sprites(const world *w) {
    const view v = ecs_get_entities(w, EC_SPRITE);

    for (u32 i = 0; i < v.components.size; i++) {
        const u32 *entity_id = darray_get(&v.entity_ids, i);
        const ec_sprite *ec_sprite = darray_get(&v.components, i);

        const ec_transform *transform = ecs_get_component(w, *entity_id, EC_TRANSFORM);
        if (transform == nullptr) continue;

        sprite s;
        s.size = ec_sprite->size;
        s.color = ec_sprite->color;

        s.position = transform->position;
        s.rotation = transform->rotation;
        s.scale = transform->scale;

        s.origin = transform->origin;

        s.texture = ec_sprite->texture;
        s.texture_rect = ec_sprite->texture_rect;

        renderer_batch_submit_sprite(&b, s);
    }
}

void render_ui(const world *w) {
    const view v = ecs_get_entities(w, EC_TEXT);

    for (u32 i = 0; i < v.components.size; i++) {
        const u32 *entity_id = darray_get(&v.entity_ids, i);
        const ec_text *ec_text = darray_get(&v.components, i);

        const ec_transform *transform = ecs_get_component(w, *entity_id, EC_TRANSFORM);
        if (transform == nullptr) continue;

        text t = {
            .str = ec_text->str,
            .color = ec_text->color,

            .position = transform->position,
            .rotation = transform->rotation,
            .scale = transform->scale,

            .origin = transform->origin,
        };

        renderer_batch_submit_text(&b, ec_text->font, t);
    }
}

void render_system_draw(const world *w) {
    renderer_batch_begin(&b);
    render_sprites(w);
    render_ui(w);
    renderer_batch_end(&b);
}
