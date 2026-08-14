#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;

layout(push_constant) uniform PushConstants {
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

layout(set = 1, binding = 0) uniform samplerBuffer u_instances;

layout(location = 0) out vec3 vWorldPos;
layout(location = 1) out vec3 vNormal;
layout(location = 2) out vec2 vUV;
#ifdef FORWARD_MRT
layout(location = 3) out vec2 v_velocity;
layout(std140, set = 2, binding = 0) uniform ForwardTemporal {
    mat4 u_prev_vp;
    mat4 u_prev_model_unused;
} temporal;
#endif

void main() {
    int idx = gl_InstanceIndex * 8;
    vec4 r0 = texelFetch(u_instances, idx);
    vec4 r1 = texelFetch(u_instances, idx + 1);
    vec4 r2 = texelFetch(u_instances, idx + 2);
    vec4 r3 = texelFetch(u_instances, idx + 3);
    mat4 model = mat4(r0, r1, r2, r3);

    vec4 world_pos = model * vec4(aPos, 1.0);
    vWorldPos = world_pos.xyz;
    vNormal = mat3(model) * aNormal;
    vUV = aUV;
    vec4 curr_clip = pc.u_proj * pc.u_view * world_pos;
#ifdef FORWARD_MRT
    mat4 prev_model = mat4(
        texelFetch(u_instances, idx + 4),
        texelFetch(u_instances, idx + 5),
        texelFetch(u_instances, idx + 6),
        texelFetch(u_instances, idx + 7));
    vec4 prev_clip = temporal.u_prev_vp * prev_model * vec4(aPos, 1.0);
    v_velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
#endif
    gl_Position = curr_clip;
    /* R214-A: OpenGL proj → Vulkan clip.z [0,1] (match depth_only / CSM). */
    gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;
}
