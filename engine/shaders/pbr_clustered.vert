#version 450 core

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;

/* R589: FORWARD_MRT velocity contract (blinn_phong precedent) — temporal
 * pair reads offsets 0/64 of the shared clustered frame UBO {prev_vp,
 * prev_model, proj} bound at binding 0 (VK twin: set=2 binding=0, same
 * layout; u_proj stays a plain uniform on GL). */
#ifdef FORWARD_MRT
layout(std140, binding = 0) uniform ClusterVertTemporal {
    mat4 u_prev_vp;
    mat4 u_prev_model;
};
out vec2 v_velocity;
#endif

layout(location = 0) out vec3 vWorldPos;
layout(location = 1) out vec3 vNormal;
layout(location = 2) out vec2 vUV;

void main() {
    vec4 world_pos = u_model * vec4(aPos, 1.0);
    vWorldPos = world_pos.xyz;
    vNormal = mat3(u_model) * aNormal;
    vUV = aUV;
    vec4 curr_clip = u_proj * u_view * world_pos;
#ifdef FORWARD_MRT
    vec4 prev_clip = u_prev_vp * u_prev_model * vec4(aPos, 1.0);
    v_velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
#endif
    gl_Position = curr_clip;
}
