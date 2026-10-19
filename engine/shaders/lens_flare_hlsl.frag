// lens_flare_hlsl.frag - star, streaks, ghost, halo (D3D12 hand-authored
// sidecar of shaders/lens_flare.frag, the GL variant).
//
// Two textures: t0 depth, t1 scene (R550-A, matching lens_flare_vk.frag and
// the GL bind_textures_multi order). No matrices -- eight floats, 32 bytes --
// so this is the smallest push block in the post family.
//
// Unlike the other post passes this is a closed-form function of uv with no
// march, no early-outs and no depth-driven branching beyond one ghost test,
// so the test can derive all 64 expected pixels rather than only pinning the
// wiring. That is why its proof is stronger than ssr's or motion_blur's.
struct PushConsts {
    float u_lf_light_x;  //  0
    float u_lf_light_y;  //  4
    float u_lf_intensity;//  8
    float u_lf_sw;       // 12
    float u_lf_sh;       // 16
    float u_lf_lc_r;     // 20
    float u_lf_lc_g;     // 24
    float u_lf_lc_b;     // 28
};                      // tail at 32
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_lf_light_x 0
// rhi:uniform u_lf_light_y 4
// rhi:uniform u_lf_intensity 8
// rhi:uniform u_lf_sw 12
// rhi:uniform u_lf_sh 16
// rhi:uniform u_lf_lc_r 20
// rhi:uniform u_lf_lc_g 24
// rhi:uniform u_lf_lc_b 28

Texture2D g_depth : register(t0, space0);
Texture2D g_scene : register(t1, space0);
SamplerState g_smp0 : register(s0, space0);
SamplerState g_smp1 : register(s1, space0);

float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    float2 light_pos = float2(g_push.u_lf_light_x, g_push.u_lf_light_y);
    float2 center = uv - light_pos;
    float dist = length(center);
    float2 dir = dist > 0.001f ? center / dist : float2(0.0f, 1.0f);

    float3 flare = (float3)0.0f;
    float3 light_color = float3(g_push.u_lf_lc_r, g_push.u_lf_lc_g,
                                g_push.u_lf_lc_b);

    float star = exp(-dist * 6.0f) * 0.8f;
    float streak_h = exp(-abs(center.y) * 40.0f) * exp(-abs(center.x) * 3.0f) * 0.15f;
    float streak_v = exp(-abs(center.x) * 40.0f) * exp(-abs(center.y) * 3.0f) * 0.15f;
    flare += star * light_color;
    flare += streak_h * light_color;
    flare += streak_v * light_color;

    float2 ghost_uv = light_pos + center * -0.5f;
    float ghost_dist = length(ghost_uv - (float2)0.5f);
    float ghost = exp(-ghost_dist * 4.0f) * 0.3f;
    if (ghost_uv.x > 0.0f && ghost_uv.x < 1.0f &&
        ghost_uv.y > 0.0f && ghost_uv.y < 1.0f) {
        float gd = g_depth.Sample(g_smp0, ghost_uv).r;
        if (gd > 0.99f) {
            flare += ghost * light_color;
        }
    }

    float2 halo_uv = light_pos + dir * 0.3f;
    float halo = exp(-abs(length(halo_uv - (float2)0.5f) - 0.3f) * 20.0f) * 0.2f;
    if (halo_uv.x > 0.0f && halo_uv.x < 1.0f &&
        halo_uv.y > 0.0f && halo_uv.y < 1.0f) {
        flare += halo * light_color;
    }

    flare *= g_push.u_lf_intensity;

    // R550-A: self-composite -- additive light contribution over the incoming
    // frame-chain colour.
    float3 scene = g_scene.Sample(g_smp1, uv).rgb;
    return float4(scene + flare, 1.0f);
}
