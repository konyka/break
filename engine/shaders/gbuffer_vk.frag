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
layout(location = 4) out vec4 out_emissive; /* R584: RGBA16F HDR emissive */

layout(binding = 0) uniform sampler2D u_albedo;
layout(binding = 2) uniform sampler2D u_metallic_roughness;
layout(binding = 4) uniform sampler2D u_emissive; /* R582 */
/* R583: glTF occlusionTexture at set 0 binding 9 — the shared layout's only
 * otherwise-unwritten slot (the deferred LIGHTING pass uses binding 9 for
 * its emissive target, but binds its own descriptor set). */
layout(binding = 9) uniform sampler2D u_occlusion;

/* R595: tangent-space normal map at set 0 binding 3 — the shared material
 * layout's normal slot (bind_material always binds it; textureless materials
 * ride the flat 1x1 fallback so the perturbation is the identity). */
layout(binding = 3) uniform sampler2D u_normal_map;

/* R580/R581: glTF per-material factors via the aux UBO (std140).
 * The vert stage fills all 256B of push space (R204-A), so factors ride the
 * always-appended auxiliary UBO set instead: set=1 binding=0 here (base
 * pipeline layout: textures@0, ubo@1); the skinned variant uses
 * gbuffer_skinned_vk.frag with set=2 (its layout inserts the joint texel
 * set at index 1). u_factors: x/y = metallic/roughness factors,
 * z = AO strength (R583: scales the per-pixel occlusion texture as
 * mix(1.0, tex.r, z) — textureless materials bind the white 1x1 fallback
 * so ao = 1.0), w = emissive flag; u_emissive_factor (R582): rgb =
 * emissiveFactor x strength, composed with u_emissive into out_emissive.
 * Defaults (1,1,1,0)+(0,0,0,0) = passthrough, full AO, no emissive. */
layout(std140, set = 1, binding = 0) uniform GbufFactors { vec4 u_factors; vec4 u_emissive_factor; };

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

/* R595: tangent-space normal map perturbation — derivative TBN (the 32B/64B
 * vertex contracts carry no tangent attribute; pbr_clustered precedent). */
vec3 perturb_normal(vec3 n, vec2 uv) {
    vec3 map = texture(u_normal_map, uv).rgb * 2.0 - 1.0;
    vec3 q1  = dFdx(v_world_pos);
    vec3 q2  = dFdy(v_world_pos);
    vec2 st1 = dFdx(uv);
    vec2 st2 = dFdy(uv);
    vec3 t = normalize(q1 * st2.t - q2 * st1.t);
    vec3 b = -normalize(cross(n, t));
    return normalize(mat3(t, b, n) * map);
}

void main() {
    vec3  base  = texture(u_albedo, v_texcoord).rgb;
    vec2  mr    = texture(u_metallic_roughness, v_texcoord).bg;
    vec2  mrf   = mr * u_factors.xy; /* R580: glTF factor x texture composition */
    float metal = clamp(mrf.x, 0.0, 1.0);
    float rough = clamp(mrf.y, 0.04, 1.0);
    float ao    = mix(1.0, texture(u_occlusion, v_texcoord).r,
                      clamp(u_factors.z, 0.0, 1.0)); /* R583: glTF occlusion x strength */
    vec3  emis  = texture(u_emissive, v_texcoord).rgb * u_emissive_factor.rgb; /* R582 */

    out_albedo_metallic = vec4(base, metal);
    vec3 nrm = perturb_normal(normalize(v_normal), v_texcoord); /* R595 */
    out_normal          = vec4(octahedron_encode(nrm), 0.0, 1.0);
    out_roughness_ao    = vec4(rough, ao, clamp(u_factors.w, 0.0, 1.0), 1.0);
    out_emissive        = vec4(emis, 1.0); /* R584: HDR — no LDR clamp (RGBA16F) */
    out_velocity        = vec4(v_velocity, 0.0, 1.0);
}
