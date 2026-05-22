#version 450 core

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 frag_color;

layout(push_constant) uniform PushConstants {
    layout(offset = 0) float u_threshold;
} pc;

layout(binding = 0) uniform sampler2D u_scene;

void main() {
    vec3 col = texture(u_scene, vUV).rgb;
    float brightness = dot(col, vec3(0.2126, 0.7152, 0.0722));
    float contrib = max(brightness - pc.u_threshold, 0.0) / max(brightness, 0.001);
    frag_color = vec4(col * contrib, 1.0);
}
