#include "game.h"
#include <caldera/window/window.h>

#include "caldera/utils/log.h"
#include "caldera/window/input.h"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 720
#define RENDER_SIZE 200

void key_callback(i32 key, i32 action) {
    if (key == CALDERA_KEY_ESCAPE && action == CALDERA_PRESS) {
        window_close();
    }
}

i32 main() {
    if (!window_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Demo")) {
        fatalf("failed to init a window");
        return 1;
    }

    window_set_key_callback(&key_callback);

    game_init();

    while (!window_should_close()) {
        game_draw();
    }

    game_free();
    window_free();

    return 0;
}
