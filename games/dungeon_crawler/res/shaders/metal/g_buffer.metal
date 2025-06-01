#include <metal_stdlib>

using namespace metal;

struct vertex_input {
    float2 position [[attribute(0)]];
    float4 color [[attribute(1)]];
    float2 tex_coords [[attribute(2)]];
    int tex_index [[attribute(3)]];
};

struct vertex_output {
    float4 position [[position]];
    float4 color;
    float2 tex_coords;
    int tex_index;
};

struct uniform_input {
    float4x4 model_mat;
    float4x4 view_mat;
    float4x4 proj_mat;
};

vertex vertex_output g_buffer_vertex_shader(vertex_input input [[stage_in]],
                                            constant uniform_input &uniforms [[buffer(1)]]) {
    vertex_output output;

    float4 world_pos = uniforms.model_mat * float4(input.position, 0.0, 1.0);
    output.position = uniforms.proj_mat * uniforms.view_mat * world_pos;

    output.color = input.color;
    output.tex_coords = input.tex_coords;
    output.tex_index = input.tex_index;
    
    return output;
}

fragment float4 g_buffer_fragment_shader(vertex_output frag [[stage_in]],
                                         array<texture2d<float>, 10> textures [[ texture(0) ]]) {
    if (frag.tex_index < 0) {
        return frag.color;
    }
    return textures[frag.tex_index].read(uint2(frag.tex_coords)) * frag.color;
}
