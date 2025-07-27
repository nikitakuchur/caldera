#include "components.h"

#include <stdarg.h>
#include <stdio.h>

void ec_text_printf(ec_text *text, const char *fmt, ...) {
    if (!text || !fmt) return;

    va_list args;
    va_start(args, fmt);

    // estimate the required size
    va_list args_copy;
    va_copy(args_copy, args);
    int len = vsnprintf(nullptr, 0, fmt, args_copy);
    va_end(args_copy);

    if (len < 0) {
        va_end(args);
        return;
    }

    // allocate and format the string
    char *buffer = malloc(len + 1);
    if (!buffer) {
        va_end(args);
        return;
    }

    vsnprintf(buffer, len + 1, fmt, args);
    va_end(args);

    // Replace previous string
    free(text->str);
    text->str = buffer;
}

void ec_text_free(void *ptr) {
    ec_text *text = ptr;
    free(text->str);
    text->str = nullptr;
}
