#include "game.h"

#include <math.h>
#include <graphics/frontend/sprite.h>

#include <stdlib.h>
#include <graphics/frontend/renderer.h>
#include <math/vec2.h>
#include <window/window.h>

#define STARS_COUNT 100

static float render_size = 400;

static sprite stars[STARS_COUNT];

static texture planet_texture;
static sprite planet;

struct {
    texture texture;
    sprite sprite;
    vec2 velocity;
} player;

static batch main_batch;

static void random_star_color(vec4 color) {
    color[0] = 1.f;
    color[1] = 1.f;
    color[2] = 1.f;
    color[3] = (float) rand() / (float) RAND_MAX;
}

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
    update_render_size();
    renderer_init();

    for (int i = 0; i < STARS_COUNT; i++) {
        float x = rand() % 640 - 320;
        float y = rand() % 480 - 240;
        stars[i] = (sprite){
            .size = {1.f, 1.f},
            .position = {x, y},
            .rotation = 0,
            .scale = {1.f, 1.f},
            .origin = {0, 0},
            .texture = texture_create_empty()
        };
        random_star_color(stars[i].color);
    }

    planet_texture = texture_create("../res/textures/green-planet.png");
    planet = (sprite){
        .size = {256, 256},
        .color = {1, 1, 1, 1},

        .position = {100, 50},
        .rotation = 0,
        .scale = {1.0f, 1.0f},

        .origin = {128, 128},
        .texture = planet_texture
    };

    player.texture = texture_create("../res/textures/ship.png");
    player.sprite = (sprite){
        .size = {64, 64},
        .color = {1, 1, 1, 1},

        .position = {0, 0},
        .rotation = 0,
        .scale = {1.0f, 1.0f},

        .origin = {32, 28},
        .texture = player.texture
    };
    vec2_zero(player.velocity);

    main_batch = renderer_batch_create();
}

void game_update(float delta_time) {
    for (int i = 0; i < STARS_COUNT; i++) {
        float k = (float) (i % 10) + 1;
        stars[i].position[0] += 0.1f * sinf(stars[i].position[1] * 0.08f * k) * delta_time;
        stars[i].position[1] += 0.1f * cosf(stars[i].position[0] * 0.08f * k) * delta_time;
    }

    sprite *ship = &player.sprite;

    vec2 velocity;
    vec2_zero(velocity);

    if (window_get_key(GLFW_KEY_Q) == GLFW_PRESS) {
        ship->rotation += 5.f * delta_time;
    }
    if (window_get_key(GLFW_KEY_E) == GLFW_PRESS) {
        ship->rotation -= 5.f * delta_time;
    }

    // if (window_get_key(GLFW_KEY_A) == GLFW_PRESS) {
    //     velocity[0] -= 0.1f;
    // }
    // if (window_get_key(GLFW_KEY_D) == GLFW_PRESS) {
    //     velocity[0] += 0.1f;
    // }
    if (window_get_key(GLFW_KEY_W) == GLFW_PRESS) {
        velocity[1] += 1.0f;
    }
    // if (window_get_key(GLFW_KEY_S) == GLFW_PRESS) {
    //     velocity[1] -= 0.1f;
    // }

    vec2_normalize(velocity);
    vec2_rotate(velocity, ship->rotation);
    vec2_scale(velocity, 1.f, velocity);

    player.velocity[0] += velocity[0];
    player.velocity[1] += velocity[1];

    float speed_limit = 180.f;
    if (vec2_len(player.velocity) > speed_limit) {
        vec2_normalize(player.velocity);
        vec2_scale(player.velocity, speed_limit, player.velocity);
    }

    ship->position[0] += player.velocity[0] * delta_time;
    ship->position[1] += player.velocity[1] * delta_time;

    if (vec2_len(velocity) == 0 && vec2_len(player.velocity) > 0) {
        float friction = 2.f;
        vec2 negative_velocity;
        vec2_scale(player.velocity, -1 * friction * delta_time, negative_velocity);
        vec2_add(player.velocity, negative_velocity, player.velocity);
    }


    float new_render_size = render_size;
    if (window_get_key(GLFW_KEY_EQUAL) == GLFW_PRESS) {
        new_render_size -= 100.f * delta_time;
    }
    if (window_get_key(GLFW_KEY_MINUS) == GLFW_PRESS) {
        new_render_size += 100.f * delta_time;
    }

    if (new_render_size > 1) {
        render_size = new_render_size;
    }

    update_render_size();
}

void game_draw() {
    renderer_frame_begin();
    renderer_set_clear_color((vec4){0.11f, 0.1f, 0.15f, 1.0f});

    renderer_batch_begin(&main_batch);

    for (int i = 0; i < STARS_COUNT; i++) {
        renderer_batch_submit(&main_batch, stars[i]);
    }

    renderer_batch_submit(&main_batch, planet);
    renderer_batch_submit(&main_batch, player.sprite);

    renderer_batch_end(&main_batch);

    renderer_frame_end();
}

void game_destroy() {
    texture_destroy(player.texture);
    texture_destroy(planet_texture);
    renderer_batch_destroy(&main_batch);
    renderer_destroy();
}
