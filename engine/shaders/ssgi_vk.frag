#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

layout(binding = 0) uniform sampler2D u_ssgi_depth;
layout(binding = 1) uniform sampler2D u_ssgi_color;

layout(push_constant) uniform SSGIParams {
    layout(offset = 0)   mat4 u_ssgi_inv_proj;
    layout(offset = 64)  mat4 u_ssgi_proj;
    layout(offset = 128) float u_ssgi_radius;
    layout(offset = 132) float u_ssgi_intensity;
    layout(offset = 136) float u_ssgi_sw;
    layout(offset = 140) float u_ssgi_sh;
};

vec3 view_pos_from_depth(vec2 uv, float depth) {
    vec4 clip = vec4(uv * 2.0 - 1.0, depth, 1.0);
    vec4 view_h = u_ssgi_inv_proj * clip;
    return view_h.xyz / view_h.w;
}

float interleaved_gradient_noise(vec2 screen_pos) {
    vec3 magic = vec3(0.06711056, 0.00583715, 52.9829189);
    return fract(magic.z * fract(dot(screen_pos, magic.xy)));
}

void main() {
    float depth = texture(u_ssgi_depth, vUV).r;
    if (depth >= 1.0) {
        fragColor = vec4(0.0, 0.0, 0.0, 1.0);
        return;
    }

    vec3 pos = view_pos_from_depth(vUV, depth);
    vec3 normal = normalize(cross(dFdx(pos), dFdy(pos)));

    vec2 noise_scale = vec2(u_ssgi_sw / 4.0, u_ssgi_sh / 4.0);
    float noise = interleaved_gradient_noise(gl_FragCoord.xy);

    vec3 gi = vec3(0.0);
    float total_weight = 0.0;

    int steps = 8;
    for (int i = 0; i < steps; i++) {
        float angle = (float(i) + noise) * 6.283185 / float(steps);
        float radius_scale = (float(i) + 0.5) / float(steps);

        vec2 sample_offset = vec2(cos(angle), sin(angle)) * u_ssgi_radius * radius_scale;
        vec2 sample_uv = vUV + sample_offset / vec2(u_ssgi_sw, u_ssgi_sh);

        if (sample_uv.x < 0.0 || sample_uv.x > 1.0 || sample_uv.y < 0.0 || sample_uv.y > 1.0)
            continue;

        float sample_depth = texture(u_ssgi_depth, sample_uv).r;
        vec3 sample_pos = view_pos_from_depth(sample_uv, sample_depth);
        vec3 diff = sample_pos - pos;

        float dist = length(diff);
        vec3 sample_dir = diff / max(dist, 0.001);

        float n_dot_d = max(dot(normal, sample_dir), 0.0);

        float falloff = 1.0 / (1.0 + dist * dist * 0.1);

        vec3 sample_color = texture(u_ssgi_color, sample_uv).rgb;

        gi += sample_color * n_dot_d * falloff;
        total_weight += falloff;
    }

    if (total_weight > 0.0) gi /= total_weight;

    gi *= u_ssgi_intensity;

    fragColor = vec4(gi, 1.0);
}
