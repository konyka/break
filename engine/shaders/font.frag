#version 330 core

in vec2 vUV;
in vec4 vColor;

out vec4 frag_color;

uniform sampler2D u_atlas;

void main() {
    float a = texture(u_atlas, vUV).r;
    frag_color = vec4(vColor.rgb, vColor.a * a);
}
