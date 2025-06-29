#include "window.h"

#include <GLFW/glfw3.h>

#include "caldera/math/ivec2.h"
#include "caldera/math/vec2.h"

static struct {
    GLFWwindow *window;

    window_resize_callback resize_callback_func;
    window_key_callback key_callback_func;
    window_mouse_btn_callback mouse_btn_callback_func;
} context;

static void size_callback(GLFWwindow *window, i32 width, i32 height) {
    if (context.resize_callback_func) {
        context.resize_callback_func(width, height);
    }
}

static void key_callback(GLFWwindow *window, i32 key, i32 scancode, i32 action, i32 mods) {
    if (context.key_callback_func) {
        context.key_callback_func(key, action);
    }
}

static void mouse_btn_callback(GLFWwindow *window, i32 button, i32 action, i32 mods) {
    if (context.mouse_btn_callback_func) {
        context.mouse_btn_callback_func(button, action);
    }
}

b8 window_init(u32 width, u32 height, const char *title) {
    // don't create a new window again
    if (context.window) {
        return true;
    }

    if (!glfwInit()) {
        return false;
    }

    glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
    context.window = glfwCreateWindow((i32) width, (i32) height, title, nullptr, nullptr);

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

i32 window_get_key(i32 key) {
    return glfwGetKey(context.window, key);
}

vec2 window_get_cursor_position() {
    f64 x, y;
    glfwGetCursorPos(context.window, &x, &y);
    return vec2_new((f32) x, (f32) y);
}

void window_poll_events() {
    glfwPollEvents();
}

ivec2 window_get_size() {
    i32 width, height;
    glfwGetWindowSize(context.window, &width, &height);
    return ivec2_new(width, height);
}

b8 window_should_close() {
    return glfwWindowShouldClose(context.window);
}

void window_close() {
    glfwSetWindowShouldClose(context.window, GLFW_TRUE);
}

void *window_get_native_window() {
    return context.window;
}
