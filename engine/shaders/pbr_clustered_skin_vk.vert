#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;
layout(location = 3) in uvec4 aJoints;
layout(location = 4) in vec4 aWeights;

/* R591: clustered SKINNED variant — joint matrices ride a vertex-stage SSBO
 * (same R590 rationale: the shared texel set caps at 2 bindings — already
 * light_data/light_grid — and GL texture units are exhausted). Pipeline set
 * order: textures@0, texel@1, storage@2, ubo@3. The push block keeps the
 * clustered frag-compatible first members (u_model@0 unused — the skin
 * matrix replaces it, declared so u_view stays at 64). */
layout(push_constant) uniform PushConstants {
    mat4 u_model;       /*   0 — unused (skin matrix); offset pad */
    mat4 u_view;        /*  64 — same offset as pbr_clustered_vk.frag */
} pc;

/* Current pose mat4s at [0, 512) vec4 slots, previous pose at [512, 1024)
 * (blinn skinned_vk texel contract — 128 joints x 4 columns each). */
layout(set = 2, binding = 0) readonly buffer ClusterJoints {
    vec4 data[];
} joints;

/* R589/R591: single aux-UBO binding {prev_vp, prev_model_unused, proj} —
 * prev_skin comes from the previous-pose half of the joint SSBO instead. */
#ifdef FORWARD_MRT
layout(std140, set = 3, binding = 0) uniform ClusterSkinUBO {
    mat4 u_prev_vp;
    mat4 u_prev_model_unused;
    mat4 u_proj;
} fru;
#else
layout(std140, set = 3, binding = 0) uniform ClusterSkinProj {
    mat4 u_proj;
} fru;
#endif

layout(location = 0) out vec3 vWorldPos;
layout(location = 1) out vec3 vNormal;
layout(location = 2) out vec2 vUV;
#ifdef FORWARD_MRT
layout(location = 3) out vec2 v_velocity;
#endif

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
    vec4 curr_clip = fru.u_proj * pc.u_view * world_pos;
#ifdef FORWARD_MRT
    vec4 prev_clip = fru.u_prev_vp * prev_skin * vec4(aPos, 1.0);
    v_velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
#endif
    gl_Position = curr_clip;
    /* R214-A: OpenGL proj → Vulkan clip.z [0,1] (match depth_only / CSM). */
    gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;
}
