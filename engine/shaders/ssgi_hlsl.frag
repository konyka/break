// ssgi_hlsl.frag - screen-space global illumination, 16-tap hemisphere
// gather (D3D12 hand-authored sidecar of shaders/ssgi.frag, the GL variant).
//
// Two textures: t0 depth, t1 colour (R222-B, matching ssgi_vk.frag and the GL
// bind_textures_multi order). Two tables clamp 32BIT_CONSTANTS at 62 DWORDs;
// this uses 36.
//
// The mat4s go first so the four floats follow them without a 16-byte
// alignment hole: the GLSL declaration order would put u_ssgi_radius first
// and push the first matrix to offset 16 anyway, spending 4 DWORDs.
//
// R621 matters for t0: depth is decoded as depth * 2 - 1, which assumes the
// forward pass wrote (ndc_z + 1) / 2.
struct PushConsts {
    float4x4 u_ssgi_inv_proj;  //   0
    float4x4 u_ssgi_proj;      //  64
    float    u_ssgi_radius;    // 128
    float    u_ssgi_intensity; // 132
    float    u_ssgi_sw;        // 136
    float    u_ssgi_sh;        // 140
};                             // tail at 144
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_ssgi_inv_proj 0
// rhi:uniform u_ssgi_proj 64
// rhi:uniform u_ssgi_radius 128
// rhi:uniform u_ssgi_intensity 132
// rhi:uniform u_ssgi_sw 136
// rhi:uniform u_ssgi_sh 140

Texture2D g_depth : register(t0, space0);
Texture2D g_color : register(t1, space0);
SamplerState g_smp0 : register(s0, space0);
SamplerState g_smp1 : register(s1, space0);

float3 view_pos_from_depth(float2 uv, float depth) {
    float4 clip = float4(uv * 2.0f - 1.0f, depth * 2.0f - 1.0f, 1.0f);
    float4 view_h = mul(g_push.u_ssgi_inv_proj, clip);
    return view_h.xyz / view_h.w;
}

float interleaved_gradient_noise(float2 screen_pos) {
    float3 magic = float3(0.06711056f, 0.00583715f, 52.9829189f);
    return frac(magic.z * frac(dot(screen_pos, magic.xy)));
}

float3 construct_normal(float3 pos) {
    // GLSL's dFdx / dFdy are the FINE derivatives; this DXC spells them
    // ddx_fine / ddy_fine. Plain ddx would be the COARSE derivative and would
    // give a different normal on a 2x2 quad -- see ssr_hlsl.frag.
    return normalize(cross(ddx_fine(pos), ddy_fine(pos)));
}

float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    float depth = g_depth.Sample(g_smp0, uv).r;
    if (depth >= 1.0f)
        return float4(0.0f, 0.0f, 0.0f, 1.0f);

    float3 p = view_pos_from_depth(uv, depth);
    float3 nrm = construct_normal(p);

    float noise = interleaved_gradient_noise(pos.xy);

    // R84-2: hoist the tangent frame out of the 16-iteration loop.
    float3 up = abs(nrm.z) < 0.999f ? float3(0.0f, 0.0f, 1.0f)
                                    : float3(1.0f, 0.0f, 0.0f);
    float3 tangent = normalize(cross(up, nrm));
    float3 bitangent = cross(nrm, tangent);

    float3 gi = (float3)0.0f;
    float total_weight = 0.0f;

    const int steps = 16;
    for (int i = 0; i < steps; i++) {
        float angle = ((float)i + noise) * 6.283185f / (float)steps;
        float radius_scale = ((float)i + 0.5f) / (float)steps;
        radius_scale = radius_scale * radius_scale;

        float2 sample_offset = (tangent * cos(angle) +
                                bitangent * sin(angle)).xy;
        sample_offset *= g_push.u_ssgi_radius * radius_scale;
        float2 sample_uv = uv + sample_offset /
                           float2(g_push.u_ssgi_sw, g_push.u_ssgi_sh);

        if (sample_uv.x < 0.0f || sample_uv.x > 1.0f ||
            sample_uv.y < 0.0f || sample_uv.y > 1.0f)
            continue;

        float sample_depth = g_depth.Sample(g_smp0, sample_uv).r;
        if (sample_depth >= 1.0f) continue;

        float3 sample_pos = view_pos_from_depth(sample_uv, sample_depth);
        float3 diff = sample_pos - p;
        float dist = length(diff);
        float3 sample_dir = diff / max(dist, 0.001f);

        float n_dot_d = max(dot(nrm, sample_dir), 0.0f);
        if (n_dot_d < 0.01f) continue;

        float falloff = 1.0f / (1.0f + dist * dist * 0.05f);

        float3 sample_color = g_color.Sample(g_smp1, sample_uv).rgb;

        gi += sample_color * n_dot_d * falloff * 2.0f;
        total_weight += falloff;
    }

    if (total_weight > 0.0f) gi /= total_weight;

    gi *= g_push.u_ssgi_intensity;

    return float4(gi, 1.0f);
}
