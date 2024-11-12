#include "game.h"

#include <math.h>
#include <graphics/frontend/sprite.h>

#include <stdlib.h>
#include <graphics/frontend/renderer.h>
#include <window/window.h>

#define STARS_COUNT 100

static float render_size = 400;

static sprite stars[STARS_COUNT];

static texture planet_texture;
static sprite planet;

static texture ship_texture;
static sprite ship;

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

    ship_texture = texture_create("../res/textures/ship.png");
    ship = (sprite){
        .size = {64, 64},
        .color = {1, 1, 1, 1},

        .position = {0, 0},
        .rotation = 0,
        .scale = {1.0f, 1.0f},

        .origin = {32, 24},
        .texture = ship_texture
    };

    main_batch = renderer_batch_create();
}

void game_update(float delta_time) {
    for (int i = 0; i < STARS_COUNT; i++) {
        float k = (float) (i % 10) + 1;
        stars[i].position[0] += 0.1f * sinf(stars[i].position[1] * 0.08f * k) * delta_time;
        stars[i].position[1] += 0.1f * cosf(stars[i].position[0] * 0.08f * k) * delta_time;
    }

    if (window_get_key(GLFW_KEY_Q) == GLFW_PRESS) {
        ship.rotation += 5.f * delta_time;
    }
    if (window_get_key(GLFW_KEY_E) == GLFW_PRESS) {
        ship.rotation -= 5.f * delta_time;
    }

    if (window_get_key(GLFW_KEY_A) == GLFW_PRESS) {
        ship.position[0] -= 50.f * delta_time;
    }
    if (window_get_key(GLFW_KEY_D) == GLFW_PRESS) {
        ship.position[0] += 50.f * delta_time;
    }
    if (window_get_key(GLFW_KEY_W) == GLFW_PRESS) {
        ship.position[1] += 50.f * delta_time;
    }
    if (window_get_key(GLFW_KEY_S) == GLFW_PRESS) {
        ship.position[1] -= 50.f * delta_time;
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
    renderer_batch_submit(&main_batch, ship);

    renderer_batch_end(&main_batch);

    renderer_frame_end();
}

void game_destroy() {
    texture_destroy(ship_texture);
    texture_destroy(planet_texture);
    renderer_batch_destroy(&main_batch);
    renderer_destroy();
}
