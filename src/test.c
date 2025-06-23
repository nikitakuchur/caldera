#include <stdio.h>

#include "caldera/containers/bitset.h"
#include "caldera/containers/sparse_set.h"

typedef struct component {
    float x, y;
} component;

int main() {
    // bitset test
    bitset bs;
    bitset_init(&bs, 130);

    for (size_t i = 0; i < 130; i++) {
        bool bit = bitset_get(&bs, i);
        printf("%lu: %d, ", i, bit);
    }
    printf("\n\n");

    bitset_set(&bs, 5, true);
    bitset_set(&bs, 36, true);
    bitset_set(&bs, 63, true);
    bitset_set(&bs, 64, true);
    bitset_set(&bs, 65, true);
    bitset_set(&bs, 128, true);
    bitset_set(&bs, 129, true);

    for (size_t i = 0; i < 130; i++) {
        bool bit = bitset_get(&bs, i);
        printf("%lu: %d, ", i, bit);
    }
    printf("\n\n");

    bitset_set(&bs, 63, false);
    bitset_set(&bs, 128, false);
    bitset_set(&bs, 129, false);

    for (size_t i = 0; i < 130; i++) {
        bool bit = bitset_get(&bs, i);
        printf("%lu: %d, ", i, bit);
    }
    printf("\n\n");

    bitset_free(&bs);


    // sparse set test
    sparse_set set;
    sparse_set_init(&set, sizeof(component));

    component *c1 = sparse_set_add(&set, 0);
    c1->x = 20;
    c1->y = 42;

    component *c2 = sparse_set_add(&set, 1);
    c2->x = 55;
    c2->y = 66;

    component *c3 = sparse_set_add(&set, 2);
    c3->x = 77;
    c3->y = 88;

    for (size_t i = 0; i < 3; i++) {
        const component *c = sparse_set_get(&set, i);
        if (c == nullptr) continue;
        printf("%lu: component_x=%f, component_y=%f\n", i, c->x, c->y);
    }

    sparse_set_remove(&set, 1);

    for (size_t i = 0; i < 3; i++) {
        const component *c = sparse_set_get(&set, i);
        if (c == nullptr) continue;
        printf("%lu: component_x=%f, component_y=%f\n", i, c->x, c->y);
    }

    sparse_set_free(&set);

    return 0;
}
