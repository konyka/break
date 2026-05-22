#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

layout(binding = 0) uniform sampler2D u_sharp_tex;

layout(push_constant) uniform SharpParams {
    layout(offset = 0) float u_sharp_strength;
    layout(offset = 4) float u_sharp_sw;
    layout(offset = 8) float u_sharp_sh;
};

void main() {
    vec2 texel = 1.0 / vec2(u_sharp_sw, u_sharp_sh);

    vec3 c   = texture(u_sharp_tex, vUV).rgb;
    vec3 cU  = texture(u_sharp_tex, vUV + vec2(0, -texel.y)).rgb;
    vec3 cD  = texture(u_sharp_tex, vUV + vec2(0,  texel.y)).rgb;
    vec3 cL  = texture(u_sharp_tex, vUV + vec2(-texel.x, 0)).rgb;
    vec3 cR  = texture(u_sharp_tex, vUV + vec2( texel.x, 0)).rgb;

    vec3 blur = (cU + cD + cL + cR) * 0.25;
    vec3 sharp = c + (c - blur) * u_sharp_strength;

    float luma_c = dot(c, vec3(0.2126, 0.7152, 0.0722));
    float luma_min = min(dot(cU, vec3(0.2126, 0.7152, 0.0722)),
                         min(dot(cD, vec3(0.2126, 0.7152, 0.0722)),
                         min(dot(cL, vec3(0.2126, 0.7152, 0.0722)),
                             dot(cR, vec3(0.2126, 0.7152, 0.0722)))));
    float luma_max = max(dot(cU, vec3(0.2126, 0.7152, 0.0722)),
                         max(dot(cD, vec3(0.2126, 0.7152, 0.0722)),
                         max(dot(cL, vec3(0.2126, 0.7152, 0.0722)),
                             dot(cR, vec3(0.2126, 0.7152, 0.0722)))));
    luma_min = min(luma_min, luma_c);
    luma_max = max(luma_max, luma_c);

    float luma_sharp = dot(sharp, vec3(0.2126, 0.7152, 0.0722));
    float clamped = clamp(luma_sharp, luma_min, luma_max);
    sharp = mix(sharp, c, (luma_sharp - clamped) / max(luma_sharp - luma_c, 0.001));

    fragColor = vec4(max(sharp, vec3(0.0)), 1.0);
}
