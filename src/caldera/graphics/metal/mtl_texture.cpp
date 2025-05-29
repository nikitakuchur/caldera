extern "C" {
#include <caldera/graphics/backend/texture.h>
}

#include <cstdio>
#include <stb_image.h>
#include <Metal/MTLTexture.hpp>

#include "mtl_graphics_context.hpp"

texture texture_create_empty() {
    return {-1, 0, 0, nullptr};
}

texture texture_create(const char *filename) {
    static int id = -1;
    id++;

    int width, height, channels;
    stbi_set_flip_vertically_on_load(1);
    uint8_t *data = stbi_load(filename, &width, &height, &channels, 0);
    if (!data) {
        printf("failed to load a texture\n");
        return {};
    }

    auto texture_descriptor = MTL::TextureDescriptor::texture2DDescriptor(
        MTL::PixelFormatRGBA8Unorm,
        width,
        height,
        false
    );
    auto mtl_texture = graphics_context.device->newTexture(texture_descriptor);

    MTL::Region region = MTL::Region::Make2D(0, 0, width, height);
    size_t bytes_per_row = width * 4; // 4 bytes per pixel (RGBA)
    mtl_texture->replaceRegion(region, 0, data, bytes_per_row);

    stbi_image_free(data);

    return (texture){id, width, height, mtl_texture};
}

void texture_destroy(texture texture) {
    static_cast<MTL::Texture *>(texture.platform_texture)->release();
}