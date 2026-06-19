#version 450

layout(location = 0) in vec2 vUV;

layout(location = 0) out vec4 fragColor;

uniform sampler2D u_taa_curr_tex;
uniform sampler2D u_taa_hist_tex;
uniform sampler2D u_taa_depth;
uniform sampler2D u_taa_velocity;

uniform mat4 u_taa_curr_vp;
uniform mat4 u_taa_prev_vp;
uniform mat4 u_taa_inv_proj;
uniform float u_taa_sw;
uniform float u_taa_sh;
const float u_taa_blend = 0.1;
uniform float u_taa_first_frame;
uniform float u_taa_use_velocity;

vec3 clip_aabb(vec3 aabb_min, vec3 aabb_max, vec3 p) {
    vec3 center = (aabb_min + aabb_max) * 0.5;
    vec3 extent = (aabb_max - aabb_min) * 0.5;
    vec3 dir = p - center;
    vec3 scaled = abs(dir) / max(extent, vec3(1e-5));
    float max_s = max(scaled.x, max(scaled.y, scaled.z));
    if (max_s > 1.0)
        return center + dir / max_s;
    return p;
}

void main() {
    vec2 texel_size = vec2(1.0 / u_taa_sw, 1.0 / u_taa_sh);

    float depth = texture(u_taa_depth, vUV).r;

    vec3 curr_color = texture(u_taa_curr_tex, vUV).rgb;

    vec3 neighbor[8];
    neighbor[0] = texture(u_taa_curr_tex, vUV + vec2(-1, -1) * texel_size).rgb;
    neighbor[1] = texture(u_taa_curr_tex, vUV + vec2( 0, -1) * texel_size).rgb;
    neighbor[2] = texture(u_taa_curr_tex, vUV + vec2( 1, -1) * texel_size).rgb;
    neighbor[3] = texture(u_taa_curr_tex, vUV + vec2(-1,  0) * texel_size).rgb;
    neighbor[4] = texture(u_taa_curr_tex, vUV + vec2( 1,  0) * texel_size).rgb;
    neighbor[5] = texture(u_taa_curr_tex, vUV + vec2(-1,  1) * texel_size).rgb;
    neighbor[6] = texture(u_taa_curr_tex, vUV + vec2( 0,  1) * texel_size).rgb;
    neighbor[7] = texture(u_taa_curr_tex, vUV + vec2( 1,  1) * texel_size).rgb;

    vec3 n_min = curr_color;
    vec3 n_max = curr_color;
    for (int i = 0; i < 8; i++) {
        n_min = min(n_min, neighbor[i]);
        n_max = max(n_max, neighbor[i]);
    }

    if (depth < 1.0 && u_taa_first_frame < 0.5) {
        vec2 prev_uv;
        if (u_taa_use_velocity > 0.5) {
            vec2 vel = texture(u_taa_velocity, vUV).rg;
            prev_uv = vUV - vel * 0.5;
        } else {
            vec2 ndc = vUV * 2.0 - 1.0;
            vec4 clip_pos = vec4(ndc.x, ndc.y, depth, 1.0);
            vec4 world_pos_h = u_taa_inv_proj * clip_pos;
            vec3 world_pos = world_pos_h.xyz / world_pos_h.w;
            vec4 prev_clip = u_taa_prev_vp * vec4(world_pos, 1.0);
            prev_uv = (prev_clip.xy / prev_clip.w) * 0.5 + 0.5;
        }

        if (prev_uv.x >= 0.0 && prev_uv.x <= 1.0 && prev_uv.y >= 0.0 && prev_uv.y <= 1.0) {
            vec3 hist_color = texture(u_taa_hist_tex, prev_uv).rgb;
            hist_color = clip_aabb(n_min, n_max, hist_color);
            curr_color = mix(hist_color, curr_color, u_taa_blend);
        }
    }

    fragColor = vec4(curr_color, 1.0);
}
