#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

uniform sampler2D u_tm_hdr;

uniform float u_tm_exposure;
uniform float u_tm_gamma;
uniform float u_tm_aberration;
uniform float u_tm_vignette;
uniform float u_tm_grain;
uniform float u_tm_time;
uniform float u_tm_screen_w;
uniform float u_tm_screen_h;
uniform float u_tm_saturation;
uniform float u_tm_contrast;
uniform float u_tm_brightness;
uniform float u_tm_temperature;
uniform float u_tm_tint;

vec3 aces_fit(vec3 x) {
    float a = 2.51;
    float b = 0.03;
    float c = 2.43;
    float d = 0.59;
    float e = 0.14;
    return clamp((x * (a * x + b)) / (x * (c * x + d) + e), 0.0, 1.0);
}

float hash(vec2 p) {
    vec3 p3 = fract(vec3(p.xyx) * 0.1031);
    p3 += dot(p3, p3.yzx + 33.33);
    return fract((p3.x + p3.y) * p3.z);
}

void main() {
    vec2 center = vUV - 0.5;
    float dist = length(center);

    vec2 r_offset = center * u_tm_aberration * dist;
    vec2 g_offset = center * u_tm_aberration * dist * 0.5;
    vec2 b_offset = vec2(0.0);

    vec3 hdr;
    hdr.r = texture(u_tm_hdr, vUV + r_offset).r;
    hdr.g = texture(u_tm_hdr, vUV + g_offset).g;
    hdr.b = texture(u_tm_hdr, vUV + b_offset).b;
    hdr *= u_tm_exposure;

    vec3 ldr = aces_fit(hdr);

    float vig = 1.0 - dist * dist * u_tm_vignette;
    ldr *= max(vig, 0.0);

    float noise = hash(vUV * u_tm_screen_w + u_tm_time) * 2.0 - 1.0;
    ldr += noise * u_tm_grain;

    ldr = pow(max(ldr, vec3(0.0)), vec3(1.0 / u_tm_gamma));

    float luma = dot(ldr, vec3(0.2126, 0.7152, 0.0722));
    ldr = mix(vec3(luma), ldr, u_tm_saturation);

    ldr = (ldr - 0.5) * u_tm_contrast + 0.5;
    ldr *= u_tm_brightness;

    vec3 warm = vec3(1.0, 0.85, 0.7);
    vec3 cool = vec3(0.7, 0.85, 1.0);
    vec3 wb = mix(cool, warm, u_tm_temperature * 0.5 + 0.5);
    ldr *= wb;
    ldr.g += u_tm_tint * 0.05;

    fragColor = vec4(clamp(ldr, 0.0, 1.0), 1.0);
}
