#ifndef FONT_H
#define FONT_H

#include "caldera/defines.h"
#include "caldera/graphics/backend/texture.h"

#define ATLAS_WIDTH 1024
#define ATLAS_HEIGHT 1024

#define FONT_SIZE 18.f

#define CHAR_SETS_COUNT 3

typedef struct packed_char {
    u16 x0, y0, x1, y1;
    f32 xoff, yoff, xadvance;
    f32 xoff2, yoff2;
} packed_char;

typedef struct {
    f32 x0, y0, s0, t0; // top-left
    f32 x1, y1, s1, t1; // bottom-right
} aligned_quad;

typedef struct char_set {
    u32 first;
    u32 range;

    packed_char *packed_chars;
    aligned_quad *aligned_quads;
} char_set;

typedef struct font {
    ivec2 size;
    texture atlas;

    char_set char_sets[CHAR_SETS_COUNT];
    char_set specials;
} font;

b8 font_init(font *font, const char *filename);

void font_free(font *font);

#endif //FONT_H
