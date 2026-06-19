#version 450 core

layout(location = 0) in vec3 vWorldPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vUV;

layout(push_constant) uniform PushConstants {
    mat4 u_model;
    mat4 u_view;
    mat4 u_proj;
    vec3 u_camera_pos;
    float _pad0;
    vec3 u_ambient;
    float _pad1;
    float u_screen_w;
    float u_screen_h;
    float u_near;
    float u_far;
    uint u_point_count;
    uint u_dir_count;
} pc;

layout(binding = 0) uniform sampler2D u_albedo;
layout(set = 1, binding = 0) uniform samplerBuffer u_light_data;
layout(set = 1, binding = 1) uniform samplerBuffer u_light_grid;

layout(location = 0) out vec4 FragColor;

struct PointLight {
    vec3 pos;
    float radius;
    vec3 color;
    float _pad;
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

void main() {
    vec3 N = normalize(vNormal);
    vec3 V = normalize(pc.u_camera_pos - vWorldPos);

    vec3 albedo = texture(u_albedo, vUV).rgb;
    vec3 color = pc.u_ambient * albedo;

    for (uint di = 0u; di < pc.u_dir_count; di++) {
        DirLight dl = read_dir_light(int(di));
        vec3 L = normalize(-dl.dir);
        vec3 H = normalize(L + V);
        float diff = max(dot(N, L), 0.0);
        float NdH = max(dot(N, H), 0.0); float spec = NdH * NdH; spec *= spec; spec *= spec; spec *= spec; spec *= spec; spec *= spec;
        color += dl.color * (diff + spec * 0.15) * albedo;
    }

    if (pc.u_point_count > 0u && pc.u_screen_w > 0.0) {
        float tile_w = pc.u_screen_w / 16.0;
        float tile_h = pc.u_screen_h / 8.0;

        vec4 vp_pos = pc.u_view * vec4(vWorldPos, 1.0);
        float linear_depth = -vp_pos.z;

        uint cx = uint(gl_FragCoord.x / tile_w);
        uint cy = uint(gl_FragCoord.y / tile_h);
        cx = min(cx, 15u);
        cy = min(cy, 7u);

        /* R83-1: O(1) log2 replaces O(24) pow() loop — mathematically equivalent:
         * ld >= near * (far/near)^(z/24)  <=>  z <= 24 * log2(ld/near) / log2(far/near) */
        uint cz = min(uint(floor(24.0 * log2(max(linear_depth / pc.u_near, 1.0)) / log2(pc.u_far / pc.u_near))), 23u);

        uint ci = cx + cy * 16u + cz * 16u * 8u;

        int grid_offset = int(texelFetch(u_light_grid, int(ci * 2u)).r);
        int grid_count = int(texelFetch(u_light_grid, int(ci * 2u + 1u)).r);

        int grid_base = 16 * 8 * 24 * 2;

        for (int i = 0; i < grid_count; i++) {
            int li = int(texelFetch(u_light_grid, grid_base + grid_offset + i).r);
            PointLight pl = read_point_light(li);

            vec3 to_light = pl.pos - vWorldPos;
            float dist = length(to_light);
            if (dist > pl.radius) continue;

            vec3 L = to_light / max(dist, 0.001);
            vec3 H = normalize(L + V);
            float atten = 1.0 - dist / pl.radius;
            atten *= atten;
            float diff = max(dot(N, L), 0.0);
            float NdH = max(dot(N, H), 0.0); float spec = NdH * NdH; spec *= spec; spec *= spec; spec *= spec; spec *= spec; spec *= spec;

            color += pl.color * atten * (diff + spec * 0.15) * albedo;
        }
    }

    FragColor = vec4(color, 1.0);
}
