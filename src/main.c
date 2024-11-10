#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <window/window.h>
#include <graphics/frontend/renderer.h>

#define SPRITE_COUNT 100

void resize_callback(int width, int height) {
    printf("size: %d, %d\n", width, height);
    renderer_set_size(width, height, 400);
}

void key_callback(int key, int action) {
    if (key == 256 && action == 1) {
        window_close();
    }
    printf("key: %d\n", key);
}

void mouse_btn_callback(int btn, int action) {
    printf("mouse button: %d\n", btn);
}

void random_star_color(vec4 color) {
    color[0] = 1.f;
    color[1] = 1.f;
    color[2] = 1.f;
    color[3] = (float) rand() / (float) RAND_MAX;
}

int main() {
    if (!window_init(640, 480, "Game")) {
        printf("failed to init a window");
        return -1;
    }

    window_set_resize_callback(&resize_callback);
    window_set_key_callback(&key_callback);
    window_set_mouse_btn_callback(&mouse_btn_callback);

    sprite particles[SPRITE_COUNT];

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

    sprite quad = {
        .size = {20, 26},
        .color = {1, 1, 1, 1},

        .position = {0, 0},
        .rotation = 0,
        .scale = {1.f, 1.f},

        .origin = {10, 13}
    };

    renderer_init();
    renderer_set_size(680, 480, 400);

    vec4 clear_color = {0.11f, 0.1f, 0.15f, 1.0f};
    renderer_set_clear_color(clear_color);

    batch b = renderer_batch_create();

    while (!window_is_closed()) {
        renderer_frame_begin();

        renderer_batch_begin(&b);

        for (int i = 0; i < SPRITE_COUNT; i++) {
            float k = (float) (i % 10) + 1;
            particles[i].position[0] += 0.01f * sinf(particles[i].position[1] * 0.08f * k);
            particles[i].position[1] += 0.01f * cosf(particles[i].position[0] * 0.08f * k);
            renderer_batch_submit(&b, particles[i]);
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

        renderer_batch_submit(&b, quad);
        renderer_batch_end(&b);

        renderer_frame_end();
        window_poll_events();
    }

    renderer_batch_destroy(&b);

    renderer_destroy();
    window_destroy();

    return 0;
}
