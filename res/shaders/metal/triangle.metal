#include <metal_stdlib>

using namespace metal;

constant float4 positions[] = {
    float4(-0.75, -0.75, 0.0, 1.0),
    float4( 0.75, -0.75, 0.0, 1.0),
    float4(  0.0,  0.75, 0.0, 1.0)
};

constant half3 colors[] = {
    half3(1.0, 0.0, 0.0),
    half3(0.0, 1.0, 0.0),
    half3(0.0, 0.0, 1.0)
};

struct vertex_payload {
    float4 position [[position]];
    half3 color;
};

vertex vertex_payload vertex_shader(uint vertex_id [[vertex_id]]) {
    vertex_payload payload;
    
    payload.position = positions[vertex_id];
    payload.color = colors[vertex_id];
    
    return payload;
}

fragment half4 fragment_shader(vertex_payload payload [[stage_in]]) {
    return half4(payload.color, 1.0);
}
