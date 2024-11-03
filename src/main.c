#include <stdio.h>
#include <window/window.h>
#include <graphics/api/graphics_context.h>
#include <graphics/api/renderer.h>

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
    if (!window_init(640, 480, "Triangle")) {
        printf("failed to init a window");
        return -1;
    }

    window_set_key_callback(&key_callback);
    window_set_mouse_btn_callback(&mouse_btn_callback);

    graphics_context_init("../res/shaders/metal/triangle.metal");

    while (!window_is_closed()) {
        renderer_draw_triangle();
        window_poll_events();
    }

    graphics_context_destroy();
    window_destroy();

    return 0;
}
