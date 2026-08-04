#version 450 core

layout(location = 0) in vec2 vUV;
layout(location = 1) in vec4 vColor;

layout(location = 0) out vec4 frag_color;

layout(binding = 0) uniform sampler2D u_atlas;

void main() {
    /* R282 (CORRECTNESS): glyph data lives in ALPHA (font.c uploads
     * R=G=B=255, A=stbtt value); sampling .r read the constant 255. Sample
     * .a. The solid-fill white patch (draw_rect) has A=255, so rects are
     * unaffected.
     *
     * R439: the atlas is now a signed distance field (stbtt_GetCodepointSDF,
     * on-edge value 128 ≈ 0.5), not coverage. Threshold at the on-edge value
     * and antialias with a smoothstep whose half-width follows the
     * screen-space derivative, so edges stay sharp at any scale. Mirrors
     * font_sdf_coverage() in font.h. The max() guard keeps smoothstep's
     * edge0 < edge1 in constant regions (white patch) where fwidth is 0. */
    float dist = texture(u_atlas, vUV).a;
    float w = max(fwidth(dist) * 0.5, 1e-4);
    float a = smoothstep(0.5 - w, 0.5 + w, dist);
    frag_color = vec4(vColor.rgb, vColor.a * a);
}
