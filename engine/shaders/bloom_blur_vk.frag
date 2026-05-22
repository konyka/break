#version 450 core

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 frag_color;

layout(push_constant) uniform PushConstants {
    layout(offset = 0) vec2 u_direction;
} pc;

layout(binding = 0) uniform sampler2D u_texture;

void main() {
    vec2 texel = 1.0 / vec2(textureSize(u_texture, 0));
    vec3 result = vec3(0.0);

    result += texture(u_texture, vUV - 4.0 * texel * pc.u_direction).rgb * 0.0162;
    result += texture(u_texture, vUV - 3.0 * texel * pc.u_direction).rgb * 0.0540;
    result += texture(u_texture, vUV - 2.0 * texel * pc.u_direction).rgb * 0.1218;
    result += texture(u_texture, vUV - 1.0 * texel * pc.u_direction).rgb * 0.1960;
    result += texture(u_texture, vUV).rgb * 0.2240;
    result += texture(u_texture, vUV + 1.0 * texel * pc.u_direction).rgb * 0.1960;
    result += texture(u_texture, vUV + 2.0 * texel * pc.u_direction).rgb * 0.1218;
    result += texture(u_texture, vUV + 3.0 * texel * pc.u_direction).rgb * 0.0540;
    result += texture(u_texture, vUV + 4.0 * texel * pc.u_direction).rgb * 0.0162;

    frag_color = vec4(result, 1.0);
}
