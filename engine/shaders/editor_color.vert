#version 450 core

/* Stage 4 scene editor Phase 2 Task 3: minimal unlit flat-color pipeline for
 * the editor viewport (entity proxy cubes + gizmo handles). Position-only
 * vertex input (RHI vertex_stride == 12 layout); per-draw MVP + color. */

layout(location = 0) in vec3 aPos;

uniform mat4 u_mvp;

void main() {
    gl_Position = u_mvp * vec4(aPos, 1.0);
}
