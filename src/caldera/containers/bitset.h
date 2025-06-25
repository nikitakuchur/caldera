#ifndef BITSET_H
#define BITSET_H

#include <stddef.h>
#include <stdint.h>

typedef struct bitset {
    uint64_t *bits;
    size_t size;
} bitset;

bool bitset_init(bitset *set, size_t size);

void bitset_free(bitset *set);

void bitset_set(const bitset *set, size_t index, bool value);

bool bitset_get(const bitset *set, size_t index);

void bitset_clear(const bitset *set);

#endif //BITSET_H
