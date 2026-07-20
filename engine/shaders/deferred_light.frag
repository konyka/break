#version 430 core

/* Deferred lighting pass -- fragment stage (GL).
 * Decodes the G-Buffer and evaluates clustered direct lighting, CSM shadows,
 * and split-sum IBL (when HAS_IBL) matching pbr_clustered.frag. */

layout(location = 0) in  vec2 v_texcoord;
layout(location = 0) out vec4 frag_color;

layout(binding = 0) uniform sampler2D u_gbuf_albedo_metallic;
layout(binding = 1) uniform sampler2D u_gbuf_normal;
layout(binding = 2) uniform sampler2D u_gbuf_roughness_ao;
layout(binding = 3) uniform sampler2D u_gbuf_depth;
layout(binding = 4) uniform sampler2D u_shadow_map;
layout(binding = 10) uniform samplerCube u_point_shadow_cubes[4];
/* R272: screen-space SSAO at unit 14 (matches forward pbr_clustered.frag R213-B;
 * deferred gbuffer uses 0-4, IBL 7-9, point-shadow cubes 10-13, so 14 is free). */
layout(binding = 14) uniform sampler2D u_ssao;
layout(binding = 5) uniform samplerBuffer u_light_data;
layout(binding = 6) uniform samplerBuffer u_light_grid;
#ifdef HAS_IBL
layout(binding = 7) uniform sampler2D u_brdf_lut;
layout(binding = 8) uniform samplerCube u_irradiance_map;
layout(binding = 9) uniform samplerCube u_prefilter_map;
#endif

uniform mat4  u_inv_vp;
uniform mat4  u_view;
uniform vec3  u_camera_pos;
uniform float u_screen_w;
uniform float u_screen_h;
uniform float u_near;
uniform float u_far;
uniform float u_shadow_bias;
uniform uint  u_point_count;
uniform uint  u_dir_count;
uniform float u_point_shadow_far_planes[4];

const float PI = 3.14159265359;

struct PointLight { vec3 pos; float radius; vec3 color; float shadow_index; };
struct DirLight   { vec3 dir; float _pad0; vec3 color; float _pad1; };

PointLight read_point_light(int index) {
    int base = index * 2;
    vec4 d0 = texelFetch(u_light_data, base);
    vec4 d1 = texelFetch(u_light_data, base + 1);
    PointLight l;
    l.pos = d0.xyz; l.radius = d0.w; l.color = d1.xyz; l.shadow_index = d1.w;
    return l;
}

DirLight read_dir_light(int index) {
    int base = (512 * 2) + index * 2;
    vec4 d0 = texelFetch(u_light_data, base);
    vec4 d1 = texelFetch(u_light_data, base + 1);
    DirLight l;
    l.dir = d0.xyz; l.color = d1.xyz;
    return l;
}

uint grid_u32(uint k) {
    return floatBitsToUint(texelFetch(u_light_grid, int(k >> 2u))[int(k & 3u)]);
}

vec3 octahedron_decode(vec2 e) {
    e = e * 2.0 - 1.0;
    vec3 n = vec3(e.xy, 1.0 - abs(e.x) - abs(e.y));
    float t = max(-n.z, 0.0);
    n.x += n.x >= 0.0 ? -t : t;
    n.y += n.y >= 0.0 ? -t : t;
    return normalize(n);
}

vec3 reconstruct_world_pos(vec2 uv, float depth) {
    vec4 clip  = vec4(uv * 2.0 - 1.0, depth * 2.0 - 1.0, 1.0);
    vec4 world = u_inv_vp * clip;
    return world.xyz / world.w;
}

float distribution_ggx(vec3 N, vec3 H, float a) {
    float a2 = a * a;
    float NdH = max(dot(N, H), 0.0);
    float d   = (NdH * NdH) * (a2 - 1.0) + 1.0;
    return a2 / (PI * d * d);
}

float geometry_schlick_ggx(float NdV, float k) {
    return NdV / (NdV * (1.0 - k) + k);
}

float geometry_smith(vec3 N, vec3 V, vec3 L, float r) {
    float k = (r + 1.0) * (r + 1.0) / 8.0;
    return geometry_schlick_ggx(max(dot(N, V), 0.0), k) *
           geometry_schlick_ggx(max(dot(N, L), 0.0), k);
}

vec3 fresnel_schlick(float cos_t, vec3 F0) {
    /* R84-4: Manual 5th power avoids transcendental pow() */
    float t = 1.0 - cos_t;
    return F0 + (1.0 - F0) * (t * t * t * t * t);
}

vec3 cook_torrance(vec3 albedo, float metallic, float roughness,
                   vec3 N, vec3 V, vec3 L, vec3 light_color) {
    vec3 H  = normalize(V + L);
    vec3 F0 = mix(vec3(0.04), albedo, metallic);

    float NDF = distribution_ggx(N, H, roughness * roughness);
    float G   = geometry_smith(N, V, L, roughness);
    vec3  F   = fresnel_schlick(max(dot(H, V), 0.0), F0);

    vec3  num   = NDF * G * F;
    float denom = 4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 0.001;
    vec3  spec  = num / denom;

    vec3 kS = F;
    vec3 kD = (vec3(1.0) - kS) * (1.0 - metallic);

    return (kD * albedo / PI + spec) * light_color * max(dot(N, L), 0.0);
}

const int SHADOW_MATRIX_OFFSET = 520;

mat4 get_cascade_vp(int cascade) {
    int offset = SHADOW_MATRIX_OFFSET + cascade * 4;
    return mat4(
        texelFetch(u_light_data, offset),
        texelFetch(u_light_data, offset + 1),
        texelFetch(u_light_data, offset + 2),
        texelFetch(u_light_data, offset + 3)
    );
}

float sample_cascade(int cascade, vec2 uv, vec2 offset, vec2 texel_size) {
    vec2 q = vec2(float(cascade & 1), float(cascade >> 1));
    vec2 qmin = q * 0.5 + texel_size;
    vec2 qmax = (q + vec2(1.0)) * 0.5 - texel_size;
    vec2 auv = (q + uv) * 0.5 + offset;
    return texture(u_shadow_map, clamp(auv, qmin, qmax)).r;
}

float find_blocker(int cascade, vec2 uv, float compare, vec2 texel_size, float search_width) {
    float blocker_sum = 0.0;
    int blocker_count = 0;
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            float d = sample_cascade(cascade, uv, vec2(x, y) * texel_size * search_width, texel_size);
            if (d < compare - 0.002) {
                blocker_sum += d;
                blocker_count++;
            }
        }
    }
    if (blocker_count == 0) return -1.0;
    return blocker_sum / float(blocker_count);
}

float pcf_shadow(int cascade, vec2 uv, float compare, vec2 texel_size, float filter_radius) {
    float shadow = 0.0;
    float bias = u_shadow_bias;
    int samples = int(ceil(filter_radius * 2.0));
    samples = clamp(samples, 1, 5);
    for (int x = -samples; x <= samples; x++) {
        for (int y = -samples; y <= samples; y++) {
            float d = sample_cascade(cascade, uv, vec2(x, y) * texel_size * filter_radius, texel_size);
            shadow += (compare - bias) > d ? 0.3 : 1.0;
        }
    }
    float total = float((2 * samples + 1) * (2 * samples + 1));
    return shadow / total;
}

float shadow_test(vec3 world_pos) {
    int cascade = -1;
    vec3 ndc = vec3(0.0);
    for (int i = 0; i < 4; i++) {
        vec4 clip = get_cascade_vp(i) * vec4(world_pos, 1.0);
        vec3 n = clip.xyz / clip.w;
        vec2 uv = n.xy * 0.5 + 0.5;
        if (uv.x >= 0.0 && uv.x <= 1.0 && uv.y >= 0.0 && uv.y <= 1.0) {
            cascade = i;
            ndc = n;
            break;
        }
    }
    if (cascade < 0) return 1.0;

    vec2 uv = ndc.xy * 0.5 + 0.5;
    vec2 texel_size = 1.0 / vec2(textureSize(u_shadow_map, 0));

    /* R211-A: Window-space Z for compare (OpenGL NDC → [0,1]; matches depth tex). */
    float z_win = ndc.z * 0.5 + 0.5;
    float light_size = 0.02 * (1.0 + float(cascade) * 0.5);
    float search_width = light_size / max(z_win, 1e-3);

    float blocker = find_blocker(cascade, uv, z_win, texel_size, search_width);
    if (blocker < 0.0) return 1.0;

    float penumbra = (z_win - blocker) / max(blocker, 1e-3);
    float filter_radius = penumbra * light_size * 40.0;
    filter_radius = clamp(filter_radius, 1.0, 5.0);

    return pcf_shadow(cascade, uv, z_win, texel_size, filter_radius);
}

float point_shadow_test(vec3 wpos, int shadow_idx, vec3 light_pos, float light_radius) {
    if (shadow_idx < 0 || shadow_idx > 3) return 1.0;
    vec3 frag_to_light = wpos - light_pos;
    float dist = length(frag_to_light);
    if (dist > light_radius) return 0.0;
    float far_plane = u_point_shadow_far_planes[shadow_idx];
    float compare = dist / max(far_plane, 1e-4);
    float depth = texture(u_point_shadow_cubes[shadow_idx], frag_to_light).r;
    return compare <= depth + u_shadow_bias ? 1.0 : 0.15;
}

void main() {
    vec2  uv    = v_texcoord;
    float depth = texture(u_gbuf_depth, uv).r;
    if (depth >= 1.0) {
        frag_color = vec4(0.0, 0.0, 0.0, 1.0);
        return;
    }

    vec4  am      = texture(u_gbuf_albedo_metallic, uv);
    vec4  rao     = texture(u_gbuf_roughness_ao, uv);
    vec3  albedo  = am.rgb;
    float metal   = am.a;
    float rough   = max(rao.r, 0.04);
    /* R272: combine baked material AO (rao.g) with screen-space SSAO, matching
     * the forward path which multiplies IBL by texture(u_ssao). Previously
     * deferred ignored the per-frame SSAO entirely (used only rao.g). */
    float ao      = rao.g * texture(u_ssao, uv).r;

    vec3 N    = octahedron_decode(texture(u_gbuf_normal, uv).rg);
    vec3 wpos = reconstruct_world_pos(uv, depth);
    vec3 V    = normalize(u_camera_pos - wpos);
    vec3 F0   = mix(vec3(0.04), albedo, metal);

#ifdef HAS_IBL
    vec3 F_env  = fresnel_schlick(max(dot(N, V), 0.0), F0);
    vec3 kD_env = (vec3(1.0) - F_env) * (1.0 - metal);

    vec3 irradiance  = texture(u_irradiance_map, N).rgb;
    vec3 diffuse_ibl = irradiance * albedo * kD_env;

    vec3 R = reflect(-V, N);
    float lod = rough * 4.0;
    vec3 prefiltered  = textureLod(u_prefilter_map, R, lod).rgb;
    vec2 brdf         = texture(u_brdf_lut, vec2(max(dot(N, V), 0.0), rough)).rg;
    vec3 specular_ibl = prefiltered * (F_env * brdf.x + brdf.y);
#else
    vec3 diffuse_ibl = vec3(0.0);
    vec3 specular_ibl = vec3(0.0);
#endif

    vec3 color = (diffuse_ibl + specular_ibl) * ao;

    /* R84-3: shadow_test doesn't depend on loop variable */
    float dir_shadow = shadow_test(wpos);
    for (uint di = 0u; di < u_dir_count; di++) {
        DirLight dl = read_dir_light(int(di));
        color += cook_torrance(albedo, metal, rough, N, V, (-dl.dir)  /* R96-3: dl.dir pre-normalized in light_system_add_dir */,
                               dl.color * dir_shadow);
    }

    if (u_point_count > 0u && u_screen_w > 0.0) {
        vec4 vp = u_view * vec4(wpos, 1.0);
        float ld = -vp.z;
        uint cx = min(uint(gl_FragCoord.x / (u_screen_w / 16.0)), 15u);
        uint cy = min(uint(gl_FragCoord.y / (u_screen_h / 8.0)), 7u);
        /* R83-1: O(1) log2 replaces O(24) pow() loop — mathematically equivalent:
         * ld >= near * (far/near)^(z/24)  <=>  z <= 24 * log2(ld/near) / log2(far/near) */
        uint cz = min(uint(floor(24.0 * log2(max(ld / u_near, 1.0)) / log2(u_far / u_near))), 23u);
        uint ci = cx + cy * 16u + cz * 128u;
        uint go = grid_u32(ci * 2u);
        uint gc = grid_u32(ci * 2u + 1u);
        uint gb = 16u * 8u * 24u * 2u;

        for (uint i = 0u; i < gc; i++) {
            int li = int(grid_u32(gb + go + i));
            PointLight pl = read_point_light(li);
            vec3 toL = pl.pos - wpos;
            float dist = length(toL);
            if (dist > pl.radius) continue;
            vec3 L = toL / max(dist, 1e-3);
            float att = 1.0 - dist / pl.radius; att *= att;
            float pshadow = point_shadow_test(wpos, int(pl.shadow_index), pl.pos, pl.radius);
            color += cook_torrance(albedo, metal, rough, N, V, L, pl.color * att * pshadow);
        }
    }

    color = color / (color + vec3(1.0));
    frag_color = vec4(color, 1.0);
}
