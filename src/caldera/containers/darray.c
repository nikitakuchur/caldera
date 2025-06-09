#include "darray.h"

#include "caldera/utils/panic.h"

void darray_init(darray *darray, const size_t element_size, const size_t capacity) {
    darray->element_size = element_size;
    darray->capacity = capacity;
    darray->array = malloc(element_size * capacity);
    if (darray->array == nullptr) {
        panic("failed to allocate dynamic array");
    }
    darray->size = 0;
}

void darray_free(darray *darray) {
    free(darray->array);
    darray->array = nullptr;
    darray->size = 0;
    darray->capacity = 0;
}

void* darray_add(darray *darray) {
    if (darray->size >= darray->capacity) {
        darray->capacity *= 2;

        const size_t new_size = darray->element_size * darray->capacity;
        void *result = realloc(darray->array, new_size);
        if (result == nullptr) {
            panic("failed to reallocate dynamic array");
        }

        darray->array = result;
    }

    const size_t index = darray->size;
    darray->size++;

    return (char *) darray->array + index * darray->element_size;;
}

void *darray_get(const darray *darray, const size_t index) {
    if (index >= darray->size) {
        panic("index out of bounds in dynamic_array_get");
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
