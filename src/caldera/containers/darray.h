#ifndef DARRAY_H
#define DARRAY_H

#include "caldera/defines.h"

// note: do not store the returned pointer for later use as it might expire due to reallocations

typedef struct darray {
    u32 element_size;
    u32 capacity;
    void *array;
    u32 size;
} darray;

// initializes the dynamic array
b8 darray_init(darray *darray, u32 element_size, u32 capacity);

// frees the dynamic array
void darray_free(darray *darray);

// creates a new element at the end of the array and returns it
void *darray_add(darray *darray);

// returns the element by its index
void *darray_get(const darray *darray, u32 index);

// returns the last element of the array
void *darray_get_last(const darray *darray);

// removes the last element
void darray_remove_last(darray *darray);

#endif //DARRAY_H
