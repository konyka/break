#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

layout(binding = 0) uniform sampler2D u_lf_depth;

layout(push_constant) uniform LFParams {
    layout(offset = 0)   float u_lf_light_x;
    layout(offset = 4)   float u_lf_light_y;
    layout(offset = 8)   float u_lf_intensity;
    layout(offset = 12)  float u_lf_sw;
    layout(offset = 16)  float u_lf_sh;
    layout(offset = 20)  float u_lf_lc_r;
    layout(offset = 24)  float u_lf_lc_g;
    layout(offset = 28)  float u_lf_lc_b;
};

void main() {
    vec2 light_pos = vec2(u_lf_light_x, u_lf_light_y);
    vec2 center = vUV - light_pos;
    float dist = length(center);
    vec2 dir = dist > 0.001 ? center / dist : vec2(0.0, 1.0);

    vec3 flare = vec3(0.0);
    vec3 light_color = vec3(u_lf_lc_r, u_lf_lc_g, u_lf_lc_b);

    float star = exp(-dist * 6.0) * 0.8;
    float streak_h = exp(-abs(center.y) * 40.0) * exp(-abs(center.x) * 3.0) * 0.15;
    float streak_v = exp(-abs(center.x) * 40.0) * exp(-abs(center.y) * 3.0) * 0.15;
    flare += star * light_color;
    flare += streak_h * light_color;
    flare += streak_v * light_color;

    vec2 ghost_uv = light_pos + center * -0.5;
    float ghost_dist = length(ghost_uv - vec2(0.5));
    float ghost = exp(-ghost_dist * 4.0) * 0.3;
    if (ghost_uv.x > 0.0 && ghost_uv.x < 1.0 && ghost_uv.y > 0.0 && ghost_uv.y < 1.0) {
        float gd = texture(u_lf_depth, ghost_uv).r;
        if (gd > 0.99) {
            flare += ghost * light_color;
        }
    }

    vec2 halo_uv = light_pos + dir * 0.3;
    float halo = exp(-abs(length(halo_uv - vec2(0.5)) - 0.3) * 20.0) * 0.2;
    if (halo_uv.x > 0.0 && halo_uv.x < 1.0 && halo_uv.y > 0.0 && halo_uv.y < 1.0) {
        flare += halo * light_color;
    }

    flare *= u_lf_intensity;

    fragColor = vec4(flare, 1.0);
}
