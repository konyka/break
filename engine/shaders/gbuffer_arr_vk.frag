#version 450 core

/* R442: texture-array variant of gbuffer_vk.frag — bindings 0 and 2 become
 * sampler2DArray (the shared COMBINED_IMAGE_SAMPLER layout accepts a
 * 2D_ARRAY view unchanged), layer selected by v_layer (flat, from
 * gl_BaseInstanceARB). MRT writes are byte-identical to gbuffer_vk.frag. */

layout(location = 0) in vec3 v_world_pos;
layout(location = 1) in vec3 v_normal;
layout(location = 2) in vec2 v_texcoord;
layout(location = 3) in vec2 v_velocity;
layout(location = 4) flat in uint v_layer;

layout(location = 0) out vec4 out_albedo_metallic;
layout(location = 1) out vec4 out_normal;
layout(location = 2) out vec4 out_roughness_ao;
layout(location = 3) out vec4 out_velocity;

layout(binding = 0) uniform sampler2DArray u_albedo;
layout(binding = 2) uniform sampler2DArray u_metallic_roughness;

/* R204-A: match gbuffer_vk.frag consts — C never uploaded these. */
const float u_metallic_default = 0.0;
const float u_roughness_default = 0.0;
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
    vec3  base  = texture(u_albedo, vec3(v_texcoord, float(v_layer))).rgb;
    vec2  mr    = texture(u_metallic_roughness, vec3(v_texcoord, float(v_layer))).bg;
    float metal = clamp(mr.x + u_metallic_default, 0.0, 1.0);
    float rough = clamp(mr.y + u_roughness_default, 0.04, 1.0);
    float ao    = clamp(u_ao_default, 0.0, 1.0);

    out_albedo_metallic = vec4(base, metal);
    out_normal          = vec4(octahedron_encode(v_normal), 0.0, 1.0);
    out_roughness_ao    = vec4(rough, ao, u_emissive_flag, 1.0);
    out_velocity        = vec4(v_velocity, 0.0, 1.0);
}
