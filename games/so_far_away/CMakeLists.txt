cmake_minimum_required(VERSION 3.29)
project(so_far_away LANGUAGES C)

set(CMAKE_C_STANDARD 23)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

file(GLOB_RECURSE SOURCES "src/*.c")
add_executable(so_far_away ${SOURCES})

# Link against the caldera library
target_link_libraries(so_far_away PRIVATE caldera)
