#include <metal_stdlib>

using namespace metal;

struct vertex_input {
    packed_float2 position;
    packed_float4 color;
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

vertex vertex_output vertex_shader(uint vertex_id [[vertex_id]],
                                   device const vertex_input* vertices [[buffer(0)]],
                                   constant uniform_input &uniforms [[buffer(1)]]) {
    vertex_output output;

    packed_float2 vert_position = vertices[vertex_id].position;

    // we need this to create an effect of pixel snapping
    vert_position.x = (int) rint(vert_position.x);
    vert_position.y = (int) rint(vert_position.y);

    float4 world_pos = uniforms.model_mat * float4(vert_position, 0.0, 1.0);
    output.position = uniforms.proj_mat * uniforms.view_mat * world_pos;

    output.color = half4(vertices[vertex_id].color);
    
    return output;
}

fragment half4 fragment_shader(vertex_output frag [[stage_in]]) {
    return frag.color;
}
