// ssao_hlsl.frag - horizon-based ambient occlusion, 4 directions x 6 steps
// (D3D12 hand-authored sidecar of shaders/ssao.frag, the GL variant).
//
// u_ssao_proj is declared by the GLSL twin but never read there, so GL's
// linker drops it and ssao_init resolves -1; it is left out of this push
// block for the same result (and 16 DWORDs of root budget). The block is
// 80 bytes: the matrix first, the four floats packed into the slot after it.
//
// One texture, t0 depth: ssao_apply binds it with rhi_cmd_bind_texture(...,
// unit 0). Depth is decoded as depth * 2 - 1, the GL window-depth convention
// that R621 made the D3D12 forward pass write too.
//
// dFdx / dFdy are the FINE derivatives, ddx_fine / ddy_fine here (see
// ssr_hlsl.frag). gl_FragCoord.xy is SV_Position.xy: offscreen targets keep
// NDC y = -1 on memory row 0 on both backends, so the noise sees the same
// pixel coordinates. The march samples inside a loop with a data-dependent
// continue, so it uses SampleLevel 0 -- the depth target has one mip, which
// is what texture() selects on GL too.
struct PushConsts {
    float4x4 u_ssao_inv_proj;  //  0
    float    u_ssao_sw;        // 64
    float    u_ssao_sh;        // 68
    float    u_ssao_radius;    // 72
    float    u_ssao_bias;      // 76
};                             // tail at 80
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_ssao_inv_proj 0
// rhi:uniform u_ssao_sw 64
// rhi:uniform u_ssao_sh 68
// rhi:uniform u_ssao_radius 72
// rhi:uniform u_ssao_bias 76

Texture2D g_depth : register(t0, space0);
SamplerState g_smp0 : register(s0, space0);

float3 reconstruct_pos(float2 uv, float depth) {
    float4 ndc = float4(uv * 2.0f - 1.0f, depth * 2.0f - 1.0f, 1.0f);
    float4 view_h = mul(g_push.u_ssao_inv_proj, ndc);
    return view_h.xyz / view_h.w;
}

float3 reconstruct_normal(float3 p) {
    return normalize(cross(ddx_fine(p), ddy_fine(p)));
}

float interleaved_gradient_noise(float2 p) {
    float3 magic = float3(0.06711056f, 0.00583715f, 52.9829189f);
    return frac(magic.z * frac(dot(p, magic.xy)));
}

float4 main(float4 frag_pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    float depth = g_depth.Sample(g_smp0, uv).r;
    if (depth >= 1.0f)
        return (float4)1.0f;

    float3 p = reconstruct_pos(uv, depth);
    float3 normal = reconstruct_normal(p);

    float2 noise_scale = float2(g_push.u_ssao_sw, g_push.u_ssao_sh);
    float noise = interleaved_gradient_noise(frag_pos.xy);

    float3 view = normalize(-p);

    float ao = 0.0f;

    const int directions = 4;
    const int steps = 6;

    for (int d = 0; d < directions; d++) {
        float angle = ((float)d + noise) * 3.14159265f / (float)directions;
        float2 dir = float2(cos(angle), sin(angle));

        float horizon_neg = 1.0f;
        float horizon_pos = -1.0f;

        for (int s = 0; s < steps; s++) {
            float t = ((float)s + 0.5f) / (float)steps;
            t *= g_push.u_ssao_radius;
            float2 sample_uv = uv + dir * t / noise_scale;
            if (sample_uv.x < 0.0f || sample_uv.x > 1.0f ||
                sample_uv.y < 0.0f || sample_uv.y > 1.0f) continue;

            float sd = g_depth.SampleLevel(g_smp0, sample_uv, 0.0f).r;
            if (sd >= 1.0f) continue;
            float3 sp = reconstruct_pos(sample_uv, sd);

            float3 diff = sp - p;
            float dist = length(diff);
            float3 sv = diff / max(dist, 0.001f);

            float cos_h = dot(view, sv);

            if (cos_h > horizon_pos) horizon_pos = cos_h;
            if (cos_h < horizon_neg) horizon_neg = cos_h;
        }

        float3 tangent = float3(dir.x, dir.y, 0.0f);
        float3 bitangent = normalize(cross(view, tangent));
        float3 n_proj = normal - bitangent * dot(normal, bitangent);

        float n_len = length(n_proj);
        float cos_n = n_len > 0.001f ? dot(normalize(n_proj), view) : 0.0f;

        float h2 = clamp(horizon_pos + g_push.u_ssao_bias, -1.0f, 1.0f);

        float a1 = acos(clamp(cos_n, -1.0f, 1.0f));
        float a2 = acos(clamp(h2, -1.0f, 1.0f));

        float contrib = (sin(a2) - sin(a1)) * 0.5f + (a2 - a1) * cos_n;
        contrib = max(contrib, 0.0f);

        ao += contrib;
    }

    ao = 1.0f - ao / (float)directions * 2.0f;

    return float4(clamp(ao, 0.0f, 1.0f), 0.0f, 0.0f, 1.0f);
}
