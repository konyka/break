#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

/* R222-A: Match bind_textures_multi {color, depth} and ssr_vk.frag. */
layout(binding = 0) uniform sampler2D u_ssr_color;
layout(binding = 1) uniform sampler2D u_ssr_depth;

uniform mat4 u_ssr_proj;
uniform mat4 u_ssr_inv_proj;
uniform mat4 u_ssr_view;
uniform float u_ssr_sw;
uniform float u_ssr_sh;
uniform float u_ssr_max_steps;
uniform float u_ssr_stride;
const float u_ssr_thickness = 0.05;  /* R89-2: hardcoded constant */

vec3 view_pos_from_depth(vec2 uv, float depth) {
    vec4 clip = vec4(uv * 2.0 - 1.0, depth * 2.0 - 1.0, 1.0);
    vec4 view_h = u_ssr_inv_proj * clip;
    return view_h.xyz / view_h.w;
}

void main() {
    float depth = texture(u_ssr_depth, vUV).r;

    if (depth >= 1.0) {
        fragColor = vec4(0.0);
        return;
    }

    vec3 pos_vs = view_pos_from_depth(vUV, depth);
    vec3 normal_vs = normalize(cross(dFdx(pos_vs), dFdy(pos_vs)));

    vec3 view_dir = normalize(-pos_vs);
    vec3 refl_dir = reflect(-view_dir, normal_vs);

    if (refl_dir.z > 0.0) {
        fragColor = vec4(0.0);
        return;
    }

    vec3 ray_start = pos_vs;
    vec3 ray_end = ray_start + refl_dir * 100.0;

    vec4 start_clip = u_ssr_proj * vec4(ray_start, 1.0);
    vec4 end_clip   = u_ssr_proj * vec4(ray_end, 1.0);
    start_clip.xyz /= start_clip.w;
    end_clip.xyz   /= end_clip.w;

    vec3 start_screen = start_clip.xyz * 0.5 + 0.5;
    vec3 end_screen   = end_clip.xyz * 0.5 + 0.5;

    vec3 ray_delta = end_screen - start_screen;
    vec3 step_delta = ray_delta / u_ssr_max_steps * u_ssr_stride;

    vec3 ray = start_screen;
    vec3 prev_ray = ray;
    vec2 hit_uv = vec2(0.0);
    bool found = false;

    for (int i = 0; i < int(u_ssr_max_steps); i++) {
        prev_ray = ray;
        ray += step_delta;
        if (ray.x < 0.0 || ray.x > 1.0 || ray.y < 0.0 || ray.y > 1.0) break;

        float sample_depth = texture(u_ssr_depth, ray.xy).r;
        float diff = ray.z - sample_depth;
        if (diff > 0.0 && diff < u_ssr_thickness) {
            vec3 lo = prev_ray;
            vec3 hi = ray;
            for (int j = 0; j < 4; j++) {
                vec3 mid = (lo + hi) * 0.5;
                float mid_depth = texture(u_ssr_depth, mid.xy).r;
                if (mid.z - mid_depth > 0.0 && mid.z - mid_depth < u_ssr_thickness) {
                    hi = mid;
                } else {
                    lo = mid;
                }
            }
            hit_uv = hi.xy;
            found = true;
            break;
        }
    }

    vec3 ssr_color = vec3(0.0);
    float fade = 0.0;
    if (found) {
        ssr_color = texture(u_ssr_color, hit_uv).rgb;

        float edge_fade = min(min(hit_uv.x, 1.0 - hit_uv.x), min(hit_uv.y, 1.0 - hit_uv.y));
        fade = smoothstep(0.0, 0.15, edge_fade);

        float n_dot_v = max(dot(normal_vs, view_dir), 0.0);
        float t = 1.0 - n_dot_v; float fresnel = 0.04 + 0.96 * (t * t * t * t * t); /* R84-4 */
        fade *= fresnel;
    }

    fragColor = vec4(ssr_color, fade);
}
