// ui_img_hlsl.vert - vgcanvas image VS (D3D12 sidecar of shaders/ui_img.vert).
// Identical contract to font_hlsl.vert: NDC positions, font_vertex layout.
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
