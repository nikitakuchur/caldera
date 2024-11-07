#include <stdio.h>
#include <window/window.h>
#include <graphics/frontend/renderer.h>

void resize_callback(int width, int height) {
    printf("size: %d, %d\n", width, height);
    //renderer_set_viewport(width, height);
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
    if (!window_init(480, 480, "Game")) {
        printf("failed to init a window");
        return -1;
    }

    window_set_resize_callback(&resize_callback);
    window_set_key_callback(&key_callback);
    window_set_mouse_btn_callback(&mouse_btn_callback);

    sprite s1 = {{0.0f, 0.0f}, {0, 0}, {0.5f, 0.5f}, {0.8f, 0.3f, 0.0f, 1.0f}};
    sprite s2 = {{-0.4f, 0.1f}, {0, 0}, {0.2f, 0.3f}, {0.3f, 0.3f, 0.6f, 1.0f}};
    renderer_init();
    renderer_set_viewport(480, 480);

    while (!window_is_closed()) {
        renderer_begin();
        renderer_draw_sprite(s1);
        renderer_draw_sprite(s2);
        renderer_end();

        window_poll_events();
    }

    renderer_destroy();
    window_destroy();

    return 0;
}
