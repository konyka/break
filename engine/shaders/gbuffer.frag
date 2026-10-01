#version 430 core

/* G-Buffer write pass -- fragment stage (GL).
 * Writes 5 attachments per the deferred RT layout (R582: +RT4 emissive).
 * The current RHI binds a single attachment per FBO; in that case only
 * out_albedo_metallic is written (RT0 path). When the host supports MRT
 * the same shader feeds all five targets in one pass. */

layout(location = 0) in vec3 v_world_pos;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texcoord;
layout(location = 3) in vec2 v_velocity;

layout(location = 0) out vec4 out_albedo_metallic; /* RGBA8 */
layout(location = 1) out vec4 out_normal;          /* RGBA16F (rg used) */
layout(location = 2) out vec4 out_roughness_ao;    /* RGBA8 */
layout(location = 3) out vec4 out_velocity;        /* NDC delta xy */
layout(location = 4) out vec4 out_emissive;        /* R582: RGBA8 LDR emissive */

layout(binding = 0) uniform sampler2D u_albedo;
layout(binding = 2) uniform sampler2D u_metallic_roughness;
layout(binding = 4) uniform sampler2D u_emissive; /* R582 */
/* R583: glTF occlusionTexture at unit 15 — 5/6 are vertex-stage texel-buffer
 * units, 7-14 taken by the shared material/IBL map; 15 is free in this pass
 * (it is the deferred LIGHTING pass's emissive unit — different pass). */
layout(binding = 15) uniform sampler2D u_occlusion;

/* R580/R581: glTF per-material scalar factors arrive via the aux UBO
 * (std140; GL binding 0), written per material by
 * deferred_bind_gbuffer_factors(). u_factors: x/y = metallic/roughness
 * factors (multiplicative, glTF); z = AO strength (R583: scales the
 * per-pixel occlusion texture as mix(1.0, tex.r, z) — textureless
 * materials bind the white 1x1 fallback so ao = 1.0);
 * w = emissive flag (1 = material emits). u_emissive_factor (R582):
 * rgb = emissiveFactor x emissiveStrength, composed with the emissive
 * texture into out_emissive (LDR-clamped). Defaults (1,1,1,0)+(0,0,0,0) =
 * texture passthrough, full AO, no emissive. */
layout(std140, binding = 0) uniform GbufFactors { vec4 u_factors; vec4 u_emissive_factor; };

/* Octahedron normal encoding (Cigolle et al.). Lossless on the unit sphere
 * up to 16-bit precision; deterministic round-trip with octahedron_decode. */
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
    vec3  base    = texture(u_albedo, v_texcoord).rgb;
    vec2  mr      = texture(u_metallic_roughness, v_texcoord).bg;
    vec2  mrf     = mr * u_factors.xy; /* R580: glTF factor x texture composition */
    float metal   = clamp(mrf.x, 0.0, 1.0);
    float rough   = clamp(mrf.y, 0.04, 1.0);
    float ao      = mix(1.0, texture(u_occlusion, v_texcoord).r,
                        clamp(u_factors.z, 0.0, 1.0)); /* R583: glTF occlusion x strength */
    vec3  emis    = texture(u_emissive, v_texcoord).rgb * u_emissive_factor.rgb; /* R582 */

    out_albedo_metallic = vec4(base, metal);
    out_normal          = vec4(octahedron_encode(v_normal), 0.0, 1.0);
    out_roughness_ao    = vec4(rough, ao, clamp(u_factors.w, 0.0, 1.0), 1.0);
    out_emissive        = vec4(clamp(emis, 0.0, 1.0), 1.0); /* R582: LDR */
    out_velocity        = vec4(v_velocity, 0.0, 1.0);
}
