#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

layout(binding = 0) uniform sampler2D u_sssv_color;
layout(binding = 1) uniform sampler2D u_sssv_depth;
layout(binding = 2) uniform sampler2D u_sssv_original;

layout(push_constant) uniform SSSVParams {
    layout(offset = 0)  float u_sssv_strength;
    layout(offset = 4)  float u_sssv_sw;
    layout(offset = 8)  float u_sssv_sh;
    layout(offset = 12) float u_sssv_max_dist;
};

vec3 kernel_weights[9] = vec3[9](
    vec3(0.020, 0.020, 0.020),
    vec3(0.050, 0.040, 0.030),
    vec3(0.100, 0.070, 0.050),
    vec3(0.150, 0.130, 0.080),
    vec3(0.160, 0.160, 0.120),
    vec3(0.150, 0.130, 0.080),
    vec3(0.100, 0.070, 0.050),
    vec3(0.050, 0.040, 0.030),
    vec3(0.020, 0.020, 0.020)
);

void main() {
    vec2 texel = 1.0 / vec2(u_sssv_sw, u_sssv_sh);

    float depth = texture(u_sssv_depth, vUV).r;
    vec3 center = texture(u_sssv_original, vUV).rgb;

    if (depth >= 1.0) {
        fragColor = vec4(center, 1.0);
        return;
    }

    float radius = u_sssv_strength * 12.0;

    vec3 sss = vec3(0.0);
    vec3 total_w = vec3(0.0);

    for (int i = -4; i <= 4; i++) {
        vec2 offset = vec2(0.0, float(i) * texel.y * radius);
        vec2 sample_uv = vUV + offset;

        if (sample_uv.y < 0.0 || sample_uv.y > 1.0) continue;

        float sd = texture(u_sssv_depth, sample_uv).r;
        float depth_diff = abs(sd - depth);
        float falloff = 1.0 - smoothstep(0.0, u_sssv_max_dist, depth_diff);

        vec3 w = kernel_weights[i + 4] * falloff;
        vec3 sc = texture(u_sssv_color, sample_uv).rgb;
        sss += sc * w;
        total_w += w;
    }

    sss /= max(total_w, vec3(0.001));

    vec3 result = mix(center, sss, u_sssv_strength);
    fragColor = vec4(max(result, vec3(0.0)), 1.0);
}
