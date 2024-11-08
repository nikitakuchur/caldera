#include <metal_stdlib>

using namespace metal;

struct vertex_input {
    float2 position [[attribute(0)]];
    float4 color [[attribute(1)]];
};

struct vertex_output {
    float4 position [[position]];
    half4 color;
};

struct uniform_input {
    float4x4 model_mat;
    float4x4 view_mat;
    float4x4 proj_mat;
};

vertex vertex_output vertex_shader(vertex_input input [[stage_in]],
                                   constant uniform_input &uniforms [[buffer(1)]]) {
    vertex_output output;

    float2 vert_position = input.position;

    // we need this to create an effect of pixel snapping
    vert_position.x = (int) rint(vert_position.x);
    vert_position.y = (int) rint(vert_position.y);

    float4 world_pos = uniforms.model_mat * float4(vert_position, 0.0, 1.0);
    output.position = uniforms.proj_mat * uniforms.view_mat * world_pos;

    output.color = half4(input.color);
    
    return output;
}

fragment half4 fragment_shader(vertex_output frag [[stage_in]]) {
    return frag.color;
}
