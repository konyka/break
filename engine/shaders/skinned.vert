#version 430 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;
layout(location = 3) in uvec4 aJoints;
layout(location = 4) in vec4 aWeights;

uniform mat4 u_view;
uniform mat4 u_proj;
#ifdef FORWARD_MRT
layout(std140, binding = 0) uniform ForwardTemporal {
    mat4 u_prev_vp;
    mat4 u_prev_model_unused;
};
#endif

layout(binding = 5) uniform samplerBuffer u_joints;  /* R103-1: match GL rhi_cmd_bind_texel_buffers unit 5 */

out vec3 vWorldPos;
out vec3 vNormal;
out vec2 vUV;
#ifdef FORWARD_MRT
out vec2 v_velocity;
#endif

void main() {
    mat4 skin = mat4(0.0);
#ifdef FORWARD_MRT
    mat4 prev_skin = mat4(0.0);
#endif
    for (int i = 0; i < 4; i++) {
        int j = int(aJoints[i]);
        mat4 joint = mat4(
            texelFetch(u_joints, j * 4 + 0),
            texelFetch(u_joints, j * 4 + 1),
            texelFetch(u_joints, j * 4 + 2),
            texelFetch(u_joints, j * 4 + 3)
        );
        skin += aWeights[i] * joint;
#ifdef FORWARD_MRT
        mat4 prev_joint = mat4(
            texelFetch(u_joints, 512 + j * 4 + 0),
            texelFetch(u_joints, 512 + j * 4 + 1),
            texelFetch(u_joints, 512 + j * 4 + 2),
            texelFetch(u_joints, 512 + j * 4 + 3));
        prev_skin += aWeights[i] * prev_joint;
#endif
    }

    vec4 world_pos = skin * vec4(aPos, 1.0);
    vWorldPos = world_pos.xyz;
    vNormal = mat3(skin) * aNormal;
    vUV = aUV;
    vec4 curr_clip = u_proj * u_view * world_pos;
#ifdef FORWARD_MRT
    vec4 prev_clip = u_prev_vp * prev_skin * vec4(aPos, 1.0);
    v_velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
#endif
    gl_Position = curr_clip;
}
