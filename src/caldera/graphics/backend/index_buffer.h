#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include <stdint.h>

typedef struct index_buffer {
    void *platform_buffer;
    uint32_t count;
} index_buffer;

void index_buffer_init(index_buffer *buffer, uint32_t count);

void index_buffer_free(index_buffer *buffer);

void index_buffer_set(index_buffer *buffer, const uint32_t *indices, uint32_t count);

#endif //INDEX_BUFFER_H
