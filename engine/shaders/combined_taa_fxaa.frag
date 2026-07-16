#version 450

/* Combined TAA resolve + FXAA in a single pass (GL).  See the _vk variant for
 * the algorithm description; this mirrors it with loose uniforms (GL reflects
 * uniform names directly). */

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

/* R218-A: Match bind_textures_multi units 0–3 and combined_taa_fxaa_vk.frag. */
layout(binding = 0) uniform sampler2D u_taa_curr_tex;
layout(binding = 1) uniform sampler2D u_taa_hist_tex;
layout(binding = 2) uniform sampler2D u_taa_depth;
layout(binding = 3) uniform sampler2D u_taa_velocity;

uniform mat4 u_taa_curr_vp;
uniform mat4 u_taa_prev_vp;
uniform mat4 u_taa_inv_proj;
uniform float u_screen_w;
uniform float u_screen_h;
const float u_taa_blend = 0.1;
uniform float u_taa_first_frame;
const float u_fxaa_threshold = 0.0312;
uniform float u_taa_use_velocity;

const vec3 LUMA = vec3(0.2126, 0.7152, 0.0722);

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

vec3 fxaa(vec2 uv, vec2 texel) {
    vec3 cM  = texture(u_taa_curr_tex, uv).rgb;
    vec3 cN  = texture(u_taa_curr_tex, uv + vec2(0.0, -texel.y)).rgb;
    vec3 cS  = texture(u_taa_curr_tex, uv + vec2(0.0,  texel.y)).rgb;
    vec3 cW  = texture(u_taa_curr_tex, uv + vec2(-texel.x, 0.0)).rgb;
    vec3 cE  = texture(u_taa_curr_tex, uv + vec2( texel.x, 0.0)).rgb;
    vec3 cNW = texture(u_taa_curr_tex, uv + vec2(-texel.x, -texel.y)).rgb;
    vec3 cNE = texture(u_taa_curr_tex, uv + vec2( texel.x, -texel.y)).rgb;
    vec3 cSW = texture(u_taa_curr_tex, uv + vec2(-texel.x,  texel.y)).rgb;
    vec3 cSE = texture(u_taa_curr_tex, uv + vec2( texel.x,  texel.y)).rgb;

    float lumaM  = dot(cM,  LUMA);
    float lumaNW = dot(cNW, LUMA);
    float lumaNE = dot(cNE, LUMA);
    float lumaSW = dot(cSW, LUMA);
    float lumaSE = dot(cSE, LUMA);

    float lumaMin = min(lumaM, min(min(lumaNW, lumaNE), min(lumaSW, lumaSE)));
    float lumaMax = max(lumaM, max(max(lumaNW, lumaNE), max(lumaSW, lumaSE)));

    float range = lumaMax - lumaMin;
    if (range < max(u_fxaa_threshold, lumaMax * 0.125))
        return cM;

    float lumaN = dot(cN, LUMA);
    float lumaS = dot(cS, LUMA);
    float lumaW = dot(cW, LUMA);
    float lumaE = dot(cE, LUMA);

    float edgeVert  = abs(lumaN + lumaS - 2.0 * lumaM) * 2.0
                    + abs(lumaNW + lumaSW - 2.0 * lumaN)
                    + abs(lumaNE + lumaSE - 2.0 * lumaS);
    float edgeHoriz = abs(lumaW + lumaE - 2.0 * lumaM) * 2.0
                    + abs(lumaNW + lumaNE - 2.0 * lumaW)
                    + abs(lumaSW + lumaSE - 2.0 * lumaE);

    bool horizontal = edgeHoriz >= edgeVert;
    float pixel1 = horizontal ? texel.y : texel.x;
    float pixel2 = horizontal ? texel.x : texel.y;
    float luma1 = horizontal ? lumaN : lumaW;
    float luma2 = horizontal ? lumaS : lumaE;
    float gradient1 = abs(luma1 - lumaM);
    float gradient2 = abs(luma2 - lumaM);
    bool isLuma1 = gradient1 >= gradient2;

    float gradientScaled = max(gradient1, gradient2) * 0.25;
    float stepLength = pixel1;
    float lumaLocalAvg = isLuma1 ? (luma1 + lumaM) * 0.5 : (luma2 + lumaM) * 0.5;
    float pos = isLuma1 ? -stepLength : stepLength;

    vec2 posA = uv;
    vec2 posB = uv;
    if (horizontal) {
        posA.y += pos; posB.y += pos;
        posA.x -= pixel2 * 0.5; posB.x += pixel2 * 0.5;
    } else {
        posA.x += pos; posB.x += pos;
        posA.y -= pixel2 * 0.5; posB.y += pixel2 * 0.5;
    }

    float lumaPosA = dot(texture(u_taa_curr_tex, posA).rgb, LUMA);
    float lumaPosB = dot(texture(u_taa_curr_tex, posB).rgb, LUMA);
    float distA = abs(lumaPosA - lumaLocalAvg);
    float distB = abs(lumaPosB - lumaLocalAvg);

    float blend;
    if (distA < gradientScaled && distB < gradientScaled)
        blend = 0.5 - 0.5 * (pos / stepLength);
    else
        blend = distA < distB ? -0.5 + 0.5 * (distA / (distA + distB))
                              :  0.5 - 0.5 * (distB / (distA + distB));

    vec2 finalPos = uv;
    if (horizontal) finalPos.y += blend * stepLength;
    else            finalPos.x += blend * stepLength;
    return texture(u_taa_curr_tex, finalPos).rgb;
}

void main() {
    vec2 texel = vec2(1.0 / u_screen_w, 1.0 / u_screen_h);

    vec3 aa_color = fxaa(vUV, texel);

    vec3 c0 = texture(u_taa_curr_tex, vUV).rgb;
    vec3 n_min = c0, n_max = c0;
    for (int y = -1; y <= 1; ++y)
    for (int x = -1; x <= 1; ++x) {
        vec3 s = texture(u_taa_curr_tex, vUV + vec2(x, y) * texel).rgb;
        n_min = min(n_min, s);
        n_max = max(n_max, s);
    }

    vec3 result = aa_color;
    float depth = texture(u_taa_depth, vUV).r;
    if (depth < 1.0 && u_taa_first_frame < 0.5) {
        vec2 prev_uv;
        if (u_taa_use_velocity > 0.5) {
            vec2 vel = texture(u_taa_velocity, vUV).rg;
            prev_uv = vUV - vel * 0.5;
        } else {
            vec2 ndc = vUV * 2.0 - 1.0;
            vec4 world_h = u_taa_inv_proj * vec4(ndc, depth * 2.0 - 1.0, 1.0);
            vec3 world = world_h.xyz / world_h.w;
            vec4 prev_clip = u_taa_prev_vp * vec4(world, 1.0);
            prev_uv = (prev_clip.xy / prev_clip.w) * 0.5 + 0.5;
        }
        if (all(greaterThanEqual(prev_uv, vec2(0.0))) &&
            all(lessThanEqual(prev_uv, vec2(1.0)))) {
            vec3 hist = texture(u_taa_hist_tex, prev_uv).rgb;
            hist = clip_aabb(n_min, n_max, hist);
            result = mix(hist, aa_color, clamp(u_taa_blend, 0.05, 1.0));
        }
    }

    fragColor = vec4(result, 1.0);
}
