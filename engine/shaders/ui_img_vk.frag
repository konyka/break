#version 450 core

layout(location = 0) in vec2 vUV;
layout(location = 1) in vec4 vColor;

layout(location = 0) out vec4 frag_color;

layout(binding = 0) uniform sampler2D u_image;

void main() {
    vec4 texel = texture(u_image, vUV);
    frag_color = texel * vColor;
}
