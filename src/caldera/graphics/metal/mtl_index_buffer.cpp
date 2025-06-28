extern "C" {
#include <caldera/graphics/backend/index_buffer.h>
}

#include "mtl_graphics_context.hpp"

void index_buffer_init(index_buffer *buffer, uint32_t count) {
    buffer->platform_buffer = graphics_context.device->newBuffer(count * sizeof(uint32_t), MTL::StorageModeShared);
    buffer->count = count;
}

void index_buffer_free(index_buffer *buffer) {
    auto *platform_buffer = static_cast<MTL::Buffer *>(buffer->platform_buffer);
    platform_buffer->release();

    buffer->platform_buffer = nullptr;
    buffer->count = 0;
}

void index_buffer_set(index_buffer *buffer, const uint32_t *indices, uint32_t count) {
    auto *platform_buffer = static_cast<MTL::Buffer *>(buffer->platform_buffer);
    memcpy(platform_buffer->contents(), indices, count * sizeof(uint32_t));
}
