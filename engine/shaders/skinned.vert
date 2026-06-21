#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;
layout(location = 3) in uvec4 aJoints;
layout(location = 4) in vec4 aWeights;

uniform mat4 u_view;
uniform mat4 u_proj;

layout(binding = 5) uniform samplerBuffer u_joints;  /* R103-1: match GL rhi_cmd_bind_texel_buffers unit 5 */

out vec3 vWorldPos;
out vec3 vNormal;
out vec2 vUV;

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
    gl_Position = u_proj * u_view * world_pos;
}
