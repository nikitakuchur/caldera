# Library definition
add_library(metal-cpp ${CMAKE_CURRENT_SOURCE_DIR}/definition.cpp)

# Metal cpp headers
target_include_directories(metal-cpp PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/metal-cpp"
        "${CMAKE_CURRENT_SOURCE_DIR}/metal-cpp-extensions"
)

# Metal cpp library (linker)
target_link_libraries(metal-cpp
        "-framework Metal"
        "-framework MetalKit"
        "-framework AppKit"
        "-framework Foundation"
        "-framework QuartzCore"
)
