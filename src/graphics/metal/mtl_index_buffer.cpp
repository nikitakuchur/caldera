extern "C" {
#include <graphics/backend/index_buffer.h>
}

#include "mtl_graphics_context.hpp"

index_buffer index_buffer_create(uint32_t count) {
    MTL::Buffer *buffer = graphics_context.device->newBuffer(count * sizeof(uint32_t), MTL::StorageModeShared);
    return {buffer, count};
}

void index_buffer_set(index_buffer ib, const uint32_t *indices, uint32_t count) {
    auto *buffer = static_cast<MTL::Buffer *>(ib.platform_buffer);
    memcpy(buffer->contents(), indices, count * sizeof(uint32_t));
}

void index_buffer_destroy(index_buffer ib) {
    auto *buffer = static_cast<MTL::Buffer *>(ib.platform_buffer);
    buffer->release();
}