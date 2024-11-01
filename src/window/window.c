#include "window.h"

#include "glfw/glfw_window.h"

bool window_create(int width, int height, const char *title) {
    return glfw_window_create(width, height, title);
}

void window_set_key_callback(window_key_callback callback) {
    glfw_window_set_key_callback(callback);
}

void window_set_mouse_btn_callback(window_mouse_btn_callback callback) {
    glfw_window_set_mouse_btn_callback(callback);
}

void window_swap_buffers() {
    glfw_window_swap_buffers();
}

void window_poll_events() {
    glfw_window_poll_events();
}

bool window_is_closed() {
    return glfw_window_is_closed();
}

void window_close() {
    glfw_window_close();
}

void window_destroy() {
    glfw_window_destroy();
}
