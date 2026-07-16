#version 450 core

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 frag_color;

/* R220-B: Match bind_material_textures (scene@0, bloom@shadow@1) and VK. */
layout(binding = 0) uniform sampler2D u_scene;
layout(binding = 1) uniform sampler2D u_bloom;
uniform float u_bloom_strength;

void main() {
    vec3 scene = texture(u_scene, vUV).rgb;
    vec3 bloom = texture(u_bloom, vUV).rgb;
    vec3 result = scene + bloom * u_bloom_strength;
    frag_color = vec4(result, 1.0);
}
