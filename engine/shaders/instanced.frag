#version 450 core

layout(location = 0) in vec3 vWorldPos;
layout(location = 1) in vec3 vNormal;
layout(location = 2) in vec2 vUV;

uniform vec3 u_light_dir;
uniform vec3 u_light_color;
uniform vec3 u_ambient;
uniform vec3 u_camera_pos;

layout(binding = 0) uniform sampler2D u_albedo;

layout(location = 0) out vec4 FragColor;

void main() {
    vec3 N = normalize(vNormal);
    vec3 L = normalize(-u_light_dir);
    vec3 V = normalize(u_camera_pos - vWorldPos);
    vec3 H = normalize(L + V);

    float diff = max(dot(N, L), 0.0);
    float spec = pow(max(dot(N, H), 0.0), 32.0);
    vec3 albedo = texture(u_albedo, vUV).rgb;

    vec3 color = u_ambient * albedo + u_light_color * (diff + spec * 0.15) * albedo;
    FragColor = vec4(color, 1.0);
}
