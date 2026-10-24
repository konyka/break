// luminance_hlsl.frag - log-average scene luminance with temporal adaptation
// (D3D12 sidecar of shaders/luminance.frag). Renders one texel into the 1x1
// RGBA16F target tonemap reads at t1. t0 = HDR scene, t1 = previous adapted
// value, bound by rhi_cmd_bind_material_textures (albedo -> 0, shadow -> 1).
struct PushConsts {
    float u_lum_w;     // 0
    float u_lum_h;     // 4
    float u_lum_speed; // 8
    float u_lum_dt;    // 12
};
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_lum_w 0
// rhi:uniform u_lum_h 4
// rhi:uniform u_lum_speed 8
// rhi:uniform u_lum_dt 12
Texture2D g_hdr : register(t0, space0);
SamplerState g_smp : register(s0, space0);
Texture2D g_prev : register(t1, space0);
SamplerState g_smp1 : register(s1, space0);

float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {
    /* R687: [unroll], not [loop]. One pixel does all 256 taps; a rolled
     * loop issues them one dependent fetch at a time (0.127 ms on RTX vs
     * 0.028 ms for the GL/VK twins, whose compilers unroll). */
    const int N = 16;
    float luma_sum = 0.0f;
    [unroll] for (int y = 0; y < N; y++) {
        [unroll] for (int x = 0; x < N; x++) {
            float2 suv = (float2((float)x, (float)y) + 0.5f) / (float)N;
            float3 c = g_hdr.SampleLevel(g_smp, suv, 0.0f).rgb;
            luma_sum += log(max(dot(c, float3(0.2126f, 0.7152f, 0.0722f)), 0.001f));
        }
    }
    float current_luma = exp(luma_sum / (float)(N * N));
    float prev_luma = g_prev.Sample(g_smp1, float2(0.5f, 0.5f)).r;
    if (prev_luma < 0.001f) prev_luma = current_luma;
    float adapted = lerp(prev_luma, current_luma, 1.0f - exp(-g_push.u_lum_speed * g_push.u_lum_dt));
    adapted = clamp(adapted, 0.01f, 10.0f);
    return float4(adapted, 0.0f, 0.0f, 1.0f);
}
