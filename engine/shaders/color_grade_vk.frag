#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

layout(binding = 0) uniform sampler2D u_cg_tex;

layout(push_constant) uniform CGParams {
    layout(offset = 0)  float u_cg_saturation;
    layout(offset = 4)  float u_cg_contrast;
    layout(offset = 8)  float u_cg_brightness;
    layout(offset = 12) float u_cg_temperature;
    layout(offset = 16) float u_cg_tint;
};

vec3 adjust_contrast(vec3 c, float contrast) {
    return (c - 0.5) * contrast + 0.5;
}

vec3 adjust_saturation(vec3 c, float sat) {
    float luma = dot(c, vec3(0.2126, 0.7152, 0.0722));
    return mix(vec3(luma), c, sat);
}

vec3 white_balance(vec3 c, float temp, float tint) {
    vec3 warm = vec3(1.0, 0.85, 0.7);
    vec3 cool = vec3(0.7, 0.85, 1.0);

    vec3 t = mix(cool, warm, temp * 0.5 + 0.5);
    c *= t;

    c.g += tint * 0.05;

    return c;
}

void main() {
    vec3 c = texture(u_cg_tex, vUV).rgb;

    c = adjust_saturation(c, u_cg_saturation);
    c = adjust_contrast(c, u_cg_contrast);
    c *= u_cg_brightness;
    c = white_balance(c, u_cg_temperature, u_cg_tint);

    fragColor = vec4(clamp(c, 0.0, 1.0), 1.0);
}
