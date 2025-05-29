extern "C" {
#include <caldera/graphics/backend/vertex_buffer.h>
}

#include "mtl_graphics_context.hpp"

vertex_buffer vertex_buffer_create(uint32_t size) {
    MTL::Buffer *buffer = graphics_context.device->newBuffer(size, MTL::StorageModeShared);
    return {buffer};
}

void vertex_buffer_set(vertex_buffer vb, const void *data, uint32_t size) {
    auto *buffer = static_cast<MTL::Buffer *>(vb.platform_buffer);
    memcpy(buffer->contents(), data, size);
}

void vertex_buffer_destroy(vertex_buffer vb) {
    auto *buffer = static_cast<MTL::Buffer *>(vb.platform_buffer);
    buffer->release();
}
