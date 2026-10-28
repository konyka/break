// color_grade_hlsl.frag - saturation / contrast / brightness / white balance
// (D3D12 hand-authored sidecar of shaders/color_grade.frag, the GL variant --
// not color_grade_vk.frag; D3D12 is not Vulkan and the GLSL file has no
// per-backend arm here).
//
// The five u_cg_ floats are loose uniforms in the GLSL and land in the b0
// root-constant block here, which is where rhi_cmd_set_uniform_f32 can reach
// them: on D3D12 that entry point only writes root constants, so anything the
// engine sets per draw has to be in this block. Twenty bytes is a
// non-question -- this family is the opposite of instanced, whose six uniforms
// do not fit (see the R616 entry in
// docs/superpowers/plans/2026-10-19-d3d12-forward-mrt-velocity-design-plan.md).
//
// The texture is register t0 because color_grade_apply binds it with
// rhi_cmd_bind_texture(..., unit 0).
struct PushConsts {
    float u_cg_saturation;  //   0
    float u_cg_contrast;    //   4
    float u_cg_brightness;  //   8
    float u_cg_temperature; //  12
    float u_cg_tint;        //  16
};                          // tail at 20
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_cg_saturation 0
// rhi:uniform u_cg_contrast 4
// rhi:uniform u_cg_brightness 8
// rhi:uniform u_cg_temperature 12
// rhi:uniform u_cg_tint 16

Texture2D g_src : register(t0, space0);
SamplerState g_smp : register(s0, space0);

float3 adjust_contrast(float3 c, float contrast) {
    return (c - 0.5f) * contrast + 0.5f;
}

// Toolchain note, since it will bite the next sidecar written here: this
// DXC REJECTS the single-argument vector constructor. float3(x) fails with
// "too few elements in vector initialization (expected 3 elements, have 1)",
// so a scalar must be widened with the C-style cast (float3)x instead. The
// other existing sidecars already avoid splats, which is why this was not
// written down anywhere until now. lerp(vector, vector, scalar) IS accepted,
// unlike GLSL's mix() spelling habit of leaving it scalar.
float3 adjust_saturation(float3 c, float sat) {
    float luma = dot(c, float3(0.2126f, 0.7152f, 0.0722f));
    return lerp((float3)luma, c, sat);
}

float3 white_balance(float3 c, float temp, float tint) {
    float3 warm = float3(1.0f, 0.85f, 0.7f);
    float3 cool = float3(0.7f, 0.85f, 1.0f);
    float3 t = lerp(cool, warm, temp * 0.5f + 0.5f);
    c *= t;
    c.g += tint * 0.05f;
    return c;
}

float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    float3 c = g_src.Sample(g_smp, uv).rgb;

    c = adjust_saturation(c, g_push.u_cg_saturation);
    c = adjust_contrast(c, g_push.u_cg_contrast);
    c *= g_push.u_cg_brightness;
    c = white_balance(c, g_push.u_cg_temperature, g_push.u_cg_tint);

    return float4(saturate(c), 1.0f);
}
