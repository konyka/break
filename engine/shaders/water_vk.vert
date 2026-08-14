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
#ifdef FORWARD_MRT
layout(location = 1) out vec2 v_velocity;
layout(std140, set = 1, binding = 0) uniform ForwardTemporal {
    mat4 u_prev_vp;
    mat4 u_prev_model_unused;
} temporal;
#endif

void main() {
    /* R235-B: Mesh verts sit at y=0; lift to logical water plane. */
    vec3 wp = vec3(aPos.x, pc.u_watery.x, aPos.z);
    vWorldPos = wp;
    vec4 curr_clip = pc.u_proj * pc.u_view * vec4(wp, 1.0);
#ifdef FORWARD_MRT
    vec4 prev_clip = temporal.u_prev_vp * vec4(wp, 1.0);
    v_velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
#endif
    gl_Position = curr_clip;
    /* R214-A: OpenGL proj → Vulkan clip.z [0,1] (match depth_only / CSM). */
    gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;
}
