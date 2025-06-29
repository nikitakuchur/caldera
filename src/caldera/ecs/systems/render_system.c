#include "render_system.h"

#include "caldera/ecs/components.h"
#include "caldera/graphics/frontend/renderer.h"
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

void render_system_draw(const world *w) {
    const view v = ecs_get_entities(w, SPRITE_RENDERER);

    renderer_batch_begin(&b);

    for (u32 i = 0; i < v.components.size; i++) {
        const u32 *entity_id = darray_get(&v.entity_ids, i);
        const sprite_renderer *renderer = darray_get(&v.components, i);

        const transform *t = ecs_get_component(w, *entity_id, TRANSFORM);
        if (t == nullptr) continue;

        sprite s;
        s.size = renderer->size;
        s.color = renderer->color;

        s.position = t->position;
        s.rotation = t->rotation;
        s.scale = t->scale;

        s.origin = t->origin;

        s.texture = renderer->texture;
        s.texture_rect = renderer->texture_rect;

        renderer_batch_submit(&b, s);
    }

    renderer_batch_end(&b);
}
