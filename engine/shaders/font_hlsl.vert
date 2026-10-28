// font_hlsl.vert - vgcanvas glyph/rect VS (D3D12 sidecar of shaders/font.vert).
// Positions arrive already in NDC; the input layout is RHIPipelineDesc.
// font_vertex (32B stride: pos2, uv2, color4), the same one myui_hlsl.vert
// consumes. No root constants: the GLSL twin has no uniforms.
struct VSIn {
    float2 pos : POSITION;
    float2 uv : TEXCOORD0;
    float4 color : COLOR0;
};
struct VSOut {
    float4 pos : SV_Position;
    float2 uv : TEXCOORD0;
    float4 color : COLOR0;
};
VSOut main(VSIn i) {
    VSOut o;
    o.pos = float4(i.pos, 0.0f, 1.0f);
    o.uv = i.uv;
    o.color = i.color;
    return o;
}
