#include "darray.h"

bool darray_init(darray *darray, size_t element_size, size_t capacity) {
    darray->element_size = element_size;
    darray->capacity = capacity;
    darray->array = malloc(element_size * capacity);
    if (darray->array == nullptr) {
        // failed to allocate dynamic array
        return false;
    }
    darray->size = 0;
    return true;
}

void darray_free(darray *darray) {
    free(darray->array);
    darray->array = nullptr;
    darray->element_size = 0;
    darray->size = 0;
    darray->capacity = 0;
}

void *darray_add(darray *darray) {
    if (darray->size >= darray->capacity) {
        darray->capacity *= 2;

        size_t new_size = darray->element_size * darray->capacity;
        void *result = realloc(darray->array, new_size);
        if (result == nullptr) {
            // failed to reallocate dynamic array
            return nullptr;
        }

        darray->array = result;
    }

    size_t index = darray->size;
    darray->size++;

    return (char *) darray->array + index * darray->element_size;
}

void *darray_get(const darray *darray, size_t index) {
    if (index >= darray->size) {
        // index out of bounds
        return nullptr;
    }
    return (char *) darray->array + index * darray->element_size;
}

void *darray_get_last(const darray *darray) {
    if (darray->size == 0) {
        return nullptr;
    }
    return darray_get(darray, darray->size - 1);
}

void darray_remove_last(darray *darray) {
    if (darray->size > 0) {
        darray->size--;
    }
}
