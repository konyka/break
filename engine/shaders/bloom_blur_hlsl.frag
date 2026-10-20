// bloom_blur_hlsl.frag - separable 9-tap gaussian (D3D12 sidecar of
// shaders/bloom_blur.frag). textureSize(u_texture, 0) is GetDimensions here.
struct PushConsts { float2 u_direction; };
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_direction 0
Texture2D g_texture : register(t0, space0);
SamplerState g_smp : register(s0, space0);
float3 tap(float2 uv) { return g_texture.Sample(g_smp, uv).rgb; }
float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {
    uint w, h;
    g_texture.GetDimensions(w, h);
    float2 step = g_push.u_direction / float2((float)w, (float)h);
    float3 result = tap(uv - 4.0f * step) * 0.0162f;
    result += tap(uv - 3.0f * step) * 0.0540f;
    result += tap(uv - 2.0f * step) * 0.1218f;
    result += tap(uv - 1.0f * step) * 0.1960f;
    result += tap(uv) * 0.2240f;
    result += tap(uv + 1.0f * step) * 0.1960f;
    result += tap(uv + 2.0f * step) * 0.1218f;
    result += tap(uv + 3.0f * step) * 0.0540f;
    result += tap(uv + 4.0f * step) * 0.0162f;
    return float4(result, 1.0f);
}
