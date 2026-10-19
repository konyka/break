// post_hlsl.vert - fullscreen-triangle VS shared by every post-process pass
// (D3D12 hand-authored sidecar of shaders/post.vert).
//
// 21 subsystems in src/renderer/ request shaders/post.vert, so this one file
// is the common prerequisite for the whole post-processing family; the GLSL
// twin carries no uniforms at all, which is why it ports with no budget
// question attached.
//
// The GLSL picks its vertex-index builtin per backend -- gl_VertexID on
// desktop GL, gl_VertexIndex under glslang's VULKAN define -- because neither
// spelling exists on both. HLSL has one name for the system value, and like
// the skybox sidecar it is a SYSTEM-VALUE semantic that consumes no vertex
// slot, so the input layout stays at rhi_d3d12_input_layout's no_vertex_input
// arm with zero elements and zero stride. That is exactly what every caller's
// RHIPipelineDesc.no_vertex_input = true selects.
//
// The triangle is (-1,-1) (3,-1) (-1,3), not two triangles sharing an edge:
// at these coordinates the shared edge lands on a pixel boundary and the seam
// can crack. UV is p*0.5+0.5, same as the GLSL, so vUV runs 0..2 over the
// visible 0..1 and the sampler's address mode is what clamps the overhang.
struct VSOut {
    float4 pos : SV_Position;
    float2 uv  : TEXCOORD0;
};
static const float2 POST_POS[3] = {
    float2(-1.0f, -1.0f),
    float2( 3.0f, -1.0f),
    float2(-1.0f,  3.0f)
};
VSOut main(uint vid : SV_VertexID) {
    VSOut o;
    float2 p = POST_POS[vid];
    o.pos = float4(p, 1.0f, 1.0f);
    o.uv = p * 0.5f + 0.5f;
    return o;
}
