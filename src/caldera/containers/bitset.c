#include "bitset.h"

#include <assert.h>
#include <stdlib.h>
#include "caldera/utils/panic.h"

void bitset_init(bitset *set, size_t size) {
    size_t arr_size = (size + 63) / 64; // 64 bits
    set->bits = malloc(sizeof(uint64_t) * arr_size);
    if (!set->bits) {
        panic("failed to allocate bitset");
    }
    for (size_t i = 0; i < arr_size; i++) {
        set->bits[i] = 0;
    }
    set->size = size;
}

void bitset_set(const bitset *set, size_t index, bool value) {
    assert(index < set->size);

    size_t arr_index = index / 64;

    uint64_t mask = (uint64_t) 1 << (index % 64);
    if (value) {
        set->bits[arr_index] |= mask;
    } else {
        mask = ~mask;
        set->bits[arr_index] &= mask;
    }
}

bool bitset_get(const bitset *set, size_t index) {
    assert(index < set->size);
    size_t arr_index = index / 64;
    uint64_t mask = (uint64_t) 1 << (index % 64);
    return (set->bits[arr_index] & mask) != 0;
}

void bitset_clear(const bitset *set) {
    size_t array_size = (set->size + 63) / 64;
    for (size_t i = 0; i < array_size; i++) {
        set->bits[i] = 0;
    }
}

void bitset_free(bitset *set) {
    free(set->bits);
    set->size = 0;
}
