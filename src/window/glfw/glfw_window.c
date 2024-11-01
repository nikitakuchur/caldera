#include "glfw_window.h"

#include <GLFW/glfw3.h>

static GLFWwindow *window = nullptr;

// callback functions
static window_key_callback key_callback_func = nullptr;
static window_mouse_btn_callback mouse_btn_callback_func = nullptr;

static void glfw_key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    key_callback_func(key, action);
}

static void glfw_mouse_btn_callback(GLFWwindow *window, int button, int action, int mods) {
    mouse_btn_callback_func(button, action);
}

bool glfw_window_create(int width, int height, const char *title) {
    // don't create a new window again
    if (window != nullptr) {
        return true;
    }

    if (!glfwInit()) {
        return false;
    }

    window = glfwCreateWindow(width, height, title, nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return false;
    }

    glfwSetKeyCallback(window, &glfw_key_callback);
    glfwSetMouseButtonCallback(window, &glfw_mouse_btn_callback);
    glfwMakeContextCurrent(window);

    return true;
}

void glfw_window_set_key_callback(window_key_callback callback) {
    key_callback_func = callback;
}

void glfw_window_set_mouse_btn_callback(window_mouse_btn_callback callback) {
    mouse_btn_callback_func = callback;
}

void glfw_window_swap_buffers() {
    glfwSwapBuffers(window);
}

void glfw_window_poll_events() {
    glfwPollEvents();
}

bool glfw_window_is_closed() {
    return glfwWindowShouldClose(window);
}

void glfw_window_close() {
    glfwSetWindowShouldClose(window, GLFW_TRUE);
}

void glfw_window_destroy() {
    if (window != nullptr) {
        glfwTerminate();
    }
}
