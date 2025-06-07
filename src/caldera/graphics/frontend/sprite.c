#include <math.h>
#include <caldera/graphics/frontend/sprite.h>
#include <caldera/math/vec2.h>
#include <caldera/math/vec4.h>

void sprite_init(sprite *s, vec2 size, texture t) {
    vec2_copy(s->size, size);
    vec4_copy(s->color, (vec4){1.f, 1.f, 1.f, 1.f});
    vec2_copy(s->position, (vec2){0.f, 0.f});
    s->rotation = 0;
    vec2_copy(s->scale, (vec2){1.f, 1.f});
    vec2_copy(s->origin, (vec2){12.f, 5.f});
    s->texture = t;
    s->texture_rect = (irect){
        0, 0,
        t.width, 0,
        t.width, t.height,
        0, t.height
    };
}

static rect rotate_rect(rect r, float angle) {
    rect result;

    vec2_copy(result.bottom_left, r.bottom_left);
    vec2_copy(result.bottom_right, r.bottom_right);
    vec2_copy(result.top_left, r.top_left);
    vec2_copy(result.top_right, r.top_right);

    vec2_rotate(result.bottom_left, angle);
    vec2_rotate(result.bottom_right, angle);
    vec2_rotate(result.top_right, angle);
    vec2_rotate(result.top_left, angle);

    return result;
}

static rect move_rect(rect r, vec2 v) {
    rect result;
    vec2_add(r.bottom_left, v, result.bottom_left);
    vec2_add(r.bottom_right, v, result.bottom_right);
    vec2_add(r.top_right, v, result.top_right);
    vec2_add(r.top_left, v, result.top_left);
    return result;
}

static rect scale_rect(rect r, vec2 v) {
    rect result;
    vec2_mul(r.bottom_left, v, result.bottom_left);
    vec2_mul(r.bottom_right, v, result.bottom_right);
    vec2_mul(r.top_right, v, result.top_right);
    vec2_mul(r.top_left, v, result.top_left);
    return result;
}

rect sprite_to_rect(sprite *s) {
    rect result;

    // build a rect
    result.bottom_left[0] = 0.f;
    result.bottom_left[1] = 0.f;

    result.bottom_right[0] = s->size[0];
    result.bottom_right[1] = 0.f;

    result.top_right[0] = s->size[0];
    result.top_right[1] = s->size[1];

    result.top_left[0] = 0.f;
    result.top_left[1] = s->size[1];

    // apply transformations
    vec2 v;
    vec2_scale(s->origin, -1, v);
    result = move_rect(result, v);
    result = scale_rect(result, s->scale);
    result = rotate_rect(result, s->rotation);

    vec2 rounded_position;
    vec2_copy(rounded_position, (vec2){s->position[0], s->position[1]});

    result = move_rect(result, rounded_position);

    return result;
}
