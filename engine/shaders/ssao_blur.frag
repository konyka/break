#version 450 core

layout(location = 0) in vec2 vUV;

layout(binding = 0) uniform sampler2D u_ssao;

layout(location = 0) out vec4 frag_color;

void main() {
    vec2 texel = 1.0 / textureSize(u_ssao, 0);

    float result = 0.0;
    result += texture(u_ssao, vUV + vec2(-texel.x, 0.0)).r;
    result += texture(u_ssao, vUV + vec2( texel.x, 0.0)).r;
    result += texture(u_ssao, vUV + vec2(0.0, -texel.y)).r;
    result += texture(u_ssao, vUV + vec2(0.0,  texel.y)).r;
    result += texture(u_ssao, vUV).r * 2.0;

    frag_color = vec4(result / 6.0, result / 6.0, result / 6.0, 1.0);
}
