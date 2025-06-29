#ifndef UTILS_H
#define UTILS_H

#include "caldera/defines.h"

// caller is responsible for freeing the returned string when no longer needed
char* read_text_file(const char* filename);

u8 *read_file(const char *filename, i64 *out_size);

#endif //UTILS_H
