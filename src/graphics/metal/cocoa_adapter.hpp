#ifndef COCOA_ADAPTER_HPP
#define COCOA_ADAPTER_HPP

#include <GLFW/glfw3.h>

#include <AppKit/AppKit.hpp>
#include <QuartzCore/CAMetalLayer.hpp>

// gets the cocoa window from GLFW and binds the given metal layer to it
NS::Window* get_and_configure_ns_window(GLFWwindow* glfwWindow, CA::MetalLayer* layer);

#endif //COCOA_ADAPTER_HPP
