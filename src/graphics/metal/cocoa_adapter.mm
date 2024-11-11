#import "cocoa_adapter.hpp"

#import <QuartzCore/CAMetalLayer.h>

#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

NS::Window* get_and_configure_ns_window(GLFWwindow* glfwWindow, CA::MetalLayer* layer) {
    CAMetalLayer* ca_metal_layer = (__bridge CAMetalLayer*) layer;
    NSWindow* ns_window = glfwGetCocoaWindow(glfwWindow);

    ca_metal_layer.displaySyncEnabled = false;
    
    ns_window.contentView.layer = ca_metal_layer;
    ns_window.contentView.wantsLayer = YES;

    return (__bridge NS::Window*)ns_window;
}
