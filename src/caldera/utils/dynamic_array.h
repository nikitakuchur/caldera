#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdlib.h>

typedef struct dynamic_array {
    size_t element_size;
    size_t capacity;
    void *array;
    size_t size;
} dynamic_array;

// initializes the dynamic array
void dynamic_array_init(dynamic_array *dynamic_array, size_t element_size, size_t capacity);

// creates a new element at the end of the array and returns its address
void* dynamic_array_add(dynamic_array *dynamic_array);

// gets the element by its index
void* dynamic_array_get(const dynamic_array *dynamic_array, size_t index);

// removes the last element
void dynamic_array_remove_last(dynamic_array *dynamic_array);

#endif //DYNAMIC_ARRAY_H
