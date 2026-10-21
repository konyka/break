// debug_viz_hlsl.frag - depth / normal / AO / cascade debug views
// (D3D12 hand-authored sidecar of shaders/debug_viz.frag, the GL variant).
//
// Seven push constants in the GLSL declaration order. debug_viz_apply binds
// through rhi_cmd_bind_material_textures with the input colour as albedo
// (unit 0, t0) and the scene depth as shadow (unit 1, t1) -- the GLSL
// layout(binding = 0/1). textureSize(depth_tex, 0) is GetDimensions.
struct PushConsts {
    int   u_dv_mode;    //  0
    float u_dv_near;    //  4
    float u_dv_far;     //  8
    float u_dv_split0;  // 12
    float u_dv_split1;  // 16
    float u_dv_split2;  // 20
    float u_dv_split3;  // 24
};                      // tail at 28
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_dv_mode 0
// rhi:uniform u_dv_near 4
// rhi:uniform u_dv_far 8
// rhi:uniform u_dv_split0 12
// rhi:uniform u_dv_split1 16
// rhi:uniform u_dv_split2 20
// rhi:uniform u_dv_split3 24

Texture2D g_tex   : register(t0, space0);
Texture2D g_depth : register(t1, space0);
SamplerState g_smp0 : register(s0, space0);
SamplerState g_smp1 : register(s1, space0);

float3 normals_from_depth(float2 uv) {
    uint tw, th, levels;
    g_depth.GetDimensions(0u, tw, th, levels);
    float2 ts = 1.0f / float2(tw, th);
    float d0 = g_depth.Sample(g_smp1, uv).r;
    float dx = g_depth.Sample(g_smp1, uv + float2(ts.x, 0.0f)).r;
    float dy = g_depth.Sample(g_smp1, uv + float2(0.0f, ts.y)).r;
    float3 p0 = float3(uv, d0) * 2.0f - 1.0f;
    float3 p1 = float3(uv + float2(ts.x, 0.0f), dx) * 2.0f - 1.0f;
    float3 p2 = float3(uv + float2(0.0f, ts.y), dy) * 2.0f - 1.0f;
    float3 n = normalize(cross(p1 - p0, p2 - p0));
    return n * 0.5f + 0.5f;
}

float linearize(float d) {
    return g_push.u_dv_near * g_push.u_dv_far /
           (g_push.u_dv_far - d * (g_push.u_dv_far - g_push.u_dv_near));
}

float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    float3 result = (float3)0.0f;

    if (g_push.u_dv_mode == 0) {
        result = g_tex.Sample(g_smp0, uv).rgb;
    } else if (g_push.u_dv_mode == 1) {
        float linear_d = linearize(g_depth.Sample(g_smp1, uv).r);
        float viz = clamp(linear_d / g_push.u_dv_far, 0.0f, 1.0f);
        result = lerp(float3(0.0f, 0.0f, 1.0f), float3(1.0f, 0.0f, 0.0f), viz);
    } else if (g_push.u_dv_mode == 2) {
        result = normals_from_depth(uv);
    } else if (g_push.u_dv_mode == 3) {
        result = g_tex.Sample(g_smp0, uv).rrr;
    } else if (g_push.u_dv_mode == 4) {
        float linear_d = linearize(g_depth.Sample(g_smp1, uv).r);
        float3 cascade_colors[4];
        cascade_colors[0] = float3(1.0f, 0.2f, 0.2f);
        cascade_colors[1] = float3(0.2f, 1.0f, 0.2f);
        cascade_colors[2] = float3(0.2f, 0.4f, 1.0f);
        cascade_colors[3] = float3(1.0f, 1.0f, 0.2f);
        float splits[4];
        splits[0] = g_push.u_dv_split0; splits[1] = g_push.u_dv_split1;
        splits[2] = g_push.u_dv_split2; splits[3] = g_push.u_dv_split3;
        result = cascade_colors[3];
        for (int i = 0; i < 4; i++) {
            if (linear_d < splits[i]) {
                result = cascade_colors[i];
                break;
            }
        }
    }

    return float4(result, 1.0f);
}
