#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

uniform sampler2D u_tm_hdr;
uniform sampler2D u_tm_lum;

uniform float u_tm_exposure;
uniform float u_tm_gamma;
uniform int u_tm_mode;

vec3 aces_fit(vec3 x) {
    float a = 2.51;
    float b = 0.03;
    float c = 2.43;
    float d = 0.59;
    float e = 0.14;
    return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}

vec3 agx(vec3 val) {
    val = max(val, 0.0);
    val = val * mat3(
        0.84247906, 0.04232824, 0.04237565,
        0.07843371, 0.87846855, 0.07843397,
        0.07922376, 0.07916613, 0.87923044);
    val = clamp(val, 0.0, 1.0);
    val = log2(val + 0.0001);
    val = (val * 1.7 + 6.5) / 11.7;
    val = clamp(val, 0.0, 1.0);
    val = val * val * (3.0 - 2.0 * val);
    val = val * mat3(
        1.1968790, -0.0525374, -0.0525374,
        -0.0920852, 1.1515179, -0.0920852,
        -0.0398265, -0.0398265, 1.1637448);
    return clamp(val, 0.0, 1.0);
}

vec3 khronos_neutral(vec3 c) {
    c = max(c, 0.0);
    c = c * (2.51 * c + 0.03) / (c * (2.43 * c + 0.59) + 0.14);
    return clamp(c, 0.0, 1.0);
}

void main() {
    float scene_luma = texture(u_tm_lum, vec2(0.5)).r;
    float auto_exp = scene_luma > 0.01 ? 1.0 / (scene_luma + 0.5) : u_tm_exposure;
    float exposure = mix(u_tm_exposure, auto_exp, 0.8);

    vec3 hdr = texture(u_tm_hdr, vUV).rgb * exposure;

    vec3 ldr;
    if (u_tm_mode == 1) {
        ldr = agx(hdr);
    } else if (u_tm_mode == 2) {
        ldr = khronos_neutral(hdr);
    } else {
        ldr = aces_fit(hdr);
    }

    ldr = pow(max(ldr, vec3(0.0)), vec3(1.0 / u_tm_gamma));

    fragColor = vec4(clamp(ldr, 0.0, 1.0), 1.0);
}
