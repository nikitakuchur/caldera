#include "mtl_graphics_context.hpp"

extern "C" {
#include <graphics/api/renderer.h>
#include <graphics/api/vertex_buffer.h>
#include <utils/utils.h>
}

static MTL::RenderPipelineState *build_pipeline(const char *shader_filename) {
    mtl_graphics_context ctx = metal_graphics_context;

    char *str = read_file(shader_filename);
    if (!str) {
        printf("failed to read the metal shader: %s\n", shader_filename);
        return nullptr;
    }

    NS::String *shader = NS::String::string(str, NS::StringEncoding::ASCIIStringEncoding);
    free(str);

    NS::Error *error = nullptr;
    MTL::CompileOptions *options = nullptr;
    MTL::Library *library = ctx.device->newLibrary(shader, options, &error);
    if (!library) {
        printf("failed to read a metal shader: %s\n", error->localizedDescription()->utf8String());
        return nullptr;
    }

    NS::String *vertex_shader_name = NS::String::string("vertex_shader", NS::StringEncoding::ASCIIStringEncoding);
    MTL::Function *vertex_func = library->newFunction(vertex_shader_name);

    NS::String *fragment_shader_name = NS::String::string("fragment_shader", NS::StringEncoding::ASCIIStringEncoding);
    MTL::Function *fragment_func = library->newFunction(fragment_shader_name);

    MTL::RenderPipelineDescriptor *descriptor = MTL::RenderPipelineDescriptor::alloc()->init();
    descriptor->setVertexFunction(vertex_func);
    descriptor->setFragmentFunction(fragment_func);
    descriptor->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);

    MTL::RenderPipelineState *render_pipeline_state = ctx.device->newRenderPipelineState(descriptor, &error);
    if (!render_pipeline_state) {
        printf("failed to load a metal shader: %s\n", error->localizedDescription()->utf8String());
        return nullptr;
    }

    // free resources
    descriptor->release();
    vertex_func->release();
    fragment_func->release();
    library->release();

    return render_pipeline_state;
}

void renderer_init() {
    metal_graphics_context.render_pipeline = build_pipeline("../res/shaders/metal/general.metal");
}

static struct {
    NS::AutoreleasePool *pool;
    CA::MetalDrawable *metal_drawable;
    MTL::CommandBuffer *command_buffer;
    MTL::RenderCommandEncoder *encoder;
} renderer_context;

void renderer_begin() {
    mtl_graphics_context ctx = metal_graphics_context;

    renderer_context.pool = NS::AutoreleasePool::alloc()->init();
    renderer_context.metal_drawable = ctx.mtl_layer->nextDrawable();

    renderer_context.command_buffer = ctx.command_queue->commandBuffer();

    MTL::RenderPassDescriptor *render_pass = MTL::RenderPassDescriptor::alloc()->init();

    MTL::RenderPassColorAttachmentDescriptor *color_attachment = render_pass->colorAttachments()->object(0);
    color_attachment->setTexture(renderer_context.metal_drawable->texture());
    color_attachment->setLoadAction(MTL::LoadActionClear);
    color_attachment->setClearColor(MTL::ClearColor(0.1f, 0.1f, 0.1f, 1.0f));
    color_attachment->setStoreAction(MTL::StoreActionStore);

    renderer_context.encoder = renderer_context.command_buffer->renderCommandEncoder(render_pass);
    renderer_context.encoder->setRenderPipelineState(ctx.render_pipeline);
}

void renderer_submit(vertex_buffer vb, uint32_t vertex_count) {
    MTL::RenderCommandEncoder *encoder = renderer_context.encoder;
    encoder->setVertexBuffer(static_cast<MTL::Buffer *>(vb.platform_buffer), 0, 0);
    encoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0), vertex_count);
}

void renderer_end() {
    renderer_context.encoder->endEncoding();
    renderer_context.command_buffer->presentDrawable(renderer_context.metal_drawable);
    renderer_context.command_buffer->commit();
    renderer_context.command_buffer->waitUntilCompleted();

    renderer_context.pool->release();
}

void renderer_destroy() {
}
