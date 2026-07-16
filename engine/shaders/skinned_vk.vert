#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;
layout(location = 3) in uvec4 aJoints;
layout(location = 4) in vec4 aWeights;

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

layout(set = 1, binding = 0) uniform samplerBuffer u_joints;

layout(location = 0) out vec3 vWorldPos;
layout(location = 1) out vec3 vNormal;
layout(location = 2) out vec2 vUV;

void main() {
    mat4 skin = mat4(0.0);
    for (int i = 0; i < 4; i++) {
        int j = int(aJoints[i]);
        mat4 joint = mat4(
            texelFetch(u_joints, j * 4 + 0),
            texelFetch(u_joints, j * 4 + 1),
            texelFetch(u_joints, j * 4 + 2),
            texelFetch(u_joints, j * 4 + 3)
        );
        skin += aWeights[i] * joint;
    }

    vec4 world_pos = skin * vec4(aPos, 1.0);
    vWorldPos = world_pos.xyz;
    vNormal = mat3(skin) * aNormal;
    vUV = aUV;
    gl_Position = pc.u_proj * pc.u_view * world_pos;
    /* R214-A: OpenGL proj → Vulkan clip.z [0,1] (match depth_only / CSM). */
    gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;
}
