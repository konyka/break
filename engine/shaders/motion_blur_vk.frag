#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

layout(binding = 0) uniform sampler2D u_mb_color;
layout(binding = 1) uniform sampler2D u_mb_depth;

layout(push_constant) uniform MBParams {
    layout(offset = 0)  float u_mb_strength;
    layout(offset = 4)  float u_mb_sw;
    layout(offset = 8)  float u_mb_sh;
    layout(offset = 12) float u_mb_inv_proj[16];
    layout(offset = 76) float u_mb_prev_vp[16];
};

mat4 load_inv_proj() {
    mat4 m;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m[i][j] = u_mb_inv_proj[i * 4 + j];
    return m;
}

mat4 load_prev_vp() {
    mat4 m;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m[i][j] = u_mb_prev_vp[i * 4 + j];
    return m;
}

float interleaved_gradient_noise(vec2 p) {
    vec3 magic = vec3(0.06711056, 0.00583715, 52.9829189);
    return fract(magic.z * fract(dot(p, magic.xy)));
}

void main() {
    vec2 res = vec2(u_mb_sw, u_mb_sh);
    float depth = texture(u_mb_depth, vUV).r;

    if (depth >= 1.0) {
        fragColor = texture(u_mb_color, vUV);
        return;
    }

    vec2 ndc = vUV * 2.0 - 1.0;
    vec4 view_pos = load_inv_proj() * vec4(ndc, depth, 1.0);
    view_pos.xyz /= view_pos.w;

    mat4 prev_vp = load_prev_vp();
    vec4 prev_clip = prev_vp * vec4(view_pos.xyz, 1.0);
    vec2 prev_ndc = prev_clip.xy / prev_clip.w;
    vec2 prev_uv = prev_ndc * 0.5 + 0.5;

    vec2 velocity = (vUV - prev_uv) * res;

    float vel_len = length(velocity);
    if (vel_len < 0.5) {
        fragColor = texture(u_mb_color, vUV);
        return;
    }

    float max_vel = min(vel_len, 200.0);
    float sample_count = min(max_vel * u_mb_strength, 16.0);
    vec2 dir = velocity / max(vel_len, 0.001);
    vec2 step_size = dir * u_mb_strength / max(sample_count, 1.0);

    float jitter = interleaved_gradient_noise(gl_FragCoord.xy) - 0.5;

    vec3 result = vec3(0.0);
    float total_w = 0.0;

    for (float i = -sample_count * 0.5; i <= sample_count * 0.5; i += 1.0) {
        float w = 1.0 - abs(i) / (sample_count * 0.5 + 1.0);
        float offset = i + jitter;
        vec2 sample_uv = vUV + step_size * offset / res;
        result += texture(u_mb_color, clamp(sample_uv, vec2(0.0), vec2(1.0))).rgb * w;
        total_w += w;
    }

    fragColor = vec4(result / max(total_w, 0.001), 1.0);
}
