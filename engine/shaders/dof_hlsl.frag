// dof_hlsl.frag - depth of field, hex-disk gather (D3D12 hand-authored
// sidecar of shaders/dof.frag, the GL variant).
//
// Four floats of push block. u_dof_near / u_dof_far are GLSL *consts* in the
// twin (R89-2 hardcoded them), so dof_apply's writes to them are already
// no-ops on GL; they are static consts here with no rhi:uniform marker, so
// both backends resolve -1 -- the rule terrain's u_light_* and fxaa's
// threshold follow.
//
// Two textures at t0 / t1 because dof_apply binds them with
// rhi_cmd_bind_textures_multi(tex = {color, depth}, 2), which maps
// textures[i] to unit i; that binder was a stub on D3D12 until R620. Depth
// is read as .r: rhi_d3d12_srv_format aliases a typeless depth resource to an
// R32_FLOAT SRV, which is the route the shadow-atlas test already proves.
//
// linearize_depth keeps the GL formula (z_n = 2d - 1): it decodes a window
// depth d in [0,1] written as (ndc_z + 1) / 2, which is what GL's depth range
// produces and what the Vulkan forward shaders produce by doing
// gl_Position.z = (z + w) * 0.5 themselves (blinn_phong_vk.vert R214-A).
//
// R621 made the D3D12 forward sidecars do that conversion too, so the depth
// this reads is now the same convention on all three backends and this shader
// needs no compensation. Before R621 it was reading raw ndc_z here, which is
// what made DOF's focus wrong on D3D12; the fix belongs in the forward pass,
// not in this one.
struct PushConsts {
    float u_dof_focus;   //  0
    float u_dof_range;   //  4
    float u_dof_sw;      //  8
    float u_dof_sh;      // 12
};
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_dof_focus 0
// rhi:uniform u_dof_range 4
// rhi:uniform u_dof_sw 8
// rhi:uniform u_dof_sh 12

static const float u_dof_near = 0.1f;
static const float u_dof_far = 100.0f;

Texture2D g_color : register(t0, space0);
Texture2D g_depth : register(t1, space0);
SamplerState g_smp0 : register(s0, space0);
SamplerState g_smp1 : register(s1, space0);

static const int RINGS = 3;
static const int SAMPLES_PER_RING = 6;
static const float2 hex_disk[19] = {
    float2(0.0f, 0.0f),
    float2(0.33333f, 0.19245f), float2(0.0f, 0.38490f), float2(-0.33333f, 0.19245f),
    float2(-0.33333f, -0.19245f), float2(0.0f, -0.38490f), float2(0.33333f, -0.19245f),
    float2(0.66667f, 0.38490f), float2(0.0f, 0.76980f), float2(-0.66667f, 0.38490f),
    float2(-0.66667f, -0.38490f), float2(0.0f, -0.76980f), float2(0.66667f, -0.38490f),
    float2(1.0f, 0.57735f), float2(0.0f, 1.15470f), float2(-1.0f, 0.57735f),
    float2(-1.0f, -0.57735f), float2(0.0f, -1.15470f), float2(1.0f, -0.57735f)
};

float linearize_depth(float d) {
    float z_n = 2.0f * d - 1.0f;
    return 2.0f * u_dof_near * u_dof_far /
           (u_dof_far + u_dof_near - z_n * (u_dof_far - u_dof_near));
}

float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    const int total_samples = RINGS * SAMPLES_PER_RING + 1;
    float2 texel_size = float2(1.0f / g_push.u_dof_sw, 1.0f / g_push.u_dof_sh);

    float focus = g_push.u_dof_focus;
    if (focus <= 0.0f) {
        float center_d = 0.0f;
        for (int y = -1; y <= 1; y++) {
            for (int x = -1; x <= 1; x++) {
                float2 suv = (float2)0.5f + float2((float)x, (float)y) * texel_size;
                center_d += g_depth.Sample(g_smp1, suv).r;
            }
        }
        center_d /= 9.0f;
        focus = linearize_depth(center_d);
    }

    float depth = g_depth.Sample(g_smp1, uv).r;
    float linear_depth = linearize_depth(depth);

    float range = max(g_push.u_dof_range, 0.001f);
    float coc = clamp(abs(linear_depth - focus) / range, 0.0f, 1.0f);
    float blur_radius = coc * 10.0f;

    if (blur_radius < 0.5f)
        return g_color.Sample(g_smp0, uv);

    float3 result = (float3)0.0f;
    float total_weight = 0.0f;
    for (int i = 0; i < total_samples; i++) {
        float2 sample_uv = uv + hex_disk[i] * texel_size * blur_radius;
        if (sample_uv.x < 0.0f || sample_uv.x > 1.0f ||
            sample_uv.y < 0.0f || sample_uv.y > 1.0f) continue;
        float sample_linear = linearize_depth(g_depth.Sample(g_smp1, sample_uv).r);
        float sample_coc = clamp(abs(sample_linear - focus) / range, 0.0f, 1.0f);
        float weight = max(1.0f - sample_coc, 0.1f);
        result += g_color.Sample(g_smp0, sample_uv).rgb * weight;
        total_weight += weight;
    }

    if (total_weight > 0.0f)
        result /= total_weight;
    else
        result = g_color.Sample(g_smp0, uv).rgb;

    return float4(result, 1.0f);
}
