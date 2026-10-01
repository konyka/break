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

layout(binding = 0) uniform sampler2DArray u_albedo;
layout(binding = 2) uniform sampler2DArray u_metallic_roughness;

/* R580/R581: per-layer glTF material factors — indexed by v_layer, the
 * same layer that selects the albedo/MR array texels. std140 vec4 stride;
 * capacity 64 = MAT_ARR_MAX_LAYERS (main.c). Production fills it from
 * MatArraySet via deferred_set_gbuffer_factor_array(); layer 0 and
 * textureless materials get (1,1,1,0) = passthrough. x/y = metallic/
 * roughness factors (glTF composes multiplicatively — the R93-1 additive
 * defaults are retired); z = AO strength, w = emissive flag. */
layout(std140, binding = 0) uniform GbufFactorArr { vec4 u_factor_arr[64]; };

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

void main() {
    vec4  fac     = u_factor_arr[min(v_layer, 63u)]; /* R580/R581 */
    vec3  base    = texture(u_albedo, vec3(v_texcoord, float(v_layer))).rgb;
    vec2  mr      = texture(u_metallic_roughness, vec3(v_texcoord, float(v_layer))).bg;
    vec2  mrf     = mr * fac.xy; /* R580: glTF factor x texture composition */
    float metal   = clamp(mrf.x, 0.0, 1.0);
    float rough   = clamp(mrf.y, 0.04, 1.0);
    float ao      = clamp(fac.z, 0.0, 1.0); /* R581: per-layer AO strength */

    out_albedo_metallic = vec4(base, metal);
    out_normal          = vec4(octahedron_encode(v_normal), 0.0, 1.0);
    out_roughness_ao    = vec4(rough, ao, clamp(fac.w, 0.0, 1.0), 1.0);
    out_velocity        = vec4(v_velocity, 0.0, 1.0);
}
