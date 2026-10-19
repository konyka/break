// taa_hlsl.frag - temporal anti-aliasing, neighbourhood AABB clamp
// (D3D12 hand-authored sidecar of shaders/taa.frag, the GL variant).
//
// Four textures, which is the largest bind rhi_cmd_bind_textures_multi takes
// -- and the reason SSR's R620 binder change mattered here too. They map to
// t0..t3 because taa_apply binds {curr, hist, depth, velocity} in that order
// (R218-A, matching taa_vk.frag).
//
// 212 bytes of push block: three matrices and five floats. Four descriptor
// tables clamp 32BIT_CONSTANTS at 60 DWORDs = 248 bytes, so it fits.
struct PushConsts {
    float4x4 u_taa_curr_vp;       //   0
    float4x4 u_taa_prev_vp;       //  64
    float4x4 u_taa_inv_proj;      // 128
    float    u_taa_sw;            // 192
    float    u_taa_sh;            // 196
    float    u_taa_first_frame;   // 200
    float    u_taa_use_velocity;  // 204
};                                // tail at 208
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_taa_curr_vp 0
// rhi:uniform u_taa_prev_vp 64
// rhi:uniform u_taa_inv_proj 128
// rhi:uniform u_taa_sw 192
// rhi:uniform u_taa_sh 196
// rhi:uniform u_taa_first_frame 200
// rhi:uniform u_taa_use_velocity 204

static const float u_taa_blend = 0.1f;   /* GLSL const in the twin */

Texture2D g_curr     : register(t0, space0);
Texture2D g_hist     : register(t1, space0);
Texture2D g_depth    : register(t2, space0);
Texture2D g_velocity : register(t3, space0);
SamplerState g_smp0 : register(s0, space0);
SamplerState g_smp1 : register(s1, space0);
SamplerState g_smp2 : register(s2, space0);
SamplerState g_smp3 : register(s3, space0);

float3 clip_aabb(float3 aabb_min, float3 aabb_max, float3 p) {
    float3 center = (aabb_min + aabb_max) * 0.5f;
    float3 extent = (aabb_max - aabb_min) * 0.5f;
    float3 dir = p - center;
    float3 scaled = abs(dir) / max(extent, (float3)1e-5f);
    float max_s = max(scaled.x, max(scaled.y, scaled.z));
    if (max_s > 1.0f)
        return center + dir / max_s;
    return p;
}

float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    float2 texel_size = float2(1.0f / g_push.u_taa_sw, 1.0f / g_push.u_taa_sh);

    float depth = g_depth.Sample(g_smp2, uv).r;
    float3 curr_color = g_curr.Sample(g_smp0, uv).rgb;

    float3 neighbor[8];
    neighbor[0] = g_curr.Sample(g_smp0, uv + float2(-1.0f, -1.0f) * texel_size).rgb;
    neighbor[1] = g_curr.Sample(g_smp0, uv + float2( 0.0f, -1.0f) * texel_size).rgb;
    neighbor[2] = g_curr.Sample(g_smp0, uv + float2( 1.0f, -1.0f) * texel_size).rgb;
    neighbor[3] = g_curr.Sample(g_smp0, uv + float2(-1.0f,  0.0f) * texel_size).rgb;
    neighbor[4] = g_curr.Sample(g_smp0, uv + float2( 1.0f,  0.0f) * texel_size).rgb;
    neighbor[5] = g_curr.Sample(g_smp0, uv + float2(-1.0f,  1.0f) * texel_size).rgb;
    neighbor[6] = g_curr.Sample(g_smp0, uv + float2( 0.0f,  1.0f) * texel_size).rgb;
    neighbor[7] = g_curr.Sample(g_smp0, uv + float2( 1.0f,  1.0f) * texel_size).rgb;

    float3 n_min = curr_color;
    float3 n_max = curr_color;
    for (int i = 0; i < 8; i++) {
        n_min = min(n_min, neighbor[i]);
        n_max = max(n_max, neighbor[i]);
    }

    if (depth < 1.0f && g_push.u_taa_first_frame < 0.5f) {
        float2 prev_uv;
        if (g_push.u_taa_use_velocity > 0.5f) {
            float2 vel = g_velocity.Sample(g_smp3, uv).rg;
            prev_uv = uv - vel * 0.5f;
        } else {
            float2 ndc = uv * 2.0f - 1.0f;
            float4 clip_pos = float4(ndc.x, ndc.y, depth * 2.0f - 1.0f, 1.0f);
            float4 world_pos_h = mul(g_push.u_taa_inv_proj, clip_pos);
            float3 world_pos = world_pos_h.xyz / world_pos_h.w;
            float4 prev_clip = mul(g_push.u_taa_prev_vp, float4(world_pos, 1.0f));
            prev_uv = (prev_clip.xy / prev_clip.w) * 0.5f + 0.5f;
        }

        if (prev_uv.x >= 0.0f && prev_uv.x <= 1.0f &&
            prev_uv.y >= 0.0f && prev_uv.y <= 1.0f) {
            float3 hist_color = g_hist.Sample(g_smp1, prev_uv).rgb;
            hist_color = clip_aabb(n_min, n_max, hist_color);
            curr_color = lerp(hist_color, curr_color, u_taa_blend);
        }
    }

    return float4(curr_color, 1.0f);
}
