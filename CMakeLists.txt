cmake_minimum_required(VERSION 3.29)
project(c_game C)

set(CMAKE_C_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

file(GLOB_RECURSE SOURCES "src/*.c")

# Find Vulkan package
find_package(Vulkan REQUIRED)

add_subdirectory(deps/glfw)
add_subdirectory(deps/cglm)

add_executable(c_game ${SOURCES})

target_link_libraries(c_game glfw cglm Vulkan::Vulkan)

include_directories(c_game PRIVATE src)
