#include "font.h"

#include <stdlib.h>
#include <stb_truetype.h>

#include "caldera/utils/files.h"

static b8 char_set_pack(char_set *set, stbtt_pack_context *ctx, const u8 *font_buffer, i32 first, i32 last) {
    set->first = first;
    set->range = last - first + 1;

    set->packed_chars = malloc(set->range * sizeof(packed_char));
    if (set->packed_chars == nullptr) {
        return false;
    }

    set->aligned_quads = malloc(set->range * sizeof(aligned_quad));
    if (set->aligned_quads == nullptr) {
        return false;
    }

    stbtt_PackFontRange(
        ctx,
        font_buffer,
        0,
        FONT_SIZE,
        first,
        (i32) set->range,
        (stbtt_packedchar *) set->packed_chars
    );

    for (i32 i = 0; i < set->range; i++) {
        f32 x, y;
        stbtt_GetPackedQuad(
            (stbtt_packedchar *) set->packed_chars,
            ATLAS_WIDTH,
            ATLAS_HEIGHT,
            i,
            &x,
            &y,
            (stbtt_aligned_quad *) &set->aligned_quads[i],
            0
        );
    }

    return true;
}

static void char_set_free(char_set *set) {
    set->first = 0;
    set->range = 0;

    free(set->packed_chars);
    free(set->aligned_quads);
    set->packed_chars = nullptr;
    set->aligned_quads = nullptr;
}

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

    char_set_pack(&font->char_sets[0], &ctx, font_buffer, 0x0020, 0x007F); // basic latin
    char_set_pack(&font->char_sets[1], &ctx, font_buffer, 0x0410, 0x044F); // cyrillic (Russian)
    char_set_pack(&font->char_sets[2], &ctx, font_buffer, 0xFFF0, 0xFFFF); // specials
    font->specials = font->char_sets[2];

    stbtt_PackEnd(&ctx);

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

    for (u32 i = 0; i < CHAR_SETS_COUNT; i++) {
        char_set_free(&font->char_sets[i]);
    }
}
