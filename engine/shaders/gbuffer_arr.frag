#version 450 core

/* R442: texture-array variant of gbuffer.frag — u_albedo and
 * u_metallic_roughness become sampler2DArray, layer selected by v_layer
 * (flat, from gl_BaseInstanceARB). MRT writes are byte-identical to
 * gbuffer.frag. */

layout(location = 0) in vec3 v_world_pos;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texcoord;
layout(location = 3) in vec2 v_velocity;
layout(location = 4) flat in uint v_layer;

layout(location = 0) out vec4 out_albedo_metallic; /* RGBA8 */
layout(location = 1) out vec4 out_normal;          /* RGBA16F (rg used) */
layout(location = 2) out vec4 out_roughness_ao;    /* RGBA8 */
layout(location = 3) out vec4 out_velocity;        /* NDC delta xy */
layout(location = 4) out vec4 out_emissive;        /* R584: RGBA16F HDR emissive */

layout(binding = 0) uniform sampler2DArray u_albedo;
layout(binding = 2) uniform sampler2DArray u_metallic_roughness;
layout(binding = 4) uniform sampler2DArray u_emissive; /* R582 */
/* R583: glTF occlusion array at unit 15 (GL; VK uses binding 9) — see
 * gbuffer.frag for the slot rationale. Textureless layers are white-filled
 * by the bake so mix(1.0, 1.0, z) = 1.0 (no occlusion). */
layout(binding = 15) uniform sampler2DArray u_occlusion;

/* R595: tangent-space normal map array at binding 3 — layer follows v_layer;
 * the pass binds the R594 baked per-layer normal_array (textureless layers
 * flat-filled, so the perturbation is the identity there). */
layout(binding = 3) uniform sampler2DArray u_normal_map_arr;

/* R580/R581: per-layer glTF material factors — indexed by v_layer, the
 * same layer that selects the albedo/MR/emissive array texels. std140
 * vec4 stride; capacity 64 = MAT_ARR_MAX_LAYERS (main.c). Production fills
 * it from MatArraySet via deferred_set_gbuffer_factor_array() /
 * deferred_set_gbuffer_emissive_array() (R582); layer 0 and textureless
 * materials get (1,1,1,0)+(0,0,0,0) = passthrough.
 * u_factor_arr: x/y = metallic/roughness factors (glTF composes
 * multiplicatively — the R93-1 additive defaults are retired);
 * z = AO strength (R583: scales the per-pixel occlusion texel as
 * mix(1.0, tex.r, z)), w = emissive flag.
 * u_emissive_arr (R582): rgb = emissiveFactor x emissiveStrength. */
layout(std140, binding = 0) uniform GbufFactorArr { vec4 u_factor_arr[64]; vec4 u_emissive_arr[64]; };

/* Octahedron normal encoding (Cigolle et al.). */
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

/* R595: tangent-space normal map perturbation — derivative TBN (the 32B
 * vertex contract carries no tangent attribute); the map layer follows
 * v_layer like every other array sampler in this pass. */
vec3 perturb_normal(vec3 n, vec2 uv) {
    vec3 map = texture(u_normal_map_arr, vec3(uv, float(v_layer))).rgb * 2.0 - 1.0;
    vec3 q1  = dFdx(v_world_pos);
    vec3 q2  = dFdy(v_world_pos);
    vec2 st1 = dFdx(uv);
    vec2 st2 = dFdy(uv);
    vec3 t = normalize(q1 * st2.t - q2 * st1.t);
    vec3 b = -normalize(cross(n, t));
    return normalize(mat3(t, b, n) * map);
}

void main() {
    vec4  fac     = u_factor_arr[min(v_layer, 63u)];   /* R580/R581 */
    vec4  efac    = u_emissive_arr[min(v_layer, 63u)]; /* R582 */
    vec3  base    = texture(u_albedo, vec3(v_texcoord, float(v_layer))).rgb;
    vec2  mr      = texture(u_metallic_roughness, vec3(v_texcoord, float(v_layer))).bg;
    vec2  mrf     = mr * fac.xy; /* R580: glTF factor x texture composition */
    float metal   = clamp(mrf.x, 0.0, 1.0);
    float rough   = clamp(mrf.y, 0.04, 1.0);
    float ao      = mix(1.0, texture(u_occlusion, vec3(v_texcoord, float(v_layer))).r,
                        clamp(fac.z, 0.0, 1.0)); /* R583: per-layer occlusion x strength */
    vec3  emis    = texture(u_emissive, vec3(v_texcoord, float(v_layer))).rgb * efac.rgb; /* R582 */

    out_albedo_metallic = vec4(base, metal);
    vec3 nrm = perturb_normal(normalize(v_normal), v_texcoord); /* R595 */
    out_normal          = vec4(octahedron_encode(nrm), 0.0, 1.0);
    out_roughness_ao    = vec4(rough, ao, clamp(fac.w, 0.0, 1.0), 1.0);
    out_emissive        = vec4(emis, 1.0); /* R584: HDR — no LDR clamp (RGBA16F) */
    out_velocity        = vec4(v_velocity, 0.0, 1.0);
}
