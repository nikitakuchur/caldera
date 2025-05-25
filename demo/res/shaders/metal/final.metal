#include <metal_stdlib>

using namespace metal;

struct vertex_output {
    float4 position [[position]];
    float2 uv;
};

vertex vertex_output final_vertex_shader(uint vertex_id [[ vertex_id ]]) {
    float2 pos[] = { {-1.0, -1.0}, {1.0, -1.0}, {-1.0, 1.0}, {-1.0, 1.0}, {1.0, 1.0}, {1.0, -1.0} };

    vertex_output output;
    output.position = float4(pos[vertex_id], 0.0, 1.0);
    output.uv = float2(pos[vertex_id].x * 0.5 + 0.5, 1.0 - (pos[vertex_id].y * 0.5 + 0.5));
    return output;
}

fragment float4 final_fragment_shader(vertex_output input [[ stage_in ]],
                                      texture2d<float> texture [[ texture(0) ]],
                                      sampler nearest_sampler [[ sampler(0) ]]) {
    return texture.sample(nearest_sampler, input.uv);
}
