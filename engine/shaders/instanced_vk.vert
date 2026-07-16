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

void main() {
    int idx = gl_InstanceIndex * 4;
    vec4 r0 = texelFetch(u_instances, idx);
    vec4 r1 = texelFetch(u_instances, idx + 1);
    vec4 r2 = texelFetch(u_instances, idx + 2);
    vec4 r3 = texelFetch(u_instances, idx + 3);
    mat4 model = mat4(r0, r1, r2, r3);

    vec4 world_pos = model * vec4(aPos, 1.0);
    vWorldPos = world_pos.xyz;
    vNormal = mat3(model) * aNormal;
    vUV = aUV;
    gl_Position = pc.u_proj * pc.u_view * world_pos;
    /* R214-A: OpenGL proj → Vulkan clip.z [0,1] (match depth_only / CSM). */
    gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;
}
