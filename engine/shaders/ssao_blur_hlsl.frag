// ssao_blur_hlsl.frag - 5x5 depth-aware bilateral blur of the raw AO
// (D3D12 hand-authored sidecar of shaders/ssao_blur.frag).
//
// No push block. Two textures: ssao_apply binds the blur pass through
// rhi_cmd_bind_material_textures with the raw AO as albedo (unit 0, t0) and
// the depth as shadow (unit 1, t1) -- the GLSL layout(binding = 0/1). The
// other four material units get the AO too; this shader declares neither,
// so the binder skips them.
//
// textureSize(u_ssao, 0) is GetDimensions. The taps are integer texel steps
// from the pixel centre, so on a target the size of the AO buffer they land
// on texel centres and the filter mode does not matter; inside the loop they
// use SampleLevel 0 (single-mip targets, same LOD texture() picks on GL).
// Taps past the edge are addressed by the backend's static WRAP sampler,
// not the CLAMP_TO_EDGE sampler ssao_init asks for (the known D3D12 sampler
// limit, rhi_cmd_bind_texture), so the outer two rings of a frame can differ
// from GL.
Texture2D g_ssao  : register(t0, space0);
Texture2D g_depth : register(t1, space0);
SamplerState g_smp0 : register(s0, space0);
SamplerState g_smp1 : register(s1, space0);

float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    uint tw, th, levels;
    g_ssao.GetDimensions(0u, tw, th, levels);
    float2 texel = 1.0f / float2(tw, th);

    float center_depth = g_depth.Sample(g_smp1, uv).r;
    float center_ao = g_ssao.Sample(g_smp0, uv).r;

    if (center_depth >= 1.0f)
        return (float4)1.0f;

    float sigma = 0.01f;
    float result = 0.0f;
    float total_w = 0.0f;

    for (int y = -2; y <= 2; y++) {
        for (int x = -2; x <= 2; x++) {
            float2 offset = float2((float)x, (float)y) * texel;
            float2 sample_uv = uv + offset;

            float sample_ao = g_ssao.SampleLevel(g_smp0, sample_uv, 0.0f).r;
            float sample_depth = g_depth.SampleLevel(g_smp1, sample_uv, 0.0f).r;

            float depth_diff = abs(sample_depth - center_depth);
            float w = exp(-depth_diff * depth_diff / (2.0f * sigma * sigma));

            float spatial = exp(-(float)(x * x + y * y) / 4.0f);
            w *= spatial;

            result += sample_ao * w;
            total_w += w;
        }
    }

    float ao = total_w > 0.0f ? result / total_w : center_ao;

    return float4(ao, ao, ao, 1.0f);
}
