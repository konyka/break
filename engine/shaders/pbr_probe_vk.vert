#version 450 core

/* R579-I probe 2: THREE mat4s (model/view/proj, 192B) — binary-search the
 * clustered block death between 1 mat4 (alive) and 13 members/248B (dead). */
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;

layout(push_constant) uniform PC {
    mat4 u_model;
    mat4 u_view;
    mat4 u_proj;
} pc;

layout(location = 0) out vec3 vWorldPos;
layout(location = 1) out vec3 vNormal;
layout(location = 2) out vec2 vUV;

void main() {
    vWorldPos = aPos;
    vNormal = aNormal;
    vUV = aUV;
    gl_Position = pc.u_proj * pc.u_view * pc.u_model * vec4(aPos, 1.0);
    gl_Position.z = (gl_Position.z + gl_Position.w) * 0.5;
}
