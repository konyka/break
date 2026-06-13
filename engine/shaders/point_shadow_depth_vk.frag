#version 450 core

layout(location = 0) in vec3 v_world_pos;

layout(push_constant) uniform PushConstants {
    mat4 u_model;
    mat4 u_mvp;
    vec4 u_light_pos;
    vec4 u_far_plane;
} pc;

void main() {
    float dist = length(v_world_pos - pc.u_light_pos.xyz);
    gl_FragDepth = clamp(dist / max(pc.u_far_plane.x, 0.0001), 0.0, 1.0);
}
