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

/* R93-1: These uniforms are never set from C code. Use const defaults.
 * u_ao_default=1.0 (full AO, no darkening) — was 0.0 (no AO) which was a bug. */
const float u_metallic_default = 0.0;
const float u_roughness_default = 0.0;
const float u_ao_default = 1.0;
const float u_emissive_flag = 0.0;

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
    float metal   = clamp(mr.x + u_metallic_default, 0.0, 1.0);
    float rough   = clamp(mr.y + u_roughness_default, 0.04, 1.0);
    float ao      = clamp(u_ao_default, 0.0, 1.0);

    out_albedo_metallic = vec4(base, metal);
    out_normal          = vec4(octahedron_encode(v_normal), 0.0, 1.0);
    out_roughness_ao    = vec4(rough, ao, u_emissive_flag, 1.0);
    out_velocity        = vec4(v_velocity, 0.0, 1.0);
}
