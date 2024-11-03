extern "C" {
#include <graphics/api/vertex_buffer.h>
}

#include "mtl_graphics_context.hpp"

vertex_buffer vertex_buffer_create(uint32_t size) {
    MTL::Buffer *mtl_buffer = metal_graphics_context.device->newBuffer(size, MTL::StorageModeShared);
    return {mtl_buffer};
}

void vertex_buffer_set(vertex_buffer buffer, const void *data, uint32_t size) {
    auto *mtl_buffer = static_cast<MTL::Buffer *>(buffer.platform_buffer);
    memcpy(mtl_buffer->contents(), data, size);
}

void vertex_buffer_destroy(vertex_buffer buffer) {
    auto *mtl_buffer = static_cast<MTL::Buffer *>(buffer.platform_buffer);
    mtl_buffer->release();
}
