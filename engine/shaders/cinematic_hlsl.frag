// cinematic_hlsl.frag - chromatic aberration, vignette, film grain
// (D3D12 hand-authored sidecar of shaders/cinematic.frag, the GL variant).
//
// Six floats of push block in the GLSL declaration order (the _vk twin's
// offsets 0..20 are the same packing). One texture at t0: cinematic_apply
// binds it with rhi_cmd_bind_texture(..., unit 0).
//
// The grain hash is fed vUV * (sw, sh) + fract(time), i.e. the pixel
// coordinate, so it needs the interpolated uv, not SV_Position -- the two
// agree only up to the half-pixel offset, and the hash is chaotic. GLSL
// mix/fract are lerp/frac; vec3(p.xyx) is the same swizzle.
struct PushConsts {
    float u_cine_aberration;  //  0
    float u_cine_vignette;    //  4
    float u_cine_grain;       //  8
    float u_cine_time;        // 12
    float u_cine_sw;          // 16
    float u_cine_sh;          // 20
};                            // tail at 24
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_cine_aberration 0
// rhi:uniform u_cine_vignette 4
// rhi:uniform u_cine_grain 8
// rhi:uniform u_cine_time 12
// rhi:uniform u_cine_sw 16
// rhi:uniform u_cine_sh 20

Texture2D g_tex : register(t0, space0);
SamplerState g_smp0 : register(s0, space0);

float hash(float2 p) {
    float3 p3 = frac(p.xyx * 0.1031f);
    p3 += dot(p3, p3.yzx + 33.33f);
    return frac((p3.x + p3.y) * p3.z);
}

float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    float2 texel_size = float2(1.0f / g_push.u_cine_sw, 1.0f / g_push.u_cine_sh);
    float2 dir = uv - 0.5f;
    float dist = length(dir);

    float2 r_offset = dir * g_push.u_cine_aberration * texel_size;
    float2 g_offset = (float2)0.0f;
    float2 b_offset = -dir * g_push.u_cine_aberration * texel_size;

    float r = g_tex.Sample(g_smp0, uv + r_offset).r;
    float g = g_tex.Sample(g_smp0, uv + g_offset).g;
    float b = g_tex.Sample(g_smp0, uv + b_offset).b;
    float3 color = float3(r, g, b);

    float vignette = 1.0f - dist * dist * g_push.u_cine_vignette;
    color *= max(vignette, 0.0f);

    float noise = hash(uv * float2(g_push.u_cine_sw, g_push.u_cine_sh) +
                       frac(g_push.u_cine_time)) - 0.5f;
    color += noise * g_push.u_cine_grain;

    return float4(max(color, (float3)0.0f), 1.0f);
}
