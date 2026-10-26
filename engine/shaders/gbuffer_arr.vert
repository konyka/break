#version 450 core

/* R442: texture-array variant of gbuffer.vert — forwards the indirect cmd's
 * first_instance as the sampler2DArray layer shared by the albedo and
 * metallic-roughness arrays. #version 450 requires the ARB suffix
 * (unsuffixed gl_BaseInstance needs GLSL 460). */
#extension GL_ARB_shader_draw_parameters : require

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texcoord;

layout(location = 0) out vec3 v_world_pos;
layout(location = 1) out vec3 v_normal;
layout(location = 2) out vec2 v_texcoord;
layout(location = 3) out vec2 v_velocity;
layout(location = 4) flat out uint v_layer;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;
uniform mat4 u_prev_mvp;

#ifdef LOD_FADE
layout(location = 5) flat out float vLodFade;
#endif
void main() {
#ifdef LOD_FADE
    uint fade_code = uint(gl_BaseInstanceARB) >> 16;
    vLodFade = fade_code == 0u ? 0.0 : float(int(fade_code) - 16);
#endif
    vec4 wp     = u_model * vec4(a_position, 1.0);
    v_world_pos = wp.xyz;
    v_normal    = mat3(u_model) * a_normal;
    v_texcoord  = a_texcoord;
#ifdef LOD_FADE
    v_layer     = uint(gl_BaseInstanceARB) & 0xFFFFu;
#else
    v_layer     = uint(gl_BaseInstanceARB);
#endif
    vec4 curr_clip = u_proj * u_view * wp;
    vec4 prev_clip = u_prev_mvp * vec4(a_position, 1.0);
    vec2 curr_ndc = curr_clip.xy / curr_clip.w;
    vec2 prev_ndc = prev_clip.xy / prev_clip.w;
    v_velocity  = curr_ndc - prev_ndc;
    gl_Position = curr_clip;
}
