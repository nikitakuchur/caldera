#ifndef FONT_H
#define FONT_H

#include "caldera/defines.h"
#include "caldera/graphics/backend/texture.h"

#define FIRST_CHAR 32
#define CHAR_NUM 95

#define ATLAS_WIDTH 512
#define ATLAS_HEIGHT 512

#define FONT_SIZE 18.f

typedef struct packed_char {
    u8 x0, y0, x1, y1;
    f32 xoff, yoff, xadvance;
    f32 xoff2, yoff2;
} packed_char;

typedef struct {
    f32 x0, y0, s0, t0;
    f32 x1, y1, s1, t1;
} aligned_quad;

typedef struct font {
    texture atlas;
    ivec2 size;
    packed_char packed_chars[CHAR_NUM];
    aligned_quad aligned_quads[CHAR_NUM];
} font;

b8 font_init(font *font, const char *filename);

void font_free(font *font);

#endif //FONT_H
