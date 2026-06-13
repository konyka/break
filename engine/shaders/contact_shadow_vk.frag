#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

layout(binding = 0) uniform sampler2D u_cs_depth;

layout(push_constant) uniform CSParams {
    layout(offset = 0)  float u_cs_light_x;
    layout(offset = 4)  float u_cs_light_y;
    layout(offset = 8)  float u_cs_light_z;
    layout(offset = 12) float u_cs_inv_proj[16];
    layout(offset = 76) float u_cs_sw;
    layout(offset = 80) float u_cs_sh;
};

mat4 load_inv_proj() {
    mat4 m;
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            m[i][j] = u_cs_inv_proj[i * 4 + j];
    return m;
}

void main() {
    float depth = texture(u_cs_depth, vUV).r;
    if (depth >= 1.0) {
        fragColor = vec4(1.0);
        return;
    }

    mat4 inv_p = load_inv_proj();
    vec2 res = vec2(u_cs_sw, u_cs_sh);
    vec3 light_dir = normalize(vec3(u_cs_light_x, u_cs_light_y, u_cs_light_z));

    vec2 ndc = vUV * 2.0 - 1.0;
    vec4 vp = inv_p * vec4(ndc, depth, 1.0);
    vec3 view_pos = vp.xyz / vp.w;

    int steps = 12;
    float ray_len = 0.5;
    float thickness = 0.04;
    float t = ray_len / float(steps);

    vec2 screen_step = (light_dir.xy * 5.0) / res;

    vec3 magic = vec3(0.06711056, 0.00583715, 52.9829189);
    float noise = fract(magic.z * fract(dot(gl_FragCoord.xy, magic.xy)));
    float jitter = noise * t;

    float shadow = 1.0;

    for (int i = 1; i <= steps; i++) {
        float offset = t * float(i) + jitter;
        vec3 ray_pos = view_pos + light_dir * offset;
        vec2 sample_uv = vUV + screen_step * float(i);

        if (sample_uv.x < 0.0 || sample_uv.x > 1.0 ||
            sample_uv.y < 0.0 || sample_uv.y > 1.0) break;

        float sd = texture(u_cs_depth, sample_uv).r;
        vec2 s_ndc = sample_uv * 2.0 - 1.0;
        vec4 svp = inv_p * vec4(s_ndc, sd, 1.0);
        vec3 sampled_view = svp.xyz / svp.w;

        float diff = sampled_view.z - ray_pos.z;
        if (diff > 0.0 && diff < thickness) {
            float penumbra = 1.0 - smoothstep(0.0, thickness, diff);
            shadow *= 1.0 - penumbra * 0.8;
        }
    }

    shadow = max(shadow, 0.0);

    fragColor = vec4(vec3(shadow), 1.0);
}
