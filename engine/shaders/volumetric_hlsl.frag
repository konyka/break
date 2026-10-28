// volumetric_hlsl.frag - 16-step view-space fog march with height falloff,
// self-composited over the frame chain (D3D12 hand-authored sidecar of
// shaders/volumetric.frag, the GL variant).
//
// Three textures at t0..t2 because volumetric_apply binds {depth, shadow,
// scene} with rhi_cmd_bind_textures_multi (textures[i] -> unit i), R221-B /
// R550-A. The shadow is read once at the SCREEN uv as a plain .r value
// (> 0.01 lit), not projected into light space; on D3D12 the shadow atlas
// reaches t1 through the R32_FLOAT SRV alias of its typeless depth, the
// route the shadow-atlas test proves.
//
// Push block 232 bytes = 58 DWORDs; three descriptor tables leave 61. The
// three matrices go first so the floats pack behind them with no hole.
// u_vol_sw / u_vol_sh are declared by the GLSL twin but never read, so GL's
// linker drops them and volumetric_init resolves -1; they have no member
// and no marker here, for the same result (the _vk twin keeps them, which is
// why its inv_view sits at 176 instead).
//
// Matrices are uploaded column-major whole, so GLSL M * v is mul(M, v) with
// no transpose (ssr_hlsl.frag). Depth is decoded as depth * 2 - 1, the GL
// window-depth convention R621 made the D3D12 forward pass write too.
struct PushConsts {
    float4x4 u_vol_inv_proj;  //   0
    float4x4 u_vol_view;      //  64
    float4x4 u_vol_inv_view;  // 128
    float    u_vol_ldx;       // 192
    float    u_vol_ldy;       // 196
    float    u_vol_ldz;       // 200
    float    u_vol_lcx;       // 204
    float    u_vol_lcy;       // 208
    float    u_vol_lcz;       // 212
    float    u_vol_density;   // 216
    float    u_vol_fog_r;     // 220
    float    u_vol_fog_g;     // 224
    float    u_vol_fog_b;     // 228
};                            // tail at 232
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_vol_inv_proj 0
// rhi:uniform u_vol_view 64
// rhi:uniform u_vol_inv_view 128
// rhi:uniform u_vol_ldx 192
// rhi:uniform u_vol_ldy 196
// rhi:uniform u_vol_ldz 200
// rhi:uniform u_vol_lcx 204
// rhi:uniform u_vol_lcy 208
// rhi:uniform u_vol_lcz 212
// rhi:uniform u_vol_density 216
// rhi:uniform u_vol_fog_r 220
// rhi:uniform u_vol_fog_g 224
// rhi:uniform u_vol_fog_b 228

Texture2D g_depth  : register(t0, space0);
Texture2D g_shadow : register(t1, space0);
Texture2D g_scene  : register(t2, space0);
SamplerState g_smp0 : register(s0, space0);
SamplerState g_smp1 : register(s1, space0);
SamplerState g_smp2 : register(s2, space0);

float3 view_pos_from_depth(float2 uv, float depth) {
    float4 clip = float4(uv * 2.0f - 1.0f, depth * 2.0f - 1.0f, 1.0f);
    float4 view_h = mul(g_push.u_vol_inv_proj, clip);
    return view_h.xyz / view_h.w;
}

float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    float depth = g_depth.Sample(g_smp0, uv).r;

    float3 ray_start = (float3)0.0f;
    float3 ray_end = view_pos_from_depth(uv, depth);
    float ray_length = length(ray_end - ray_start);

    if (depth >= 1.0f) {
        ray_end = view_pos_from_depth(uv, 0.999f) * 5.0f;
        ray_length = length(ray_end);
    }

    float3 ray_dir = ray_length > 0.001f ? (ray_end - ray_start) / ray_length
                                         : float3(0.0f, 0.0f, -1.0f);

    const int steps = 16;
    float step_size = ray_length / (float)steps;

    float3 fog_color = float3(g_push.u_vol_fog_r, g_push.u_vol_fog_g, g_push.u_vol_fog_b);
    float3 light_dir = normalize(mul(g_push.u_vol_view,
        float4(g_push.u_vol_ldx, g_push.u_vol_ldy, g_push.u_vol_ldz, 0.0f)).xyz);
    float light_amount = max(dot(-ray_dir, light_dir), 0.0f);

    float3 accum = (float3)0.0f;
    float transmittance = 1.0f;

    float shadow = g_shadow.Sample(g_smp1, uv).r;
    float light_visibility = shadow > 0.01f ? 1.0f : 0.15f;
    float3 lighting = fog_color * 0.3f +
        float3(g_push.u_vol_lcx, g_push.u_vol_lcy, g_push.u_vol_lcz) *
        light_amount * light_visibility;
    for (int i = 0; i < steps; i++) {
        float t = ((float)i + 0.5f) * step_size;
        float3 p = ray_start + ray_dir * t;

        float density = g_push.u_vol_density;
        float world_y = mul(g_push.u_vol_inv_view, float4(p, 1.0f)).y;
        float height_factor = exp(-world_y * 0.3f);
        density *= max(height_factor, 0.0f);

        if (density < 0.0001f) continue;

        float fog_amount = density * step_size;
        accum += lighting * transmittance * fog_amount;
        transmittance *= 1.0f - fog_amount;
        transmittance = max(transmittance, 0.0f);
    }

    float3 scene = g_scene.Sample(g_smp2, uv).rgb;
    return float4(scene * transmittance + accum, 1.0f);
}
