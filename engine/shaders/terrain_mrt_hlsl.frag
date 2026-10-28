// terrain_mrt_hlsl.frag - terrain PS, FORWARD_MRT twin of terrain_hlsl.frag
// (D3D12 hand-authored sidecar). Twin of shaders/terrain.frag (the GL variant, NOT terrain_vk.frag): the GL
// twin declares u_light_dir / u_light_color / u_ambient as GLSL *consts*, so
// they are consts here too and get no rhi:uniform marker -- the engine writes
// exactly these values from terrain_render, so resolve() returning -1 for them
// costs nothing and the GL/VK/D3D12 pixels agree. The root-constant struct is
// declared byte-identically to the vertex sidecar (one shared block); only the
// markers this stage actually reads are published here. The MRT twin of this
// file is terrain_mrt_hlsl.frag.
//
// u_albedo is declared but never sampled in the GL twin (the four procedural
// colour functions below are the whole albedo), and a GLSL compiler drops the
// inactive binding, so no t0 is declared here either. That is also what keeps
// this pipeline to ONE descriptor table -- two tables would clamp the root-
// constant range to 248 bytes and drop u_fog_strength@216+4. The shadow atlas
// is register t1 because terrain_render reaches it through
// rhi_cmd_bind_material_textures, whose shadow argument is material unit 1.
struct PushConsts {
    float4x4 u_view;          //   0
    float4x4 u_proj;          //  64
    float4x4 u_light_vp;      // 128
    float3   u_camera_pos;    // 192
    float    u_time;          // 204
    float    u_water_y;       // 208
    float    u_shadow_bias;   // 212
    float    u_fog_strength;  // 216
};                            // tail ends at 220, 16B-aligned to 224
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_light_vp 128
// rhi:uniform u_camera_pos 192
// rhi:uniform u_time 204
// rhi:uniform u_water_y 208
// rhi:uniform u_shadow_bias 212
// rhi:uniform u_fog_strength 216

Texture2D g_shadow : register(t1, space0);   /* sampler2D u_shadow_map */
SamplerState g_smp : register(s1, space0);    /* static sampler for t1 */

/* R88-2: Pre-normalized (length=0.98995) -- avoids per-fragment normalize() */
static const float3 u_light_dir = float3(0.5050763f, -0.8081220f, 0.3030458f);
static const float3 u_light_color = float3(1.0f, 0.95f, 0.9f);
static const float3 u_ambient = float3(0.35f, 0.35f, 0.40f);

float terrain_shadow(float3 world_pos) {
    float4 clip = mul(g_push.u_light_vp, float4(world_pos, 1.0f));
    float3 ndc = clip.xyz / clip.w;
    float2 uv = ndc.xy * 0.5f + 0.5f;
    if (uv.x < 0.0f || uv.x > 1.0f || uv.y < 0.0f || uv.y > 1.0f) return 1.0f;
    /* u_light_vp is CSM cascade 0 -> quadrant (0,0) of the shadow atlas. */
    uint tw, th, levels;
    g_shadow.GetDimensions(0, tw, th, levels);
    float2 texel = 1.0f / float2(tw, th);
    float2 atlas_uv = clamp(uv * 0.5f, texel, 0.5f - texel);
    float d = g_shadow.Sample(g_smp, atlas_uv).r;
    /* R211-A: Compare in window depth [0,1]; ndc.z is OpenGL NDC [-1,1]. */
    float z = ndc.z * 0.5f + 0.5f;
    return (z - g_push.u_shadow_bias) > d ? 0.4f : 1.0f;
}

float3 grass_color(float2 uv) {
    float pattern = sin(uv.x * 80.0f) * sin(uv.y * 80.0f) * 0.03f;
    return float3(0.22f + pattern, 0.45f + pattern * 2.0f, 0.12f + pattern);
}

float3 rock_color(float2 uv) {
    float noise = frac(sin(dot(uv * 50.0f, float2(12.9898f, 78.233f))) * 43758.5453f);
    return float3(0.35f + noise * 0.08f, 0.32f + noise * 0.06f, 0.28f + noise * 0.05f);
}

float3 snow_color(float2 uv) {
    float sparkle = frac(sin(dot(uv * 200.0f, float2(93.989f, 67.345f))) * 23421.631f);
    return float3(0.85f + sparkle * 0.1f, 0.88f + sparkle * 0.08f, 0.92f + sparkle * 0.06f);
}

float3 sand_color(float2 uv) {
    float grain = frac(sin(dot(uv * 60.0f, float2(45.164f, 23.891f))) * 17645.234f);
    return float3(0.76f + grain * 0.04f, 0.70f + grain * 0.03f, 0.50f + grain * 0.03f);
}

struct PSOut {
    float4 color : SV_Target0;
    float2 velocity : SV_Target1;   /* GLSL layout(location = 1) */
};
PSOut main(float4 pos : SV_Position, float3 world : TEXCOORD0,
           float3 normal : TEXCOORD1, float2 uv : TEXCOORD2,
           float2 velocity : TEXCOORD3) {
    float3 N = normalize(normal);
    float3 L = -u_light_dir; /* R88-2: already normalized */
    float3 V = normalize(g_push.u_camera_pos - world);
    float3 H = normalize(L + V);

    float slope = 1.0f - N.y;
    float height = world.y;

    float grass_w = 1.0f - smoothstep(0.0f, 0.5f, slope);
    float rock_w = smoothstep(0.3f, 0.7f, slope);
    float snow_w = smoothstep(3.5f, 5.5f, height) * (1.0f - smoothstep(0.5f, 0.8f, slope));
    float sand_w = smoothstep(1.5f, 0.0f, height) * grass_w;
    grass_w = grass_w * (1.0f - snow_w) * (1.0f - sand_w);
    rock_w = rock_w * (1.0f - snow_w);

    float total = grass_w + rock_w + snow_w + sand_w;
    if (total < 0.001f) total = 1.0f;

    float3 albedo = (grass_color(uv) * grass_w +
                     rock_color(uv) * rock_w +
                     snow_color(uv) * snow_w +
                     sand_color(uv) * sand_w) / total;

    float diff = max(dot(N, L), 0.0f);
    float spec = max(dot(N, H), 0.0f);
    spec *= spec; spec *= spec; spec *= spec; spec *= spec; spec *= spec;
    spec = spec * rock_w / total;
    float shadow = terrain_shadow(world);

    float3 color = albedo * (u_ambient + u_light_color * diff * shadow)
                 + u_light_color * spec * shadow * 0.15f;

    float shore_dist = world.y - g_push.u_water_y;
    float foam = smoothstep(0.8f, 0.0f, shore_dist)
               * (1.0f - smoothstep(-0.3f, -0.8f, shore_dist));
    foam *= 0.4f + 0.3f * sin(world.x * 6.0f + g_push.u_camera_pos.x * 0.1f)
                     * sin(world.z * 5.0f + g_push.u_camera_pos.z * 0.1f);
    color = lerp(color, float3(0.85f, 0.9f, 0.95f), foam * 0.6f);

    if (world.y < g_push.u_water_y) {
        float c1 = sin(world.x * 2.5f + g_push.u_time * 0.8f)
                 * sin(world.z * 2.3f - g_push.u_time * 0.6f);
        float c2 = sin(world.x * 3.7f - g_push.u_time * 1.1f)
                 * sin(world.z * 3.1f + g_push.u_time * 0.9f);
        float caustic = max(0.0f, (c1 + c2) * 0.5f);
        caustic *= caustic; caustic *= caustic; caustic *= 0.4f;
        float depth = clamp((g_push.u_water_y - world.y) * 0.5f, 0.0f, 1.0f);
        color += float3(0.15f, 0.25f, 0.3f) * caustic * depth;
        color *= lerp(1.0f, 0.6f, depth * 0.4f);
    }

    float fog_dist = length(world - g_push.u_camera_pos);
    float fog = clamp((fog_dist - 40.0f) / 60.0f, 0.0f, 1.0f);
    color = lerp(color, u_ambient * 1.5f, fog * g_push.u_fog_strength);

    PSOut o;
    o.color = float4(color, 1.0f);
    o.velocity = velocity;
    return o;
}
