// water_mrt_hlsl.frag - water plane PS, FORWARD_MRT twin of water_hlsl.frag
// (D3D12 hand-authored sidecar). Twin of shaders/water.frag (the GL variant, NOT water_vk.frag):
// the loose `uniform`s the GL twin declares become the root-constant block,
// and the GL `layout(binding = 1) uniform sampler2D u_shadow_map` becomes the
// register the engine actually writes -- water_render binds the shadow atlas
// with rhi_cmd_bind_texture(..., unit 1), and rhi_cmd_bind_texture indexes
// pd->image_root_params[unit], so unit 1 must be register t1. The root-
// constant struct is declared byte-identically to the vertex sidecar (one
// shared block); only the markers this stage actually reads are published
// here. The MRT twin of this file is water_mrt_hlsl.frag.
struct PushConsts {
    float4x4 u_view;         //   0
    float4x4 u_proj;         //  64
    float4x4 u_light_vp;     // 128
    float3   u_camera_pos;   // 192
    float    u_time;         // 204
    float3   u_water_color;  // 208
    float    u_shadow_bias;  // 220
    float    u_water_y;      // 224
};                           // tail ends at 228, 16B-aligned to 240
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_light_vp 128
// rhi:uniform u_camera_pos 192
// rhi:uniform u_time 204
// rhi:uniform u_water_color 208
// rhi:uniform u_shadow_bias 220
// rhi:uniform u_water_y 224

Texture2D g_shadow : register(t1, space0);   /* sampler2D u_shadow_map */
SamplerState g_smp : register(s1, space0);    /* static sampler for t1 */

float water_shadow(float3 wp) {
    float4 clip = mul(g_push.u_light_vp, float4(wp, 1.0f));
    float3 ndc = clip.xyz / clip.w;
    float2 uv = ndc.xy * 0.5f + 0.5f;
    if (uv.x < 0.0f || uv.x > 1.0f || uv.y < 0.0f || uv.y > 1.0f) return 1.0f;
    /* u_light_vp is CSM cascade 0 -> quadrant (0,0) of the shadow atlas. */
    uint tw, th, levels;
    g_shadow.GetDimensions(0, tw, th, levels);
    float2 texel = 1.0f / float2(tw, th);
    float2 atlas_uv = clamp(uv * 0.5f, texel, 0.5f - texel);
    float z = ndc.z * 0.5f + 0.5f; /* R211-A: window depth */
    return (z - g_push.u_shadow_bias) > g_shadow.Sample(g_smp, atlas_uv).r
               ? 0.5f : 1.0f;
}

struct PSOut {
    float4 color : SV_Target0;
    float2 velocity : SV_Target1;   /* GLSL layout(location = 1) */
};
PSOut main(float4 pos : SV_Position, float3 world : TEXCOORD0,
           float2 velocity : TEXCOORD1) {
    float3 cam = g_push.u_camera_pos;
    float dist = length(world.xz - cam.xz);
    float fade = 1.0f - smoothstep(10.0f, 50.0f, dist);

    float wave1 = sin(world.x * 0.8f + g_push.u_time * 1.2f) * 0.15f;
    float wave2 = sin(world.z * 1.1f + g_push.u_time * 0.9f) * 0.1f;
    float wave3 = sin((world.x + world.z) * 0.5f + g_push.u_time * 1.5f) * 0.08f;
    float wave = (wave1 + wave2 + wave3) * fade;

    float _wf = 1.0f - max(dot(normalize(cam - world), float3(0.0f, 1.0f, 0.0f)), 0.0f);
    float fresnel = 0.04f + 0.96f * (_wf * _wf * _wf);

    float3 deep = g_push.u_water_color * 0.5f;
    float3 surface = g_push.u_water_color * 1.2f
                   + float3(0.05f, 0.08f, 0.1f) * wave;
    float3 color = lerp(deep, surface, fresnel * fade);

    float shadow = water_shadow(world);
    color *= shadow;

    float depth_darken = 1.0f;
    if (cam.y < g_push.u_water_y) {
        depth_darken = clamp(1.0f - (g_push.u_water_y - cam.y) * 0.15f, 0.2f, 1.0f);
    }
    color *= depth_darken;

    float specular = max(0.0f, sin(world.x * 3.0f + g_push.u_time * 2.0f)
                              * sin(world.z * 2.5f + g_push.u_time * 1.7f));
    specular *= specular; specular *= specular;
    specular *= specular; specular *= specular;
    specular *= specular; specular *= specular;
    specular *= 0.4f * fade;
    color += float3(specular, specular, specular);

    float alpha = lerp(0.5f, 0.85f, fresnel) * fade;
    PSOut o;
    o.color = float4(color, alpha);
    o.velocity = velocity;
    return o;
}
