#ifndef MTL_CONTEXT_HPP
#define MTL_CONTEXT_HPP

// this block should be available only to C++ code
#ifdef __cplusplus

#include <Metal/Metal.hpp>
#include <AppKit/AppKit.hpp>
#include <QuartzCore/CAMetalLayer.hpp>

struct mtl_context {
    MTL::Device *device;
    CA::MetalLayer *mtl_layer;
    NS::Window *ns_window;
    MTL::CommandQueue *command_queue;
};

extern mtl_context metal_graphics_context;

#endif

// C API
#ifdef __cplusplus
extern "C" {
#endif

void mtl_context_init();

void mtl_context_destroy();

#ifdef __cplusplus
}
#endif

#endif //MTL_CONTEXT_HPP
