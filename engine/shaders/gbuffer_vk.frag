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

/* R580/R581: glTF per-material factors via the aux UBO (std140 vec4).
 * The vert stage fills all 256B of push space (R204-A), so factors ride the
 * always-appended auxiliary UBO set instead: set=1 binding=0 here (base
 * pipeline layout: textures@0, ubo@1); the skinned variant uses
 * gbuffer_skinned_vk.frag with set=2 (its layout inserts the joint texel
 * set at index 1). x/y = metallic/roughness factors, z = AO strength,
 * w = emissive flag; default (1,1,1,0) = passthrough, full AO, no emissive. */
layout(std140, set = 1, binding = 0) uniform GbufFactors { vec4 u_factors; };

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
    vec2  mrf   = mr * u_factors.xy; /* R580: glTF factor x texture composition */
    float metal = clamp(mrf.x, 0.0, 1.0);
    float rough = clamp(mrf.y, 0.04, 1.0);
    float ao    = clamp(u_factors.z, 0.0, 1.0); /* R581: material AO strength */

    out_albedo_metallic = vec4(base, metal);
    out_normal          = vec4(octahedron_encode(v_normal), 0.0, 1.0);
    out_roughness_ao    = vec4(rough, ao, clamp(u_factors.w, 0.0, 1.0), 1.0);
    out_velocity        = vec4(v_velocity, 0.0, 1.0);
}
