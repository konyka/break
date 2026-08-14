#version 450 core
/* R441: texture-array variant of blinn_phong.vert — forwards the indirect
 * cmd's first_instance as the sampler2DArray layer. #version 450 requires the
 * ARB suffix (unsuffixed gl_BaseInstance needs GLSL 460). */
#extension GL_ARB_shader_draw_parameters : require

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aNormal;
layout(location = 2) in vec2 aUV;

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_proj;
#ifdef FORWARD_MRT
layout(std140, binding = 0) uniform ForwardTemporal {
    mat4 u_prev_vp;
    mat4 u_prev_model;
};
#endif

out vec3 vWorldPos;
out vec3 vNormal;
out vec2 vUV;
flat out uint vLayer;
#ifdef FORWARD_MRT
out vec2 v_velocity;
#endif

void main() {
    vec4 world_pos = u_model * vec4(aPos, 1.0);
    vWorldPos = world_pos.xyz;
    vNormal = mat3(u_model) * aNormal;
    vUV = aUV;
    vLayer = uint(gl_BaseInstanceARB);
    vec4 curr_clip = u_proj * u_view * world_pos;
#ifdef FORWARD_MRT
    vec4 prev_clip = u_prev_vp * u_prev_model * vec4(aPos, 1.0);
    v_velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
#endif
    gl_Position = curr_clip;
}
