#include "bitset.h"

#include <assert.h>
#include <stdlib.h>

// calculates the number of 64-bit words needed to store the given number of bits
static u32 bitset_num_words(u32 size) {
    return (size + 63) / 64;
}

b8 bitset_init(bitset *set, u32 size) {
    u32 num_words = bitset_num_words(size);
    set->words = malloc(sizeof(u64) * num_words);
    if (!set->words) {
        // failed to allocate bitset
        return false;
    }
    for (u32 i = 0; i < num_words; i++) {
        set->words[i] = 0;
    }
    set->size = size;
    return true;
}

void bitset_free(bitset *set) {
    free(set->words);
    set->words = nullptr;
    set->size = 0;
}

void bitset_set(bitset *set, u32 index, b8 value) {
    assert(index < set->size);

    u32 word_index = index / 64;

    u64 mask = (u64) 1 << (index % 64);
    if (value) {
        set->words[word_index] |= mask;
    } else {
        mask = ~mask;
        set->words[word_index] &= mask;
    }
}

b8 bitset_get(const bitset *set, u32 index) {
    assert(index < set->size);
    u32 word_index = index / 64;
    uint64_t mask = (u64) 1 << (index % 64);
    return (set->words[word_index] & mask) != 0;
}

void bitset_clear(bitset *set) {
    u32 num_words = bitset_num_words(set->size);
    for (u32 i = 0; i < num_words; i++) {
        set->words[i] = 0;
    }
}
