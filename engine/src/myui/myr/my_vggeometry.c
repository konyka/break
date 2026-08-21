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
  g->tx = tx;
  g->ty = ty;
  g->scale = scale;
}

void my_vggeometry_begin_verts(my_vggeometry_t* g) {
  g->vert_count = 0;
}

void my_vggeometry_push(my_vggeometry_t* g, float x, float y) {
  if (geo_grow(g->allocator, (void**)&g->verts, &g->vert_cap,
               g->vert_count + 2, sizeof(float)) == MY_RET_OK) {
    g->verts[g->vert_count++] = (x + g->tx) * g->scale;
    g->verts[g->vert_count++] = (y + g->ty) * g->scale;
  }
}

void my_vggeometry_rect(my_vggeometry_t* g, float x0, float y0, float x1,
                        float y1) {
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
  my_vggeometry_rect(g, x0, y0, x1, y0 + lw);
  my_vggeometry_rect(g, x0, y1 - lw, x1, y1);
  my_vggeometry_rect(g, x0, y0 + lw, x0 + lw, y1 - lw);
  my_vggeometry_rect(g, x1 - lw, y0 + lw, x1, y1 - lw);
}

/* ---------------- path accumulation ---------------- */

my_ret_t my_vggeometry_begin_path(my_vggeometry_t* g) {
  g->point_count = 0;
  g->contour_count = 0;
  return MY_RET_OK;
}

my_ret_t my_vggeometry_move_to(my_vggeometry_t* g, float x, float y) {
  if (geo_grow(g->allocator, (void**)&g->contours, &g->contour_cap,
               g->contour_count + 1, sizeof(my_vggeo_contour_t)) !=
      MY_RET_OK) {
    return MY_RET_OOM;
  }
  g->contours[g->contour_count].start = g->point_count;
  g->contours[g->contour_count].count = 0;
  g->contours[g->contour_count].closed = false;
  g->contour_count++;
  return my_vggeometry_line_to(g, x, y);
}

my_ret_t my_vggeometry_line_to(my_vggeometry_t* g, float x, float y) {
  if (g->contour_count == 0) {
    return my_vggeometry_move_to(g, x, y);
  }
  if (geo_grow(g->allocator, (void**)&g->points, &g->point_cap,
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
  if (g->contour_count == 0 ||
      g->contours[g->contour_count - 1].count == 0) {
    return MY_RET_FAIL; /* no current point (canvas convention) */
  }
  x0 = g->points[g->point_count - 1].x;
  y0 = g->points[g->point_count - 1].y;
  /* same adaptive subdivision as the soft backend */
  return my_bezier_cubic_to_lines(x0, y0, cx1, cy1, cx2, cy2, x, y, 0.25f,
                                  16, geo_bezier_emit, g, NULL);
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
  int32_t y;
  if (g->point_count < 2) {
    return MY_RET_OK;
  }
  xs_cap = g->point_count;
  xs = (float*)my_mem_alloc(g->allocator, xs_cap * sizeof(float));
  if (xs == NULL) {
    return MY_RET_OOM;
  }
  for (y = clip->y; y < clip->y + clip->h; y++) {
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
  return MY_RET_OK;
}

/** @brief One segment as a quad expanded along its normal. */
static void geo_segment(my_vggeometry_t* g, float x0, float y0, float x1,
                        float y1, float half_w) {
  float dx = x1 - x0;
  float dy = y1 - y0;
  float len = sqrtf(dx * dx + dy * dy);
  float nx, ny;
  if (len < 0.001f) {
    my_vggeometry_rect(g, x0 - half_w, y0 - half_w, x0 + half_w,
                       y0 + half_w);
    return;
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
                  half_w);
      /* round joins: half-lw disk at each interior vertex (same coverage
       * rule as soft: not at vertex 0 of closed contours) */
      if (join == MY_LINE_JOIN_ROUND && i + 1 < c->count) {
        my_vggeometry_circle_fan(g, g->points[c->start + j].x,
                                 g->points[c->start + j].y, half_w, 8);
      }
    }
  }
  return MY_RET_OK;
}
