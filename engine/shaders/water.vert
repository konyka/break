#version 450 core

layout(location = 0) in vec3 aPos;

uniform mat4 u_view;
uniform mat4 u_proj;
uniform float u_water_y;
#ifdef FORWARD_MRT
layout(std140, binding = 0) uniform ForwardTemporal {
    mat4 u_prev_vp;
    mat4 u_prev_model_unused;
};
#endif

out vec3 vWorldPos;
#ifdef FORWARD_MRT
out vec2 v_velocity;
#endif

void main() {
    /* R235-B: Mesh verts sit at y=0; lift to logical water plane. */
    vec3 wp = vec3(aPos.x, u_water_y, aPos.z);
    vWorldPos = wp;
    vec4 curr_clip = u_proj * u_view * vec4(wp, 1.0);
#ifdef FORWARD_MRT
    vec4 prev_clip = u_prev_vp * vec4(wp, 1.0);
    v_velocity = curr_clip.xy / curr_clip.w - prev_clip.xy / prev_clip.w;
#endif
    gl_Position = curr_clip;
}
