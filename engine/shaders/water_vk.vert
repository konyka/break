#version 450 core

layout(location = 0) in vec3 aPos;

/* Shared push block (vertex+fragment); offsets must match the water layout in
 * rhi_pipeline_get_uniform_location. */
layout(push_constant) uniform PushConstants {
    mat4 u_view;         /*   0 */
    mat4 u_proj;         /*  64 */
    mat4 u_light_vp;     /* 128 */
    vec4 u_camera_time;  /* 192: xyz camera, w time */
    vec4 u_color_bias;   /* 208: xyz water_color, w shadow_bias */
    vec4 u_watery;       /* 224: x water_y */
} pc;

layout(location = 0) out vec3 vWorldPos;

void main() {
    vWorldPos = aPos;
    gl_Position = pc.u_proj * pc.u_view * vec4(aPos, 1.0);
}
