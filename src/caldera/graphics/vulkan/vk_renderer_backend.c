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

void renderer_backend_set_model_mat(const mat4 *model_mat) {
    printf("renderer_backend_set_model_mat not supported\n");
}

void renderer_backend_set_view_mat(const mat4 *view_mat) {
    printf("renderer_backend_set_model_mat not supported\n");
}

void renderer_backend_set_proj_mat(const mat4 *proj_mat) {
    printf("renderer_backend_set_model_mat not supported\n");
}

void renderer_backend_set_screen_size(u32 width, u32 height) {
    printf("renderer_backend_set_screen_size not supported\n");
}

void renderer_backend_set_pixel_size(u32 width, u32 height) {
    printf("renderer_backend_set_screen_size not supported\n");
}

void renderer_backend_set_clear_color(vec4 clear_color) {
    printf("renderer_backend_set_screen_size not supported\n");
}

void renderer_backend_submit(vertex_buffer vb, index_buffer ib, u32 index_count, texture textures[], u32 texture_count) {
    printf("renderer_backend_submit not supported\n");
}
