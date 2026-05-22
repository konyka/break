#version 450 core

layout(location = 0) in vec3 vWorldPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vUV;

uniform vec3 u_camera_pos;
uniform vec3 u_ambient;
uniform float u_screen_w;
uniform float u_screen_h;
uniform float u_near;
uniform float u_far;
uniform uint u_point_count;
uniform uint u_dir_count;
uniform mat4 u_view;

layout(binding = 0) uniform sampler2D u_albedo;
layout(binding = 1) uniform sampler2D u_shadow_map;
layout(binding = 2) uniform sampler2D u_metallic_roughness;
layout(binding = 3) uniform sampler2D u_normal_map;
layout(binding = 4) uniform sampler2D u_emissive;
layout(binding = 5) uniform sampler2D u_ssao;
layout(binding = 5) uniform samplerBuffer u_light_data;
layout(binding = 6) uniform samplerBuffer u_light_grid;

layout(location = 0) out vec4 FragColor;

const float PI = 3.14159265359;

const vec3 SKY_ZENITH  = vec3(0.25, 0.42, 0.78);
const vec3 SKY_HORIZON = vec3(0.50, 0.68, 0.90);
const vec3 SKY_NADIR   = vec3(0.08, 0.08, 0.12);

vec3 sky_color(vec3 dir) {
    float t = dir.y;
    if (t > 0.0)
        return mix(SKY_HORIZON, SKY_ZENITH, pow(t, 0.6));
    else
        return mix(SKY_HORIZON, SKY_NADIR, pow(-t, 0.8));
}

vec3 irradiance_hemisphere(vec3 normal) {
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
            irradiance += sky_color(sample_dir) * cos_t;
            samples += 1.0;
        }
    }
    return irradiance / samples;
}

vec3 prefiltered_specular(vec3 R, float roughness) {
    float blur = roughness * 0.5;
    vec3 up = abs(R.y) < 0.999 ? vec3(0, 1, 0) : vec3(1, 0, 0);
    vec3 t1 = normalize(cross(up, R)) * blur;
    vec3 t2 = cross(R, t1) * blur;

    vec3 sum = sky_color(R);
    sum += sky_color(R + t1);
    sum += sky_color(R - t1);
    sum += sky_color(R + t2);
    sum += sky_color(R - t2);
    return sum / 5.0;
}

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

float d_ggx(vec3 N, vec3 H, float r) {
    float a2 = r * r; a2 *= a2;
    float d = max(dot(N, H), 0.0); d *= d;
    float denom = d * (a2 - 1.0) + 1.0;
    return a2 / (PI * denom * denom + 1e-4);
}

float g_schlick(float NdV, float r) {
    float k = (r + 1.0); k *= k; k /= 8.0;
    return NdV / (NdV * (1.0 - k) + k);
}

float g_smith(vec3 N, vec3 V, vec3 L, float r) {
    return g_schlick(max(dot(N, V), 0.0), r) * g_schlick(max(dot(N, L), 0.0), r);
}

vec3 f_schlick(float cosT, vec3 F0) {
    return F0 + (1.0 - F0) * pow(1.0 - cosT, 5.0);
}

vec3 pbr(vec3 N, vec3 V, vec3 L, vec3 rad, vec3 alb, float met, float rou) {
    vec3 H = normalize(V + L);
    vec3 F0 = mix(vec3(0.04), alb, met);
    float D = d_ggx(N, H, rou);
    float G = g_smith(N, V, L, rou);
    vec3  F = f_schlick(max(dot(H, V), 0.0), F0);
    vec3 spec = (D * G * F) / (4.0 * max(dot(N, V), 0.0) * max(dot(N, L), 0.0) + 1e-4);
    vec3 kD = (1.0 - F) * (1.0 - met);
    return (kD * alb / PI + spec) * rad * max(dot(N, L), 0.0);
}

const int SHADOW_MATRIX_OFFSET = 520;

const float cascade_splits[5] = float[](0.1, 5.0, 15.0, 40.0, 100.0);

mat4 get_cascade_vp(int cascade) {
    int offset = SHADOW_MATRIX_OFFSET + cascade * 4;
    return mat4(
        texelFetch(u_light_data, offset),
        texelFetch(u_light_data, offset + 1),
        texelFetch(u_light_data, offset + 2),
        texelFetch(u_light_data, offset + 3)
    );
}

float pcf_shadow(vec2 uv, float compare, vec2 texel_size) {
    float shadow = 0.0;
    float bias = 0.002;
    for (int x = -2; x <= 2; x++) {
        for (int y = -2; y <= 2; y++) {
            float d = texture(u_shadow_map, uv + vec2(x, y) * texel_size).r;
            shadow += (compare - bias) > d ? 0.3 : 1.0;
        }
    }
    return shadow / 25.0;
}

float shadow_test(vec3 world_pos) {
    vec4 vp_pos = u_view * vec4(world_pos, 1.0);
    float view_depth = -vp_pos.z;

    int cascade = 0;
    for (int i = 0; i < 4; i++) {
        if (view_depth < cascade_splits[i + 1]) {
            cascade = i;
            break;
        }
        cascade = i;
    }

    mat4 light_vp = get_cascade_vp(cascade);
    vec4 clip = light_vp * vec4(world_pos, 1.0);
    vec3 ndc = clip.xyz / clip.w;
    vec2 uv = ndc.xy * 0.5 + 0.5;
    if (uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0) return 1.0;

    vec2 texel_size = vec2(1.0 / 1024.0);
    return pcf_shadow(uv, ndc.z, texel_size);
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
    vec3 V = normalize(u_camera_pos - vWorldPos);

    vec2 pom_uv = parallax_occlusion_mapping(V, N, vUV);

    vec3 albedo = texture(u_albedo, pom_uv).rgb;

    vec2 mr = texture(u_metallic_roughness, pom_uv).bg;
    float metallic  = mr.x;
    float roughness = mr.y;

    N = perturb_normal(N, V, pom_uv);

    vec3 emissive = texture(u_emissive, pom_uv).rgb;

    vec3 F0 = mix(vec3(0.04), albedo, metallic);
    vec3 kD = (1.0 - f_schlick(max(dot(N, V), 0.0), F0)) * (1.0 - metallic);

    vec3 irradiance = irradiance_hemisphere(N);
    vec3 diffuse_ibl = irradiance * albedo * kD;

    vec3 R = reflect(-V, N);
    vec3 prefiltered = prefiltered_specular(R, roughness);
    vec3 F = f_schlick(max(dot(N, R), 0.0), F0);
    vec2 brdf = vec2(0.8, 0.2);
    vec3 specular_ibl = prefiltered * (F * brdf.x + brdf.y);

    float ao = texture(u_ssao, vUV).r;
    vec3 color = (diffuse_ibl + specular_ibl) * ao;

    for (uint di = 0u; di < u_dir_count; di++) {
        DirLight dl = read_dir_light(int(di));
        float shadow = shadow_test(vWorldPos);
        color += pbr(N, V, normalize(-dl.dir), dl.color * shadow, albedo, metallic, roughness);
    }

    if (u_point_count > 0u && u_screen_w > 0.0) {
        vec4 vp = u_view * vec4(vWorldPos, 1.0);
        float ld = -vp.z;
        uint cx = min(uint(gl_FragCoord.x / (u_screen_w / 16.0)), 15u);
        uint cy = min(uint(gl_FragCoord.y / (u_screen_h / 8.0)), 7u);
        uint cz = 0u;
        for (uint z = 0u; z < 24u; z++) {
            if (ld >= u_near * pow(u_far / u_near, float(z) / 24.0)) cz = z;
        }
        uint ci = cx + cy * 16u + cz * 128u;
        int go = int(texelFetch(u_light_grid, int(ci * 2u)).r);
        int gc = int(texelFetch(u_light_grid, int(ci * 2u + 1u)).r);
        int gb = 16 * 8 * 24 * 2;

        for (int i = 0; i < gc; i++) {
            int li = int(texelFetch(u_light_grid, gb + go + i).r);
            PointLight pl = read_point_light(li);
            vec3 toL = pl.pos - vWorldPos;
            float dist = length(toL);
            if (dist > pl.radius) continue;
            vec3 L = toL / max(dist, 1e-3);
            float att = 1.0 - dist / pl.radius; att *= att;
            color += pbr(N, V, L, pl.color * att, albedo, metallic, roughness);
        }
    }

    color += emissive;

    color = color / (color + vec3(1.0));
    color = pow(color, vec3(1.0 / 2.2));

    FragColor = vec4(color, 1.0);
}
