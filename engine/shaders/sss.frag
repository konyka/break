#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

uniform sampler2D u_sss_color;
uniform sampler2D u_sss_depth;

uniform float u_sss_strength;
uniform float u_sss_sw;
uniform float u_sss_sh;
uniform float u_sss_max_dist;

vec3 diffuse_profile(float r) {
    vec3 sss_r = vec3(0.233, 0.455, 0.649) * exp(-r * r / (2.0 * 0.0064));
    vec3 sss_g = vec3(0.100, 0.336, 0.344) * exp(-r * r / (2.0 * 0.0484));
    vec3 sss_b = vec3(0.118, 0.198, 0.000) * exp(-r * r / (2.0 * 0.1870));
    return sss_r + sss_g + sss_b;
}

void main() {
    vec2 res = vec2(u_sss_sw, u_sss_sh);
    vec2 texel = 1.0 / res;

    float depth = texture(u_sss_depth, vUV).r;
    vec3 center = texture(u_sss_color, vUV).rgb;

    if (depth >= 1.0) {
        fragColor = vec4(center, 1.0);
        return;
    }

    vec3 sss = center * diffuse_profile(0.0);
    float total_w = 1.0;

    for (int i = -4; i <= 4; i++) {
        for (int j = -4; j <= 4; j++) {
            if (i == 0 && j == 0) continue;

            float dist = length(vec2(float(i), float(j)));
            vec2 offset = vec2(float(i), float(j)) * texel * u_sss_strength * 8.0;
            vec2 sample_uv = vUV + offset;

            if (sample_uv.x < 0.0 || sample_uv.x > 1.0 ||
                sample_uv.y < 0.0 || sample_uv.y > 1.0) continue;

            float sd = texture(u_sss_depth, sample_uv).r;
            float depth_diff = abs(sd - depth);
            float falloff = 1.0 - smoothstep(0.0, u_sss_max_dist, depth_diff);

            vec3 profile = diffuse_profile(dist / 4.0);
            float w = dot(profile, vec3(0.333)) * falloff;

            vec3 sc = texture(u_sss_color, sample_uv).rgb;
            sss += sc * profile * w;
            total_w += w;
        }
    }

    sss /= max(total_w, 0.001);

    vec3 result = mix(center, sss, u_sss_strength);
    fragColor = vec4(max(result, vec3(0.0)), 1.0);
}
