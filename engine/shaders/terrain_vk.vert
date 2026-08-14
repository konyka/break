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
#ifdef FORWARD_MRT
layout(location = 3) out vec2 v_velocity;
layout(std140, set = 1, binding = 0) uniform ForwardTemporal {
    mat4 u_prev_vp;
    mat4 u_prev_model_unused;
} temporal;
#endif

void main() {
    vec4 world_pos = vec4(aPos, 1.0);
    vWorldPos = world_pos.xyz;
    vNormal = aNormal;
    vUV = aUV;
    vec4 curr_clip = pc.u_proj * pc.u_view * world_pos;
#ifdef FORWARD_MRT
    vec4 prev_clip = temporal.u_prev_vp * world_pos;
    v_velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
#endif
    gl_Position = curr_clip;
    /* R214-A: OpenGL proj → Vulkan clip.z [0,1] (match depth_only / CSM). */
    gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;
}
