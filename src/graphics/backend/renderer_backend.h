#ifndef RENDERER_BACKEND_H
#define RENDERER_BACKEND_H

#include "index_buffer.h"
#include "vertex_buffer.h"

void renderer_backend_init();

void renderer_backend_begin();

void renderer_backend_set_viewport(int width, int height);

void renderer_backend_submit(vertex_buffer vb, index_buffer io, uint32_t index_count);

void renderer_backend_end();

void renderer_backend_destroy();

#endif //RENDERER_BACKEND_H
