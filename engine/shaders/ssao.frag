#version 450 core

layout(location = 0) in vec2 vUV;

uniform mat4 u_ssao_proj;
uniform mat4 u_ssao_inv_proj;
uniform float u_ssao_sw;
uniform float u_ssao_sh;
uniform float u_ssao_radius;
uniform float u_ssao_bias;

layout(binding = 0) uniform sampler2D u_depth;

layout(location = 0) out vec4 frag_color;

vec3 reconstruct_pos(vec2 uv, float depth) {
    vec4 ndc = vec4(uv * 2.0 - 1.0, depth, 1.0);
    vec4 view = u_ssao_inv_proj * ndc;
    return view.xyz / view.w;
}

vec3 reconstruct_normal(vec3 pos) {
    return normalize(cross(dFdx(pos), dFdy(pos)));
}

float interleaved_gradient_noise(vec2 p) {
    vec3 magic = vec3(0.06711056, 0.00583715, 52.9829189);
    return fract(magic.z * fract(dot(p, magic.xy)));
}

void main() {
    float depth = texture(u_depth, vUV).r;
    if (depth >= 1.0) {
        frag_color = vec4(1.0);
        return;
    }

    vec3 pos = reconstruct_pos(vUV, depth);
    vec3 normal = reconstruct_normal(pos);

    vec2 noise_scale = vec2(u_ssao_sw, u_ssao_sh);
    float noise = interleaved_gradient_noise(gl_FragCoord.xy);

    vec3 view = normalize(-pos);

    float ao = 0.0;

    const int directions = 4;
    const int steps = 6;

    for (int d = 0; d < directions; d++) {
        float angle = (float(d) + noise) * 3.14159265 / float(directions);
        vec2 dir = vec2(cos(angle), sin(angle));

        float horizon_neg = 1.0;
        float horizon_pos = -1.0;

        for (int s = 0; s < steps; s++) {
            float t = (float(s) + 0.5) / float(steps);
            t *= u_ssao_radius;
            vec2 sample_uv = vUV + dir * t / noise_scale;
            if (sample_uv.x < 0.0 || sample_uv.x > 1.0 || sample_uv.y < 0.0 || sample_uv.y > 1.0) continue;

            float sd = texture(u_depth, sample_uv).r;
            if (sd >= 1.0) continue;
            vec3 sp = reconstruct_pos(sample_uv, sd);

            vec3 diff = sp - pos;
            float dist = length(diff);
            vec3 sv = diff / max(dist, 0.001);

            float cos_h = dot(view, sv);

            if (cos_h > horizon_pos) horizon_pos = cos_h;
            if (cos_h < horizon_neg) horizon_neg = cos_h;
        }

        vec3 tangent = vec3(dir.x, dir.y, 0.0);
        vec3 bitangent = normalize(cross(view, tangent));
        vec3 n_proj = normal - bitangent * dot(normal, bitangent);

        float n_len = length(n_proj);
        float cos_n = n_len > 0.001 ? dot(normalize(n_proj), view) : 0.0;

        float h2 = clamp(horizon_pos + u_ssao_bias, -1.0, 1.0);

        float a1 = acos(clamp(cos_n, -1.0, 1.0));
        float a2 = acos(clamp(h2, -1.0, 1.0));

        float contrib = (sin(a2) - sin(a1)) * 0.5 + (a2 - a1) * cos_n;
        contrib = max(contrib, 0.0);

        ao += contrib;
    }

    ao = 1.0 - ao / float(directions) * 2.0;

    frag_color = vec4(clamp(ao, 0.0, 1.0), 0.0, 0.0, 1.0);
}
