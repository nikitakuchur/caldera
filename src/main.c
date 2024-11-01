#include <stdio.h>
#include <window/window.h>
#include <window/macos/macos_window.hpp>

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
    // bool created = window_create(640, 480, "Game");
    // if (!created) {
    //     printf("failed to create a window");
    //     return -1;
    // }
    //
    // window_set_key_callback(&key_callback);
    // window_set_mouse_btn_callback(&mouse_btn_callback);
    //
    // while (!window_is_closed()) {
    //
    //     // Render here
    //
    //     window_swap_buffers();
    //     window_poll_events();
    // }
    //
    // window_destroy();
    macos_window_create(640, 480, "Game");

    return 0;
}
