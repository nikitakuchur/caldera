#include "render_system.h"

#include "caldera/ecs/components.h"
#include "caldera/graphics/frontend/renderer.h"
#include "caldera/math/vec2.h"
#include "caldera/math/vec4.h"
#include "caldera/window/window.h"
#include <string.h>

static batch b;

static void resize_callback(int32_t width, int32_t height) {
    renderer_set_size(width, height, 100.f);
}

static void update_render_size() {
    int32_t width, height;
    window_get_size(&width, &height);
    renderer_set_size(width, height, 100.f);
    window_set_resize_callback(&resize_callback);
}

void render_system_init() {
    renderer_init();
    update_render_size();
    renderer_batch_init(&b);
}

void render_system_draw(const registry *r) {
    const view v = ecs_get_entities(r, SPRITE_RENDERER);

    renderer_frame_begin();
    renderer_set_clear_color((vec4){0.11f, 0.1f, 0.15f, 1.0f});

    renderer_batch_begin(&b);

    for (size_t i = 0; i < v.components.size; i++) {
        const size_t *entity_id = darray_get(&v.entity_ids, i);
        const sprite_renderer *renderer = darray_get(&v.components, i);

        const transform *t = ecs_get_component(r, *entity_id, TRANSFORM);
        if (t == nullptr) continue;

        sprite s;
        vec2_copy(s.size, renderer->size);
        vec4_copy(s.color, renderer->color);

        vec2_copy(s.position, t->position);
        s.rotation = t->rotation;
        vec2_copy(s.scale, t->scale);

        vec2_copy(s.origin, t->origin);

        s.texture = renderer->texture;
        memcpy(&s.texture_rect, &renderer->texture_rect, sizeof(irect));

        renderer_batch_submit(&b, s);
    }

    renderer_batch_end(&b);

    renderer_frame_end();
}

void render_system_destroy() {
    renderer_batch_free(&b);
    renderer_free();
}
