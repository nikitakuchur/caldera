#include <assert.h>
#include <caldera/containers/bitset.h>
#include <stdio.h>

b8 contains(const u32 arr[], u32 size, u32 value) {
    for (u32 i = 0; i < size; i++) {
        if (value == arr[i]) {
            return true;
        }
    }
    return false;
}

i32 main() {
    bitset bs;
    bool success = bitset_init(&bs, 130);
    assert(success);

    for (u32 i = 0; i < bs.size; i++) {
        b8 bit = bitset_get(&bs, i);
        printf("[%u]=%d, ", i, bit);
        assert(!bit);
    }
    printf("\n");

    u32 enabled_bits_1[] = {5, 36, 63, 64, 65, 66, 128, 129};
    u32 enabled_bits_1_size = sizeof(enabled_bits_1) / sizeof(enabled_bits_1[0]);

    for (u32 i = 0; i < enabled_bits_1_size; i++) {
        bitset_set(&bs, enabled_bits_1[i], true);
    }

    for (u32 i = 0; i < bs.size; i++) {
        b8 bit = bitset_get(&bs, i);
        printf("[%u]=%d, ", i, bit);

        b8 expected = contains(enabled_bits_1, enabled_bits_1_size, i);
        assert(bit == expected);
    }
    printf("\n");

    bitset_set(&bs, 63, false);
    bitset_set(&bs, 128, false);
    bitset_set(&bs, 129, false);

    u32 enabled_bits_2[] = {5, 36, 64, 65, 66};
    u32 enabled_bits_2_size = sizeof(enabled_bits_2) / sizeof(enabled_bits_2[0]);

    for (u32 i = 0; i < bs.size; i++) {
        b8 bit = bitset_get(&bs, i);
        printf("[%u]=%d, ", i, bit);

        b8 expected = contains(enabled_bits_2, enabled_bits_2_size, i);
        assert(bit == expected);
    }
    printf("\n");

    bitset_clear(&bs);

    for (u32 i = 0; i < bs.size; i++) {
        b8 bit = bitset_get(&bs, i);
        printf("[%u]=%d, ", i, bit);
        assert(!bit);
    }

    bitset_free(&bs);
    assert(bs.words == nullptr);
    assert(bs.size == 0);
}