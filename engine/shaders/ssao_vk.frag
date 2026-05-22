#version 450 core

layout(location = 0) in vec2 vUV;

layout(push_constant) uniform Push {
    mat4 u_ssao_proj;
    mat4 u_ssao_inv_proj;
    float u_ssao_sw;
    float u_ssao_sh;
    float u_ssao_radius;
    float u_ssao_bias;
} pc;

layout(binding = 0) uniform sampler2D u_depth;

layout(location = 0) out vec4 frag_color;

const int KERNEL_SIZE = 16;
vec3 KERNEL[KERNEL_SIZE];

vec3 reconstruct_pos(vec2 uv, float depth) {
    vec4 ndc = vec4(uv * 2.0 - 1.0, depth * 2.0 - 1.0, 1.0);
    vec4 view = pc.u_ssao_inv_proj * ndc;
    return view.xyz / view.w;
}

void main() {
    KERNEL[0]  = vec3( 0.05,  0.15, 0.25);
    KERNEL[1]  = vec3(-0.10,  0.05, 0.35);
    KERNEL[2]  = vec3( 0.20, -0.10, 0.45);
    KERNEL[3]  = vec3(-0.15,  0.20, 0.55);
    KERNEL[4]  = vec3( 0.10, -0.20, 0.65);
    KERNEL[5]  = vec3(-0.25,  0.10, 0.30);
    KERNEL[6]  = vec3( 0.15,  0.25, 0.50);
    KERNEL[7]  = vec3(-0.05, -0.15, 0.40);
    KERNEL[8]  = vec3( 0.30,  0.05, 0.20);
    KERNEL[9]  = vec3(-0.20, -0.25, 0.60);
    KERNEL[10] = vec3( 0.25,  0.15, 0.35);
    KERNEL[11] = vec3(-0.30,  0.20, 0.45);
    KERNEL[12] = vec3( 0.05, -0.30, 0.55);
    KERNEL[13] = vec3(-0.15,  0.30, 0.25);
    KERNEL[14] = vec3( 0.35, -0.05, 0.40);
    KERNEL[15] = vec3(-0.25, -0.10, 0.30);

    float depth = texture(u_depth, vUV).r;
    if (depth >= 1.0) {
        frag_color = vec4(1.0);
        return;
    }

    vec3 pos = reconstruct_pos(vUV, depth);

    vec3 normal = normalize(cross(dFdx(pos), dFdy(pos)));

    vec2 noise_scale = vec2(pc.u_ssao_sw / 4.0, pc.u_ssao_sh / 4.0);

    float occlusion = 0.0;
    for (int i = 0; i < KERNEL_SIZE; i++) {
        vec3 sample_dir = KERNEL[i];
        float scale = float(i) / float(KERNEL_SIZE);
        scale = mix(0.1, 1.0, scale * scale);
        sample_dir *= scale;

        vec3 tangent = normalize(cross(normal, vec3(0.0, 1.0, 0.0)));
        float d = dot(normal, vec3(0.0, 1.0, 0.0));
        if (abs(d) > 0.99) tangent = normalize(cross(normal, vec3(1.0, 0.0, 0.0)));
        vec3 bitangent = cross(normal, tangent);

        vec3 sample_pos = pos + (tangent * sample_dir.x + bitangent * sample_dir.y + normal * sample_dir.z) * pc.u_ssao_radius;

        vec4 offset = pc.u_ssao_proj * vec4(sample_pos, 1.0);
        offset.xy = offset.xy / offset.w * 0.5 + 0.5;

        float sample_depth = texture(u_depth, offset.xy).r;
        vec3 sample_world = reconstruct_pos(offset.xy, sample_depth);

        float range_check = smoothstep(0.0, 1.0, pc.u_ssao_radius / abs(pos.z - sample_world.z));
        occlusion += (sample_world.z >= sample_pos.z + pc.u_ssao_bias ? 1.0 : 0.0) * range_check;
    }
    occlusion = 1.0 - occlusion / float(KERNEL_SIZE);

    frag_color = vec4(occlusion, occlusion, occlusion, 1.0);
}
