// bloom_composite_hlsl.frag - scene + bloom * strength (D3D12 sidecar of
// shaders/bloom_composite.frag). post_process_apply binds through
// rhi_cmd_bind_material_textures, which puts albedo (the scene) on unit 0
// and shadow (the bloom) on unit 1 -- t0 and t1 here, same as the GLSL
// layout(binding = 0/1).
struct PushConsts { float u_bloom_strength; };
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_bloom_strength 0
Texture2D g_scene : register(t0, space0);
SamplerState g_smp : register(s0, space0);
Texture2D g_bloom : register(t1, space0);
SamplerState g_smp1 : register(s1, space0);
float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {
    float3 scene = g_scene.Sample(g_smp, uv).rgb;
    float3 bloom = g_bloom.Sample(g_smp1, uv).rgb;
    return float4(scene + bloom * g_push.u_bloom_strength, 1.0f);
}
