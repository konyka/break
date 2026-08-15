#version 430 core

/* R560: Deferred G-Buffer write pass -- skinned vertex stage (GL).
 * Same joint texel-buffer contract as skinned.vert (binding 5, current pose
 * at 0 and previous-frame pose at 512 Mat4s), but writes the four G-Buffer
 * varyings used by gbuffer.frag and computes per-object velocity from the
 * previous skin under u_prev_mvp. */

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;
layout(location = 3) in uvec4 aJoints;
layout(location = 4) in vec4 aWeights;

layout(location = 0) out vec3 v_world_pos;
layout(location = 1) out vec3 v_normal;
layout(location = 2) out vec2 v_texcoord;
layout(location = 3) out vec2 v_velocity;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;
uniform mat4 u_prev_mvp;

layout(binding = 5) uniform samplerBuffer u_joints;  /* R103-1: match GL rhi_cmd_bind_texel_buffers unit 5 */

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

    vec4 world_pos = u_model * (skin * vec4(aPos, 1.0));
    v_world_pos = world_pos.xyz;
    v_normal = mat3(u_model) * (mat3(skin) * aNormal);
    v_texcoord = aUV;
    vec4 curr_clip = u_proj * u_view * world_pos;
    vec4 prev_clip = u_prev_mvp * (prev_skin * vec4(aPos, 1.0));
    vec2 curr_ndc = curr_clip.xy / curr_clip.w;
    vec2 prev_ndc = prev_clip.xy / prev_clip.w;
    v_velocity  = curr_ndc - prev_ndc;
    gl_Position = curr_clip;
}
