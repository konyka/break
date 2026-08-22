#version 330 core

in vec2 vUV;
in vec4 vColor;

out vec4 frag_color;

uniform sampler2D u_image;

void main() {
    vec4 texel = texture(u_image, vUV);
    frag_color = texel * vColor;
}
