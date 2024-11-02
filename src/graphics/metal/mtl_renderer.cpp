#include "mtl_renderer.hpp"

#include "mtl_context.hpp"

void mtl_renderer_draw() {
    auto [device, mtl_layer, ns_window, command_queue] = metal_graphics_context;

    NS::AutoreleasePool* pool = NS::AutoreleasePool::alloc()->init();
    CA::MetalDrawable* metal_drawable = mtl_layer->nextDrawable();

    auto command_buffer = command_queue->commandBuffer();

    MTL::RenderPassDescriptor* renderPassDescriptor = MTL::RenderPassDescriptor::alloc()->init();

    MTL::RenderPassColorAttachmentDescriptor* colorAttachment = renderPassDescriptor->colorAttachments()->object(0);
    colorAttachment->setTexture(metal_drawable->texture());
    colorAttachment->setLoadAction(MTL::LoadActionClear);
    colorAttachment->setClearColor(MTL::ClearColor(0.6f, 0.2f, 0.5f, 1.0f));
    colorAttachment->setStoreAction(MTL::StoreActionStore);

    MTL::RenderCommandEncoder* renderCommandEncoder = command_buffer->renderCommandEncoder(renderPassDescriptor);
    renderCommandEncoder->endEncoding();

    command_buffer->presentDrawable(metal_drawable);
    command_buffer->commit();
    command_buffer->waitUntilCompleted();

    pool->release();
}
