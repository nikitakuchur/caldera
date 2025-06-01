#include "game.h"

#include <caldera/graphics/frontend/sprite.h>

#include <caldera/graphics/frontend/renderer.h>
#include <caldera/math/vec2.h>
#include <caldera/window/window.h>

#include "caldera/window/input.h"

static float render_size = 100;

struct {
    texture texture;
    sprite sprite;
    vec2 velocity;

    float walk_speed;
} player;

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

void game_init() {
    renderer_init();
    update_render_size();

    player.texture = texture_create("../res/textures/character.png");
    sprite_init(&player.sprite, (vec2) {25.f, 25.f}, player.texture);
    player.sprite.texture_rect = (irect) {
        0, 0,
        25, 0,
        25, 25,
        0, 25
    };

    player.walk_speed = 30.f;
    vec2_zero(player.velocity);

    main_batch = renderer_batch_create();
}

void game_update(const float delta_time) {
    sprite *player_sprite = &player.sprite;

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
    vec2_rotate(velocity, player_sprite->rotation);
    vec2_scale(velocity, 1.f, velocity);

    player.velocity[0] = velocity[0] * player.walk_speed;
    player.velocity[1] = velocity[1] * player.walk_speed;

    player_sprite->position[0] += player.velocity[0] * delta_time;
    player_sprite->position[1] += player.velocity[1] * delta_time;
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
