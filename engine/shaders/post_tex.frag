#version 450 core

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 frag_color;

uniform sampler2D u_texture;

void main() {
    frag_color = texture(u_texture, vUV);
}
