#include <caldera/graphics/backend/renderer_backend.h>

#include <stdio.h>

void renderer_backend_init() {
    printf("renderer_backend_init not supported\n");
}

void renderer_backend_free() {
    printf("renderer_backend_free not supported\n");
}

void renderer_backend_begin() {
    printf("renderer_backend_begin not supported\n");
}

void renderer_backend_end() {
    printf("renderer_backend_end not supported\n");
}

void renderer_backend_set_model_mat(mat4 model_mat) {
    printf("renderer_backend_set_model_mat not supported\n");
}

void renderer_backend_set_view_mat(mat4 view_mat) {
    printf("renderer_backend_set_model_mat not supported\n");
}

void renderer_backend_set_proj_mat(mat4 proj_mat) {
    printf("renderer_backend_set_model_mat not supported\n");
}

void renderer_backend_set_screen_size(int width, int height) {
    printf("renderer_backend_set_screen_size not supported\n");
}

void renderer_backend_set_pixel_size(int width, int height) {
    printf("renderer_backend_set_screen_size not supported\n");
}

void renderer_backend_set_clear_color(vec4 clear_color) {
    printf("renderer_backend_set_screen_size not supported\n");
}

void renderer_backend_submit(vertex_buffer vb, index_buffer ib, uint32_t index_count, texture textures[],
                             uint32_t texture_count) {
    printf("renderer_backend_submit not supported\n");
}
