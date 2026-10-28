// deferred_light_hlsl.frag - deferred lighting pass, fragment stage
// (D3D12 hand-authored sidecar of shaders/deferred_light.frag, the GL
// variant). Decodes the G-Buffer and evaluates clustered point lights,
// directional lights with the 4-cascade PCSS shadow atlas, AO and emissive.
//
// Registers follow the GL unit map that rhi_cmd_bind_deferred_gbuf_textures
// binds on D3D12 (same as rhi_gl.c):
//   t0 albedo+metallic  t1 normal  t2 roughness/AO  t3 depth  t4 shadow atlas
//   t5 light data (texel buffer)   t6 light grid (texel buffer)
//   t10..t13 point-shadow depth cubes (R647)
//   t14 SSAO            t15 emissive
//
// R654: HAS_IBL is always on here (the GL loader injects it): t7 BRDF LUT,
// t8 irradiance cube, t9 prefiltered cube, read as the GLSL does. The D3D12
// binder fills them with a white LUT / black cubes when no IBL is supplied,
// which makes both IBL terms exactly 0 -- the GLSL #else branch.
//
// Root-signature budget: 17 descriptor tables + the 184-byte push block
// (46 DWORDs) = 63 of 64. The far-plane vector therefore starts at 168,
// in what used to be padding: two float2 halves keep it contiguous for the
// engine's single vec4 write without crossing a 16-byte row.
//
// The point-shadow cubes are the one place that uses Sample(), as GL does
// (LINEAR sampler, deferred.c): cube addressing is seamless on D3D12, so
// the static sampler's WRAP mode does not apply to them. The binder fills
// every cube register — a live cube, else a 1x1 cube cleared to 1.0 that
// reads as unshadowed.
//
// Push block: u_inv_vp / u_view / camera / screen / clip / counts / far
// planes in the GLSL declaration order, with the vec3 padded to 16 bytes.
// The counts are int, as on GL (deferred.c uploads them with set_uniform_i32).
//
// Texture reads are Load(), not Sample(). deferred.c binds every lighting
// texture with its NEAREST + CLAMP sampler, but the backend's static sampler
// is LINEAR + WRAP (known D3D12 limit). nearest() reproduces NEAREST + CLAMP
// exactly -- texel floor(uv * size), clamped to the edge. Every read goes
// through it by uv, never Load(SV_Position): no input is guaranteed to be
// this pass's size. The demo allocates the G-Buffer at the window size
// (deferred_init(w, h)) and lights into the half-resolution scene FBO, the
// SSAO buffer is half resolution again, and the shadow atlas PCF / blocker
// taps land between texel centres.
//
// gl_FragCoord.xy is SV_Position.xy: offscreen targets keep NDC y = -1 on
// memory row 0 on both backends, so the cluster column/row match the CPU
// binning in lighting.c (screen y up from NDC -1). floatBitsToUint is
// asuint; texelFetch on a samplerBuffer is the StructuredBuffer index.
struct PushConsts {
    float4x4 u_inv_vp;                   //   0
    float4x4 u_view;                     //  64
    float3   u_camera_pos;               // 128
    float    u_screen_w;                 // 140
    float    u_screen_h;                 // 144
    float    u_near;                     // 148
    float    u_far;                      // 152
    float    u_shadow_bias;              // 156
    int      u_point_count;              // 160
    int      u_dir_count;                // 164
    float2   u_point_shadow_far_planes;  // 168 (lights 0, 1)
    float2   _point_shadow_far_23;       // 176 (lights 2, 3)
};                                       // tail at 184
ConstantBuffer<PushConsts> g_push : register(b0, space0);
// rhi:uniform u_inv_vp 0
// rhi:uniform u_view 64
// rhi:uniform u_camera_pos 128
// rhi:uniform u_screen_w 140
// rhi:uniform u_screen_h 144
// rhi:uniform u_near 148
// rhi:uniform u_far 152
// rhi:uniform u_shadow_bias 156
// rhi:uniform u_point_count 160
// rhi:uniform u_dir_count 164
// rhi:uniform u_point_shadow_far_planes 168

Texture2D g_albedo_metallic : register(t0, space0);
Texture2D g_normal          : register(t1, space0);
Texture2D g_roughness_ao    : register(t2, space0);
Texture2D g_depth           : register(t3, space0);
Texture2D g_shadow_map      : register(t4, space0);
StructuredBuffer<float4> g_light_data : register(t5, space0);
StructuredBuffer<float4> g_light_grid : register(t6, space0);
TextureCube g_point_shadow0 : register(t10, space0);
TextureCube g_point_shadow1 : register(t11, space0);
TextureCube g_point_shadow2 : register(t12, space0);
TextureCube g_point_shadow3 : register(t13, space0);
SamplerState g_cube_smp     : register(s10, space0);
Texture2D g_brdf_lut        : register(t7, space0);
TextureCube g_irradiance_map : register(t8, space0);
TextureCube g_prefilter_map  : register(t9, space0);
SamplerState g_ibl_smp      : register(s7, space0);
Texture2D g_ssao            : register(t14, space0);
Texture2D g_emissive        : register(t15, space0);

float4 nearest(Texture2D t, float2 uv) {
    uint w, h, levels;
    t.GetDimensions(0u, w, h, levels);
    int2 c = int2(floor(uv * float2(w, h)));
    c = clamp(c, int2(0, 0), int2((int)w - 1, (int)h - 1));
    return t.Load(int3(c, 0));
}

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
    /* R644: dir lights start right after LIGHT_MAX_POINT (256) point lights
     * of 2 texels each -- texel 512, which is also why the cascades sit at
     * 520 = 512 + LIGHT_MAX_DIR * 2 (lighting.c upload layout). This read
     * (512 * 2) = 1024, past the end of the 536-texel buffer: the sun read
     * as zero on GL/VK (robust access) and out of bounds on D3D12. */
    int base = (256 * 2) + index * 2;
    float4 d0 = g_light_data[base];
    float4 d1 = g_light_data[base + 1];
    DirLight l;
    l.dir = d0.xyz; l.color = d1.xyz;
    return l;
}

uint grid_u32(uint k) {
    return asuint(g_light_grid[k >> 2u][k & 3u]);
}

float3 octahedron_decode(float2 e) {
    e = e * 2.0f - 1.0f;
    float3 n = float3(e.xy, 1.0f - abs(e.x) - abs(e.y));
    float t = max(-n.z, 0.0f);
    n.x += n.x >= 0.0f ? -t : t;
    n.y += n.y >= 0.0f ? -t : t;
    return normalize(n);
}

float3 reconstruct_world_pos(float2 uv, float depth) {
    float4 clip  = float4(uv * 2.0f - 1.0f, depth * 2.0f - 1.0f, 1.0f);
    float4 world = mul(g_push.u_inv_vp, clip);
    return world.xyz / world.w;
}

float distribution_ggx(float3 N, float3 H, float a) {
    float a2 = a * a;
    float NdH = max(dot(N, H), 0.0f);
    float d   = (NdH * NdH) * (a2 - 1.0f) + 1.0f;
    return a2 / (PI * d * d);
}

float geometry_schlick_ggx(float NdV, float k) {
    return NdV / (NdV * (1.0f - k) + k);
}

float geometry_smith(float3 N, float3 V, float3 L, float r) {
    float k = (r + 1.0f) * (r + 1.0f) / 8.0f;
    return geometry_schlick_ggx(max(dot(N, V), 0.0f), k) *
           geometry_schlick_ggx(max(dot(N, L), 0.0f), k);
}

float3 fresnel_schlick(float cos_t, float3 F0) {
    float t = 1.0f - cos_t;
    return F0 + (1.0f - F0) * (t * t * t * t * t);
}

float3 cook_torrance(float3 albedo, float metallic, float roughness,
                     float3 N, float3 V, float3 L, float3 light_color) {
    float3 H  = normalize(V + L);
    float3 F0 = lerp((float3)0.04f, albedo, metallic);

    float  NDF = distribution_ggx(N, H, roughness * roughness);
    float  G   = geometry_smith(N, V, L, roughness);
    float3 F   = fresnel_schlick(max(dot(H, V), 0.0f), F0);

    float3 num   = NDF * G * F;
    float  denom = 4.0f * max(dot(N, V), 0.0f) * max(dot(N, L), 0.0f) + 0.001f;
    float3 spec  = num / denom;

    float3 kS = F;
    float3 kD = ((float3)1.0f - kS) * (1.0f - metallic);

    return (kD * albedo / PI + spec) * light_color * max(dot(N, L), 0.0f);
}

static const int SHADOW_MATRIX_OFFSET = 520;

// GLSL mat4(c0, c1, c2, c3) takes the four texels as COLUMNS; HLSL's
// float4x4(r0..r3) fills ROWS, so the texels build the transpose and the
// product is written mul(v, M) == M_glsl * v.
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
    return nearest(g_shadow_map, clamp(auv, qmin, qmax)).r;
}

float find_blocker(int cascade, float2 uv, float compare, float2 texel_size, float search_width) {
    float blocker_sum = 0.0f;
    int blocker_count = 0;
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            float d = sample_cascade(cascade, uv, float2(x, y) * texel_size * search_width, texel_size);
            if (d < compare - 0.002f) {
                blocker_sum += d;
                blocker_count++;
            }
        }
    }
    if (blocker_count == 0) return -1.0f;
    return blocker_sum / (float)blocker_count;
}

float pcf_shadow(int cascade, float2 uv, float compare, float2 texel_size, float filter_radius) {
    float shadow = 0.0f;
    float bias = g_push.u_shadow_bias;
    int samples = (int)ceil(filter_radius * 2.0f);
    samples = clamp(samples, 1, 5);
    for (int x = -samples; x <= samples; x++) {
        for (int y = -samples; y <= samples; y++) {
            float d = sample_cascade(cascade, uv, float2(x, y) * texel_size * filter_radius, texel_size);
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
    float filter_radius = penumbra * light_size * 40.0f;
    filter_radius = clamp(filter_radius, 1.0f, 5.0f);

    return pcf_shadow(cascade, uv, z_win, texel_size, filter_radius);
}

float point_shadow_test(float3 wpos, int shadow_idx, float3 light_pos, float light_radius) {
    if (shadow_idx < 0 || shadow_idx > 3) return 1.0f;
    float3 frag_to_light = wpos - light_pos;
    float dist = length(frag_to_light);
    if (dist > light_radius) return 0.0f;
    float4 fps = float4(g_push.u_point_shadow_far_planes, g_push._point_shadow_far_23);
    float far_plane = fps[shadow_idx];
    float compare = dist / max(far_plane, 1e-4f);
    float depth;
    if (shadow_idx == 0)      depth = g_point_shadow0.Sample(g_cube_smp, frag_to_light).r;
    else if (shadow_idx == 1) depth = g_point_shadow1.Sample(g_cube_smp, frag_to_light).r;
    else if (shadow_idx == 2) depth = g_point_shadow2.Sample(g_cube_smp, frag_to_light).r;
    else                      depth = g_point_shadow3.Sample(g_cube_smp, frag_to_light).r;
    return compare <= depth + g_push.u_shadow_bias ? 1.0f : 0.15f;
}

float4 main(float4 frag_pos : SV_Position, float2 uv : TEXCOORD0) : SV_Target0 {
    float depth = nearest(g_depth, uv).r;
    if (depth >= 1.0f)
        return float4(0.0f, 0.0f, 0.0f, 1.0f);

    float4 am     = nearest(g_albedo_metallic, uv);
    float4 rao    = nearest(g_roughness_ao, uv);
    float3 albedo = am.rgb;
    float  metal  = am.a;
    float  rough  = max(rao.r, 0.04f);
    float  ao     = rao.g * nearest(g_ssao, uv).r;

    float3 N    = octahedron_decode(nearest(g_normal, uv).rg);
    float3 wpos = reconstruct_world_pos(uv, depth);
    float3 V    = normalize(g_push.u_camera_pos - wpos);

    // HAS_IBL, line for line with the GLSL. GL binds these with the
    // G-Buffer's NEAREST sampler (MIN NEAREST_MIPMAP_NEAREST): the LUT read
    // is nearest() exactly; the cube reads take the nearest mip (round of
    // the lod) with the static LINEAR filter inside the face -- the one
    // known difference, sub-texel on 64^2 / 256^2 smooth environment maps.
    float3 F0     = lerp((float3)0.04f, albedo, metal);
    float3 F_env  = fresnel_schlick(max(dot(N, V), 0.0f), F0);
    float3 kD_env = (1.0f - F_env) * (1.0f - metal);
    float3 irradiance = g_irradiance_map.SampleLevel(g_ibl_smp, N, 0.0f).rgb;
    float3 diffuse_ibl = irradiance * albedo * kD_env;
    float3 R = reflect(-V, N);
    float lod = round(rough * 4.0f);
    float3 prefiltered = g_prefilter_map.SampleLevel(g_ibl_smp, R, lod).rgb;
    float2 brdf = nearest(g_brdf_lut, float2(max(dot(N, V), 0.0f), rough)).rg;
    float3 specular_ibl = prefiltered * (F0 * brdf.x + brdf.y);
    float3 color = (diffuse_ibl + specular_ibl) * ao;

    color += nearest(g_emissive, uv).rgb;

    float dir_shadow = shadow_test(wpos);
    for (int di = 0; di < g_push.u_dir_count; di++) {
        DirLight dl = read_dir_light(di);
        color += cook_torrance(albedo, metal, rough, N, V, -dl.dir,
                               dl.color * dir_shadow);
    }

    if (g_push.u_point_count > 0 && g_push.u_screen_w > 0.0f) {
        float4 vp = mul(g_push.u_view, float4(wpos, 1.0f));
        float ld = -vp.z;
        uint cx = min((uint)(frag_pos.x / (g_push.u_screen_w / 16.0f)), 15u);
        uint cy = min((uint)(frag_pos.y / (g_push.u_screen_h / 8.0f)), 7u);
        uint cz = min((uint)floor(24.0f * log2(max(ld / g_push.u_near, 1.0f)) /
                                  log2(g_push.u_far / g_push.u_near)), 23u);
        uint ci = cx + cy * 16u + cz * 128u;
        uint go = grid_u32(ci * 2u);
        uint gc = grid_u32(ci * 2u + 1u);
        uint gb = 16u * 8u * 24u * 2u;

        for (uint i = 0u; i < gc; i++) {
            int li = (int)grid_u32(gb + go + i);
            PointLight pl = read_point_light(li);
            float3 toL = pl.pos - wpos;
            float dist = length(toL);
            if (dist > pl.radius) continue;
            float3 L = toL / max(dist, 1e-3f);
            float att = 1.0f - dist / pl.radius; att *= att;
            float pshadow = point_shadow_test(wpos, (int)pl.shadow_index, pl.pos, pl.radius);
            color += cook_torrance(albedo, metal, rough, N, V, L, pl.color * att * pshadow);
        }
    }

    color = color / (color + (float3)1.0f);
    return float4(color, 1.0f);
}
