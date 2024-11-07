#include <stdio.h>
#include <graphics/backend/index_buffer.h>

index_buffer index_buffer_create(uint32_t count) {
    printf("index_buffer_create not supported");
    index_buffer vb = {};
    return vb;
}

void index_buffer_set(index_buffer ib, const uint32_t *indices) {
    printf("index_buffer_set not supported");
}

void index_buffer_destroy(index_buffer ib) {
    printf("index_buffer_destroy not supported");
}