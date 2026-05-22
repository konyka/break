#version 450 core

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 frag_color;

layout(push_constant) uniform PushConstants {
    layout(offset = 0) float u_bloom_strength;
} pc;

layout(binding = 0) uniform sampler2D u_scene;
layout(binding = 1) uniform sampler2D u_bloom;

void main() {
    vec3 scene = texture(u_scene, vUV).rgb;
    vec3 bloom = texture(u_bloom, vUV).rgb;
    vec3 result = scene + bloom * pc.u_bloom_strength;
    frag_color = vec4(result, 1.0);
}
