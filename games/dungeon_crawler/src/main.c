#include <stdio.h>
#include "game.h"
#include <caldera/window/window.h>

#include "caldera/window/input.h"
#include "caldera/utils/time.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define RENDER_SIZE 200

void key_callback(int key, int action) {
    if (key == CALDERA_KEY_ESCAPE && action == CALDERA_PRESS) {
        window_close();
    }
}

int main() {
    if (!window_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Demo")) {
        printf("failed to init a window");
        return 1;
    }

    window_set_key_callback(&key_callback);

    game_init();

    double last_frame_time = get_current_time();

    int frame_count = 0;
    float elapsed_time = 0.0f;

    while (!window_is_closed()) {
        // Calculate delta time in seconds
        double current_frame_time = get_current_time();
        float delta_time = current_frame_time - last_frame_time;
        last_frame_time = current_frame_time;

        frame_count++;
        elapsed_time += delta_time;

        if (elapsed_time >= 1.0f) {
            printf("FPS: %d\n", frame_count);
            frame_count = 0;
            elapsed_time = 0.0f;
        }

        game_update(delta_time);
        game_draw();

        window_poll_events();
    }

    game_destroy();
    window_free();

    return 0;
}
