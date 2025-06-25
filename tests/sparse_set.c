#include <assert.h>
#include <caldera/containers/sparse_set.h>
#include <stdio.h>

typedef struct component {
    float x, y;
} component;

void print_all(const sparse_set *set, size_t size) {
    for (size_t i = 0; i < size; i++) {
        const component *c = sparse_set_get(set, i);
        if (c == nullptr) {
            printf("%lu: NULL\n", i);
            continue;
        }
        printf("%lu: component_x=%f, component_y=%f\n", i, c->x, c->y);
    }
}

int main() {
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

    print_all(&set, 3);
    printf("\n");

    c1 = sparse_set_get(&set, 0);
    assert(c1->x == 20);
    assert(c1->y == 42);

    c2 = sparse_set_get(&set, 1);
    assert(c2->x == 55);
    assert(c2->y == 66);

    c3 = sparse_set_get(&set, 2);
    assert(c3->x == 77);
    assert(c3->y == 88);

    sparse_set_remove(&set, 1);

    print_all(&set, 3);

    c1 = sparse_set_get(&set, 0);
    assert(c1->x == 20);
    assert(c1->y == 42);

    c2 = sparse_set_get(&set, 1);
    assert(c2 == nullptr);

    c3 = sparse_set_get(&set, 2);
    assert(c3->x == 77);
    assert(c3->y == 88);

    sparse_set_free(&set);

    return 0;
}
