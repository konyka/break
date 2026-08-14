#version 450 core
/* R441: texture-array variant of blinn_phong_vk.frag — binding 0 becomes a
 * sampler2DArray (the shared COMBINED_IMAGE_SAMPLER layout accepts a 2D_ARRAY
 * view unchanged). Lighting math identical to blinn_phong_vk.frag. */

layout(location = 0) in vec3 vWorldPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vUV;
layout(location = 3) flat in uint vLayer;
#ifdef FORWARD_MRT
layout(location = 4) in vec2 v_velocity;
#endif

layout(push_constant) uniform PushConstants {
    mat4 u_model;
    mat4 u_view;
    mat4 u_proj;
    vec3 u_light_dir;
    float _pad0;
    vec3 u_light_color;
    float _pad1;
    vec3 u_ambient;
    float _pad2;
    vec3 u_camera_pos;
    float _pad3;
} pc;

layout(binding = 0) uniform sampler2DArray u_albedo;

layout(location = 0) out vec4 FragColor;
#ifdef FORWARD_MRT
layout(location = 1) out vec2 out_velocity;
#endif

void main() {
    vec3 N = normalize(vNormal);
    vec3 L = (-pc.u_light_dir)  /* R96-3: u_light_dir pre-normalized on CPU */;
    vec3 V = normalize(pc.u_camera_pos - vWorldPos);
    vec3 H = normalize(L + V);

    float diff = max(dot(N, L), 0.0);
    float spec = max(dot(N, H), 0.0); spec *= spec; spec *= spec; spec *= spec; spec *= spec; spec *= spec;

    vec3 albedo = texture(u_albedo, vec3(vUV, float(vLayer))).rgb;
    vec3 color = albedo * (pc.u_ambient + pc.u_light_color * diff) + pc.u_light_color * spec * 0.15;
    FragColor = vec4(color, 1.0);
#ifdef FORWARD_MRT
    out_velocity = v_velocity;
#endif
}
