#include <stdio.h>
#include <caldera/graphics/backend/vertex_buffer.h>

vertex_buffer vertex_buffer_create(uint32_t size) {
    printf("vertex_buffer_create not supported");
    vertex_buffer vb = {};
    return vb;
}

void vertex_buffer_set(vertex_buffer vb, const void *data, uint32_t size) {
    printf("vertex_buffer_set not supported");
}

void vertex_buffer_destroy(vertex_buffer vb) {
    printf("vertex_buffer_destroy not supported");
}
