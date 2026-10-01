#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;
layout(location = 3) in uvec4 aJoints;
layout(location = 4) in vec4 aWeights;

/* R591: clustered SKINNED variant (GL twin) — joints ride a vertex SSBO at
 * storage binding 0 (GL texture units exhausted: 5/6 texel, 7-15
 * shared/IBL). u_view/u_proj stay plain uniforms. */
uniform mat4 u_view;
uniform mat4 u_proj;

/* Current pose at [0, 512) vec4 slots, previous pose at [512, 1024). */
layout(std430, binding = 0) readonly buffer ClusterJoints {
    vec4 data[];
} joints;

/* R589: FORWARD_MRT velocity contract — temporal pair at offsets 0/64 of
 * the shared clustered frame UBO (uniform binding 0); prev_skin comes from
 * the previous-pose half of the joint SSBO instead. */
#ifdef FORWARD_MRT
layout(std140, binding = 0) uniform ClusterSkinTemporal {
    mat4 u_prev_vp;
    mat4 u_prev_model_unused;
};
out vec2 v_velocity;
#endif

layout(location = 0) out vec3 vWorldPos;
layout(location = 1) out vec3 vNormal;
layout(location = 2) out vec2 vUV;

void main() {
    mat4 skin = mat4(0.0);
#ifdef FORWARD_MRT
    mat4 prev_skin = mat4(0.0);
#endif
    for (int i = 0; i < 4; i++) {
        int j = int(aJoints[i]);
        mat4 joint = mat4(joints.data[j * 4 + 0], joints.data[j * 4 + 1],
                          joints.data[j * 4 + 2], joints.data[j * 4 + 3]);
        skin += aWeights[i] * joint;
#ifdef FORWARD_MRT
        mat4 prev_joint = mat4(joints.data[512 + j * 4 + 0], joints.data[512 + j * 4 + 1],
                               joints.data[512 + j * 4 + 2], joints.data[512 + j * 4 + 3]);
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
