#include <caldera/graphics/frontend/sprite.h>

#include <caldera/math/vec2.h>
#include <caldera/math/vec4.h>

void sprite_init(sprite *s, ivec2 size, texture t) {
    s->size = size;
    s->color = vec4_new(1.f, 1.f, 1.f, 1.f);
    s->position = vec2_zero();
    s->rotation = 0;
    s->scale = vec2_new(1.f, 1.f);
    s->origin = vec2_zero();
    s->texture = t;
    s->texture_rect = (irect){
        0, 0,
        t.size.x, 0,
        t.size.x, t.size.y,
        0, t.size.y
    };
}
