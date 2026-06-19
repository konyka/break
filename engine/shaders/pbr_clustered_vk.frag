#version 450 core

layout(location = 0) in vec3 vWorldPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vUV;

/* Vulkan GLSL forbids non-opaque uniforms outside a block, so fog colour and
 * the underwater flag live in the push-constant block. u_proj was unused by
 * this fragment shader, so its 64-byte slot is reclaimed (block = 232 bytes,
 * within the 256-byte push limit). Offsets must match rhi_vk.c's clustered map. */
layout(push_constant) uniform PushConstants {
    mat4 u_model;       /*   0 */
    mat4 u_view;        /*  64 */
    vec3 u_camera_pos;  /* 128 */
    float u_fog_near;   /* 140 */
    vec3 u_ambient;     /* 144 */
    float u_fog_far;    /* 156 */
    float u_screen_w;   /* 160 */
    float u_screen_h;   /* 164 */
    float u_near;       /* 168 */
    float u_far;        /* 172 */
    uint u_point_count; /* 176 */
    uint u_dir_count;   /* 180 */
    float u_shadow_bias;/* 184 */
    vec3 u_fog_color;   /* 192 */
    float u_underwater; /* 204 */
    uint u_point_shadow_count;    /* 208 */
    uint u_point_shadow_light_0;  /* 212 */
    uint u_point_shadow_light_1;  /* 216 */
    uint u_point_shadow_light_2;  /* 220 */
    uint u_point_shadow_light_3;  /* 224 */
    float u_pom_enabled;          /* 228 */
} pc;

layout(binding = 0) uniform sampler2D u_albedo;
layout(binding = 1) uniform sampler2D u_shadow_map;
layout(binding = 2) uniform sampler2D u_metallic_roughness;
layout(binding = 3) uniform sampler2D u_normal_map;
layout(binding = 4) uniform sampler2D u_emissive;
layout(set = 0, binding = 5) uniform sampler2D u_ssao;
layout(set = 1, binding = 0) uniform samplerBuffer u_light_data;
layout(set = 1, binding = 1) uniform samplerBuffer u_light_grid;
#ifdef HAS_IBL
layout(set = 0, binding = 6) uniform sampler2D u_brdf_lut;
layout(set = 0, binding = 7) uniform samplerCube u_irradiance_map;
layout(set = 0, binding = 8) uniform samplerCube u_prefilter_map;
#endif
layout(set = 0, binding = 10) uniform samplerCube u_point_shadow_cubes[4];

layout(location = 0) out vec4 FragColor;

const float PI = 3.14159265359;

const float PI_IBL = 3.14159265;
const vec3 IBL_RAYLEIGH = vec3(5.5e-6, 13.0e-6, 22.4e-6);
const float IBL_MIE = 21.0e-6;

/* Light readers must precede their first use (GLSL has no forward decls). */
struct PointLight { vec3 pos; float radius; vec3 color; float _pad; };
struct DirLight   { vec3 dir; float _pad0; vec3 color; float _pad1; };

PointLight read_point_light(int index) {
    int base = index * 2;
    vec4 d0 = texelFetch(u_light_data, base);
    vec4 d1 = texelFetch(u_light_data, base + 1);
    PointLight l;
    l.pos = d0.xyz; l.radius = d0.w; l.color = d1.xyz;
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

/* The light grid is a dense uint array viewed through an RGBA32F texel buffer.
 * Logical uint index k lives in component (k & 3) of texel (k >> 2); recover the
 * original integer bits with floatBitsToUint. */
uint grid_u32(uint k) {
    return floatBitsToUint(texelFetch(u_light_grid, int(k >> 2u))[int(k & 3u)]);
}

vec3 sky_color_ibl(vec3 dir, vec3 sun_dir, vec3 sun_col) {
    float cos_sun = max(dot(dir, sun_dir), -1.0);

    float rayleigh_p = (3.0 / (16.0 * PI_IBL)) * (1.0 + cos_sun * cos_sun);
    float g = 0.758;
    float g2 = g * g;
    float mie_p = (1.0 - g2) / ((4.0 * PI_IBL) * max((1.0 + g2 - 2.0 * g * cos_sun) * sqrt(1.0 + g2 - 2.0 * g * cos_sun), 1e-6));

    float zenith_angle = acos(clamp(dir.y, -1.0, 1.0));
    float density = exp(-zenith_angle * 6371.0 / 8400.0) + exp(-zenith_angle * 6371.0 / 1250.0);
    density = min(density, 1.0);

    vec3 scattering = (IBL_RAYLEIGH * rayleigh_p + vec3(IBL_MIE * mie_p)) * 20.0 * density;
    vec3 extinction = exp(-(IBL_RAYLEIGH + vec3(IBL_MIE * 0.1)) * density * 0.5 * 60.0);

    vec3 sky = sun_col * scattering * extinction;

    float sun_disc = smoothstep(0.9995, 0.9999, cos_sun);
    sky += sun_col * 1.0 * sun_disc * extinction;

    float horizon_fog = (1.0 - abs(dir.y)) * (1.0 - abs(dir.y)) * (1.0 - abs(dir.y));
    sky += sun_col * 0.1 * horizon_fog;

    return max(sky, vec3(0.0));
}

vec3 irradiance_hemisphere(vec3 normal) {
    vec3 sun_dir = normalize(-read_dir_light(0).dir);
    vec3 sun_col = read_dir_light(0).color;
    vec3 up = abs(normal.y) < 0.999 ? vec3(0, 1, 0) : vec3(1, 0, 0);
    vec3 tangent = normalize(cross(up, normal));
    vec3 bitangent = cross(normal, tangent);

    vec3 irradiance = vec3(0.0);
    float samples = 0.0;
    float phi_step = 0.523598;
    float cos_step = 0.2;

    for (float phi = 0.0; phi < 6.283185; phi += phi_step) {
        for (float cos_t = 0.1; cos_t < 1.0; cos_t += cos_step) {
            float sin_t = sqrt(1.0 - cos_t * cos_t);
            vec3 local = vec3(sin_t * cos(phi), cos_t, sin_t * sin(phi));
            vec3 sample_dir = tangent * local.x + normal * local.y + bitangent * local.z;
            irradiance += sky_color_ibl(sample_dir, sun_dir, sun_col) * cos_t;
            samples += 1.0;
        }
    }
    return irradiance / samples;
}

vec3 prefiltered_specular(vec3 R, float roughness) {
    vec3 sun_dir = normalize(-read_dir_light(0).dir);
    vec3 sun_col = read_dir_light(0).color;
    float blur = roughness * 0.5;
    vec3 up = abs(R.y) < 0.999 ? vec3(0, 1, 0) : vec3(1, 0, 0);
    vec3 t1 = normalize(cross(up, R)) * blur;
    vec3 t2 = cross(R, t1) * blur;

    vec3 sum = sky_color_ibl(R, sun_dir, sun_col);
    sum += sky_color_ibl(R + t1, sun_dir, sun_col);
    sum += sky_color_ibl(R - t1, sun_dir, sun_col);
    sum += sky_color_ibl(R + t2, sun_dir, sun_col);
    sum += sky_color_ibl(R - t2, sun_dir, sun_col);
    return sum / 5.0;
}

// Normal Distribution Function - GGX/Trowbridge-Reitz
float D_GGX(float NdotH, float roughness) {
    float a = roughness * roughness;
    float a2 = a * a;
    float NdotH2 = NdotH * NdotH;
    float denom = NdotH2 * (a2 - 1.0) + 1.0;
    return a2 / (PI * denom * denom);
}

// Fresnel - Schlick approximation
vec3 F_Schlick(float cosTheta, vec3 F0) {
    /* R84-4: Manual 5th power avoids transcendental pow() */
    float t = clamp(1.0 - cosTheta, 0.0, 1.0);
    return F0 + (1.0 - F0) * (t * t * t * t * t);
}

// Geometry - Smith's method with GGX (Schlick-GGX, k = (r+1)^2/8 for direct lighting)
float G_SmithGGX(float NdotV, float NdotL, float roughness) {
    float r = roughness + 1.0;
    float k = (r * r) / 8.0;
    float ggx1 = NdotV / (NdotV * (1.0 - k) + k);
    float ggx2 = NdotL / (NdotL * (1.0 - k) + k);
    return ggx1 * ggx2;
}

// Cook-Torrance microfacet BRDF (direct lighting term)
vec3 cook_torrance_brdf(vec3 N, vec3 V, vec3 L, vec3 radiance, vec3 albedo, float metallic, float roughness) {
    vec3 H = normalize(V + L);
    float NdotH = max(dot(N, H), 0.0);
    float NdotV = max(dot(N, V), 0.0);
    float NdotL = max(dot(N, L), 0.0);
    float HdotV = max(dot(H, V), 0.0);

    vec3 F0 = mix(vec3(0.04), albedo, metallic);

    float D = D_GGX(NdotH, roughness);
    vec3  F = F_Schlick(HdotV, F0);
    float G = G_SmithGGX(NdotV, NdotL, roughness);

    vec3 numerator = D * F * G;
    float denominator = 4.0 * NdotV * NdotL + 0.0001;
    vec3 specular = numerator / denominator;

    vec3 kD = (vec3(1.0) - F) * (1.0 - metallic);
    return (kD * albedo / PI + specular) * radiance * NdotL;
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

/* The 4 CSM cascades are packed into the 2x2 quadrants of a single shadow
 * atlas; cascade c lives at quadrant (c&1, c>>1). Sampling is clamped to the
 * quadrant interior so PCF/PCSS taps cannot bleed across cascade borders. */
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
    float bias = pc.u_shadow_bias;
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
    /* Pick the tightest (highest-resolution) cascade whose frustum contains the
     * fragment. Split-independent, so correct regardless of the CPU splits. */
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
    /* Real per-quadrant texel size derived from the bound atlas resolution. */
    vec2 texel_size = 1.0 / vec2(textureSize(u_shadow_map, 0));

    float light_size = 0.02 * (1.0 + float(cascade) * 0.5);
    float search_width = light_size / max(ndc.z, 1e-3);

    float blocker = find_blocker(cascade, uv, ndc.z, texel_size, search_width);
    if (blocker < 0.0) return 1.0;

    float penumbra = (ndc.z - blocker) / max(blocker, 1e-3);
    float filter_radius = penumbra * light_size * 40.0;
    filter_radius = clamp(filter_radius, 1.0, 5.0);

    return pcf_shadow(cascade, uv, ndc.z, texel_size, filter_radius);
}

float shadow_cascade(vec3 world_pos) {
    return shadow_test(world_pos);
}

float point_shadow_test(vec3 wpos, int light_idx, vec3 light_pos, float light_radius) {
    if (pc.u_point_shadow_count == 0u) return 1.0;
    int slot = -1;
    if (pc.u_point_shadow_count > 0u && pc.u_point_shadow_light_0 == uint(light_idx)) slot = 0;
    else if (pc.u_point_shadow_count > 1u && pc.u_point_shadow_light_1 == uint(light_idx)) slot = 1;
    else if (pc.u_point_shadow_count > 2u && pc.u_point_shadow_light_2 == uint(light_idx)) slot = 2;
    else if (pc.u_point_shadow_count > 3u && pc.u_point_shadow_light_3 == uint(light_idx)) slot = 3;
    if (slot < 0) return 1.0;
    vec3 frag_to_light = wpos - light_pos;
    float dist = length(frag_to_light);
    if (dist > light_radius) return 0.0;
    float compare = dist / max(light_radius, 1e-4);
    float depth = texture(u_point_shadow_cubes[slot], frag_to_light).r;
    return compare <= depth + pc.u_shadow_bias ? 1.0 : 0.15;
}

vec3 perturb_normal(vec3 N, vec3 V, vec2 uv) {
    vec3 map = texture(u_normal_map, uv).rgb * 2.0 - 1.0;
    vec3 Q1 = dFdx(vWorldPos);
    vec3 Q2 = dFdy(vWorldPos);
    vec2 st1 = dFdx(uv);
    vec2 st2 = dFdy(uv);
    vec3 T = normalize(Q1 * st2.t - Q2 * st1.t);
    vec3 B = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);
    return normalize(TBN * map);
}

vec2 parallax_occlusion_mapping(vec3 V, vec3 N, vec2 uv) {
    vec3 Q1 = dFdx(vWorldPos);
    vec3 Q2 = dFdy(vWorldPos);
    vec2 st1 = dFdx(uv);
    vec2 st2 = dFdy(uv);
    vec3 T = normalize(Q1 * st2.t - Q2 * st1.t);
    vec3 B = -normalize(cross(N, T));
    mat3 TBN = mat3(T, B, N);

    vec3 tan_view = transpose(TBN) * V;
    tan_view = normalize(tan_view);

    float height_scale = 0.03;
    float num_layers = 16.0;
    float layer_depth = 1.0 / num_layers;

    vec2 P = tan_view.xy / max(tan_view.z, 0.01) * height_scale;
    vec2 delta_uv = P / num_layers;

    vec2 current_uv = uv;
    float current_depth = 0.0;

    for (float i = 0.0; i < num_layers; i += 1.0) {
        float h = texture(u_normal_map, current_uv).b;
        if (current_depth >= h) break;
        current_depth += layer_depth;
        current_uv -= delta_uv;
    }

    vec2 prev_uv = current_uv + delta_uv;
    float after = texture(u_normal_map, current_uv).b - current_depth;
    float before = current_depth - layer_depth - texture(u_normal_map, prev_uv).b;
    float weight = after / max(after - before, 0.001);
    return mix(prev_uv, current_uv, weight);
}

void main() {
    vec3 N = normalize(vNormal);
    vec3 V = normalize(pc.u_camera_pos - vWorldPos);

    /* R84-1: Gate POM */
    vec2 pom_uv = pc.u_pom_enabled > 0.5 ? parallax_occlusion_mapping(V, N, vUV) : vUV;

    vec3 albedo = texture(u_albedo, pom_uv).rgb;

    vec2 mr = texture(u_metallic_roughness, pom_uv).bg;
    float metallic  = mr.x;
    float roughness = mr.y;

    N = perturb_normal(N, V, pom_uv);

    vec3 emissive = texture(u_emissive, pom_uv).rgb;

    vec3 F0 = mix(vec3(0.04), albedo, metallic);
    /* R85-4: Compute F_Schlick once — reuse for both IBL and fallback paths. */
    vec3 F_env  = F_Schlick(max(dot(N, V), 0.0), F0);
    vec3 kD_env = (vec3(1.0) - F_env) * (1.0 - metallic);

#ifdef HAS_IBL
    // ---- IBL ambient (split-sum approximation) ----

    vec3 irradiance  = texture(u_irradiance_map, N).rgb;
    vec3 diffuse_ibl = irradiance * albedo * kD_env;

    vec3 R = reflect(-V, N);
    float lod = roughness * 4.0; // 5 mip levels (0-4)
    vec3 prefiltered  = textureLod(u_prefilter_map, R, lod).rgb;
    vec2 brdf         = texture(u_brdf_lut, vec2(max(dot(N, V), 0.0), roughness)).rg;
    vec3 specular_ibl = prefiltered * (F_env * brdf.x + brdf.y);
#else
    vec3 irradiance = irradiance_hemisphere(N);
    vec3 diffuse_ibl = irradiance * albedo * kD_env;

    vec3 R = reflect(-V, N);
    vec3 prefiltered = prefiltered_specular(R, roughness);
    vec3 F = F_Schlick(max(dot(N, R), 0.0), F0);
    vec2 brdf = vec2(0.8, 0.2);
    vec3 specular_ibl = prefiltered * (F * brdf.x + brdf.y);
#endif

    float ao = texture(u_ssao, vUV).r;
    vec3 color = (diffuse_ibl + specular_ibl) * ao;

    /* R84-3: shadow_test doesn't depend on loop variable */
    float dir_shadow = shadow_test(vWorldPos);
    for (uint di = 0u; di < pc.u_dir_count; di++) {
        DirLight dl = read_dir_light(int(di));
        color += cook_torrance_brdf(N, V, normalize(-dl.dir), dl.color * dir_shadow, albedo, metallic, roughness);
    }

    if (pc.u_point_count > 0u && pc.u_screen_w > 0.0) {
        vec4 vp = pc.u_view * vec4(vWorldPos, 1.0);
        float ld = -vp.z;
        uint cx = min(uint(gl_FragCoord.x / (pc.u_screen_w / 16.0)), 15u);
        uint cy = min(uint(gl_FragCoord.y / (pc.u_screen_h / 8.0)), 7u);
        /* R83-1: O(1) log2 replaces O(24) pow() loop — mathematically equivalent:
         * ld >= near * (far/near)^(z/24)  <=>  z <= 24 * log2(ld/near) / log2(far/near) */
        uint cz = min(uint(floor(24.0 * log2(max(ld / pc.u_near, 1.0)) / log2(pc.u_far / pc.u_near))), 23u);
        uint ci = cx + cy * 16u + cz * 128u;
        uint go = grid_u32(ci * 2u);
        uint gc = grid_u32(ci * 2u + 1u);
        uint gb = 16u * 8u * 24u * 2u;

        for (uint i = 0u; i < gc; i++) {
            int li = int(grid_u32(gb + go + i));
            PointLight pl = read_point_light(li);
            vec3 toL = pl.pos - vWorldPos;
            float dist = length(toL);
            if (dist > pl.radius) continue;
            vec3 L = toL / max(dist, 1e-3);
            float att = 1.0 - dist / pl.radius; att *= att;
            float pshadow = point_shadow_test(vWorldPos, li, pl.pos, pl.radius);
            color += cook_torrance_brdf(N, V, L, pl.color * att * pshadow, albedo, metallic, roughness);
        }
    }

    color += emissive;

    float fog_dist = length(vWorldPos - pc.u_camera_pos);
    float fog_factor = clamp((fog_dist - pc.u_fog_near) / max(pc.u_fog_far - pc.u_fog_near, 0.001), 0.0, 1.0);
    color = mix(color, pc.u_fog_color, fog_factor);

    if (pc.u_underwater > 0.5) {
        color = mix(color, vec3(0.0, 0.15, 0.25), 0.35);
        float uw_absorb = clamp(fog_dist * 0.02, 0.0, 0.6);
        color *= (1.0 - uw_absorb);
        color.r *= 0.7;
    }

    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0 / 2.2));

    FragColor = vec4(color, 1.0);
}
