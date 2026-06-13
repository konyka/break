#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

uniform sampler2D u_depth;
uniform mat4 u_inv_proj;
uniform mat4 u_curr_vp;
uniform mat4 u_prev_vp;

void main() {
    float depth = texture(u_depth, vUV).r;
    if (depth >= 1.0) {
        fragColor = vec4(0.0);
        return;
    }

    vec2 ndc_xy = vUV * 2.0 - 1.0;
    vec4 view_pos = u_inv_proj * vec4(ndc_xy, depth, 1.0);
    view_pos.xyz /= view_pos.w;

    vec4 curr_clip = u_curr_vp * vec4(view_pos.xyz, 1.0);
    vec4 prev_clip = u_prev_vp * vec4(view_pos.xyz, 1.0);
    vec2 curr_ndc = curr_clip.xy / max(curr_clip.w, 1e-6);
    vec2 prev_ndc = prev_clip.xy / max(prev_clip.w, 1e-6);
    fragColor = vec4(curr_ndc - prev_ndc, 0.0, 1.0);
}
