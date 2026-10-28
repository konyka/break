// god_rays_hlsl.frag - 32-step screen-space light shafts toward the sun
// (D3D12 hand-authored sidecar of shaders/god_rays.frag, the GL variant).
//
// Two textures: god_rays_apply binds through rhi_cmd_bind_material_textures
// with the scene as albedo (unit 0, t0) and the depth as shadow (unit 1,
// t1) -- the GLSL layout(binding = 0/1), R217-B.
//
// Three floats of push block. u_gr_sw / u_gr_sh are declared by the GLSL
// twin but never read, so GL's linker drops them and god_rays_init resolves
// -1; they have no member and no marker here, for the same result. The march
// samples inside a loop with a data-dependent break, so it uses SampleLevel
// 0 (single-mip depth, the LOD texture() selects on GL).
struct PushConsts {
    float u_gr_sun_x;      //  0
    float u_gr_sun_y;      //  4
    float u_gr_intensity;  //  8
};                         // tail at 12
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_gr_sun_x 0
// rhi:uniform u_gr_sun_y 4
// rhi:uniform u_gr_intensity 8

Texture2D g_scene : register(t0, space0);
Texture2D g_depth : register(t1, space0);
SamplerState g_smp0 : register(s0, space0);
SamplerState g_smp1 : register(s1, space0);

float4 main(float4 pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    float2 sun_uv = float2(g_push.u_gr_sun_x, g_push.u_gr_sun_y);
    float2 delta = (uv - sun_uv) / 32.0f;

    float3 scene = g_scene.Sample(g_smp0, uv).rgb;

    float illum = 0.0f;
    float2 ray = uv;

    for (int i = 0; i < 32; i++) {
        ray -= delta;
        if (ray.x < 0.0f || ray.x > 1.0f || ray.y < 0.0f || ray.y > 1.0f) break;

        float d = g_depth.SampleLevel(g_smp1, ray, 0.0f).r;
        if (d >= 1.0f) {
            float dist = 1.0f - (float)i / 32.0f;
            illum += dist * dist;
        }
    }
    illum /= 32.0f;
    illum *= g_push.u_gr_intensity;

    float sun_dist = length(uv - sun_uv);
    float mask = 1.0f - smoothstep(0.0f, 0.8f, sun_dist);

    float3 rays = scene * illum * mask * 2.0f;

    return float4(clamp(scene + rays, 0.0f, 1.0f), 1.0f);
}
