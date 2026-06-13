#version 450 core

/* Fullscreen-triangle vertex shader shared by every post-process pass.
 * glslang predefines VULKAN when compiling for the Vulkan target, so the
 * Vulkan-only gl_VertexIndex builtin is selected there and the desktop-GL
 * gl_VertexID everywhere else. The explicit varying location is valid in
 * GLSL 4.50 on both backends. */
#ifdef VULKAN
#define VERT_INDEX gl_VertexIndex
#else
#define VERT_INDEX gl_VertexID
#endif

layout(location = 0) out vec2 vUV;

const vec2 POS[3] = vec2[3](
    vec2(-1.0, -1.0),
    vec2( 3.0, -1.0),
    vec2(-1.0,  3.0)
);

void main() {
    vec2 p = POS[VERT_INDEX];
    gl_Position = vec4(p, 1.0, 1.0);
    vUV = p * 0.5 + 0.5;
}
