#version 330 core

in vec2 vUV;
in vec4 vColor;

out vec4 frag_color;

uniform sampler2D u_atlas;

void main() {
    /* Coverage alpha (NOT SDF): the RHI vgcanvas atlas stores raw coverage
     * bitmaps (R=G=B=255, A = stbtt coverage; see atlas_copy_glyph in
     * my_vgcanvas_break_rhi.c). The old SDF smoothstep made text and solid
     * patches render wrong here. White-patch pixels have A=255, so rects
     * stay opaque; glyph edges get correct coverage blending. */
    float cov = texture(u_atlas, vUV).a;
    frag_color = vec4(vColor.rgb, vColor.a * cov);
}
