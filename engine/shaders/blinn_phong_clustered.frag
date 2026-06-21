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
uniform float u_shadow_bias;

layout(binding = 0) uniform sampler2D u_albedo;
layout(binding = 5) uniform samplerBuffer u_light_data;  /* R103-1: match GL rhi_cmd_bind_texel_buffers unit 5 */
layout(binding = 6) uniform samplerBuffer u_light_grid;  /* R103-1: match GL rhi_cmd_bind_texel_buffers unit 6 */
#ifdef HAS_POINT_SHADOW
layout(binding = 10) uniform samplerCube u_point_shadow_cubes[4];
#endif

layout(location = 0) out vec4 FragColor;

struct PointLight {
    vec3 pos;
    float radius;
    vec3 color;
    float shadow_index;
};

struct DirLight {
    vec3 dir;
    float _pad0;
    vec3 color;
    float _pad1;
};

PointLight read_point_light(int index) {
    int base = index * 2;
    vec4 d0 = texelFetch(u_light_data, base);
    vec4 d1 = texelFetch(u_light_data, base + 1);
    PointLight l;
    l.pos = d0.xyz;
    l.radius = d0.w;
    l.color = d1.xyz;
    l.shadow_index = d1.w;
    return l;
}

DirLight read_dir_light(int index) {
    int base = (512 * 2) + index * 2;
    vec4 d0 = texelFetch(u_light_data, base);
    vec4 d1 = texelFetch(u_light_data, base + 1);
    DirLight l;
    l.dir = d0.xyz;
    l.color = d1.xyz;
    return l;
}

#ifdef HAS_POINT_SHADOW
float point_shadow_test(vec3 wpos, int shadow_idx, vec3 light_pos, float light_radius) {
    if (shadow_idx < 0 || shadow_idx > 3) return 1.0;
    vec3 frag_to_light = wpos - light_pos;
    float dist = length(frag_to_light);
    if (dist > light_radius) return 0.0;
    float compare = dist / max(light_radius, 1e-4);
    float depth = texture(u_point_shadow_cubes[shadow_idx], frag_to_light).r;
    return compare <= depth + u_shadow_bias ? 1.0 : 0.15;
}
#else
float point_shadow_test(vec3 wpos, int shadow_idx, vec3 light_pos, float light_radius) {
    return 1.0;
}
#endif

/* R103-2: grid_u32 matches pbr_clustered.frag — grid buffer stores u32 values
 * packed into RGBA32F texels; floatBitsToUint recovers the original uint. */
uint grid_u32(uint k) {
    return floatBitsToUint(texelFetch(u_light_grid, int(k >> 2u))[int(k & 3u)]);
}

void main() {
    vec3 N = normalize(vNormal);
    vec3 V = normalize(u_camera_pos - vWorldPos);

    vec3 albedo = texture(u_albedo, vUV).rgb;
    vec3 color = u_ambient * albedo;

    for (uint di = 0u; di < u_dir_count; di++) {
        DirLight dl = read_dir_light(int(di));
        vec3 L = (-dl.dir)  /* R96-3: dl.dir pre-normalized in light_system_add_dir */;
        vec3 H = normalize(L + V);
        float diff = max(dot(N, L), 0.0);
        float NdH = max(dot(N, H), 0.0); float spec = NdH; spec *= spec; spec *= spec; spec *= spec; spec *= spec; spec *= spec;
        color += dl.color * (diff + spec * 0.15) * albedo;
    }

    if (u_point_count > 0u && u_screen_w > 0.0) {
        float tile_w = u_screen_w / 16.0;
        float tile_h = u_screen_h / 8.0;

        vec4 vp_pos = u_view * vec4(vWorldPos, 1.0);
        float linear_depth = -vp_pos.z;

        uint cx = uint(gl_FragCoord.x / tile_w);
        uint cy = uint(gl_FragCoord.y / tile_h);
        cx = min(cx, 15u);
        cy = min(cy, 7u);

        /* R83-1: O(1) log2 replaces O(24) pow() loop — mathematically equivalent:
         * ld >= near * (far/near)^(z/24)  <=>  z <= 24 * log2(ld/near) / log2(far/near) */
        uint cz = min(uint(floor(24.0 * log2(max(linear_depth / u_near, 1.0)) / log2(u_far / u_near))), 23u);

        uint ci = cx + cy * 16u + cz * 16u * 8u;

        int grid_offset = int(grid_u32(ci * 2u));
        int grid_count = int(grid_u32(ci * 2u + 1u));

        int grid_base = 16 * 8 * 24 * 2;

        for (int i = 0; i < grid_count; i++) {
            int li = int(grid_u32(uint(grid_base + grid_offset + i)));
            PointLight pl = read_point_light(li);

            vec3 to_light = pl.pos - vWorldPos;
            float dist = length(to_light);
            if (dist > pl.radius) continue;

            vec3 L = to_light / max(dist, 0.001);
            vec3 H = normalize(L + V);
            float atten = 1.0 - dist / pl.radius;
            atten *= atten;
            float diff = max(dot(N, L), 0.0);
            float NdH = max(dot(N, H), 0.0); float spec = NdH; spec *= spec; spec *= spec; spec *= spec; spec *= spec; spec *= spec;

            float pshadow = point_shadow_test(vWorldPos, int(pl.shadow_index), pl.pos, pl.radius);
            color += pl.color * atten * (diff + spec * 0.15) * albedo * pshadow;
        }
    }

    FragColor = vec4(color, 1.0);
}
