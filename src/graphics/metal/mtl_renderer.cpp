#include "mtl_renderer.hpp"

#include "mtl_graphics_context.hpp"

extern "C" {
#include <graphics/api/renderer.h>
}

void renderer_draw_triangle() {
    mtl_graphics_context ctx = metal_graphics_context;

    NS::AutoreleasePool *pool = NS::AutoreleasePool::alloc()->init();
    CA::MetalDrawable *metal_drawable = ctx.mtl_layer->nextDrawable();

    auto command_buffer = ctx.command_queue->commandBuffer();

    MTL::RenderPassDescriptor *render_pass = MTL::RenderPassDescriptor::alloc()->init();

    MTL::RenderPassColorAttachmentDescriptor *color_attachment = render_pass->colorAttachments()->object(0);
    color_attachment->setTexture(metal_drawable->texture());
    color_attachment->setLoadAction(MTL::LoadActionClear);
    color_attachment->setClearColor(MTL::ClearColor(0.1f, 0.1f, 0.1f, 1.0f));
    color_attachment->setStoreAction(MTL::StoreActionStore);

    MTL::RenderCommandEncoder *encoder = command_buffer->renderCommandEncoder(render_pass);

    // draw a triangle
    encoder->setRenderPipelineState(ctx.render_pipeline_state);
    encoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, static_cast<NS::UInteger>(0), 3);
    encoder->endEncoding();

    command_buffer->presentDrawable(metal_drawable);
    command_buffer->commit();
    command_buffer->waitUntilCompleted();

    pool->release();
}
