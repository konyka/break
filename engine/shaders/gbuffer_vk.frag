#version 450 core

/* G-Buffer write pass -- fragment stage (Vulkan). */

layout(location = 0) in vec3 v_world_pos;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texcoord;
layout(location = 3) in vec2 v_velocity;

layout(location = 0) out vec4 out_albedo_metallic;
layout(location = 1) out vec4 out_normal;
layout(location = 2) out vec4 out_roughness_ao;
layout(location = 3) out vec4 out_velocity;

layout(binding = 0) uniform sampler2D u_albedo;
layout(binding = 2) uniform sampler2D u_metallic_roughness;

/* R580: glTF per-material metallic/roughness factors via the aux UBO.
 * The vert stage fills all 256B of push space (R204-A), so factors ride the
 * always-appended auxiliary UBO set instead: set=1 binding=0 here (base
 * pipeline layout: textures@0, ubo@1); the skinned variant uses
 * gbuffer_skinned_vk.frag with set=2 (its layout inserts the joint texel
 * set at index 1). Default (1,1) = texture passthrough. */
layout(std140, set = 1, binding = 0) uniform GbufMR { vec2 u_mr_factor; };
const float u_ao_default = 1.0;
const float u_emissive_flag = 0.0;

vec2 octahedron_encode(vec3 n) {
    n = normalize(n);
    n /= (abs(n.x) + abs(n.y) + abs(n.z));
    if (n.z < 0.0) {
        vec2 wrapped = (1.0 - abs(n.yx)) * vec2(
            n.x >= 0.0 ? 1.0 : -1.0,
            n.y >= 0.0 ? 1.0 : -1.0);
        n.xy = wrapped;
    }
    return n.xy * 0.5 + 0.5;
}

void main() {
    vec3  base  = texture(u_albedo, v_texcoord).rgb;
    vec2  mr    = texture(u_metallic_roughness, v_texcoord).bg;
    vec2  mrf   = mr * u_mr_factor; /* R580: glTF factor x texture composition */
    float metal = clamp(mrf.x, 0.0, 1.0);
    float rough = clamp(mrf.y, 0.04, 1.0);
    float ao    = clamp(u_ao_default, 0.0, 1.0);

    out_albedo_metallic = vec4(base, metal);
    out_normal          = vec4(octahedron_encode(v_normal), 0.0, 1.0);
    out_roughness_ao    = vec4(rough, ao, u_emissive_flag, 1.0);
    out_velocity        = vec4(v_velocity, 0.0, 1.0);
}
