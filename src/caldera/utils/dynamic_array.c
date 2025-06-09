#include "dynamic_array.h"

#include "caldera/utils/panic.h"

void dynamic_array_init(dynamic_array *dynamic_array, const size_t element_size, const size_t capacity) {
    dynamic_array->element_size = element_size;
    dynamic_array->capacity = capacity;
    dynamic_array->array = malloc(element_size * capacity);
    if (dynamic_array->array == NULL) {
        panic("failed to allocate dynamic array");
    }
    dynamic_array->size = 0;
}

void dynamic_array_free(dynamic_array *dynamic_array) {
    free(dynamic_array->array);
    dynamic_array->array = NULL;
    dynamic_array->size = 0;
    dynamic_array->capacity = 0;
}

void *dynamic_array_add(dynamic_array *dynamic_array) {
    if (dynamic_array->size >= dynamic_array->capacity) {
        dynamic_array->capacity *= 2;

        const size_t new_size = dynamic_array->element_size * dynamic_array->capacity;
        void *result = realloc(dynamic_array->array, new_size);
        if (result == NULL) {
            panic("failed to reallocate dynamic array");
        }

        dynamic_array->array = result;
    }

    const size_t index = dynamic_array->size;
    dynamic_array->size++;

    return (char *) dynamic_array->array + index * dynamic_array->element_size;
}

void *dynamic_array_get(const dynamic_array *dynamic_array, const size_t index) {
    if (index >= dynamic_array->size) {
        panic("index out of bounds in dynamic_array_get");
    }
    return (char *) dynamic_array->array + index * dynamic_array->element_size;
}

void dynamic_array_remove_last(dynamic_array *dynamic_array) {
    if (dynamic_array->size > 0) {
        dynamic_array->size--;
    }
}
