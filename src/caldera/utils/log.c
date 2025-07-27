#include "log.h"

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

void fatalf(const char *format, ...) {
    va_list args;
    va_start(args, format);

    char message[1024];
    vsnprintf(message, sizeof(message), format, args);

    va_end(args);

    fprintf(stderr, "[FATAL]: %s\n", message);
    exit(EXIT_FAILURE);
}

void debugf(const char *format, ...) {
#ifdef DEBUG
    va_list args;
    va_start(args, format);

    char message[1024];
    vsnprintf(message, sizeof(message), format, args);

    va_end(args);

    fprintf(stderr, "[DEBUG]: %s\n", message);
#endif
}
