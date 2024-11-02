#ifndef WINDOW_H
#define WINDOW_H

#include <GLFW/glfw3.h>

typedef void (*window_key_callback)(int key, int action);

typedef void (*window_mouse_btn_callback)(int key, int action);

bool window_init(int width, int height, const char *title);

void window_set_key_callback(window_key_callback callback);

void window_set_mouse_btn_callback(window_mouse_btn_callback callback);

void window_poll_events();

bool window_is_closed();

void window_close();

void window_destroy();

// this function should be used only by the renderer
GLFWwindow *window_get_glfw_window();

#endif //WINDOW_H
