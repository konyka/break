#version 450 core

layout(location = 0) in vec3 vWorldPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vUV;

/* Shared push block (must match terrain_vk.vert and the terrain offset map). */
layout(push_constant) uniform PushConstants {
    mat4 u_view;              /*   0 */
    mat4 u_proj;              /*  64 */
    mat4 u_light_vp;          /* 128 */
    vec4 u_light_dir_bias;    /* 192 */
    vec4 u_light_color_watery;/* 208 */
    vec4 u_ambient_time;      /* 224 */
    vec4 u_camera_pos;        /* 240 */
} pc;

#define u_light_dir   (pc.u_light_dir_bias.xyz)
#define u_shadow_bias (pc.u_light_dir_bias.w)
#define u_light_color (pc.u_light_color_watery.xyz)
#define u_water_y     (pc.u_light_color_watery.w)
#define u_ambient     (pc.u_ambient_time.xyz)
#define u_time        (pc.u_ambient_time.w)
#define u_camera_pos  (pc.u_camera_pos.xyz)
#define u_light_vp    (pc.u_light_vp)

layout(binding = 0) uniform sampler2D u_albedo;
layout(binding = 1) uniform sampler2D u_shadow_map;

layout(location = 0) out vec4 FragColor;

float terrain_shadow(vec3 world_pos) {
    vec4 clip = u_light_vp * vec4(world_pos, 1.0);
    vec3 ndc = clip.xyz / clip.w;
    vec2 uv = ndc.xy * 0.5 + 0.5;
    if (uv.x < 0.0 || uv.x > 1.0 || uv.y < 0.0 || uv.y > 1.0) return 1.0;
    /* u_light_vp is CSM cascade 0 -> quadrant (0,0) of the shadow atlas. */
    vec2 texel = 1.0 / vec2(textureSize(u_shadow_map, 0));
    vec2 atlas_uv = clamp(uv * 0.5, texel, vec2(0.5) - texel);
    float d = texture(u_shadow_map, atlas_uv).r;
    return (ndc.z - u_shadow_bias) > d ? 0.4 : 1.0;
}

vec3 grass_color(vec2 uv) {
    float pattern = sin(uv.x * 80.0) * sin(uv.y * 80.0) * 0.03;
    return vec3(0.22 + pattern, 0.45 + pattern * 2.0, 0.12 + pattern);
}

vec3 rock_color(vec2 uv) {
    float noise = fract(sin(dot(uv * 50.0, vec2(12.9898, 78.233))) * 43758.5453);
    return vec3(0.35 + noise * 0.08, 0.32 + noise * 0.06, 0.28 + noise * 0.05);
}

vec3 snow_color(vec2 uv) {
    float sparkle = fract(sin(dot(uv * 200.0, vec2(93.989, 67.345))) * 23421.631);
    return vec3(0.85 + sparkle * 0.1, 0.88 + sparkle * 0.08, 0.92 + sparkle * 0.06);
}

vec3 sand_color(vec2 uv) {
    float grain = fract(sin(dot(uv * 60.0, vec2(45.164, 23.891))) * 17645.234);
    return vec3(0.76 + grain * 0.04, 0.70 + grain * 0.03, 0.50 + grain * 0.03);
}

void main() {
    vec3 N = normalize(vNormal);
    vec3 L = (-u_light_dir)  /* R96-3: u_light_dir pre-normalized on CPU */;
    vec3 V = normalize(u_camera_pos - vWorldPos);
    vec3 H = normalize(L + V);

    float slope = 1.0 - N.y;
    float height = vWorldPos.y;

    float grass_w = 1.0 - smoothstep(0.0, 0.5, slope);
    float rock_w = smoothstep(0.3, 0.7, slope);
    float snow_w = smoothstep(3.5, 5.5, height) * (1.0 - smoothstep(0.5, 0.8, slope));
    float sand_w = smoothstep(1.5, 0.0, height) * grass_w;
    grass_w = grass_w * (1.0 - snow_w) * (1.0 - sand_w);
    rock_w = rock_w * (1.0 - snow_w);

    float total = grass_w + rock_w + snow_w + sand_w;
    if (total < 0.001) total = 1.0;

    vec3 albedo = (grass_color(vUV) * grass_w +
                   rock_color(vUV) * rock_w +
                   snow_color(vUV) * snow_w +
                   sand_color(vUV) * sand_w) / total;

    float diff = max(dot(N, L), 0.0);
    float spec = max(dot(N, H), 0.0); spec *= spec; spec *= spec; spec *= spec; spec *= spec; spec *= spec; spec = spec * rock_w / total;
    float shadow = terrain_shadow(vWorldPos);

    vec3 color = albedo * (u_ambient + u_light_color * diff * shadow) + u_light_color * spec * shadow * 0.15;

    float shore_dist = vWorldPos.y - u_water_y;
    float foam = smoothstep(0.8, 0.0, shore_dist) * (1.0 - smoothstep(-0.3, -0.8, shore_dist));
    foam *= 0.4 + 0.3 * sin(vWorldPos.x * 6.0 + u_camera_pos.x * 0.1) * sin(vWorldPos.z * 5.0 + u_camera_pos.z * 0.1);
    color = mix(color, vec3(0.85, 0.9, 0.95), foam * 0.6);

    if (vWorldPos.y < u_water_y) {
        float c1 = sin(vWorldPos.x * 2.5 + u_time * 0.8) * sin(vWorldPos.z * 2.3 - u_time * 0.6);
        float c2 = sin(vWorldPos.x * 3.7 - u_time * 1.1) * sin(vWorldPos.z * 3.1 + u_time * 0.9);
        float caustic = max(0.0, (c1 + c2) * 0.5) * max(0.0, (c1 + c2) * 0.5) * max(0.0, (c1 + c2) * 0.5) * 0.4;
        float depth = clamp((u_water_y - vWorldPos.y) * 0.5, 0.0, 1.0);
        color += vec3(0.15, 0.25, 0.3) * caustic * depth;
        color *= mix(1.0, 0.6, depth * 0.4);
    }

    float fog_dist = length(vWorldPos - u_camera_pos);
    float fog = clamp((fog_dist - 40.0) / 60.0, 0.0, 1.0);
    color = mix(color, u_ambient * 1.5, fog * 0.3);

    FragColor = vec4(color, 1.0);
}
