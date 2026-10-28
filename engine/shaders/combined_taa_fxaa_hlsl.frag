// combined_taa_fxaa_hlsl.frag - TAA resolve + FXAA in one pass
// (D3D12 hand-authored sidecar of shaders/combined_taa_fxaa.frag, the GL
// variant).
//
// Four textures at t0..t3 because combined_aa_apply binds {curr, hist,
// depth, velocity} through rhi_cmd_bind_textures_multi (R218-A order).
//
// u_taa_curr_vp is declared by the GLSL but never read, so GL's linker drops
// it (resolve -1); it is left out of the push block here too. u_taa_blend
// and u_fxaa_threshold are GLSL consts, static consts here with no
// rhi:uniform marker, so combined_aa_apply's writes to them are no-ops on
// both backends. Matrix products follow taa_hlsl.frag: mul(M, v).
struct PushConsts {
    float4x4 u_taa_prev_vp;       //   0
    float4x4 u_taa_inv_proj;      //  64
    float    u_screen_w;          // 128
    float    u_screen_h;          // 132
    float    u_taa_first_frame;   // 136
    float    u_taa_use_velocity;  // 140
};                                // tail at 144
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_taa_prev_vp 0
// rhi:uniform u_taa_inv_proj 64
// rhi:uniform u_screen_w 128
// rhi:uniform u_screen_h 132
// rhi:uniform u_taa_first_frame 136
// rhi:uniform u_taa_use_velocity 140

static const float u_taa_blend = 0.1f;
static const float u_fxaa_threshold = 0.0312f;

Texture2D g_curr     : register(t0, space0);
Texture2D g_hist     : register(t1, space0);
Texture2D g_depth    : register(t2, space0);
Texture2D g_velocity : register(t3, space0);
SamplerState g_smp0 : register(s0, space0);
SamplerState g_smp1 : register(s1, space0);
SamplerState g_smp2 : register(s2, space0);
SamplerState g_smp3 : register(s3, space0);

static const float3 LUMA = float3(0.2126f, 0.7152f, 0.0722f);

float3 tap(float2 uv) { return g_curr.Sample(g_smp0, uv).rgb; }

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

float3 fxaa(float2 uv, float2 texel) {
    float3 cM  = tap(uv);
    float3 cN  = tap(uv + float2(0.0f, -texel.y));
    float3 cS  = tap(uv + float2(0.0f,  texel.y));
    float3 cW  = tap(uv + float2(-texel.x, 0.0f));
    float3 cE  = tap(uv + float2( texel.x, 0.0f));
    float3 cNW = tap(uv + float2(-texel.x, -texel.y));
    float3 cNE = tap(uv + float2( texel.x, -texel.y));
    float3 cSW = tap(uv + float2(-texel.x,  texel.y));
    float3 cSE = tap(uv + float2( texel.x,  texel.y));

    float lumaM  = dot(cM,  LUMA);
    float lumaNW = dot(cNW, LUMA);
    float lumaNE = dot(cNE, LUMA);
    float lumaSW = dot(cSW, LUMA);
    float lumaSE = dot(cSE, LUMA);

    float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
    float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));

    float range = lumaMax - lumaMin;
    if (range < max(u_fxaa_threshold, lumaMax * 0.125f))
        return cM;

    float lumaN = dot(cN, LUMA);
    float lumaS = dot(cS, LUMA);
    float lumaW = dot(cW, LUMA);
    float lumaE = dot(cE, LUMA);

    float edgeVert  = abs(lumaN + lumaS - 2.0f * lumaM) * 2.0f
                    + abs(lumaNW + lumaSW - 2.0f * lumaN)
                    + abs(lumaNE + lumaSE - 2.0f * lumaS);
    float edgeHoriz = abs(lumaW + lumaE - 2.0f * lumaM) * 2.0f
                    + abs(lumaNW + lumaNE - 2.0f * lumaW)
                    + abs(lumaSW + lumaSE - 2.0f * lumaE);

    bool horizontal = edgeHoriz >= edgeVert;
    float pixel1 = horizontal ? texel.y : texel.x;
    float pixel2 = horizontal ? texel.x : texel.y;
    float luma1 = horizontal ? lumaN : lumaW;
    float luma2 = horizontal ? lumaS : lumaE;
    float gradient1 = abs(luma1 - lumaM);
    float gradient2 = abs(luma2 - lumaM);
    bool isLuma1 = gradient1 >= gradient2;

    float gradientScaled = max(gradient1, gradient2) * 0.25f;
    float stepLength = pixel1;
    float lumaLocalAvg = isLuma1 ? (luma1 + lumaM) * 0.5f : (luma2 + lumaM) * 0.5f;
    float pos = isLuma1 ? -stepLength : stepLength;

    float2 posA = uv;
    float2 posB = uv;
    if (horizontal) {
        posA.y += pos; posB.y += pos;
        posA.x -= pixel2 * 0.5f; posB.x += pixel2 * 0.5f;
    } else {
        posA.x += pos; posB.x += pos;
        posA.y -= pixel2 * 0.5f; posB.y += pixel2 * 0.5f;
    }

    float lumaPosA = dot(tap(posA), LUMA);
    float lumaPosB = dot(tap(posB), LUMA);
    float distA = abs(lumaPosA - lumaLocalAvg);
    float distB = abs(lumaPosB - lumaLocalAvg);

    float blend;
    if (distA < gradientScaled && distB < gradientScaled)
        blend = 0.5f - 0.5f * (pos / stepLength);
    else
        blend = distA < distB ? -0.5f + 0.5f * (distA / (distA + distB))
                              :  0.5f - 0.5f * (distB / (distA + distB));

    float2 finalPos = uv;
    if (horizontal) finalPos.y += blend * stepLength;
    else            finalPos.x += blend * stepLength;
    return tap(finalPos);
}

float4 main(float4 pos_px : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    float2 texel = float2(1.0f / g_push.u_screen_w, 1.0f / g_push.u_screen_h);

    float3 aa_color = fxaa(uv, texel);

    float3 c0 = tap(uv);
    float3 n_min = c0, n_max = c0;
    for (int y = -1; y <= 1; ++y)
    for (int x = -1; x <= 1; ++x) {
        float3 s = tap(uv + float2(x, y) * texel);
        n_min = min(n_min, s);
        n_max = max(n_max, s);
    }

    float3 result = aa_color;
    float depth = g_depth.Sample(g_smp2, uv).r;
    if (depth < 1.0f && g_push.u_taa_first_frame < 0.5f) {
        float2 prev_uv;
        if (g_push.u_taa_use_velocity > 0.5f) {
            float2 vel = g_velocity.Sample(g_smp3, uv).rg;
            prev_uv = uv - vel * 0.5f;
        } else {
            float2 ndc = uv * 2.0f - 1.0f;
            float4 world_h = mul(g_push.u_taa_inv_proj,
                                 float4(ndc, depth * 2.0f - 1.0f, 1.0f));
            float3 world = world_h.xyz / world_h.w;
            float4 prev_clip = mul(g_push.u_taa_prev_vp, float4(world, 1.0f));
            prev_uv = (prev_clip.xy / prev_clip.w) * 0.5f + 0.5f;
        }
        if (prev_uv.x >= 0.0f && prev_uv.y >= 0.0f &&
            prev_uv.x <= 1.0f && prev_uv.y <= 1.0f) {
            float3 hist = g_hist.Sample(g_smp1, prev_uv).rgb;
            hist = clip_aabb(n_min, n_max, hist);
            result = lerp(hist, aa_color, clamp(u_taa_blend, 0.05f, 1.0f));
        }
    }

    return float4(result, 1.0f);
}
