/**
 * @file my_vggeometry.c
 * @brief Shared CPU geometry for the GPU vgcanvas backends (M25b).
 * The algorithms are extracted verbatim from my_vgcanvas_gles2.c — do
 * not "improve" them here without keeping the two backends (and their
 * pixel-tested expectations) in sync.
 */
#include "myr/my_vggeometry.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "myr/my_bezier.h"

static my_ret_t geo_grow(const my_allocator_t* alloc, void** arr, size_t* cap,
                         size_t need, size_t elem) {
  void* p;
  size_t new_cap = *cap > 0 ? *cap : 64;
  if (elem == 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (need == SIZE_MAX) {
    return MY_RET_OOM;
  }
  if (need <= *cap) {
    return MY_RET_OK;
  }
  while (new_cap < need) {
    if (new_cap > SIZE_MAX / 2u) {
      new_cap = need;
      break;
    }
    new_cap *= 2;
  }
  if (new_cap > SIZE_MAX / elem) {
    return MY_RET_OOM;
  }
  p = my_mem_realloc(alloc, *arr, new_cap * elem);
  if (p == NULL) {
    return MY_RET_OOM;
  }
  *arr = p;
  *cap = new_cap;
  return MY_RET_OK;
}

static bool geo_finite(float value) { return isfinite(value) != 0; }

static bool geo_valid_cap(my_line_cap_t cap) {
  return cap == MY_LINE_CAP_BUTT || cap == MY_LINE_CAP_ROUND ||
         cap == MY_LINE_CAP_SQUARE;
}

static bool geo_valid_join(my_line_join_t join) {
  return join == MY_LINE_JOIN_MITER || join == MY_LINE_JOIN_ROUND ||
         join == MY_LINE_JOIN_BEVEL;
}

static void geo_record_error(my_vggeometry_t* g, my_ret_t status) {
  if (g != NULL && g->status == MY_RET_OK) g->status = status;
}

void my_vggeometry_init(my_vggeometry_t* g, const my_allocator_t* allocator) {
  if (g != NULL) {
    memset(g, 0, sizeof(*g));
    g->allocator = allocator;
    g->scale = 1.0f;
  }
}

void my_vggeometry_destroy(my_vggeometry_t* g) {
  if (g != NULL) {
    my_mem_free(g->allocator, g->points);
    my_mem_free(g->allocator, g->contours);
    my_mem_free(g->allocator, g->verts);
    my_vggeometry_init(g, g->allocator);
  }
}

void my_vggeometry_set_transform(my_vggeometry_t* g, float tx, float ty,
                                 float scale) {
  if (g == NULL || !geo_finite(tx) || !geo_finite(ty) ||
      !geo_finite(scale) || scale <= 0.0f) {
    return;
  }
  g->tx = tx;
  g->ty = ty;
  g->scale = scale;
}

void my_vggeometry_begin_verts(my_vggeometry_t* g) {
  if (g != NULL) {
    g->vert_count = 0;
    g->status = MY_RET_OK;
  }
}

void my_vggeometry_push(my_vggeometry_t* g, float x, float y) {
  float device_x, device_y;
  if (g == NULL) {
    return;
  }
  if (g->status != MY_RET_OK || g->vert_count > SIZE_MAX - 2u) {
    geo_record_error(g, MY_RET_OOM);
    return;
  }
  if (!geo_finite(x) || !geo_finite(y)) {
    geo_record_error(g, MY_RET_INVALID_PARAMS);
    return;
  }
  device_x = (x + g->tx) * g->scale;
  device_y = (y + g->ty) * g->scale;
  if (!geo_finite(device_x) || !geo_finite(device_y)) {
    geo_record_error(g, MY_RET_INVALID_PARAMS);
    return;
  }
  if (geo_grow(g->allocator, (void**)&g->verts, &g->vert_cap,
               g->vert_count + 2, sizeof(float)) == MY_RET_OK) {
    g->verts[g->vert_count++] = device_x;
    g->verts[g->vert_count++] = device_y;
  } else {
    geo_record_error(g, MY_RET_OOM);
  }
}

my_ret_t my_vggeometry_status(const my_vggeometry_t* g) {
  return g != NULL ? g->status : MY_RET_INVALID_PARAMS;
}

void my_vggeometry_rect(my_vggeometry_t* g, float x0, float y0, float x1,
                        float y1) {
  if (g == NULL || !geo_finite(x0) || !geo_finite(y0) || !geo_finite(x1) ||
      !geo_finite(y1)) {
    return;
  }
  if (x1 <= x0 || y1 <= y0) {
    return;
  }
  my_vggeometry_push(g, x0, y0);
  my_vggeometry_push(g, x1, y0);
  my_vggeometry_push(g, x1, y1);
  my_vggeometry_push(g, x0, y0);
  my_vggeometry_push(g, x1, y1);
  my_vggeometry_push(g, x0, y1);
}

void my_vggeometry_circle_fan(my_vggeometry_t* g, float cx, float cy, float r,
                              int segments) {
  int i;
  if (g == NULL || !geo_finite(cx) || !geo_finite(cy) || !geo_finite(r) ||
      r < 0.0f || segments <= 0) {
    return;
  }
  for (i = 0; i < segments; i++) {
    float a0 = (float)i * 6.2831853f / (float)segments;
    float a1 = (float)(i + 1) * 6.2831853f / (float)segments;
    my_vggeometry_push(g, cx, cy);
    my_vggeometry_push(g, cx + r * cosf(a0), cy + r * sinf(a0));
    my_vggeometry_push(g, cx + r * cosf(a1), cy + r * sinf(a1));
  }
}

void my_vggeometry_fill_rounded_rect(my_vggeometry_t* g, float x, float y,
                                     float w, float h, float radius) {
  float r = radius;
  float x0 = x, y0 = y, x1 = x + w, y1 = y + h;
  if (g == NULL || !geo_finite(x) || !geo_finite(y) || !geo_finite(w) ||
      !geo_finite(h) || !geo_finite(radius) || radius < 0.0f || w <= 0.0f ||
      h <= 0.0f || !geo_finite(x1) || !geo_finite(y1)) {
    return;
  }
  if (r > w / 2.0f) {
    r = w / 2.0f;
  }
  if (r > h / 2.0f) {
    r = h / 2.0f;
  }
  if (r <= 0.5f) {
    my_vggeometry_rect(g, x0, y0, x1, y1);
  } else {
    my_vggeometry_rect(g, x0 + r, y0, x1 - r, y1);
    my_vggeometry_rect(g, x0, y0 + r, x0 + r, y1 - r);
    my_vggeometry_rect(g, x1 - r, y0 + r, x1, y1 - r);
    my_vggeometry_circle_fan(g, x0 + r, y0 + r, r, 8);
    my_vggeometry_circle_fan(g, x1 - r, y0 + r, r, 8);
    my_vggeometry_circle_fan(g, x0 + r, y1 - r, r, 8);
    my_vggeometry_circle_fan(g, x1 - r, y1 - r, r, 8);
  }
}

void my_vggeometry_stroke_rect(my_vggeometry_t* g, float x, float y, float w,
                               float h, float line_width) {
  float lw = line_width < 1.0f ? 1.0f : line_width;
  float x0 = x, y0 = y, x1 = x + w, y1 = y + h;
  if (g == NULL || !geo_finite(x) || !geo_finite(y) || !geo_finite(w) ||
      !geo_finite(h) || !geo_finite(line_width) || line_width <= 0.0f ||
      w <= 0.0f || h <= 0.0f || !geo_finite(x1) || !geo_finite(y1)) {
    return;
  }
  my_vggeometry_rect(g, x0, y0, x1, y0 + lw);
  my_vggeometry_rect(g, x0, y1 - lw, x1, y1);
  my_vggeometry_rect(g, x0, y0 + lw, x0 + lw, y1 - lw);
  my_vggeometry_rect(g, x1 - lw, y0 + lw, x1, y1 - lw);
}

/* ---------------- path accumulation ---------------- */

my_ret_t my_vggeometry_begin_path(my_vggeometry_t* g) {
  if (g == NULL) return MY_RET_INVALID_PARAMS;
  g->point_count = 0;
  g->contour_count = 0;
  g->status = MY_RET_OK;
  return MY_RET_OK;
}

my_ret_t my_vggeometry_move_to(my_vggeometry_t* g, float x, float y) {
  if (g == NULL || !geo_finite(x) || !geo_finite(y)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (g->contour_count == SIZE_MAX || g->point_count == SIZE_MAX ||
      geo_grow(g->allocator, (void**)&g->contours, &g->contour_cap,
               g->contour_count + 1, sizeof(my_vggeo_contour_t)) !=
          MY_RET_OK ||
      geo_grow(g->allocator, (void**)&g->points, &g->point_cap,
               g->point_count + 1, sizeof(my_vggeo_point_t)) != MY_RET_OK) {
    return MY_RET_OOM;
  }
  g->contours[g->contour_count].start = g->point_count;
  g->contours[g->contour_count].count = 0;
  g->contours[g->contour_count].closed = false;
  g->points[g->point_count].x = x;
  g->points[g->point_count].y = y;
  g->point_count++;
  g->contours[g->contour_count].count++;
  g->contour_count++;
  return MY_RET_OK;
}

my_ret_t my_vggeometry_line_to(my_vggeometry_t* g, float x, float y) {
  if (g == NULL || !geo_finite(x) || !geo_finite(y))
    return MY_RET_INVALID_PARAMS;
  if (g->contour_count == 0) {
    return my_vggeometry_move_to(g, x, y);
  }
  if (g->point_count == SIZE_MAX ||
      geo_grow(g->allocator, (void**)&g->points, &g->point_cap,
               g->point_count + 1, sizeof(my_vggeo_point_t)) != MY_RET_OK) {
    return MY_RET_OOM;
  }
  g->points[g->point_count].x = x;
  g->points[g->point_count].y = y;
  g->point_count++;
  g->contours[g->contour_count - 1].count++;
  return MY_RET_OK;
}

my_ret_t my_vggeometry_close_path(my_vggeometry_t* g) {
  if (g == NULL) return MY_RET_INVALID_PARAMS;
  if (g->contour_count > 0) {
    g->contours[g->contour_count - 1].closed = true;
  }
  return MY_RET_OK;
}

/** @brief Emit one subdivision endpoint as a line_to. */
static my_ret_t geo_bezier_emit(void* ctx, float x, float y) {
  return my_vggeometry_line_to((my_vggeometry_t*)ctx, x, y);
}

my_ret_t my_vggeometry_curve_to(my_vggeometry_t* g, float cx1, float cy1,
                                float cx2, float cy2, float x, float y) {
  float x0, y0;
  size_t point_count;
  size_t contour_count;
  if (g == NULL || !geo_finite(cx1) || !geo_finite(cy1) ||
      !geo_finite(cx2) || !geo_finite(cy2) || !geo_finite(x) ||
      !geo_finite(y)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (g->contour_count == 0 ||
      g->contours[g->contour_count - 1].count == 0) {
    return MY_RET_FAIL; /* no current point (canvas convention) */
  }
  x0 = g->points[g->point_count - 1].x;
  y0 = g->points[g->point_count - 1].y;
  point_count = g->point_count;
  contour_count = g->contours[g->contour_count - 1].count;
  /* same adaptive subdivision as the soft backend */
  {
    my_ret_t ret = my_bezier_cubic_to_lines(
        x0, y0, cx1, cy1, cx2, cy2, x, y, 0.25f, 16, geo_bezier_emit, g,
        NULL);
    if (ret != MY_RET_OK) {
      g->point_count = point_count;
      g->contours[g->contour_count - 1].count = contour_count;
    }
    return ret;
  }
}

/* ---------------- fill / stroke ---------------- */

static int float_cmp(const void* a, const void* b) {
  float fa = *(const float*)a;
  float fb = *(const float*)b;
  return fa < fb ? -1 : fa > fb ? 1 : 0;
}

my_ret_t my_vggeometry_fill(my_vggeometry_t* g, const my_rect_t* clip) {
  float* xs;
  size_t xs_cap;
  int64_t y;
  int64_t x_end, y_end;
  if (g == NULL || clip == NULL || clip->w < 0 || clip->h < 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (g->status != MY_RET_OK) return g->status;
  x_end = (int64_t)clip->x + (int64_t)clip->w;
  y_end = (int64_t)clip->y + (int64_t)clip->h;
  if (x_end > INT32_MAX || y_end > INT32_MAX) {
    return MY_RET_INVALID_PARAMS;
  }
  if (g->point_count < 2 || clip->w == 0 || clip->h == 0) {
    return MY_RET_OK;
  }
  xs_cap = g->point_count;
  if (xs_cap > SIZE_MAX / sizeof(float)) return MY_RET_OOM;
  xs = (float*)my_mem_alloc(g->allocator, xs_cap * sizeof(float));
  if (xs == NULL) {
    return MY_RET_OOM;
  }
  for (y = clip->y; y < y_end; y++) {
    float yc = (float)y + 0.5f;
    size_t nxs = 0, ci, i, k;
    for (ci = 0; ci < g->contour_count; ci++) {
      const my_vggeo_contour_t* c = &g->contours[ci];
      for (i = 0; i < c->count; i++) {
        size_t j = i + 1;
        float x0, y0, x1, y1;
        if (j == c->count) {
          if (!c->closed) {
            break;
          }
          j = 0;
        }
        x0 = g->points[c->start + i].x + g->tx;
        y0 = g->points[c->start + i].y + g->ty;
        x1 = g->points[c->start + j].x + g->tx;
        y1 = g->points[c->start + j].y + g->ty;
        if ((y0 <= yc) != (y1 <= yc) && nxs < xs_cap) {
          xs[nxs++] = x0 + (yc - y0) * (x1 - x0) / (y1 - y0);
        }
      }
    }
    if (nxs > 1) {
      qsort(xs, nxs, sizeof(float), float_cmp);
      for (k = 0; k + 1 < nxs; k += 2) {
        /* spans are computed in device space: undo translate for push */
        float xa = ceilf(xs[k] - 0.5f) - g->tx;
        float xb = ceilf(xs[k + 1] - 0.5f) - g->tx;
        my_vggeometry_rect(g, xa, (float)y - g->ty, xb,
                           (float)y + 1.0f - g->ty);
      }
    }
  }
  my_mem_free(g->allocator, xs);
  return g->status;
}

/** @brief One segment as a quad expanded along its normal. */
static void geo_segment(my_vggeometry_t* g, float x0, float y0, float x1,
                        float y1, float half_w, bool extend_start,
                        bool extend_end) {
  float dx = x1 - x0;
  float dy = y1 - y0;
  float len = sqrtf(dx * dx + dy * dy);
  float nx, ny;
  if (len < 0.001f) {
    my_vggeometry_rect(g, x0 - half_w, y0 - half_w, x0 + half_w,
                       y0 + half_w);
    return;
  }
  if (extend_start) {
    x0 -= dx / len * half_w;
    y0 -= dy / len * half_w;
  }
  if (extend_end) {
    x1 += dx / len * half_w;
    y1 += dy / len * half_w;
  }
  nx = -dy / len * half_w;
  ny = dx / len * half_w;
  my_vggeometry_push(g, x0 + nx, y0 + ny);
  my_vggeometry_push(g, x1 + nx, y1 + ny);
  my_vggeometry_push(g, x1 - nx, y1 - ny);
  my_vggeometry_push(g, x0 + nx, y0 + ny);
  my_vggeometry_push(g, x1 - nx, y1 - ny);
  my_vggeometry_push(g, x0 - nx, y0 - ny);
}

static void geo_triangle(my_vggeometry_t* g, float ax, float ay, float bx,
                         float by, float cx, float cy) {
  my_vggeometry_push(g, ax, ay);
  my_vggeometry_push(g, bx, by);
  my_vggeometry_push(g, cx, cy);
}

static float geo_cross(float ax, float ay, float bx, float by) {
  return ax * by - ay * bx;
}

/** @brief Add the outer half of one join, with a bounded miter fallback. */
static void geo_join(my_vggeometry_t* g, float px, float py, float prev_x,
                     float prev_y, float next_x, float next_y, float half_w,
                     my_line_join_t join) {
  float in_x = px - prev_x;
  float in_y = py - prev_y;
  float out_x = next_x - px;
  float out_y = next_y - py;
  float in_len = sqrtf(in_x * in_x + in_y * in_y);
  float out_len = sqrtf(out_x * out_x + out_y * out_y);
  float cross;
  float in_nx, in_ny, out_nx, out_ny;
  float side;
  float ax, ay, bx, by;

  if (in_len < 0.001f || out_len < 0.001f) return;
  cross = geo_cross(in_x, in_y, out_x, out_y);
  if (fabsf(cross) < 0.0001f) return;
  in_nx = -in_y / in_len * half_w;
  in_ny = in_x / in_len * half_w;
  out_nx = -out_y / out_len * half_w;
  out_ny = out_x / out_len * half_w;
  /* A left turn has its outer edge on the right side. */
  side = cross > 0.0f ? -1.0f : 1.0f;
  ax = px + side * in_nx;
  ay = py + side * in_ny;
  bx = px + side * out_nx;
  by = py + side * out_ny;

  if (join == MY_LINE_JOIN_ROUND) {
    my_vggeometry_circle_fan(g, px, py, half_w, 8);
    return;
  }
  if (join == MY_LINE_JOIN_MITER) {
    float denom = geo_cross(in_x, in_y, out_x, out_y);
    float t = geo_cross(bx - ax, by - ay, out_x, out_y) / denom;
    float mx = ax + in_x * t;
    float my = ay + in_y * t;
    float miter_len = sqrtf((mx - px) * (mx - px) +
                            (my - py) * (my - py));
    if (isfinite(miter_len) && miter_len <= half_w * 4.0f) {
      geo_triangle(g, ax, ay, mx, my, bx, by);
      return;
    }
  }
  /* Bevel is also the safe fallback for an over-limit miter. */
  geo_triangle(g, ax, ay, px, py, bx, by);
}

/** @brief Semicircle fan (round cap): 8 triangles sweeping pi from a0. */
static void geo_semicircle_fan(my_vggeometry_t* g, float cx, float cy,
                               float r, float a0) {
  int i;
  for (i = 0; i < 8; i++) {
    float t0 = a0 + (float)i * 3.14159265f / 8.0f;
    float t1 = a0 + (float)(i + 1) * 3.14159265f / 8.0f;
    my_vggeometry_push(g, cx, cy);
    my_vggeometry_push(g, cx + r * cosf(t0), cy + r * sinf(t0));
    my_vggeometry_push(g, cx + r * cosf(t1), cy + r * sinf(t1));
  }
}

/** @brief Round cap at an open-contour endpoint (full disk for degenerate
 * segments). dx/dy = segment direction at the endpoint. */
static void geo_round_cap(my_vggeometry_t* g, float cx, float cy, float dx,
                          float dy, float half_w) {
  float len = sqrtf(dx * dx + dy * dy);
  if (len < 0.001f) {
    my_vggeometry_circle_fan(g, cx, cy, half_w, 8);
    return;
  }
  geo_semicircle_fan(g, cx, cy, half_w, atan2f(dy, dx) - 3.14159265f / 2.0f);
}

my_ret_t my_vggeometry_stroke(my_vggeometry_t* g, float line_width,
                              my_line_cap_t cap, my_line_join_t join) {
  float half_w = line_width / 2.0f;
  size_t ci, i;
  if (g == NULL || !geo_finite(line_width) || line_width <= 0.0f ||
      !geo_valid_cap(cap) || !geo_valid_join(join)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (g->status != MY_RET_OK) return g->status;
  if (half_w < 0.5f) {
    half_w = 0.5f;
  }
  for (ci = 0; ci < g->contour_count; ci++) {
    const my_vggeo_contour_t* c = &g->contours[ci];
    size_t edges = c->count > 1 ? (c->closed ? c->count : c->count - 1) : 0;
    if (c->count > 1 && !c->closed && cap == MY_LINE_CAP_ROUND) {
      /* round caps on the two endpoints (aligned with soft, M9c) */
      size_t last = c->start + c->count - 1;
      geo_round_cap(g, g->points[c->start].x, g->points[c->start].y,
                    g->points[c->start].x - g->points[c->start + 1].x,
                    g->points[c->start].y - g->points[c->start + 1].y,
                    half_w);
      geo_round_cap(g, g->points[last].x, g->points[last].y,
                    g->points[last].x - g->points[last - 1].x,
                    g->points[last].y - g->points[last - 1].y, half_w);
    }
    for (i = 0; i < edges; i++) {
      size_t j = (i + 1) % c->count;
      geo_segment(g, g->points[c->start + i].x, g->points[c->start + i].y,
                  g->points[c->start + j].x, g->points[c->start + j].y,
                  half_w, !c->closed && i == 0 && cap == MY_LINE_CAP_SQUARE,
                  !c->closed && i + 1 == edges &&
                      cap == MY_LINE_CAP_SQUARE);
    }
    for (i = 0; i < c->count; i++) {
      size_t vertex = c->start + i;
      size_t prev;
      size_t next;
      if (!c->closed && (i == 0 || i + 1 == c->count)) continue;
      prev = c->start + (i == 0 ? c->count - 1 : i - 1);
      next = c->start + ((i + 1) % c->count);
      geo_join(g, g->points[vertex].x, g->points[vertex].y,
               g->points[prev].x, g->points[prev].y, g->points[next].x,
               g->points[next].y, half_w, join);
    }
  }
  return g->status;
}
