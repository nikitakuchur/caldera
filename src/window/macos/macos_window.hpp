#ifndef MACOS_WINDOW_H
#define MACOS_WINDOW_H

#include "window/window.h"

#ifdef __cplusplus
extern "C" {
#endif

bool macos_window_create(int width, int height, const char *title);

void macos_window_set_key_callback(window_key_callback callback);

void macos_window_set_mouse_btn_callback(window_mouse_btn_callback callback);

void macos_window_swap_buffers();

void macos_window_poll_events();

bool macos_window_is_closed();

void macos_window_close();

void macos_window_destroy();

#ifdef __cplusplus
}
#endif

#endif //MACOS_WINDOW_H
