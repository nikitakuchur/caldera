#ifndef SPARSE_SET_H
#define SPARSE_SET_H

#include "../containers/darray.h"

#define SPARSE_MAX_SIZE 2048

typedef struct sparse_set {
    size_t sparse_array[SPARSE_MAX_SIZE];
    darray dense_array;
    darray data;
} sparse_set;

void sparse_set_init(sparse_set *sparse_set, size_t element_size);

void sparse_set_free(sparse_set *sparse_set);

void* sparse_set_add(sparse_set *sparse_set, size_t id);

void* sparse_set_get(const sparse_set *sparse_set, size_t id);

void sparse_set_remove(sparse_set *sparse_set, size_t id);

#endif //SPARSE_SET_H
