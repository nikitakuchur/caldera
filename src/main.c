#include <vulkan/vulkan.h>
#include <GLFW/glfw3.h>
#include <stdio.h>
#include <cglm/vec2.h>

static void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    printf("key: %d\n", key);
}

static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    printf("mouse button: %d\n", button);
}

void init() {
    VkInstance instance;

    VkInstanceCreateInfo create_info = {};

    create_info.enabledExtensionCount = 1;
    const char *extensionNames[1] = {
        VK_KHR_PORTABILITY_ENUMERATION_EXTENSION_NAME,
    };
    create_info.ppEnabledExtensionNames = extensionNames;

    // macos specific
    create_info.flags = VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;

    const VkResult result = vkCreateInstance(&create_info, nullptr, &instance);

    if (result == VK_SUCCESS) {
        printf("VkInstance created successfully!\n");
    } else {
        printf("Failed to create a VkI¢nstance: %d\n", result);
    }
}

int main() {
    if (!glfwInit()) {
        return -1;
    }

    if (!glfwVulkanSupported()) {
        return -1;
    }

    init();

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
