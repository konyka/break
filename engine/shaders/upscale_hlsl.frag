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
// GLSL textureOffset(s, uv, ivec2) is Sample(s, uv, int2); the AABB taps and
// the history read sit behind a data-dependent branch, so they use
// SampleLevel 0 (single-mip targets, the LOD texture() selects on GL). The
// Catmull-Rom taps land on source texel centres (base is floor(pos) - 0.5
// texels), so filtering does not move them. Matrices come in whole and
// column-major: GLSL M * v is mul(M, v).
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

float3 sample_catmull(float2 uv, float2 texel) {
    float2 p = uv / texel - 0.5f;
    float2 f = frac(p);
    float fx = f.x, fy = f.y;

    /* R641: Catmull-Rom weights carry an overall 1/2. Without it they
     * summed to 2 at texel centres (1.5 at the midpoint), so the upscale
     * doubled every flat region and clamp() turned it white on every
     * backend; each axis now sums to exactly 1. */
    float wx0 = 0.5f * (-fx + 2.0f*fx*fx - fx*fx*fx);
    float wx1 = 0.5f * (2.0f - 5.0f*fx*fx + 3.0f*fx*fx*fx);
    float wx2 = 0.5f * (fx + 4.0f*fx*fx - 3.0f*fx*fx*fx);
    float wx3 = 0.5f * (-fx*fx + fx*fx*fx);

    float wy0 = 0.5f * (-fy + 2.0f*fy*fy - fy*fy*fy);
    float wy1 = 0.5f * (2.0f - 5.0f*fy*fy + 3.0f*fy*fy*fy);
    float wy2 = 0.5f * (fy + 4.0f*fy*fy - 3.0f*fy*fy*fy);
    float wy3 = 0.5f * (-fy*fy + fy*fy*fy);

    float row_w[4] = { wy0, wy1, wy2, wy3 };
    float col_w[4] = { wx0, wx1, wx2, wx3 };

    float2 base = (floor(p) - float2(0.5f, 0.5f)) * texel;

    float3 result = (float3)0.0f;
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            float2 sample_uv = base + float2((float)c, (float)r) * texel;
            result += g_src.SampleLevel(g_smp0, sample_uv, 0.0f).rgb * row_w[r] * col_w[c];
        }
    }
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

    if (g_push.u_ups_sharp > 0.0f) {
        float3 c = g_src.SampleLevel(g_smp0, render_uv, 0.0f).rgb;
        float3 n = g_src.SampleLevel(g_smp0, render_uv + float2(0.0f, -render_texel.y), 0.0f).rgb;
        float3 s = g_src.SampleLevel(g_smp0, render_uv + float2(0.0f,  render_texel.y), 0.0f).rgb;
        float3 w = g_src.SampleLevel(g_smp0, render_uv + float2(-render_texel.x, 0.0f), 0.0f).rgb;
        float3 e = g_src.SampleLevel(g_smp0, render_uv + float2( render_texel.x, 0.0f), 0.0f).rgb;
        upscaled += (c * 4.0f - n - s - w - e) * g_push.u_ups_sharp * 0.25f;
    }

    float depth = g_depth.Sample(g_smp1, render_uv).r;
    if (depth < 1.0f && g_push.u_ups_first_frame < 0.5f) {
        float2 ndc = render_uv * 2.0f - 1.0f;
        float4 clip_pos = float4(ndc.x, ndc.y, depth * 2.0f - 1.0f, 1.0f);
        float4 view_pos = mul(g_push.u_ups_inv_proj, clip_pos);
        view_pos.xyz /= view_pos.w;
        float4 prev_clip = mul(g_push.u_ups_prev_vp, float4(view_pos.xyz, 1.0f));
        float2 prev_uv = (prev_clip.xy / prev_clip.w) * 0.5f + 0.5f;

        if (prev_uv.x >= 0.0f && prev_uv.x <= 1.0f &&
            prev_uv.y >= 0.0f && prev_uv.y <= 1.0f) {
            float3 history = g_history.SampleLevel(g_smp2, prev_uv, 0.0f).rgb;

            float3 n0 = g_src.SampleLevel(g_smp0, render_uv, 0.0f, int2(-1, 0)).rgb;
            float3 n1 = g_src.SampleLevel(g_smp0, render_uv, 0.0f, int2( 1, 0)).rgb;
            float3 n2 = g_src.SampleLevel(g_smp0, render_uv, 0.0f, int2( 0,-1)).rgb;
            float3 n3 = g_src.SampleLevel(g_smp0, render_uv, 0.0f, int2( 0, 1)).rgb;
            float3 aabb_min = min(min(n0, n1), min(n2, n3));
            float3 aabb_max = max(max(n0, n1), max(n2, n3));

            history = clip_aabb(aabb_min, aabb_max, history);
            upscaled = lerp(history, upscaled, 0.15f);
        }
    }

    return float4(saturate(upscaled), 1.0f);
}
