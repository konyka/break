#version 430 core

/* G-Buffer write pass -- fragment stage (GL).
 * Writes 3 attachments per the deferred RT layout. The current RHI binds
 * a single attachment per FBO; in that case only out_albedo_metallic is
 * written (RT0 path). When the host supports MRT the same shader feeds all
 * three targets in one pass. */

layout(location = 0) in vec3 v_world_pos;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texcoord;
layout(location = 3) in vec2 v_velocity;

layout(location = 0) out vec4 out_albedo_metallic; /* RGBA8 */
layout(location = 1) out vec4 out_normal;          /* RGBA16F (rg used) */
layout(location = 2) out vec4 out_roughness_ao;    /* RGBA8 */
layout(location = 3) out vec4 out_velocity;        /* NDC delta xy */

layout(binding = 0) uniform sampler2D u_albedo;
layout(binding = 2) uniform sampler2D u_metallic_roughness;

/* R580/R581: glTF per-material scalar factors arrive via the aux UBO
 * (std140 vec4; GL binding 0), written per material by
 * deferred_bind_gbuffer_factors(). x/y = metallic/roughness factors
 * (multiplicative, glTF); z = AO strength (material occlusion strength —
 * scalar channel until a per-pixel occlusion texture exists); w = emissive
 * flag (1 = material has emissive content). Default (1,1,1,0) = texture
 * passthrough, full AO, no emissive. The R93-1 additive defaults for
 * metal/rough are retired (glTF composes multiplicatively). */
layout(std140, binding = 0) uniform GbufFactors { vec4 u_factors; };

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
    float ao      = clamp(u_factors.z, 0.0, 1.0); /* R581: material AO strength */

    out_albedo_metallic = vec4(base, metal);
    out_normal          = vec4(octahedron_encode(v_normal), 0.0, 1.0);
    out_roughness_ao    = vec4(rough, ao, clamp(u_factors.w, 0.0, 1.0), 1.0);
    out_velocity        = vec4(v_velocity, 0.0, 1.0);
}
