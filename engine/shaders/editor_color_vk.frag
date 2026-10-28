#version 450 core

layout(push_constant) uniform PushConstants {
    mat4 u_mvp;
    vec4 u_color;
} pc;

layout(location = 0) out vec4 frag_color;

void main() {
    frag_color = pc.u_color;
}
