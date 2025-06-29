#include "panic.h"

#include <stdio.h>
#include <stdlib.h>

void panic(const char* message) {
    fprintf(stderr, "PANIC: %s\n", message);
    exit(EXIT_FAILURE);
}
