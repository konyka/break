/**
 * @file my_vgcanvas.h
 * @brief 2D vector canvas abstract interface — vtable (frozen in M1).
 *
 * All widget rendering goes through this interface. Backends:
 * my_vgcanvas_soft (software rasterizer on an lcd, M1); later GLES /
 * Metal / WebGL implement the same vtable so widget code never changes.
 *
 * Semantics:
 *  - Coordinates are float "user space". Translation and device scale are
 *    part of the portable state; rotation is intentionally not exposed.
 *  - State = fill/stroke color, line width, translate, clip. save/restore
 *    form a stack; clip_rect always intersects with the current clip.
 *  - Path: begin_path/move_to/line_to/close_path build subpaths; fill()
 *    rasterizes with the EVEN-ODD rule, stroke() draws the polyline(s).
 *  - Anti-aliasing, alpha blending, image filtering, and text are backend
 *    capabilities. Query my_vgcanvas_get_capabilities() before selecting
 *    quality; unsupported controls return MY_RET_NOT_SUPPORTED and failed
 *    changes do not alter the active state.
 */
#ifndef MY_VGCANVAS_H
#define MY_VGCANVAS_H

#include "myc/my_error.h"
#include "myr/my_color.h"
#include "myr/my_font.h"
#include "myr/my_rect.h"
#include "myr/my_text_layout.h"
#include "myr/my_ui_metrics.h"

#include <math.h>

typedef struct my_vgcanvas_t my_vgcanvas_t;

/** @brief Stroke cap style (M9c). */
typedef enum my_line_cap_t {
  MY_LINE_CAP_BUTT = 0,
  MY_LINE_CAP_ROUND,
  MY_LINE_CAP_SQUARE
} my_line_cap_t;

/** @brief Stroke join style (M9c). */
typedef enum my_line_join_t {
  MY_LINE_JOIN_MITER = 0,
  MY_LINE_JOIN_ROUND,
  MY_LINE_JOIN_BEVEL
} my_line_join_t;

/** @brief Image scaling filter (draw_image, M9b). */
typedef enum my_scale_filter_t {
  MY_SCALE_FILTER_NEAREST = 0,
  MY_SCALE_FILTER_BILINEAR
} my_scale_filter_t;

#define MY_VGCANVAS_AA_LEVEL_BIT(level) (1u << (level))
#define MY_VGCANVAS_FILTER_BIT(filter) (1u << (filter))

typedef struct my_vgcanvas_capabilities_t {
  uint32_t antialias_levels; /**< bitset of supported levels 0..2 */
  uint32_t scale_filters; /**< bitset of supported my_scale_filter_t values */
  uint8_t active_antialias_level; /**< last successfully activated level */
  my_scale_filter_t active_scale_filter; /**< last successfully activated filter */
} my_vgcanvas_capabilities_t;

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

  /** @brief Draw text using the installed font and layout backend. */
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
   * @brief Blit an RGBA8888 image into dst (user space), using the current
   * image scale filter. When bg != NULL each source pixel is first composited over bg
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
   * @brief Stroke cap/join styles. All bundled backends use the same bounded
   * geometry contract: butt/round/square caps and miter/round/bevel joins.
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
  /** @brief Select image filtering; nearest and bilinear are portable GPU options. */
  my_ret_t (*set_scale_filter)(my_vgcanvas_t* vg, my_scale_filter_t filter);
} my_vgcanvas_vtable_t;

/** @brief vgcanvas base "class": first member of every backend. */
struct my_vgcanvas_t {
  const my_vgcanvas_vtable_t* vtable;
  my_vgcanvas_capabilities_t capabilities;
  const my_font_shape_params_t* active_shape_params;
};

static inline const my_font_shape_params_t* my_vgcanvas_shape_params(
    const my_vgcanvas_t* vg) {
  return vg != NULL ? vg->active_shape_params : NULL;
}

static inline my_ret_t my_vgcanvas_shape_font(
    my_vgcanvas_t* vg, my_font_t* font, const char* text, int32_t size,
    bool rtl, const my_allocator_t* allocator,
    my_font_shape_result_t* result) {
  my_font_shape_params_t defaults = {rtl, 0u, NULL, NULL};
  const my_font_shape_params_t* params = my_vgcanvas_shape_params(vg);
  return my_font_shape_ex(font, text, size,
                          params != NULL ? params : &defaults, allocator,
                          result);
}

static inline my_ret_t my_vgcanvas_shape_layout(
    my_vgcanvas_t* vg, const my_text_layout_t* layout, const char* text,
    my_font_t* font, int32_t size, const my_allocator_t* allocator,
    my_font_shape_result_t* result) {
  const my_font_shape_params_t* params = my_vgcanvas_shape_params(vg);
  if (params != NULL) {
    return my_text_layout_shape_ex(layout, text, font, size, params,
                                   allocator, result);
  }
  return my_text_layout_shape(layout, text, font, size, allocator, result);
}

/** @brief Read immutable backend capabilities and current quality state. */
static inline my_ret_t my_vgcanvas_get_capabilities(
    const my_vgcanvas_t* vg, my_vgcanvas_capabilities_t* out) {
  if (vg == NULL || out == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  *out = vg->capabilities;
  return MY_RET_OK;
}

#define MY_VGCANVAS_REQUIRE_SLOT(canvas, slot)                              \
  do {                                                                      \
    if ((canvas) == NULL || (canvas)->vtable == NULL)                       \
      return MY_RET_INVALID_PARAMS;                                        \
    if ((canvas)->vtable->slot == NULL) return MY_RET_NOT_SUPPORTED;        \
  } while (0)

static inline bool my_vgcanvas_finite_float(float value) {
  return isfinite(value) != 0;
}

static inline bool my_vgcanvas_finite_rect(const my_rectf_t* rect) {
  return rect != NULL && my_vgcanvas_finite_float(rect->x) &&
         my_vgcanvas_finite_float(rect->y) &&
         my_vgcanvas_finite_float(rect->w) &&
         my_vgcanvas_finite_float(rect->h);
}

static inline my_ret_t my_vgcanvas_begin_frame(my_vgcanvas_t* vg,
                                               const my_rect_t* dirty) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, begin_frame);
  {
    my_ret_t ret = vg->vtable->begin_frame(vg, dirty);
    if (ret == MY_RET_OK) my_ui_metrics_begin_frame();
    return ret;
  }
}

static inline my_ret_t my_vgcanvas_end_frame(my_vgcanvas_t* vg) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, end_frame);
  {
    my_ret_t ret = vg->vtable->end_frame(vg);
    if (ret == MY_RET_OK) {
      my_ui_metrics_end_frame();
    } else {
      my_ui_metrics_abort_frame();
    }
    return ret;
  }
}

static inline my_ret_t my_vgcanvas_save(my_vgcanvas_t* vg) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, save);
  return vg->vtable->save(vg);
}

static inline my_ret_t my_vgcanvas_restore(my_vgcanvas_t* vg) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, restore);
  return vg->vtable->restore(vg);
}

static inline my_ret_t my_vgcanvas_translate(my_vgcanvas_t* vg, float dx, float dy) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, translate);
  if (!my_vgcanvas_finite_float(dx) || !my_vgcanvas_finite_float(dy))
    return MY_RET_INVALID_PARAMS;
  return vg->vtable->translate(vg, dx, dy);
}

static inline my_ret_t my_vgcanvas_clip_rect(my_vgcanvas_t* vg,
                                             const my_rectf_t* rect) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, clip_rect);
  if (!my_vgcanvas_finite_rect(rect)) return MY_RET_INVALID_PARAMS;
  return vg->vtable->clip_rect(vg, rect);
}

static inline my_ret_t my_vgcanvas_set_fill_color(my_vgcanvas_t* vg,
                                                  my_color_t color) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, set_fill_color);
  return vg->vtable->set_fill_color(vg, color);
}

static inline my_ret_t my_vgcanvas_set_stroke_color(my_vgcanvas_t* vg,
                                                    my_color_t color) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, set_stroke_color);
  return vg->vtable->set_stroke_color(vg, color);
}

static inline my_ret_t my_vgcanvas_set_line_width(my_vgcanvas_t* vg, float width) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, set_line_width);
  if (!my_vgcanvas_finite_float(width) || width <= 0.0f)
    return MY_RET_INVALID_PARAMS;
  return vg->vtable->set_line_width(vg, width);
}

static inline my_ret_t my_vgcanvas_fill_rect(my_vgcanvas_t* vg,
                                             const my_rectf_t* rect) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, fill_rect);
  if (!my_vgcanvas_finite_rect(rect)) return MY_RET_INVALID_PARAMS;
  {
    my_ret_t ret = vg->vtable->fill_rect(vg, rect);
    if (ret == MY_RET_OK) my_ui_metrics_record_draw_call();
    return ret;
  }
}

static inline my_ret_t my_vgcanvas_stroke_rect(my_vgcanvas_t* vg,
                                               const my_rectf_t* rect) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, stroke_rect);
  if (!my_vgcanvas_finite_rect(rect)) return MY_RET_INVALID_PARAMS;
  {
    my_ret_t ret = vg->vtable->stroke_rect(vg, rect);
    if (ret == MY_RET_OK) my_ui_metrics_record_draw_call();
    return ret;
  }
}

static inline my_ret_t my_vgcanvas_fill_rounded_rect(my_vgcanvas_t* vg,
                                                     const my_rectf_t* rect,
                                                     float radius) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, fill_rounded_rect);
  if (!my_vgcanvas_finite_rect(rect) || !my_vgcanvas_finite_float(radius) ||
      radius < 0.0f)
    return MY_RET_INVALID_PARAMS;
  {
    my_ret_t ret = vg->vtable->fill_rounded_rect(vg, rect, radius);
    if (ret == MY_RET_OK) my_ui_metrics_record_draw_call();
    return ret;
  }
}

static inline my_ret_t my_vgcanvas_begin_path(my_vgcanvas_t* vg) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, begin_path);
  return vg->vtable->begin_path(vg);
}

static inline my_ret_t my_vgcanvas_move_to(my_vgcanvas_t* vg, float x, float y) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, move_to);
  if (!my_vgcanvas_finite_float(x) || !my_vgcanvas_finite_float(y))
    return MY_RET_INVALID_PARAMS;
  return vg->vtable->move_to(vg, x, y);
}

static inline my_ret_t my_vgcanvas_line_to(my_vgcanvas_t* vg, float x, float y) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, line_to);
  if (!my_vgcanvas_finite_float(x) || !my_vgcanvas_finite_float(y))
    return MY_RET_INVALID_PARAMS;
  return vg->vtable->line_to(vg, x, y);
}

/** @brief Cubic bezier (M19a); NOT_SUPPORTED when the backend has no
 * curve_to slot. */
static inline my_ret_t my_vgcanvas_curve_to(my_vgcanvas_t* vg, float cx1,
                                            float cy1, float cx2, float cy2,
                                            float x, float y) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, curve_to);
  if (!my_vgcanvas_finite_float(cx1) || !my_vgcanvas_finite_float(cy1) ||
      !my_vgcanvas_finite_float(cx2) || !my_vgcanvas_finite_float(cy2) ||
      !my_vgcanvas_finite_float(x) || !my_vgcanvas_finite_float(y))
    return MY_RET_INVALID_PARAMS;
  return vg->vtable->curve_to(vg, cx1, cy1, cx2, cy2, x, y);
}

static inline my_ret_t my_vgcanvas_close_path(my_vgcanvas_t* vg) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, close_path);
  return vg->vtable->close_path(vg);
}

static inline my_ret_t my_vgcanvas_fill(my_vgcanvas_t* vg) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, fill);
  {
    my_ret_t ret = vg->vtable->fill(vg);
    if (ret == MY_RET_OK) my_ui_metrics_record_draw_call();
    return ret;
  }
}

static inline my_ret_t my_vgcanvas_stroke(my_vgcanvas_t* vg) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, stroke);
  {
    my_ret_t ret = vg->vtable->stroke(vg);
    if (ret == MY_RET_OK) my_ui_metrics_record_draw_call();
    return ret;
  }
}

static inline my_ret_t my_vgcanvas_draw_text(my_vgcanvas_t* vg, const char* text,
                                             float x, float y) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, draw_text);
  if (!my_vgcanvas_finite_float(x) || !my_vgcanvas_finite_float(y))
    return MY_RET_INVALID_PARAMS;
  {
    my_ret_t ret = vg->vtable->draw_text(vg, text, x, y);
    if (ret == MY_RET_OK) my_ui_metrics_record_draw_call();
    return ret;
  }
}

static inline my_ret_t my_vgcanvas_draw_text_ex(
    my_vgcanvas_t* vg, const char* text, float x, float y,
    const my_font_shape_params_t* params) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, draw_text);
  if (!my_vgcanvas_finite_float(x) || !my_vgcanvas_finite_float(y))
    return MY_RET_INVALID_PARAMS;
  const my_font_shape_params_t* previous = vg->active_shape_params;
  my_ret_t ret;
  vg->active_shape_params = params;
  ret = vg->vtable->draw_text(vg, text, x, y);
  vg->active_shape_params = previous;
  if (ret == MY_RET_OK) my_ui_metrics_record_draw_call();
  return ret;
}

static inline void my_vgcanvas_destroy(my_vgcanvas_t* vg) {
  if (vg != NULL && vg->vtable != NULL && vg->vtable->destroy != NULL) {
    vg->vtable->destroy(vg);
  }
}

static inline my_ret_t my_vgcanvas_set_font(my_vgcanvas_t* vg, my_font_t* font,
                                            int32_t size) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, set_font);
  if (size <= 0) return MY_RET_INVALID_PARAMS;
  return vg->vtable->set_font(vg, font, size);
}

static inline my_ret_t my_vgcanvas_measure_text(my_vgcanvas_t* vg,
                                                const char* text, int32_t* w,
                                                int32_t* h) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, measure_text);
  return vg->vtable->measure_text(vg, text, w, h);
}

static inline my_ret_t my_vgcanvas_measure_text_ex(
    my_vgcanvas_t* vg, const char* text, int32_t* w, int32_t* h,
    const my_font_shape_params_t* params) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, measure_text);
  const my_font_shape_params_t* previous = vg->active_shape_params;
  my_ret_t ret;
  vg->active_shape_params = params;
  ret = vg->vtable->measure_text(vg, text, w, h);
  vg->active_shape_params = previous;
  return ret;
}

static inline my_ret_t my_vgcanvas_draw_image(my_vgcanvas_t* vg,
                                              const uint8_t* rgba, int32_t w,
                                              int32_t h, const my_rectf_t* dst,
                                              const my_color_t* bg) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, draw_image);
  if (!my_vgcanvas_finite_rect(dst)) return MY_RET_INVALID_PARAMS;
  {
    my_ret_t ret = vg->vtable->draw_image(vg, rgba, w, h, dst, bg);
    if (ret == MY_RET_OK) my_ui_metrics_record_draw_call();
    return ret;
  }
}

static inline my_ret_t my_vgcanvas_set_line_cap(my_vgcanvas_t* vg,
                                                my_line_cap_t cap) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, set_line_cap);
  if (cap != MY_LINE_CAP_BUTT && cap != MY_LINE_CAP_ROUND &&
      cap != MY_LINE_CAP_SQUARE)
    return MY_RET_INVALID_PARAMS;
  return vg->vtable->set_line_cap(vg, cap);
}

static inline my_ret_t my_vgcanvas_set_line_join(my_vgcanvas_t* vg,
                                                 my_line_join_t join) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, set_line_join);
  if (join != MY_LINE_JOIN_MITER && join != MY_LINE_JOIN_ROUND &&
      join != MY_LINE_JOIN_BEVEL)
    return MY_RET_INVALID_PARAMS;
  return vg->vtable->set_line_join(vg, join);
}

/** @brief Replace (not intersect) the clip; NOT_SUPPORTED when the
 * backend has no reset_clip slot (M25). */
static inline my_ret_t my_vgcanvas_reset_clip(my_vgcanvas_t* vg,
                                              const my_rectf_t* rect) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, reset_clip);
  if (!my_vgcanvas_finite_rect(rect)) return MY_RET_INVALID_PARAMS;
  return vg->vtable->reset_clip(vg, rect);
}

static inline my_ret_t my_vgcanvas_set_scale(my_vgcanvas_t* vg, float scale) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, set_scale);
  if (!my_vgcanvas_finite_float(scale) || scale <= 0.0f)
    return MY_RET_INVALID_PARAMS;
  return vg->vtable->set_scale(vg, scale);
}

static inline my_ret_t my_vgcanvas_set_antialias_level(my_vgcanvas_t* vg,
                                                       int level) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, set_antialias_level);
  if (level < 0 || level > 2) {
    return MY_RET_INVALID_PARAMS;
  }
  if ((vg->capabilities.antialias_levels &
       MY_VGCANVAS_AA_LEVEL_BIT(level)) == 0u) {
    return MY_RET_NOT_SUPPORTED;
  }
  if (vg->capabilities.active_antialias_level == (uint8_t)level) {
    return MY_RET_OK;
  }
  {
    my_ret_t ret = vg->vtable->set_antialias_level(vg, level);
    if (ret == MY_RET_OK) {
      vg->capabilities.active_antialias_level = (uint8_t)level;
    }
    return ret;
  }
}

static inline my_ret_t my_vgcanvas_set_scale_filter(my_vgcanvas_t* vg,
                                                     my_scale_filter_t filter) {
  MY_VGCANVAS_REQUIRE_SLOT(vg, set_scale_filter);
  if (filter != MY_SCALE_FILTER_NEAREST &&
      filter != MY_SCALE_FILTER_BILINEAR) {
    return MY_RET_INVALID_PARAMS;
  }
  if ((vg->capabilities.scale_filters & MY_VGCANVAS_FILTER_BIT(filter)) ==
      0u) {
    return MY_RET_NOT_SUPPORTED;
  }
  if (vg->capabilities.active_scale_filter == filter) {
    return MY_RET_OK;
  }
  {
    my_ret_t ret = vg->vtable->set_scale_filter(vg, filter);
    if (ret == MY_RET_OK) {
      vg->capabilities.active_scale_filter = filter;
    }
    return ret;
  }
}

#undef MY_VGCANVAS_REQUIRE_SLOT

#endif /* MY_VGCANVAS_H */
