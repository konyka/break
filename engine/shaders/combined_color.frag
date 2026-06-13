#version 450

/* Combined tonemap + colour grade + cinematic in a single pass (GL).
 * See the _vk variant for details. */

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

uniform sampler2D u_color_tex;

uniform float u_tm_exposure;
uniform float u_tm_gamma;
uniform int   u_tm_mode;
uniform float u_cg_saturation;
uniform float u_cg_contrast;
uniform float u_cg_brightness;
uniform float u_cg_temperature;
uniform float u_cg_tint;
uniform float u_cine_aberration;
uniform float u_cine_vignette;
uniform float u_cine_grain;
uniform float u_cine_time;
uniform float u_screen_w;
uniform float u_screen_h;

const vec3 LUMA = vec3(0.2126, 0.7152, 0.0722);

vec3 aces_fit(vec3 x) {
    const float a = 2.51, b = 0.03, c = 2.43, d = 0.59, e = 0.14;
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

float hash(vec2 p) {
    vec3 p3 = fract(vec3(p.xyx) * 0.1031);
    p3 += dot(p3, p3.yzx + 33.33);
    return fract((p3.x + p3.y) * p3.z);
}

void main() {
    vec2 texel = vec2(1.0 / u_screen_w, 1.0 / u_screen_h);
    vec2 dir = vUV - 0.5;
    float dist = length(dir);

    vec2 ca = dir * u_cine_aberration * texel;
    vec3 hdr;
    hdr.r = texture(u_color_tex, vUV + ca).r;
    hdr.g = texture(u_color_tex, vUV).g;
    hdr.b = texture(u_color_tex, vUV - ca).b;

    hdr *= u_tm_exposure;
    vec3 ldr;
    if (u_tm_mode == 1)      ldr = agx(hdr);
    else if (u_tm_mode == 2) ldr = khronos_neutral(hdr);
    else                     ldr = aces_fit(hdr);
    ldr = pow(max(ldr, vec3(0.0)), vec3(1.0 / u_tm_gamma));

    float luma = dot(ldr, LUMA);
    ldr = mix(vec3(luma), ldr, u_cg_saturation);
    ldr = (ldr - 0.5) * u_cg_contrast + 0.5;
    ldr *= u_cg_brightness;
    vec3 warm = vec3(1.0, 0.85, 0.7);
    vec3 cool = vec3(0.7, 0.85, 1.0);
    ldr *= mix(cool, warm, u_cg_temperature * 0.5 + 0.5);
    ldr.g += u_cg_tint * 0.05;

    float vignette = 1.0 - dist * dist * u_cine_vignette;
    ldr *= max(vignette, 0.0);
    float noise = hash(vUV * vec2(u_screen_w, u_screen_h) + fract(u_cine_time)) - 0.5;
    ldr += noise * u_cine_grain;

    fragColor = vec4(clamp(ldr, 0.0, 1.0), 1.0);
}
