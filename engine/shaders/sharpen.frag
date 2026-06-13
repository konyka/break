#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

uniform sampler2D u_sharp_tex;

uniform float u_sharp_strength;
uniform float u_sharp_sw;
uniform float u_sharp_sh;

void main() {
    vec2 texel = 1.0 / vec2(u_sharp_sw, u_sharp_sh);

    vec3 a = texture(u_sharp_tex, vUV + vec2(-texel.x, -texel.y)).rgb;
    vec3 b = texture(u_sharp_tex, vUV + vec2( 0.0,     -texel.y)).rgb;
    vec3 c = texture(u_sharp_tex, vUV + vec2( texel.x, -texel.y)).rgb;
    vec3 d = texture(u_sharp_tex, vUV + vec2(-texel.x,  0.0    )).rgb;
    vec3 e = texture(u_sharp_tex, vUV).rgb;
    vec3 f = texture(u_sharp_tex, vUV + vec2( texel.x,  0.0    )).rgb;
    vec3 g = texture(u_sharp_tex, vUV + vec2(-texel.x,  texel.y)).rgb;
    vec3 h = texture(u_sharp_tex, vUV + vec2( 0.0,      texel.y)).rgb;
    vec3 i = texture(u_sharp_tex, vUV + vec2( texel.x,  texel.y)).rgb;

    vec3 mn  = min(min(min(a, c), min(g, i)), min(min(b, d), min(f, h)));
    vec3 mx  = max(max(max(a, c), max(g, i)), max(max(b, d), max(f, h)));
    vec3 rng = mx - mn;

    float peak = -1.0 / (u_sharp_strength * 8.0 + 1.0);
    vec3 w = vec3(1.0 + 4.0 * peak);

    vec3 t = fma(a + c + g + i, vec3(4.0 * peak),
                 (b + d + f + h) * vec3(peak));
    vec3 out_color = max(e * w + t, 0.0) / max(w, 1e-5);

    out_color = clamp(out_color, mn - rng * 0.125, mx + rng * 0.125);

    out_color = max(out_color, vec3(0.0));

    fragColor = vec4(out_color, 1.0);
}
