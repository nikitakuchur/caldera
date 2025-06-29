#ifndef INDEX_BUFFER_H
#define INDEX_BUFFER_H

#include "caldera/defines.h"

typedef struct index_buffer {
    void *platform_buffer;
    u32 count;
} index_buffer;

void index_buffer_init(index_buffer *buffer, u32 count);

void index_buffer_free(index_buffer *buffer);

void index_buffer_set(index_buffer *buffer, const u32 *indices, u32 count);

#endif //INDEX_BUFFER_H
