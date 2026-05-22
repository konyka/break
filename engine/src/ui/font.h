#pragma once
#include <core/types.h>
#include <rhi/rhi.h>

#define FONT_ATLAS_SIZE 512
#define FONT_GLYPH_COUNT 96

typedef struct {
    f32 x0, y0, x1, y1;
} FontRect;

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
    RHIBuffer   vbo;
    f32         font_size;
    f32         ascent;
    f32         descent;
    f32         line_gap;
    GlyphInfo   glyphs[FONT_GLYPH_COUNT];

    u8         *quad_data;
    u32         quad_count;
    u32         quad_capacity;
} FontRenderer;

bool font_renderer_init(FontRenderer *fr, RHIDevice *dev, const char *ttf_path, f32 font_size);
void font_renderer_shutdown(FontRenderer *fr);
void font_renderer_begin(FontRenderer *fr);
void font_renderer_draw(FontRenderer *fr, const char *text, f32 x, f32 y,
                         f32 screen_w, f32 screen_h, f32 r, f32 g, f32 b, f32 a);
void font_renderer_end(FontRenderer *fr, RHICmdBuffer *cmd, f32 screen_w, f32 screen_h);
