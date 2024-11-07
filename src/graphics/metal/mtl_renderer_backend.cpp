#include "mtl_graphics_context.hpp"

extern "C" {
#include <graphics/backend/renderer_backend.h>
#include <utils/utils.h>
}

static struct {
    int width;
    int height;

    MTL::RenderPipelineState *render_pipeline;

    NS::AutoreleasePool *pool;
    CA::MetalDrawable *metal_drawable;
    MTL::CommandBuffer *command_buffer;
    MTL::RenderCommandEncoder *encoder;
} context{
    .width = 1,
    .height = 1
};

static MTL::RenderPipelineState *build_pipeline(const char *shader_filename) {
    mtl_graphics_context ctx = graphics_context;

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

void renderer_backend_init() {
    context.render_pipeline = build_pipeline("../res/shaders/metal/general.metal");
}

void renderer_backend_begin() {
    context.pool = NS::AutoreleasePool::alloc()->init();
    context.metal_drawable = graphics_context.mtl_layer->nextDrawable();

    context.command_buffer = graphics_context.command_queue->commandBuffer();

    MTL::RenderPassDescriptor *render_pass = MTL::RenderPassDescriptor::alloc()->init();

    MTL::RenderPassColorAttachmentDescriptor *color_attachment = render_pass->colorAttachments()->object(0);
    color_attachment->setTexture(context.metal_drawable->texture());
    color_attachment->setLoadAction(MTL::LoadActionClear);
    color_attachment->setClearColor(MTL::ClearColor(0.1f, 0.1f, 0.1f, 1.0f));
    color_attachment->setStoreAction(MTL::StoreActionStore);

    context.encoder = context.command_buffer->renderCommandEncoder(render_pass);
    context.encoder->setRenderPipelineState(context.render_pipeline);

    context.encoder->setViewport({0, 0, (double) context.width, (double) context.height, 0, 1});
    //context.encoder->setScissorRect({0, 0, (uint32_t) context.width, (uint32_t) context.height});
}

void renderer_backend_set_viewport(int width, int height) {
    context.width = width;
    context.height = height;
}

void renderer_backend_submit(vertex_buffer vb, index_buffer ib, uint32_t index_count) {
    MTL::RenderCommandEncoder *encoder = context.encoder;
    encoder->setVertexBuffer(static_cast<MTL::Buffer *>(vb.platform_buffer), 0, 0);
    encoder->drawIndexedPrimitives(
        MTL::PrimitiveType::PrimitiveTypeTriangle,
        index_count,
        MTL::IndexType::IndexTypeUInt32,
        static_cast<MTL::Buffer *>(ib.platform_buffer),
        0,
        1
    );
}

void renderer_backend_end() {
    context.encoder->endEncoding();

    context.command_buffer->presentDrawable(context.metal_drawable);
    context.command_buffer->commit();
    context.command_buffer->waitUntilCompleted();

    context.pool->release();
}

void renderer_backend_destroy() {
    context.render_pipeline->release();
}
