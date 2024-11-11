#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <game/game.h>
#include <window/window.h>
#include <graphics/frontend/renderer.h>

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480
#define RENDER_SIZE 200

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
    if (!window_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Game")) {
        printf("failed to init a window");
        return -1;
    }

    window_set_key_callback(&key_callback);
    window_set_mouse_btn_callback(&mouse_btn_callback);

    game_init();

    while (!window_is_closed()) {
        game_update();
        game_draw();
        window_poll_events();
    }

    game_destroy();
    window_destroy();

    return 0;
}
