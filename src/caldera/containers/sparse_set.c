#include "sparse_set.h"

#include <string.h>

#define NULL_INDEX (-1)

void sparse_set_init(sparse_set *sparse_set, size_t element_size) {
    for (size_t i = 0; i < SPARSE_MAX_SIZE; i++) {
        sparse_set->sparse_array[i] = NULL_INDEX;
    }
    darray_init(&sparse_set->dense_array, sizeof(size_t), 8);
    darray_init(&sparse_set->data, element_size, 8);
}

void sparse_set_free(sparse_set *sparse_set) {
    for (size_t i = 0; i < SPARSE_MAX_SIZE; i++) {
        sparse_set->sparse_array[i] = NULL_INDEX;
    }
    darray_free(&sparse_set->dense_array);
    darray_free(&sparse_set->data);
}

void *sparse_set_add(sparse_set *sparse_set, size_t id) {
    sparse_set->sparse_array[id] = sparse_set->dense_array.size;

    size_t *p = darray_add(&sparse_set->dense_array);
    *p = id;

    return darray_add(&sparse_set->data);
}

void *sparse_set_get(const sparse_set *sparse_set, size_t id) {
    size_t index = sparse_set->sparse_array[id];
    if (index != NULL_INDEX) {
        return darray_get(&sparse_set->data, index);
    }
    return nullptr;
}

void sparse_set_remove(sparse_set *sparse_set, size_t id) {
    size_t dense_index = sparse_set->sparse_array[id];
    if (dense_index == NULL_INDEX) {
        return;
    }

    sparse_set->sparse_array[id] = NULL_INDEX;

    // swap the elements of the data array
    void *element_to_delete = darray_get(&sparse_set->data, dense_index);
    const void *last_element = darray_get_last(&sparse_set->data);
    // copy the value of 'last_element' into 'element_to_delete'
    memcpy(element_to_delete, last_element, sparse_set->data.element_size);
    darray_remove_last(&sparse_set->data);

    // update the swaped element's index
    const size_t *id_to_update = darray_get_last(&sparse_set->dense_array);
    sparse_set->sparse_array[*id_to_update] = dense_index;
    darray_remove_last(&sparse_set->dense_array);
}
