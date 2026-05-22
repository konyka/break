#version 330 core

in vec2 vUV;
out vec4 frag_color;

uniform sampler2D u_scene;
uniform sampler2D u_bloom;
uniform float u_bloom_strength = 0.3;

void main() {
    vec3 scene = texture(u_scene, vUV).rgb;
    vec3 bloom = texture(u_bloom, vUV).rgb;
    vec3 result = scene + bloom * u_bloom_strength;
    frag_color = vec4(result, 1.0);
}
