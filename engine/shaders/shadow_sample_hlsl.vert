// shadow_sample_hlsl.vert — VS for the shadow-atlas sampling test. Oversized
// triangle covering the whole target, UVs in 0..1 so the sampling PS can read
// every texel of the atlas exactly once.
struct PushConsts { float4x4 u_transform; };
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_transform 0
struct VSOut { float4 pos : SV_Position; float2 uv : TEXCOORD0; };
VSOut main(uint vid : SV_VertexID) {
    float2 p = float2((float)(vid & 1u) * 4.0 - 1.0,
                      (float)(vid >> 1u) * 4.0 - 1.0);
    VSOut o;
    o.pos = mul(g_push.u_transform, float4(p, 0.0, 1.0));
    o.uv = p * 0.5 + 0.5;
    return o;
}
