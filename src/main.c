#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <graphics/vulkan/vulkan_test.h>

#include "cpp_module/module.hpp"

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    printf("key: %d\n", key);
}

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    printf("mouse button: %d\n", button);
}

int main() {
    // Just for a test
    cpp_function();

    if (!glfwInit()) {
        return -1;
    }

    if (!glfwVulkanSupported()) {
        return -1;
    }

    vk_init();

    GLFWwindow *window = glfwCreateWindow(640, 480, "Game", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwSetKeyCallback(window, &key_callback);
    glfwSetMouseButtonCallback(window, &mouse_button_callback);
    glfwMakeContextCurrent(window);

    while (!glfwWindowShouldClose(window)) {
        // Render here

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}
