#ifndef RENDERER_H
#define RENDERER_H

#include "vertex_buffer.h"

void renderer_init();

void renderer_begin();

void renderer_submit(vertex_buffer vb, uint32_t vertex_count);

void renderer_end();

void renderer_destroy();

#endif //RENDERER_H
