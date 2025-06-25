#include <assert.h>
#include <caldera/containers/bitset.h>
#include <stdio.h>

bool contains(const size_t arr[], size_t size, size_t value) {
    for (size_t i = 0; i < size; i++) {
        if (value == arr[i]) {
            return true;
        }
    }
    return false;
}

int main() {
    bitset bs;
    bitset_init(&bs, 130);

    for (size_t i = 0; i < bs.size; i++) {
        bool bit = bitset_get(&bs, i);
        printf("[%lu]=%d, ", i, bit);
        assert(!bit);
    }
    printf("\n");

    size_t enabled_bits_1[] = {5, 36, 63, 64, 65, 66, 128, 129};
    size_t enabled_bits_1_size = sizeof(enabled_bits_1) / sizeof(enabled_bits_1[0]);

    for (size_t i = 0; i < enabled_bits_1_size; i++) {
        bitset_set(&bs, enabled_bits_1[i], true);
    }

    for (size_t i = 0; i < bs.size; i++) {
        bool bit = bitset_get(&bs, i);
        printf("[%lu]=%d, ", i, bit);

        bool expected = contains(enabled_bits_1, enabled_bits_1_size, i);
        assert(bit == expected);
    }
    printf("\n");

    bitset_set(&bs, 63, false);
    bitset_set(&bs, 128, false);
    bitset_set(&bs, 129, false);

    size_t enabled_bits_2[] = {5, 36, 64, 65, 66};
    size_t enabled_bits_2_size = sizeof(enabled_bits_2) / sizeof(enabled_bits_2[0]);

    for (size_t i = 0; i < bs.size; i++) {
        bool bit = bitset_get(&bs, i);
        printf("[%lu]=%d, ", i, bit);

        bool expected = contains(enabled_bits_2, enabled_bits_2_size, i);
        assert(bit == expected);
    }
    printf("\n");

    bitset_clear(&bs);

    for (size_t i = 0; i < bs.size; i++) {
        bool bit = bitset_get(&bs, i);
        printf("[%lu]=%d, ", i, bit);
        assert(!bit);
    }

    bitset_free(&bs);
}