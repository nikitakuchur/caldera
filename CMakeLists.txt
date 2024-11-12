cmake_minimum_required(VERSION 3.29)
project(c_game LANGUAGES C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

# Define a single option for choosing the rendering API
set(RENDER_API "VULKAN" CACHE STRING "Choose the rendering API (VULKAN, METAL)")
set_property(CACHE RENDER_API PROPERTY STRINGS "VULKAN" "METAL")

# Gather source files
file(GLOB_RECURSE SOURCES "src/*.c")
list(FILTER SOURCES EXCLUDE REGEX "src/graphics/metal/.*")
list(FILTER SOURCES EXCLUDE REGEX "src/graphics/vulkan/.*")

add_subdirectory(deps/glfw)
add_subdirectory(deps/stb_image)

# API-specific sources
if(RENDER_API STREQUAL "VULKAN")
    file(GLOB_RECURSE GRAPHICS_SOURCES "src/graphics/vulkan/*.c")
    find_package(Vulkan REQUIRED)
elseif(RENDER_API STREQUAL "METAL")
    if (NOT APPLE)
        message(FATAL_ERROR "METAL rendering API is only supported on Apple platforms.")
    endif()
    add_subdirectory(deps/metal-cpp)
    file(GLOB_RECURSE GRAPHICS_SOURCES "src/graphics/metal/*.mm" "src/graphics/metal/*.cpp")
else()
    message(FATAL_ERROR "Invalid RENDER_API selected. Choose from VULKAN or METAL.")
endif()

include_directories(c_game PRIVATE src)
add_executable(c_game ${SOURCES} ${GRAPHICS_SOURCES})

# Link libraries based on the API
if(RENDER_API STREQUAL "VULKAN")
    target_link_libraries(c_game PRIVATE glfw stb_image Vulkan::Vulkan)
    target_compile_definitions(c_game PRIVATE USE_VULKAN)
elseif(RENDER_API STREQUAL "METAL")
    target_link_libraries(c_game PRIVATE glfw stb_image metal_cpp)
    target_compile_definitions(c_game PRIVATE USE_METAL)
endif()
