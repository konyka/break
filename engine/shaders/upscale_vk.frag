#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

layout(binding = 0) uniform sampler2D u_ups_src;
layout(binding = 1) uniform sampler2D u_ups_depth;
layout(binding = 2) uniform sampler2D u_ups_history;

layout(push_constant) uniform UpscaleParams {
    layout(offset = 0)   float u_ups_rw;
    layout(offset = 4)   float u_ups_rh;
    layout(offset = 8)   float u_ups_dw;
    layout(offset = 12)  float u_ups_dh;
    layout(offset = 16)  float u_ups_sharp;
    layout(offset = 20)  float u_ups_copy_only; /* R197-A: Pass 2 blit, skip TSR */
    layout(offset = 32)  mat4 u_ups_inv_proj;
    layout(offset = 96)  mat4 u_ups_prev_vp;
};

vec3 sample_catmull(sampler2D tex, vec2 uv, vec2 texel) {
    vec2 pos = uv / texel - 0.5;
    vec2 f = fract(pos);
    float fx = f.x, fy = f.y;

    float wx0 =       -fx + 2.0*fx*fx - fx*fx*fx;
    float wx1 =  2.0 - fx +       fx*fx*(-5.0 + 3.0*fx);
    float wx2 =       fx +       fx*fx*( 4.0 - 3.0*fx);
    float wx3 =           -fx*fx + fx*fx*fx;

    float wy0 =       -fy + 2.0*fy*fy - fy*fy*fy;
    float wy1 =  2.0 - fy +       fy*fy*(-5.0 + 3.0*fy);
    float wy2 =       fy +       fy*fy*( 4.0 - 3.0*fy);
    float wy3 =           -fy*fy + fy*fy*fy;

    float row_w[4] = float[4](wy0, wy1, wy2, wy3);
    float col_w[4] = float[4](wx0, wx1, wx2, wx3);

    vec2 base = (floor(pos) - vec2(0.5, 0.5)) * texel;

    vec3 result = vec3(0.0);
    for (int r = 0; r < 4; r++) {
        for (int c = 0; c < 4; c++) {
            vec2 sample_uv = base + vec2(float(c), float(r)) * texel;
            result += texture(tex, sample_uv).rgb * row_w[r] * col_w[c];
        }
    }
    return result;
}

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
    vec2 render_uv = vUV;

    /* R197-A: Pass 2 must store Pass 1 output verbatim into history.
     * Re-running TSR with stale read_idx history double-mixes and ghosts. */
    if (u_ups_copy_only > 0.5) {
        fragColor = vec4(clamp(texture(u_ups_src, render_uv).rgb, 0.0, 1.0), 1.0);
        return;
    }

    vec2 render_texel = 1.0 / vec2(u_ups_rw, u_ups_rh);
    vec3 upscaled = sample_catmull(u_ups_src, render_uv, render_texel);

    if (u_ups_sharp > 0.0) {
        vec3 c  = texture(u_ups_src, render_uv).rgb;
        vec3 n  = texture(u_ups_src, render_uv + vec2(0, -render_texel.y)).rgb;
        vec3 s  = texture(u_ups_src, render_uv + vec2(0,  render_texel.y)).rgb;
        vec3 w  = texture(u_ups_src, render_uv + vec2(-render_texel.x, 0)).rgb;
        vec3 e  = texture(u_ups_src, render_uv + vec2( render_texel.x, 0)).rgb;
        upscaled += (c * 4.0 - n - s - w - e) * u_ups_sharp * 0.25;
    }

    float depth = texture(u_ups_depth, render_uv).r;
    if (depth < 1.0) {
        vec2 ndc = render_uv * 2.0 - 1.0;
        vec4 clip_pos = vec4(ndc.x, ndc.y, depth, 1.0);
        vec4 view_pos = u_ups_inv_proj * clip_pos;
        view_pos.xyz /= view_pos.w;
        vec4 prev_clip = u_ups_prev_vp * vec4(view_pos.xyz, 1.0);
        vec2 prev_uv = (prev_clip.xy / prev_clip.w) * 0.5 + 0.5;

        if (prev_uv.x >= 0.0 && prev_uv.x <= 1.0 && prev_uv.y >= 0.0 && prev_uv.y <= 1.0) {
            vec3 history = texture(u_ups_history, prev_uv).rgb;

            vec3 n0 = textureOffset(u_ups_src, render_uv, ivec2(-1, 0)).rgb;
            vec3 n1 = textureOffset(u_ups_src, render_uv, ivec2( 1, 0)).rgb;
            vec3 n2 = textureOffset(u_ups_src, render_uv, ivec2( 0,-1)).rgb;
            vec3 n3 = textureOffset(u_ups_src, render_uv, ivec2( 0, 1)).rgb;
            vec3 aabb_min = min(min(n0, n1), min(n2, n3));
            vec3 aabb_max = max(max(n0, n1), max(n2, n3));

            history = clip_aabb(aabb_min, aabb_max, history);
            upscaled = mix(history, upscaled, 0.15);
        }
    }

    fragColor = vec4(clamp(upscaled, 0.0, 1.0), 1.0);
}
