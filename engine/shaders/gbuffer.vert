#version 430 core

/* G-Buffer write pass -- vertex stage (GL).
 * Layout matches `pbr_clustered.vert`: pos + normal + uv from vertex stream;
 * tangent is derived from screen-space derivatives in the fragment stage. */

layout(location = 0) in vec3 a_position;
layout(location = 1) in vec3 a_normal;
layout(location = 2) in vec2 a_texcoord;

layout(location = 0) out vec3 v_world_pos;
layout(location = 1) out vec3 v_normal;
layout(location = 2) out vec2 v_texcoord;
layout(location = 3) out vec2 v_velocity;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;
uniform mat4 u_prev_vp;

void main() {
    vec4 wp     = u_model * vec4(a_position, 1.0);
    v_world_pos = wp.xyz;
    v_normal    = mat3(u_model) * a_normal;
    v_texcoord  = a_texcoord;
    vec4 curr_clip = u_proj * u_view * wp;
    vec4 prev_clip = u_prev_vp * wp;
    vec2 curr_ndc = curr_clip.xy / curr_clip.w;
    vec2 prev_ndc = prev_clip.xy / prev_clip.w;
    v_velocity  = curr_ndc - prev_ndc;
    gl_Position = curr_clip;
}
