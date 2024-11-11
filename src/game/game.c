#include "game.h"

#include <math.h>
#include <graphics/frontend/sprite.h>

#include <stdlib.h>
#include <graphics/frontend/renderer.h>
#include <window/window.h>

#define SPRITE_COUNT 100

static float render_size = 200;

static sprite particles[SPRITE_COUNT];
static sprite quad;

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
    renderer_init();
    update_render_size();

    for (int i = 0; i < SPRITE_COUNT; i++) {
        float x = rand() % 640 - 320;
        float y = rand() % 480 - 240;
        particles[i] = (sprite){
            .size = {1.f, 1.f},
            .position = {x, y},
            .rotation = 0,
            .scale = {1.f, 1.f},
            .origin = {0, 0},
        };
        random_star_color(particles[i].color);
    }

    quad = (sprite){
        .size = {20, 26},
        .color = {1, 1, 1, 1},

        .position = {0, 0},
        .rotation = 0,
        .scale = {1.f, 1.f},

        .origin = {10, 13}
    };

    main_batch = renderer_batch_create();
}

void game_update() {
    for (int i = 0; i < SPRITE_COUNT; i++) {
        float k = (float) (i % 10) + 1;
        particles[i].position[0] += 0.01f * sinf(particles[i].position[1] * 0.08f * k);
        particles[i].position[1] += 0.01f * cosf(particles[i].position[0] * 0.08f * k);
    }

    if (window_get_key(GLFW_KEY_Q) == GLFW_PRESS) {
        quad.rotation += 0.05f;
    }
    if (window_get_key(GLFW_KEY_E) == GLFW_PRESS) {
        quad.rotation -= 0.05f;
    }

    if (window_get_key(GLFW_KEY_A) == GLFW_PRESS) {
        quad.position[0] -= 0.8f;
    }
    if (window_get_key(GLFW_KEY_D) == GLFW_PRESS) {
        quad.position[0] += 0.8f;
    }
    if (window_get_key(GLFW_KEY_W) == GLFW_PRESS) {
        quad.position[1] += 0.8f;
    }
    if (window_get_key(GLFW_KEY_S) == GLFW_PRESS) {
        quad.position[1] -= 0.8f;
    }

    if (window_get_key(GLFW_KEY_EQUAL) == GLFW_PRESS && render_size > 5) {
        render_size -= 5;
    }
    if (window_get_key(GLFW_KEY_MINUS) == GLFW_PRESS) {
        render_size += 5;
    }

    update_render_size();
}

void game_draw() {
    renderer_frame_begin();
    renderer_set_clear_color((vec4){0.11f, 0.1f, 0.15f, 1.0f});

    renderer_batch_begin(&main_batch);

    for (int i = 0; i < SPRITE_COUNT; i++) {
        renderer_batch_submit(&main_batch, particles[i]);
    }

    renderer_batch_submit(&main_batch, quad);

    renderer_batch_end(&main_batch);

    renderer_frame_end();
}

void game_destroy() {
    renderer_batch_destroy(&main_batch);
    renderer_destroy();
}
