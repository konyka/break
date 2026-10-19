// contact_shadow_hlsl.frag - screen-space contact shadow, 12-step march
// (D3D12 hand-authored sidecar of shaders/contact_shadow.frag, the GL variant).
//
// Two textures: t0 depth, t1 scene (R550-A, matching contact_shadow_vk.frag
// and the GL bind_textures_multi order). Two tables clamp 32BIT_CONSTANTS at
// 62 DWORDs = 248 bytes; this uses 24.
//
// The push block puts the mat4 FIRST rather than mirroring the GLSL
// declaration order. u_cs_light_x/_y/_z, u_cs_sw and u_cs_sh are five floats,
// so keeping them ahead of the matrix would leave a 12-byte hole before the
// 16-byte alignment boundary; leading with the matrix packs the block into 21
// DWORDs instead of 24. The offsets are pinned by the test either way, and
// this is a sidecar-local layout, not a change to the engine's contract.
struct PushConsts {
    float4x4 u_cs_inv_proj;  //   0
    float    u_cs_light_x;   //  64
    float    u_cs_light_y;   //  68
    float    u_cs_light_z;   //  72
    float    u_cs_sw;        //  76
    float    u_cs_sh;        //  80
};                          // tail at 84, 16B-aligned to 96
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_cs_inv_proj 0
// rhi:uniform u_cs_light_x 64
// rhi:uniform u_cs_light_y 68
// rhi:uniform u_cs_light_z 72
// rhi:uniform u_cs_sw 76
// rhi:uniform u_cs_sh 80

Texture2D g_depth : register(t0, space0);
Texture2D g_scene : register(t1, space0);
SamplerState g_smp0 : register(s0, space0);
SamplerState g_smp1 : register(s1, space0);

float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    // R550-A: self-composite -- multiply the incoming frame-chain colour by the
    // shadow mask. Approximation: this darkens ambient/indirect terms too,
    // accepted for a screen-space contact hint.
    float3 scene = g_scene.Sample(g_smp1, uv).rgb;
    float depth = g_depth.Sample(g_smp0, uv).r;
    if (depth >= 1.0f)
        return float4(scene, 1.0f);

    float2 res = float2(g_push.u_cs_sw, g_push.u_cs_sh);
    float3 light_dir = normalize(float3(g_push.u_cs_light_x,
                                         g_push.u_cs_light_y,
                                         g_push.u_cs_light_z));

    float2 ndc = uv * 2.0f - 1.0f;
    float4 vp = mul(g_push.u_cs_inv_proj, float4(ndc, depth * 2.0f - 1.0f, 1.0f));
    float3 view_pos = vp.xyz / vp.w;

    const int steps = 12;
    const float ray_len = 0.5f;
    const float thickness = 0.04f;

    float2 screen_step = (light_dir.xy * 5.0f) / res;

    float t = ray_len / (float)steps;

    float3 magic = float3(0.06711056f, 0.00583715f, 52.9829189f);
    float noise = frac(magic.z * frac(dot(pos.xy, magic.xy)));
    float jitter = noise * t;

    float shadow = 1.0f;

    for (int i = 1; i <= steps; i++) {
        float offset = t * (float)i + jitter;
        float3 ray_pos = view_pos + light_dir * offset;
        float2 sample_uv = uv + screen_step * (float)i;

        if (sample_uv.x < 0.0f || sample_uv.x > 1.0f ||
            sample_uv.y < 0.0f || sample_uv.y > 1.0f) break;

        float sd = g_depth.Sample(g_smp0, sample_uv).r;
        float2 s_ndc = sample_uv * 2.0f - 1.0f;
        float4 svp = mul(g_push.u_cs_inv_proj, float4(s_ndc, sd * 2.0f - 1.0f, 1.0f)); /* R211-B */
        float3 sampled_view = svp.xyz / svp.w;

        float diff = sampled_view.z - ray_pos.z;
        if (diff > 0.0f && diff < thickness) {
            float penumbra = 1.0f - smoothstep(0.0f, thickness, diff);
            shadow *= 1.0f - penumbra * 0.8f;
        }
    }

    shadow = max(shadow, 0.0f);

    return float4(scene * shadow, 1.0f);
}
