#include "mtl_graphics_context.hpp"

extern "C" {
#include <graphics/backend/renderer_backend.h>
#include <utils/utils.h>
#include <math/cam.h>
#include <math/mat4.h>
#include <math/vec4.h>
}

static struct {
    MTL::RenderPipelineState *g_buffer_render_pipeline;

    int g_buffer_width;
    int g_buffer_height;

    vec4 clear_color;

    NS::AutoreleasePool *pool;
    MTL::Texture *g_buffer;
    MTL::CommandBuffer *command_buffer;
    MTL::RenderCommandEncoder *batch_encoder;

    struct {
        mat4 model_mat;
        mat4 view_mat;
        mat4 proj_mat;
    } uniforms;

    // the final render pipeline that draws the result on the screen
    MTL::RenderPipelineState *final_render_pipeline;
} context;

static void configure_color_attachment(MTL::RenderPipelineColorAttachmentDescriptor *color_attachment) {
    color_attachment->setPixelFormat(MTL::PixelFormat::PixelFormatRGBA8Unorm);
    color_attachment->setBlendingEnabled(true);
    color_attachment->setRgbBlendOperation(MTL::BlendOperationAdd);
    color_attachment->setAlphaBlendOperation(MTL::BlendOperationAdd);
    color_attachment->setSourceRGBBlendFactor(MTL::BlendFactorSourceAlpha);
    color_attachment->setSourceAlphaBlendFactor(MTL::BlendFactorSourceAlpha);
    color_attachment->setDestinationRGBBlendFactor(MTL::BlendFactorOneMinusSourceAlpha);
    color_attachment->setDestinationAlphaBlendFactor(MTL::BlendFactorOneMinusSourceAlpha);
}

static void configure_vertex_descriptor(MTL::VertexDescriptor *vertex_descriptor) {
    auto attributes = vertex_descriptor->attributes();

    // attribute 1: position
    auto position_descriptor = attributes->object(0);
    position_descriptor->setFormat(MTL::VertexFormat::VertexFormatFloat2);
    position_descriptor->setBufferIndex(0);
    position_descriptor->setOffset(0);

    // attribute 2: color
    auto color_descriptor = attributes->object(1);
    color_descriptor->setFormat(MTL::VertexFormat::VertexFormatFloat4);
    color_descriptor->setBufferIndex(0);
    color_descriptor->setOffset(2 * sizeof(float));

    auto layoutDescriptor = vertex_descriptor->layouts()->object(0);
    layoutDescriptor->setStride(6 * sizeof(float));
}

static MTL::RenderPipelineState *build_pipeline(const char *filename, const char *vertex, const char *fragment) {
    mtl_graphics_context ctx = graphics_context;

    char *str = read_file(filename);
    if (!str) {
        printf("failed to read the metal shader: %s\n", filename);
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

    auto vertex_func = library->newFunction(NS::String::string(vertex, NS::StringEncoding::ASCIIStringEncoding));
    auto fragment_func = library->newFunction(NS::String::string(fragment, NS::StringEncoding::ASCIIStringEncoding));

    MTL::RenderPipelineDescriptor *pipeline_descriptor = MTL::RenderPipelineDescriptor::alloc()->init();
    pipeline_descriptor->setVertexFunction(vertex_func);
    pipeline_descriptor->setFragmentFunction(fragment_func);

    auto color_attachment = pipeline_descriptor->colorAttachments()->object(0);
    configure_color_attachment(color_attachment);

    MTL::VertexDescriptor *vertex_descriptor = MTL::VertexDescriptor::alloc()->init();
    configure_vertex_descriptor(vertex_descriptor);
    pipeline_descriptor->setVertexDescriptor(vertex_descriptor);

    MTL::RenderPipelineState *render_pipeline_state = ctx.device->newRenderPipelineState(pipeline_descriptor, &error);
    if (!render_pipeline_state) {
        printf("failed to load a metal shader: %s\n", error->localizedDescription()->utf8String());
        return nullptr;
    }

    // free resources
    vertex_descriptor->release();
    pipeline_descriptor->release();
    vertex_func->release();
    fragment_func->release();
    library->release();

    return render_pipeline_state;
}

void renderer_backend_init() {
    context.g_buffer_render_pipeline = build_pipeline(
        "../res/shaders/metal/g_buffer.metal",
        "g_buffer_vertex_shader",
        "g_buffer_fragment_shader"
    );
    context.final_render_pipeline = build_pipeline(
        "../res/shaders/metal/final.metal",
        "final_vertex_shader",
        "final_fragment_shader"
    );

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

void renderer_backend_set_screen_size(int width, int height) {
    graphics_context.mtl_layer->setDrawableSize({static_cast<float>(width), static_cast<float>(height)});
}

void renderer_backend_set_pixel_size(int width, int height) {
    context.g_buffer_width = width;
    context.g_buffer_height = height;
}

void renderer_backend_set_clear_color(vec4 clear_color) {
    vec4_copy(context.clear_color, clear_color);
}

void renderer_backend_begin() {
    context.pool = NS::AutoreleasePool::alloc()->init();

    context.command_buffer = graphics_context.command_queue->commandBuffer();

    auto texture_descriptor = MTL::TextureDescriptor::texture2DDescriptor(
        MTL::PixelFormatRGBA8Unorm,
        context.g_buffer_width,
        context.g_buffer_height,
        false
    );
    context.g_buffer = graphics_context.device->newTexture(texture_descriptor);

    MTL::RenderPassDescriptor *render_pass = MTL::RenderPassDescriptor::alloc()->init();
    MTL::RenderPassColorAttachmentDescriptor *color_attachment = render_pass->colorAttachments()->object(0);
    color_attachment->setTexture(context.g_buffer);
    color_attachment->setLoadAction(MTL::LoadActionClear);
    auto clear_color = context.clear_color;
    color_attachment->setClearColor(MTL::ClearColor(clear_color[0], clear_color[1], clear_color[2], clear_color[3]));
    color_attachment->setStoreAction(MTL::StoreActionStore);

    context.batch_encoder = context.command_buffer->renderCommandEncoder(render_pass);
    context.batch_encoder->setRenderPipelineState(context.g_buffer_render_pipeline);
}

void renderer_backend_submit(vertex_buffer vb, index_buffer ib, uint32_t index_count) {
    MTL::RenderCommandEncoder *encoder = context.batch_encoder;
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

static void renderer_draw_final() {
    auto drawable = graphics_context.mtl_layer->nextDrawable();
    auto command_buffer = graphics_context.command_queue->commandBuffer();

    MTL::RenderPassDescriptor *render_pass = MTL::RenderPassDescriptor::alloc()->init();
    MTL::RenderPassColorAttachmentDescriptor *color_attachment = render_pass->colorAttachments()->object(0);
    color_attachment->setTexture(drawable->texture());
    color_attachment->setLoadAction(MTL::LoadActionClear);
    color_attachment->setClearColor(MTL::ClearColor(1, 1, 1, 1));
    color_attachment->setStoreAction(MTL::StoreActionStore);

    MTL::RenderCommandEncoder *encoder = command_buffer->renderCommandEncoder(render_pass);
    encoder->setRenderPipelineState(context.final_render_pipeline);

    auto sampler_descriptor = MTL::SamplerDescriptor::alloc()->init();
    sampler_descriptor->setMinFilter(MTL::SamplerMinMagFilterNearest);
    sampler_descriptor->setMagFilter(MTL::SamplerMinMagFilterNearest);

    auto sampler_state = graphics_context.device->newSamplerState(sampler_descriptor);
    encoder->setFragmentSamplerState(sampler_state, 0);

    encoder->setFragmentTexture(context.g_buffer, 0);
    encoder->drawPrimitives(MTL::PrimitiveType::PrimitiveTypeTriangle, NS::UInteger(0), 6);
    encoder->endEncoding();

    command_buffer->presentDrawable(drawable);
    command_buffer->commit();
    command_buffer->waitUntilCompleted();
}

void renderer_backend_end() {
    context.batch_encoder->endEncoding();

    context.command_buffer->commit();
    context.command_buffer->waitUntilCompleted();

    renderer_draw_final();

    context.pool->release();
}

void renderer_backend_destroy() {
    context.g_buffer_render_pipeline->release();
}
