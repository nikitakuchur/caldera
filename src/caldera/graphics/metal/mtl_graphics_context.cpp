#include "mtl_graphics_context.hpp"

#include <Metal/MTLDevice.hpp>
#include "cocoa_adapter.hpp"
#include "GLFW/glfw3native.h"

extern "C" {
#include <caldera/graphics/backend/graphics_context.h>
#include <caldera/window/window.h>
}

mtl_graphics_context graphics_context = {};

void graphics_context_init() {
    graphics_context.device = MTL::CreateSystemDefaultDevice();

    graphics_context.mtl_layer = CA::MetalLayer::layer()->retain();
    graphics_context.mtl_layer->setDevice(graphics_context.device);
    graphics_context.mtl_layer->setPixelFormat(MTL::PixelFormat::PixelFormatRGBA8Unorm);

    // get the cocoa window using GLFW native
    graphics_context.ns_window = get_and_configure_ns_window(
        static_cast<GLFWwindow *>(window_get_native_window()),
        graphics_context.mtl_layer
    )->retain();

    graphics_context.command_queue = graphics_context.device->newCommandQueue()->retain();
}

void graphics_context_free() {
    graphics_context.command_queue->release();
    graphics_context.mtl_layer->release();
    graphics_context.ns_window->release();
    graphics_context.device->release();
}
