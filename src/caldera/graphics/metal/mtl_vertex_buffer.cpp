extern "C" {
#include <caldera/graphics/backend/vertex_buffer.h>
}

#include "mtl_graphics_context.hpp"

void vertex_buffer_init(vertex_buffer *buffer, uint32_t size) {
    buffer->platform_buffer = graphics_context.device->newBuffer(size, MTL::StorageModeShared);
}

void vertex_buffer_free(vertex_buffer *buffer) {
    auto *platform_buffer = static_cast<MTL::Buffer *>(buffer->platform_buffer);
    platform_buffer->release();

    buffer->platform_buffer = nullptr;
}

void vertex_buffer_set(vertex_buffer *buffer, const void *data, uint32_t size) {
    auto *platform_buffer = static_cast<MTL::Buffer *>(buffer->platform_buffer);
    memcpy(platform_buffer->contents(), data, size);
}
