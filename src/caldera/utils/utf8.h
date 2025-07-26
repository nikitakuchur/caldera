#ifndef UTF8_H
#define UTF8_H

#include "caldera/defines.h"

u32 utf8_char_len(char c);

u32 utf8_to_codepoint(const char *p, u32 len);

#endif //UTF8_H
