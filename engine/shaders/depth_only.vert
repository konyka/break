#version 450 core

layout(push_constant) uniform PushConstants {
    mat4 u_model;
    mat4 u_light_vp;
} pc;

layout(location = 0) in vec3 a_pos;

void main() {
    gl_Position = pc.u_light_vp * vec4(a_pos, 1.0);
}
