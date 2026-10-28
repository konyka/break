// shadow_sample_hlsl.frag — PS for the shadow-atlas sampling test (D3D12
// hand-authored sidecar).
//
// The compare here is DONE BY HAND on the sampled .r channel, not through a
// comparison sampler. That is deliberate and it is what the production
// shaders do: blinn_phong_clustered.frag:70-71 samples the point-shadow cube
// as texture(cube, uv).r and compares in GLSL, and the GL backend explicitly
// sets GL_TEXTURE_COMPARE_MODE = GL_NONE for the same reason (rhi_gl.c:3809).
// No production shader declares sampler2DShadow / samplerCubeShadow, so the
// static LINEAR sampler the root signature provides is exactly what is needed.
// Rewriting this as a SamplerComparisonState would be the regression this
// shader exists to rule out.
//
// t1 is material unit 1, where rhi_cmd_bind_shadow_texture binds the atlas.
// g_shadow.r is the stored depth in .r; u_compare.z is the fragment's own depth
// and u_compare.w is the bias. Output is 1.0 (white = lit) when the fragment
// is nearer than the stored depth, else 0.0.
struct PushConsts {
    float4x4 u_transform;
    float4 u_compare;   // z = receiver depth, w = bias
};
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_transform 0
// rhi:uniform u_compare 64
Texture2D g_shadow : register(t1, space0);
SamplerState g_smp : register(s1, space0);
float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target {
    float stored = g_shadow.Sample(g_smp, uv).r;
    float lit = g_push.u_compare.z - g_push.u_compare.w <= stored ? 1.0 : 0.0;
    return float4(lit, lit, lit, 1.0);
}
