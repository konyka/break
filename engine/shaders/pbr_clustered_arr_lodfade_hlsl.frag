// pbr_clustered_arr_hlsl.frag - clustered forward PBR, TEXTURE-ARRAY pixel
// stage (D3D12 hand-authored sidecar of shaders/pbr_clustered.frag built with
// CLUSTERED_ARR). Same as pbr_clustered_hlsl.frag except: the albedo,
// metallic-roughness, normal, emissive and occlusion registers are
// Texture2DArray and are sampled at the layer the vertex stage forwards
// (nointerpolation uint layer, the indirect first_instance), and the per-layer
// material factors come from two 64-entry tables appended to the b1 cbuffer
// at offsets 304 and 1328 (the GL variant keeps them at 192/1216 of its own
// UBO; here the frame constants occupy 0..304). The push block keeps the
// static variant's shape so the two share a root signature layout, but its
// material members are unused: the tables replace them.
//
// Original header of the static variant follows.
//
// Same registers as the GL unit map (rhi_cmd_bind_material_textures_ibl):
//   t0 albedo   t1 shadow atlas   t2 metallic-roughness   t3 normal map
//   t4 emissive t5 light data     t6 light grid           t7 BRDF LUT
//   t8 irradiance cube  t9 prefiltered cube  t10..t13 point-shadow cubes
//   t14 SSAO    t15 occlusion
// One SamplerState serves every texture: the backend's static sampler is
// LINEAR + WRAP for all of them, which is also what the GL path binds here
// (the engine's LINEAR + REPEAT material sampler).
//
// The frame constants (camera, ambient, fog, cluster setup, counts, shadow
// bias, far planes) are in the b1 cbuffer, not the push block -- the 17
// descriptor tables leave 47 root DWORDs, and u_model / u_view / the
// per-material factors use 40 of them. PushConsts and ClusterFrame are
// declared byte-identically in the vertex sidecar.
//
// Left out, as in the other D3D12 forward sidecars: POM. The engine writes
// u_pom_enabled = 0 on every backend, so the branch is dead code.
struct PushConsts {
    float4x4 u_model;              //   0
    float4x4 u_view;               //  64
    float2   u_mr_factor;          // 128
    float    u_occlusion_strength; // 136
    float3   u_emissive_factor;    // 144
};                                 // tail at 156
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_mr_factor 128
// rhi:uniform u_occlusion_strength 136
// rhi:uniform u_emissive_factor 144

struct ClusterFrame {
    float4x4 prev_vp;              //   0
    float4x4 prev_model;           //  64
    float4x4 proj;                 // 128
    float4   camera_pos;           // 192 xyz
    float4   ambient;              // 208 xyz (unused: the GLSL declares it too)
    float4   fog_color;            // 224 xyz
    float4   fog;                  // 240 x near, y far, z underwater, w pom
    float4   screen;               // 256 x w, y h, z near, w far
    float4   counts;               // 272 x point, y dir, z shadow_bias
    float4   far_planes;           // 288
    float4   layer_factor[64];     // 304 x metallic, y roughness, z AO strength, w flag
    float4   layer_emissive[64];   // 1328 rgb factor x strength
};                                 // tail at 2352
ConstantBuffer<ClusterFrame> g_frame : register(b1, space0);

Texture2DArray g_albedo : register(t0, space0);
Texture2D g_shadow_map   : register(t1, space0);
Texture2DArray g_mr     : register(t2, space0);
Texture2DArray g_normal_map : register(t3, space0);
Texture2DArray g_emissive : register(t4, space0);
StructuredBuffer<float4> g_light_data : register(t5, space0);
StructuredBuffer<float4> g_light_grid : register(t6, space0);
Texture2D   g_brdf_lut        : register(t7, space0);
TextureCube g_irradiance_map  : register(t8, space0);
TextureCube g_prefilter_map   : register(t9, space0);
TextureCube g_point_shadow0   : register(t10, space0);
TextureCube g_point_shadow1   : register(t11, space0);
TextureCube g_point_shadow2   : register(t12, space0);
TextureCube g_point_shadow3   : register(t13, space0);
Texture2D g_ssao         : register(t14, space0);
Texture2DArray g_occlusion : register(t15, space0);
SamplerState g_smp       : register(s0, space0);

static const float PI = 3.14159265359f;

struct PointLight { float3 pos; float radius; float3 color; float shadow_index; };
struct DirLight   { float3 dir; float3 color; };

PointLight read_point_light(int index) {
    int base = index * 2;
    float4 d0 = g_light_data[base];
    float4 d1 = g_light_data[base + 1];
    PointLight l;
    l.pos = d0.xyz; l.radius = d0.w; l.color = d1.xyz; l.shadow_index = d1.w;
    return l;
}
DirLight read_dir_light(int index) {
    int base = (256 * 2) + index * 2;   // R644: dir lights start at texel 512
    float4 d0 = g_light_data[base];
    float4 d1 = g_light_data[base + 1];
    DirLight l;
    l.dir = d0.xyz; l.color = d1.xyz;
    return l;
}
uint grid_u32(uint k) {
    return asuint(g_light_grid[k >> 2u][k & 3u]);
}

float D_GGX(float NdotH, float roughness) {
    float a = roughness * roughness;
    float a2 = a * a;
    float d = NdotH * NdotH * (a2 - 1.0f) + 1.0f;
    return a2 / (PI * d * d);
}
float3 F_Schlick(float cos_theta, float3 F0) {
    float t = clamp(1.0f - cos_theta, 0.0f, 1.0f);
    return F0 + (1.0f - F0) * (t * t * t * t * t);
}
float G_SmithGGX(float NdotV, float NdotL, float roughness) {
    float r = roughness + 1.0f;
    float k = (r * r) / 8.0f;
    return (NdotV / (NdotV * (1.0f - k) + k)) * (NdotL / (NdotL * (1.0f - k) + k));
}
float3 cook_torrance_brdf(float3 N, float3 V, float3 L, float3 radiance,
                          float3 albedo, float metallic, float roughness) {
    float3 H = normalize(V + L);
    float NdotH = max(dot(N, H), 0.0f);
    float NdotV = max(dot(N, V), 0.0f);
    float NdotL = max(dot(N, L), 0.0f);
    float HdotV = max(dot(H, V), 0.0f);
    float3 F0 = lerp((float3)0.04f, albedo, metallic);
    float D = D_GGX(NdotH, roughness);
    float3 F = F_Schlick(HdotV, F0);
    float G = G_SmithGGX(NdotV, NdotL, roughness);
    float3 specular = (D * F * G) / (4.0f * NdotV * NdotL + 0.0001f);
    float3 kD = ((float3)1.0f - F) * (1.0f - metallic);
    return (kD * albedo / PI + specular) * radiance * NdotL;
}

static const int SHADOW_MATRIX_OFFSET = 520;
// GLSL mat4(c0..c3) takes the four texels as COLUMNS; HLSL float4x4(r0..r3)
// fills ROWS, so the texels build the transpose and mul(v, M) == M_glsl * v.
float4 cascade_mul(int cascade, float4 v) {
    int offset = SHADOW_MATRIX_OFFSET + cascade * 4;
    float4x4 m = float4x4(g_light_data[offset], g_light_data[offset + 1],
                          g_light_data[offset + 2], g_light_data[offset + 3]);
    return mul(v, m);
}
float sample_cascade(int cascade, float2 uv, float2 offset, float2 texel_size) {
    float2 q = float2((float)(cascade & 1), (float)(cascade >> 1));
    float2 qmin = q * 0.5f + texel_size;
    float2 qmax = (q + (float2)1.0f) * 0.5f - texel_size;
    float2 auv = (q + uv) * 0.5f + offset;
    return g_shadow_map.SampleLevel(g_smp, clamp(auv, qmin, qmax), 0.0f).r;
}
float find_blocker(int cascade, float2 uv, float compare, float2 texel_size,
                   float search_width) {
    float blocker_sum = 0.0f;
    int blocker_count = 0;
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            float d = sample_cascade(cascade, uv,
                float2(x, y) * texel_size * search_width, texel_size);
            if (d < compare - 0.002f) { blocker_sum += d; blocker_count++; }
        }
    }
    if (blocker_count == 0) return -1.0f;
    return blocker_sum / (float)blocker_count;
}
float pcf_shadow(int cascade, float2 uv, float compare, float2 texel_size,
                 float filter_radius) {
    float shadow = 0.0f;
    float bias = g_frame.counts.z;
    int samples = clamp((int)ceil(filter_radius * 2.0f), 1, 5);
    for (int x = -samples; x <= samples; x++) {
        for (int y = -samples; y <= samples; y++) {
            float d = sample_cascade(cascade, uv,
                float2(x, y) * texel_size * filter_radius, texel_size);
            shadow += (compare - bias) > d ? 0.3f : 1.0f;
        }
    }
    float total = (float)((2 * samples + 1) * (2 * samples + 1));
    return shadow / total;
}
float shadow_test(float3 world_pos) {
    int cascade = -1;
    float3 ndc = (float3)0.0f;
    for (int i = 0; i < 4; i++) {
        float4 clip = cascade_mul(i, float4(world_pos, 1.0f));
        float3 n = clip.xyz / clip.w;
        float2 uv = n.xy * 0.5f + 0.5f;
        if (uv.x >= 0.0f && uv.x <= 1.0f && uv.y >= 0.0f && uv.y <= 1.0f) {
            cascade = i;
            ndc = n;
            break;
        }
    }
    if (cascade < 0) return 1.0f;
    float2 uv = ndc.xy * 0.5f + 0.5f;
    uint tw, th, levels;
    g_shadow_map.GetDimensions(0u, tw, th, levels);
    float2 texel_size = 1.0f / float2(tw, th);
    float z_win = ndc.z * 0.5f + 0.5f;
    float light_size = 0.02f * (1.0f + (float)cascade * 0.5f);
    float search_width = light_size / max(z_win, 1e-3f);
    float blocker = find_blocker(cascade, uv, z_win, texel_size, search_width);
    if (blocker < 0.0f) return 1.0f;
    float penumbra = (z_win - blocker) / max(blocker, 1e-3f);
    float filter_radius = clamp(penumbra * light_size * 40.0f, 1.0f, 5.0f);
    return pcf_shadow(cascade, uv, z_win, texel_size, filter_radius);
}

float point_shadow_test(float3 wpos, int shadow_idx, float3 light_pos,
                        float light_radius) {
    if (shadow_idx < 0 || shadow_idx > 3) return 1.0f;
    float3 frag_to_light = wpos - light_pos;
    float dist = length(frag_to_light);
    if (dist > light_radius) return 0.0f;
    float far_plane = g_frame.far_planes[shadow_idx];
    float compare = dist / max(far_plane, 1e-4f);
    float depth;
    if (shadow_idx == 0)      depth = g_point_shadow0.SampleLevel(g_smp, frag_to_light, 0.0f).r;
    else if (shadow_idx == 1) depth = g_point_shadow1.SampleLevel(g_smp, frag_to_light, 0.0f).r;
    else if (shadow_idx == 2) depth = g_point_shadow2.SampleLevel(g_smp, frag_to_light, 0.0f).r;
    else                      depth = g_point_shadow3.SampleLevel(g_smp, frag_to_light, 0.0f).r;
    return compare <= depth + g_frame.counts.z ? 1.0f : 0.15f;
}

float3 perturb_normal(float3 world, float3 N, float2 uv, float layer) {
    float3 map = g_normal_map.Sample(g_smp, float3(uv, layer)).rgb * 2.0f - 1.0f;
    float3 Q1 = ddx_fine(world);
    float3 Q2 = ddy_fine(world);
    float2 st1 = ddx_fine(uv);
    float2 st2 = ddy_fine(uv);
    float3 T = normalize(Q1 * st2.y - Q2 * st1.y);
    float3 B = -normalize(cross(N, T));
    // GLSL mat3(T, B, N) * map: T, B, N are the COLUMNS.
    return normalize(T * map.x + B * map.y + N * map.z);
}

struct PSOut {
    float4 color    : SV_Target0;
    float2 velocity : SV_Target1;
};

static const float k_lod_bayer[16] = { 0.0f, 8.0f, 2.0f, 10.0f, 12.0f, 4.0f, 14.0f, 6.0f,
                                       3.0f, 11.0f, 1.0f, 9.0f, 15.0f, 7.0f, 13.0f, 5.0f };
bool lod_fade_discard(float4 frag_pos, float fade) {
    if (fade == 0.0f) return false;
    uint2 p = uint2(frag_pos.xy) & 3u;
    float b = k_lod_bayer[p.y * 4u + p.x] + 0.5f;
    return fade > 0.0f ? (b > fade) : (b < -fade);
}
PSOut main(float4 frag_pos : SV_Position, float3 world : TEXCOORD0,
           float3 normal : TEXCOORD1, float2 uv : TEXCOORD2,
           float2 velocity : TEXCOORD3,
           nointerpolation uint layer_id : TEXCOORD4,
           nointerpolation float lod_fade : TEXCOORD5) {
    if (lod_fade_discard(frag_pos, lod_fade)) discard;
    float layer = (float)layer_id;
    float4 fac = g_frame.layer_factor[min(layer_id, 63u)];
    float4 efac = g_frame.layer_emissive[min(layer_id, 63u)];
    float3 cam = g_frame.camera_pos.xyz;
    float3 N = normalize(normal);
    float3 V = normalize(cam - world);

    float3 albedo = g_albedo.Sample(g_smp, float3(uv, layer)).rgb;
    float2 mr = g_mr.Sample(g_smp, float3(uv, layer)).bg * fac.xy;
    float metallic = mr.x;
    float roughness = mr.y;
    N = perturb_normal(world, N, uv, layer);
    float3 emissive = g_emissive.Sample(g_smp, float3(uv, layer)).rgb * efac.rgb;

    float3 F0 = lerp((float3)0.04f, albedo, metallic);
    float3 F_env = F_Schlick(max(dot(N, V), 0.0f), F0);
    float3 kD_env = ((float3)1.0f - F_env) * (1.0f - metallic);

    // HAS_IBL, line for line with the GLSL.
    float3 irradiance = g_irradiance_map.SampleLevel(g_smp, N, 0.0f).rgb;
    float3 diffuse_ibl = irradiance * albedo * kD_env;
    float3 R = reflect(-V, N);
    float lod = roughness * 4.0f;
    float3 prefiltered = g_prefilter_map.SampleLevel(g_smp, R, lod).rgb;
    float2 brdf = g_brdf_lut.SampleLevel(g_smp, float2(max(dot(N, V), 0.0f), roughness), 0.0f).rg;
    float3 specular_ibl = prefiltered * (F0 * brdf.x + brdf.y);

    float ao = g_ssao.Sample(g_smp, uv).r *
               lerp(1.0f, g_occlusion.Sample(g_smp, float3(uv, layer)).r,
                    clamp(fac.z, 0.0f, 1.0f));
    float3 color = (diffuse_ibl + specular_ibl) * ao;

    float dir_shadow = shadow_test(world);
    int dir_count = (int)g_frame.counts.y;
    for (int di = 0; di < dir_count; di++) {
        DirLight dl = read_dir_light(di);
        color += cook_torrance_brdf(N, V, -dl.dir, dl.color * dir_shadow,
                                    albedo, metallic, roughness);
    }

    float screen_w = g_frame.screen.x;
    float screen_h = g_frame.screen.y;
    float near_p = g_frame.screen.z;
    float far_p = g_frame.screen.w;
    if ((int)g_frame.counts.x > 0 && screen_w > 0.0f) {
        float4 vp = mul(g_push.u_view, float4(world, 1.0f));
        float ld = -vp.z;
        uint cx = min((uint)(frag_pos.x / (screen_w / 16.0f)), 15u);
        uint cy = min((uint)(frag_pos.y / (screen_h / 8.0f)), 7u);
        uint cz = min((uint)floor(24.0f * log2(max(ld / near_p, 1.0f)) /
                                  log2(far_p / near_p)), 23u);
        uint ci = cx + cy * 16u + cz * 128u;
        uint go = grid_u32(ci * 2u);
        uint gc = grid_u32(ci * 2u + 1u);
        uint gb = 16u * 8u * 24u * 2u;
        for (uint i = 0u; i < gc; i++) {
            int li = (int)grid_u32(gb + go + i);
            PointLight pl = read_point_light(li);
            float3 toL = pl.pos - world;
            float dist = length(toL);
            if (dist > pl.radius) continue;
            float3 L = toL / max(dist, 1e-3f);
            float att = 1.0f - dist / pl.radius;
            att *= att;
            float pshadow = point_shadow_test(world, (int)pl.shadow_index, pl.pos, pl.radius);
            color += cook_torrance_brdf(N, V, L, pl.color * att * pshadow,
                                        albedo, metallic, roughness);
        }
    }

    color += emissive;

    float fog_dist = length(world - cam);
    float fog_factor = clamp((fog_dist - g_frame.fog.x) /
                             max(g_frame.fog.y - g_frame.fog.x, 0.001f), 0.0f, 1.0f);
    color = lerp(color, g_frame.fog_color.xyz, fog_factor);
    if (g_frame.fog.z > 0.5f) {
        color = lerp(color, float3(0.0f, 0.15f, 0.25f), 0.35f);
        float uw_absorb = clamp(fog_dist * 0.02f, 0.0f, 0.6f);
        color *= (1.0f - uw_absorb);
        color.r *= 0.7f;
    }
    color = color / (color + (float3)1.0f);
    color = exp2(log2(max(color, (float3)0.0f)) * (1.0f / 2.2f));

    PSOut o;
    o.color = float4(color, 1.0f);
    o.velocity = velocity;
    return o;
}
