#include "utf8.h"

#include "caldera/defines.h"

u32 utf8_char_len(char c) {
    if ((c & 0x80) == 0) return 1; // ASCII
    if ((c & 0xE0) == 0xC0) return 2; // 2-byte sequence
    if ((c & 0xF0) == 0xE0) return 3; // 3-byte sequence
    if ((c & 0xF8) == 0xF0) return 4; // 4-byte sequence
    return 1; // fallback
}

u32 utf8_to_codepoint(const char *p, u32 len) {
    switch (len) {
        case 1: return p[0];
        case 2: return (p[0] & 0x1F) << 6 |
                       p[1] & 0x3F;
        case 3: return (p[0] & 0x0F) << 12 |
                       (p[1] & 0x3F) << 6 |
                       p[2] & 0x3F;
        case 4: return (p[0] & 0x07) << 18 |
                       (p[1] & 0x3F) << 12 |
                       (p[2] & 0x3F) << 6 |
                       p[3] & 0x3F;
        default: return 0xFFFD; // replacement character
    }
}
