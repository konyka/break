/**
 * @file my_vgcanvas_gles2.c
 * @brief GLES2 vgcanvas backend: CPU triangulation + batched submission.
 */
#include "myr/my_vgcanvas_gles2.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "myc/my_mem.h"
#include "myr/my_bezier.h"
#include "myr/my_text_layout.h"
#include "myr/my_vggeometry.h"

/* ---------------- shaders ---------------- */

static const char* VS_SRC =
    "attribute vec2 a_pos;\n"
    "uniform vec2 u_resolution;\n"
    "void main(void) {\n"
    "  vec2 ndc = (a_pos / u_resolution) * 2.0 - 1.0;\n"
    "  gl_Position = vec4(ndc.x, -ndc.y, 0.0, 1.0);\n"
    "}\n";

static const char* FS_SRC =
    "uniform vec4 u_color;\n"
    "void main(void) { gl_FragColor = u_color; }\n";

static const char* VS_TEXT_SRC =
    "attribute vec2 a_pos;\n"
    "attribute vec2 a_uv;\n"
    "uniform vec2 u_resolution;\n"
    "varying vec2 v_uv;\n"
    "void main(void) {\n"
    "  vec2 ndc = (a_pos / u_resolution) * 2.0 - 1.0;\n"
    "  gl_Position = vec4(ndc.x, -ndc.y, 0.0, 1.0);\n"
    "  v_uv = a_uv;\n"
    "}\n";

static const char* FS_IMG_SRC =
    "uniform sampler2D u_tex;\n"
    "varying vec2 v_uv;\n"
    "void main(void) { gl_FragColor = texture2D(u_tex, v_uv); }\n";

static const char* FS_TEXT_SRC =
    "uniform vec4 u_color;\n"
    "uniform sampler2D u_tex;\n"
    "varying vec2 v_uv;\n"
    "void main(void) {\n"
    "  gl_FragColor = vec4(u_color.rgb, u_color.a * texture2D(u_tex, v_uv).r);\n"
    "}\n";

#define GLES_TEX_CACHE_SIZE 64
#define GLES_IMG_TEX_CACHE_SIZE 16

/* ---------------- state ---------------- */

typedef struct gles_state_t {
  my_color_t fill_color;
  my_color_t stroke_color;
  float line_width;
  my_line_cap_t line_cap;
  my_line_join_t line_join;
  float tx;
  float ty;
  float scale; /* device = (user + translate) * scale (M12c HiDPI; 1) */
  my_rect_t clip;
  my_font_t* font;   /**< borrowed; NULL = no text */
  int32_t font_size;
  my_scale_filter_t scale_filter;
} gles_state_t;

typedef struct gles_tex_entry_t {
  my_font_t* font;
  uint32_t codepoint;
  int32_t size;
  uint32_t texture; /**< 0 = empty */
} gles_tex_entry_t;

/** @brief Image texture cache entry: keyed by (ptr, w, h); the caller must
 * keep the bitmap alive while it may be used (my_image's decode cache
 * holds images for many frames, so this is safe in practice). */
typedef struct gles_img_tex_entry_t {
  const uint8_t* ptr;
  int32_t w;
  int32_t h;
  my_scale_filter_t filter;
  uint32_t texture; /**< 0 = empty */
  uint64_t last_used;
} gles_img_tex_entry_t;

typedef struct my_vgcanvas_gles2_t {
  my_vgcanvas_t base;
  const my_allocator_t* allocator;
  my_gl_t gl;
  int32_t fb_w;
  int32_t fb_h;
  uint32_t program;
  uint32_t text_program; /**< lazy: created on first draw_text */
  uint32_t img_program;  /**< lazy: created on first draw_image */
  bool msaa;             /**< GL_MULTISAMPLE requested (M11c) */
  bool multisample_available;
  gles_tex_entry_t tex_cache[GLES_TEX_CACHE_SIZE];
  gles_img_tex_entry_t img_tex_cache[GLES_IMG_TEX_CACHE_SIZE];
  uint64_t img_tex_tick;
  gles_state_t state;

  gles_state_t* stack;
  size_t stack_count, stack_cap;

  my_vggeometry_t geo; /**< CPU triangulation (M25b, shared) */
} my_vgcanvas_gles2_t;

/**
 * @brief create_program with the GL table's shader headers applied
 * (M25a): the bodies above are API-neutral; the header seam adapts them
 * (ES2 prepends the precision line, desktop GL "#version 120"). Bodies
 * are compile-time constants that always fit the buffers.
 */
static uint32_t gles_make_program(my_vgcanvas_gles2_t* s, const char* vs_body,
                                  const char* fs_body) {
  char vs[1024];
  char fs[1024];
  size_t vh =
      s->gl.shader_header_vs != NULL ? strlen(s->gl.shader_header_vs) : 0;
  size_t fh =
      s->gl.shader_header_fs != NULL ? strlen(s->gl.shader_header_fs) : 0;
  if (vh + strlen(vs_body) >= sizeof(vs) ||
      fh + strlen(fs_body) >= sizeof(fs)) {
    return 0; /* defensive: the built-in sources always fit */
  }
  if (vh > 0) {
    memcpy(vs, s->gl.shader_header_vs, vh);
  }
  strcpy(vs + vh, vs_body);
  if (fh > 0) {
    memcpy(fs, s->gl.shader_header_fs, fh);
  }
  strcpy(fs + fh, fs_body);
  return s->gl.create_program(s->gl.ctx, vs, fs);
}

/* ---------------- helpers ---------------- */

static my_ret_t gles_grow(const my_allocator_t* alloc, void** arr, size_t* cap,
                          size_t need, size_t elem) {
  void* p;
  size_t new_cap = *cap > 0 ? *cap : 64;
  if (need <= *cap) {
    return MY_RET_OK;
  }
  while (new_cap < need) {
    new_cap *= 2;
  }
  p = my_mem_realloc(alloc, *arr, new_cap * elem);
  if (p == NULL) {
    return MY_RET_OOM;
  }
  *arr = p;
  *cap = new_cap;
  return MY_RET_OK;
}

static void gles_apply_clip(my_vgcanvas_gles2_t* s) {
  /* GL scissor origin is bottom-left: flip y */
  s->gl.scissor(s->gl.ctx, s->state.clip.x,
                s->fb_h - s->state.clip.y - s->state.clip.h, s->state.clip.w,
                s->state.clip.h);
}

static void gles_draw(my_vgcanvas_gles2_t* s, const float* xy, int32_t count,
                      my_color_t color) {
  s->gl.uniform4f(s->gl.ctx, s->program, "u_color", (float)color.r / 255.0f,
                  (float)color.g / 255.0f, (float)color.b / 255.0f,
                  (float)color.a / 255.0f);
  s->gl.draw_arrays_triangles(s->gl.ctx, s->program, xy, count);
}

/** @brief Reset the triangle output and apply the current state transform
 * (M25b: the writer moved into the shared my_vggeometry). */
static void gles_geo_setup(my_vgcanvas_gles2_t* s) {
  my_vggeometry_set_transform(&s->geo, s->state.tx, s->state.ty,
                              s->state.scale);
  my_vggeometry_begin_verts(&s->geo);
}

/** @brief Submit the accumulated triangles with `color` (skip when empty). */
static void gles_draw_geo(my_vgcanvas_gles2_t* s, my_color_t color) {
  if (s->geo.vert_count > 0) {
    gles_draw(s, s->geo.verts, (int32_t)(s->geo.vert_count / 2), color);
  }
}

/* ---------------- frame/state vtable ---------------- */

static my_ret_t gles_begin_frame(my_vgcanvas_t* vg, const my_rect_t* dirty) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  (void)dirty;
  s->gl.viewport(s->gl.ctx, s->fb_w, s->fb_h);
  s->gl.uniform2f(s->gl.ctx, s->program, "u_resolution", (float)s->fb_w,
                  (float)s->fb_h);
  s->gl.enable_scissor(s->gl.ctx, true);
  gles_apply_clip(s);
  return MY_RET_OK;
}

static my_ret_t gles_end_frame(my_vgcanvas_t* vg) {
  (void)vg; /* submission is immediate per draw call; nothing to flush */
  return MY_RET_OK;
}

static my_ret_t gles_save(my_vgcanvas_t* vg) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  if (gles_grow(s->allocator, (void**)&s->stack, &s->stack_cap,
                s->stack_count + 1, sizeof(gles_state_t)) != MY_RET_OK) {
    return MY_RET_OOM;
  }
  s->stack[s->stack_count++] = s->state;
  return MY_RET_OK;
}

static my_ret_t gles_restore(my_vgcanvas_t* vg) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  if (s->stack_count == 0) {
    return MY_RET_FAIL;
  }
  s->state = s->stack[--s->stack_count];
  gles_apply_clip(s);
  return MY_RET_OK;
}

static my_ret_t gles_translate(my_vgcanvas_t* vg, float dx, float dy) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  s->state.tx += dx;
  s->state.ty += dy;
  return MY_RET_OK;
}

/** @brief reset_clip slot (M25): same device-space math as clip_rect but
 * REPLACES the clip instead of intersecting (overlay escape hatch). */
static my_ret_t gles_reset_clip(my_vgcanvas_t* vg, const my_rectf_t* rect) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  if (rect == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  s->state.clip = my_rect_init(
      (int32_t)floorf((rect->x + s->state.tx) * s->state.scale),
      (int32_t)floorf((rect->y + s->state.ty) * s->state.scale),
      (int32_t)ceilf((rect->x + s->state.tx + rect->w) * s->state.scale) -
          (int32_t)floorf((rect->x + s->state.tx) * s->state.scale),
      (int32_t)ceilf((rect->y + s->state.ty + rect->h) * s->state.scale) -
          (int32_t)floorf((rect->y + s->state.ty) * s->state.scale));
  gles_apply_clip(s);
  return MY_RET_OK;
}

static my_ret_t gles_clip_rect(my_vgcanvas_t* vg, const my_rectf_t* rect) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  my_rect_t dev, clipped;
  if (rect == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  dev = my_rect_init(
      (int32_t)floorf((rect->x + s->state.tx) * s->state.scale),
      (int32_t)floorf((rect->y + s->state.ty) * s->state.scale),
      (int32_t)ceilf((rect->x + s->state.tx + rect->w) * s->state.scale) -
          (int32_t)floorf((rect->x + s->state.tx) * s->state.scale),
      (int32_t)ceilf((rect->y + s->state.ty + rect->h) * s->state.scale) -
          (int32_t)floorf((rect->y + s->state.ty) * s->state.scale));
  if (my_rect_intersect(&s->state.clip, &dev, &clipped)) {
    s->state.clip = clipped;
  } else {
    s->state.clip = my_rect_init(0, 0, 0, 0);
  }
  gles_apply_clip(s);
  return MY_RET_OK;
}

static my_ret_t gles_set_fill_color(my_vgcanvas_t* vg, my_color_t color) {
  ((my_vgcanvas_gles2_t*)vg)->state.fill_color = color;
  return MY_RET_OK;
}

static my_ret_t gles_set_stroke_color(my_vgcanvas_t* vg, my_color_t color) {
  ((my_vgcanvas_gles2_t*)vg)->state.stroke_color = color;
  return MY_RET_OK;
}

static my_ret_t gles_set_line_width(my_vgcanvas_t* vg, float width) {
  ((my_vgcanvas_gles2_t*)vg)->state.line_width = width;
  return MY_RET_OK;
}

/* ---------------- primitives ---------------- */

static my_ret_t gles_fill_rect(my_vgcanvas_t* vg, const my_rectf_t* rect) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  if (rect == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  gles_geo_setup(s);
  my_vggeometry_rect(&s->geo, rect->x, rect->y, rect->x + rect->w,
                     rect->y + rect->h);
  gles_draw_geo(s, s->state.fill_color);
  return MY_RET_OK;
}

static my_ret_t gles_stroke_rect(my_vgcanvas_t* vg, const my_rectf_t* rect) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  if (rect == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  gles_geo_setup(s);
  my_vggeometry_stroke_rect(&s->geo, rect->x, rect->y, rect->w, rect->h,
                            s->state.line_width);
  gles_draw_geo(s, s->state.stroke_color);
  return MY_RET_OK;
}

static my_ret_t gles_fill_rounded_rect(my_vgcanvas_t* vg, const my_rectf_t* rect,
                                       float radius) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  if (rect == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  gles_geo_setup(s);
  my_vggeometry_fill_rounded_rect(&s->geo, rect->x, rect->y, rect->w,
                                  rect->h, radius);
  gles_draw_geo(s, s->state.fill_color);
  return MY_RET_OK;
}

/* ---------------- path (delegated to my_vggeometry, M25b) ---------------- */

static my_ret_t gles_begin_path(my_vgcanvas_t* vg) {
  return my_vggeometry_begin_path(&((my_vgcanvas_gles2_t*)vg)->geo);
}

static my_ret_t gles_move_to(my_vgcanvas_t* vg, float x, float y) {
  return my_vggeometry_move_to(&((my_vgcanvas_gles2_t*)vg)->geo, x, y);
}

static my_ret_t gles_line_to(my_vgcanvas_t* vg, float x, float y) {
  return my_vggeometry_line_to(&((my_vgcanvas_gles2_t*)vg)->geo, x, y);
}

static my_ret_t gles_close_path(my_vgcanvas_t* vg) {
  return my_vggeometry_close_path(&((my_vgcanvas_gles2_t*)vg)->geo);
}

/* ---------------- vtable: curve_to (M19a) ---------------- */

static my_ret_t gles_curve_to(my_vgcanvas_t* vg, float cx1, float cy1,
                              float cx2, float cy2, float x, float y) {
  return my_vggeometry_curve_to(&((my_vgcanvas_gles2_t*)vg)->geo, cx1, cy1,
                                cx2, cy2, x, y);
}

/**
 * @brief Even-odd scanline fill, identical rasterization rule to the soft
 * backend: every filled span becomes one rect (2 triangles).
 */
static my_ret_t gles_fill(my_vgcanvas_t* vg) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  gles_geo_setup(s);
  if (my_vggeometry_fill(&s->geo, &s->state.clip) == MY_RET_OOM) {
    return MY_RET_OOM;
  }
  gles_draw_geo(s, s->state.fill_color);
  return MY_RET_OK;
}

static my_ret_t gles_stroke(my_vgcanvas_t* vg) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  gles_geo_setup(s);
  my_vggeometry_stroke(&s->geo, s->state.line_width, s->state.line_cap,
                       s->state.line_join);
  gles_draw_geo(s, s->state.stroke_color);
  return MY_RET_OK;
}

static my_ret_t gles_set_line_cap(my_vgcanvas_t* vg, my_line_cap_t cap) {
  ((my_vgcanvas_gles2_t*)vg)->state.line_cap = cap;
  return MY_RET_OK;
}

static my_ret_t gles_set_line_join(my_vgcanvas_t* vg, my_line_join_t join) {
  ((my_vgcanvas_gles2_t*)vg)->state.line_join = join;
  return MY_RET_OK;
}

static my_ret_t gles_set_scale_vtable(my_vgcanvas_t* vg, float scale) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  if (s == NULL || scale <= 0.0f) {
    return MY_RET_INVALID_PARAMS;
  }
  s->state.scale = scale;
  return MY_RET_OK;
}

static my_ret_t gles_set_antialias_level_vtable(my_vgcanvas_t* vg,
                                                int level) {
  return my_vgcanvas_gles2_set_antialias(vg, level > 0);
}

static my_ret_t gles_set_scale_filter_vtable(my_vgcanvas_t* vg,
                                             my_scale_filter_t filter) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  if (s == NULL || (filter != MY_SCALE_FILTER_NEAREST &&
                    filter != MY_SCALE_FILTER_BILINEAR)) {
    return MY_RET_INVALID_PARAMS;
  }
  s->state.scale_filter = filter;
  return MY_RET_OK;
}

/** @brief Font size in device pixels (M12c: logical size * scale). */
static int32_t gles_dev_font_size(const my_vgcanvas_gles2_t* s) {
  int32_t d = (int32_t)((float)s->state.font_size * s->state.scale + 0.5f);
  return d > 0 ? d : 1;
}

/** @brief Draw one codepoint at pen_x and advance it (gles text body). */
static void gles_draw_cp(my_vgcanvas_gles2_t* s, uint32_t cp, float* pen_x,
                         float top, int32_t ascent) {
  my_glyph_t g;
  uint32_t slot;
  float gx, gy, quad[24];
  if (my_font_get_glyph(s->state.font, cp, gles_dev_font_size(s), &g) !=
          MY_RET_OK ||
      g.bitmap == NULL || g.w <= 0 || g.h <= 0) {
    *pen_x += g.advance > 0 ? (float)g.advance : 0.0f;
    return;
  }
  /* direct-mapped texture cache: evict on slot collision */
  slot = (cp ^ (uint32_t)gles_dev_font_size(s)) % GLES_TEX_CACHE_SIZE;
  if (s->tex_cache[slot].texture == 0 ||
      s->tex_cache[slot].font != s->state.font ||
      s->tex_cache[slot].codepoint != cp ||
      s->tex_cache[slot].size != gles_dev_font_size(s)) {
    if (s->tex_cache[slot].texture != 0) {
      s->gl.delete_texture(s->gl.ctx, s->tex_cache[slot].texture);
    }
    s->tex_cache[slot].texture =
        s->gl.create_texture(s->gl.ctx, g.bitmap, g.w, g.h);
    s->tex_cache[slot].font = s->state.font;
    s->tex_cache[slot].codepoint = cp;
    s->tex_cache[slot].size = gles_dev_font_size(s);
  }
  gx = *pen_x + (float)g.bearing_x;
  gy = top + (float)(ascent - g.bearing_y);
  /* quad: 2 triangles, interleaved xy+uv */
  {
    float x0 = gx, y0 = gy, x1 = gx + (float)g.w, y1 = gy + (float)g.h;
    const float verts[6][4] = {{x0, y0, 0, 0}, {x1, y0, 1, 0}, {x1, y1, 1, 1},
                               {x0, y0, 0, 0}, {x1, y1, 1, 1}, {x0, y1, 0, 1}};
    memcpy(quad, verts, sizeof(quad));
  }
  s->gl.uniform4f(s->gl.ctx, s->text_program, "u_color",
                  (float)s->state.fill_color.r / 255.0f,
                  (float)s->state.fill_color.g / 255.0f,
                  (float)s->state.fill_color.b / 255.0f,
                  (float)s->state.fill_color.a / 255.0f);
  s->gl.draw_textured_quads(s->gl.ctx, s->text_program,
                            s->tex_cache[slot].texture, quad, 6);
  *pen_x += (float)g.advance;
}

static my_ret_t gles_draw_text(my_vgcanvas_t* vg, const char* text, float x,
                               float y) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  int32_t ascent;
  float pen_x, top;
  const char* p = text;

  if (text == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (s->state.font == NULL || s->state.font_size <= 0 ||
      s->gl.create_texture == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  if (s->text_program == 0) {
    s->text_program =
        gles_make_program(s, VS_TEXT_SRC, FS_TEXT_SRC);
    if (s->text_program == 0) {
      return MY_RET_FAIL;
    }
  }
  s->gl.use_program(s->gl.ctx, s->text_program);
  s->gl.uniform2f(s->gl.ctx, s->text_program, "u_resolution", (float)s->fb_w,
                  (float)s->fb_h);

  ascent = my_font_ascent(s->state.font, gles_dev_font_size(s));
  pen_x = (x + s->state.tx) * s->state.scale;
  top = (y + s->state.ty) * s->state.scale;

  if (!my_text_layout_may_need_bidi(text)) {
    /* fast path: plain LTR, no layout work at all */
    while (*p != '\0') {
      gles_draw_cp(s, my_utf8_next(&p), &pen_x, top, ascent);
    }
  } else {
    /* shaped + visually reordered path (M11a); x is always the left
     * edge (see my_text_layout.h) */
    my_text_layout_t* l = my_text_layout_process(s->allocator, text);
    size_t i;
    if (l == NULL) {
      return MY_RET_OOM;
    }
    for (i = 0; i < l->len; i++) {
      gles_draw_cp(s, l->visual_cps[i], &pen_x, top, ascent);
    }
    my_text_layout_destroy(l);
  }
  /* restore the flat-color program for subsequent geometry */
  s->gl.use_program(s->gl.ctx, s->program);
  return MY_RET_OK;
}

static my_ret_t gles_set_font(my_vgcanvas_t* vg, my_font_t* font,
                              int32_t size) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  if (font != NULL) {
    s->state.font = font;
  }
  if (size > 0) {
    s->state.font_size = size;
  }
  return MY_RET_OK;
}

static uint32_t gles_image_texture(my_vgcanvas_gles2_t* s, const uint8_t* rgba,
                                   int32_t w, int32_t h,
                                   my_scale_filter_t filter) {
  size_t i;
  gles_img_tex_entry_t* lru = &s->img_tex_cache[0];
  for (i = 0; i < GLES_IMG_TEX_CACHE_SIZE; i++) {
    gles_img_tex_entry_t* e = &s->img_tex_cache[i];
    if (e->texture == 0) {
      lru = e;
      continue;
    }
    if (e->last_used < lru->last_used) {
      lru = e;
    }
    if (e->ptr == rgba && e->w == w && e->h == h && e->filter == filter) {
      e->last_used = ++s->img_tex_tick;
      return e->texture;
    }
  }
  if (lru->texture != 0) {
    s->gl.delete_texture(s->gl.ctx, lru->texture);
  }
  if (s->gl.create_texture_rgba_filtered != NULL) {
    lru->texture = s->gl.create_texture_rgba_filtered(
        s->gl.ctx, rgba, w, h, filter == MY_SCALE_FILTER_BILINEAR);
  } else {
    lru->texture = s->gl.create_texture_rgba(s->gl.ctx, rgba, w, h);
  }
  lru->ptr = rgba;
  lru->w = w;
  lru->h = h;
  lru->filter = filter;
  lru->last_used = ++s->img_tex_tick;
  return lru->texture;
}

static my_ret_t gles_draw_image(my_vgcanvas_t* vg, const uint8_t* rgba,
                                int32_t w, int32_t h, const my_rectf_t* dst,
                                const my_color_t* bg) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  uint32_t tex;
  float quad[24];
  if (rgba == NULL || dst == NULL || w <= 0 || h <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (s->gl.create_texture_rgba == NULL &&
      s->gl.create_texture_rgba_filtered == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  /* bg compositing: paint bg rect first, then blend the textured quad */
  if (bg != NULL && bg->a > 0) {
    gles_geo_setup(s);
    my_vggeometry_rect(&s->geo, dst->x, dst->y, dst->x + dst->w,
                       dst->y + dst->h);
    gles_draw_geo(s, *bg);
  }
  if (s->img_program == 0) {
    s->img_program = gles_make_program(s, VS_TEXT_SRC, FS_IMG_SRC);
    if (s->img_program == 0) {
      return MY_RET_FAIL;
    }
  }
  tex = gles_image_texture(s, rgba, w, h, s->state.scale_filter);
  if (tex == 0) {
    return MY_RET_OOM;
  }
  {
    float x0 = (dst->x + s->state.tx) * s->state.scale;
    float y0 = (dst->y + s->state.ty) * s->state.scale;
    float x1 = x0 + dst->w * s->state.scale;
    float y1 = y0 + dst->h * s->state.scale;
    const float verts[6][4] = {{x0, y0, 0, 0}, {x1, y0, 1, 0}, {x1, y1, 1, 1},
                               {x0, y0, 0, 0}, {x1, y1, 1, 1}, {x0, y1, 0, 1}};
    memcpy(quad, verts, sizeof(quad));
  }
  s->gl.use_program(s->gl.ctx, s->img_program);
  s->gl.uniform2f(s->gl.ctx, s->img_program, "u_resolution", (float)s->fb_w,
                  (float)s->fb_h);
  s->gl.draw_textured_quads(s->gl.ctx, s->img_program, tex, quad, 6);
  s->gl.use_program(s->gl.ctx, s->program);
  return MY_RET_OK;
}

static my_ret_t gles_measure_text(my_vgcanvas_t* vg, const char* text,
                                  int32_t* w, int32_t* h) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  my_ret_t ret;
  if (s->state.font == NULL || s->state.font_size <= 0) {
    return MY_RET_NOT_SUPPORTED;
  }
  /* measure at the device size, report LOGICAL units (M12c) */
  if (text != NULL && my_text_layout_may_need_bidi(text)) {
    /* shaping changes widths (order does not): measure the shaped and
     * reordered string (M11a) */
    my_text_layout_t* l = my_text_layout_process(s->allocator, text);
    if (l == NULL) {
      return MY_RET_OOM;
    }
    ret = my_font_measure(s->state.font, l->visual_utf8,
                          gles_dev_font_size(s), w, h);
    my_text_layout_destroy(l);
  } else {
    ret = my_font_measure(s->state.font, text, gles_dev_font_size(s), w, h);
  }
  if (ret == MY_RET_OK && s->state.scale != 1.0f) {
    if (w != NULL) {
      *w = (int32_t)((float)*w / s->state.scale + 0.5f);
    }
    if (h != NULL) {
      *h = (int32_t)((float)*h / s->state.scale + 0.5f);
    }
  }
  return ret;
}

/* ---------------- lifecycle ---------------- */

static void gles_destroy(my_vgcanvas_t* vg) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  if (s != NULL) {
    size_t i;
    if (s->gl.delete_texture != NULL) {
      for (i = 0; i < GLES_TEX_CACHE_SIZE; i++) {
        if (s->tex_cache[i].texture != 0) {
          s->gl.delete_texture(s->gl.ctx, s->tex_cache[i].texture);
        }
      }
      for (i = 0; i < GLES_IMG_TEX_CACHE_SIZE; i++) {
        if (s->img_tex_cache[i].texture != 0) {
          s->gl.delete_texture(s->gl.ctx, s->img_tex_cache[i].texture);
        }
      }
    }
    if (s->text_program != 0 && s->gl.delete_program != NULL) {
      s->gl.delete_program(s->gl.ctx, s->text_program);
    }
    if (s->img_program != 0 && s->gl.delete_program != NULL) {
      s->gl.delete_program(s->gl.ctx, s->img_program);
    }
    if (s->program != 0 && s->gl.delete_program != NULL) {
      s->gl.delete_program(s->gl.ctx, s->program);
    }
    my_mem_free(s->allocator, s->stack);
    my_vggeometry_destroy(&s->geo);
    my_mem_free(s->allocator, s);
  }
}

static const my_vgcanvas_vtable_t s_gles_vtable = {
    gles_begin_frame,      gles_end_frame,   gles_save,          gles_restore,
    gles_translate,        gles_clip_rect,   gles_set_fill_color,
    gles_set_stroke_color, gles_set_line_width, gles_fill_rect,  gles_stroke_rect,
    gles_fill_rounded_rect, gles_begin_path, gles_move_to,       gles_line_to,
    gles_close_path,       gles_fill,        gles_stroke,        gles_draw_text,
    gles_destroy,          gles_set_font,    gles_measure_text,
    gles_draw_image,       gles_set_line_cap, gles_set_line_join,
    gles_curve_to,         gles_reset_clip,  gles_set_scale_vtable,
    gles_set_antialias_level_vtable, gles_set_scale_filter_vtable};

my_vgcanvas_t* my_vgcanvas_gles2_create_with_gl(const my_allocator_t* allocator,
                                                int32_t width, int32_t height,
                                                const my_gl_t* gl) {
  my_vgcanvas_gles2_t* s;
  if (gl == NULL || gl->create_program == NULL || width <= 0 || height <= 0) {
    return NULL;
  }
  s = (my_vgcanvas_gles2_t*)my_mem_calloc(allocator, 1,
                                          sizeof(my_vgcanvas_gles2_t));
  if (s == NULL) {
    return NULL;
  }
  s->base.vtable = &s_gles_vtable;
  s->base.capabilities.antialias_levels = MY_VGCANVAS_AA_LEVEL_BIT(0);
  s->base.capabilities.scale_filters =
      MY_VGCANVAS_FILTER_BIT(MY_SCALE_FILTER_NEAREST) |
      MY_VGCANVAS_FILTER_BIT(MY_SCALE_FILTER_BILINEAR);
  s->base.capabilities.active_antialias_level = 0u;
  s->base.capabilities.active_scale_filter = MY_SCALE_FILTER_BILINEAR;
  s->allocator = allocator;
  s->gl = *gl;
  s->fb_w = width;
  s->fb_h = height;
  s->multisample_available =
      gl->has_multisample != NULL && gl->has_multisample(gl->ctx);
  if (s->multisample_available) {
    s->base.capabilities.antialias_levels |= MY_VGCANVAS_AA_LEVEL_BIT(2);
  }
  my_vggeometry_init(&s->geo, allocator);
  s->program = gles_make_program(s, VS_SRC, FS_SRC);
  if (s->program == 0) {
    my_mem_free(allocator, s);
    return NULL;
  }
  gl->use_program(gl->ctx, s->program);
  s->state.fill_color = my_color_rgba(0, 0, 0, 255);
  s->state.stroke_color = my_color_rgba(0, 0, 0, 255);
  s->state.line_width = 1.0f;
  s->state.line_cap = MY_LINE_CAP_BUTT;
  s->state.line_join = MY_LINE_JOIN_MITER;
  s->state.scale = 1.0f; /* HiDPI: my_vgcanvas_gles2_set_scale (M12c) */
  s->state.font = NULL;
  s->state.font_size = 16;
  s->state.scale_filter = MY_SCALE_FILTER_BILINEAR;
  s->state.clip = my_rect_init(0, 0, width, height);
  return (my_vgcanvas_t*)s;
}

my_vgcanvas_t* my_vgcanvas_gles2_create(const my_allocator_t* allocator,
                                        int32_t width, int32_t height) {
  const my_gl_t* gl = my_gl_real_default();
  if (gl == NULL) {
    return NULL;
  }
  return my_vgcanvas_gles2_create_with_gl(allocator, width, height, gl);
}

my_ret_t my_vgcanvas_gles2_resize(my_vgcanvas_t* vg, int32_t width,
                                  int32_t height) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  if (s == NULL || width <= 0 || height <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  s->fb_w = width;
  s->fb_h = height;
  s->gl.viewport(s->gl.ctx, width, height);
  s->gl.uniform2f(s->gl.ctx, s->program, "u_resolution", (float)width,
                  (float)height);
  return MY_RET_OK;
}

my_ret_t my_vgcanvas_gles2_set_antialias(my_vgcanvas_t* vg, bool enabled) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  if (s == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (enabled && !s->multisample_available) {
    return MY_RET_NOT_SUPPORTED;
  }
  if (s->msaa == enabled) {
    return MY_RET_OK;
  }
  s->msaa = enabled;
  if (s->gl.set_multisample != NULL) {
    s->gl.set_multisample(s->gl.ctx, enabled);
  }
  s->base.capabilities.active_antialias_level = enabled ? 2u : 0u;
  return MY_RET_OK;
}

my_ret_t my_vgcanvas_gles2_set_multisample_available(my_vgcanvas_t* vg,
                                                      bool available) {
  my_vgcanvas_gles2_t* s = (my_vgcanvas_gles2_t*)vg;
  if (s == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (!available && s->msaa) {
    if (s->gl.set_multisample != NULL) {
      s->gl.set_multisample(s->gl.ctx, false);
    }
    s->msaa = false;
    s->base.capabilities.active_antialias_level = 0u;
  }
  s->multisample_available = available;
  s->base.capabilities.antialias_levels = MY_VGCANVAS_AA_LEVEL_BIT(0);
  if (available) {
    s->base.capabilities.antialias_levels |= MY_VGCANVAS_AA_LEVEL_BIT(2);
  }
  return MY_RET_OK;
}

my_ret_t my_vgcanvas_gles2_set_scale(my_vgcanvas_t* vg, float scale) {
  return gles_set_scale_vtable(vg, scale);
}
