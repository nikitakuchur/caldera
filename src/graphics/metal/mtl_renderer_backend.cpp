#include "mtl_graphics_context.hpp"

extern "C" {
#include <graphics/backend/renderer_backend.h>
#include <utils/utils.h>
#include <math/cam.h>
#include <math/mat4.h>
}

static struct {
    MTL::RenderPipelineState *render_pipeline;

    NS::AutoreleasePool *pool;
    CA::MetalDrawable *metal_drawable;
    MTL::CommandBuffer *command_buffer;
    MTL::RenderCommandEncoder *encoder;

    struct {
        mat4 model_mat;
        mat4 view_mat;
        mat4 proj_mat;
    } uniforms;
} context;

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
    descriptor->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm);

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

    mat4_identity(context.uniforms.model_mat);
    mat4_identity(context.uniforms.view_mat);
    ortho(-1, 1, -1, 1, 0, 1, context.uniforms.proj_mat);
}

void renderer_backend_set_model_mat(mat4 model_mat) {
    mat4_copy(model_mat, context.uniforms.model_mat);
}

void renderer_backend_set_view_mat(mat4 view_mat) {
    mat4_copy(view_mat, context.uniforms.view_mat);
}

void renderer_backend_set_proj_mat(mat4 proj_mat) {
    mat4_copy(proj_mat, context.uniforms.proj_mat);
}

void renderer_backend_set_size(int width, int height) {
    graphics_context.mtl_layer->setDrawableSize({(float) width, (float) height});
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
}

void renderer_backend_submit(vertex_buffer vb, index_buffer ib, uint32_t index_count) {
    MTL::RenderCommandEncoder *encoder = context.encoder;
    encoder->setVertexBuffer(static_cast<MTL::Buffer *>(vb.platform_buffer), 0, 0);
    encoder->setVertexBytes(&context.uniforms, sizeof(context.uniforms), 1);
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
