#include <metal_stdlib>

using namespace metal;

struct vertex_input {
    packed_float2 position;
    packed_float3 color;
};

struct vertex_output {
    float4 position [[position]];
    half3 color;
};

vertex vertex_output vertex_shader(uint vertex_id [[vertex_id]], device const vertex_input* vertices [[buffer(0)]]) {
    vertex_output output;

    output.position = float4(vertices[vertex_id].position, 0.0, 1.0);
    output.color = half3(vertices[vertex_id].color);
    
    return output;
}

fragment half4 fragment_shader(vertex_output frag [[stage_in]]) {
    return half4(frag.color, 1.0);
}
