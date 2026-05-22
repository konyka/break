#version 450 core

layout(location = 0) in vec3 aPos;

layout(push_constant) uniform PushConstants {
    mat4 u_light_mvp;
} pc;

void main() {
    gl_Position = pc.u_light_mvp * vec4(aPos, 1.0);
}
