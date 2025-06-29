#ifndef RENDERER_BACKEND_H
#define RENDERER_BACKEND_H

#include "index_buffer.h"
#include "vertex_buffer.h"
#include "texture.h"

#include <caldera/math/types.h>

void renderer_backend_init();

void renderer_backend_free();

void renderer_backend_begin();

void renderer_backend_end();

void renderer_backend_set_model_mat(const mat4 *model_mat);

void renderer_backend_set_view_mat(const mat4 *view_mat);

void renderer_backend_set_proj_mat(const mat4 *proj_mat);

void renderer_backend_set_screen_size(u32 width, u32 height);

void renderer_backend_set_pixel_size(u32 width, u32 height);

void renderer_backend_set_clear_color(vec4 clear_color);

void renderer_backend_submit(vertex_buffer vb, index_buffer ib, u32 index_count, texture textures[], u32 texture_count);

#endif //RENDERER_BACKEND_H
