#include <ui/font.h>
#include <ui/utf8.h>
#include <core/log.h>
#include <math/math.h>
#include <rhi/rhi.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define STB_TRUETYPE_IMPLEMENTATION
#include <stb_truetype.h>

/* Codepoint ranges baked into the atlas (inclusive). ASCII printable +
 * Latin-1 supplement covers western European accented letters and symbols. */
typedef struct { u32 first, last; } GlyphRange;
static const GlyphRange FONT_RANGES[] = {
    { 0x20, 0x7E },  /* Basic Latin (printable ASCII) */
    { 0xA0, 0xFF },  /* Latin-1 supplement            */
};
#define FONT_RANGE_COUNT (sizeof(FONT_RANGES) / sizeof(FONT_RANGES[0]))

static const GlyphInfo *font_lookup_glyph(const FontRenderer *fr, u32 cp) {
    if (cp < FONT_CPMAP_SIZE) {
        i16 gi = fr->cp_map[cp];
        if (gi >= 0) return &fr->glyphs[gi];
    }
    /* Fallback to '?' so unknown codepoints stay visible. */
    if ('?' < FONT_CPMAP_SIZE && fr->cp_map['?'] >= 0)
        return &fr->glyphs[fr->cp_map['?']];
    return NULL;
}

extern RHIDevice *g_current_device;

typedef struct {
    f32 x, y;
    f32 u, v;
    f32 r, g, b, a;
} FontVertex;

bool font_renderer_init(FontRenderer *fr, RHIDevice *dev, const char *ttf_path, f32 font_size) {
    memset(fr, 0, sizeof(*fr));
    fr->device = dev;
    fr->font_size = font_size;

    FILE *f = fopen(ttf_path, "rb");
    if (!f) {
        LOG_WARN("Font: cannot open %s", ttf_path);
        return false;
    }
    fseek(f, 0, SEEK_END);
    long sz = ftell(f);
    fseek(f, 0, SEEK_SET);
    u8 *ttf_buf = malloc((usize)sz);
    if (!ttf_buf) { fclose(f); return false; }
    fread(ttf_buf, 1, (usize)sz, f);
    fclose(f);

    stbtt_fontinfo fi;
    if (!stbtt_InitFont(&fi, ttf_buf, stbtt_GetFontOffsetForIndex(ttf_buf, 0))) {
        LOG_WARN("Font: stbtt_InitFont failed");
        free(ttf_buf);
        return false;
    }

    f32 scale = stbtt_ScaleForPixelHeight(&fi, font_size);

    int iascent, idescent, ilinegap;
    stbtt_GetFontVMetrics(&fi, &iascent, &idescent, &ilinegap);
    fr->ascent = (f32)iascent * scale;
    fr->descent = (f32)idescent * scale;
    fr->line_gap = (f32)ilinegap * scale;

    u8 *atlas = calloc(FONT_ATLAS_SIZE * FONT_ATLAS_SIZE, 1);
    if (!atlas) { free(ttf_buf); return false; }

    for (u32 i = 0; i < FONT_CPMAP_SIZE; i++) fr->cp_map[i] = -1;
    fr->glyph_count = 0;

    /* Reserve a small opaque white patch at the top-left for solid-fill quads.
     * Sample its center so linear filtering never picks transparent neighbors. */
    const u32 WHITE_PATCH = 4;
    for (u32 wy = 0; wy < WHITE_PATCH; wy++)
        for (u32 wx = 0; wx < WHITE_PATCH; wx++)
            atlas[wy * FONT_ATLAS_SIZE + wx] = 255;
    fr->white_u = 2.0f / (f32)FONT_ATLAS_SIZE;
    fr->white_v = 2.0f / (f32)FONT_ATLAS_SIZE;

    u32 px = WHITE_PATCH + 1;
    u32 py = 1;
    u32 row_height = 0;

    for (u32 ri = 0; ri < FONT_RANGE_COUNT; ri++) {
        for (u32 cp = FONT_RANGES[ri].first; cp <= FONT_RANGES[ri].last; cp++) {
            if (fr->glyph_count >= FONT_MAX_GLYPHS) break;

            int advance, lsb;
            stbtt_GetCodepointHMetrics(&fi, (int)cp, &advance, &lsb);

            int x0, y0, x1, y1;
            stbtt_GetCodepointBitmapBox(&fi, (int)cp, scale, scale, &x0, &y0, &x1, &y1);

            int gw = x1 - x0;
            int gh = y1 - y0;

            if (px + (u32)gw + 1 >= FONT_ATLAS_SIZE) {
                px = 1;
                py += row_height + 1;
                row_height = 0;
            }
            if (py + (u32)gh + 1 >= FONT_ATLAS_SIZE) {
                LOG_WARN("Font: atlas overflow at codepoint U+%04X", cp);
                break;
            }

            if (gw > 0 && gh > 0) {
                stbtt_MakeCodepointBitmap(&fi, atlas + py * FONT_ATLAS_SIZE + px,
                    gw, gh, FONT_ATLAS_SIZE, scale, scale, (int)cp);
            }

            u32 gi = fr->glyph_count++;
            fr->glyphs[gi].codepoint = cp;
            fr->glyphs[gi].advance = (f32)advance * scale;
            fr->glyphs[gi].x_off = (f32)x0;
            fr->glyphs[gi].y_off = (f32)y0;
            fr->glyphs[gi].width = (f32)gw;
            fr->glyphs[gi].height = (f32)gh;
            fr->glyphs[gi].uv.x0 = (f32)px / (f32)FONT_ATLAS_SIZE;
            fr->glyphs[gi].uv.y0 = (f32)py / (f32)FONT_ATLAS_SIZE;
            fr->glyphs[gi].uv.x1 = (f32)(px + gw) / (f32)FONT_ATLAS_SIZE;
            fr->glyphs[gi].uv.y1 = (f32)(py + gh) / (f32)FONT_ATLAS_SIZE;
            if (cp < FONT_CPMAP_SIZE) fr->cp_map[cp] = (i16)gi;

            px += (u32)gw + 1;
            if ((u32)gh + 1 > row_height) row_height = (u32)gh + 1;
        }
    }

    free(ttf_buf);

    RHITextureDesc tdesc;
    memset(&tdesc, 0, sizeof(tdesc));
    tdesc.width = FONT_ATLAS_SIZE;
    tdesc.height = FONT_ATLAS_SIZE;
    tdesc.format = RHI_FORMAT_R8G8B8A8_UNORM;
    tdesc.mip_levels = 1;

    u32 atlas_rgba_size = FONT_ATLAS_SIZE * FONT_ATLAS_SIZE * 4;
    u8 *atlas_rgba = malloc(atlas_rgba_size);
    if (!atlas_rgba) { free(atlas); return false; }
    for (u32 i = 0; i < FONT_ATLAS_SIZE * FONT_ATLAS_SIZE; i++) {
        atlas_rgba[i * 4 + 0] = 255;
        atlas_rgba[i * 4 + 1] = 255;
        atlas_rgba[i * 4 + 2] = 255;
        atlas_rgba[i * 4 + 3] = atlas[i];
    }
    free(atlas);
    tdesc.data = atlas_rgba;

    fr->atlas_tex = rhi_texture_create(dev, &tdesc);
    free(atlas_rgba);
    if (!rhi_handle_valid(fr->atlas_tex)) {
        LOG_WARN("Font: atlas texture creation failed");
        return false;
    }

    RHISamplerDesc sdesc;
    memset(&sdesc, 0, sizeof(sdesc));
    sdesc.min_filter = RHI_FILTER_LINEAR;
    sdesc.mag_filter = RHI_FILTER_LINEAR;
    sdesc.wrap_u = RHI_WRAP_CLAMP_TO_EDGE;
    sdesc.wrap_v = RHI_WRAP_CLAMP_TO_EDGE;
    sdesc.wrap_w = RHI_WRAP_CLAMP_TO_EDGE;
    fr->sampler = rhi_sampler_create(dev, &sdesc);
    if (!rhi_handle_valid(fr->sampler)) {
        LOG_WARN("Font: sampler creation failed");
        return false;
    }

    const char *vert_path =
#ifdef ENGINE_VULKAN
        "shaders/font_vk.vert";
#else
        "shaders/font.vert";
#endif
    const char *frag_path =
#ifdef ENGINE_VULKAN
        "shaders/font_vk.frag";
#else
        "shaders/font.frag";
#endif

    usize vs_len = 0, fs_len = 0;
    char *vs_src = NULL, *fs_src = NULL;
    FILE *vf = fopen(vert_path, "rb");
    if (vf) {
        fseek(vf, 0, SEEK_END); vs_len = (usize)ftell(vf); fseek(vf, 0, SEEK_SET);
        vs_src = malloc(vs_len + 1);
        if (!vs_src) { fclose(vf); vs_len = 0; }
        else {
            vs_len = fread(vs_src, 1, vs_len, vf);
            vs_src[vs_len] = '\0';
            fclose(vf);
        }
    }
    FILE *ff = fopen(frag_path, "rb");
    if (ff) {
        fseek(ff, 0, SEEK_END); fs_len = (usize)ftell(ff); fseek(ff, 0, SEEK_SET);
        fs_src = malloc(fs_len + 1);
        if (!fs_src) { fclose(ff); fs_len = 0; }
        else {
            fs_len = fread(fs_src, 1, fs_len, ff);
            fs_src[fs_len] = '\0';
            fclose(ff);
        }
    }

    if (!vs_src || !fs_src) {
        LOG_WARN("Font: shaders not found (%s / %s)", vert_path, frag_path);
        free(vs_src); free(fs_src);
        return false;
    }

    RHIShader vs = rhi_shader_create(dev, vs_src, vs_len, false);
    RHIShader fs = rhi_shader_create(dev, fs_src, fs_len, true);
    free(vs_src); free(fs_src);

    if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
        LOG_WARN("Font: shader compile failed");
        if (rhi_handle_valid(vs)) rhi_shader_destroy(dev, vs);
        if (rhi_handle_valid(fs)) rhi_shader_destroy(dev, fs);
        return false;
    }

    RHIPipelineDesc pdesc;
    memset(&pdesc, 0, sizeof(pdesc));
    pdesc.vert = vs;
    pdesc.frag = fs;
    pdesc.vertex_stride = 32;
    pdesc.uses_textures = true;
    pdesc.depth_write_disable = true;
    pdesc.disable_culling = true;
    pdesc.alpha_blend = true;
    pdesc.font_vertex = true;
    fr->pipeline = rhi_pipeline_create(dev, &pdesc);
    rhi_shader_destroy(dev, vs);
    rhi_shader_destroy(dev, fs);

    if (!rhi_handle_valid(fr->pipeline)) {
        LOG_WARN("Font: pipeline creation failed");
        return false;
    }

    fr->quad_capacity = 4096;
    fr->quad_data = malloc(fr->quad_capacity * 6 * sizeof(FontVertex));
    if (!fr->quad_data) {
        LOG_WARN("Font: quad data allocation failed");
        return false;
    }
    fr->quad_count = 0;

    RHIBufferDesc bdesc;
    memset(&bdesc, 0, sizeof(bdesc));
    bdesc.usage = RHI_BUFFER_USAGE_VERTEX;
    bdesc.size = fr->quad_capacity * 6 * sizeof(FontVertex);
    fr->vbo = rhi_buffer_create(dev, &bdesc);
    if (!rhi_handle_valid(fr->vbo)) {
        LOG_WARN("Font: VBO creation failed");
        return false;
    }

    LOG_INFO("Font: initialized (%.0fpx, atlas %ux%u, %u glyphs)", font_size,
        FONT_ATLAS_SIZE, FONT_ATLAS_SIZE, fr->glyph_count);
    return true;
}

void font_renderer_shutdown(FontRenderer *fr) {
    if (!fr->device) return;
    if (rhi_handle_valid(fr->vbo)) rhi_buffer_destroy(fr->device, fr->vbo);
    if (rhi_handle_valid(fr->sampler)) rhi_sampler_destroy(fr->device, fr->sampler);
    if (rhi_handle_valid(fr->atlas_tex)) rhi_texture_destroy(fr->device, fr->atlas_tex);
    if (rhi_handle_valid(fr->pipeline)) rhi_pipeline_destroy(fr->device, fr->pipeline);
    free(fr->quad_data);
    memset(fr, 0, sizeof(*fr));
}

void font_renderer_begin(FontRenderer *fr) {
    fr->quad_count = 0;
}

void font_renderer_draw(FontRenderer *fr, const char *text, f32 x, f32 y,
                         f32 screen_w, f32 screen_h, f32 r, f32 g, f32 b, f32 a) {
    (void)screen_w;
    f32 cursor_x = x;
    f32 cursor_y = y + fr->ascent;
    f32 inv_sh = 2.0f / screen_h;
    f32 inv_sw = 2.0f / screen_w;

    const char *s = text;
    while (*s) {
        u32 cp;
        s += utf8_decode(s, &cp);
        if (cp == '\n') {
            cursor_x = x;
            cursor_y += fr->ascent - fr->descent + fr->line_gap;
            continue;
        }

        const GlyphInfo *gi = font_lookup_glyph(fr, cp);
        if (!gi) continue;
        if (gi->width <= 0 || gi->height <= 0) {
            cursor_x += gi->advance;
            continue;
        }

        f32 qx = cursor_x + gi->x_off;
        f32 qy = cursor_y + gi->y_off;
        f32 qw = gi->width;
        f32 qh = gi->height;

        f32 x0 = qx * inv_sw - 1.0f;
        f32 y0 = 1.0f - qy * inv_sh;
        f32 x1 = (qx + qw) * inv_sw - 1.0f;
        f32 y1 = 1.0f - (qy + qh) * inv_sh;

        if (fr->quad_count >= fr->quad_capacity) break;
        usize base = (usize)fr->quad_count * 6 * sizeof(FontVertex);
        FontVertex *dst = (FontVertex *)(fr->quad_data + base);
        dst[0] = (FontVertex){x0, y0, gi->uv.x0, gi->uv.y0, r, g, b, a};
        dst[1] = (FontVertex){x1, y0, gi->uv.x1, gi->uv.y0, r, g, b, a};
        dst[2] = (FontVertex){x0, y1, gi->uv.x0, gi->uv.y1, r, g, b, a};
        dst[3] = (FontVertex){x1, y0, gi->uv.x1, gi->uv.y0, r, g, b, a};
        dst[4] = (FontVertex){x1, y1, gi->uv.x1, gi->uv.y1, r, g, b, a};
        dst[5] = (FontVertex){x0, y1, gi->uv.x0, gi->uv.y1, r, g, b, a};
        fr->quad_count++;
        cursor_x += gi->advance;
    }
}

void font_renderer_draw_rect(FontRenderer *fr, f32 x, f32 y, f32 w, f32 h,
                             f32 screen_w, f32 screen_h, f32 r, f32 g, f32 b, f32 a) {
    if (w <= 0.0f || h <= 0.0f) return;
    if (fr->quad_count >= fr->quad_capacity) return;

    f32 inv_sw = 2.0f / screen_w;
    f32 inv_sh = 2.0f / screen_h;
    f32 x0 = x * inv_sw - 1.0f;
    f32 y0 = 1.0f - y * inv_sh;
    f32 x1 = (x + w) * inv_sw - 1.0f;
    f32 y1 = 1.0f - (y + h) * inv_sh;

    f32 u = fr->white_u, vv = fr->white_v;

    usize base = (usize)fr->quad_count * 6 * sizeof(FontVertex);
    FontVertex *dst = (FontVertex *)(fr->quad_data + base);
    dst[0] = (FontVertex){x0, y0, u, vv, r, g, b, a};
    dst[1] = (FontVertex){x1, y0, u, vv, r, g, b, a};
    dst[2] = (FontVertex){x0, y1, u, vv, r, g, b, a};
    dst[3] = (FontVertex){x1, y0, u, vv, r, g, b, a};
    dst[4] = (FontVertex){x1, y1, u, vv, r, g, b, a};
    dst[5] = (FontVertex){x0, y1, u, vv, r, g, b, a};
    fr->quad_count++;
}

f32 font_renderer_text_width(const FontRenderer *fr, const char *text) {
    f32 w = 0.0f, line_w = 0.0f;
    const char *s = text;
    while (*s) {
        u32 cp;
        s += utf8_decode(s, &cp);
        if (cp == '\n') {
            if (line_w > w) w = line_w;
            line_w = 0.0f;
            continue;
        }
        const GlyphInfo *gi = font_lookup_glyph(fr, cp);
        if (gi) line_w += gi->advance;
    }
    return line_w > w ? line_w : w;
}

f32 font_renderer_line_height(const FontRenderer *fr) {
    return fr->ascent - fr->descent + fr->line_gap;
}

void font_renderer_end(FontRenderer *fr, RHICmdBuffer *cmd, f32 screen_w, f32 screen_h) {
    (void)screen_w; (void)screen_h;
    if (fr->quad_count == 0) return;

    usize data_size = (usize)fr->quad_count * 6 * sizeof(FontVertex);
    rhi_buffer_update(fr->device, fr->vbo, fr->quad_data, data_size);

    rhi_cmd_bind_pipeline(cmd, fr->pipeline);
    rhi_cmd_bind_texture(cmd, fr->atlas_tex, fr->sampler, 0);
    rhi_cmd_set_uniform_vec4(cmd, 0, 1.0f, 1.0f, 1.0f, 1.0f);
    rhi_cmd_bind_vertex_buffer(cmd, fr->vbo, 0);
    rhi_cmd_draw(cmd, fr->quad_count * 6, 1);
}
