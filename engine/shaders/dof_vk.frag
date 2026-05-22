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

const int DISK_SAMPLES = 16;
const vec2 DISK[16] = vec2[](
    vec2( 0.0000,  0.0000),
    vec2( 0.2706,  0.0000),
    vec2(-0.0833,  0.2568),
    vec2( 0.1871, -0.1963),
    vec2(-0.2568, -0.0833),
    vec2( 0.3827,  0.3827),
    vec2(-0.4619,  0.1913),
    vec2( 0.1913, -0.4619),
    vec2(-0.3827, -0.3827),
    vec2( 0.5412,  0.0000),
    vec2(-0.1667,  0.5136),
    vec2( 0.3742, -0.3927),
    vec2(-0.5136, -0.1667),
    vec2( 0.6935,  0.1379),
    vec2(-0.5449, -0.4084),
    vec2( 0.3386,  0.5878)
);

float linearize_depth(float d) {
    float z_n = 2.0 * d - 1.0;
    float near = u_dof_near;
    float far = u_dof_far;
    return 2.0 * near * far / (far + near - z_n * (far - near));
}

void main() {
    vec2 texel_size = vec2(1.0 / u_dof_sw, 1.0 / u_dof_sh);

    float depth = texture(u_dof_depth, vUV).r;
    float linear_depth = linearize_depth(depth);

    float coc = abs(linear_depth - u_dof_focus) / max(u_dof_range, 0.001);
    coc = clamp(coc, 0.0, 1.0);

    float max_radius = 8.0;
    float blur_radius = coc * max_radius;

    vec3 result = vec3(0.0);
    float total_weight = 0.0;

    for (int i = 0; i < DISK_SAMPLES; i++) {
        vec2 offset = DISK[i] * texel_size * blur_radius;
        vec2 sample_uv = vUV + offset;

        if (sample_uv.x < 0.0 || sample_uv.x > 1.0 ||
            sample_uv.y < 0.0 || sample_uv.y > 1.0) continue;

        float sample_depth = texture(u_dof_depth, sample_uv).r;
        float sample_linear = linearize_depth(sample_depth);

        float sample_coc = abs(sample_linear - u_dof_focus) / max(u_dof_range, 0.001);
        sample_coc = clamp(sample_coc, 0.0, 1.0);

        float weight = 1.0 / (1.0 + sample_coc * 4.0);

        result += texture(u_dof_color, sample_uv).rgb * weight;
        total_weight += weight;
    }

    if (total_weight > 0.0)
        result /= total_weight;
    else
        result = texture(u_dof_color, vUV).rgb;

    fragColor = vec4(result, 1.0);
}
