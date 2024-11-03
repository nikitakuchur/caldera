#include <stdio.h>
#include <window/window.h>
#include <graphics/api/graphics_context.h>
#include <graphics/api/renderer.h>
#include <graphics/api/vertex_buffer.h>
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

    vertex triangle[3] = {
        {{-0.75f, -0.75f}, {1.0f, 0.0f, 0.0f}},
        {{0.75f, -0.75f}, {0.0f, 1.0f, 0.0f}},
        {{0.0f, 0.75f}, {0.0f, 0.0f, 1.0f}}
    };

    vertex_buffer vb = vertex_buffer_create(3 * sizeof(vertex));
    vertex_buffer_set(vb, triangle, 3 * sizeof(vertex));

    while (!window_is_closed()) {
        renderer_begin();

        if (window_get_key(GLFW_KEY_W) == GLFW_PRESS) {
            triangle[0].pos[1] += 0.01f;
            triangle[1].pos[1] += 0.01f;
            triangle[2].pos[1] += 0.01f;
        }
        if (window_get_key(GLFW_KEY_D) == GLFW_PRESS) {
            triangle[0].pos[0] += 0.01f;
            triangle[1].pos[0] += 0.01f;
            triangle[2].pos[0] += 0.01f;
        }
        if (window_get_key(GLFW_KEY_A) == GLFW_PRESS) {
            triangle[0].pos[0] -= 0.01f;
            triangle[1].pos[0] -= 0.01f;
            triangle[2].pos[0] -= 0.01f;
        }
        if (window_get_key(GLFW_KEY_S) == GLFW_PRESS) {
            triangle[0].pos[1] -= 0.01f;
            triangle[1].pos[1] -= 0.01f;
            triangle[2].pos[1] -= 0.01f;
        }

        vertex_buffer_set(vb, triangle, 3 * sizeof(triangle));
        renderer_submit(vb, 3);

        renderer_end();

        window_poll_events();
    }

    vertex_buffer_destroy(vb);
    renderer_destroy();
    graphics_context_destroy();

    window_destroy();

    return 0;
}
