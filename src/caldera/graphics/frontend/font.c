#include "font.h"

#include <stdlib.h>
#include <stb_truetype.h>

#include "caldera/utils/files.h"

b8 font_init(font *font, const char *filename) {
    i64 font_size;
    u8 *font_buffer = read_file(filename, &font_size);

    stbtt_fontinfo info;
    if (!stbtt_InitFont(&info, font_buffer, 0)) {
        return false;
    }

    u8 bitmap[ATLAS_WIDTH * ATLAS_HEIGHT];

    stbtt_pack_context ctx;
    stbtt_PackBegin(&ctx, bitmap, ATLAS_WIDTH, ATLAS_HEIGHT, 0, 1, nullptr);
    stbtt_PackFontRange(
        &ctx,
        font_buffer,
        0,
        FONT_SIZE,
        FIRST_CHAR,
        CHAR_NUM,
        font->packed_chars
    );
    stbtt_PackEnd(&ctx);

    for (i32 i = 0; i < CHAR_NUM; i++) {
        f32 x, y;
        stbtt_GetPackedQuad(
            font->packed_chars,
            ATLAS_WIDTH,
            ATLAS_HEIGHT,
            i,
            &x,
            &y,
            &font->aligned_quads[i],
            0
        );
    }

    free(font_buffer);

    u8 *result_bitmap = malloc(4 * ATLAS_WIDTH * ATLAS_HEIGHT * sizeof(u8));

    for (u32 i = 0; i < ATLAS_WIDTH * ATLAS_HEIGHT; i++) {
        result_bitmap[i * 4] = bitmap[i];
        result_bitmap[i * 4 + 1] = bitmap[i];
        result_bitmap[i * 4 + 2] = bitmap[i];
        result_bitmap[i * 4 + 3] = bitmap[i];
    }

    texture atlas;
    texture_init(&atlas, result_bitmap, ATLAS_WIDTH, ATLAS_HEIGHT);

    free(result_bitmap);

    font->atlas = atlas;
    font->size.x = ATLAS_WIDTH;
    font->size.y = ATLAS_HEIGHT;

    return true;
}

void font_free(font *font) {
    texture_free(&font->atlas);
    font->size = ivec2_zero();
}
