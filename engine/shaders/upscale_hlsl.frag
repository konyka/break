// upscale_hlsl.frag - temporal upscale: Catmull-Rom reconstruction, optional
// cross sharpen, reprojected history clipped to the neighbourhood AABB
// (D3D12 hand-authored sidecar of shaders/upscale.frag, the GL variant).
//
// Three textures from upscale_apply's rhi_cmd_bind_material_textures: the
// render-res source as albedo (unit 0, t0), the depth as shadow (unit 1,
// t1) and the display-res history as metallic-roughness (unit 2, t2) -- the
// GLSL layout(binding = 0/1/2), R221-A.
//
// Push block 148 bytes: the two matrices first, then the five floats the
// shader reads. u_ups_dw / u_ups_dh are declared by the GLSL twin but never
// read, so GL's linker drops them and upscale_init resolves -1; no member
// and no marker here, for the same result.
//
// The neighbour taps and the history read sit behind a data-dependent
// branch, so they use SampleLevel 0 (single-mip targets, the LOD texture()
// selects on GL). Matrices come in whole and column-major: GLSL M * v is
// mul(M, v).
struct PushConsts {
    float4x4 u_ups_inv_proj;     //   0
    float4x4 u_ups_prev_vp;      //  64
    float    u_ups_rw;           // 128
    float    u_ups_rh;           // 132
    float    u_ups_sharp;        // 136
    float    u_ups_copy_only;    // 140
    float    u_ups_first_frame;  // 144
};                               // tail at 148
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_ups_inv_proj 0
// rhi:uniform u_ups_prev_vp 64
// rhi:uniform u_ups_rw 128
// rhi:uniform u_ups_rh 132
// rhi:uniform u_ups_sharp 136
// rhi:uniform u_ups_copy_only 140
// rhi:uniform u_ups_first_frame 144

Texture2D g_src     : register(t0, space0);
Texture2D g_depth   : register(t1, space0);
Texture2D g_history : register(t2, space0);
SamplerState g_smp0 : register(s0, space0);
SamplerState g_smp1 : register(s1, space0);
SamplerState g_smp2 : register(s2, space0);

/* R686: 9 bilinear taps instead of 16 point taps; see upscale.frag. The
 * outer taps sit on texel centres, the folded inner tap needs the linear
 * filter, so all of them use SampleLevel 0 (single-mip source). */
float3 sample_catmull(float2 uv, float2 texel) {
    float2 pos = uv / texel;
    float2 t1 = floor(pos - 0.5f) + 0.5f;
    float2 f = pos - t1;

    float2 w0 = f * (-0.5f + f * (1.0f - 0.5f * f));
    float2 w1 = 1.0f + f * f * (-2.5f + 1.5f * f);
    float2 w2 = f * (0.5f + f * (2.0f - 1.5f * f));
    float2 w3 = f * f * (-0.5f + 0.5f * f);

    float2 w12 = w1 + w2;
    float2 uv0  = (t1 - 1.0f) * texel;
    float2 uv12 = (t1 + w2 / w12) * texel;
    float2 uv3  = (t1 + 2.0f) * texel;

    float3 result = (float3)0.0f;
    result += g_src.SampleLevel(g_smp0, float2(uv0.x,  uv0.y), 0.0f).rgb  * (w0.x  * w0.y);
    result += g_src.SampleLevel(g_smp0, float2(uv12.x, uv0.y), 0.0f).rgb  * (w12.x * w0.y);
    result += g_src.SampleLevel(g_smp0, float2(uv3.x,  uv0.y), 0.0f).rgb  * (w3.x  * w0.y);
    result += g_src.SampleLevel(g_smp0, float2(uv0.x,  uv12.y), 0.0f).rgb * (w0.x  * w12.y);
    result += g_src.SampleLevel(g_smp0, float2(uv12.x, uv12.y), 0.0f).rgb * (w12.x * w12.y);
    result += g_src.SampleLevel(g_smp0, float2(uv3.x,  uv12.y), 0.0f).rgb * (w3.x  * w12.y);
    result += g_src.SampleLevel(g_smp0, float2(uv0.x,  uv3.y), 0.0f).rgb  * (w0.x  * w3.y);
    result += g_src.SampleLevel(g_smp0, float2(uv12.x, uv3.y), 0.0f).rgb  * (w12.x * w3.y);
    result += g_src.SampleLevel(g_smp0, float2(uv3.x,  uv3.y), 0.0f).rgb  * (w3.x  * w3.y);
    return result;
}

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
    float2 render_uv = uv;

    if (g_push.u_ups_copy_only > 0.5f)
        return float4(saturate(g_src.Sample(g_smp0, render_uv).rgb), 1.0f);

    float2 render_texel = 1.0f / float2(g_push.u_ups_rw, g_push.u_ups_rh);
    float3 upscaled = sample_catmull(render_uv, render_texel);

    /* R686: the sharpen cross and the history clip AABB share four taps. */
    float depth = g_depth.Sample(g_smp1, render_uv).r;
    bool use_history = depth < 1.0f && g_push.u_ups_first_frame < 0.5f;
    float3 nw = (float3)0.0f, ne = (float3)0.0f, nn = (float3)0.0f, ns = (float3)0.0f;
    if (g_push.u_ups_sharp > 0.0f || use_history) {
        nw = g_src.SampleLevel(g_smp0, render_uv + float2(-render_texel.x, 0.0f), 0.0f).rgb;
        ne = g_src.SampleLevel(g_smp0, render_uv + float2( render_texel.x, 0.0f), 0.0f).rgb;
        nn = g_src.SampleLevel(g_smp0, render_uv + float2(0.0f, -render_texel.y), 0.0f).rgb;
        ns = g_src.SampleLevel(g_smp0, render_uv + float2(0.0f,  render_texel.y), 0.0f).rgb;
    }

    if (g_push.u_ups_sharp > 0.0f) {
        float3 c = g_src.SampleLevel(g_smp0, render_uv, 0.0f).rgb;
        upscaled += (c * 4.0f - nn - ns - nw - ne) * g_push.u_ups_sharp * 0.25f;
    }

    if (use_history) {
        float2 ndc = render_uv * 2.0f - 1.0f;
        float4 clip_pos = float4(ndc.x, ndc.y, depth * 2.0f - 1.0f, 1.0f);
        float4 view_pos = mul(g_push.u_ups_inv_proj, clip_pos);
        view_pos.xyz /= view_pos.w;
        float4 prev_clip = mul(g_push.u_ups_prev_vp, float4(view_pos.xyz, 1.0f));
        float2 prev_uv = (prev_clip.xy / prev_clip.w) * 0.5f + 0.5f;

        if (prev_uv.x >= 0.0f && prev_uv.x <= 1.0f &&
            prev_uv.y >= 0.0f && prev_uv.y <= 1.0f) {
            float3 history = g_history.SampleLevel(g_smp2, prev_uv, 0.0f).rgb;

            float3 aabb_min = min(min(nw, ne), min(nn, ns));
            float3 aabb_max = max(max(nw, ne), max(nn, ns));

            history = clip_aabb(aabb_min, aabb_max, history);
            upscaled = lerp(history, upscaled, 0.15f);
        }
    }

    return float4(saturate(upscaled), 1.0f);
}
