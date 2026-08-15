#version 450 core

/* R560: Deferred G-Buffer write pass -- skinned vertex stage (Vulkan).
 * Push block matches gbuffer_vk.vert (u_model@0 u_view@64 u_proj@128
 * u_prev_mvp@192); the joint texel buffer sits in the texel descriptor set
 * (set=1 binding=0) like skinned_vk.vert. */

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;
layout(location = 3) in uvec4 aJoints;
layout(location = 4) in vec4 aWeights;

layout(location = 0) out vec3 v_world_pos;
layout(location = 1) out vec3 v_normal;
layout(location = 2) out vec2 v_texcoord;
layout(location = 3) out vec2 v_velocity;

layout(push_constant) uniform Push {
    mat4 u_model;
    mat4 u_view;
    mat4 u_proj;
    mat4 u_prev_mvp;
} pc;

layout(set = 1, binding = 0) uniform samplerBuffer u_joints;

void main() {
    mat4 skin = mat4(0.0);
    mat4 prev_skin = mat4(0.0);
    for (int i = 0; i < 4; i++) {
        int j = int(aJoints[i]);
        mat4 joint = mat4(
            texelFetch(u_joints, j * 4 + 0),
            texelFetch(u_joints, j * 4 + 1),
            texelFetch(u_joints, j * 4 + 2),
            texelFetch(u_joints, j * 4 + 3)
        );
        skin += aWeights[i] * joint;
        mat4 prev_joint = mat4(
            texelFetch(u_joints, 512 + j * 4 + 0),
            texelFetch(u_joints, 512 + j * 4 + 1),
            texelFetch(u_joints, 512 + j * 4 + 2),
            texelFetch(u_joints, 512 + j * 4 + 3));
        prev_skin += aWeights[i] * prev_joint;
    }

    vec4 world_pos = pc.u_model * (skin * vec4(aPos, 1.0));
    v_world_pos = world_pos.xyz;
    v_normal = mat3(pc.u_model) * (mat3(skin) * aNormal);
    v_texcoord = aUV;
    vec4 curr_clip = pc.u_proj * pc.u_view * world_pos;
    vec4 prev_clip = pc.u_prev_mvp * (prev_skin * vec4(aPos, 1.0));
    vec2 curr_ndc = curr_clip.xy / curr_clip.w;
    vec2 prev_ndc = prev_clip.xy / prev_clip.w;
    v_velocity  = curr_ndc - prev_ndc;
    gl_Position = curr_clip;
    /* R214-A: OpenGL proj → Vulkan clip.z [0,1] (match depth_only / CSM). */
    gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;
}
