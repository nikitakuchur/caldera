#include "files.h"

#include <stdio.h>
#include <stdlib.h>

#include "caldera/defines.h"

char *read_text_file(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (!file) {
        return nullptr;
    }

    fseek(file, 0, SEEK_END);
    i64 length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *str = malloc((length + 1) * sizeof(char));
    if (!str) {
        return nullptr;
    }

    fread(str, 1, length, file);
    fclose(file);

    str[length] = '\0';

    return str;
}

u8 *read_file(const char *filename, i64 *out_size) {
    FILE *file = fopen(filename, "rb");

    if (!file) {
        if (out_size) *out_size = 0;
        return nullptr;
    }

    fseek(file, 0, SEEK_END);
    i64 size = ftell(file);
    fseek(file, 0, SEEK_SET);

    u8* buffer = malloc(size * sizeof(u8));
    if (!buffer) {
        fclose(file);
        if (out_size) *out_size = 0;
        return nullptr;
    }

    fread(buffer, size, 1, file);
    fclose(file);

    if (out_size) *out_size = size;
    return buffer;
}
