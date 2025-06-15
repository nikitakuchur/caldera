#include "player_system.h"

#include <math.h>

#include "../custom_components.h"
#include "caldera/ecs/components.h"
#include "caldera/graphics/frontend/renderer.h"
#include "caldera/math/util.h"
#include "caldera/math/vec2.h"
#include "caldera/window/input.h"
#include "caldera/window/window.h"

static direction vec_to_dir(const vec2 v) {
    if (v[0] == 0 && v[1] == 0) {
        return DIR_LEFT;
    }

    const float vx = v[0];
    const float vy = v[1];

    const float rad = atan2f(vy, vx);
    int angle = (int) deg(rad); // to degrees

    if (angle < 0) angle += 360;
    angle = (angle + 45) % 360;

    //printf("angle=%d, dir=%d\n", angle, angle / 45);

    return angle / 90;
}

void player_system_update(const registry *r, float delta_time) {
    const view v = ecs_get_entities(r, PLAYER_CONTROLLER);

    for (int i = 0; i < v.components.size; i++) {
        const size_t *entity_id = darray_get(&v.entity_ids, i);
        const player_controller *controller = darray_get(&v.components, i);

        transform *t = ecs_get_component(r, *entity_id, TRANSFORM);
        if (t == nullptr) continue;

        facing_direction *facing_dir = ecs_get_component(r, *entity_id, FACING_DIRECTION);
        if (facing_dir == nullptr) continue;

        // direction
        vec2 cursor_position;
        window_get_cursor_position(cursor_position);
        renderer_screen_to_world(cursor_position, cursor_position);
        //printf("cursor_x=%f, cursor_y=%f\n", cursor_position[0], cursor_position[1]);

        vec2 dir_vector;
        vec2_sub(cursor_position, t->position, dir_vector);

        facing_dir->direction = vec_to_dir(dir_vector);

        // movement
        vec2 velocity;
        vec2_zero(velocity);

        if (window_get_key(CALDERA_KEY_W) == CALDERA_PRESS) {
            velocity[1] += 1.f;
        }
        if (window_get_key(CALDERA_KEY_S) == CALDERA_PRESS) {
            velocity[1] -= 1.f;
        }
        if (window_get_key(CALDERA_KEY_A) == CALDERA_PRESS) {
            velocity[0] -= 1.f;
        }
        if (window_get_key(CALDERA_KEY_D) == CALDERA_PRESS) {
            velocity[0] += 1.f;
        }

        vec2_normalize(velocity);

        float speed = controller->walk_speed;
        if (vec2_dot(dir_vector, velocity) >= 1) {
            speed *= controller->forward_speed_multiplier;
        } else {
            speed *= controller->backwards_speed_multiplier;
        }

        vec2_scale(velocity, speed * delta_time, velocity);

        t->position[0] += velocity[0];
        t->position[1] += velocity[1];
    }
}
