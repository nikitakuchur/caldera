#ifndef DARRAY_H
#define DARRAY_H

#include <stdlib.h>

// note: do not store the returned pointer for later use as it might expire due to reallocations

typedef struct darray {
    size_t element_size;
    size_t capacity;
    void *array;
    size_t size;
} darray;

// initializes the dynamic array
void darray_init(darray *darray, size_t element_size, size_t capacity);

// frees the dynamic array
void darray_free(darray *darray);

// creates a new element at the end of the array and returns it
void* darray_add(darray *darray);

// returns the element by its index
void* darray_get(const darray *darray, size_t index);

// returns the last element of the array
void *darray_get_last(const darray *darray);

// removes the last element
void darray_remove_last(darray *darray);

#endif //DARRAY_H
