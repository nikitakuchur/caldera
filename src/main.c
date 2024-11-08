#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <window/window.h>
#include <graphics/frontend/renderer.h>

#define SPRITE_COUNT 500

void resize_callback(int width, int height) {
    printf("size: %d, %d\n", width, height);
    renderer_set_size(width, height);
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

void random_color(vec4 color) {
    color[0] = 1.0f;
    color[1] = fmin(0.7f * (float) rand() / (float) RAND_MAX, 1.f);
    color[2] = 0.3f;
    color[3] = 1.f;
}

int main() {
    if (!window_init(640, 480, "Game")) {
        printf("failed to init a window");
        return -1;
    }

    window_set_resize_callback(&resize_callback);
    window_set_key_callback(&key_callback);
    window_set_mouse_btn_callback(&mouse_btn_callback);

    sprite sprites[SPRITE_COUNT];

    for (int i = 0; i < SPRITE_COUNT; i++) {
        float x = rand() % 640 - 320;
        float y = rand() % 480 - 240;
        sprites[i] = (sprite){
            {x, y},
            {0, 0},
            {1.f, 1.f}
        };
        random_color(sprites[i].color);
    }

    renderer_init();
    renderer_set_size(680, 480);

    batch b = renderer_batch_create();

    while (!window_is_closed()) {
        renderer_frame_begin();

        renderer_batch_begin(&b);
        for (int i = 0; i < SPRITE_COUNT; i++) {
            float k = (float) (i % 10) + 1;
            sprites[i].position[0] += 0.5f * sinf(sprites[i].position[1] * 0.08f * k);
            sprites[i].position[1] += 0.5f * cosf(sprites[i].position[0] * 0.08f * k);
            renderer_batch_submit(&b, sprites[i]);
        }
        renderer_batch_end(&b);

        renderer_frame_end();
        window_poll_events();
    }

    renderer_batch_destroy(&b);

    renderer_destroy();
    window_destroy();

    return 0;
}
