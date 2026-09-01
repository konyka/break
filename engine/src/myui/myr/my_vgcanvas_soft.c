/**
 * @file my_vgcanvas_soft.c
 * @brief Software rasterizer vgcanvas backend.
 *
 * Rasterization notes:
 *  - Path fill: scanline even-odd rule over ALL subpaths (a half-open
 *    [y0, y1) edge test avoids double-counted vertices); correct for
 *    concave and self-intersecting polygons; nested contours punch holes.
 *  - Stroke: Bresenham line per segment with a square line_width brush —
 *    a deliberate 1px/integer-width approximation, no joins/caps yet.
 *  - Rounded rect: 3 body rects + 4 scanline-filled quarter circles.
 *  - No anti-aliasing, no alpha blending (documented in my_vgcanvas.h).
 */
#include "myr/my_vgcanvas_soft.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "myr/my_bezier.h"
#include "myr/my_text_layout.h"

typedef struct soft_state_t {
  my_color_t fill_color;
  my_color_t stroke_color;
  float line_width;
  float tx;
  float ty;
  float scale; /* device = (user + translate) * scale (M12c HiDPI; 1) */
  my_rect_t clip; /* device coordinates */
  my_font_t* font;     /**< borrowed; NULL = no text */
  int32_t font_size;
  my_line_cap_t line_cap;
  my_line_join_t line_join;
} soft_state_t;

/** @brief User -> device coordinate macros (M12c). */
#define SOFT_SX(s, x) (((x) + (s)->state.tx) * (s)->state.scale)
#define SOFT_SY(s, y) (((y) + (s)->state.ty) * (s)->state.scale)

typedef struct path_point_t {
  float x;
  float y;
} path_point_t;

typedef struct contour_t {
  size_t start;  /**< index into points[] */
  size_t count;  /**< number of points */
  bool closed;   /**< close_path() was called */
} contour_t;

typedef struct my_vgcanvas_soft_t {
  my_vgcanvas_t base;
  const my_allocator_t* allocator;
  my_lcd_t* lcd; /* borrowed */
  soft_state_t state;

  soft_state_t* stack;
  size_t stack_count;
  size_t stack_cap;

  path_point_t* points;
  size_t point_count;
  size_t point_cap;

  contour_t* contours;
  size_t contour_count;
  size_t contour_cap;

  my_dirty_rects_t dirty;
  int antialias_level; /**< 0=off 1=x4 2=x4*y2 (M8c, default 2) */
  my_scale_filter_t scale_filter; /**< draw_image sampling (M9b) */
} my_vgcanvas_soft_t;

/* ---------------- growable arrays ---------------- */

static my_ret_t soft_grow(const my_allocator_t* alloc, void** arr, size_t* cap,
                          size_t need, size_t elem_size) {
  void* p;
  size_t new_cap = *cap > 0 ? *cap : 16;
  if (need <= *cap) {
    return MY_RET_OK;
  }
  while (new_cap < need) {
    new_cap *= 2;
  }
  p = my_mem_realloc(alloc, *arr, new_cap * elem_size);
  if (p == NULL) {
    return MY_RET_OOM;
  }
  *arr = p;
  *cap = new_cap;
  return MY_RET_OK;
}

/* ---------------- drawing helpers ---------------- */

static int32_t soft_round(float v) {
  return (int32_t)floorf(v + 0.5f);
}

/** @brief Fill a device-space rect, clipped to the current clip; tracked dirty. */
static void soft_fill_device_rect(my_vgcanvas_soft_t* s, my_rect_t r,
                                  my_color_t color) {
  my_rect_t clipped;
  if (my_rect_intersect(&r, &s->state.clip, &clipped)) {
    my_lcd_fill_rect(s->lcd, &clipped, color);
    my_dirty_rects_add(&s->dirty, &clipped);
  }
}

/* ---------------- coverage anti-aliasing (M7c x, M8c +y) ----------------
 * AA levels: 0 = off (pixel-center hard edges, M1 behavior),
 * 1 = x-direction 4x subsampling (subsample centers (2k+1)/8),
 * 2 = x4 x y2 (scanline evaluated at +0.25 and +0.75). Edge pixels blend
 * src-over with alpha = color.a * cov / maxcov. Axis-aligned straight
 * edges always have full coverage (no visual/perf regression).
 */

/** @brief Coverage 0..4 of a left-edge pixel whose fraction is f. */
static int cov_left(float f) {
  int k, n = 0;
  for (k = 0; k < 4; k++) {
    if ((float)(2 * k + 1) / 8.0f >= f) {
      n++;
    }
  }
  return n;
}

/** @brief Coverage 0..4 of a right-edge pixel whose fraction is f. */
static int cov_right(float f) {
  int k, n = 0;
  for (k = 0; k < 4; k++) {
    if ((float)(2 * k + 1) / 8.0f <= f) {
      n++;
    }
  }
  return n;
}

static int float_cmp(const void* a, const void* b);

/** @brief Per-row coverage/alpha buffers for one fill call. */
typedef struct aa_rowbuf_t {
  uint8_t* cov;
  uint8_t* alpha;
} aa_rowbuf_t;

static void aa_add(uint8_t* cov, int32_t idx, int n) {
  int v = cov[idx] + n;
  cov[idx] = (uint8_t)(v > 8 ? 8 : v);
}

/** @brief Accumulate x-coverage (0..4 per pixel) of span [xl,xr] into cov. */
static void span_accum(uint8_t* cov, int32_t base_x,
                       int32_t width, float xl, float xr) {
  int32_t x0 = base_x, x1 = base_x + width;
  float fxl, fxr;
  int32_t lpix, rpix, p;
  if (xr <= xl) {
    return;
  }
  fxl = xl - floorf(xl);
  fxr = xr - floorf(xr);
  lpix = (int32_t)floorf(xl);
  rpix = (int32_t)floorf(xr);
  if (lpix == rpix) {
    int k, n = 0;
    for (k = 0; k < 4; k++) {
      float c = (float)(2 * k + 1) / 8.0f;
      if (c >= fxl && c <= fxr) {
        n++;
      }
    }
    if (lpix >= x0 && lpix < x1) {
      aa_add(cov, lpix - x0, n);
    }
    return;
  }
  if (lpix >= x0 && lpix < x1) {
    aa_add(cov, lpix - x0, cov_left(fxl));
  }
  for (p = lpix + 1; p <= rpix - 1; p++) {
    if (p >= x0 && p < x1) {
      aa_add(cov, p - x0, 4);
    }
  }
  if (fxr > 0.0f && rpix >= x0 && rpix < x1) {
    aa_add(cov, rpix - x0, cov_right(fxr));
  }
}

/** @brief Emit one device row from the coverage buffer. */
static void emit_row(my_vgcanvas_soft_t* s, aa_rowbuf_t* rb, int32_t y,
                     int32_t base_x, int32_t width, int maxcov,
                     my_color_t color) {
  int32_t i = 0;
  int32_t first = -1, last = -1;
  while (i < width) {
    if (rb->cov[i] == 0) {
      i++;
      continue;
    }
    if ((int)rb->cov[i] == maxcov) {
      int32_t start = i;
      while (i < width && (int)rb->cov[i] == maxcov) {
        i++;
      }
      soft_fill_device_rect(s, my_rect_init(base_x + start, y, i - start, 1),
                            color);
      if (first < 0) {
        first = start;
      }
      last = i;
    } else {
      int32_t start = i, n = 0;
      while (i < width && rb->cov[i] > 0 && (int)rb->cov[i] < maxcov) {
        rb->alpha[n++] = (uint8_t)((color.a * rb->cov[i]) / maxcov);
        i++;
      }
      if (n > 0) {
        my_lcd_blend_span(s->lcd, base_x + start, y, rb->alpha, n, color);
      }
      if (first < 0) {
        first = start;
      }
      last = i;
    }
  }
  if (first >= 0) {
    my_dirty_rects_add(&s->dirty, &(my_rect_t){base_x + first, y,
                                               last - first, 1});
  }
}

/** @brief Collect even-odd scanline intersections at yc (device space). */
static size_t collect_intersections(my_vgcanvas_soft_t* s,
                                    const path_point_t* pts,
                                    const contour_t* contours,
                                    size_t ncontours, float yc, float* xs,
                                    size_t cap, bool close_open) {
  size_t nxs = 0, ci, i;
  for (ci = 0; ci < ncontours; ci++) {
    const contour_t* c = &contours[ci];
    for (i = 0; i < c->count; i++) {
      size_t j = i + 1;
      float x0, y0, x1, y1;
      if (j == c->count) {
        if (!c->closed && !close_open) {
          break;
        }
        j = 0;
      }
      x0 = SOFT_SX(s, pts[c->start + i].x);
      y0 = SOFT_SY(s, pts[c->start + i].y);
      x1 = SOFT_SX(s, pts[c->start + j].x);
      y1 = SOFT_SY(s, pts[c->start + j].y);
      if ((y0 <= yc) != (y1 <= yc) && nxs < cap) {
        xs[nxs++] = x0 + (yc - y0) * (x1 - x0) / (y1 - y0);
      }
    }
  }
  return nxs;
}

/**
 * @brief Fill a set of polygon contours (even-odd) with the current AA
 * level. Core of soft_fill/soft_stroke (M8c: shared).
 */
static my_ret_t fill_polys(my_vgcanvas_soft_t* s, const path_point_t* pts,
                           size_t npts, const contour_t* contours,
                           size_t ncontours, my_color_t color) {
  const my_rect_t* clip = &s->state.clip;
  float* xs;
  size_t xs_cap;
  int32_t y;
  if (npts < 2 || ncontours == 0 || clip->w <= 0 || clip->h <= 0) {
    return MY_RET_OK;
  }
  xs_cap = npts;
  xs = (float*)my_mem_alloc(s->allocator, xs_cap * sizeof(float));
  if (xs == NULL) {
    return MY_RET_OOM;
  }
  if (s->antialias_level <= 0) {
    /* hard edges: pixel-center rule */
    for (y = clip->y; y < clip->y + clip->h; y++) {
      size_t nxs = collect_intersections(s, pts, contours, ncontours,
                                         (float)y + 0.5f, xs, xs_cap, true);
      size_t k;
      qsort(xs, nxs, sizeof(float), float_cmp);
      for (k = 0; k + 1 < nxs; k += 2) {
        int32_t xa = (int32_t)ceilf(xs[k] - 0.5f);
        int32_t xb = (int32_t)ceilf(xs[k + 1] - 0.5f);
        if (xb > xa) {
          soft_fill_device_rect(s, my_rect_init(xa, y, xb - xa, 1), color);
        }
      }
    }
  } else {
    aa_rowbuf_t rb;
    int halves = s->antialias_level >= 2 ? 2 : 1;
    static const float OFF1[1] = {0.5f};
    static const float OFF2[2] = {0.25f, 0.75f};
    const float* offs = halves == 2 ? OFF2 : OFF1;
    rb.cov = (uint8_t*)my_mem_alloc(s->allocator, (size_t)clip->w * 2);
    if (rb.cov == NULL) {
      my_mem_free(s->allocator, xs);
      return MY_RET_OOM;
    }
    rb.alpha = rb.cov + clip->w;
    {
      /* limit the scan to the polygon's y range (clipped); the range
       * must be in DEVICE space like collect_intersections (M23: it used
       * y+ty without the scale, emptying the fill at scale != 1) */
      float ymin = SOFT_SY(s, pts[0].y), ymax = ymin;
      size_t pi;
      int32_t row0, row1;
      for (pi = 1; pi < npts; pi++) {
        float py = SOFT_SY(s, pts[pi].y);
        if (py < ymin) {
          ymin = py;
        }
        if (py > ymax) {
          ymax = py;
        }
      }
      row0 = (int32_t)floorf(ymin) > clip->y ? (int32_t)floorf(ymin) : clip->y;
      row1 = (int32_t)ceilf(ymax) < clip->y + clip->h ? (int32_t)ceilf(ymax)
                                                      : clip->y + clip->h;
      for (y = row0; y < row1; y++) {
      float row_min = 0.0f, row_max = 0.0f;
      int32_t bx0, bw;
      int hh;
      row_min = (float)(clip->x + clip->w);
      row_max = (float)clip->x;
      for (hh = 0; hh < halves; hh++) {
        size_t nxs = collect_intersections(s, pts, contours, ncontours,
                                           (float)y + offs[hh], xs, xs_cap,
                                           true);
        if (nxs > 0) {
          qsort(xs, nxs, sizeof(float), float_cmp);
          if (xs[0] < row_min) {
            row_min = xs[0];
          }
          if (xs[nxs - 1] > row_max) {
            row_max = xs[nxs - 1];
          }
        }
      }
      if (row_max <= row_min) {
        continue;
      }
      bx0 = (int32_t)floorf(row_min);
      if (bx0 < clip->x) {
        bx0 = clip->x;
      }
      bw = (int32_t)ceilf(row_max) - bx0;
      if (bx0 + bw > clip->x + clip->w) {
        bw = clip->x + clip->w - bx0;
      }
      if (bw <= 0) {
        continue;
      }
      memset(rb.cov, 0, (size_t)bw);
      for (hh = 0; hh < halves; hh++) {
        size_t nxs = collect_intersections(s, pts, contours, ncontours,
                                           (float)y + offs[hh], xs, xs_cap,
                                           true);
        size_t k;
        qsort(xs, nxs, sizeof(float), float_cmp);
        for (k = 0; k + 1 < nxs; k += 2) {
          span_accum(rb.cov, bx0, bw, xs[k], xs[k + 1]);
        }
      }
      emit_row(s, &rb, y, bx0, bw, 4 * halves, color);
      }
    }
    my_mem_free(s->allocator, rb.cov);
  }
  my_mem_free(s->allocator, xs);
  return MY_RET_OK;
}

/** @brief User-space rect -> device-space rect (origin floor, size exact). */
static my_rect_t soft_user_rect_to_device(const my_vgcanvas_soft_t* s,
                                          const my_rectf_t* r) {
  int32_t x0 = (int32_t)floorf(SOFT_SX(s, r->x));
  int32_t y0 = (int32_t)floorf(SOFT_SY(s, r->y));
  int32_t x1 = (int32_t)floorf(SOFT_SX(s, r->x + r->w));
  int32_t y1 = (int32_t)floorf(SOFT_SY(s, r->y + r->h));
  return my_rect_init(x0, y0, x1 - x0, y1 - y0);
}

/* ---------------- vtable: frame ---------------- */

static my_ret_t soft_begin_frame(my_vgcanvas_t* vg, const my_rect_t* dirty) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  my_dirty_rects_clear(&s->dirty);
  return my_lcd_begin_frame(s->lcd, dirty);
}

static my_ret_t soft_end_frame(my_vgcanvas_t* vg) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  return my_lcd_end_frame(s->lcd);
}

/* ---------------- vtable: state stack ---------------- */

static my_ret_t soft_save(my_vgcanvas_t* vg) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  my_ret_t ret = soft_grow(s->allocator, (void**)&s->stack, &s->stack_cap,
                           s->stack_count + 1, sizeof(soft_state_t));
  if (ret != MY_RET_OK) {
    return ret;
  }
  s->stack[s->stack_count++] = s->state;
  return MY_RET_OK;
}

static my_ret_t soft_restore(my_vgcanvas_t* vg) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  if (s->stack_count == 0) {
    return MY_RET_FAIL;
  }
  s->state = s->stack[--s->stack_count];
  return MY_RET_OK;
}

static my_ret_t soft_translate(my_vgcanvas_t* vg, float dx, float dy) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  s->state.tx += dx;
  s->state.ty += dy;
  return MY_RET_OK;
}

static my_ret_t soft_clip_rect(my_vgcanvas_t* vg, const my_rectf_t* rect) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  my_rect_t dev, clipped;
  if (rect == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  /* clip is inclusive: origin floors, far edge ceils */
  dev = my_rect_init((int32_t)floorf(SOFT_SX(s, rect->x)),
                     (int32_t)floorf(SOFT_SY(s, rect->y)),
                     (int32_t)ceilf(SOFT_SX(s, rect->x + rect->w)) -
                         (int32_t)floorf(SOFT_SX(s, rect->x)),
                     (int32_t)ceilf(SOFT_SY(s, rect->y + rect->h)) -
                         (int32_t)floorf(SOFT_SY(s, rect->y)));
  if (my_rect_intersect(&s->state.clip, &dev, &clipped)) {
    s->state.clip = clipped;
  } else {
    s->state.clip = my_rect_init(0, 0, 0, 0); /* empty clip */
  }
  return MY_RET_OK;
}

static my_ret_t soft_set_fill_color(my_vgcanvas_t* vg, my_color_t color) {
  ((my_vgcanvas_soft_t*)vg)->state.fill_color = color;
  return MY_RET_OK;
}

static my_ret_t soft_set_stroke_color(my_vgcanvas_t* vg, my_color_t color) {
  ((my_vgcanvas_soft_t*)vg)->state.stroke_color = color;
  return MY_RET_OK;
}

static my_ret_t soft_set_line_width(my_vgcanvas_t* vg, float width) {
  ((my_vgcanvas_soft_t*)vg)->state.line_width = width;
  return MY_RET_OK;
}

/* ---------------- vtable: rect primitives ---------------- */

static my_ret_t soft_fill_rect(my_vgcanvas_t* vg, const my_rectf_t* rect) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  if (rect == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  soft_fill_device_rect(s, soft_user_rect_to_device(s, rect), s->state.fill_color);
  return MY_RET_OK;
}

static my_ret_t soft_stroke_rect(my_vgcanvas_t* vg, const my_rectf_t* rect) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  my_rect_t r;
  int32_t lw;
  if (rect == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  r = soft_user_rect_to_device(s, rect);
  lw = soft_round(s->state.line_width);
  if (lw < 1) {
    lw = 1;
  }
  if (lw * 2 >= r.w || lw * 2 >= r.h) {
    /* degenerate: the stroke covers everything */
    soft_fill_device_rect(s, r, s->state.stroke_color);
    return MY_RET_OK;
  }
  soft_fill_device_rect(s, my_rect_init(r.x, r.y, r.w, lw), s->state.stroke_color);
  soft_fill_device_rect(s, my_rect_init(r.x, r.y + r.h - lw, r.w, lw),
                        s->state.stroke_color);
  soft_fill_device_rect(s, my_rect_init(r.x, r.y + lw, lw, r.h - 2 * lw),
                        s->state.stroke_color);
  soft_fill_device_rect(s, my_rect_init(r.x + r.w - lw, r.y + lw, lw, r.h - 2 * lw),
                        s->state.stroke_color);
  return MY_RET_OK;
}

/** @brief Scanline-filled circle of radius r centered at (cx, cy). */
static void soft_fill_circle(my_vgcanvas_soft_t* s, int32_t cx, int32_t cy,
                             int32_t r, my_color_t color) {
  int32_t dy;
  if (s->antialias_level <= 0) {
    for (dy = -r; dy <= r; dy++) {
      int32_t dx = (int32_t)floorf(sqrtf((float)(r * r - dy * dy)));
      soft_fill_device_rect(s, my_rect_init(cx - dx, cy + dy, 2 * dx + 1, 1),
                            color);
    }
    return;
  }
  {
    int halves = s->antialias_level >= 2 ? 2 : 1;
    static const float OFF1[1] = {0.5f};
    static const float OFF2[2] = {0.25f, 0.75f};
    const float* offs = halves == 2 ? OFF2 : OFF1;
    const my_rect_t* clip = &s->state.clip;
    int32_t y0 = cy - r > clip->y ? cy - r : clip->y;
    int32_t y1 = cy + r < clip->y + clip->h - 1 ? cy + r : clip->y + clip->h - 1;
    aa_rowbuf_t rb;
    int32_t y;
    if (clip->w <= 0) {
      return;
    }
    rb.cov = (uint8_t*)my_mem_alloc(s->allocator, (size_t)clip->w * 2);
    if (rb.cov == NULL) {
      return;
    }
    rb.alpha = rb.cov + clip->w;
    for (y = y0; y <= y1; y++) {
      int hh;
      float fx = (float)cx + 0.5f;
      int32_t bx0 = (int32_t)floorf(fx - (float)r);
      int32_t bw = (int32_t)ceilf(fx + (float)r) - bx0 + 1;
      if (bx0 < clip->x) {
        bw -= clip->x - bx0;
        bx0 = clip->x;
      }
      if (bx0 + bw > clip->x + clip->w) {
        bw = clip->x + clip->w - bx0;
      }
      if (bw <= 0) {
        continue;
      }
      memset(rb.cov, 0, (size_t)bw);
      for (hh = 0; hh < halves; hh++) {
        float fdy = (float)y + offs[hh] - ((float)cy + 0.5f);
        float fdx;
        if (fdy * fdy > (float)(r * r)) {
          continue;
        }
        fdx = sqrtf((float)(r * r) - fdy * fdy);
        span_accum(rb.cov, bx0, bw, fx - fdx, fx + fdx);
      }
      emit_row(s, &rb, y, bx0, bw, 4 * halves, color);
    }
    my_mem_free(s->allocator, rb.cov);
  }
}

static my_ret_t soft_fill_rounded_rect(my_vgcanvas_t* vg, const my_rectf_t* rect,
                                       float radius) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  my_rect_t r;
  int32_t ri;
  if (rect == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  r = soft_user_rect_to_device(s, rect);
  ri = soft_round(radius * s->state.scale);
  if (ri > r.w / 2) {
    ri = r.w / 2;
  }
  if (ri > r.h / 2) {
    ri = r.h / 2;
  }
  if (ri <= 0) {
    soft_fill_device_rect(s, r, s->state.fill_color);
    return MY_RET_OK;
  }
  /* body: full-height middle band + two side bands between the corners */
  soft_fill_device_rect(s, my_rect_init(r.x + ri, r.y, r.w - 2 * ri, r.h),
                        s->state.fill_color);
  soft_fill_device_rect(s, my_rect_init(r.x, r.y + ri, ri, r.h - 2 * ri),
                        s->state.fill_color);
  soft_fill_device_rect(s, my_rect_init(r.x + r.w - ri, r.y + ri, ri, r.h - 2 * ri),
                        s->state.fill_color);
  /* corners: quarter circles (full circles, overdrawing the body is fine) */
  soft_fill_circle(s, r.x + ri, r.y + ri, ri, s->state.fill_color);
  soft_fill_circle(s, r.x + r.w - ri - 1, r.y + ri, ri, s->state.fill_color);
  soft_fill_circle(s, r.x + ri, r.y + r.h - ri - 1, ri, s->state.fill_color);
  soft_fill_circle(s, r.x + r.w - ri - 1, r.y + r.h - ri - 1, ri,
                   s->state.fill_color);
  return MY_RET_OK;
}

/* ---------------- vtable: path ---------------- */

static my_ret_t soft_begin_path(my_vgcanvas_t* vg) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  s->point_count = 0;
  s->contour_count = 0;
  return MY_RET_OK;
}

static my_ret_t soft_move_to(my_vgcanvas_t* vg, float x, float y) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  my_ret_t ret = soft_grow(s->allocator, (void**)&s->contours, &s->contour_cap,
                           s->contour_count + 1, sizeof(contour_t));
  if (ret != MY_RET_OK) {
    return ret;
  }
  s->contours[s->contour_count].start = s->point_count;
  s->contours[s->contour_count].count = 0;
  s->contours[s->contour_count].closed = false;
  s->contour_count++;
  return my_vgcanvas_line_to(vg, x, y);
}

static my_ret_t soft_line_to(my_vgcanvas_t* vg, float x, float y) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  my_ret_t ret;
  if (s->contour_count == 0) {
    return soft_move_to(vg, x, y); /* implicit move_to */
  }
  ret = soft_grow(s->allocator, (void**)&s->points, &s->point_cap,
                  s->point_count + 1, sizeof(path_point_t));
  if (ret != MY_RET_OK) {
    return ret;
  }
  s->points[s->point_count].x = x;
  s->points[s->point_count].y = y;
  s->point_count++;
  s->contours[s->contour_count - 1].count++;
  return MY_RET_OK;
}

static my_ret_t soft_close_path(my_vgcanvas_t* vg) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  if (s->contour_count > 0) {
    s->contours[s->contour_count - 1].closed = true;
  }
  return MY_RET_OK;
}

/* ---------------- vtable: curve_to (M19a) ---------------- */

/** @brief Emit one subdivision endpoint as a line_to. */
static my_ret_t soft_bezier_emit(void* ctx, float x, float y) {
  return my_vgcanvas_line_to((my_vgcanvas_t*)ctx, x, y);
}

static my_ret_t soft_curve_to(my_vgcanvas_t* vg, float cx1, float cy1,
                              float cx2, float cy2, float x, float y) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  float x0 = 0.0f, y0 = 0.0f;
  if (s->contour_count == 0 ||
      s->contours[s->contour_count - 1].count == 0) {
    return MY_RET_FAIL; /* no current point (canvas convention: move
                         * first); documented in my_vgcanvas.h */
  }
  x0 = s->points[s->point_count - 1].x;
  y0 = s->points[s->point_count - 1].y;
  /* adaptive de Casteljau -> polyline -> the existing stroke strip/AA
   * path does the rest (fill of open beziers is a documented TODO) */
  return my_bezier_cubic_to_lines(x0, y0, cx1, cy1, cx2, cy2, x, y, 0.25f,
                                  16, soft_bezier_emit, vg, NULL);
}

static int float_cmp(const void* a, const void* b) {
  float fa = *(const float*)a;
  float fb = *(const float*)b;
  return fa < fb ? -1 : fa > fb ? 1 : 0;
}

/** @brief Fill one scanline (device y) with the even-odd rule. */
static my_ret_t soft_fill(my_vgcanvas_t* vg) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  return fill_polys(s, s->points, s->point_count, s->contours,
                    s->contour_count, s->state.fill_color);
}

/** @brief Disk piece for the union stroke (device space; span math
 * identical to soft_fill_circle for pixel parity). */
typedef struct stroke_disk_t {
  int32_t cx, cy, r;
} stroke_disk_t;

/** @brief Union-merge stroke fill (M11d, AA levels >= 1): all segment
 * quads and cap/join disks accumulate into ONE per-row coverage buffer
 * (saturating add capped at maxcov), so a pixel's effective alpha never
 * exceeds color.a -- the translucent joint over-blend of the per-piece
 * path is gone. Scope: one stroke() call; separate stroke() calls still
 * composite normally (documented). */
static my_ret_t soft_stroke_union(my_vgcanvas_soft_t* s, float half,
                                  float odd_off) {
  const my_rect_t* clip = &s->state.clip;
  size_t nquads = 0, ndisks = 0, ci, i;
  path_point_t* pts = NULL;
  contour_t* cs = NULL;
  stroke_disk_t* disks = NULL;
  size_t np = 0, nq = 0, nd = 0;
  int halves = s->antialias_level >= 2 ? 2 : 1;
  static const float OFF1[1] = {0.5f};
  static const float OFF2[2] = {0.25f, 0.75f};
  const float* offs = halves == 2 ? OFF2 : OFF1;
  aa_rowbuf_t rb;
  int32_t row0, row1, y;
  float ymin = 0.0f, ymax = 0.0f;
  my_ret_t ret = MY_RET_OOM;

  /* count pieces */
  for (ci = 0; ci < s->contour_count; ci++) {
    const contour_t* c = &s->contours[ci];
    size_t edges = c->count > 1 ? (c->closed ? c->count : c->count - 1) : 0;
    nquads += edges;
    if (c->count > 1 && !c->closed &&
        s->state.line_cap == MY_LINE_CAP_ROUND) {
      ndisks += 2;
    }
    if (s->state.line_join == MY_LINE_JOIN_ROUND && edges > 0) {
      ndisks += c->closed ? edges - 1 : edges;
    }
  }
  if (nquads == 0 && ndisks == 0) {
    return MY_RET_OK;
  }
  pts = (path_point_t*)my_mem_alloc(s->allocator,
                                    (nquads > 0 ? nquads : 1) * 4 *
                                        sizeof(path_point_t));
  cs = (contour_t*)my_mem_alloc(s->allocator,
                                (nquads > 0 ? nquads : 1) * sizeof(contour_t));
  disks = (stroke_disk_t*)my_mem_alloc(s->allocator,
                                       (ndisks > 0 ? ndisks : 1) *
                                           sizeof(stroke_disk_t));
  rb.cov = (uint8_t*)my_mem_alloc(s->allocator, (size_t)clip->w * 2);
  if (pts == NULL || cs == NULL || disks == NULL || rb.cov == NULL) {
    goto done;
  }
  rb.alpha = rb.cov + clip->w;

  /* build quads (user space + odd_off; collect_intersections adds the
   * translate, matching the fill path) and disks (device space) */
  for (ci = 0; ci < s->contour_count; ci++) {
    const contour_t* c = &s->contours[ci];
    size_t edges = c->count > 1 ? (c->closed ? c->count : c->count - 1) : 0;
    if (c->count > 1 && !c->closed &&
        s->state.line_cap == MY_LINE_CAP_ROUND) {
      int32_t r = (int32_t)(half * s->state.scale + 0.5f);
      size_t last = c->start + c->count - 1;
      disks[nd].cx = (int32_t)floorf(SOFT_SX(s, s->points[c->start].x) +
                                     odd_off);
      disks[nd].cy = (int32_t)floorf(SOFT_SY(s, s->points[c->start].y) +
                                     odd_off);
      disks[nd].r = r;
      nd++;
      disks[nd].cx =
          (int32_t)floorf(SOFT_SX(s, s->points[last].x) + odd_off);
      disks[nd].cy =
          (int32_t)floorf(SOFT_SY(s, s->points[last].y) + odd_off);
      disks[nd].r = r;
      nd++;
    }
    for (i = 0; i < edges; i++) {
      size_t j = (i + 1) % c->count;
      float x0 = s->points[c->start + i].x + odd_off;
      float y0 = s->points[c->start + i].y + odd_off;
      float x1 = s->points[c->start + j].x + odd_off;
      float y1 = s->points[c->start + j].y + odd_off;
      float dx = x1 - x0, dy = y1 - y0;
      float len = sqrtf(dx * dx + dy * dy);
      float nx, ny;
      contour_t* qc = &cs[nq];
      if (len < 0.001f) {
        nx = 0.0f;
        ny = 0.0f; /* zero-length: small square stamp */
        pts[np].x = x0 - half;
        pts[np].y = y0 - half;
        pts[np + 1].x = x0 + half;
        pts[np + 1].y = y0 - half;
        pts[np + 2].x = x0 + half;
        pts[np + 2].y = y0 + half;
        pts[np + 3].x = x0 - half;
        pts[np + 3].y = y0 + half;
      } else {
        nx = -dy / len * half;
        ny = dx / len * half;
        pts[np].x = x0 + nx;
        pts[np].y = y0 + ny;
        pts[np + 1].x = x1 + nx;
        pts[np + 1].y = y1 + ny;
        pts[np + 2].x = x1 - nx;
        pts[np + 2].y = y1 - ny;
        pts[np + 3].x = x0 - nx;
        pts[np + 3].y = y0 - ny;
      }
      qc->start = np;
      qc->count = 4;
      qc->closed = true;
      nq++;
      np += 4;
      if (s->state.line_join == MY_LINE_JOIN_ROUND && i + 1 < c->count) {
        disks[nd].cx = (int32_t)floorf(SOFT_SX(s, s->points[c->start + j].x) +
                                       odd_off);
        disks[nd].cy = (int32_t)floorf(SOFT_SY(s, s->points[c->start + j].y) +
                                       odd_off);
        disks[nd].r = (int32_t)(half * s->state.scale + 0.5f);
        nd++;
      }
    }
  }

  /* row range: quads (device) and disks, intersected with the clip */
  ymin = (float)(clip->y + clip->h);
  ymax = (float)clip->y;
  for (i = 0; i < np; i++) {
    float py = SOFT_SY(s, pts[i].y);
    if (py < ymin) {
      ymin = py;
    }
    if (py > ymax) {
      ymax = py;
    }
  }
  for (i = 0; i < nd; i++) {
    float y0 = (float)(disks[i].cy - disks[i].r);
    float y1 = (float)(disks[i].cy + disks[i].r + 1);
    if (y0 < ymin) {
      ymin = y0;
    }
    if (y1 > ymax) {
      ymax = y1;
    }
  }
  row0 = (int32_t)floorf(ymin) > clip->y ? (int32_t)floorf(ymin) : clip->y;
  row1 = (int32_t)ceilf(ymax) < clip->y + clip->h ? (int32_t)ceilf(ymax)
                                                  : clip->y + clip->h;
  for (y = row0; y < row1; y++) {
    int hh;
    memset(rb.cov, 0, (size_t)clip->w);
    for (hh = 0; hh < halves; hh++) {
      /* quads: even-odd WITHIN each contour (convex -> one span) */
      for (i = 0; i < nq; i++) {
        float xs[4];
        size_t nxs = collect_intersections(s, pts, &cs[i], 1,
                                           (float)y + offs[hh], xs, 4,
                                           false);
        if (nxs > 1) {
          size_t k;
          qsort(xs, nxs, sizeof(float), float_cmp);
          for (k = 0; k + 1 < nxs; k += 2) {
            span_accum(rb.cov, clip->x, clip->w, xs[k], xs[k + 1]);
          }
        }
      }
      /* disks: exact circle spans (device space) */
      for (i = 0; i < nd; i++) {
        float fx = (float)disks[i].cx + 0.5f;
        float fdy = (float)y + offs[hh] - ((float)disks[i].cy + 0.5f);
        float r = (float)disks[i].r;
        if (fdy * fdy <= r * r) {
          float fdx = sqrtf(r * r - fdy * fdy);
          span_accum(rb.cov, clip->x, clip->w, fx - fdx, fx + fdx);
        }
      }
    }
    emit_row(s, &rb, y, clip->x, clip->w, 4 * halves, s->state.stroke_color);
  }
  ret = MY_RET_OK;

done:
  my_mem_free(s->allocator, pts);
  my_mem_free(s->allocator, cs);
  my_mem_free(s->allocator, disks);
  my_mem_free(s->allocator, rb.cov);
  return ret;
}

/** @brief Stroke: each segment becomes a quad contour filled with the
 * shared coverage path (blending + AA for free). AA levels >= 1 take
 * soft_stroke_union (M11d: single coverage buffer, no joint over-blend);
 * level 0 keeps the per-piece fills below (translucent joints still
 * over-blend there -- documented boundary). */
static my_ret_t soft_stroke(my_vgcanvas_t* vg) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  float half = s->state.line_width / 2.0f;
  float odd_off = 0.0f;
  size_t ci, i;
  if (half < 0.5f) {
    half = 0.5f;
  }
  /* odd integer widths: shift 0.5px so thin lines land on pixel centers */
  if (((int32_t)s->state.line_width) % 2 == 1) {
    odd_off = 0.5f;
  }
  if (s->antialias_level >= 1 && s->contour_count > 0) {
    /* M11d: union-merge all pieces of this stroke into one coverage
     * buffer (no translucent joint over-blend) */
    return soft_stroke_union(s, half, odd_off);
  }
  for (ci = 0; ci < s->contour_count; ci++) {
    const contour_t* c = &s->contours[ci];
    size_t edges = c->count > 1 ? (c->closed ? c->count : c->count - 1) : 0;
    if (c->count > 1 && !c->closed && s->state.line_cap == MY_LINE_CAP_ROUND) {
      /* round caps: half-lw disks on the two endpoints (coverage-AA) */
      int32_t r = (int32_t)(half * s->state.scale + 0.5f);
      int32_t cx0 = (int32_t)floorf(SOFT_SX(s, s->points[c->start].x) +
                                    odd_off);
      int32_t cy0 = (int32_t)floorf(SOFT_SY(s, s->points[c->start].y) +
                                    odd_off);
      size_t last = c->start + c->count - 1;
      int32_t cx1 = (int32_t)floorf(SOFT_SX(s, s->points[last].x) + odd_off);
      int32_t cy1 = (int32_t)floorf(SOFT_SY(s, s->points[last].y) + odd_off);
      if (r > 0) {
        soft_fill_circle(s, cx0, cy0, r, s->state.stroke_color);
        soft_fill_circle(s, cx1, cy1, r, s->state.stroke_color);
      }
    }
    for (i = 0; i < edges; i++) {
      size_t j = (i + 1) % c->count;
      float x0 = s->points[c->start + i].x + odd_off;
      float y0 = s->points[c->start + i].y + odd_off;
      float x1 = s->points[c->start + j].x + odd_off;
      float y1 = s->points[c->start + j].y + odd_off;
      float dx = x1 - x0, dy = y1 - y0;
      float len = sqrtf(dx * dx + dy * dy);
      float nx, ny;
      path_point_t quad[4];
      contour_t qcontour;
      if (len < 0.001f) {
        /* zero-length segment: small square stamp */
        quad[0].x = x0 - half;
        quad[0].y = y0 - half;
        quad[1].x = x0 + half;
        quad[1].y = y0 - half;
        quad[2].x = x0 + half;
        quad[2].y = y0 + half;
        quad[3].x = x0 - half;
        quad[3].y = y0 + half;
      } else {
        nx = -dy / len * half;
        ny = dx / len * half;
        quad[0].x = x0 + nx;
        quad[0].y = y0 + ny;
        quad[1].x = x1 + nx;
        quad[1].y = y1 + ny;
        quad[2].x = x1 - nx;
        quad[2].y = y1 - ny;
        quad[3].x = x0 - nx;
        quad[3].y = y0 - ny;
      }
      qcontour.start = 0;
      qcontour.count = 4;
      qcontour.closed = true;
      fill_polys(s, quad, 4, &qcontour, 1, s->state.stroke_color);
      /* round joins: half-lw disk at each interior vertex (slight
       * over-blend with segment ends for translucent strokes, noted) */
      if (s->state.line_join == MY_LINE_JOIN_ROUND && i + 1 < c->count) {
        int32_t r = (int32_t)(half * s->state.scale + 0.5f);
        if (r > 0) {
          soft_fill_circle(
              s, (int32_t)floorf(s->points[c->start + j].x + s->state.tx +
                                 odd_off),
              (int32_t)floorf(s->points[c->start + j].y + s->state.ty +
                              odd_off),
              r, s->state.stroke_color);
        }
      }
    }
  }
  return MY_RET_OK;
}

static my_ret_t soft_set_line_cap(my_vgcanvas_t* vg, my_line_cap_t cap) {
  ((my_vgcanvas_soft_t*)vg)->state.line_cap = cap;
  return MY_RET_OK;
}

static my_ret_t soft_set_line_join(my_vgcanvas_t* vg, my_line_join_t join) {
  ((my_vgcanvas_soft_t*)vg)->state.line_join = join;
  return MY_RET_OK;
}

/** @brief Font size in device pixels (M12c: logical size * scale). */
static int32_t soft_dev_font_size(const my_vgcanvas_soft_t* s) {
  int32_t d = (int32_t)((float)s->state.font_size * s->state.scale + 0.5f);
  return d > 0 ? d : 1;
}

/** @brief Draw one codepoint at pen_x and advance it (soft text body). */
static void soft_draw_cp(my_vgcanvas_soft_t* s, uint32_t cp, float* pen_x,
                         int32_t top, int32_t ascent) {
  const my_rect_t* clip = &s->state.clip;
  my_glyph_t g = {0};
  int32_t gx, gy, row;
  if (my_font_get_glyph(s->state.font, cp, soft_dev_font_size(s), &g) !=
      MY_RET_OK) {
    return;
  }
  gx = soft_round(*pen_x) + g.bearing_x;
  gy = top + ascent - g.bearing_y;
  if (g.bitmap != NULL) {
    for (row = 0; row < g.h; row++) {
      int32_t dy = gy + row;
      int32_t dx0 = gx, dx1 = gx + g.w;
      const uint8_t* alpha_row = g.bitmap + (size_t)row * (size_t)g.w;
      if (dy < clip->y || dy >= clip->y + clip->h) {
        continue;
      }
      if (dx0 < clip->x) {
        dx0 = clip->x;
      }
      if (dx1 > clip->x + clip->w) {
        dx1 = clip->x + clip->w;
      }
      if (dx1 > dx0) {
        my_lcd_blend_span(s->lcd, dx0, dy, alpha_row + (dx0 - gx), dx1 - dx0,
                          s->state.fill_color);
      }
    }
  }
  *pen_x += (float)g.advance;
}

static void soft_draw_shaped_glyph(my_vgcanvas_soft_t* s,
                                   const my_font_shape_glyph_t* shaped,
                                   float* pen_x, int32_t top, int32_t ascent) {
  const my_rect_t* clip = &s->state.clip;
  my_glyph_t g = {0};
  int32_t gx, gy, row;
  float advance = (float)shaped->advance_x_26_6 / 64.0f;
  float offset_x = (float)shaped->offset_x_26_6 / 64.0f;
  float offset_y = (float)shaped->offset_y_26_6 / 64.0f;
  if (my_font_get_glyph_id(
          shaped->font != NULL ? shaped->font : s->state.font,
          shaped->glyph_id,
                           soft_dev_font_size(s), &g) != MY_RET_OK) {
    *pen_x += advance;
    return;
  }
  gx = soft_round(*pen_x + offset_x) + g.bearing_x;
  gy = top + ascent - g.bearing_y - soft_round(offset_y);
  if (g.bitmap != NULL) {
    for (row = 0; row < g.h; row++) {
      int32_t dy = gy + row;
      int32_t dx0 = gx, dx1 = gx + g.w;
      const uint8_t* alpha_row = g.bitmap + (size_t)row * (size_t)g.w;
      if (dy < clip->y || dy >= clip->y + clip->h) continue;
      if (dx0 < clip->x) dx0 = clip->x;
      if (dx1 > clip->x + clip->w) dx1 = clip->x + clip->w;
      if (dx1 > dx0) {
        my_lcd_blend_span(s->lcd, dx0, dy, alpha_row + (dx0 - gx),
                          dx1 - dx0, s->state.fill_color);
      }
    }
  }
  *pen_x += advance;
}

static my_ret_t soft_draw_text(my_vgcanvas_t* vg, const char* text, float x,
                               float y) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  int32_t ascent;
  float pen_x;
  int32_t top;
  const char* p = text;

  if (text == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (s->state.font == NULL || s->state.font_size <= 0) {
    return MY_RET_NOT_SUPPORTED;
  }
  ascent = my_font_ascent(s->state.font, soft_dev_font_size(s));
  pen_x = SOFT_SX(s, x);
  top = soft_round(SOFT_SY(s, y));

  if (!my_text_layout_may_need_bidi(text)) {
    my_font_shape_result_t shaped = {0};
    if (my_vgcanvas_shape_font(vg, s->state.font, text,
                               soft_dev_font_size(s), false, s->allocator,
                               &shaped) == MY_RET_OK) {
      size_t i;
      for (i = 0; i < shaped.count; i++) {
        soft_draw_shaped_glyph(s, &shaped.glyphs[i], &pen_x, top, ascent);
      }
      my_font_shape_destroy(&shaped);
      return MY_RET_OK;
    }
    /* fallback: plain LTR, no layout work at all */
    while (*p != '\0') {
      soft_draw_cp(s, my_utf8_next(&p), &pen_x, top, ascent);
    }
    return MY_RET_OK;
  }
  /* shaped + visually reordered path (M11a). x is ALWAYS the left edge:
   * the visual order of an RTL paragraph simply starts there; alignment
   * is the widget's business (see my_text_layout.h). */
  {
    my_text_layout_t* l = my_text_layout_process(s->allocator, text);
    my_font_shape_result_t shaped = {0};
    my_ret_t shape_ret;
    size_t i;
    if (l == NULL) {
      return MY_RET_OOM;
    }
    shape_ret = my_vgcanvas_shape_layout(
        vg, l, text, s->state.font, soft_dev_font_size(s), s->allocator,
        &shaped);
    if (shape_ret == MY_RET_OK) {
      for (i = 0; i < shaped.count; i++) {
        soft_draw_shaped_glyph(s, &shaped.glyphs[i], &pen_x, top, ascent);
      }
      my_font_shape_destroy(&shaped);
    } else if (shape_ret == MY_RET_NOT_SUPPORTED) {
      for (i = 0; i < l->len; i++) {
        soft_draw_cp(s, l->visual_cps[i], &pen_x, top, ascent);
      }
    } else {
      my_text_layout_destroy(l);
      return shape_ret;
    }
    my_text_layout_destroy(l);
  }
  return MY_RET_OK;
}

static my_ret_t soft_set_font(my_vgcanvas_t* vg, my_font_t* font,
                              int32_t size) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  if (font != NULL) {
    s->state.font = font;
  }
  if (size > 0) {
    s->state.font_size = size;
  }
  return MY_RET_OK;
}

static my_ret_t soft_measure_text(my_vgcanvas_t* vg, const char* text,
                                  int32_t* w, int32_t* h) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  my_ret_t ret;
  if (s->state.font == NULL || s->state.font_size <= 0) {
    return MY_RET_NOT_SUPPORTED;
  }
  /* measure at the device size, report LOGICAL units (M12c) */
  if (text != NULL && my_text_layout_may_need_bidi(text)) {
    my_text_layout_t* l = my_text_layout_process(s->allocator, text);
    if (l == NULL) {
      return MY_RET_OOM;
    }
    {
      my_font_shape_result_t shaped = {0};
      ret = my_vgcanvas_shape_layout(
          vg, l, text, s->state.font, soft_dev_font_size(s), s->allocator,
          &shaped);
      if (ret == MY_RET_OK) {
        int64_t width = 0;
        size_t i;
        for (i = 0; i < shaped.count; i++) {
          width += shaped.glyphs[i].advance_x_26_6;
        }
        if (w != NULL) *w = (int32_t)((width + 32) / 64);
        if (h != NULL) {
          *h = my_font_line_height(s->state.font, soft_dev_font_size(s));
        }
        my_font_shape_destroy(&shaped);
      } else if (ret == MY_RET_NOT_SUPPORTED) {
        ret = my_font_measure(s->state.font, l->visual_utf8,
                              soft_dev_font_size(s), w, h);
      }
    }
    my_text_layout_destroy(l);
  } else {
    my_font_shape_result_t shaped = {0};
    ret = my_vgcanvas_shape_font(vg, s->state.font, text,
                                 soft_dev_font_size(s), false, s->allocator,
                                 &shaped);
    if (ret == MY_RET_OK) {
      int64_t width = 0;
      size_t i;
      for (i = 0; i < shaped.count; i++) width += shaped.glyphs[i].advance_x_26_6;
      if (w != NULL) *w = (int32_t)((width + 32) / 64);
      if (h != NULL) *h = my_font_line_height(s->state.font,
                                               soft_dev_font_size(s));
      my_font_shape_destroy(&shaped);
    } else {
      ret = my_font_measure(s->state.font, text, soft_dev_font_size(s), w, h);
    }
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

/** @brief Bilinear sample at source coords (already pixel-center mapped:
 * gx = (dst+0.5)*w/dw - 0.5). Edges clamped.
 *
 * M12c fixed point: coords 16.16, weights quantized to 1/256 (0..256,
 * +-1px tolerance vs the old float version). Little-endian fast path
 * packs the x-combine of the r|b and g|a channel pairs into two uint32
 * multiplies each (lane sums peak at 255*256 = 65280, never carry into
 * the neighbour lane); big-endian uses the scalar integer form. Degenerate
 * weights (ax == ay == 0, e.g. exact integer scales) short-circuit. */
static void sample_bilinear(const uint8_t* rgba, int32_t w, int32_t h,
                            float gx, float gy, uint8_t out[4]) {
  int32_t fx16 = (int32_t)(gx * 65536.0f + (gx >= 0.0f ? 0.5f : -0.5f));
  int32_t fy16 = (int32_t)(gy * 65536.0f + (gy >= 0.0f ? 0.5f : -0.5f));
  int32_t x0 = fx16 >> 16, y0 = fy16 >> 16;
  uint32_t ax = (uint32_t)(fx16 & 0xFFFF);
  uint32_t ay = (uint32_t)(fy16 & 0xFFFF);
  int32_t x1, y1;
  ax = (ax + 128u) >> 8; /* 0..256 */
  ay = (ay + 128u) >> 8;
  if (x0 < 0) { x0 = 0; ax = 0; }
  if (y0 < 0) { y0 = 0; ay = 0; }
  x1 = x0 + 1 < w ? x0 + 1 : w - 1;
  y1 = y0 + 1 < h ? y0 + 1 : h - 1;
  if (x0 >= w) { x0 = w - 1; x1 = w - 1; ax = 0; }
  if (y0 >= h) { y0 = h - 1; y1 = h - 1; ay = 0; }
#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && \
    __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  {
    static const uint32_t M = 0x00FF00FFu;
    uint32_t p00, p10, p01, p11, ix = 256u - ax, iy = 256u - ay;
    uint32_t trb, tga, brb, bga;
    memcpy(&p00, rgba + ((size_t)y0 * (size_t)w + (size_t)x0) * 4u, 4);
    if (ax == 0 && ay == 0) {
      memcpy(out, &p00, 4);
      return;
    }
    memcpy(&p10, rgba + ((size_t)y0 * (size_t)w + (size_t)x1) * 4u, 4);
    memcpy(&p01, rgba + ((size_t)y1 * (size_t)w + (size_t)x0) * 4u, 4);
    memcpy(&p11, rgba + ((size_t)y1 * (size_t)w + (size_t)x1) * 4u, 4);
    /* x-combine, packed per channel pair */
    trb = (p00 & M) * ix + (p10 & M) * ax;
    tga = ((p00 >> 8) & M) * ix + ((p10 >> 8) & M) * ax;
    brb = (p01 & M) * ix + (p11 & M) * ax;
    bga = ((p01 >> 8) & M) * ix + ((p11 >> 8) & M) * ax;
    /* y-combine per 16-bit lane (+32768 rounding) */
    out[0] = (uint8_t)(((trb & 0xFFFFu) * iy + (brb & 0xFFFFu) * ay +
                        0x8000u) >> 16);
    out[2] = (uint8_t)(((trb >> 16) * iy + (brb >> 16) * ay + 0x8000u) >> 16);
    out[1] = (uint8_t)(((tga & 0xFFFFu) * iy + (bga & 0xFFFFu) * ay +
                        0x8000u) >> 16);
    out[3] = (uint8_t)(((tga >> 16) * iy + (bga >> 16) * ay + 0x8000u) >> 16);
  }
#else
  {
    uint32_t ix = 256u - ax, iy = 256u - ay;
    int c;
    if (ax == 0 && ay == 0) {
      memcpy(out, rgba + ((size_t)y0 * (size_t)w + (size_t)x0) * 4u, 4);
      return;
    }
    for (c = 0; c < 4; c++) {
      uint32_t v00 = rgba[((size_t)y0 * (size_t)w + (size_t)x0) * 4u + c];
      uint32_t v10 = rgba[((size_t)y0 * (size_t)w + (size_t)x1) * 4u + c];
      uint32_t v01 = rgba[((size_t)y1 * (size_t)w + (size_t)x0) * 4u + c];
      uint32_t v11 = rgba[((size_t)y1 * (size_t)w + (size_t)x1) * 4u + c];
      uint32_t top = v00 * ix + v10 * ax;
      uint32_t bot = v01 * ix + v11 * ax;
      out[c] = (uint8_t)((top * iy + bot * ay + 0x8000u) >> 16);
    }
  }
#endif
}

/** @brief Pack one RGBA pixel into the lcd's native format (over bg). */
static void pack_native(my_pixel_format_t fmt, const uint8_t* rgba,
                        const my_color_t* bg, uint8_t* out) {
  uint8_t r = rgba[0], g = rgba[1], b = rgba[2], a = rgba[3];
  if (bg != NULL && a < 255) {
    r = (uint8_t)(((uint32_t)r * a + (uint32_t)bg->r * (255u - a)) / 255u);
    g = (uint8_t)(((uint32_t)g * a + (uint32_t)bg->g * (255u - a)) / 255u);
    b = (uint8_t)(((uint32_t)b * a + (uint32_t)bg->b * (255u - a)) / 255u);
    a = 255;
  }
  switch (fmt) {
    case MY_PIXEL_FORMAT_RGB565: {
      uint16_t v = (uint16_t)(((r >> 3) << 11) | ((g >> 2) << 5) | (b >> 3));
      memcpy(out, &v, 2);
      break;
    }
    case MY_PIXEL_FORMAT_RGB888:
      out[0] = r;
      out[1] = g;
      out[2] = b;
      break;
    case MY_PIXEL_FORMAT_ARGB8888:
      out[0] = a;
      out[1] = r;
      out[2] = g;
      out[3] = b;
      break;
    case MY_PIXEL_FORMAT_BGRA8888:
      out[0] = b;
      out[1] = g;
      out[2] = r;
      out[3] = a;
      break;
    case MY_PIXEL_FORMAT_MONO:
    default:
      out[0] = (uint8_t)(((uint32_t)r * 299 + (uint32_t)g * 587 +
                          (uint32_t)b * 114) / 1000u >= 128u
                             ? 1
                             : 0);
      break;
  }
}

static bool mono_dither_on(int32_t x, int32_t y, uint8_t r, uint8_t g,
                           uint8_t b, uint8_t a, const my_color_t* bg) {
  static const uint8_t matrix[4][4] = {
      {0, 8, 2, 10}, {12, 4, 14, 6}, {3, 11, 1, 9}, {15, 7, 13, 5}};
  uint32_t luma;
  if (bg != NULL && a < 255) {
    r = (uint8_t)(((uint32_t)r * a + (uint32_t)bg->r * (255u - a)) / 255u);
    g = (uint8_t)(((uint32_t)g * a + (uint32_t)bg->g * (255u - a)) / 255u);
    b = (uint8_t)(((uint32_t)b * a + (uint32_t)bg->b * (255u - a)) / 255u);
  }
  luma = ((uint32_t)r * 299u + (uint32_t)g * 587u + (uint32_t)b * 114u) /
         1000u;
  return luma * 16u >= (uint32_t)matrix[(uint32_t)y % 4u][(uint32_t)x % 4u] *
                         255u + 128u;
}

/** @brief Box pre-downsample tier (M10c): largest power-of-2 factor f in
 * {2,4,8} with dst*f <= src (the remaining scale ratio stays <= 1), and
 * only when downscaling past 0.5x. Returns 1 when no tier applies. */
static int32_t box_factor(int32_t src, int32_t dst) {
  int32_t f = 2;
  if (src <= 0 || dst <= 0 || (int64_t)dst * 2 >= src) {
    return 1; /* upscale, 1:1, or mild downscale (ratio >= 0.5) */
  }
  while (f < 8 && (int64_t)dst * (f * 2) <= src) {
    f *= 2;
  }
  return f;
}

/** @brief Box-average src into tmp (nw x nh): output pixel (tx,ty) is the
 * mean of the fx x fy source block at (tx*fx, ty*fy); edge blocks may be
 * partial (only valid pixels are averaged). Straight-alpha channels are
 * averaged independently -- semi-transparent edges deviate slightly from
 * premultiplied filtering (accepted, keeps it simple).
 *
 * M11c fast path (little-endian): the 4 channels of a pixel are summed
 * as TWO packed 16-bit lanes per uint32 (r|b in one, g|a in the other).
 * Blocks are at most 8x8 = 64 px, so a lane peaks at 255*64 = 16320 and
 * never carries into its neighbour lane. Identical sums to the scalar
 * path -> pixel-exact output, ~2-3x faster at -O0. */
/** @brief Box-average src into tmp (nw x nh): output pixel (tx,ty) is the
 * mean of the fx x fy source block at (tx*fx, ty*fy); edge blocks may be
 * partial (only valid pixels are averaged). Straight-alpha channels are
 * averaged independently -- semi-transparent edges deviate slightly from
 * premultiplied filtering (accepted, keeps it simple).
 *
 * M11c SWAR fast path (little-endian): the 4 channels of a pixel are
 * summed as TWO packed 16-bit lanes per uint32 (r|b in one, g|a in the
 * other). Blocks are at most 8x8 = 64 px, so a lane peaks at 255*64 =
 * 16320 and never carries into its neighbour lane. Identical sums to the
 * scalar path -> pixel-exact output. M13b experiment: a row-buffer
 * sliding-window variant was tried and REVERTED -- it was SLOWER at both
 * -O0 (13.9ms vs 11.0) and -O2 (5.2 vs 4.8): blocks do not overlap, so
 * every source pixel is read exactly once either way, and the row buffer
 * only adds read-modify-write traffic; the per-block register
 * accumulators win. Kept: per-block SWAR. Big-endian keeps the scalar
 * path. */
static bool box_average(const uint8_t* src, int32_t w, int32_t h, int32_t fx,
                        int32_t fy, uint8_t* tmp, int32_t nw, int32_t nh) {
  int32_t tx, ty;
#if defined(__BYTE_ORDER__) && defined(__ORDER_LITTLE_ENDIAN__) && \
    __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
  for (ty = 0; ty < nh; ty++) {
    int32_t y0 = ty * fy;
    int32_t y1 = y0 + fy < h ? y0 + fy : h;
    for (tx = 0; tx < nw; tx++) {
      int32_t x0 = tx * fx;
      int32_t x1 = x0 + fx < w ? x0 + fx : w;
      uint32_t acc_rb = 0, acc_ga = 0, cnt;
      int32_t y;
      uint8_t* out = tmp + ((size_t)ty * (size_t)nw + (size_t)tx) * 4u;
      for (y = y0; y < y1; y++) {
        const uint8_t* p = src + ((size_t)y * (size_t)w + (size_t)x0) * 4u;
        const uint8_t* end = src + ((size_t)y * (size_t)w + (size_t)x1) * 4u;
        for (; p < end; p += 4) {
          uint32_t px;
          memcpy(&px, p, 4);
          acc_rb += px & 0x00FF00FFu;
          acc_ga += (px >> 8) & 0x00FF00FFu;
        }
      }
      cnt = (uint32_t)(x1 - x0) * (uint32_t)(y1 - y0);
      out[0] = (uint8_t)((acc_rb & 0xFFFFu) / cnt);
      out[1] = (uint8_t)((acc_ga & 0xFFFFu) / cnt);
      out[2] = (uint8_t)((acc_rb >> 16) / cnt);
      out[3] = (uint8_t)((acc_ga >> 16) / cnt);
    }
  }
  return true;
#else  /* portable scalar path (big-endian) */
  for (ty = 0; ty < nh; ty++) {
    int32_t y0 = ty * fy;
    int32_t y1 = y0 + fy < h ? y0 + fy : h;
    for (tx = 0; tx < nw; tx++) {
      int32_t x0 = tx * fx;
      int32_t x1 = x0 + fx < w ? x0 + fx : w;
      uint32_t acc[4] = {0, 0, 0, 0};
      uint32_t cnt;
      int32_t x, y, c;
      for (y = y0; y < y1; y++) {
        for (x = x0; x < x1; x++) {
          const uint8_t* p = src + ((size_t)y * (size_t)w + (size_t)x) * 4u;
          for (c = 0; c < 4; c++) {
            acc[c] += p[c];
          }
        }
      }
      cnt = (uint32_t)(x1 - x0) * (uint32_t)(y1 - y0);
      for (c = 0; c < 4; c++) {
        tmp[((size_t)ty * (size_t)nw + (size_t)tx) * 4u + (size_t)c] =
            (uint8_t)(acc[c] / cnt);
      }
    }
  }
  return true;
#endif
}

static my_ret_t soft_draw_image(my_vgcanvas_t* vg, const uint8_t* rgba,
                                int32_t w, int32_t h, const my_rectf_t* dst,
                                const my_color_t* bg) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  my_pixel_format_t fmt;
  my_rect_t dev, clipped;
  uint32_t bpp;
  uint8_t* row = NULL;
  const uint8_t* src;
  uint8_t* pre = NULL;
  int32_t sw, sh;
  int32_t dy;
  my_ret_t ret = MY_RET_OK;
  if (rgba == NULL || dst == NULL || w <= 0 || h <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  fmt = my_lcd_get_format(s->lcd);
  if (fmt == MY_PIXEL_FORMAT_MONO) {
    int32_t y;
    uint32_t mono_stride;
    dev = my_rect_init((int32_t)floorf(SOFT_SX(s, dst->x)),
                       (int32_t)floorf(SOFT_SY(s, dst->y)),
                       (int32_t)floorf(dst->w * s->state.scale),
                       (int32_t)floorf(dst->h * s->state.scale));
    if (!my_rect_intersect(&dev, &s->state.clip, &clipped)) {
      return MY_RET_OK;
    }
    mono_stride = (uint32_t)clipped.w / 8u +
                  ((uint32_t)clipped.w % 8u != 0u ? 1u : 0u);
    row = (uint8_t*)my_mem_alloc(s->allocator, mono_stride);
    if (row == NULL) {
      return MY_RET_OOM;
    }
    for (y = clipped.y; y < clipped.y + clipped.h; y++) {
      int32_t x;
      memset(row, 0, mono_stride);
      for (x = clipped.x; x < clipped.x + clipped.w; x++) {
        int32_t sx = (int32_t)((int64_t)(x - dev.x) * w /
                               (dev.w > 0 ? dev.w : 1));
        int32_t sy = (int32_t)((int64_t)(y - dev.y) * h /
                               (dev.h > 0 ? dev.h : 1));
        const uint8_t* pixel = rgba +
            ((size_t)(sy < 0 ? 0 : sy >= h ? h - 1 : sy) * (size_t)w +
             (size_t)(sx < 0 ? 0 : sx >= w ? w - 1 : sx)) * 4u;
        if (mono_dither_on(x, y, pixel[0], pixel[1], pixel[2], pixel[3], bg)) {
          row[(uint32_t)(x - clipped.x) / 8u] |=
              (uint8_t)(0x80u >> ((uint32_t)(x - clipped.x) % 8u));
        }
      }
      ret = my_lcd_draw_pixels(s->lcd, row, clipped.x, y,
                               (uint32_t)clipped.w, 1);
      if (ret != MY_RET_OK) {
        break;
      }
    }
    my_mem_free(s->allocator, row);
    if (ret != MY_RET_OK) {
      return ret;
    }
    my_dirty_rects_add(&s->dirty, &clipped);
    return MY_RET_OK;
  }
  bpp = my_pixel_format_bpp(fmt) / 8u;
  dev = my_rect_init((int32_t)floorf(SOFT_SX(s, dst->x)),
                     (int32_t)floorf(SOFT_SY(s, dst->y)),
                     (int32_t)floorf(dst->w * s->state.scale),
                     (int32_t)floorf(dst->h * s->state.scale));
  if (!my_rect_intersect(&dev, &s->state.clip, &clipped)) {
    return MY_RET_OK;
  }
  /* box pre-downsample (M10c): deep downscales in bilinear mode first drop
   * an integer tier (2/4/8) by box averaging, then bilinear the rest --
   * much less source traffic than direct bilinear, far less aliasing than
   * nearest */
  src = rgba;
  sw = w;
  sh = h;
  if (s->scale_filter == MY_SCALE_FILTER_BILINEAR) {
    int32_t fx = box_factor(w, dev.w);
    int32_t fy = box_factor(h, dev.h);
    if (fx > 1 || fy > 1) {
      int32_t nw = (w + fx - 1) / fx;
      int32_t nh = (h + fy - 1) / fy;
      pre = (uint8_t*)my_mem_alloc(s->allocator,
                                   (size_t)nw * (size_t)nh * 4u);
      if (pre != NULL &&
          box_average(rgba, w, h, fx, fy, pre, nw, nh)) {
        src = pre;
        sw = nw;
        sh = nh;
      }
      /* OOM: fall through to direct bilinear on the full source */
    }
  }
  row = (uint8_t*)my_mem_alloc(s->allocator, (size_t)clipped.w * bpp);
  if (row == NULL) {
    my_mem_free(s->allocator, pre);
    return MY_RET_OOM;
  }
  for (dy = clipped.y; dy < clipped.y + clipped.h; dy++) {
    int32_t sy =
        (int32_t)((int64_t)(dy - dev.y) * sh / (dev.h > 0 ? dev.h : 1));
    int32_t dx;
    uint8_t* out = row;
    if (sy < 0) {
      sy = 0;
    }
    if (sy >= sh) {
      sy = sh - 1;
    }
    for (dx = clipped.x; dx < clipped.x + clipped.w; dx++) {
      if (s->scale_filter == MY_SCALE_FILTER_BILINEAR) {
        uint8_t px4[4];
        float fx = ((float)(dx - dev.x) + 0.5f) * (float)sw /
                       (float)(dev.w > 0 ? dev.w : 1) -
                   0.5f;
        float fy = ((float)(dy - dev.y) + 0.5f) * (float)sh /
                       (float)(dev.h > 0 ? dev.h : 1) -
                   0.5f;
        sample_bilinear(src, sw, sh, fx, fy, px4);
        pack_native(fmt, px4, bg, out);
      } else {
        int32_t sx =
            (int32_t)((int64_t)(dx - dev.x) * sw / (dev.w > 0 ? dev.w : 1));
        if (sx < 0) {
          sx = 0;
        }
        if (sx >= sw) {
          sx = sw - 1;
        }
        pack_native(fmt, src + ((size_t)sy * (size_t)sw + (size_t)sx) * 4u, bg,
                    out);
      }
      out += bpp;
    }
    ret = my_lcd_draw_pixels(s->lcd, row, clipped.x, dy,
                             (uint32_t)clipped.w, 1);
    if (ret != MY_RET_OK) {
      break;
    }
  }
  my_mem_free(s->allocator, row);
  my_mem_free(s->allocator, pre);
  if (ret == MY_RET_OK) {
    my_dirty_rects_add(&s->dirty, &clipped);
  }
  return ret;
}

/* ---------------- lifecycle ---------------- */

static void soft_destroy(my_vgcanvas_t* vg) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  if (s != NULL) {
    my_mem_free(s->allocator, s->stack);
    my_mem_free(s->allocator, s->points);
    my_mem_free(s->allocator, s->contours);
    my_mem_free(s->allocator, s);
  }
}

static my_ret_t soft_reset_clip(my_vgcanvas_t* vg, const my_rectf_t* rect);
static my_ret_t soft_set_scale_vtable(my_vgcanvas_t* vg, float scale);
static my_ret_t soft_set_antialias_level_vtable(my_vgcanvas_t* vg, int level);
static my_ret_t soft_set_scale_filter_vtable(my_vgcanvas_t* vg,
                                             my_scale_filter_t filter);

static const my_vgcanvas_vtable_t s_soft_vtable = {
    soft_begin_frame,      soft_end_frame,   soft_save,          soft_restore,
    soft_translate,        soft_clip_rect,   soft_set_fill_color,
    soft_set_stroke_color, soft_set_line_width, soft_fill_rect,  soft_stroke_rect,
    soft_fill_rounded_rect, soft_begin_path, soft_move_to,       soft_line_to,
    soft_close_path,       soft_fill,        soft_stroke,        soft_draw_text,
    soft_destroy,          soft_set_font,    soft_measure_text,
    soft_draw_image,       soft_set_line_cap, soft_set_line_join,
    soft_curve_to,         soft_reset_clip,  soft_set_scale_vtable,
    soft_set_antialias_level_vtable, soft_set_scale_filter_vtable};

my_vgcanvas_t* my_vgcanvas_soft_create(const my_allocator_t* allocator,
                                       my_lcd_t* lcd) {
  my_vgcanvas_soft_t* s;
  if (lcd == NULL) {
    return NULL;
  }
  s = (my_vgcanvas_soft_t*)my_mem_calloc(allocator, 1, sizeof(my_vgcanvas_soft_t));
  if (s == NULL) {
    return NULL;
  }
  s->base.vtable = &s_soft_vtable;
  s->base.capabilities.antialias_levels =
      MY_VGCANVAS_AA_LEVEL_BIT(0) | MY_VGCANVAS_AA_LEVEL_BIT(1) |
      MY_VGCANVAS_AA_LEVEL_BIT(2);
  s->base.capabilities.scale_filters =
      MY_VGCANVAS_FILTER_BIT(MY_SCALE_FILTER_NEAREST) |
      MY_VGCANVAS_FILTER_BIT(MY_SCALE_FILTER_BILINEAR);
  s->base.capabilities.active_antialias_level = 2u;
  s->base.capabilities.active_scale_filter = MY_SCALE_FILTER_BILINEAR;
  s->allocator = allocator;
  s->lcd = lcd;
  s->state.fill_color = my_color_rgba(0, 0, 0, 255);
  s->state.stroke_color = my_color_rgba(0, 0, 0, 255);
  s->state.line_width = 1.0f;
  s->state.tx = 0.0f;
  s->state.ty = 0.0f;
  s->state.scale = 1.0f; /* HiDPI: my_vgcanvas_soft_set_scale (M12c) */
  s->state.font = NULL;
  s->state.font_size = 16;
  s->state.line_cap = MY_LINE_CAP_BUTT;
  s->state.line_join = MY_LINE_JOIN_MITER;
  s->state.clip =
      my_rect_init(0, 0, (int32_t)my_lcd_get_width(lcd), (int32_t)my_lcd_get_height(lcd));
  s->antialias_level = 2;
  s->scale_filter = MY_SCALE_FILTER_BILINEAR;
  my_dirty_rects_init(&s->dirty);
  return (my_vgcanvas_t*)s;
}

static my_ret_t soft_reset_clip(my_vgcanvas_t* vg, const my_rectf_t* rect) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  my_rect_t dev;
  if (rect == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  dev = my_rect_init((int32_t)floorf(SOFT_SX(s, rect->x)),
                     (int32_t)floorf(SOFT_SY(s, rect->y)),
                     (int32_t)ceilf(SOFT_SX(s, rect->x + rect->w)) -
                         (int32_t)floorf(SOFT_SX(s, rect->x)),
                     (int32_t)ceilf(SOFT_SY(s, rect->y + rect->h)) -
                         (int32_t)floorf(SOFT_SY(s, rect->y)));
  s->state.clip = dev; /* replace, not intersect */
  return MY_RET_OK;
}

void my_vgcanvas_soft_reset_clip(my_vgcanvas_t* vg, const my_rectf_t* rect) {
  /* M25: vtable-guarded like the other soft-specific setters — calling
   * this on a non-soft backend used to CORRUPT its state struct */
  if (vg != NULL && vg->vtable == &s_soft_vtable) {
    soft_reset_clip(vg, rect);
  }
}

void my_vgcanvas_soft_set_scale(my_vgcanvas_t* vg, float scale) {
  if (vg != NULL && vg->vtable == &s_soft_vtable) {
    (void)soft_set_scale_vtable(vg, scale);
  }
}

static my_ret_t soft_set_scale_vtable(my_vgcanvas_t* vg, float scale) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  if (s == NULL || scale <= 0.0f) {
    return MY_RET_INVALID_PARAMS;
  }
  s->state.scale = scale;
  return MY_RET_OK;
}

void my_vgcanvas_soft_set_scale_filter(my_vgcanvas_t* vg,
                                       my_scale_filter_t filter) {
  if (vg != NULL && vg->vtable == &s_soft_vtable) {
    (void)soft_set_scale_filter_vtable(vg, filter);
  }
}

static my_ret_t soft_set_scale_filter_vtable(my_vgcanvas_t* vg,
                                             my_scale_filter_t filter) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  if (s == NULL || (filter != MY_SCALE_FILTER_NEAREST &&
                    filter != MY_SCALE_FILTER_BILINEAR)) {
    return MY_RET_INVALID_PARAMS;
  }
  s->scale_filter = filter;
  s->base.capabilities.active_scale_filter = filter;
  return MY_RET_OK;
}

void my_vgcanvas_soft_set_antialias(my_vgcanvas_t* vg, bool enabled) {
  my_vgcanvas_soft_set_antialias_level(vg, enabled ? 2 : 0);
}

void my_vgcanvas_soft_set_antialias_level(my_vgcanvas_t* vg, int level) {
  if (vg != NULL && vg->vtable == &s_soft_vtable) {
    (void)soft_set_antialias_level_vtable(vg, level);
  }
}

static my_ret_t soft_set_antialias_level_vtable(my_vgcanvas_t* vg,
                                                int level) {
  my_vgcanvas_soft_t* s = (my_vgcanvas_soft_t*)vg;
  if (s == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (level < 0) {
    level = 0;
  }
  if (level > 2) {
    level = 2;
  }
  s->antialias_level = level;
  s->base.capabilities.active_antialias_level = (uint8_t)level;
  return MY_RET_OK;
}

const my_dirty_rects_t* my_vgcanvas_soft_get_dirty_rects(my_vgcanvas_t* vg) {
  if (vg == NULL || vg->vtable != &s_soft_vtable) {
    return NULL;
  }
  return &((my_vgcanvas_soft_t*)vg)->dirty;
}
