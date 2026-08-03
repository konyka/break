#pragma once
#include <core/types.h>
#include <rhi/rhi.h>

#define FONT_ATLAS_SIZE 512
/* Baked glyphs span ASCII (0x20-0x7E) plus Latin-1 supplement (0xA0-0xFF).
 * Codepoints are looked up through cp_map[] so UTF-8 text renders correctly. */
#define FONT_MAX_GLYPHS  256
#define FONT_CPMAP_SIZE  256
/* R400: TTF is read whole into memory for stbtt; cap before malloc. */
#define FONT_TTF_MAX_BYTES (32u << 20)  /* 32 MiB — large CJK fonts fit */
/* R436: sparse kern-pair table capacity. LiberationSans (the shipped font)
 * has 96 non-zero pairs in the baked ranges; 512 leaves ample headroom for
 * kern-heavy fonts at ~2 KB per FontRenderer. */
#define FONT_MAX_KERN_PAIRS 512

typedef struct {
    f32 x0, y0, x1, y1;
} FontRect;

/* R436: one kerning pair between two baked glyphs. kern is a fixed-point
 * advance adjustment in 1/64 pixel units at the baked font size (26.6-style;
 * signed, so pair tightening and loosening both fit). */
typedef struct {
    u8  a_idx;  /* glyph index of the left codepoint  */
    u8  b_idx;  /* glyph index of the right codepoint */
    i16 kern;   /* advance adjustment, 1/64 px        */
} FontKernPair;

typedef struct {
    u32     codepoint;
    FontRect uv;
    f32     advance;
    f32     x_off;
    f32     y_off;
    f32     width;
    f32     height;
} GlyphInfo;

typedef struct {
    RHIDevice  *device;
    RHITexture  atlas_tex;
    RHISampler  sampler;
    RHIPipeline pipeline;
    RHIBuffer   vbo[2]; /* R184: dual-slot vs in-flight font VS read */
    f32         font_size;
    f32         ascent;
    f32         descent;
    f32         line_gap;
    GlyphInfo   glyphs[FONT_MAX_GLYPHS];
    u32         glyph_count;
    i16         cp_map[FONT_CPMAP_SIZE]; /* codepoint(<256) -> glyph index, -1 if absent */
    FontKernPair kern_pairs[FONT_MAX_KERN_PAIRS]; /* R436: baked kern pairs */
    u32         kern_count;                       /* R436: valid entries     */
    f32         white_u, white_v;        /* UV of an opaque white texel for solid fills */

    u8         *quad_data;
    u32         quad_count;
    u32         quad_capacity;
} FontRenderer;

bool font_renderer_init(FontRenderer *fr, RHIDevice *dev, const char *ttf_path, f32 font_size);
void font_renderer_shutdown(FontRenderer *fr);
void font_renderer_begin(FontRenderer *fr);
void font_renderer_draw(FontRenderer *fr, const char *text, f32 x, f32 y,
                         f32 screen_w, f32 screen_h, f32 r, f32 g, f32 b, f32 a);
/* Solid color rectangle (pixels), reuses the text pipeline via the white texel. */
void font_renderer_draw_rect(FontRenderer *fr, f32 x, f32 y, f32 w, f32 h,
                             f32 screen_w, f32 screen_h, f32 r, f32 g, f32 b, f32 a);
/* Pixel width of a UTF-8 string at the baked font size. */
f32  font_renderer_text_width(const FontRenderer *fr, const char *text);
/* R436: kerning adjustment in pixels for adjacent codepoints a,b.
 * Returns 0 for unknown pairs, unbaked codepoints, and cp >= FONT_CPMAP_SIZE.
 * Callers pass the *effective* codepoint (after '?' fallback, i.e.
 * GlyphInfo.codepoint) so substituted glyphs kern like the real thing. */
f32  font_kern_advance(const FontRenderer *fr, u32 cp_a, u32 cp_b);
/* Line advance in pixels (ascent - descent + line_gap). */
f32  font_renderer_line_height(const FontRenderer *fr);
void font_renderer_end(FontRenderer *fr, RHICmdBuffer *cmd, f32 screen_w, f32 screen_h);
