#include "mtl_graphics_context.hpp"

#include <Metal/MTLDevice.hpp>

#include "cocoa_adapter.hpp"

extern "C" {
#include <graphics/api/graphics_context.h>

#include <window/window.h>
#include <utils/utils.h>
}

mtl_graphics_context metal_graphics_context = {};

static MTL::RenderPipelineState* build_pipeline(const char *shader_filename) {
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
    MTL::Library* library = ctx.device->newLibrary(shader, options, &error);
    if (!library) {
        printf("failed to read a metal shader: %s\n", error->localizedDescription()->utf8String());
        return nullptr;
    }

    NS::String* vertex_shader_name = NS::String::string("vertex_shader", NS::StringEncoding::ASCIIStringEncoding);
    MTL::Function* vertex_func = library->newFunction(vertex_shader_name);

    NS::String* fragment_shader_name = NS::String::string("fragment_shader", NS::StringEncoding::ASCIIStringEncoding);
    MTL::Function* fragment_func = library->newFunction(fragment_shader_name);

    MTL::RenderPipelineDescriptor* descriptor = MTL::RenderPipelineDescriptor::alloc()->init();
    descriptor->setVertexFunction(vertex_func);
    descriptor->setFragmentFunction(fragment_func);
    descriptor->colorAttachments()->object(0)->setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm_sRGB);

    MTL::RenderPipelineState* render_pipeline_state = ctx.device->newRenderPipelineState(descriptor, &error);
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

void graphics_context_init(const char *shader_filename) {
    metal_graphics_context.device = MTL::CreateSystemDefaultDevice();

    metal_graphics_context.mtl_layer = CA::MetalLayer::layer()->retain();
    metal_graphics_context.mtl_layer->setDevice(metal_graphics_context.device);
    metal_graphics_context.mtl_layer->setPixelFormat(MTL::PixelFormat::PixelFormatBGRA8Unorm);

    // get the cocoa window using GLFW native
    metal_graphics_context.ns_window = get_and_configure_ns_window(
        window_get_glfw_window(),
        metal_graphics_context.mtl_layer
    )->retain();

    metal_graphics_context.command_queue = metal_graphics_context.device->newCommandQueue()->retain();

    metal_graphics_context.render_pipeline_state = build_pipeline(shader_filename);
}

void graphics_context_destroy() {
    metal_graphics_context.render_pipeline_state->release();
    metal_graphics_context.command_queue->release();
    metal_graphics_context.mtl_layer->release();
    metal_graphics_context.ns_window->release();
    metal_graphics_context.device->release();
}
