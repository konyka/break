// lens_effects_hlsl.frag - chromatic aberration, vignette, film grain
// (D312 hand-authored sidecar of shaders/lens_effects.frag, the GL variant --
// D3D12 is not Vulkan and this file has no per-backend arm).
//
// Four floats and one texture: sixteen bytes of push block, so this is the
// opposite end of the budget scale from instanced, whose six uniforms do not
// fit (R616 in
// docs/superpowers/plans/2026-10-19-d3d12-forward-mrt-velocity-design-plan.md).
// The texture is register t0 because lens_effects_apply binds it with
// rhi_cmd_bind_texture(..., unit 0), and shares post_hlsl.vert with the rest of
// the post family.
struct PushConsts {
    float u_ca_strength;         //   0
    float u_vignette_strength;   //   4
    float u_vignette_softness;   //   8
    float u_grain_strength;      //  12
};
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_ca_strength 0
// rhi:uniform u_vignette_strength 4
// rhi:uniform u_vignette_softness 8
// rhi:uniform u_grain_strength 12

Texture2D g_src : register(t0, space0);
SamplerState g_smp : register(s0, space0);

float interleaved_gradient_noise(float2 p) {
    float3 magic = float3(0.06711056f, 0.00583715f, 52.9829189f);
    return frac(magic.z * frac(dot(p, magic.xy)));
}

float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    float2 centre = uv - 0.5f;

    // gl_FragCoord is SV_Position in HLSL -- the pixel centre in framebuffer
    // coordinates, which is what the grain hash is defined against. Feeding it
    // UV instead would make the grain a smooth function of position and turn
    // film grain into a gradient.
    float ca_offset = g_push.u_ca_strength * length(centre);
    float3 color;
    color.r = g_src.Sample(g_smp, uv + centre * ca_offset).r;
    color.g = g_src.Sample(g_smp, uv).g;
    color.b = g_src.Sample(g_smp, uv - centre * ca_offset).b;

    float dist = length(centre);
    float vignette = 1.0f - smoothstep(g_push.u_vignette_softness, 0.8f,
                                       dist * g_push.u_vignette_strength);
    color *= vignette;

    float grain = interleaved_gradient_noise(pos.xy) - 0.5f;
    color += grain * g_push.u_grain_strength;

    return float4(max(color, (float3)0.0f), 1.0f);
}
