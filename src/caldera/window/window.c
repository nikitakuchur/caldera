#include "window.h"

#include <GLFW/glfw3.h>

static struct {
    GLFWwindow *window;

    window_resize_callback resize_callback_func;
    window_key_callback key_callback_func;
    window_mouse_btn_callback mouse_btn_callback_func;
} context;

static void size_callback(GLFWwindow *window, int width, int height) {
    if (context.resize_callback_func) {
        context.resize_callback_func(width, height);
    }
}

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (context.key_callback_func) {
        context.key_callback_func(key, action);
    }
}

static void mouse_btn_callback(GLFWwindow *window, int button, int action, int mods) {
    if (context.mouse_btn_callback_func) {
        context.mouse_btn_callback_func(button, action);
    }
}

bool window_init(int width, int height, const char *title) {
    // don't create a new window again
    if (context.window) {
        return true;
    }

    if (!glfwInit()) {
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    context.window = glfwCreateWindow(width, height, title, nullptr, nullptr);

    if (!context.window) {
        glfwTerminate();
        return false;
    }

    glfwSetWindowSizeCallback(context.window, &size_callback);
    glfwSetKeyCallback(context.window, &key_callback);
    glfwSetMouseButtonCallback(context.window, &mouse_btn_callback);

    return true;
}

void window_free() {
    if (!context.window) {
        glfwTerminate();

        context.window = nullptr;

        context.resize_callback_func = nullptr;
        context.key_callback_func = nullptr;
        context.mouse_btn_callback_func = nullptr;
    }
}

void window_set_resize_callback(window_resize_callback callback) {
    context.resize_callback_func = callback;
}

void window_set_key_callback(window_key_callback callback) {
    context.key_callback_func = callback;
}

void window_set_mouse_btn_callback(window_mouse_btn_callback callback) {
    context.mouse_btn_callback_func = callback;
}

int window_get_key(int key) {
    return glfwGetKey(context.window, key);
}

void window_get_cursor_position(vec2 dest) {
    double x, y;
    glfwGetCursorPos(context.window, &x, &y);
    dest[0] = (float) x;
    dest[1] = (float) y;
}

void window_poll_events() {
    glfwPollEvents();
}

void window_get_size(int *width, int *height) {
    glfwGetWindowSize(context.window, width, height);
}

bool window_is_closed() {
    return glfwWindowShouldClose(context.window);
}

void window_close() {
    glfwSetWindowShouldClose(context.window, GLFW_TRUE);
}

void* window_get_native_window() {
    return context.window;
}
