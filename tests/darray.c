#include <caldera/containers/darray.h>
#include <assert.h>
#include <stdio.h>

void print_all(const darray *arr) {
    for (u32 i = 0; i < arr->size; i++) {
        i32 *element = darray_get(arr, i);
        printf("arr[%u]=%d ", i, *element);
    }
}

i32 main() {
    darray arr;
    b8 success = darray_init(&arr, sizeof(i32), 2);
    assert(success);
    assert(arr.array != nullptr);
    assert(arr.size == 0);
    assert(arr.element_size == sizeof(i32));
    assert(arr.capacity == 2);

    assert(darray_get(&arr, 2) == nullptr);
    assert(darray_get_last(&arr) == nullptr);

    // add new elements
    i32 *element = darray_add(&arr);
    assert(element != nullptr);
    *element = 5;

    element = darray_add(&arr);
    assert(element != nullptr);
    *element = 7;

    element = darray_add(&arr);
    assert(element != nullptr);
    *element = 9;

    element = darray_add(&arr);
    assert(element != nullptr);
    *element = 15;

    element = darray_add(&arr);
    assert(element != nullptr);
    *element = 42;

    assert(arr.size == 5);
    assert(arr.capacity == 8);

    print_all(&arr);
    printf("\n");

    // remove last elements
    i32 *last = darray_get_last(&arr);
    assert(*last == 42);

    darray_remove_last(&arr);
    assert(arr.size == 4);

    last = darray_get_last(&arr);
    assert(*last == 15);

    darray_remove_last(&arr);
    assert(arr.size == 3);

    last = darray_get_last(&arr);
    assert(*last == 9);

    element = darray_add(&arr);
    assert(element != nullptr);
    *element = 89;

    element = darray_add(&arr);
    assert(element != nullptr);
    *element = 130;

    element = darray_add(&arr);
    assert(element != nullptr);
    *element = 166;

    assert(arr.size == 6);
    assert(arr.capacity == 8);

    print_all(&arr);

    // remove the rest
    darray_remove_last(&arr); // 5
    darray_remove_last(&arr); // 4
    darray_remove_last(&arr); // 3
    darray_remove_last(&arr); // 2
    darray_remove_last(&arr); // 1
    darray_remove_last(&arr); // 0
    assert(arr.size == 0);

    darray_remove_last(&arr);
    assert(arr.size == 0);

    darray_free(&arr);
    assert(arr.array == nullptr);
    assert(arr.element_size == 0);
    assert(arr.size == 0);
    assert(arr.capacity == 0);
}
