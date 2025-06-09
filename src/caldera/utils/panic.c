#include "panic.h"

#include <stdio.h>
#include <stdlib.h>

void panic(char* message) {
    fprintf(stderr, "PANIC: %s\n", message);
    abort(); // exit with non-zero status
}
