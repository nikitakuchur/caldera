cmake_minimum_required(VERSION 3.29)
project(stb)

add_library(stb STATIC src/stb.c)
target_include_directories(stb PUBLIC include/)
