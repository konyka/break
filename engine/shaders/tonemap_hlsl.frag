// tonemap_hlsl.frag - ACES / AgX / Khronos-neutral tone mapping with
// auto-exposure (D3D12 sidecar of shaders/tonemap.frag).
//
// The three loose uniforms ride the b0 root-constant block. t0 is the HDR
// scene and t1 the 1x1 adapted-luminance target: tonemap_apply binds both
// through rhi_cmd_bind_material_textures (albedo -> unit 0, shadow ->
// unit 1), the same pairing the GLSL's layout(binding = 0/1) declares.
//
// Matrix order: GLSL `v * mat3(a0..a8)` takes column j = (a[3j], a[3j+1],
// a[3j+2]) and returns dot(v, column j). HLSL float3x3(a0..a8) fills ROWS,
// and mul(M, v) returns dot(row j, v) -- the same numbers, so the literals
// are copied unchanged and the product is written mul(M, v).
struct PushConsts {
    float u_tm_exposure; // 0
    float u_tm_gamma;    // 4
    int   u_tm_mode;     // 8
};
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_tm_exposure 0
// rhi:uniform u_tm_gamma 4
// rhi:uniform u_tm_mode 8
Texture2D g_hdr : register(t0, space0);
SamplerState g_smp : register(s0, space0);
Texture2D g_lum : register(t1, space0);
SamplerState g_smp1 : register(s1, space0);

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

float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {
    float scene_luma = g_lum.Sample(g_smp1, float2(0.5f, 0.5f)).r;
    float auto_exp = scene_luma > 0.01f ? 1.0f / (scene_luma + 0.5f) : g_push.u_tm_exposure;
    float exposure = lerp(g_push.u_tm_exposure, auto_exp, 0.8f);
    float3 hdr = g_hdr.Sample(g_smp, uv).rgb * exposure;
    float3 ldr;
    if (g_push.u_tm_mode == 1)      ldr = agx(hdr);
    else if (g_push.u_tm_mode == 2) ldr = khronos_neutral(hdr);
    else                            ldr = aces_fit(hdr);
    ldr = exp2(log2(max(ldr, (float3)0.0f)) / g_push.u_tm_gamma);
    return float4(saturate(ldr), 1.0f);
}
