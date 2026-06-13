#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

layout(binding = 0) uniform sampler2D tex;

uniform float u_ca_strength;
uniform float u_vignette_strength;
uniform float u_vignette_softness;
uniform float u_grain_strength;

float interleaved_gradient_noise(vec2 p) {
    vec3 magic = vec3(0.06711056f, 0.00583715f, 52.9829189f);
    return fract(magic.z * fract(dot(p, magic.xy)));
}

void main() {
    vec2 uv = vUV;
    vec2 center = uv - 0.5;

    vec3 color;
    float ca_offset = u_ca_strength * length(center);
    color.r = texture(tex, uv + center * ca_offset).r;
    color.g = texture(tex, uv).g;
    color.b = texture(tex, uv - center * ca_offset).b;

    float dist = length(center);
    float vignette = 1.0 - smoothstep(u_vignette_softness, 0.8, dist * u_vignette_strength);
    color *= vignette;

    float grain = interleaved_gradient_noise(gl_FragCoord.xy) - 0.5;
    color += grain * u_grain_strength;

    fragColor = vec4(max(color, 0.0), 1.0);
}
