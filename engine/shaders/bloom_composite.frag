#version 450 core

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 frag_color;

uniform sampler2D u_scene;
uniform sampler2D u_bloom;
uniform float u_bloom_strength;

void main() {
    vec3 scene = texture(u_scene, vUV).rgb;
    vec3 bloom = texture(u_bloom, vUV).rgb;
    vec3 result = scene + bloom * u_bloom_strength;
    frag_color = vec4(result, 1.0);
}
