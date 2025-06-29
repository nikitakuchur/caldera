#ifndef BITSET_H
#define BITSET_H

#include "caldera/defines.h"

typedef struct bitset {
    u64 *words;
    u32 size;
} bitset;

b8 bitset_init(bitset *set, u32 size);

void bitset_free(bitset *set);

void bitset_set(bitset *set, u32 index, b8 value);

b8 bitset_get(const bitset *set, u32 index);

void bitset_clear(bitset *set);

#endif //BITSET_H
