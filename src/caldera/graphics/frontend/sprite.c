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

static rect rotate_rect(rect r, f32 angle) {
    r.bottom_left = vec2_rotate(r.bottom_left, angle);
    r.bottom_right = vec2_rotate(r.bottom_right, angle);
    r.top_right = vec2_rotate(r.top_right, angle);
    r.top_left = vec2_rotate(r.top_left, angle);
    return r;
}

static rect move_rect(rect r, vec2 v) {
    r.bottom_left = vec2_add(r.bottom_left, v);
    r.bottom_right = vec2_add(r.bottom_right, v);
    r.top_right = vec2_add(r.top_right, v);
    r.top_left = vec2_add(r.top_left, v);
    return r;
}

static rect scale_rect(rect r, vec2 v) {
    r.bottom_left = vec2_mul(r.bottom_left, v);
    r.bottom_right = vec2_mul(r.bottom_right, v);
    r.top_right = vec2_mul(r.top_right, v);
    r.top_left = vec2_mul(r.top_left, v);
    return r;
}

rect sprite_to_rect(const sprite *s) {
    rect result = (rect){
        0.f, 0.f,
        (f32) s->size.x, 0.f,
        (f32) s->size.x, (f32) s->size.y,
        0.f, (f32) s->size.y
    };

    // apply transformations
    vec2 v = vec2_scale(s->origin, -1);
    result = move_rect(result, v);
    result = scale_rect(result, s->scale);
    result = rotate_rect(result, s->rotation);
    result = move_rect(result, s->position);

    return result;
}
