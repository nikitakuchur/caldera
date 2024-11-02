#include <stdio.h>
#include <window/window.h>
#include <graphics/metal/mtl_context.hpp>
#include <graphics/metal/mtl_renderer.hpp>

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
    if (!window_init(640, 480, "Metal Test")) {
        printf("failed to init a window");
        return -1;
    }

    window_set_key_callback(&key_callback);
    window_set_mouse_btn_callback(&mouse_btn_callback);

    mtl_context_init();

    while (!window_is_closed()) {

        // render here
        mtl_renderer_draw();

        window_swap_buffers();
        window_poll_events();
    }

    mtl_context_destroy();
    window_destroy();

    return 0;
}
