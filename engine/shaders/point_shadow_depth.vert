#version 330 core

layout(location = 0) in vec3 a_position;

uniform mat4 u_mvp;
uniform mat4 u_model;

out vec3 v_world_pos;

void main() {
    vec4 world = u_model * vec4(a_position, 1.0);
    v_world_pos = world.xyz;
    /* R248: u_mvp is only the cubemap face view-proj; the clip position must
     * include u_model too, or the rasterized coverage uses model-space verts
     * while v_world_pos (and thus gl_FragDepth) uses world space — mismatched
     * point-shadow texels for any non-identity node transform. Legacy per-mesh
     * path uploads world_transform into u_model; mega-buffer/terrain use identity
     * so this stays byte-identical there. */
    gl_Position = u_mvp * world;
}
