#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

layout(binding = 0) uniform sampler2D u_cine_tex;

layout(push_constant) uniform CineParams {
    layout(offset = 0)  float u_cine_aberration;
    layout(offset = 4)  float u_cine_vignette;
    layout(offset = 8)  float u_cine_grain;
    layout(offset = 12) float u_cine_time;
    layout(offset = 16) float u_cine_sw;
    layout(offset = 20) float u_cine_sh;
};

float hash(vec2 p) {
    vec3 p3 = fract(vec3(p.xyx) * 0.1031);
    p3 += dot(p3, p3.yzx + 33.33);
    return fract((p3.x + p3.y) * p3.z);
}

void main() {
    vec2 texel_size = vec2(1.0 / u_cine_sw, 1.0 / u_cine_sh);
    vec2 dir = vUV - 0.5;
    float dist = length(dir);

    vec2 r_offset = dir * u_cine_aberration * texel_size;
    vec2 g_offset = vec2(0.0);
    vec2 b_offset = -dir * u_cine_aberration * texel_size;

    float r = texture(u_cine_tex, vUV + r_offset).r;
    float g = texture(u_cine_tex, vUV + g_offset).g;
    float b = texture(u_cine_tex, vUV + b_offset).b;
    vec3 color = vec3(r, g, b);

    float vignette = 1.0 - dist * dist * u_cine_vignette;
    color *= max(vignette, 0.0);

    float noise = hash(vUV * vec2(u_cine_sw, u_cine_sh) + fract(u_cine_time)) - 0.5;
    color += noise * u_cine_grain;

    fragColor = vec4(max(color, vec3(0.0)), 1.0);
}
