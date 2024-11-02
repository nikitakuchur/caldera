#include "mtl_renderer.hpp"

#include "mtl_context.hpp"

void mtl_renderer_draw() {
    mtl_context ctx = metal_graphics_context;

    NS::AutoreleasePool* pool = NS::AutoreleasePool::alloc()->init();
    CA::MetalDrawable* metalDrawable = ctx.mtl_layer->nextDrawable();

    auto command_buffer = ctx.command_queue->commandBuffer();

    MTL::RenderPassDescriptor* renderPassDescriptor = MTL::RenderPassDescriptor::alloc()->init();

    MTL::RenderPassColorAttachmentDescriptor* colorAttachment = renderPassDescriptor->colorAttachments()->object(0);
    colorAttachment->setTexture(metalDrawable->texture());
    colorAttachment->setLoadAction(MTL::LoadActionClear);
    colorAttachment->setClearColor(MTL::ClearColor(0.6f, 0.2f, 0.5f, 1.0f));
    colorAttachment->setStoreAction(MTL::StoreActionStore);

    MTL::RenderCommandEncoder* renderCommandEncoder = command_buffer->renderCommandEncoder(renderPassDescriptor);
    renderCommandEncoder->endEncoding();

    command_buffer->presentDrawable(metalDrawable);
    command_buffer->commit();
    command_buffer->waitUntilCompleted();
    pool->release();
}
