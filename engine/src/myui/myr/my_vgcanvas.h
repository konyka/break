/**
 * @file my_vgcanvas.h
 * @brief 2D vector canvas abstract interface — vtable (frozen in M1).
 *
 * All widget rendering goes through this interface. Backends:
 * my_vgcanvas_soft (software rasterizer on an lcd, M1); later GLES /
 * Metal / WebGL implement the same vtable so widget code never changes.
 *
 * Semantics:
 *  - Coordinates are float "user space"; the only transform is translate
 *    (rotate/scale deferred to a later milestone — the vtable does not
 *    rule them out, they will be added as new entries before freeze of
 *    dependent code).
 *  - State = fill/stroke color, line width, translate, clip. save/restore
 *    form a stack; clip_rect always intersects with the current clip.
 *  - Path: begin_path/move_to/line_to/close_path build subpaths; fill()
 *    rasterizes with the EVEN-ODD rule, stroke() draws the polyline(s).
 *  - No anti-aliasing and no alpha blending yet (M3+ re-evaluation);
 *    nothing in this interface prevents adding them inside a backend.
 *  - draw_text is a placeholder until the font system lands (M3+):
 *    backends return MY_RET_NOT_SUPPORTED for now.
 */
#ifndef MY_VGCANVAS_H
#define MY_VGCANVAS_H

#include "myc/my_error.h"
#include "myr/my_color.h"
#include "myr/my_font.h"
#include "myr/my_rect.h"

typedef struct my_vgcanvas_t my_vgcanvas_t;

/** @brief Stroke cap style (M9c). */
typedef enum my_line_cap_t {
  MY_LINE_CAP_BUTT = 0,
  MY_LINE_CAP_ROUND
} my_line_cap_t;

/** @brief Stroke join style (M9c). */
typedef enum my_line_join_t {
  MY_LINE_JOIN_MITER = 0,
  MY_LINE_JOIN_ROUND
} my_line_join_t;

/** @brief Image scaling filter (draw_image, M9b). */
typedef enum my_scale_filter_t {
  MY_SCALE_FILTER_NEAREST = 0,
  MY_SCALE_FILTER_BILINEAR
} my_scale_filter_t;

/** @brief vgcanvas vtable (frozen interface for all render backends). */
typedef struct my_vgcanvas_vtable_t {
  /** @brief Begin a frame; dirty hints the redraw region (may be NULL). */
  my_ret_t (*begin_frame)(my_vgcanvas_t* vg, const my_rect_t* dirty);
  my_ret_t (*end_frame)(my_vgcanvas_t* vg);

  my_ret_t (*save)(my_vgcanvas_t* vg);
  my_ret_t (*restore)(my_vgcanvas_t* vg);

  /** @brief Accumulate a translation to the current transform. */
  my_ret_t (*translate)(my_vgcanvas_t* vg, float dx, float dy);
  /** @brief Intersect the current clip with rect (user space). */
  my_ret_t (*clip_rect)(my_vgcanvas_t* vg, const my_rectf_t* rect);

  my_ret_t (*set_fill_color)(my_vgcanvas_t* vg, my_color_t color);
  my_ret_t (*set_stroke_color)(my_vgcanvas_t* vg, my_color_t color);
  my_ret_t (*set_line_width)(my_vgcanvas_t* vg, float width);

  my_ret_t (*fill_rect)(my_vgcanvas_t* vg, const my_rectf_t* rect);
  my_ret_t (*stroke_rect)(my_vgcanvas_t* vg, const my_rectf_t* rect);
  my_ret_t (*fill_rounded_rect)(my_vgcanvas_t* vg, const my_rectf_t* rect,
                                float radius);

  my_ret_t (*begin_path)(my_vgcanvas_t* vg);
  my_ret_t (*move_to)(my_vgcanvas_t* vg, float x, float y);
  my_ret_t (*line_to)(my_vgcanvas_t* vg, float x, float y);
  my_ret_t (*close_path)(my_vgcanvas_t* vg);
  /** @brief Fill current path (even-odd rule). */
  my_ret_t (*fill)(my_vgcanvas_t* vg);
  /** @brief Stroke current path (polyline with line_width). */
  my_ret_t (*stroke)(my_vgcanvas_t* vg);

  /** @brief Placeholder until the font system (returns NOT_SUPPORTED). */
  my_ret_t (*draw_text)(my_vgcanvas_t* vg, const char* text, float x, float y);

  void (*destroy)(my_vgcanvas_t* vg);

  /**
   * @brief Set the current font and size (M7a). font may be NULL to
   * change only the size; draw_text returns NOT_SUPPORTED without a font.
   * The canvas borrows font and does not retain or destroy it. The font must
   * remain alive until the canvas is destroyed or another font is installed.
   */
  my_ret_t (*set_font)(my_vgcanvas_t* vg, my_font_t* font, int32_t size);

  /** @brief Measure text with the current font/size (NOT_SUPPORTED without). */
  my_ret_t (*measure_text)(my_vgcanvas_t* vg, const char* text, int32_t* w,
                           int32_t* h);

  /**
   * @brief Blit an RGBA8888 image into dst (user space), nearest-neighbor
   * scaled. When bg != NULL each source pixel is first composited over bg
   * (src * a + bg * (1-a)); the result is written opaquely. May return
   * MY_RET_NOT_SUPPORTED on backends without image support. GPU backends may
   * cache by the bitmap pointer and dimensions, so rgba contents must remain
   * unchanged while the canvas may reuse that image. Use a new stable buffer
   * identity after changing pixels.
   */
  my_ret_t (*draw_image)(my_vgcanvas_t* vg, const uint8_t* rgba, int32_t w,
                         int32_t h, const my_rectf_t* dst,
                         const my_color_t* bg);
  /**
   * @brief Stroke cap/join styles (M9c). SOFT backend implements ROUND
   * (coverage-AA circles); other backends may ignore (documented TODO).
   * Part of the save/restore state.
   */
  my_ret_t (*set_line_cap)(my_vgcanvas_t* vg, my_line_cap_t cap);
  my_ret_t (*set_line_join)(my_vgcanvas_t* vg, my_line_join_t join);
  /**
   * @brief Cubic bezier from the current point to (x, y) with control
   * points (cx1, cy1), (cx2, cy2) (M19a). Path-level operation like
   * line_to; backends subdivide adaptively (flatness ~0.25px) into
   * polylines, so strokes get the usual AA. NULL slot = NOT_SUPPORTED.
   */
  my_ret_t (*curve_to)(my_vgcanvas_t* vg, float cx1, float cy1, float cx2,
                       float cy2, float x, float y);
  /**
   * @brief Replace (NOT intersect) the current clip with rect, user
   * space (M25). Escape hatch for overlays that paint in a different
   * coordinate space than the framework-baked clip assumes (node_view
   * minimap/rubber-band, M22). NULL slot = NOT_SUPPORTED (the caller
   * must tolerate that). Replaces the former soft-only
   * my_vgcanvas_soft_reset_clip() — which corrupted non-soft backends
   * when called on them.
   */
  my_ret_t (*reset_clip)(my_vgcanvas_t* vg, const my_rectf_t* rect);
  /** @brief Set the device scale used by coordinates and font sizes. */
  my_ret_t (*set_scale)(my_vgcanvas_t* vg, float scale);
  /** @brief Set AA quality (0 = off, 2 = preferred); may be unsupported. */
  my_ret_t (*set_antialias_level)(my_vgcanvas_t* vg, int level);
  /** @brief Select image filtering; fixed-sampler backends may reject it. */
  my_ret_t (*set_scale_filter)(my_vgcanvas_t* vg, my_scale_filter_t filter);
} my_vgcanvas_vtable_t;

/** @brief vgcanvas base "class": first member of every backend. */
struct my_vgcanvas_t {
  const my_vgcanvas_vtable_t* vtable;
};

static inline my_ret_t my_vgcanvas_begin_frame(my_vgcanvas_t* vg,
                                               const my_rect_t* dirty) {
  return vg->vtable->begin_frame(vg, dirty);
}

static inline my_ret_t my_vgcanvas_end_frame(my_vgcanvas_t* vg) {
  return vg->vtable->end_frame(vg);
}

static inline my_ret_t my_vgcanvas_save(my_vgcanvas_t* vg) {
  return vg->vtable->save(vg);
}

static inline my_ret_t my_vgcanvas_restore(my_vgcanvas_t* vg) {
  return vg->vtable->restore(vg);
}

static inline my_ret_t my_vgcanvas_translate(my_vgcanvas_t* vg, float dx, float dy) {
  return vg->vtable->translate(vg, dx, dy);
}

static inline my_ret_t my_vgcanvas_clip_rect(my_vgcanvas_t* vg,
                                             const my_rectf_t* rect) {
  return vg->vtable->clip_rect(vg, rect);
}

static inline my_ret_t my_vgcanvas_set_fill_color(my_vgcanvas_t* vg,
                                                  my_color_t color) {
  return vg->vtable->set_fill_color(vg, color);
}

static inline my_ret_t my_vgcanvas_set_stroke_color(my_vgcanvas_t* vg,
                                                    my_color_t color) {
  return vg->vtable->set_stroke_color(vg, color);
}

static inline my_ret_t my_vgcanvas_set_line_width(my_vgcanvas_t* vg, float width) {
  return vg->vtable->set_line_width(vg, width);
}

static inline my_ret_t my_vgcanvas_fill_rect(my_vgcanvas_t* vg,
                                             const my_rectf_t* rect) {
  return vg->vtable->fill_rect(vg, rect);
}

static inline my_ret_t my_vgcanvas_stroke_rect(my_vgcanvas_t* vg,
                                               const my_rectf_t* rect) {
  return vg->vtable->stroke_rect(vg, rect);
}

static inline my_ret_t my_vgcanvas_fill_rounded_rect(my_vgcanvas_t* vg,
                                                     const my_rectf_t* rect,
                                                     float radius) {
  return vg->vtable->fill_rounded_rect(vg, rect, radius);
}

static inline my_ret_t my_vgcanvas_begin_path(my_vgcanvas_t* vg) {
  return vg->vtable->begin_path(vg);
}

static inline my_ret_t my_vgcanvas_move_to(my_vgcanvas_t* vg, float x, float y) {
  return vg->vtable->move_to(vg, x, y);
}

static inline my_ret_t my_vgcanvas_line_to(my_vgcanvas_t* vg, float x, float y) {
  return vg->vtable->line_to(vg, x, y);
}

/** @brief Cubic bezier (M19a); NOT_SUPPORTED when the backend has no
 * curve_to slot. */
static inline my_ret_t my_vgcanvas_curve_to(my_vgcanvas_t* vg, float cx1,
                                            float cy1, float cx2, float cy2,
                                            float x, float y) {
  if (vg->vtable->curve_to == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  return vg->vtable->curve_to(vg, cx1, cy1, cx2, cy2, x, y);
}

static inline my_ret_t my_vgcanvas_close_path(my_vgcanvas_t* vg) {
  return vg->vtable->close_path(vg);
}

static inline my_ret_t my_vgcanvas_fill(my_vgcanvas_t* vg) {
  return vg->vtable->fill(vg);
}

static inline my_ret_t my_vgcanvas_stroke(my_vgcanvas_t* vg) {
  return vg->vtable->stroke(vg);
}

static inline my_ret_t my_vgcanvas_draw_text(my_vgcanvas_t* vg, const char* text,
                                             float x, float y) {
  return vg->vtable->draw_text(vg, text, x, y);
}

static inline void my_vgcanvas_destroy(my_vgcanvas_t* vg) {
  if (vg != NULL) {
    vg->vtable->destroy(vg);
  }
}

static inline my_ret_t my_vgcanvas_set_font(my_vgcanvas_t* vg, my_font_t* font,
                                            int32_t size) {
  return vg->vtable->set_font(vg, font, size);
}

static inline my_ret_t my_vgcanvas_measure_text(my_vgcanvas_t* vg,
                                                const char* text, int32_t* w,
                                                int32_t* h) {
  return vg->vtable->measure_text(vg, text, w, h);
}

static inline my_ret_t my_vgcanvas_draw_image(my_vgcanvas_t* vg,
                                              const uint8_t* rgba, int32_t w,
                                              int32_t h, const my_rectf_t* dst,
                                              const my_color_t* bg) {
  return vg->vtable->draw_image(vg, rgba, w, h, dst, bg);
}

static inline my_ret_t my_vgcanvas_set_line_cap(my_vgcanvas_t* vg,
                                                my_line_cap_t cap) {
  return vg->vtable->set_line_cap(vg, cap);
}

static inline my_ret_t my_vgcanvas_set_line_join(my_vgcanvas_t* vg,
                                                 my_line_join_t join) {
  return vg->vtable->set_line_join(vg, join);
}

/** @brief Replace (not intersect) the clip; NOT_SUPPORTED when the
 * backend has no reset_clip slot (M25). */
static inline my_ret_t my_vgcanvas_reset_clip(my_vgcanvas_t* vg,
                                              const my_rectf_t* rect) {
  if (vg->vtable->reset_clip == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  return vg->vtable->reset_clip(vg, rect);
}

static inline my_ret_t my_vgcanvas_set_scale(my_vgcanvas_t* vg, float scale) {
  if (vg == NULL || vg->vtable->set_scale == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  return vg->vtable->set_scale(vg, scale);
}

static inline my_ret_t my_vgcanvas_set_antialias_level(my_vgcanvas_t* vg,
                                                       int level) {
  if (vg == NULL || vg->vtable->set_antialias_level == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  return vg->vtable->set_antialias_level(vg, level);
}

static inline my_ret_t my_vgcanvas_set_scale_filter(my_vgcanvas_t* vg,
                                                     my_scale_filter_t filter) {
  if (vg == NULL || vg->vtable->set_scale_filter == NULL) {
    return MY_RET_NOT_SUPPORTED;
  }
  return vg->vtable->set_scale_filter(vg, filter);
}

#endif /* MY_VGCANVAS_H */
