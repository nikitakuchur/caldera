#pragma once

#include <GLFW/glfw3.h>

#include <AppKit/AppKit.hpp>
#include <QuartzCore/CAMetalLayer.hpp>

// binds the metal layer to the cocoa window and returns it
NS::Window* get_ns_window(GLFWwindow* glfwWindow, CA::MetalLayer* layer);
