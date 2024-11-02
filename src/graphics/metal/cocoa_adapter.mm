#import "cocoa_adapter.hpp"

#define GLFW_EXPOSE_NATIVE_COCOA
#include <GLFW/glfw3native.h>

NS::Window* get_and_configure_ns_window(GLFWwindow* glfwWindow, CA::MetalLayer* layer) {
    CALayer* ca_layer = (__bridge CALayer*) layer;
    NSWindow* ns_window = glfwGetCocoaWindow(glfwWindow);

    ns_window.contentView.layer = ca_layer;
    ns_window.contentView.wantsLayer = YES;

    return (__bridge NS::Window*)ns_window;
}
