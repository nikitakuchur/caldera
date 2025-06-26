#include "bitset.h"

#include <assert.h>
#include <stdlib.h>

// calculates the number of 64-bit words needed to store the given number of bits
size_t bitset_num_words(size_t size) {
    return (size + 63) / 64;
}

bool bitset_init(bitset *set, size_t size) {
    size_t num_words = bitset_num_words(size); // 64 bits
    set->words = malloc(sizeof(uint64_t) * num_words);
    if (!set->words) {
        // failed to allocate bitset
        return false;
    }
    for (size_t i = 0; i < num_words; i++) {
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

void bitset_set(const bitset *set, size_t index, bool value) {
    assert(index < set->size);

    size_t word_index = index / 64;

    uint64_t mask = (uint64_t) 1 << (index % 64);
    if (value) {
        set->words[word_index] |= mask;
    } else {
        mask = ~mask;
        set->words[word_index] &= mask;
    }
}

bool bitset_get(const bitset *set, size_t index) {
    assert(index < set->size);
    size_t word_index = index / 64;
    uint64_t mask = (uint64_t) 1 << (index % 64);
    return (set->words[word_index] & mask) != 0;
}

void bitset_clear(const bitset *set) {
    size_t num_words = bitset_num_words(set->size);
    for (size_t i = 0; i < num_words; i++) {
        set->words[i] = 0;
    }
}
