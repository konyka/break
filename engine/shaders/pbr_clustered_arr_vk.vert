#version 450 core
/* R592: clustered texture-ARRAY variant (VK) — forwards the indirect cmd's
 * first_instance as the sampler2DArray layer (blinn_phong_arr_vk precedent;
 * the ARB suffix is required under #version 450). Mega verts are
 * pre-transformed to world space (u_model = identity, written anyway).
 * No storage set in this variant — pipeline set order is the static
 * clustered one: textures@0, texel@1, ubo@2. */
#extension GL_ARB_shader_draw_parameters : require

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;

layout(push_constant) uniform PushConstants {
    mat4 u_model;       /*   0 — same offset as pbr_clustered_vk.frag */
    mat4 u_view;        /*  64 — same offset as pbr_clustered_vk.frag */
} pc;

/* R589: single aux-UBO binding {prev_vp, prev_model, proj}; the frag's
 * CLUSTERED_ARR factor block reads offsets 192+ of the same buffer. */
#ifdef FORWARD_MRT
layout(std140, set = 2, binding = 0) uniform ClusterArrUBO {
    mat4 u_prev_vp;
    mat4 u_prev_model;
    mat4 u_proj;
} fru;
#else
layout(std140, set = 2, binding = 0) uniform ClusterArrProj {
    mat4 u_proj;
} fru;
#endif

layout(location = 0) out vec3 vWorldPos;
layout(location = 1) out vec3 vNormal;
layout(location = 2) out vec2 vUV;
layout(location = 3) flat out uint vLayer;
#ifdef FORWARD_MRT
layout(location = 4) out vec2 v_velocity;
#endif

void main() {
    vec4 world_pos = pc.u_model * vec4(aPos, 1.0);
    vWorldPos = world_pos.xyz;
    vNormal = mat3(pc.u_model) * aNormal;
    vUV = aUV;
    vLayer = uint(gl_BaseInstanceARB);
    vec4 curr_clip = fru.u_proj * pc.u_view * world_pos;
#ifdef FORWARD_MRT
    vec4 prev_clip = fru.u_prev_vp * fru.u_prev_model * vec4(aPos, 1.0);
    v_velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
#endif
    gl_Position = curr_clip;
    /* R214-A: OpenGL proj → Vulkan clip.z [0,1] (match depth_only / CSM). */
    gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;
}
