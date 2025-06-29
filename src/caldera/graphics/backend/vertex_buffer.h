#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include "caldera/defines.h"

typedef struct vertex_buffer {
    void *platform_buffer;
} vertex_buffer;

void vertex_buffer_init(vertex_buffer *buffer, u32 size);

void vertex_buffer_free(vertex_buffer *buffer);

void vertex_buffer_set(const vertex_buffer *buffer, const void *data, u32 size);

#endif //VERTEX_BUFFER_H
