cmake_minimum_required(VERSION 3.29)
project(tests LANGUAGES C)

set(CMAKE_C_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

link_libraries(caldera)

file(GLOB_RECURSE TEST_SOURCES "*.c")

foreach(TEST_FILE ${TEST_SOURCES})
    # Get filename without extension
    get_filename_component(TEST_NAME ${TEST_FILE} NAME_WE)

    # Define executable and test
    add_executable(${TEST_NAME} ${TEST_FILE})
    add_test(NAME ${TEST_NAME} COMMAND $<TARGET_FILE:${TEST_NAME}>)
endforeach()
