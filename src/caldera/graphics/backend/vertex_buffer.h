#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <stdint.h>

typedef struct vertex_buffer {
    void *platform_buffer;
} vertex_buffer;

void vertex_buffer_init(vertex_buffer *buffer, uint32_t size);

void vertex_buffer_free(vertex_buffer *buffer);

void vertex_buffer_set(vertex_buffer *buffer, const void *data, uint32_t size);

#endif //VERTEX_BUFFER_H
