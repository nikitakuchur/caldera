#ifndef MTL_CONTEXT_HPP
#define MTL_CONTEXT_HPP

// platform specific API

#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>
#include <QuartzCore/CAMetalLayer.hpp>

struct mtl_graphics_context {
    MTL::Device *device;
    CA::MetalLayer *mtl_layer;
    NS::Window *ns_window;
    MTL::CommandQueue *command_queue;
};

extern mtl_graphics_context graphics_context;

#endif //MTL_CONTEXT_HPP
