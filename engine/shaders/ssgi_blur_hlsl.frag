// ssgi_blur_hlsl.frag - 9-tap Gaussian on the half-res GI buffer, added over
// the scene (D3D12 hand-authored sidecar of shaders/ssgi_blur.frag).
//
// Two textures: t0 the GI buffer, t1 the scene (R550-A, matching
// ssgi_blur_vk.frag and the GL bind_textures_multi order). One vec2 of push
// block, the smallest in the post family.
//
// textureSize(s, 0) is GetDimensions in HLSL; the taps land on exact texel
// centres (integer multiples of the texel step), so the result does not depend
// on whether the sampler filters, and a constant GI buffer passes through the
// whole 9-tap sum unchanged -- the weights add to exactly 1.
struct PushConsts {
    float2 u_direction;   //  0
};                        // tail at 8
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_direction 0

Texture2D g_gi    : register(t0, space0);
Texture2D g_scene : register(t1, space0);
SamplerState g_smp0 : register(s0, space0);
SamplerState g_smp1 : register(s1, space0);

float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    uint tw, th, levels;
    float2 texel;
    g_gi.GetDimensions(0u, tw, th, levels);
    texel = 1.0f / float2(tw, th);

    float3 result = (float3)0.0f;
    result += g_gi.Sample(g_smp0, uv - 4.0f * texel * g_push.u_direction).rgb * 0.0162f;
    result += g_gi.Sample(g_smp0, uv - 3.0f * texel * g_push.u_direction).rgb * 0.0540f;
    result += g_gi.Sample(g_smp0, uv - 2.0f * texel * g_push.u_direction).rgb * 0.1218f;
    result += g_gi.Sample(g_smp0, uv - 1.0f * texel * g_push.u_direction).rgb * 0.1960f;
    result += g_gi.Sample(g_smp0, uv).rgb * 0.2240f;
    result += g_gi.Sample(g_smp0, uv + 1.0f * texel * g_push.u_direction).rgb * 0.1960f;
    result += g_gi.Sample(g_smp0, uv + 2.0f * texel * g_push.u_direction).rgb * 0.1218f;
    result += g_gi.Sample(g_smp0, uv + 3.0f * texel * g_push.u_direction).rgb * 0.0540f;
    result += g_gi.Sample(g_smp0, uv + 4.0f * texel * g_push.u_direction).rgb * 0.0162f;

    float3 scene = g_scene.Sample(g_smp1, uv).rgb;
    return float4(scene + result, 1.0f);
}
