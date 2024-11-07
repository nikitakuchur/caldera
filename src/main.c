#include <stdio.h>
#include <window/window.h>
#include <graphics/frontend/renderer.h>

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

int main() {
    if (!window_init(680, 480, "Game")) {
        printf("failed to init a window");
        return -1;
    }

    window_set_resize_callback(&resize_callback);
    window_set_key_callback(&key_callback);
    window_set_mouse_btn_callback(&mouse_btn_callback);

    sprite s1 = {{0.0f, 0.0f}, {0, 0}, {300.f, 200.f}, {0.8f, 0.3f, 0.0f, 1.0f}};
    sprite s2 = {{-250.f, -100.f}, {0, 0}, {200.f, 150.f}, {0.3f, 0.3f, 0.6f, 1.0f}};

    sprite s3 = {{0.0f, -100.0f}, {0, 0}, {30.f, 40.f}, {0.9f, 0.1f, 0.2f, 1.0f}};
    sprite s4 = {{-30.f, -100.f}, {0, 0}, {20.f, 20.f}, {0.9f, 0.1f, 0.2f, 1.0f}};

    renderer_init();
    renderer_set_size(680, 480);

    batch b1 = renderer_batch_create();
    batch b2 = renderer_batch_create();

    while (!window_is_closed()) {
        renderer_frame_begin();

        renderer_batch_begin(&b1);
        renderer_batch_submit(&b1, s1);
        renderer_batch_submit(&b1, s2);
        renderer_batch_end(&b1);

        renderer_batch_begin(&b2);
        renderer_batch_submit(&b2, s3);
        renderer_batch_submit(&b2, s4);
        renderer_batch_end(&b2);

        renderer_frame_end();

        window_poll_events();
    }

    renderer_destroy();
    window_destroy();

    return 0;
}
