// bloom_extract_hlsl.frag - bright-pass (D3D12 sidecar of
// shaders/bloom_extract.frag). u_threshold is a loose uniform in the GLSL and
// rides the b0 root-constant block here, where rhi_cmd_set_uniform_f32 writes.
struct PushConsts { float u_threshold; };
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_threshold 0
Texture2D g_scene : register(t0, space0);
SamplerState g_smp : register(s0, space0);
float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {
    float3 col = g_scene.Sample(g_smp, uv).rgb;
    float brightness = dot(col, float3(0.2126f, 0.7152f, 0.0722f));
    float contrib = max(brightness - g_push.u_threshold, 0.0f) / max(brightness, 0.001f);
    return float4(col * contrib, 1.0f);
}
