#include "game.h"

#include <math.h>
#include <stdio.h>
#include <caldera/graphics/frontend/sprite.h>

#include <caldera/graphics/frontend/renderer.h>
#include <caldera/math/vec2.h>
#include <caldera/window/window.h>

#include "caldera/math/util.h"
#include "caldera/window/input.h"

static float render_size = 120;

struct {
    texture texture;
    sprite sprite;

    int direction;
    float walk_speed;
} player;

typedef enum {
    DIR_RIGHT = 0,
    DIR_UP_RIGHT,
    DIR_UP,
    DIR_UP_LEFT,
    DIR_LEFT,
    DIR_DOWN_LEFT,
    DIR_DOWN,
    DIR_DOWN_RIGHT,
} direction;

static batch main_batch;

static void resize_callback(int width, int height) {
    renderer_set_size(width, height, render_size);
}

static void update_render_size() {
    int width, height;
    window_get_size(&width, &height);
    renderer_set_size(width, height, render_size);
    window_set_resize_callback(&resize_callback);
}

static direction compute_player_direction(const vec2 v) {
    if (v[0] == 0 && v[1] == 0) {
        return player.direction;
    }

    const float vx = v[0];
    const float vy = v[1];

    const float rad = atan2f(vy, vx); // screen Y often flipped, adjust as needed
    int angle = (int) deg(rad); // to degrees

    if (angle < 0) angle += 360;
    angle = (angle + 23) % 360;

    //printf("angle=%d, dir=%d\n", angle, angle / 45);

    return angle / 45;
}

static void update_player_direction(vec2 v) {
    player.direction = compute_player_direction(v);
    const uint32_t row_offset = player.direction * 25;
    player.sprite.texture_rect = (irect){
        0, row_offset,
        25, row_offset,
        25, 25 + row_offset,
        0, 25 + row_offset
    };
}

void game_init() {
    renderer_init();
    update_render_size();

    player.texture = texture_create("../res/textures/character.png");
    sprite_init(&player.sprite, (vec2){25.0f, 25.0f}, player.texture);

    player.direction = 5;
    player.walk_speed = 30.f;
    update_player_direction((vec2){-1, -1});

    main_batch = renderer_batch_create();
}

/*
 * This function deals with jittering during diagonal movement.
 * If remainder in X is larger → move full X pixels, adjust Y accordingly
 * If remainder in Y is larger → move full Y pixels, adjust X accordingly
 * Remainder accumulates sub-pixel values until enough to move a whole pixel.
 */
static void move_player(const vec2 velocity) {
    static vec2 remainder = {0, 0};

    remainder[0] += velocity[0];
    remainder[1] += velocity[1];

    float abs_dx = fabsf(remainder[0]);
    float abs_dy = fabsf(remainder[1]);

    if (abs_dx == 0.0f && abs_dy == 0.0f) {
        return; // no movement needed
    }

    int dominant_axis = abs_dx > abs_dy ? 0 : 1;
    int secondary_axis = 1 - dominant_axis;

    int move_pixels = (int) remainder[dominant_axis];
    if (move_pixels == 0) {
        return; // not enough remainder to move whole pixels yet
    }

    float slope = velocity[dominant_axis] == 0 ? 0.f : velocity[secondary_axis] / velocity[dominant_axis];
    float move_secondary = slope * (float) move_pixels;

    player.sprite.position[dominant_axis] += (float) move_pixels;
    player.sprite.position[secondary_axis] += move_secondary;

    remainder[dominant_axis] -= (float) move_pixels;
    remainder[secondary_axis] -= move_secondary;
}

void game_update(const float delta_time) {
    vec2 velocity;
    vec2_zero(velocity);

    if (window_get_key(CALDERA_KEY_W) == CALDERA_PRESS) {
        velocity[1] += 1.0f;
    }
    if (window_get_key(CALDERA_KEY_S) == CALDERA_PRESS) {
        velocity[1] -= 1.0f;
    }
    if (window_get_key(CALDERA_KEY_A) == CALDERA_PRESS) {
        velocity[0] -= 1.0f;
    }
    if (window_get_key(CALDERA_KEY_D) == CALDERA_PRESS) {
        velocity[0] += 1.0f;
    }

    vec2_normalize(velocity);
    vec2_scale(velocity, player.walk_speed * delta_time, velocity);

    vec2 cursor_position;
    window_get_cursor_position(cursor_position);
    renderer_screen_to_world(cursor_position, cursor_position);
    //printf("cursor_x=%f, cursor_y=%f\n", cursor_position[0], cursor_position[1]);

    vec2 dir_vector;
    vec2_sub(cursor_position, player.sprite.position, dir_vector);

    update_player_direction(dir_vector);
    move_player(velocity);
    //printf("player_x=%f, player_y=%f\n", player.sprite.position[0], player.sprite.position[1]);
}

void game_draw() {
    renderer_frame_begin();
    renderer_set_clear_color((vec4){0.11f, 0.1f, 0.15f, 1.0f});

    renderer_batch_begin(&main_batch);
    renderer_batch_submit(&main_batch, player.sprite);
    renderer_batch_end(&main_batch);

    renderer_frame_end();
}

void game_destroy() {
    texture_destroy(player.texture);
    renderer_batch_destroy(&main_batch);
    renderer_destroy();
}
