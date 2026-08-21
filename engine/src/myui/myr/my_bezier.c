/**
 * @file my_bezier.c
 * @brief Adaptive cubic bezier subdivision (M19a). Flatness = max
 * distance of the two control points from the chord (half-chord
 * normalized), a standard cheap estimate.
 */
#include "myr/my_bezier.h"

#include <math.h>

typedef struct bez_ctx_t {
  my_bezier_emit_fn_t emit;
  void* ctx;
  float tolerance;
  int32_t max_depth;
  int32_t segments;
  my_ret_t ret;
} bez_ctx_t;

/** @brief Distance of (px,py) from the chord (x0,y0)-(x1,y1). */
static float chord_dist(float x0, float y0, float x1, float y1, float px,
                        float py) {
  float dx = x1 - x0, dy = y1 - y0;
  float len2 = dx * dx + dy * dy;
  float cross;
  if (len2 < 1e-12f) {
    /* degenerate chord: distance to the shared point */
    float ex = px - x0, ey = py - y0;
    return sqrtf(ex * ex + ey * ey);
  }
  cross = (px - x0) * dy - (py - y0) * dx;
  return fabsf(cross) / sqrtf(len2);
}

static my_ret_t bez_sub(bez_ctx_t* c, float x0, float y0, float cx1,
                        float cy1, float cx2, float cy2, float x1, float y1,
                        int32_t depth) {
  float d1 = chord_dist(x0, y0, x1, y1, cx1, cy1);
  float d2 = chord_dist(x0, y0, x1, y1, cx2, cy2);
  float dmax = d1 > d2 ? d1 : d2;
  if (dmax <= c->tolerance || depth >= c->max_depth) {
    c->segments++;
    if (c->emit != NULL) {
      my_ret_t r = c->emit(c->ctx, x1, y1);
      if (r != MY_RET_OK) {
        c->ret = r;
        return r;
      }
    }
    return MY_RET_OK;
  }
  /* de Casteljau split at t = 0.5 */
  {
    float ax = (x0 + cx1) / 2.0f, ay = (y0 + cy1) / 2.0f;
    float bx = (cx1 + cx2) / 2.0f, by = (cy1 + cy2) / 2.0f;
    float cx = (cx2 + x1) / 2.0f, cy = (cy2 + y1) / 2.0f;
    float mx = (ax + bx) / 2.0f, my = (ay + by) / 2.0f;
    float nx = (bx + cx) / 2.0f, ny = (by + cy) / 2.0f;
    float px = (mx + nx) / 2.0f, py = (my + ny) / 2.0f;
    if (bez_sub(c, x0, y0, ax, ay, mx, my, px, py, depth + 1) != MY_RET_OK) {
      return c->ret;
    }
    return bez_sub(c, px, py, nx, ny, cx, cy, x1, y1, depth + 1);
  }
}

my_ret_t my_bezier_cubic_to_lines(float x0, float y0, float cx1, float cy1,
                                  float cx2, float cy2, float x1, float y1,
                                  float tolerance, int32_t max_depth,
                                  my_bezier_emit_fn_t emit, void* ctx,
                                  int32_t* out_segments) {
  bez_ctx_t c;
  if (emit == NULL || tolerance <= 0.0f) {
    return MY_RET_INVALID_PARAMS;
  }
  c.emit = emit;
  c.ctx = ctx;
  c.tolerance = tolerance;
  c.max_depth = max_depth > 0 ? max_depth : 16;
  c.segments = 0;
  c.ret = MY_RET_OK;
  if (bez_sub(&c, x0, y0, cx1, cy1, cx2, cy2, x1, y1, 0) != MY_RET_OK) {
    return c.ret;
  }
  if (out_segments != NULL) {
    *out_segments = c.segments;
  }
  return MY_RET_OK;
}
