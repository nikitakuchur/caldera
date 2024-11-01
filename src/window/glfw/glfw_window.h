#ifndef GLFW_WINDOW_H
#define GLFW_WINDOW_H

#include "window/window.h"

bool glfw_window_create(int width, int height, const char *title);

void glfw_window_set_key_callback(window_key_callback callback);

void glfw_window_set_mouse_btn_callback(window_mouse_btn_callback callback);

void glfw_window_swap_buffers();

void glfw_window_poll_events();

bool glfw_window_is_closed();

void glfw_window_close();

void glfw_window_destroy();

#endif //GLFW_WINDOW_H
