#ifndef VERTEX_BUFFER_H
#define VERTEX_BUFFER_H

#include <stdint.h>

typedef struct vertex_buffer {
    void *platform_buffer;
} vertex_buffer;

vertex_buffer vertex_buffer_create(uint32_t size);

void vertex_buffer_set(vertex_buffer buffer, const void *data, uint32_t size);

void vertex_buffer_destroy(vertex_buffer buffer);

#endif //VERTEX_BUFFER_H
