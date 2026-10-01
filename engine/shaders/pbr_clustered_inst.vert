#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;

/* R590: clustered INSTANCED variant (GL twin) — instances ride a vertex
 * SSBO at storage binding 0 (GL texture units are exhausted: 5/6 texel,
 * 7-15 shared/IBL). u_view/u_proj stay plain uniforms (locations queried
 * per pipeline). */
uniform mat4 u_view;
uniform mat4 u_proj;

layout(std430, binding = 0) readonly buffer ClusterInstances {
    vec4 data[];
} inst;

/* R589: FORWARD_MRT velocity contract — temporal pair at offsets 0/64 of
 * the shared clustered frame UBO {prev_vp, prev_model, proj} (uniform
 * binding 0; the UBO's own prev_model is unused — per-instance prev_model
 * comes from the SSBO). */
#ifdef FORWARD_MRT
layout(std140, binding = 0) uniform ClusterInstTemporal {
    mat4 u_prev_vp;
    mat4 u_prev_model_unused;
};
out vec2 v_velocity;
#endif

layout(location = 0) out vec3 vWorldPos;
layout(location = 1) out vec3 vNormal;
layout(location = 2) out vec2 vUV;

void main() {
    int idx = gl_InstanceID * 8; /* GL twin: gl_InstanceID (VK: gl_InstanceIndex) */
    mat4 model = mat4(inst.data[idx], inst.data[idx + 1],
                      inst.data[idx + 2], inst.data[idx + 3]);

    vec4 world_pos = model * vec4(aPos, 1.0);
    vWorldPos = world_pos.xyz;
    vNormal = mat3(model) * aNormal;
    vUV = aUV;
    vec4 curr_clip = u_proj * u_view * world_pos;
#ifdef FORWARD_MRT
    mat4 prev_model = mat4(inst.data[idx + 4], inst.data[idx + 5],
                           inst.data[idx + 6], inst.data[idx + 7]);
    vec4 prev_clip = u_prev_vp * prev_model * vec4(aPos, 1.0);
    v_velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
#endif
    gl_Position = curr_clip;
}
