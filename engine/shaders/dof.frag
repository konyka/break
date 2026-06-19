#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

uniform sampler2D u_dof_color;
uniform sampler2D u_dof_depth;

uniform float u_dof_focus;
uniform float u_dof_range;
uniform float u_dof_near;
uniform float u_dof_far;
uniform float u_dof_sw;
uniform float u_dof_sh;

const int RINGS = 3;
const int SAMPLES_PER_RING = 6;

/* R83-3: Precomputed const hex_disk — values depend only on compile-time
 * constants RINGS=3 and SAMPLES_PER_RING=6. Eliminates 18 cos/sin/normalize/dot
 * calls per fragment. */
const vec2 hex_disk[RINGS * SAMPLES_PER_RING + 1] = vec2[](
    vec2(0.0, 0.0),
    vec2(0.33333, 0.19245), vec2(0.0, 0.38490), vec2(-0.33333, 0.19245),
    vec2(-0.33333, -0.19245), vec2(0.0, -0.38490), vec2(0.33333, -0.19245),
    vec2(0.66667, 0.38490), vec2(0.0, 0.76980), vec2(-0.66667, 0.38490),
    vec2(-0.66667, -0.38490), vec2(0.0, -0.76980), vec2(0.66667, -0.38490),
    vec2(1.0, 0.57735), vec2(0.0, 1.15470), vec2(-1.0, 0.57735),
    vec2(-1.0, -0.57735), vec2(0.0, -1.15470), vec2(1.0, -0.57735)
);

float linearize_depth(float d) {
    float z_n = 2.0 * d - 1.0;
    float near = u_dof_near;
    float far = u_dof_far;
    return 2.0 * near * far / (far + near - z_n * (far - near));
}

void main() {
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
