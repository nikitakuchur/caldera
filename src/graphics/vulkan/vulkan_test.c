#include "vulkan_test.h"

#include <vulkan/vulkan.h>
#include <stdio.h>

void vk_init() {
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
