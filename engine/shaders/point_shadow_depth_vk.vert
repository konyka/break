#version 450 core

layout(location = 0) in vec3 a_position;

layout(push_constant) uniform PushConstants {
    mat4 u_model;
    mat4 u_mvp;
    vec4 u_light_pos;   /* xyz = light world-space position, w unused */
    vec4 u_far_plane;   /* x = far plane, yzw unused              */
} pc;

layout(location = 0) out vec3 v_world_pos;

void main() {
    vec4 world = pc.u_model * vec4(a_position, 1.0);
    v_world_pos = world.xyz;
    gl_Position = pc.u_mvp * vec4(a_position, 1.0);
    /* R215-B: OpenGL proj → Vulkan clip.z [0,1] (match depth_only / CSM). */
    gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;
}
