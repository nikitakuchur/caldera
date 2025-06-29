#ifndef WINDOW_H
#define WINDOW_H

#include "caldera/defines.h"
#include "caldera/math/types.h"

typedef void (*window_resize_callback)(u32 width, u32 height);

typedef void (*window_key_callback)(i32 key, i32 action);

typedef void (*window_mouse_btn_callback)(i32 key, i32 action);

b8 window_init(u32 width, u32 height, const char *title);

void window_free();

void window_set_resize_callback(window_resize_callback callback);

void window_set_key_callback(window_key_callback callback);

void window_set_mouse_btn_callback(window_mouse_btn_callback callback);

i32 window_get_key(i32 key);

vec2 window_get_cursor_position();

void window_poll_events();

ivec2 window_get_size();

b8 window_should_close();

void window_close();

// this function should be used only by the renderer
void *window_get_native_window();

#endif //WINDOW_H
