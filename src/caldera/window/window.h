#ifndef WINDOW_H
#define WINDOW_H

#include "caldera/math/types.h"

typedef void (*window_resize_callback)(int width, int height);

typedef void (*window_key_callback)(int key, int action);

typedef void (*window_mouse_btn_callback)(int key, int action);

bool window_init(int width, int height, const char *title);

void window_set_resize_callback(window_resize_callback callback);

void window_set_key_callback(window_key_callback callback);

void window_set_mouse_btn_callback(window_mouse_btn_callback callback);

int window_get_key(int key);

void window_get_cursor_position(vec2 dest);

void window_poll_events();

void window_get_size(int *width, int *height);

bool window_is_closed();

void window_close();

void window_destroy();

// this function should be used only by the renderer
void *window_get_native_window();

#endif //WINDOW_H
