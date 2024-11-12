#ifndef RENDERER_BACKEND_H
#define RENDERER_BACKEND_H

#include "index_buffer.h"
#include "vertex_buffer.h"

#include <math/types.h>

void renderer_backend_init();

void renderer_backend_begin();

void renderer_backend_set_model_mat(mat4 model_mat);

void renderer_backend_set_view_mat(mat4 view_mat);

void renderer_backend_set_proj_mat(mat4 proj_mat);

void renderer_backend_set_screen_size(int width, int height);

void renderer_backend_set_pixel_size(int width, int height);

void renderer_backend_set_clear_color(vec4 clear_color);

void renderer_backend_submit(vertex_buffer vb, index_buffer ib, uint32_t index_count, texture textures[], uint32_t texture_count);

void renderer_backend_end();

void renderer_backend_destroy();

#endif //RENDERER_BACKEND_H
