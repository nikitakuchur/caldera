#include "mtl_graphics_context.hpp"

#include <Metal/MTLDevice.hpp>
#include "cocoa_adapter.hpp"

extern "C" {
#include <graphics/api/graphics_context.h>
#include <window/window.h>
}

mtl_graphics_context metal_graphics_context = {};

void graphics_context_init() {
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
}

void graphics_context_destroy() {
    metal_graphics_context.render_pipeline->release();
    metal_graphics_context.command_queue->release();
    metal_graphics_context.mtl_layer->release();
    metal_graphics_context.ns_window->release();
    metal_graphics_context.device->release();
}
