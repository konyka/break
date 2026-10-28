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
    layout(offset = 24)  float u_ups_first_frame;
    layout(offset = 32)  mat4 u_ups_inv_proj;
    layout(offset = 96)  mat4 u_ups_prev_vp;
};

/* R686: Catmull-Rom in 9 bilinear taps instead of 16 point taps. The two
 * inner weights of each axis are folded into one linear fetch placed at
 * w2 / (w1 + w2) between texels 1 and 2; the outer taps sit on texel
 * centres. Same weights as before (R641's overall 1/2 included). */
vec3 sample_catmull(sampler2D tex, vec2 uv, vec2 texel) {
    vec2 pos = uv / texel;
    vec2 t1 = floor(pos - 0.5) + 0.5;
    vec2 f = pos - t1;

    vec2 w0 = f * (-0.5 + f * (1.0 - 0.5 * f));
    vec2 w1 = 1.0 + f * f * (-2.5 + 1.5 * f);
    vec2 w2 = f * (0.5 + f * (2.0 - 1.5 * f));
    vec2 w3 = f * f * (-0.5 + 0.5 * f);

    vec2 w12 = w1 + w2;
    vec2 uv0  = (t1 - 1.0) * texel;
    vec2 uv12 = (t1 + w2 / w12) * texel;
    vec2 uv3  = (t1 + 2.0) * texel;

    vec3 result = vec3(0.0);
    result += texture(tex, vec2(uv0.x,  uv0.y)).rgb  * (w0.x  * w0.y);
    result += texture(tex, vec2(uv12.x, uv0.y)).rgb  * (w12.x * w0.y);
    result += texture(tex, vec2(uv3.x,  uv0.y)).rgb  * (w3.x  * w0.y);
    result += texture(tex, vec2(uv0.x,  uv12.y)).rgb * (w0.x  * w12.y);
    result += texture(tex, vec2(uv12.x, uv12.y)).rgb * (w12.x * w12.y);
    result += texture(tex, vec2(uv3.x,  uv12.y)).rgb * (w3.x  * w12.y);
    result += texture(tex, vec2(uv0.x,  uv3.y)).rgb  * (w0.x  * w3.y);
    result += texture(tex, vec2(uv12.x, uv3.y)).rgb  * (w12.x * w3.y);
    result += texture(tex, vec2(uv3.x,  uv3.y)).rgb  * (w3.x  * w3.y);
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

    /* R197-A copy-only blit. R686: upscale_apply no longer issues it (pass 1
     * writes the history target directly); kept so the push layout and the
     * contract tables stay put. */
    if (u_ups_copy_only > 0.5) {
        fragColor = vec4(clamp(texture(u_ups_src, render_uv).rgb, 0.0, 1.0), 1.0);
        return;
    }

    vec2 render_texel = 1.0 / vec2(u_ups_rw, u_ups_rh);
    vec3 upscaled = sample_catmull(u_ups_src, render_uv, render_texel);

    /* R686: the sharpen cross and the history clip AABB read the same four
     * neighbours; fetch them once. The branch depends on depth, so explicit
     * LOD 0 (single-mip source) instead of implicit derivatives. */
    float depth = texture(u_ups_depth, render_uv).r;
    bool use_history = depth < 1.0 && u_ups_first_frame < 0.5;
    vec3 nw = vec3(0.0), ne = vec3(0.0), nn = vec3(0.0), ns = vec3(0.0);
    if (u_ups_sharp > 0.0 || use_history) {
        nw = textureLod(u_ups_src, render_uv + vec2(-render_texel.x, 0), 0.0).rgb;
        ne = textureLod(u_ups_src, render_uv + vec2( render_texel.x, 0), 0.0).rgb;
        nn = textureLod(u_ups_src, render_uv + vec2(0, -render_texel.y), 0.0).rgb;
        ns = textureLod(u_ups_src, render_uv + vec2(0,  render_texel.y), 0.0).rgb;
    }

    if (u_ups_sharp > 0.0) {
        vec3 c  = texture(u_ups_src, render_uv).rgb;
        upscaled += (c * 4.0 - nn - ns - nw - ne) * u_ups_sharp * 0.25;
    }

    if (use_history) {
        vec2 ndc = render_uv * 2.0 - 1.0;
        vec4 clip_pos = vec4(ndc.x, ndc.y, depth * 2.0 - 1.0, 1.0);
        vec4 view_pos = u_ups_inv_proj * clip_pos;
        view_pos.xyz /= view_pos.w;
        vec4 prev_clip = u_ups_prev_vp * vec4(view_pos.xyz, 1.0);
        vec2 prev_uv = (prev_clip.xy / prev_clip.w) * 0.5 + 0.5;

        if (prev_uv.x >= 0.0 && prev_uv.x <= 1.0 && prev_uv.y >= 0.0 && prev_uv.y <= 1.0) {
            vec3 history = texture(u_ups_history, prev_uv).rgb;

            vec3 aabb_min = min(min(nw, ne), min(nn, ns));
            vec3 aabb_max = max(max(nw, ne), max(nn, ns));

            history = clip_aabb(aabb_min, aabb_max, history);
            upscaled = mix(history, upscaled, 0.15);
        }
    }

    fragColor = vec4(clamp(upscaled, 0.0, 1.0), 1.0);
}
