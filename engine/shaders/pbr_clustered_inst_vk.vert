#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;

/* R590: clustered INSTANCED variant — per-instance model (+ prev_model under
 * FORWARD_MRT) rides a vertex-stage SSBO because the shared texel set caps
 * at 2 bindings (already light_data/light_grid) and GL texture units are
 * exhausted. Pipeline set order for this textures+texel+storage pipeline:
 * textures@0, texel@1, storage@2, ubo@3. The push block keeps the clustered
 * frag-compatible first members (u_model@0 unused — instance matrix
 * replaces it, declared so u_view stays at 64). */
layout(push_constant) uniform PushConstants {
    mat4 u_model;       /*   0 — unused (instance matrix); offset pad */
    mat4 u_view;        /*  64 — same offset as pbr_clustered_vk.frag */
} pc;

layout(set = 2, binding = 0) readonly buffer ClusterInstances {
    vec4 data[];
} inst;

/* R589/R590: single aux-UBO binding {prev_vp, prev_model, proj} (RHI binds
 * one UBO descriptor set per call). The temporal pair leads so an accidental
 * rebind into a ForwardTemporal-expecting blinn pipeline reads correct
 * values — for instanced draws prev_model is per-instance and comes from
 * the SSBO instead, so the UBO's own prev_model is unused here. */
#ifdef FORWARD_MRT
layout(std140, set = 3, binding = 0) uniform ClusterInstUBO {
    mat4 u_prev_vp;
    mat4 u_prev_model_unused;
    mat4 u_proj;
} fru;
#else
layout(std140, set = 3, binding = 0) uniform ClusterInstProj {
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
    int idx = gl_InstanceIndex * 8;
    mat4 model = mat4(inst.data[idx], inst.data[idx + 1],
                      inst.data[idx + 2], inst.data[idx + 3]);

    vec4 world_pos = model * vec4(aPos, 1.0);
    vWorldPos = world_pos.xyz;
    vNormal = mat3(model) * aNormal;
    vUV = aUV;
    vec4 curr_clip = fru.u_proj * pc.u_view * world_pos;
#ifdef FORWARD_MRT
    mat4 prev_model = mat4(inst.data[idx + 4], inst.data[idx + 5],
                           inst.data[idx + 6], inst.data[idx + 7]);
    vec4 prev_clip = fru.u_prev_vp * prev_model * vec4(aPos, 1.0);
    v_velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
#endif
    gl_Position = curr_clip;
    /* R214-A: OpenGL proj → Vulkan clip.z [0,1] (match depth_only / CSM). */
    gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;
}
