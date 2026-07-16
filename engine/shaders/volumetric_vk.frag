#version 450

layout(location = 0) in vec2 vUV;
layout(location = 0) out vec4 fragColor;

layout(binding = 0) uniform sampler2D u_vol_depth;
layout(binding = 1) uniform sampler2D u_vol_shadow;

layout(push_constant) uniform VolParams {
    layout(offset = 0)   mat4 u_vol_inv_proj;
    layout(offset = 64)  mat4 u_vol_view;
    layout(offset = 128) float u_vol_ldx;
    layout(offset = 132) float u_vol_ldy;
    layout(offset = 136) float u_vol_ldz;
    layout(offset = 140) float u_vol_lcx;
    layout(offset = 144) float u_vol_lcy;
    layout(offset = 148) float u_vol_lcz;
    layout(offset = 152) float u_vol_density;
    layout(offset = 156) float u_vol_fog_r;
    layout(offset = 160) float u_vol_fog_g;
    layout(offset = 164) float u_vol_fog_b;
    layout(offset = 168) float u_vol_sw;
    layout(offset = 172) float u_vol_sh;
    /* R224-B: CPU inv(view); fits in 256B push (ends @240). */
    layout(offset = 176) mat4 u_vol_inv_view;
};

vec3 view_pos_from_depth(vec2 uv, float depth) {
    vec4 clip = vec4(uv * 2.0 - 1.0, depth * 2.0 - 1.0, 1.0);
    vec4 view_h = u_vol_inv_proj * clip;
    return view_h.xyz / view_h.w;
}

void main() {
    float depth = texture(u_vol_depth, vUV).r;

    vec3 ray_start = vec3(0.0);
    vec3 ray_end = view_pos_from_depth(vUV, depth);
    float ray_length = length(ray_end - ray_start);

    if (depth >= 1.0) {
        ray_end = view_pos_from_depth(vUV, 0.999) * 5.0;
        ray_length = length(ray_end);
    }

    vec3 ray_dir = ray_length > 0.001 ? (ray_end - ray_start) / ray_length : vec3(0.0, 0.0, -1.0);

    int steps = 16;
    float step_size = ray_length / float(steps);

    vec3 fog_color = vec3(u_vol_fog_r, u_vol_fog_g, u_vol_fog_b);
    /* R206-A: sun_dir is world-space; rays are view-space — transform before dot. */
    vec3 light_dir = normalize((u_vol_view * vec4(u_vol_ldx, u_vol_ldy, u_vol_ldz, 0.0)).xyz);
    float light_amount = max(dot(-ray_dir, light_dir), 0.0);

    vec3 accum = vec3(0.0);
    float transmittance = 1.0;

    /* R83-2: Hoist loop-invariant texture sample + lighting computation.
     * vUV is a fragment input — texture(u_vol_shadow, vUV) returns the same
     * value every iteration. */
    float shadow = texture(u_vol_shadow, vUV).r;
    float light_visibility = shadow > 0.01 ? 1.0 : 0.15;
    vec3 lighting = fog_color * 0.3 + vec3(u_vol_lcx, u_vol_lcy, u_vol_lcz) * light_amount * light_visibility;
    /* R209-B / R224-B: Height fog needs world Y from CPU inv(view). */
    for (int i = 0; i < steps; i++) {
        float t = (float(i) + 0.5) * step_size;
        vec3 pos = ray_start + ray_dir * t;

        float density = u_vol_density;
        float world_y = (u_vol_inv_view * vec4(pos, 1.0)).y;
        float height_factor = exp(-world_y * 0.3);
        density *= max(height_factor, 0.0);

        if (density < 0.0001) continue;

        float fog_amount = density * step_size;
        accum += lighting * transmittance * fog_amount;
        transmittance *= 1.0 - fog_amount;
        transmittance = max(transmittance, 0.0);
    }

    fragColor = vec4(accum, 1.0 - transmittance);
}
