// sharpen_hlsl.frag - contrast-adaptive 3x3 sharpen with a ringing clamp
// (D3D12 hand-authored sidecar of shaders/sharpen.frag, the GL variant).
//
// Three floats of push block in the GLSL declaration order, and one texture
// at t0 because sharpen_apply binds the input with rhi_cmd_bind_texture(...,
// unit 0). Vertex stage is the shared post_hlsl.vert.
//
// The texel step comes from u_sharp_sw / u_sharp_sh, not the texture size,
// so the eight neighbour taps land on texel centres only when the caller
// passes the input's own size -- same as GL. GLSL fma(a, b, c) on vectors is
// mad here (HLSL fma is double-only). Edge taps go through the backend's
// static WRAP sampler rather than sharpen_init's CLAMP_TO_EDGE (the known
// D3D12 sampler limit), so the one-pixel frame border can differ from GL.
struct PushConsts {
    float u_sharp_strength;  //  0
    float u_sharp_sw;        //  4
    float u_sharp_sh;        //  8
};                           // tail at 12
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_sharp_strength 0
// rhi:uniform u_sharp_sw 4
// rhi:uniform u_sharp_sh 8

Texture2D g_tex : register(t0, space0);
SamplerState g_smp0 : register(s0, space0);

float3 tap(float2 uv) { return g_tex.Sample(g_smp0, uv).rgb; }

float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    float2 texel = 1.0f / float2(g_push.u_sharp_sw, g_push.u_sharp_sh);

    float3 a = tap(uv + float2(-texel.x, -texel.y));
    float3 b = tap(uv + float2( 0.0f,    -texel.y));
    float3 c = tap(uv + float2( texel.x, -texel.y));
    float3 d = tap(uv + float2(-texel.x,  0.0f   ));
    float3 e = tap(uv);
    float3 f = tap(uv + float2( texel.x,  0.0f   ));
    float3 g = tap(uv + float2(-texel.x,  texel.y));
    float3 h = tap(uv + float2( 0.0f,     texel.y));
    float3 i = tap(uv + float2( texel.x,  texel.y));

    float3 mn  = min(min(min(a, c), min(g, i)), min(min(b, d), min(f, h)));
    float3 mx  = max(max(max(a, c), max(g, i)), max(max(b, d), max(f, h)));
    float3 rng = mx - mn;

    float peak = -1.0f / (g_push.u_sharp_strength * 8.0f + 1.0f);
    float3 w = (float3)(1.0f + 4.0f * peak);

    float3 t = mad(a + c + g + i, (float3)(4.0f * peak),
                   (b + d + f + h) * (float3)peak);
    float3 out_color = max(e * w + t, 0.0f) / max(w, 1e-5f);

    out_color = clamp(out_color, mn - rng * 0.125f, mx + rng * 0.125f);

    out_color = max(out_color, (float3)0.0f);

    return float4(out_color, 1.0f);
}
