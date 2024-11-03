#include "vk_graphics_context.h"
#include <graphics/api/graphics_context.h>

#include <vulkan/vulkan.h>
#include <stdio.h>

void graphics_context_init(const char *shader_filename) {
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
        printf("vulkan instance created successfully!\n");
    } else {
        printf("failed to create a new vulkan instance: %d\n", result);
    }
}

void graphics_context_destroy() {
    printf("graphics_context_destroy not supported");
}