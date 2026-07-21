#version 330 core

in vec2 vUV;
in vec4 vColor;

out vec4 frag_color;

uniform sampler2D u_atlas;

void main() {
    /* R282 (CORRECTNESS): the font atlas stores glyph coverage in ALPHA
     * (font.c uploads R=G=B=255, A=stbtt coverage); sampling .r read the
     * constant 255 → coverage was always 1.0, so every glyph filled its whole
     * quad as a solid opaque rectangle (and holes like 'O' centres stayed
     * filled). Sample .a to recover the antialiased glyph shape. The solid-fill
     * white patch (draw_rect) has A=255, so rects are unaffected. */
    float a = texture(u_atlas, vUV).a;
    frag_color = vec4(vColor.rgb, vColor.a * a);
}
