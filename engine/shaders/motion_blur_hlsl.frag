// motion_blur_hlsl.frag - per-object motion blur, velocity-scaled tap span
// (D3D12 hand-authored sidecar of shaders/motion_blur.frag, the GL variant).
//
// Three textures: t0 colour, t1 depth, t2 velocity (R219-A, matching
// motion_blur_vk.frag and the GL bind_material_textures units). Three tables
// clamp 32BIT_CONSTANTS at 61 DWORDs = 244 bytes; this uses 152, so it fits.
//
// R621 matters for t1: depth is decoded as depth * 2 - 1, which assumes the
// forward pass wrote (ndc_z + 1) / 2. Before R621 the D3D12 forward sidecars
// wrote raw ndc_z, so every reconstructed view position here was wrong.
struct PushConsts {
    float    u_mb_strength;      //   0
    float    u_mb_sw;            //   4
    float    u_mb_sh;            //   8
    float    u_mb_use_velocity;  //  12  (mat4s must stay 16B-aligned)
    float4x4 u_mb_inv_proj;      //  16
    float4x4 u_mb_prev_vp;       //  32
};                              // tail at 96
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_mb_strength 0
// rhi:uniform u_mb_sw 4
// rhi:uniform u_mb_sh 8
// rhi:uniform u_mb_use_velocity 12
// rhi:uniform u_mb_inv_proj 16
// rhi:uniform u_mb_prev_vp 32

Texture2D g_color    : register(t0, space0);
Texture2D g_depth    : register(t1, space0);
Texture2D g_velocity : register(t2, space0);
SamplerState g_smp0 : register(s0, space0);
SamplerState g_smp1 : register(s1, space0);
SamplerState g_smp2 : register(s2, space0);

float interleaved_gradient_noise(float2 p) {
    float3 magic = float3(0.06711056f, 0.00583715f, 52.9829189f);
    return frac(magic.z * frac(dot(p, magic.xy)));
}

float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    float2 res = float2(g_push.u_mb_sw, g_push.u_mb_sh);
    float depth = g_depth.Sample(g_smp1, uv).r;

    if (depth >= 1.0f)
        return g_color.Sample(g_smp0, uv);

    float2 velocity;
    if (g_push.u_mb_use_velocity > 0.5f) {
        // FORWARD_MRT / G-buffer stores the NDC delta; convert once to pixels
        // so object and skinned motion that depth cannot reconstruct survives.
        velocity = g_velocity.Sample(g_smp2, uv).rg * (0.5f * res);
    } else {
        float2 ndc = uv * 2.0f - 1.0f;
        float4 view_pos = mul(g_push.u_mb_inv_proj,
                              float4(ndc, depth * 2.0f - 1.0f, 1.0f));
        view_pos.xyz /= view_pos.w;
        float4 prev_clip = mul(g_push.u_mb_prev_vp, float4(view_pos.xyz, 1.0f));
        float2 prev_ndc = prev_clip.xy / prev_clip.w;
        float2 prev_uv = prev_ndc * 0.5f + 0.5f;
        velocity = (uv - prev_uv) * res;
    }

    float vel_len = length(velocity);
    if (vel_len < 0.5f)
        return g_color.Sample(g_smp0, uv);

    // R550-C: span is max_vel * strength px, clamped to 200. The old step
    // (dir * strength / sample_count) made the total span step*sample_count ==
    // strength (~1px) whatever the speed, i.e. a near no-op.
    float max_vel = min(vel_len, 200.0f);
    float sample_count = min(max_vel * g_push.u_mb_strength, 16.0f);
    float2 dir = velocity / max(vel_len, 0.001f);
    float2 step_size = dir * max_vel * g_push.u_mb_strength /
                       max(sample_count, 1.0f);

    float jitter = interleaved_gradient_noise(pos.xy) - 0.5f;

    float3 result = (float3)0.0f;
    float total_w = 0.0f;

    for (float i = -sample_count * 0.5f; i <= sample_count * 0.5f; i += 1.0f) {
        float w = 1.0f - abs(i) / (sample_count * 0.5f + 1.0f);
        float offset = i + jitter;
        float2 sample_uv = uv + step_size * offset / res;
        result += g_color.Sample(g_smp0,
                                 clamp(sample_uv, (float2)0.0f, (float2)1.0f)).rgb * w;
        total_w += w;
    }

    return float4(result / max(total_w, 0.001f), 1.0f);
}
