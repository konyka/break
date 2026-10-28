// combined_color_hlsl.frag - tonemap + colour grade + cinematic in one pass
// (D3D12 hand-authored sidecar of shaders/combined_color.frag, the GL
// variant).
//
// Fourteen push constants in the GLSL declaration order. t0 is the HDR scene
// and t1 the 1x1 adapted luminance: combined_color_apply binds them either
// through rhi_cmd_bind_material_textures (albedo -> 0, shadow -> 1) or
// rhi_cmd_bind_textures_multi({hdr, lum}), both of which land on units 0/1.
//
// AgX matrices: GLSL `v * mat3(a0..a8)` is dot(v, column j) with column j =
// (a[3j..3j+2]); HLSL float3x3(a0..a8) fills rows, so mul(M, v) gives the same
// numbers with the literals copied unchanged (as in tonemap_hlsl.frag).
struct PushConsts {
    float u_tm_exposure;      //  0
    float u_tm_gamma;         //  4
    int   u_tm_mode;          //  8
    float u_cg_saturation;    // 12
    float u_cg_contrast;      // 16
    float u_cg_brightness;    // 20
    float u_cg_temperature;   // 24
    float u_cg_tint;          // 28
    float u_cine_aberration;  // 32
    float u_cine_vignette;    // 36
    float u_cine_grain;       // 40
    float u_cine_time;        // 44
    float u_screen_w;         // 48
    float u_screen_h;         // 52
};                            // tail at 56
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_tm_exposure 0
// rhi:uniform u_tm_gamma 4
// rhi:uniform u_tm_mode 8
// rhi:uniform u_cg_saturation 12
// rhi:uniform u_cg_contrast 16
// rhi:uniform u_cg_brightness 20
// rhi:uniform u_cg_temperature 24
// rhi:uniform u_cg_tint 28
// rhi:uniform u_cine_aberration 32
// rhi:uniform u_cine_vignette 36
// rhi:uniform u_cine_grain 40
// rhi:uniform u_cine_time 44
// rhi:uniform u_screen_w 48
// rhi:uniform u_screen_h 52

Texture2D g_color : register(t0, space0);
Texture2D g_lum   : register(t1, space0);
SamplerState g_smp0 : register(s0, space0);
SamplerState g_smp1 : register(s1, space0);

static const float3 LUMA = float3(0.2126f, 0.7152f, 0.0722f);

float3 aces_fit(float3 x) {
    return saturate((x * (2.51f * x + 0.03f)) / (x * (2.43f * x + 0.59f) + 0.14f));
}

float3 agx(float3 val) {
    static const float3x3 inset = float3x3(
        0.84247906f, 0.04232824f, 0.04237565f,
        0.07843371f, 0.87846855f, 0.07843397f,
        0.07922376f, 0.07916613f, 0.87923044f);
    static const float3x3 outset = float3x3(
        1.1968790f, -0.0525374f, -0.0525374f,
        -0.0920852f, 1.1515179f, -0.0920852f,
        -0.0398265f, -0.0398265f, 1.1637448f);
    val = max(val, (float3)0.0f);
    val = saturate(mul(inset, val));
    val = log2(val + 0.0001f);
    val = saturate((val * 1.7f + 6.5f) / 11.7f);
    val = val * val * (3.0f - 2.0f * val);
    return saturate(mul(outset, val));
}

float3 khronos_neutral(float3 c) {
    c = max(c, (float3)0.0f);
    c = c * (2.51f * c + 0.03f) / (c * (2.43f * c + 0.59f) + 0.14f);
    return saturate(c);
}

float hash(float2 p) {
    float3 p3 = frac(p.xyx * 0.1031f);
    p3 += dot(p3, p3.yzx + 33.33f);
    return frac((p3.x + p3.y) * p3.z);
}

float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    float2 texel = float2(1.0f / g_push.u_screen_w, 1.0f / g_push.u_screen_h);
    float2 dir = uv - 0.5f;
    float dist = length(dir);

    float2 ca = dir * g_push.u_cine_aberration * texel;
    float3 hdr;
    hdr.r = g_color.Sample(g_smp0, uv + ca).r;
    hdr.g = g_color.Sample(g_smp0, uv).g;
    hdr.b = g_color.Sample(g_smp0, uv - ca).b;

    float scene_luma = g_lum.Sample(g_smp1, float2(0.5f, 0.5f)).r;
    float auto_exp = scene_luma > 0.01f ? 1.0f / (scene_luma + 0.5f) : g_push.u_tm_exposure;
    float exposure = lerp(g_push.u_tm_exposure, auto_exp, 0.8f);
    hdr *= exposure;
    float3 ldr;
    if (g_push.u_tm_mode == 1)      ldr = agx(hdr);
    else if (g_push.u_tm_mode == 2) ldr = khronos_neutral(hdr);
    else                            ldr = aces_fit(hdr);
    ldr = exp2(log2(max(ldr, (float3)0.0f)) / g_push.u_tm_gamma);

    float luma = dot(ldr, LUMA);
    ldr = lerp((float3)luma, ldr, g_push.u_cg_saturation);
    ldr = (ldr - 0.5f) * g_push.u_cg_contrast + 0.5f;
    ldr *= g_push.u_cg_brightness;
    float3 warm = float3(1.0f, 0.85f, 0.7f);
    float3 cool = float3(0.7f, 0.85f, 1.0f);
    ldr *= lerp(cool, warm, g_push.u_cg_temperature * 0.5f + 0.5f);
    ldr.g += g_push.u_cg_tint * 0.05f;

    float vignette = 1.0f - dist * dist * g_push.u_cine_vignette;
    ldr *= max(vignette, 0.0f);
    float noise = hash(uv * float2(g_push.u_screen_w, g_push.u_screen_h) +
                       frac(g_push.u_cine_time)) - 0.5f;
    ldr += noise * g_push.u_cine_grain;

    return float4(saturate(ldr), 1.0f);
}
