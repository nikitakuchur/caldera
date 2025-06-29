extern "C" {
#include <caldera/graphics/backend/texture.h>
}

#include <cstdio>
#include <stb_image.h>
#include <Metal/MTLTexture.hpp>

#include "mtl_graphics_context.hpp"

void texture_init_empty(texture *texture) {
    texture->id = -1;
    texture->size = {0, 0};
    texture->platform_texture = nullptr;
}

void texture_init(texture *texture, u8 *bitmap, u32 width, u32 height) {
    static i32 id = -1;
    id++;

    auto texture_descriptor = MTL::TextureDescriptor::texture2DDescriptor(
        MTL::PixelFormatRGBA8Unorm,
        width,
        height,
        false
    );
    auto mtl_texture = graphics_context.device->newTexture(texture_descriptor);

    MTL::Region region = MTL::Region::Make2D(0, 0, width, height);
    u32 bytes_per_row = width * 4; // 4 bytes per pixel (RGBA)
    mtl_texture->replaceRegion(region, 0, bitmap, bytes_per_row);

    texture->id = id;
    texture->size = {
        static_cast<i32>(width),
        static_cast<i32>(height)
    };
    texture->platform_texture = mtl_texture;
}

b8 texture_load_from_file(texture *texture, const char *filename) {
    stbi_set_flip_vertically_on_load(1);

    i32 width, height, channels;
    u8 *bitmap = stbi_load(filename, &width, &height, &channels, 0);
    if (!bitmap) {
        printf("failed to load a texture %s\n", filename);
        texture_init_empty(texture);
        return false;
    }

    texture_init(texture, bitmap, static_cast<u32>(width), static_cast<u32>(height));
    free(bitmap);

    return true;
}

void texture_free(texture *texture) {
    static_cast<MTL::Texture *>(texture->platform_texture)->release();
    texture_init_empty(texture);
}
