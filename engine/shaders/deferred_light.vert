#version 430 core

/* Deferred lighting pass -- vertex stage (GL).
 * Full-screen triangle via the gl_VertexID trick: emits a single oversized
 * triangle whose UVs cover [0,1]x[0,1] across the framebuffer with no
 * vertex buffer or index buffer bound. */

layout(location = 0) out vec2 v_texcoord;

void main() {
    v_texcoord = vec2((gl_VertexID << 1) & 2, gl_VertexID & 2);
    gl_Position = vec4(v_texcoord * 2.0 - 1.0, 0.0, 1.0);
}
