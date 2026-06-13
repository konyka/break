#version 450 core

layout(location = 0) in vec2 vUV;

layout(binding = 0) uniform sampler2D u_ssao;
layout(binding = 1) uniform sampler2D u_ssao_depth;

layout(location = 0) out vec4 frag_color;

void main() {
    vec2 texel = 1.0 / vec2(textureSize(u_ssao, 0));

    float center_depth = texture(u_ssao_depth, vUV).r;
    float center_ao = texture(u_ssao, vUV).r;

    if (center_depth >= 1.0) {
        frag_color = vec4(1.0);
        return;
    }

    float sigma = 0.01;
    float result = 0.0;
    float total_w = 0.0;

    for (int y = -2; y <= 2; y++) {
        for (int x = -2; x <= 2; x++) {
            vec2 offset = vec2(float(x), float(y)) * texel;
            vec2 sample_uv = vUV + offset;

            float sample_ao = texture(u_ssao, sample_uv).r;
            float sample_depth = texture(u_ssao_depth, sample_uv).r;

            float depth_diff = abs(sample_depth - center_depth);
            float w = exp(-depth_diff * depth_diff / (2.0 * sigma * sigma));

            float spatial = exp(-float(x * x + y * y) / 4.0);
            w *= spatial;

            result += sample_ao * w;
            total_w += w;
        }
    }

    float ao = total_w > 0.0 ? result / total_w : center_ao;

    frag_color = vec4(ao, ao, ao, 1.0);
}
