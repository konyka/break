// myui_hlsl.vert — myui passthrough VS (D3D12 hand-authored sidecar).
// Input layout matches RHIPipelineDesc.font_vertex (32B stride: pos2, uv2,
// color4). b0 is the reserved 32BIT_CONSTANTS root-constant register.
struct PushConsts { float4x4 u_transform; };
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_transform 0
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
    o.pos = mul(g_push.u_transform, float4(i.pos, 0.0, 1.0));
    o.uv = i.uv;
    o.color = i.color;
    return o;
}
