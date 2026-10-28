// deferred_light_hlsl.vert - deferred lighting pass, vertex stage
// (D3D12 hand-authored sidecar of shaders/deferred_light.vert).
//
// The usual fullscreen triangle with uv = ndc * 0.5 + 0.5, identical to
// post_hlsl.vert, so uv (0,0) is NDC (-1,-1): memory row 0 of an offscreen
// target under the backend's offscreen viewport, which is also where the
// G-Buffer pass put NDC y = -1. No push block: the fragment stage owns b0.
struct VSOut {
    float4 pos : SV_Position;
    float2 uv  : TEXCOORD0;
};
static const float2 DL_POS[3] = {
    float2(-1.0f, -1.0f),
    float2( 3.0f, -1.0f),
    float2(-1.0f,  3.0f)
};
VSOut main(uint vid : SV_VertexID) {
    VSOut o;
    float2 p = DL_POS[vid];
    o.pos = float4(p, 0.0f, 1.0f);
    o.uv = p * 0.5f + 0.5f;
    return o;
}
