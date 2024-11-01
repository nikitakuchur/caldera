#include "mtl_renderer.hpp"

mtl_renderer::mtl_renderer(MTL::Device *device): device(device->retain()) {
    command_queue = device->newCommandQueue();
}

mtl_renderer::~mtl_renderer() {
    command_queue->release();
    device->release();
}

void mtl_renderer::draw(MTK::View *view) {
    NS::AutoreleasePool *pool = NS::AutoreleasePool::alloc()->init();

    MTL::CommandBuffer *command_buffer = command_queue->commandBuffer();
    MTL::RenderPassDescriptor *renderPass = view->currentRenderPassDescriptor();
    MTL::RenderCommandEncoder *encoder = command_buffer->renderCommandEncoder(renderPass);
    encoder->endEncoding();
    command_buffer->presentDrawable(view->currentDrawable());
    command_buffer->commit();

    pool->release();
}
