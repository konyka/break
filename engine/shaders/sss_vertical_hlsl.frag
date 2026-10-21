// sss_vertical_hlsl.frag - screen-space subsurface scattering, vertical
// 9-tap pass plus the strength blend over the original colour (D3D12
// hand-authored sidecar of shaders/sss_vertical.frag, the GL variant).
//
// Three textures from sss_apply's second rhi_cmd_bind_material_textures:
// the horizontal result as albedo (unit 0, t0), the depth as shadow (unit 1,
// t1) and the ORIGINAL colour as metallic-roughness (unit 2, t2) -- the GLSL
// layout(binding = 0/1/2). Four floats of push block with the u_sssv_
// prefix, same order as the horizontal pass. Same skip-not-wrap edge
// behaviour and SampleLevel 0 loop as sss_hlsl.frag.
struct PushConsts {
    float u_sssv_strength;  //  0
    float u_sssv_sw;        //  4
    float u_sssv_sh;        //  8
    float u_sssv_max_dist;  // 12
};                          // tail at 16
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_sssv_strength 0
// rhi:uniform u_sssv_sw 4
// rhi:uniform u_sssv_sh 8
// rhi:uniform u_sssv_max_dist 12

Texture2D g_color    : register(t0, space0);
Texture2D g_depth    : register(t1, space0);
Texture2D g_original : register(t2, space0);
SamplerState g_smp0 : register(s0, space0);
SamplerState g_smp1 : register(s1, space0);
SamplerState g_smp2 : register(s2, space0);

static const float3 kernel_weights[9] = {
    float3(0.020f, 0.020f, 0.020f),
    float3(0.050f, 0.040f, 0.030f),
    float3(0.100f, 0.070f, 0.050f),
    float3(0.150f, 0.130f, 0.080f),
    float3(0.160f, 0.160f, 0.120f),
    float3(0.150f, 0.130f, 0.080f),
    float3(0.100f, 0.070f, 0.050f),
    float3(0.050f, 0.040f, 0.030f),
    float3(0.020f, 0.020f, 0.020f)
};

float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    float2 texel = 1.0f / float2(g_push.u_sssv_sw, g_push.u_sssv_sh);

    float depth = g_depth.Sample(g_smp1, uv).r;
    float3 center = g_original.Sample(g_smp2, uv).rgb;

    if (depth >= 1.0f)
        return float4(center, 1.0f);

    float radius = g_push.u_sssv_strength * 12.0f;

    float3 sss = (float3)0.0f;
    float3 total_w = (float3)0.0f;

    for (int i = -4; i <= 4; i++) {
        float2 offset = float2(0.0f, (float)i * texel.y * radius);
        float2 sample_uv = uv + offset;

        if (sample_uv.y < 0.0f || sample_uv.y > 1.0f) continue;

        float sd = g_depth.SampleLevel(g_smp1, sample_uv, 0.0f).r;
        float depth_diff = abs(sd - depth);
        float falloff = 1.0f - smoothstep(0.0f, g_push.u_sssv_max_dist, depth_diff);

        float3 w = kernel_weights[i + 4] * falloff;
        float3 sc = g_color.SampleLevel(g_smp0, sample_uv, 0.0f).rgb;
        sss += sc * w;
        total_w += w;
    }

    sss /= max(total_w, (float3)0.001f);

    float3 result = lerp(center, sss, g_push.u_sssv_strength);
    return float4(max(result, (float3)0.0f), 1.0f);
}
