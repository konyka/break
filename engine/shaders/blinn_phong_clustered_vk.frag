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

    vec3 color = pc.u_ambient * texture(u_albedo, vUV).rgb;

    for (uint di = 0u; di < pc.u_dir_count; di++) {
        DirLight dl = read_dir_light(int(di));
        vec3 L = normalize(-dl.dir);
        vec3 H = normalize(L + V);
        float diff = max(dot(N, L), 0.0);
        float spec = pow(max(dot(N, H), 0.0), 32.0);
        color += dl.color * (diff + spec * 0.15) * texture(u_albedo, vUV).rgb;
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

        uint cz = 0u;
        for (uint z = 0u; z < 24u; z++) {
            float z_near = pc.u_near * pow(pc.u_far / pc.u_near, float(z) / 24.0);
            if (linear_depth >= z_near) cz = z;
        }

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
            float spec = pow(max(dot(N, H), 0.0), 32.0);

            color += pl.color * atten * (diff + spec * 0.15) * texture(u_albedo, vUV).rgb;
        }
    }

    FragColor = vec4(color, 1.0);
}
