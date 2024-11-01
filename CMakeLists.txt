cmake_minimum_required(VERSION 3.29)
project(c_game LANGUAGES C CXX)

set(CMAKE_C_STANDARD 23)
set(CMAKE_CXX_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

file(GLOB_RECURSE SOURCES "src/*.c" "src/*.cpp")

add_executable(c_game ${SOURCES})

find_package(Vulkan REQUIRED)

add_subdirectory(deps/glfw)
add_subdirectory(deps/metal)

target_link_libraries(c_game glfw Vulkan::Vulkan metal-cpp)

include_directories(c_game PRIVATE src)
