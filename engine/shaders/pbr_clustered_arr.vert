#version 450 core
/* R592: clustered texture-ARRAY variant (GL twin) — forwards the indirect
 * cmd's first_instance as the sampler2DArray layer (blinn_phong_arr
 * precedent; the ARB suffix is required under #version 450). */
#extension GL_ARB_shader_draw_parameters : require

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

/* R589: temporal pair at offsets 0/64 of the shared clustered frame UBO
 * {prev_vp, prev_model, proj} (uniform binding 0); the frag's CLUSTERED_ARR
 * factor block reads offsets 192+ of the same buffer. */
#ifdef FORWARD_MRT
layout(std140, binding = 0) uniform ClusterArrTemporal {
    mat4 u_prev_vp;
    mat4 u_prev_model;
};
out vec2 v_velocity;
#endif

/* Locations must match pbr_clustered.frag, whose base varyings carry
 * explicit locations 0-2 (same as the other clustered vertex variants);
 * vLayer and v_velocity stay name-matched. */
layout(location = 0) out vec3 vWorldPos;
layout(location = 1) out vec3 vNormal;
layout(location = 2) out vec2 vUV;
flat out uint vLayer;

#ifdef LOD_FADE
flat out float vLodFade;
#endif
void main() {
#ifdef LOD_FADE
    uint fade_code = uint(gl_BaseInstanceARB) >> 16;
    vLodFade = fade_code == 0u ? 0.0 : float(int(fade_code) - 16);
#endif
    vec4 world_pos = u_model * vec4(aPos, 1.0);
    vWorldPos = world_pos.xyz;
    vNormal = mat3(u_model) * aNormal;
    vUV = aUV;
#ifdef LOD_FADE
    vLayer = uint(gl_BaseInstanceARB) & 0xFFFFu;
#else
    vLayer = uint(gl_BaseInstanceARB);
#endif
    vec4 curr_clip = u_proj * u_view * world_pos;
#ifdef FORWARD_MRT
    vec4 prev_clip = u_prev_vp * u_prev_model * vec4(aPos, 1.0);
    v_velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
#endif
    gl_Position = curr_clip;
}
