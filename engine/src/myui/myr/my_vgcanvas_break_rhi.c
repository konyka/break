#include "myr/my_vgcanvas_break_rhi.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "core/shader_io.h"
#include "myr/my_text_layout.h"
#include "myr/my_vggeometry.h"
#include "myr/my_vgcanvas_break_rhi_internal.h"

#define BREAK_RHI_ATLAS_SIZE 1024
#define BREAK_RHI_MAX_IMAGES 64
#define BREAK_RHI_INITIAL_VERT_CAP 16384

typedef struct {
  f32 x, y, u, v, r, g, b, a;
} break_ui_vertex_t;

typedef struct {
  my_color_t fill_color;
  my_color_t stroke_color;
  float line_width;
  float tx, ty, scale;
  my_rect_t clip;
  my_font_t *font;
  int32_t font_size;
  my_line_cap_t line_cap;
  my_line_join_t line_join;
  my_scale_filter_t scale_filter;
} break_rhi_state_t;

typedef struct {
  my_font_t *font;
  uint32_t codepoint;
  int32_t size;
  u32 x, y, w, h;
} break_rhi_glyph_t;

typedef struct {
  RHITexture texture;
  const u8 *pixels;
  int32_t w, h;
} break_rhi_image_t;

typedef struct {
  RHITexture texture;
  RHISampler sampler;
  u32 offset;
  u32 count;
} break_rhi_image_batch_t;

typedef struct my_vgcanvas_break_rhi_t {
  my_vgcanvas_t base;
  const my_allocator_t *allocator;
  RHIDevice *device;
  RHICmdBuffer *cmd;
  RHIOffscreenFBO *target;
  int pending_antialias_level;
  bool frame_active;
  u32 width, height;

  break_rhi_state_t state;
  break_rhi_state_t *stack;
  size_t stack_count, stack_cap;

  my_vggeometry_t geo;

  break_ui_vertex_t *solid_verts;
  size_t solid_count, solid_cap;
  RHIBuffer solid_vbo[2];
  size_t solid_vbo_cap;

  break_ui_vertex_t *image_verts;
  size_t image_count, image_cap;
  RHIBuffer image_vbo[2];
  size_t image_vbo_cap;
  break_rhi_image_batch_t image_batches[BREAK_RHI_MAX_IMAGES];
  size_t image_batch_count;

  RHIPipeline font_pipeline;
  RHIPipeline image_pipeline;
  RHITexture atlas_texture;
  RHISampler sampler;
  RHISampler nearest_sampler;
  u8 *atlas_pixels;
  u32 atlas_x, atlas_y, atlas_row_h;
  bool atlas_dirty;

  break_rhi_glyph_t *glyphs;
  size_t glyph_count, glyph_cap;

  break_rhi_image_t images[BREAK_RHI_MAX_IMAGES];
  size_t image_cache_count;
} my_vgcanvas_break_rhi_t;

static const float BREAK_RHI_WHITE_UV =
    0.5f / (float)BREAK_RHI_ATLAS_SIZE;

static my_vgcanvas_break_rhi_t *rhi_canvas(my_vgcanvas_t *vg) {
  return (my_vgcanvas_break_rhi_t *)vg;
}

u32 my_vgcanvas_break_rhi_sample_count_for_aa_level(int level) {
  return my_vgcanvas_break_rhi_sample_count_for_aa_level_internal(level);
}

static my_ret_t grow_bytes(const my_allocator_t *allocator, void **array,
                           size_t *cap, size_t need, size_t elem_size) {
  void *p;
  size_t next;
  if (need <= *cap) {
    return MY_RET_OK;
  }
  next = *cap > 0 ? *cap : BREAK_RHI_INITIAL_VERT_CAP;
  while (next < need) {
    next *= 2;
  }
  p = my_mem_realloc(allocator, *array, next * elem_size);
  if (p == NULL) {
    return MY_RET_OOM;
  }
  *array = p;
  *cap = next;
  return MY_RET_OK;
}

static my_rect_t state_device_rect(const break_rhi_state_t *state,
                                   const my_rectf_t *rect) {
  return my_rect_init(
      (int32_t)floorf((rect->x + state->tx) * state->scale),
      (int32_t)floorf((rect->y + state->ty) * state->scale),
      (int32_t)ceilf((rect->x + state->tx + rect->w) * state->scale) -
          (int32_t)floorf((rect->x + state->tx) * state->scale),
      (int32_t)ceilf((rect->y + state->ty + rect->h) * state->scale) -
          (int32_t)floorf((rect->y + state->ty) * state->scale));
}

static void ndc_xy(my_vgcanvas_break_rhi_t *c, float x, float y, float *nx,
                   float *ny) {
  *nx = 2.0f * x / (float)c->width - 1.0f;
  *ny = 1.0f - 2.0f * y / (float)c->height;
}

static my_ret_t emit_solid_vertex(my_vgcanvas_break_rhi_t *c, float x, float y,
                                  float u, float v, my_color_t color) {
  break_ui_vertex_t *dst;
  float nx, ny;
  my_ret_t ret = grow_bytes(c->allocator, (void **)&c->solid_verts,
                            &c->solid_cap, c->solid_count + 1,
                            sizeof(break_ui_vertex_t));
  if (ret != MY_RET_OK) {
    return ret;
  }
  ndc_xy(c, x, y, &nx, &ny);
  dst = &c->solid_verts[c->solid_count++];
  dst->x = nx;
  dst->y = ny;
  dst->u = u;
  dst->v = v;
  dst->r = (f32)color.r / 255.0f;
  dst->g = (f32)color.g / 255.0f;
  dst->b = (f32)color.b / 255.0f;
  dst->a = (f32)color.a / 255.0f;
  return MY_RET_OK;
}

static my_ret_t emit_solid_triangle(my_vgcanvas_break_rhi_t *c, float x0,
                                    float y0, float x1, float y1, float x2,
                                    float y2, my_color_t color) {
  my_ret_t ret;
  ret = emit_solid_vertex(c, x0, y0, BREAK_RHI_WHITE_UV, BREAK_RHI_WHITE_UV,
                          color);
  if (ret != MY_RET_OK) return ret;
  ret = emit_solid_vertex(c, x1, y1, BREAK_RHI_WHITE_UV, BREAK_RHI_WHITE_UV,
                          color);
  if (ret != MY_RET_OK) return ret;
  return emit_solid_vertex(c, x2, y2, BREAK_RHI_WHITE_UV, BREAK_RHI_WHITE_UV,
                           color);
}

static my_ret_t emit_image_vertex(my_vgcanvas_break_rhi_t *c, float x, float y,
                                  float u, float v) {
  break_ui_vertex_t *dst;
  float nx, ny;
  my_ret_t ret = grow_bytes(c->allocator, (void **)&c->image_verts,
                            &c->image_cap, c->image_count + 1,
                            sizeof(break_ui_vertex_t));
  if (ret != MY_RET_OK) {
    return ret;
  }
  ndc_xy(c, x, y, &nx, &ny);
  dst = &c->image_verts[c->image_count++];
  dst->x = nx;
  dst->y = ny;
  dst->u = u;
  dst->v = v;
  dst->r = 1.0f;
  dst->g = 1.0f;
  dst->b = 1.0f;
  dst->a = 1.0f;
  return MY_RET_OK;
}

static my_ret_t emit_image_triangle(my_vgcanvas_break_rhi_t *c, float x0,
                                    float y0, float u0, float v0, float x1,
                                    float y1, float u1, float v1, float x2,
                                    float y2, float u2, float v2) {
  my_ret_t ret = emit_image_vertex(c, x0, y0, u0, v0);
  if (ret != MY_RET_OK) return ret;
  ret = emit_image_vertex(c, x1, y1, u1, v1);
  if (ret != MY_RET_OK) return ret;
  return emit_image_vertex(c, x2, y2, u2, v2);
}

static my_ret_t emit_geometry(my_vgcanvas_break_rhi_t *c, my_color_t color) {
  size_t i;
  for (i = 0; i + 2 < c->geo.vert_count / 2; i += 3) {
    my_ret_t ret = emit_solid_triangle(
        c, c->geo.verts[i * 2], c->geo.verts[i * 2 + 1],
        c->geo.verts[(i + 1) * 2], c->geo.verts[(i + 1) * 2 + 1],
        c->geo.verts[(i + 2) * 2], c->geo.verts[(i + 2) * 2 + 1], color);
    if (ret != MY_RET_OK) {
      return ret;
    }
  }
  return MY_RET_OK;
}

static my_ret_t emit_device_rect(my_vgcanvas_break_rhi_t *c, my_rect_t r,
                                 my_color_t color) {
  my_vggeometry_set_transform(&c->geo, 0.0f, 0.0f, 1.0f);
  my_vggeometry_begin_verts(&c->geo);
  my_vggeometry_rect(&c->geo, (float)r.x, (float)r.y, (float)(r.x + r.w),
                     (float)(r.y + r.h));
  return emit_geometry(c, color);
}

static my_ret_t emit_device_stroke_rect(my_vgcanvas_break_rhi_t *c, my_rect_t r,
                                        float line_width, my_color_t color) {
  my_vggeometry_set_transform(&c->geo, 0.0f, 0.0f, 1.0f);
  my_vggeometry_begin_verts(&c->geo);
  my_vggeometry_stroke_rect(&c->geo, (float)r.x, (float)r.y, (float)r.w,
                            (float)r.h, line_width);
  return emit_geometry(c, color);
}

static my_ret_t emit_device_rounded_rect(my_vgcanvas_break_rhi_t *c,
                                         my_rect_t r, float radius,
                                         my_color_t color) {
  my_vggeometry_set_transform(&c->geo, 0.0f, 0.0f, 1.0f);
  my_vggeometry_begin_verts(&c->geo);
  my_vggeometry_fill_rounded_rect(&c->geo, (float)r.x, (float)r.y, (float)r.w,
                                  (float)r.h, radius);
  return emit_geometry(c, color);
}

static my_ret_t ensure_vbo(my_vgcanvas_break_rhi_t *c, RHIBuffer vbo[2],
                           size_t *vbo_cap, size_t needed_verts) {
  if (needed_verts <= *vbo_cap) {
    return MY_RET_OK;
  }
  if (rhi_handle_valid(vbo[0])) rhi_buffer_destroy(c->device, vbo[0]);
  if (rhi_handle_valid(vbo[1])) rhi_buffer_destroy(c->device, vbo[1]);
  vbo[0] = RHI_HANDLE_NULL;
  vbo[1] = RHI_HANDLE_NULL;

  RHIBufferDesc desc;
  memset(&desc, 0, sizeof(desc));
  desc.usage = RHI_BUFFER_USAGE_VERTEX;
  desc.size = needed_verts * sizeof(break_ui_vertex_t);
  vbo[0] = rhi_buffer_create(c->device, &desc);
  vbo[1] = rhi_buffer_create(c->device, &desc);
  if (!rhi_handle_valid(vbo[0]) || !rhi_handle_valid(vbo[1])) {
    return MY_RET_FAIL;
  }
  *vbo_cap = needed_verts;
  return MY_RET_OK;
}

static my_ret_t ensure_glyph_cap(my_vgcanvas_break_rhi_t *c, size_t need) {
  return grow_bytes(c->allocator, (void **)&c->glyphs, &c->glyph_cap, need,
                    sizeof(break_rhi_glyph_t));
}

static void atlas_copy_glyph(my_vgcanvas_break_rhi_t *c, u32 x, u32 y,
                             const my_glyph_t *g) {
  u32 row, col;
  for (row = 0; row < (u32)g->h; row++) {
    u8 *dst = c->atlas_pixels +
              ((size_t)(y + row) * BREAK_RHI_ATLAS_SIZE + x) * 4u;
    const uint8_t *src = g->bitmap + (size_t)row * (size_t)g->w;
    for (col = 0; col < (u32)g->w; col++) {
      dst[col * 4 + 0] = 255;
      dst[col * 4 + 1] = 255;
      dst[col * 4 + 2] = 255;
      dst[col * 4 + 3] = src[col];
    }
  }
  c->atlas_dirty = true;
}

static bool atlas_alloc(my_vgcanvas_break_rhi_t *c, u32 w, u32 h, u32 *out_x,
                        u32 *out_y) {
  u32 pw = w + 2u;
  u32 ph = h + 2u;
  if (pw > BREAK_RHI_ATLAS_SIZE || ph > BREAK_RHI_ATLAS_SIZE) {
    return false;
  }
  if (c->atlas_x + pw > BREAK_RHI_ATLAS_SIZE) {
    c->atlas_x = 1;
    c->atlas_y += c->atlas_row_h + 1u;
    c->atlas_row_h = 0;
  }
  if (c->atlas_y + ph > BREAK_RHI_ATLAS_SIZE) {
    return false;
  }
  *out_x = c->atlas_x + 1u;
  *out_y = c->atlas_y + 1u;
  c->atlas_x += pw;
  if (ph > c->atlas_row_h) {
    c->atlas_row_h = ph;
  }
  return true;
}

static const break_rhi_glyph_t *glyph_slot(my_vgcanvas_break_rhi_t *c,
                                           my_font_t *font, uint32_t cp,
                                           int32_t size, const my_glyph_t *g) {
  size_t i;
  u32 x, y;
  for (i = 0; i < c->glyph_count; i++) {
    if (c->glyphs[i].font == font && c->glyphs[i].codepoint == cp &&
        c->glyphs[i].size == size) {
      return &c->glyphs[i];
    }
  }
  if (!atlas_alloc(c, (u32)g->w, (u32)g->h, &x, &y)) {
    return NULL;
  }
  if (ensure_glyph_cap(c, c->glyph_count + 1) != MY_RET_OK) {
    return NULL;
  }
  i = c->glyph_count++;
  c->glyphs[i].font = font;
  c->glyphs[i].codepoint = cp;
  c->glyphs[i].size = size;
  c->glyphs[i].x = x;
  c->glyphs[i].y = y;
  c->glyphs[i].w = (u32)g->w;
  c->glyphs[i].h = (u32)g->h;
  atlas_copy_glyph(c, x, y, g);
  return &c->glyphs[i];
}

static void draw_codepoint(my_vgcanvas_break_rhi_t *c, uint32_t cp,
                           float *pen_x, float top, int32_t ascent) {
  my_glyph_t g;
  const break_rhi_glyph_t *slot;
  float gx, gy;
  float u0, v0, u1, v1;
  int32_t dev_font_size =
      (int32_t)((float)c->state.font_size * c->state.scale + 0.5f);
  if (dev_font_size < 1) dev_font_size = 1;
  if (my_font_get_glyph(c->state.font, cp, dev_font_size, &g) != MY_RET_OK ||
      g.w <= 0 || g.h <= 0 || g.bitmap == NULL) {
    if (g.advance > 0) {
      *pen_x += (float)g.advance;
    }
    return;
  }
  slot = glyph_slot(c, c->state.font, cp, dev_font_size, &g);
  if (slot == NULL) {
    *pen_x += (float)g.advance;
    return;
  }
  gx = *pen_x + (float)g.bearing_x;
  gy = top + (float)(ascent - g.bearing_y);
  u0 = ((float)slot->x + 0.5f) / (float)BREAK_RHI_ATLAS_SIZE;
  v0 = ((float)slot->y + 0.5f) / (float)BREAK_RHI_ATLAS_SIZE;
  u1 = ((float)(slot->x + slot->w) - 0.5f) /
       (float)BREAK_RHI_ATLAS_SIZE;
  v1 = ((float)(slot->y + slot->h) - 0.5f) /
       (float)BREAK_RHI_ATLAS_SIZE;
  {
    float x0 = gx, y0 = gy;
    float x1 = gx + (float)g.w, y1 = gy + (float)g.h;
    (void)emit_solid_vertex(c, x0, y0, u0, v0, c->state.fill_color);
    (void)emit_solid_vertex(c, x1, y0, u1, v0, c->state.fill_color);
    (void)emit_solid_vertex(c, x0, y1, u0, v1, c->state.fill_color);
    (void)emit_solid_vertex(c, x1, y0, u1, v0, c->state.fill_color);
    (void)emit_solid_vertex(c, x1, y1, u1, v1, c->state.fill_color);
    (void)emit_solid_vertex(c, x0, y1, u0, v1, c->state.fill_color);
  }
  *pen_x += (float)g.advance;
}

static my_ret_t rhi_draw_text(my_vgcanvas_t *vg, const char *text, float x,
                              float y) {
  my_vgcanvas_break_rhi_t *c = rhi_canvas(vg);
  int32_t ascent;
  float pen_x, top;
  const char *p = text;
  if (text == NULL) return MY_RET_INVALID_PARAMS;
  if (c->state.font == NULL || c->state.font_size <= 0) {
    return MY_RET_NOT_SUPPORTED;
  }
  {
    int32_t dev_font_size =
        (int32_t)((float)c->state.font_size * c->state.scale + 0.5f);
    if (dev_font_size < 1) dev_font_size = 1;
    ascent = my_font_ascent(c->state.font, dev_font_size);
  }
  pen_x = (x + c->state.tx) * c->state.scale;
  top = (y + c->state.ty) * c->state.scale;

  if (!my_text_layout_may_need_bidi(text)) {
    while (*p != '\0') {
      draw_codepoint(c, my_utf8_next(&p), &pen_x, top, ascent);
    }
  } else {
    my_text_layout_t *layout = my_text_layout_process(c->allocator, text);
    size_t i;
    if (layout == NULL) {
      return MY_RET_OOM;
    }
    for (i = 0; i < layout->len; i++) {
      draw_codepoint(c, layout->visual_cps[i], &pen_x, top, ascent);
    }
    my_text_layout_destroy(layout);
  }
  return MY_RET_OK;
}

static my_ret_t rhi_measure_text(my_vgcanvas_t *vg, const char *text,
                                 int32_t *w, int32_t *h) {
  my_vgcanvas_break_rhi_t *c = rhi_canvas(vg);
  my_ret_t ret;
  if (c->state.font == NULL || c->state.font_size <= 0) {
    return MY_RET_NOT_SUPPORTED;
  }
  if (text != NULL && my_text_layout_may_need_bidi(text)) {
    my_text_layout_t *layout = my_text_layout_process(c->allocator, text);
    if (layout == NULL) return MY_RET_OOM;
    ret = my_font_measure(c->state.font, layout->visual_utf8,
                          c->state.font_size, w, h);
    my_text_layout_destroy(layout);
  } else {
    ret = my_font_measure(c->state.font, text, c->state.font_size, w, h);
  }
  if (ret == MY_RET_OK && c->state.scale != 1.0f) {
    if (w != NULL) *w = (int32_t)((float)*w / c->state.scale + 0.5f);
    if (h != NULL) *h = (int32_t)((float)*h / c->state.scale + 0.5f);
  }
  return ret;
}

static RHITexture image_texture(my_vgcanvas_break_rhi_t *c, const u8 *rgba,
                                int32_t w, int32_t h) {
  size_t i;
  for (i = 0; i < c->image_cache_count; i++) {
    if (c->images[i].pixels == rgba && c->images[i].w == w &&
        c->images[i].h == h) {
      return c->images[i].texture;
    }
  }
  if (c->image_cache_count >= BREAK_RHI_MAX_IMAGES) {
    return RHI_HANDLE_NULL;
  }
  RHITextureDesc desc;
  memset(&desc, 0, sizeof(desc));
  desc.width = (u32)w;
  desc.height = (u32)h;
  desc.format = RHI_FORMAT_R8G8B8A8_UNORM;
  desc.mip_levels = 1;
  desc.data = rgba;
  c->images[c->image_cache_count].texture = rhi_texture_create(c->device, &desc);
  c->images[c->image_cache_count].pixels = rgba;
  c->images[c->image_cache_count].w = w;
  c->images[c->image_cache_count].h = h;
  return c->images[c->image_cache_count++].texture;
}

static my_ret_t rhi_draw_image(my_vgcanvas_t *vg, const uint8_t *rgba,
                               int32_t w, int32_t h, const my_rectf_t *dst,
                               const my_color_t *bg) {
  my_vgcanvas_break_rhi_t *c = rhi_canvas(vg);
  RHITexture tex;
  RHISampler image_sampler;
  my_rect_t dr;
  float x0, y0, x1, y1;
  if (rgba == NULL || dst == NULL || w <= 0 || h <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (bg != NULL && bg->a > 0) {
    dr = state_device_rect(&c->state, dst);
    my_rect_t clipped;
    if (my_rect_intersect(&dr, &c->state.clip, &clipped)) {
      (void)emit_device_rect(c, clipped, *bg);
    }
  }
  tex = image_texture(c, rgba, w, h);
  if (!rhi_handle_valid(tex)) {
    return MY_RET_OOM;
  }
  image_sampler = c->state.scale_filter == MY_SCALE_FILTER_BILINEAR
                      ? c->sampler
                      : c->nearest_sampler;
  x0 = (dst->x + c->state.tx) * c->state.scale;
  y0 = (dst->y + c->state.ty) * c->state.scale;
  x1 = x0 + dst->w * c->state.scale;
  y1 = y0 + dst->h * c->state.scale;
  if (c->image_batch_count == 0 ||
      c->image_batches[c->image_batch_count - 1].texture.index != tex.index ||
      c->image_batches[c->image_batch_count - 1].texture.generation !=
          tex.generation ||
      c->image_batches[c->image_batch_count - 1].sampler.index !=
          image_sampler.index ||
      c->image_batches[c->image_batch_count - 1].sampler.generation !=
          image_sampler.generation) {
    if (c->image_batch_count >= BREAK_RHI_MAX_IMAGES) {
      return MY_RET_OOM;
    }
    c->image_batches[c->image_batch_count].texture = tex;
    c->image_batches[c->image_batch_count].sampler = image_sampler;
    c->image_batches[c->image_batch_count].offset = (u32)c->image_count;
    c->image_batches[c->image_batch_count].count = 0;
    c->image_batch_count++;
  }
  {
    my_ret_t ret;
    ret = emit_image_triangle(c, x0, y0, 0.0f, 0.0f, x1, y0, 1.0f, 0.0f,
                              x0, y1, 0.0f, 1.0f);
    if (ret != MY_RET_OK) return ret;
    ret = emit_image_triangle(c, x1, y0, 1.0f, 0.0f, x1, y1, 1.0f, 1.0f,
                              x0, y1, 0.0f, 1.0f);
    if (ret != MY_RET_OK) return ret;
  }
  c->image_batches[c->image_batch_count - 1].count += 6u;
  return MY_RET_OK;
}

static my_ret_t rhi_begin_frame(my_vgcanvas_t *vg, const my_rect_t *dirty) {
  my_vgcanvas_break_rhi_t *c = rhi_canvas(vg);
  (void)dirty;
  c->frame_active = true;
  c->solid_count = 0;
  c->image_count = 0;
  c->image_batch_count = 0;
  return MY_RET_OK;
}

static my_ret_t rhi_end_frame(my_vgcanvas_t *vg) {
  my_vgcanvas_break_rhi_t *c = rhi_canvas(vg);
  u32 slot;
  size_t i;
  c->frame_active = false;
  if (c->cmd == NULL || (c->solid_count == 0 && c->image_count == 0)) {
    return MY_RET_OK;
  }
  if (c->atlas_dirty) {
    rhi_texture_upload_mip(c->device, c->atlas_texture, 0,
                           BREAK_RHI_ATLAS_SIZE, BREAK_RHI_ATLAS_SIZE,
                           c->atlas_pixels,
                           BREAK_RHI_ATLAS_SIZE * BREAK_RHI_ATLAS_SIZE * 4u);
    c->atlas_dirty = false;
  }
  slot = rhi_frame_index(c->device);
  if (c->solid_count > 0) {
    if (ensure_vbo(c, c->solid_vbo, &c->solid_vbo_cap, c->solid_count) !=
        MY_RET_OK) {
      return MY_RET_FAIL;
    }
    rhi_buffer_update(c->device, c->solid_vbo[slot], c->solid_verts,
                      c->solid_count * sizeof(break_ui_vertex_t));
    rhi_cmd_bind_pipeline(c->cmd, c->font_pipeline);
    rhi_cmd_bind_texture(c->cmd, c->atlas_texture, c->sampler, 0);
    rhi_cmd_bind_vertex_buffer(c->cmd, c->solid_vbo[slot], 0);
    rhi_cmd_draw(c->cmd, (u32)c->solid_count, 1);
  }
  if (c->image_count > 0) {
    if (ensure_vbo(c, c->image_vbo, &c->image_vbo_cap, c->image_count) !=
        MY_RET_OK) {
      return MY_RET_FAIL;
    }
    rhi_buffer_update(c->device, c->image_vbo[slot], c->image_verts,
                      c->image_count * sizeof(break_ui_vertex_t));
    rhi_cmd_bind_pipeline(c->cmd, c->image_pipeline);
    rhi_cmd_bind_vertex_buffer(c->cmd, c->image_vbo[slot], 0);
    for (i = 0; i < c->image_batch_count; i++) {
      rhi_cmd_bind_texture(c->cmd, c->image_batches[i].texture,
                           c->image_batches[i].sampler, 0);
      rhi_cmd_draw_base(c->cmd, c->image_batches[i].count, 1,
                        c->image_batches[i].offset);
    }
  }
  return MY_RET_OK;
}

static my_ret_t rhi_save(my_vgcanvas_t *vg) {
  my_vgcanvas_break_rhi_t *c = rhi_canvas(vg);
  my_ret_t ret = grow_bytes(c->allocator, (void **)&c->stack, &c->stack_cap,
                            c->stack_count + 1, sizeof(break_rhi_state_t));
  if (ret != MY_RET_OK) return ret;
  c->stack[c->stack_count++] = c->state;
  return MY_RET_OK;
}

static my_ret_t rhi_restore(my_vgcanvas_t *vg) {
  my_vgcanvas_break_rhi_t *c = rhi_canvas(vg);
  if (c->stack_count == 0) return MY_RET_FAIL;
  c->state = c->stack[--c->stack_count];
  return MY_RET_OK;
}

static my_ret_t rhi_translate(my_vgcanvas_t *vg, float dx, float dy) {
  my_vgcanvas_break_rhi_t *c = rhi_canvas(vg);
  c->state.tx += dx;
  c->state.ty += dy;
  return MY_RET_OK;
}

static my_ret_t rhi_clip_rect(my_vgcanvas_t *vg, const my_rectf_t *rect) {
  my_vgcanvas_break_rhi_t *c = rhi_canvas(vg);
  my_rect_t dev, clipped;
  if (rect == NULL) return MY_RET_INVALID_PARAMS;
  dev = state_device_rect(&c->state, rect);
  if (my_rect_intersect(&c->state.clip, &dev, &clipped)) {
    c->state.clip = clipped;
  } else {
    c->state.clip = my_rect_init(0, 0, 0, 0);
  }
  return MY_RET_OK;
}

static my_ret_t rhi_reset_clip(my_vgcanvas_t *vg, const my_rectf_t *rect) {
  my_vgcanvas_break_rhi_t *c = rhi_canvas(vg);
  if (rect == NULL) return MY_RET_INVALID_PARAMS;
  c->state.clip = state_device_rect(&c->state, rect);
  return MY_RET_OK;
}

static my_ret_t rhi_set_scale_vtable(my_vgcanvas_t *vg, float scale) {
  my_vgcanvas_break_rhi_t *c = rhi_canvas(vg);
  if (c == NULL || scale <= 0.0f) return MY_RET_INVALID_PARAMS;
  c->state.scale = scale;
  return MY_RET_OK;
}

static my_ret_t rhi_set_antialias_level_vtable(my_vgcanvas_t *vg, int level) {
  my_vgcanvas_break_rhi_t *c = rhi_canvas(vg);
  if (c == NULL || !my_vgcanvas_break_rhi_aa_level_is_supported(level)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (c->target == NULL ||
      (level == 2 &&
       (c->base.capabilities.antialias_levels &
        MY_VGCANVAS_AA_LEVEL_BIT(2)) == 0u)) {
    return MY_RET_NOT_SUPPORTED;
  }
  if (c->target->sample_count ==
      my_vgcanvas_break_rhi_sample_count_for_aa_level_internal(level)) {
    return MY_RET_OK;
  }
  c->pending_antialias_level = level;
  /* Target replacement belongs to BreakUI and must happen before the next
   * render pass, not while a paint callback is recording commands. */
  return MY_RET_PENDING;
}

static my_ret_t rhi_set_scale_filter_vtable(my_vgcanvas_t *vg,
                                            my_scale_filter_t filter) {
  my_vgcanvas_break_rhi_t *c = rhi_canvas(vg);
  if (c == NULL || (filter != MY_SCALE_FILTER_NEAREST &&
                    filter != MY_SCALE_FILTER_BILINEAR)) {
    return MY_RET_INVALID_PARAMS;
  }
  c->state.scale_filter = filter;
  return MY_RET_OK;
}

static my_ret_t rhi_set_fill_color(my_vgcanvas_t *vg, my_color_t color) {
  rhi_canvas(vg)->state.fill_color = color;
  return MY_RET_OK;
}

static my_ret_t rhi_set_stroke_color(my_vgcanvas_t *vg, my_color_t color) {
  rhi_canvas(vg)->state.stroke_color = color;
  return MY_RET_OK;
}

static my_ret_t rhi_set_line_width(my_vgcanvas_t *vg, float width) {
  rhi_canvas(vg)->state.line_width = width;
  return MY_RET_OK;
}

static my_ret_t rhi_fill_rect(my_vgcanvas_t *vg, const my_rectf_t *rect) {
  my_vgcanvas_break_rhi_t *c = rhi_canvas(vg);
  my_rect_t dev, clipped;
  if (rect == NULL) return MY_RET_INVALID_PARAMS;
  dev = state_device_rect(&c->state, rect);
  if (my_rect_intersect(&dev, &c->state.clip, &clipped)) {
    return emit_device_rect(c, clipped, c->state.fill_color);
  }
  return MY_RET_OK;
}

static my_ret_t rhi_stroke_rect(my_vgcanvas_t *vg, const my_rectf_t *rect) {
  my_vgcanvas_break_rhi_t *c = rhi_canvas(vg);
  my_rect_t dev, clipped;
  if (rect == NULL) return MY_RET_INVALID_PARAMS;
  dev = state_device_rect(&c->state, rect);
  if (my_rect_intersect(&dev, &c->state.clip, &clipped)) {
    return emit_device_stroke_rect(c, clipped,
                                   c->state.line_width * c->state.scale,
                                   c->state.stroke_color);
  }
  return MY_RET_OK;
}

static my_ret_t rhi_fill_rounded_rect(my_vgcanvas_t *vg, const my_rectf_t *rect,
                                      float radius) {
  my_vgcanvas_break_rhi_t *c = rhi_canvas(vg);
  my_rect_t dev, clipped;
  if (rect == NULL) return MY_RET_INVALID_PARAMS;
  dev = state_device_rect(&c->state, rect);
  if (my_rect_intersect(&dev, &c->state.clip, &clipped)) {
    return emit_device_rounded_rect(c, clipped, radius * c->state.scale,
                                    c->state.fill_color);
  }
  return MY_RET_OK;
}

static my_ret_t rhi_begin_path(my_vgcanvas_t *vg) {
  return my_vggeometry_begin_path(&rhi_canvas(vg)->geo);
}

static my_ret_t rhi_move_to(my_vgcanvas_t *vg, float x, float y) {
  return my_vggeometry_move_to(&rhi_canvas(vg)->geo, x, y);
}

static my_ret_t rhi_line_to(my_vgcanvas_t *vg, float x, float y) {
  return my_vggeometry_line_to(&rhi_canvas(vg)->geo, x, y);
}

static my_ret_t rhi_close_path(my_vgcanvas_t *vg) {
  return my_vggeometry_close_path(&rhi_canvas(vg)->geo);
}

static my_ret_t rhi_curve_to(my_vgcanvas_t *vg, float cx1, float cy1,
                             float cx2, float cy2, float x, float y) {
  return my_vggeometry_curve_to(&rhi_canvas(vg)->geo, cx1, cy1, cx2, cy2, x, y);
}

static my_ret_t rhi_fill(my_vgcanvas_t *vg) {
  my_vgcanvas_break_rhi_t *c = rhi_canvas(vg);
  my_ret_t ret;
  my_vggeometry_set_transform(&c->geo, c->state.tx, c->state.ty,
                              c->state.scale);
  my_vggeometry_begin_verts(&c->geo);
  ret = my_vggeometry_fill(&c->geo, &c->state.clip);
  if (ret != MY_RET_OK) return ret;
  return emit_geometry(c, c->state.fill_color);
}

static my_ret_t rhi_stroke(my_vgcanvas_t *vg) {
  my_vgcanvas_break_rhi_t *c = rhi_canvas(vg);
  my_vggeometry_set_transform(&c->geo, c->state.tx, c->state.ty,
                              c->state.scale);
  my_vggeometry_begin_verts(&c->geo);
  my_vggeometry_stroke(&c->geo, c->state.line_width * c->state.scale,
                       c->state.line_cap, c->state.line_join);
  return emit_geometry(c, c->state.stroke_color);
}

static my_ret_t rhi_set_line_cap(my_vgcanvas_t *vg, my_line_cap_t cap) {
  rhi_canvas(vg)->state.line_cap = cap;
  return MY_RET_OK;
}

static my_ret_t rhi_set_line_join(my_vgcanvas_t *vg, my_line_join_t join) {
  rhi_canvas(vg)->state.line_join = join;
  return MY_RET_OK;
}

static my_ret_t rhi_set_font(my_vgcanvas_t *vg, my_font_t *font, int32_t size) {
  my_vgcanvas_break_rhi_t *c = rhi_canvas(vg);
  if (font != NULL) c->state.font = font;
  if (size > 0) c->state.font_size = size;
  return MY_RET_OK;
}

static void rhi_destroy(my_vgcanvas_t *vg) {
  my_vgcanvas_break_rhi_t *c = rhi_canvas(vg);
  size_t i;
  if (c == NULL) return;
  if (c->device != NULL) {
    if (rhi_handle_valid(c->solid_vbo[0]))
      rhi_buffer_destroy(c->device, c->solid_vbo[0]);
    if (rhi_handle_valid(c->solid_vbo[1]))
      rhi_buffer_destroy(c->device, c->solid_vbo[1]);
    if (rhi_handle_valid(c->image_vbo[0]))
      rhi_buffer_destroy(c->device, c->image_vbo[0]);
    if (rhi_handle_valid(c->image_vbo[1]))
      rhi_buffer_destroy(c->device, c->image_vbo[1]);
    if (rhi_handle_valid(c->font_pipeline))
      rhi_pipeline_destroy(c->device, c->font_pipeline);
    if (rhi_handle_valid(c->image_pipeline))
      rhi_pipeline_destroy(c->device, c->image_pipeline);
    if (rhi_handle_valid(c->atlas_texture))
      rhi_texture_destroy(c->device, c->atlas_texture);
    if (rhi_handle_valid(c->sampler))
      rhi_sampler_destroy(c->device, c->sampler);
    if (rhi_handle_valid(c->nearest_sampler))
      rhi_sampler_destroy(c->device, c->nearest_sampler);
    for (i = 0; i < c->image_cache_count; i++) {
      if (rhi_handle_valid(c->images[i].texture)) {
        rhi_texture_destroy(c->device, c->images[i].texture);
      }
    }
  }
  my_mem_free(c->allocator, c->solid_verts);
  my_mem_free(c->allocator, c->image_verts);
  my_mem_free(c->allocator, c->atlas_pixels);
  my_mem_free(c->allocator, c->stack);
  my_mem_free(c->allocator, c->glyphs);
  my_vggeometry_destroy(&c->geo);
  my_mem_free(c->allocator, c);
}

static const my_vgcanvas_vtable_t s_break_rhi_vtable = {
    rhi_begin_frame,      rhi_end_frame,    rhi_save,       rhi_restore,
    rhi_translate,        rhi_clip_rect,    rhi_set_fill_color,
    rhi_set_stroke_color, rhi_set_line_width, rhi_fill_rect, rhi_stroke_rect,
    rhi_fill_rounded_rect, rhi_begin_path,  rhi_move_to,    rhi_line_to,
    rhi_close_path,       rhi_fill,         rhi_stroke,     rhi_draw_text,
    rhi_destroy,          rhi_set_font,     rhi_measure_text,
    rhi_draw_image,       rhi_set_line_cap, rhi_set_line_join,
    rhi_curve_to,         rhi_reset_clip,  rhi_set_scale_vtable,
    rhi_set_antialias_level_vtable, rhi_set_scale_filter_vtable};

static char *read_shader_search(const char *path, usize *out_len) {
  static const char *prefixes[] = {
      "",
      "engine/",
      "../engine/",
      "../../engine/",
  };
  const char *env = getenv("BREAK_SHADER_DIR");
  size_t i;

  if (env != NULL && env[0] != '\0') {
    char buf[1024];
    snprintf(buf, sizeof(buf), "%s/%s", env, path);
    char *src = shader_read_file(buf, out_len);
    if (src != NULL) {
      return src;
    }
  }
  for (i = 0; i < sizeof(prefixes) / sizeof(prefixes[0]); i++) {
    char buf[1024];
    snprintf(buf, sizeof(buf), "%s%s", prefixes[i], path);
    char *src = shader_read_file(buf, out_len);
    if (src != NULL) {
      return src;
    }
  }
  return NULL;
}

static RHIShader load_shader(RHIDevice *device, const char *path, bool fragment) {
  usize len = 0;
  char *src = read_shader_search(path, &len);
  RHIShader shader;
  if (src == NULL) return RHI_HANDLE_NULL;
  shader = rhi_shader_create(device, src, len, fragment);
  free(src);
  return shader;
}

static RHIPipeline create_pipeline(RHIDevice *device, const char *vert_path,
                                   const char *frag_path) {
  RHIShader vs = load_shader(device, vert_path, false);
  RHIShader fs = load_shader(device, frag_path, true);
  RHIPipeline pipe;
  RHIPipelineDesc desc;
  if (!rhi_handle_valid(vs) || !rhi_handle_valid(fs)) {
    if (rhi_handle_valid(vs)) rhi_shader_destroy(device, vs);
    if (rhi_handle_valid(fs)) rhi_shader_destroy(device, fs);
    return RHI_HANDLE_NULL;
  }
  memset(&desc, 0, sizeof(desc));
  desc.vert = vs;
  desc.frag = fs;
  desc.vertex_stride = sizeof(break_ui_vertex_t);
  desc.uses_textures = true;
  desc.depth_write_disable = true;
  desc.disable_culling = true;
  desc.alpha_blend = true;
  desc.font_vertex = true;
  pipe = rhi_pipeline_create(device, &desc);
  rhi_shader_destroy(device, vs);
  rhi_shader_destroy(device, fs);
  return pipe;
}

my_vgcanvas_t *my_vgcanvas_break_rhi_create(const my_allocator_t *allocator,
                                            RHIDevice *device, u32 width,
                                            u32 height) {
  my_vgcanvas_break_rhi_t *c;
  RHITextureDesc tex_desc;
  RHISamplerDesc samp_desc;
  const char *font_vert, *font_frag, *image_vert, *image_frag;
  size_t i;
  if (device == NULL || width == 0 || height == 0) return NULL;

  c = (my_vgcanvas_break_rhi_t *)my_mem_calloc(
      allocator, 1, sizeof(my_vgcanvas_break_rhi_t));
  if (c == NULL) return NULL;
  c->base.vtable = &s_break_rhi_vtable;
  c->base.capabilities.antialias_levels = MY_VGCANVAS_AA_LEVEL_BIT(0);
  c->base.capabilities.scale_filters =
      MY_VGCANVAS_FILTER_BIT(MY_SCALE_FILTER_NEAREST) |
      MY_VGCANVAS_FILTER_BIT(MY_SCALE_FILTER_BILINEAR);
  c->base.capabilities.active_antialias_level = 0u;
  c->base.capabilities.active_scale_filter = MY_SCALE_FILTER_BILINEAR;
  c->allocator = allocator;
  c->device = device;
  c->width = width;
  c->height = height;
  c->pending_antialias_level = -1;
  c->state.fill_color = my_color_rgba(0, 0, 0, 255);
  c->state.stroke_color = my_color_rgba(0, 0, 0, 255);
  c->state.line_width = 1.0f;
  c->state.scale = 1.0f;
  c->state.scale_filter = MY_SCALE_FILTER_BILINEAR;
  c->state.font_size = 16;
  c->state.line_cap = MY_LINE_CAP_BUTT;
  c->state.line_join = MY_LINE_JOIN_MITER;
  c->state.clip = my_rect_init(0, 0, (int32_t)width, (int32_t)height);
  my_vggeometry_init(&c->geo, allocator);

#ifdef ENGINE_VULKAN
  font_vert = "shaders/font_vk.vert";
  font_frag = "shaders/font_vk.frag";
  image_vert = "shaders/ui_img_vk.vert";
  image_frag = "shaders/ui_img_vk.frag";
#else
  font_vert = "shaders/font.vert";
  font_frag = "shaders/font.frag";
  image_vert = "shaders/ui_img.vert";
  image_frag = "shaders/ui_img.frag";
#endif
  c->font_pipeline = create_pipeline(device, font_vert, font_frag);
  c->image_pipeline = create_pipeline(device, image_vert, image_frag);
  if (!rhi_handle_valid(c->font_pipeline) ||
      !rhi_handle_valid(c->image_pipeline)) {
    rhi_destroy((my_vgcanvas_t *)c);
    return NULL;
  }

  c->atlas_pixels = (u8 *)my_mem_alloc(
      allocator, BREAK_RHI_ATLAS_SIZE * BREAK_RHI_ATLAS_SIZE * 4u);
  if (c->atlas_pixels == NULL) {
    rhi_destroy((my_vgcanvas_t *)c);
    return NULL;
  }
  for (i = 0; i < BREAK_RHI_ATLAS_SIZE * BREAK_RHI_ATLAS_SIZE; i++) {
    c->atlas_pixels[i * 4 + 0] = 255;
    c->atlas_pixels[i * 4 + 1] = 255;
    c->atlas_pixels[i * 4 + 2] = 255;
    c->atlas_pixels[i * 4 + 3] = 255;
  }
  memset(&tex_desc, 0, sizeof(tex_desc));
  tex_desc.width = BREAK_RHI_ATLAS_SIZE;
  tex_desc.height = BREAK_RHI_ATLAS_SIZE;
  tex_desc.format = RHI_FORMAT_R8G8B8A8_UNORM;
  tex_desc.mip_levels = 1;
  tex_desc.data = c->atlas_pixels;
  c->atlas_texture = rhi_texture_create(device, &tex_desc);

  memset(&samp_desc, 0, sizeof(samp_desc));
  samp_desc.min_filter = RHI_FILTER_LINEAR;
  samp_desc.mag_filter = RHI_FILTER_LINEAR;
  samp_desc.wrap_u = RHI_WRAP_CLAMP_TO_EDGE;
  samp_desc.wrap_v = RHI_WRAP_CLAMP_TO_EDGE;
  samp_desc.wrap_w = RHI_WRAP_CLAMP_TO_EDGE;
  c->sampler = rhi_sampler_create(device, &samp_desc);

  samp_desc.min_filter = RHI_FILTER_NEAREST;
  samp_desc.mag_filter = RHI_FILTER_NEAREST;
  c->nearest_sampler = rhi_sampler_create(device, &samp_desc);

  if (!rhi_handle_valid(c->atlas_texture) ||
      !rhi_handle_valid(c->sampler) ||
      !rhi_handle_valid(c->nearest_sampler)) {
    rhi_destroy((my_vgcanvas_t *)c);
    return NULL;
  }
  c->atlas_x = 1;
  c->atlas_y = 1;
  c->atlas_row_h = 0;
  return (my_vgcanvas_t *)c;
}

void my_vgcanvas_break_rhi_set_cmd(my_vgcanvas_t *vg, RHICmdBuffer *cmd) {
  if (vg != NULL) {
    rhi_canvas(vg)->cmd = cmd;
  }
}

void my_vgcanvas_break_rhi_set_target(my_vgcanvas_t *vg,
                                      RHIOffscreenFBO *target) {
  my_vgcanvas_break_rhi_t *c;
  RHICapabilities caps;
  if (vg == NULL) return;
  c = rhi_canvas(vg);
  c->target = target;
  c->pending_antialias_level = -1;
  c->base.capabilities.antialias_levels = MY_VGCANVAS_AA_LEVEL_BIT(0);
  if (target != NULL && rhi_device_get_capabilities(c->device, &caps) &&
      (caps.color_sample_counts & rhi_sample_count_bit(2u)) != 0u &&
      (caps.depth_sample_counts & rhi_sample_count_bit(2u)) != 0u &&
      caps.color_resolve_supported && caps.depth_resolve_supported) {
    c->base.capabilities.antialias_levels |= MY_VGCANVAS_AA_LEVEL_BIT(2);
  }
  c->base.capabilities.active_antialias_level =
      target != NULL && target->sample_count > 1u ? 2u : 0u;
}

int my_vgcanvas_break_rhi_pending_antialias_level(const my_vgcanvas_t *vg) {
  const my_vgcanvas_break_rhi_t *c;
  if (vg == NULL) return -1;
  c = (const my_vgcanvas_break_rhi_t *)vg;
  return c->pending_antialias_level;
}

my_ret_t my_vgcanvas_break_rhi_resize(my_vgcanvas_t *vg, u32 width,
                                      u32 height) {
  my_vgcanvas_break_rhi_t *c;
  if (vg == NULL || width == 0 || height == 0) return MY_RET_INVALID_PARAMS;
  c = rhi_canvas(vg);
  c->state.clip = my_vgcanvas_break_rhi_resize_clip(
      c->state.clip, c->width, c->height, width, height);
  c->width = width;
  c->height = height;
  return MY_RET_OK;
}
