#include <stdio.h>
#include <window/window.h>
#include <graphics/api/graphics_context.h>
#include <graphics/api/renderer.h>
#include <graphics/api/index_buffer.h>
#include <math/types.h>

typedef struct {
    vec2 pos;
    vec3 color;
} vertex;

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

    graphics_context_init();
    renderer_init();

    vertex quad[4] = {
        {{-0.75f, -0.75f}, {1.0f, 0.0f, 0.0f}},
        {{ 0.75f, -0.75f}, {0.0f, 1.0f, 0.0f}},
        {{ 0.75f, 0.75f}, {0.0f, 0.0f, 1.0f}},
        {{-0.75f, 0.75f}, {1.0f, 1.0f, 1.0f}}
    };
    vertex_buffer vb = vertex_buffer_create(4 * sizeof(vertex));
    vertex_buffer_set(vb, quad, 4 * sizeof(vertex));

    u_int32_t indices[6] = {0, 1, 2, 2, 3, 0};
    index_buffer ib = index_buffer_create(6);
    index_buffer_set(ib, indices);

    while (!window_is_closed()) {
        renderer_begin();
        renderer_submit(vb, 4, ib);
        renderer_end();

        window_poll_events();
    }

    vertex_buffer_destroy(vb);
    index_buffer_destroy(ib);

    renderer_destroy();
    graphics_context_destroy();

    window_destroy();

    return 0;
}
