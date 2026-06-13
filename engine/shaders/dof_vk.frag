#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

layout(binding = 0) uniform sampler2D u_dof_color;
layout(binding = 1) uniform sampler2D u_dof_depth;

layout(push_constant) uniform DOFParams {
    layout(offset = 0)   float u_dof_focus;
    layout(offset = 4)   float u_dof_range;
    layout(offset = 8)   float u_dof_near;
    layout(offset = 12)  float u_dof_far;
    layout(offset = 16)  float u_dof_sw;
    layout(offset = 20)  float u_dof_sh;
};

const int RINGS = 3;
const int SAMPLES_PER_RING = 6;

vec2 hex_disk[RINGS * SAMPLES_PER_RING + 1];

float linearize_depth(float d) {
    float z_n = 2.0 * d - 1.0;
    float near = u_dof_near;
    float far = u_dof_far;
    return 2.0 * near * far / (far + near - z_n * (far - near));
}

void main() {
    hex_disk[0] = vec2(0.0);
    for (int ring = 1; ring <= RINGS; ring++) {
        float r = float(ring) / float(RINGS);
        for (int s = 0; s < SAMPLES_PER_RING; s++) {
            float angle = float(s) / float(SAMPLES_PER_RING) * 6.283185;
            float next_angle = float(s + 1) / float(SAMPLES_PER_RING) * 6.283185;
            vec2 v1 = vec2(cos(angle), sin(angle));
            vec2 v2 = vec2(cos(next_angle), sin(next_angle));
            vec2 hex_dir = normalize(v1 + v2);
            float hex_r = r / max(dot(hex_dir, v1), 0.001);
            hex_disk[(ring - 1) * SAMPLES_PER_RING + s + 1] = hex_dir * hex_r;
        }
    }

    const int total_samples = RINGS * SAMPLES_PER_RING + 1;

    vec2 texel_size = vec2(1.0 / u_dof_sw, 1.0 / u_dof_sh);

    float focus = u_dof_focus;
    if (focus <= 0.0) {
        float center_d = 0.0;
        for (int y = -1; y <= 1; y++) {
            for (int x = -1; x <= 1; x++) {
                vec2 uv = vec2(0.5) + vec2(float(x), float(y)) * texel_size;
                center_d += texture(u_dof_depth, uv).r;
            }
        }
        center_d /= 9.0;
        focus = linearize_depth(center_d);
    }

    float depth = texture(u_dof_depth, vUV).r;
    float linear_depth = linearize_depth(depth);

    float coc = 0.0;
    if (linear_depth < focus) {
        coc = (focus - linear_depth) / max(focus - u_dof_near, 0.001);
    } else {
        coc = (linear_depth - focus) / max(u_dof_far - focus, 0.001);
    }
    coc = clamp(coc, 0.0, 1.0);

    float max_radius = 10.0;
    float blur_radius = coc * max_radius;

    if (blur_radius < 0.5) {
        fragColor = texture(u_dof_color, vUV);
        return;
    }

    vec3 result = vec3(0.0);
    float total_weight = 0.0;

    for (int i = 0; i < total_samples; i++) {
        vec2 offset = hex_disk[i] * texel_size * blur_radius;
        vec2 sample_uv = vUV + offset;

        if (sample_uv.x < 0.0 || sample_uv.x > 1.0 ||
            sample_uv.y < 0.0 || sample_uv.y > 1.0) continue;

        float sample_depth = texture(u_dof_depth, sample_uv).r;
        float sample_linear = linearize_depth(sample_depth);

        float sample_coc = 0.0;
        if (sample_linear < focus) {
            sample_coc = (focus - sample_linear) / max(focus - u_dof_near, 0.001);
        } else {
            sample_coc = (sample_linear - focus) / max(u_dof_far - focus, 0.001);
        }
        sample_coc = clamp(sample_coc, 0.0, 1.0);

        float weight = max(1.0 - sample_coc, 0.1);

        result += texture(u_dof_color, sample_uv).rgb * weight;
        total_weight += weight;
    }

    if (total_weight > 0.0)
        result /= total_weight;
    else
        result = texture(u_dof_color, vUV).rgb;

    fragColor = vec4(result, 1.0);
}
