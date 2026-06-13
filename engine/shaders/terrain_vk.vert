#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;

/* Shared push block (vertex+fragment). Terrain model is identity, so it is
 * omitted; offsets must match rhi_pipeline_get_uniform_location (terrain). */
layout(push_constant) uniform PushConstants {
    mat4 u_view;              /*   0 */
    mat4 u_proj;              /*  64 */
    mat4 u_light_vp;          /* 128 */
    vec4 u_light_dir_bias;    /* 192: xyz dir, w shadow_bias */
    vec4 u_light_color_watery;/* 208: xyz color, w water_y */
    vec4 u_ambient_time;      /* 224: xyz ambient, w time */
    vec4 u_camera_pos;        /* 240: xyz camera */
} pc;

layout(location = 0) out vec3 vWorldPos;
layout(location = 1) out vec3 vNormal;
layout(location = 2) out vec2 vUV;

void main() {
    vec4 world_pos = vec4(aPos, 1.0);
    vWorldPos = world_pos.xyz;
    vNormal = aNormal;
    vUV = aUV;
    gl_Position = pc.u_proj * pc.u_view * world_pos;
}
