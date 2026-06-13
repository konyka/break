#version 330 core

in vec3 v_world_pos;

uniform vec3  u_light_pos;
uniform float u_far_plane;

void main() {
    float dist = length(v_world_pos - u_light_pos);
    /* Linear depth in [0, 1] */
    gl_FragDepth = clamp(dist / max(u_far_plane, 0.0001), 0.0, 1.0);
}
