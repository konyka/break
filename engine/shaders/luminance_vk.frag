#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

layout(binding = 0) uniform sampler2D u_lum_hdr;
layout(binding = 1) uniform sampler2D u_lum_prev;

layout(push_constant) uniform LumParams {
    layout(offset = 0) float u_lum_w;
    layout(offset = 4) float u_lum_h;
    layout(offset = 8) float u_lum_speed;
    layout(offset = 12) float u_lum_dt;
};

void main() {
    float luma_sum = 0.0;
    const int N = 16;

    for (int y = 0; y < N; y++) {
        for (int x = 0; x < N; x++) {
            vec2 uv = (vec2(float(x), float(y)) + 0.5) / vec2(float(N), float(N));
            vec3 c = texture(u_lum_hdr, uv).rgb;
            luma_sum += log(max(dot(c, vec3(0.2126, 0.7152, 0.0722)), 0.001));
        }
    }

    float current_luma = exp(luma_sum / float(N * N));

    float prev_luma = texture(u_lum_prev, vec2(0.5)).r;
    if (prev_luma < 0.001) prev_luma = current_luma;

    float adapted = mix(prev_luma, current_luma, 1.0 - exp(-u_lum_speed * u_lum_dt));
    adapted = clamp(adapted, 0.01, 10.0);

    fragColor = vec4(adapted, 0.0, 0.0, 1.0);
}
