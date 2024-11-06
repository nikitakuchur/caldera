#include <graphics/api/renderer.h>

#include <stdio.h>

void renderer_init() {
    printf("renderer_init not supported");
}

void renderer_begin() {
    printf("renderer_begin not supported");
}

void renderer_submit(vertex_buffer vb, uint32_t vertex_count, index_buffer io) {
    printf("renderer_submit_triangle not supported");
}

void renderer_end() {
    printf("renderer_end not supported");
}

void renderer_destroy() {
    printf("renderer_destroy not supported");
}
