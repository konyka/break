#version 450 core
/* R441: texture-array variant of blinn_phong_vk.vert — forwards the indirect
 * cmd's first_instance (gl_BaseInstanceARB) as the sampler2DArray layer. The
 * extension is required under #version 450 even for the Vulkan target
 * (unsuffixed gl_BaseInstance is core only in 460+). Push layout identical
 * to blinn_phong_vk. */
#extension GL_ARB_shader_draw_parameters : require

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;

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

layout(location = 0) out vec3 vWorldPos;
layout(location = 1) out vec3 vNormal;
layout(location = 2) out vec2 vUV;
layout(location = 3) flat out uint vLayer;
#ifdef FORWARD_MRT
layout(location = 4) out vec2 v_velocity;
layout(std140, set = 1, binding = 0) uniform ForwardTemporal {
    mat4 u_prev_vp;
    mat4 u_prev_model;
} temporal;
#endif

void main() {
    vec4 world_pos = pc.u_model * vec4(aPos, 1.0);
    vWorldPos = world_pos.xyz;
    vNormal = mat3(pc.u_model) * aNormal;
    vUV = aUV;
    vLayer = uint(gl_BaseInstanceARB);
    vec4 curr_clip = pc.u_proj * pc.u_view * world_pos;
#ifdef FORWARD_MRT
    vec4 prev_clip = temporal.u_prev_vp * temporal.u_prev_model * vec4(aPos, 1.0);
    v_velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
#endif
    gl_Position = curr_clip;
    /* R214-A: OpenGL proj → Vulkan clip.z [0,1] (match depth_only / CSM). */
    gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;
}
