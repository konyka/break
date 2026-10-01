#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;

/* R586: the clustered push block is reduced to what the vert actually loads
 * — u_model@0 / u_view@64, byte-compatible with the frag block's first two
 * members (the old u_proj@128 / u_camera_pos@160 tail CONTRADICTED the frag
 * layout — R579-C — and loading u_proj@128 crossed the 128-byte push-load
 * line that kills texel-set pipelines on the NVIDIA 616.56 hybrid driver,
 * R579-J/K). proj now rides the always-appended auxiliary UBO set (set=2
 * binding=0 for this texel pipeline — textures@0, texel@1, ubo@2), bound
 * via rhi_cmd_bind_uniform_buffer. */
layout(push_constant) uniform PushConstants {
    mat4 u_model;       /*   0 — same offset as pbr_clustered_vk.frag */
    mat4 u_view;        /*  64 — same offset as pbr_clustered_vk.frag */
} pc;

/* R589: FORWARD_MRT velocity contract (blinn_phong_vk precedent) — required
 * for the production forward MRT pass (RT1 = per-object velocity). The aux
 * UBO carries {prev_vp, prev_model, proj} in ONE binding: the RHI binds a
 * single UBO descriptor set per call, so two bindings never coexist; the
 * temporal pair sits at offsets 0/64 so an accidental rebind of this buffer
 * into a ForwardTemporal-expecting (blinn-family) pipeline still reads the
 * correct {prev_vp, prev_model}. */
#ifdef FORWARD_MRT
layout(std140, set = 2, binding = 0) uniform ClusterVertUBO {
    mat4 u_prev_vp;
    mat4 u_prev_model;
    mat4 u_proj;
} cvp;
#else
layout(std140, set = 2, binding = 0) uniform ClusterVertProj {
    mat4 u_proj;
} cvp;
#endif

layout(location = 0) out vec3 vWorldPos;
layout(location = 1) out vec3 vNormal;
layout(location = 2) out vec2 vUV;
#ifdef FORWARD_MRT
layout(location = 3) out vec2 v_velocity;
#endif

void main() {
    vec4 world_pos = pc.u_model * vec4(aPos, 1.0);
    vWorldPos = world_pos.xyz;
    vNormal = mat3(pc.u_model) * aNormal;
    vUV = aUV;
    vec4 curr_clip = cvp.u_proj * pc.u_view * world_pos;
#ifdef FORWARD_MRT
    vec4 prev_clip = cvp.u_prev_vp * cvp.u_prev_model * vec4(aPos, 1.0);
    v_velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
#endif
    gl_Position = curr_clip;
    /* R214-A: OpenGL proj → Vulkan clip.z [0,1] (match depth_only / CSM). */
    gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;
}
