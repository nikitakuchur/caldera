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

void texture_init(texture *texture, const char *filename) {
    static i32 id = -1;
    id++;

    i32 width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    u8 *data = stbi_load(filename, &width, &height, &channels, 0);
    if (!data) {
        printf("failed to load a texture %s\n", filename);
        texture_init_empty(texture);
        return;
    }

    auto texture_descriptor = MTL::TextureDescriptor::texture2DDescriptor(
        MTL::PixelFormatRGBA8Unorm,
        width,
        height,
        false
    );
    auto mtl_texture = graphics_context.device->newTexture(texture_descriptor);

    MTL::Region region = MTL::Region::Make2D(0, 0, width, height);
    u32 bytes_per_row = width * 4; // 4 bytes per pixel (RGBA)
    mtl_texture->replaceRegion(region, 0, data, bytes_per_row);

    stbi_image_free(data);

    texture->id = id;
    texture->size = {width, height};
    texture->platform_texture = mtl_texture;
}

void texture_free(texture *texture) {
    static_cast<MTL::Texture *>(texture->platform_texture)->release();
    texture_init_empty(texture);
}
