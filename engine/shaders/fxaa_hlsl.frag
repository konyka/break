// fxaa_hlsl.frag - FXAA edge blend (D3D12 hand-authored sidecar of
// shaders/fxaa.frag, the GL variant).
//
// Two floats of push block. u_fxaa_threshold is a GLSL *const* in the twin,
// so fxaa_apply's write to it is already a no-op on GL (resolve() is -1
// there too); it is a static const here with no rhi:uniform marker, so both
// backends behave the same -- the terrain sidecar's u_light_* follows the
// same rule. Texture t0 because fxaa_apply binds unit 0; vertex stage is the
// shared post_hlsl.vert.
//
// Ported line for line. The one spelling difference worth noting is that
// HLSL's ?: on vectors is component-wise, so every ternary below selects a
// scalar, exactly as the GLSL does, to keep the two diffable.
struct PushConsts {
    float u_fxaa_sw;   //  0
    float u_fxaa_sh;   //  4
};
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_fxaa_sw 0
// rhi:uniform u_fxaa_sh 4

static const float u_fxaa_threshold = 0.0312f;

Texture2D g_src : register(t0, space0);
SamplerState g_smp : register(s0, space0);

static const float3 LUMA = float3(0.2126f, 0.7152f, 0.0722f);

float3 tap(float2 uv) { return g_src.Sample(g_smp, uv).rgb; }

float4 main(float4 pos_px : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    float2 texel = float2(1.0f / g_push.u_fxaa_sw, 1.0f / g_push.u_fxaa_sh);

    float3 cN  = tap(uv + float2(0.0f, -texel.y));
    float3 cS  = tap(uv + float2(0.0f,  texel.y));
    float3 cW  = tap(uv + float2(-texel.x, 0.0f));
    float3 cE  = tap(uv + float2( texel.x, 0.0f));
    float3 cM  = tap(uv);
    float3 cNW = tap(uv + float2(-texel.x, -texel.y));
    float3 cNE = tap(uv + float2( texel.x, -texel.y));
    float3 cSW = tap(uv + float2(-texel.x,  texel.y));
    float3 cSE = tap(uv + float2( texel.x,  texel.y));

    float lumaNW = dot(cNW, LUMA);
    float lumaNE = dot(cNE, LUMA);
    float lumaSW = dot(cSW, LUMA);
    float lumaSE = dot(cSE, LUMA);
    float lumaM  = dot(cM,  LUMA);

    float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
    float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));

    float range = lumaMax - lumaMin;
    if (range < max(u_fxaa_threshold, lumaMax * 0.125f))
        return float4(cM, 1.0f);

    float lumaN = dot(cN, LUMA);
    float lumaS = dot(cS, LUMA);
    float lumaW = dot(cW, LUMA);
    float lumaE = dot(cE, LUMA);

    float edgeVert  = abs(lumaN + lumaS - 2.0f * lumaM) * 2.0f;
    float edgeHoriz = abs(lumaW + lumaE - 2.0f * lumaM) * 2.0f;
    edgeVert  += abs(lumaNW + lumaSW - 2.0f * lumaN);
    edgeVert  += abs(lumaNE + lumaSE - 2.0f * lumaS);
    edgeHoriz += abs(lumaNW + lumaNE - 2.0f * lumaW);
    edgeHoriz += abs(lumaSW + lumaSE - 2.0f * lumaE);

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

    float lumaLocalAvg;
    float pos;
    if (isLuma1) {
        lumaLocalAvg = (luma1 + lumaM) * 0.5f;
        pos = -stepLength;
    } else {
        lumaLocalAvg = (luma2 + lumaM) * 0.5f;
        pos = stepLength;
    }

    float2 posA = uv;
    float2 posB = uv;
    if (horizontal) {
        posA.y += pos;
        posB.y += pos;
        posA.x -= pixel2 * 0.5f;
        posB.x += pixel2 * 0.5f;
    } else {
        posA.x += pos;
        posB.x += pos;
        posA.y -= pixel2 * 0.5f;
        posB.y += pixel2 * 0.5f;
    }

    float3 colorA = tap(posA);
    float3 colorB = tap(posB);
    float lumaPosA = dot(colorA, LUMA);
    float lumaPosB = dot(colorB, LUMA);

    float distA = abs(lumaPosA - lumaLocalAvg);
    float distB = abs(lumaPosB - lumaLocalAvg);

    float blend;
    if (distA < gradientScaled && distB < gradientScaled) {
        blend = 0.5f - 0.5f * (pos / stepLength);
    } else {
        blend = distA < distB ? -0.5f + 0.5f * (distA / (distA + distB))
                              :  0.5f - 0.5f * (distB / (distA + distB));
    }

    float2 finalPos = uv;
    if (horizontal)
        finalPos.y += blend * stepLength;
    else
        finalPos.x += blend * stepLength;

    return float4(tap(finalPos), 1.0f);
}
