#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

layout(binding = 0) uniform sampler2D u_sss_color;
layout(binding = 1) uniform sampler2D u_sss_depth;

layout(push_constant) uniform SSSParams {
    layout(offset = 0)  float u_sss_strength;
    layout(offset = 4)  float u_sss_sw;
    layout(offset = 8)  float u_sss_sh;
    layout(offset = 12) float u_sss_max_dist;
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
    vec2 texel = 1.0 / vec2(u_sss_sw, u_sss_sh);

    float depth = texture(u_sss_depth, vUV).r;
    vec3 center = texture(u_sss_color, vUV).rgb;

    if (depth >= 1.0) {
        fragColor = vec4(center, 1.0);
        return;
    }

    float radius = u_sss_strength * 12.0;

    vec3 sss = vec3(0.0);
    vec3 total_w = vec3(0.0);

    for (int i = -4; i <= 4; i++) {
        vec2 offset = vec2(float(i) * texel.x * radius, 0.0);
        vec2 sample_uv = vUV + offset;

        if (sample_uv.x < 0.0 || sample_uv.x > 1.0) continue;

        float sd = texture(u_sss_depth, sample_uv).r;
        float depth_diff = abs(sd - depth);
        float falloff = 1.0 - smoothstep(0.0, u_sss_max_dist, depth_diff);

        vec3 w = kernel_weights[i + 4] * falloff;
        vec3 sc = texture(u_sss_color, sample_uv).rgb;
        sss += sc * w;
        total_w += w;
    }

    sss /= max(total_w, vec3(0.001));

    fragColor = vec4(sss, 1.0);
}
