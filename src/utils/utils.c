#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

char* read_file(const char* filename) {
    FILE *file = fopen(filename, "r");

    if (!file) {
        return nullptr;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *str = malloc((length + 1) * sizeof(char));

    fread(str, 1, length, file);
    fclose(file);

    str[length] = '\0';

    return str;
}
