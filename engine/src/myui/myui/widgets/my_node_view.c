/**
 * @file my_node_view.c
 * @brief Node editor canvas implementation (M19b).
 */
#include "myui/widgets/my_node_view.h"

#include <math.h>
#include <stdlib.h>
#include <string.h>

#include "myc/my_darray.h"
#include "myc/my_str.h"
#include "myr/my_bezier.h"
#include "myui/my_theme.h"
#include "myui/my_window.h"

typedef struct node_link_t {
  my_widget_t* out_node; /**< weak (tree-owned node) */
  size_t out_slot;
  my_widget_t* in_node;
  size_t in_slot;
} node_link_t;

typedef struct link_preview_t {
  bool active;
  my_widget_t* out_node; /**< weak: source socket's node */
  size_t out_slot;
  int32_t cur_x, cur_y;  /**< cursor (CANVAS coords) */
  /* magnet (M20a): snapped target socket or NULL */
  my_widget_t* magnet_node;
  size_t magnet_slot;
} link_preview_t;

typedef struct my_node_view_t {
  my_widget_t base;
  my_darray_t* links; /**< node_link_t* */
  link_preview_t preview;
  int32_t selected;     /**< link index, -1 = none */
  my_widget_t* selected_node; /**< weak, NULL = none (M20a) */
  bool panning;
  int32_t pan_x, pan_y; /**< last pointer pos (screen local) */
  float zoom;           /**< 0.25..2.0 (M20a) */
  float pan_off_x;      /**< screen-px offset: screen = canvas*zoom+off */
  float pan_off_y;
  /* node dragging (moved here from my_node: ALL pointer logic lives in
   * the view so the canvas/screen transform stays in one place) */
  my_widget_t* drag_node;
  float drag_cx, drag_cy; /**< grab point (canvas coords) */
  /* M20b: multi-select (rubber band) */
  my_darray_t* selection; /**< my_widget_t* weak node refs */
  bool banding;           /**< rubber-band drag in progress */
  float band_x0, band_y0; /**< band start (canvas) */
  float band_x1, band_y1; /**< band current (canvas) */
  bool band_moved;        /**< drag exceeded the click threshold */
  /* M20b: link flow (marching dashes, 33ms tick) */
  float flow_offset;
  uint32_t flow_timer;    /**< loop timer id, 0 = unmounted */
  bool flow_all;          /**< flow ALL links (default: selected only) */
  /* M20b: minimap (floating child, painted last) */
  my_widget_t* minimap;   /**< weak (tree ref) */
  /* M23c: embedded-widget grab for zoom != 1. The generic hit_test walks
   * SCREEN coords against CANVAS-space child rects, so at zoom != 1 an
   * embedded control (slider...) is unreachable and the event lands on
   * the view instead; the view then re-dispatches it in canvas space */
  my_widget_t* child_grab; /**< weak, NULL = none */
} my_node_view_t;

#define NV_ZOOM_MIN 0.25f
#define NV_ZOOM_MAX 2.0f
#define NV_MAGNET_DIST 20.0f /* px, canvas coords */

/* forward decls (defined in the link geometry section) */
typedef struct link_pts_t {
  float xs[256];
  float ys[256];
  int n;
} link_pts_t;
static my_ret_t link_pts_emit(void* ctx, float x, float y);
static void nv_flow_sync_timer(my_node_view_t* v);

/* ---------------- selection set (M20b) ---------------- */

bool my_node_view_is_selected(const my_widget_t* view,
                              const my_widget_t* node) {
  const my_node_view_t* v = (const my_node_view_t*)view;
  size_t i, n;
  if (view == NULL || node == NULL) {
    return false;
  }
  n = my_darray_size(v->selection);
  for (i = 0; i < n; i++) {
    if (my_darray_get(v->selection, i) == node) {
      return true;
    }
  }
  return false;
}

size_t my_node_view_selected_count(const my_widget_t* view) {
  return view != NULL
             ? my_darray_size(((const my_node_view_t*)view)->selection)
             : 0;
}

my_widget_t* my_node_view_selected_at(const my_widget_t* view, size_t i) {
  const my_node_view_t* v = (const my_node_view_t*)view;
  if (view == NULL || i >= my_darray_size(v->selection)) {
    return NULL;
  }
  return (my_widget_t*)my_darray_get(v->selection, i);
}

static void nv_select_single(my_node_view_t* v, my_widget_t* node) {
  my_darray_clear(v->selection);
  if (node != NULL) {
    my_darray_push(v->selection, node);
  }
  v->selected_node = node;
  my_widget_invalidate((my_widget_t*)v, NULL);
}

static void nv_select_toggle(my_node_view_t* v, my_widget_t* node) {
  size_t i, n = my_darray_size(v->selection);
  for (i = 0; i < n; i++) {
    if (my_darray_get(v->selection, i) == node) {
      my_darray_remove_at(v->selection, i);
      if (v->selected_node == node) {
        v->selected_node = NULL;
      }
      my_widget_invalidate((my_widget_t*)v, NULL);
      return;
    }
  }
  my_darray_push(v->selection, node);
  v->selected_node = node;
  my_widget_invalidate((my_widget_t*)v, NULL);
}

static void nv_select_clear(my_node_view_t* v) {
  if (my_darray_size(v->selection) > 0 || v->selected_node != NULL) {
    my_darray_clear(v->selection);
    v->selected_node = NULL;
    my_widget_invalidate((my_widget_t*)v, NULL);
  }
}

/* ---------------- coordinate model (M20a) ----------------
 * screen (view-local px) = canvas * zoom + pan_off */

void my_node_view_screen_to_canvas(const my_widget_t* view, int32_t sx,
                                   int32_t sy, float* cx, float* cy) {
  const my_node_view_t* v = (const my_node_view_t*)view;
  *cx = ((float)sx - v->pan_off_x) / v->zoom;
  *cy = ((float)sy - v->pan_off_y) / v->zoom;
}

void my_node_view_canvas_to_screen(const my_widget_t* view, float cx,
                                   float cy, float* sx, float* sy) {
  const my_node_view_t* v = (const my_node_view_t*)view;
  *sx = cx * v->zoom + v->pan_off_x;
  *sy = cy * v->zoom + v->pan_off_y;
}

void my_node_view_set_zoom(my_widget_t* view, float zoom) {
  my_node_view_t* v = (my_node_view_t*)view;
  if (view == NULL) {
    return;
  }
  if (zoom < NV_ZOOM_MIN) {
    zoom = NV_ZOOM_MIN;
  }
  if (zoom > NV_ZOOM_MAX) {
    zoom = NV_ZOOM_MAX;
  }
  if (zoom != v->zoom) {
    v->zoom = zoom;
    my_widget_invalidate(view, NULL);
  }
}

float my_node_view_get_zoom(const my_widget_t* view) {
  return view != NULL ? ((const my_node_view_t*)view)->zoom : 1.0f;
}

void my_node_view_zoom_at(my_widget_t* view, int32_t sx, int32_t sy,
                          float factor) {
  my_node_view_t* v = (my_node_view_t*)view;
  float cx, cy, nz;
  if (view == NULL || factor <= 0.0f) {
    return;
  }
  my_node_view_screen_to_canvas(view, sx, sy, &cx, &cy);
  nz = v->zoom * factor;
  if (nz < NV_ZOOM_MIN) {
    nz = NV_ZOOM_MIN;
  }
  if (nz > NV_ZOOM_MAX) {
    nz = NV_ZOOM_MAX;
  }
  /* keep the anchor's canvas coordinate: off = screen - canvas*zoom */
  v->zoom = nz;
  v->pan_off_x = (float)sx - cx * nz;
  v->pan_off_y = (float)sy - cy * nz;
  my_widget_invalidate(view, NULL);
}

/* ---------------- link flow (M20b) ---------------- */

void my_node_view_set_flow_enabled(my_widget_t* view, bool enabled) {
  my_node_view_t* v = (my_node_view_t*)view;
  if (view == NULL) {
    return;
  }
  v->flow_all = enabled;
  nv_flow_sync_timer(v);
  my_widget_invalidate(view, NULL);
}

bool my_node_view_get_flow_enabled(const my_widget_t* view) {
  return view != NULL ? ((const my_node_view_t*)view)->flow_all : false;
}

float my_node_view_flow_offset(const my_widget_t* view) {
  return view != NULL ? ((const my_node_view_t*)view)->flow_offset : 0.0f;
}

void my_node_view_get_pan(const my_widget_t* view, float* out_x,
                          float* out_y) {
  const my_node_view_t* v = (const my_node_view_t*)view;
  if (out_x != NULL) {
    *out_x = view != NULL ? v->pan_off_x : 0.0f;
  }
  if (out_y != NULL) {
    *out_y = view != NULL ? v->pan_off_y : 0.0f;
  }
}

/** @brief 33ms tick: advance the dash phase (marching ants). M21a: step
 * 0.5px/tick ≈ 15px/s (was 1.5 ≈ 45px/s — too frantic). */
static my_ret_t nv_flow_tick(void* ctx) {
  my_node_view_t* v = (my_node_view_t*)ctx;
  v->flow_offset += 0.5f;
  if (v->flow_offset > 100000.0f) {
    v->flow_offset = 0.0f;
  }
  my_widget_invalidate((my_widget_t*)v, NULL);
  return MY_RET_OK; /* reschedule */
}

/** @brief Mount/unmount the flow timer by demand (selected link or
 * global flow). */
static void nv_flow_sync_timer(my_node_view_t* v) {
  bool want = v->flow_all || v->selected >= 0;
  my_pal_main_loop_t* loop = my_window_loop_of_widget((my_widget_t*)v);
  if (want && v->flow_timer == 0 && loop != NULL) {
    v->flow_timer =
        my_pal_main_loop_add_timer(loop, nv_flow_tick, v, 33);
  } else if (!want && v->flow_timer != 0 && loop != NULL) {
    my_pal_main_loop_remove_timer(loop, v->flow_timer);
    v->flow_timer = 0;
  }
}

/** @brief Stroke a bezier as marching dashes (dash 8 / gap 6 since M21a,
 * phase -offset). Same sampling as the solid path (my_bezier). */
static void nv_stroke_link_dashed(my_widget_t* widget, my_vgcanvas_t* vg,
                                  float x0, float y0, float cx1, float cy1,
                                  float cx2, float cy2, float x1, float y1,
                                  float offset, uint32_t rgba) {
  link_pts_t pts;
  int i;
  float dash = 8.0f, period = 14.0f;
  float phase;
  float acc = 0.0f;
  float px = x0, py = y0;
  bool pen = false;
  my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(rgba));
  my_vgcanvas_set_line_width(vg, 3);
  my_vgcanvas_begin_path(vg);
  phase = -offset;
  while (phase < 0.0f) {
    phase += period;
  }
  pts.n = 1;
  pts.xs[0] = x0;
  pts.ys[0] = y0;
  my_bezier_cubic_to_lines(x0, y0, cx1, cy1, cx2, cy2, x1, y1, 0.25f, 16,
                           link_pts_emit, &pts, NULL);
  my_vgcanvas_move_to(vg, x0, y0);
  for (i = 0; i + 1 < pts.n; i++) {
    float seg = 1.0f; /* sub-segments are ~0.25-2px: march by whole pts */
    float mx = pts.xs[i + 1], my = pts.ys[i + 1];
    float dx = mx - px, dy = my - py;
    seg = sqrtf(dx * dx + dy * dy);
    acc += seg;
    {
      bool in_dash = fmodf(acc + phase, period) < dash;
      if (in_dash && !pen) {
        my_vgcanvas_move_to(vg, px, py);
        pen = true;
      }
      if (in_dash) {
        my_vgcanvas_line_to(vg, mx, my);
      } else {
        pen = false;
      }
    }
    px = mx;
    py = my;
  }
  my_vgcanvas_stroke(vg);
  (void)widget;
}

static node_link_t* nv_link_find_in(my_node_view_t* v, my_widget_t* in_node,
                                    size_t in_slot) {
  size_t i, n = my_darray_size(v->links);
  for (i = 0; i < n; i++) {
    node_link_t* l = (node_link_t*)my_darray_get(v->links, i);
    if (l->in_node == in_node && l->in_slot == in_slot) {
      return l;
    }
  }
  return NULL;
}

/** @brief Socket center under (x, y) within the hit radius. */
static bool nv_socket_at(my_node_view_t* v, int32_t x, int32_t y,
                         my_socket_dir_t dir, my_widget_t** out_node,
                         size_t* out_slot) {
  size_t ci, cn = my_widget_child_count((my_widget_t*)v);
  for (ci = 0; ci < cn; ci++) {
    my_widget_t* node = my_widget_get_child((my_widget_t*)v, ci);
    size_t i, cnt;
    if (node->floating) {
      continue; /* overlay/minimap is not a node (M20b) */
    }
    cnt = my_node_socket_count(node, dir);
    for (i = 0; i < cnt; i++) {
      int32_t sx = 0, sy = 0;
      if (my_node_socket_center(node, dir, i, &sx, &sy) &&
          abs(x - sx) <= MY_NODE_SOCKET_HIT &&
          abs(y - sy) <= MY_NODE_SOCKET_HIT) {
        *out_node = node;
        *out_slot = i;
        return true;
      }
    }
  }
  return false;
}

/* ---------------- model API ---------------- */

my_ret_t my_node_view_connect(my_widget_t* view, my_widget_t* out_node,
                              size_t out_slot, my_widget_t* in_node,
                              size_t in_slot) {
  my_node_view_t* v = (my_node_view_t*)view;
  node_link_t* l;
  if (view == NULL || out_node == NULL || in_node == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  /* input slots are unique: replace (Blender semantics, documented) */
  l = nv_link_find_in(v, in_node, in_slot);
  if (l == NULL) {
    l = (node_link_t*)my_mem_calloc(((my_object_t*)view)->allocator, 1,
                                    sizeof(node_link_t));
    if (l == NULL) {
      return MY_RET_OOM;
    }
    if (my_darray_push(v->links, l) != MY_RET_OK) {
      my_mem_free(((my_object_t*)view)->allocator, l);
      return MY_RET_OOM;
    }
  }
  l->out_node = out_node;
  l->out_slot = out_slot;
  l->in_node = in_node;
  l->in_slot = in_slot;
  my_widget_invalidate(view, NULL);
  my_emitter_emit(view->emitter, "changed", NULL);
  return MY_RET_OK;
}

my_ret_t my_node_view_remove_node(my_widget_t* view, const char* node_id) {
  my_node_view_t* v = (my_node_view_t*)view;
  size_t ci, n;
  size_t li;
  if (view == NULL || node_id == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  n = my_widget_child_count(view);
  for (ci = 0; ci < n; ci++) {
    my_widget_t* node = my_widget_get_child(view, ci);
    const char* id;
    if (node->floating) {
      continue; /* overlay is not a node (M20b) */
    }
    id = my_node_get_id(node);
    if (id != NULL && strcmp(id, node_id) == 0) {
      /* cascade: drop every link referencing this node */
      li = 0;
      while (li < my_darray_size(v->links)) {
        node_link_t* l = (node_link_t*)my_darray_get(v->links, li);
        if (l->out_node == node || l->in_node == node) {
          my_mem_free(((my_object_t*)view)->allocator, l);
          my_darray_remove_at(v->links, li);
        } else {
          li++;
        }
      }
      if (v->selected_node == node) {
        v->selected_node = NULL;
      }
      /* M20b: also purge from the selection set */
      {
        size_t si = 0;
        while (si < my_darray_size(v->selection)) {
          if (my_darray_get(v->selection, si) == node) {
            my_darray_remove_at(v->selection, si);
          } else {
            si++;
          }
        }
      }
      if (v->preview.active && v->preview.out_node == node) {
        v->preview.active = false;
        v->preview.out_node = NULL;
        v->preview.magnet_node = NULL;
      }
      if (v->drag_node == node) {
        v->drag_node = NULL;
      }
      v->selected = -1;
      /* the tree held the node's only reference (add_node unreffed
       * after add_child) — remove_child destroys it right here */
      my_widget_remove_child(view, node);
      my_widget_invalidate(view, NULL);
      my_emitter_emit(view->emitter, "changed", NULL);
      return MY_RET_OK;
    }
  }
  return MY_RET_NOT_FOUND;
}

my_ret_t my_node_view_disconnect_in(my_widget_t* view, my_widget_t* in_node,
                                    size_t in_slot) {
  my_node_view_t* v = (my_node_view_t*)view;
  size_t i, n;
  if (view == NULL || in_node == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  n = my_darray_size(v->links);
  for (i = 0; i < n; i++) {
    node_link_t* l = (node_link_t*)my_darray_get(v->links, i);
    if (l->in_node == in_node && l->in_slot == in_slot) {
      my_mem_free(((my_object_t*)view)->allocator, l);
      my_darray_remove_at(v->links, i);
      v->selected = -1;
      my_widget_invalidate(view, NULL);
      my_emitter_emit(view->emitter, "changed", NULL);
      return MY_RET_OK;
    }
  }
  return MY_RET_NOT_FOUND;
}

size_t my_node_view_link_count(const my_widget_t* view) {
  const my_node_view_t* v = (const my_node_view_t*)view;
  return view != NULL ? my_darray_size(v->links) : 0;
}

bool my_node_view_get_link(const my_widget_t* view, size_t index,
                           my_widget_t** out_node, size_t* out_slot,
                           my_widget_t** in_node, size_t* in_slot) {
  const my_node_view_t* v = (const my_node_view_t*)view;
  node_link_t* l;
  if (view == NULL || index >= my_darray_size(v->links)) {
    return false;
  }
  l = (node_link_t*)my_darray_get(v->links, index);
  if (out_node != NULL) *out_node = l->out_node;
  if (out_slot != NULL) *out_slot = l->out_slot;
  if (in_node != NULL) *in_node = l->in_node;
  if (in_slot != NULL) *in_slot = l->in_slot;
  return true;
}

int32_t my_node_view_get_selected(const my_widget_t* view) {
  return view != NULL ? ((const my_node_view_t*)view)->selected : -1;
}

void my_node_view_pan_by(my_widget_t* view, int32_t dx, int32_t dy) {
  my_node_view_t* v = (my_node_view_t*)view;
  if (view == NULL) {
    return;
  }
  /* M20a: pan is a view-level screen-px offset (node rects stay in
   * canvas coords) */
  v->pan_off_x += (float)dx;
  v->pan_off_y += (float)dy;
  my_widget_invalidate(view, NULL);
}

/* ---------------- link geometry ---------------- */

/** @brief Bezier endpoints/handles for a link (or preview). */
static bool nv_link_geo(my_widget_t* out_node, size_t out_slot,
                        my_widget_t* in_node, size_t in_slot, float* x0,
                        float* y0, float* cx1, float* cy1, float* cx2,
                        float* cy2, float* x1, float* y1) {
  int32_t ix0 = 0, iy0 = 0, ix1 = 0, iy1 = 0;
  float dx;
  if (!my_node_socket_center(out_node, MY_SOCKET_OUT, out_slot, &ix0, &iy0) ||
      !my_node_socket_center(in_node, MY_SOCKET_IN, in_slot, &ix1, &iy1)) {
    return false;
  }
  dx = (float)abs(ix1 - ix0) * 0.5f;
  if (dx < 40.0f) {
    dx = 40.0f; /* Blender-like horizontal tangents */
  }
  *x0 = (float)ix0;
  *y0 = (float)iy0;
  *x1 = (float)ix1;
  *y1 = (float)iy1;
  *cx1 = *x0 + dx;
  *cy1 = *y0;
  *cx2 = *x1 - dx;
  *cy2 = *y1;
  return true;
}

/** @brief Subdivide ctx for find_link_at. */
static my_ret_t link_pts_emit(void* ctx, float x, float y) {
  link_pts_t* p = (link_pts_t*)ctx;
  if (p->n < 256) {
    p->xs[p->n] = x;
    p->ys[p->n] = y;
    p->n++;
  }
  return MY_RET_OK;
}

/** @brief Min distance from (px, py) to the polyline. */
static float link_pts_dist(const link_pts_t* p, float px, float py) {
  int i;
  float best = 1e9f;
  for (i = 0; i + 1 < p->n; i++) {
    float ax = p->xs[i], ay = p->ys[i], bx = p->xs[i + 1], by = p->ys[i + 1];
    float dx = bx - ax, dy = by - ay;
    float len2 = dx * dx + dy * dy;
    float t = len2 > 1e-9f
                  ? ((px - ax) * dx + (py - ay) * dy) / len2
                  : 0.0f;
    float qx, qy, ddx, ddy;
    if (t < 0.0f) t = 0.0f;
    if (t > 1.0f) t = 1.0f;
    qx = ax + t * dx;
    qy = ay + t * dy;
    ddx = px - qx;
    ddy = py - qy;
    if (ddx * ddx + ddy * ddy < best) {
      best = ddx * ddx + ddy * ddy;
    }
  }
  return best; /* squared */
}

int32_t my_node_view_find_link_at(my_widget_t* view, int32_t x, int32_t y) {
  my_node_view_t* v = (my_node_view_t*)view;
  size_t i, n;
  if (view == NULL) {
    return -1;
  }
  n = my_darray_size(v->links);
  for (i = n; i > 0; i--) { /* later links win on overlap */
    node_link_t* l = (node_link_t*)my_darray_get(v->links, i - 1);
    float x0, y0, cx1, cy1, cx2, cy2, x1, y1;
    link_pts_t pts;
    if (!nv_link_geo(l->out_node, l->out_slot, l->in_node, l->in_slot, &x0,
                     &y0, &cx1, &cy1, &cx2, &cy2, &x1, &y1)) {
      continue;
    }
    pts.n = 0;
    pts.xs[0] = x0;
    pts.ys[0] = y0;
    pts.n = 1;
    my_bezier_cubic_to_lines(x0, y0, cx1, cy1, cx2, cy2, x1, y1, 0.25f, 16,
                             link_pts_emit, &pts, NULL);
    if (link_pts_dist(&pts, (float)x, (float)y) <= 64.0f) { /* 8px */
      return (int32_t)(i - 1);
    }
  }
  return -1;
}

/* ---------------- paint ---------------- */

static void nv_stroke_link(my_widget_t* widget, my_vgcanvas_t* vg, float x0,
                           float y0, float cx1, float cy1, float cx2,
                           float cy2, float x1, float y1,
                           const char* cls, uint32_t fallback) {
  uint32_t c = my_widget_part_color(widget, "node_link", cls,
                                    MY_STATE_NORMAL, MY_STYLE_FG_COLOR, fallback);
  my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(c));
  my_vgcanvas_set_line_width(vg, 3);
  my_vgcanvas_begin_path(vg);
  my_vgcanvas_move_to(vg, x0, y0);
  my_vgcanvas_curve_to(vg, cx1, cy1, cx2, cy2, x1, y1);
  my_vgcanvas_stroke(vg);
}

/** @brief Solid link stroke with an already-resolved color (M21b). */
static void nv_stroke_link_rgba(my_vgcanvas_t* vg, float x0, float y0,
                                float cx1, float cy1, float cx2, float cy2,
                                float x1, float y1, uint32_t rgba) {
  my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(rgba));
  my_vgcanvas_set_line_width(vg, 3);
  my_vgcanvas_begin_path(vg);
  my_vgcanvas_move_to(vg, x0, y0);
  my_vgcanvas_curve_to(vg, cx1, cy1, cx2, cy2, x1, y1);
  my_vgcanvas_stroke(vg);
}

static void nv_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  my_node_view_t* v = (my_node_view_t*)widget;
  uint32_t bg = my_widget_style_get_color(widget, MY_STATE_NORMAL,
                                          MY_STYLE_BG_COLOR, 0x282828FFu);
  size_t i, n;
  /* keep the overlay full-span HERE (view on_paint runs before the
   * children): my_widget_paint clips each child to its rect BEFORE its
   * on_paint, so syncing inside the overlay paint would clip the very
   * first frame to the stale 0x0 rect (M21b first-frame minimap bug) */
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(bg));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                          (float)widget->rect.h});
  /* AA 固化（M20a）：连线/圆点走 level 2 覆盖率 AA，不依赖调用方
   * 状态（soft 默认已是 2；幂等设置，gles 端走 MSAA 路径——注释） */
  (void)my_vgcanvas_set_antialias_level(vg, 2);
  /* canvas transform: device = (canvas + pan/zoom) * zoom (soft CTM is
   * (x+tx)*scale; HiDPI 下 window 的 base scale 由 restore 还原，故
   * 这里取 window 基础 scale 相乘） */
  if (v->zoom != 1.0f || v->pan_off_x != 0.0f || v->pan_off_y != 0.0f) {
    my_widget_t* root = widget;
    float base_scale = 1.0f;
    while (root->parent != NULL) {
      root = root->parent;
    }
    if (my_str_eq(root->widget_type, "window")) {
      base_scale = ((my_window_t*)root)->scale;
    }
    if (getenv("MYUI_NV_TRACE") != NULL) {
      fprintf(stderr, "[nvtrace] ctm zoom=%.3f pan=(%.1f,%.1f) tx=(%.1f,%.1f)\n",
              (double)v->zoom, (double)v->pan_off_x, (double)v->pan_off_y,
              (double)(v->pan_off_x / (base_scale * v->zoom)),
              (double)(v->pan_off_y / (base_scale * v->zoom)));
    }
    {
      /* scale ABOUT the view origin (M23): my_widget_paint already
       * translated by the ancestor chain (viewT) in unscaled units, so a
       * plain pan/(b*z) translate would scale viewT too — device coords
       * then disagree with canvas_to_screen/screen_to_canvas by
       * viewT*(z-1), which made clicks and overlay rings miss by up to
       * 72px at deep zoom. Correct translate: ((viewT+pan)/(b*z))-viewT. */
      float vx = (float)widget->rect.x, vy = (float)widget->rect.y;
      float dx, dy;
      my_widget_t* par = widget->parent;
      while (par != NULL) {
        vx += (float)par->rect.x;
        vy += (float)par->rect.y;
        par = par->parent;
      }
      dx = (vx + v->pan_off_x) / (base_scale * v->zoom) - vx;
      dy = (vy + v->pan_off_y) / (base_scale * v->zoom) - vy;
      my_vgcanvas_translate(vg, dx, dy);
      (void)my_vgcanvas_set_scale(vg, base_scale * v->zoom);
    }
  }
  /* links (nodes paint after us: children over links) */
  n = my_darray_size(v->links);
  for (i = 0; i < n; i++) {
    node_link_t* l = (node_link_t*)my_darray_get(v->links, i);
    float x0, y0, cx1, cy1, cx2, cy2, x1, y1;
    bool sel;
    uint32_t fb, c;
    if (!nv_link_geo(l->out_node, l->out_slot, l->in_node, l->in_slot, &x0,
                     &y0, &cx1, &cy1, &cx2, &cy2, &x1, &y1)) {
      continue;
    }
    sel = (int32_t)i == v->selected;
    /* M21b: unselected links tint from their SOURCE socket's type color
     * (theme `node_link` still wins via the part lookup) */
    fb = 0xE0A030FFu;
    if (!sel) {
      fb = my_node_socket_type_color(l->out_node, MY_SOCKET_OUT,
                                     l->out_slot);
      if (fb == 0) {
        fb = 0xA0A0A0FFu; /* pre-M21b default grey */
      }
    }
    c = my_widget_part_color(widget, "node_link", sel ? "selected" : NULL,
                             MY_STATE_NORMAL, MY_STYLE_FG_COLOR, fb);
    if (v->flow_all || sel) {
      /* M20b: marching dashes (selected always flows; flow_all covers
       * everything) */
      nv_stroke_link_dashed(widget, vg, x0, y0, cx1, cy1, cx2, cy2, x1, y1,
                            v->flow_offset, c);
    } else {
      nv_stroke_link_rgba(vg, x0, y0, cx1, cy1, cx2, cy2, x1, y1, c);
    }
    /* arrowhead + flow pulse in CANVAS space (same CTM as the curve, so
     * alignment is by construction), sizes zoom-compensated so they stay
     * ~10px/~4px on screen at any zoom (M23) */
    {
      float dx = x1 - cx2, dy = y1 - cy2, len = sqrtf(dx * dx + dy * dy);
      if (len > 1e-6f) {
        float ux = dx / len, uy = dy / len;
        float alen = 10.0f / v->zoom, aw = 5.0f / v->zoom;
        my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(c));
        my_vgcanvas_begin_path(vg);
        my_vgcanvas_move_to(vg, x1, y1);
        my_vgcanvas_line_to(vg, x1 - ux * alen - uy * aw,
                            y1 - uy * alen + ux * aw);
        my_vgcanvas_line_to(vg, x1 - ux * alen + uy * aw,
                            y1 - uy * alen - ux * aw);
        my_vgcanvas_close_path(vg);
        my_vgcanvas_fill(vg);
      }
      if (v->flow_all || sel) {
        link_pts_t pts;
        float bx = x1, by = y1;
        pts.n = 0;
        pts.xs[0] = x0;
        pts.ys[0] = y0;
        pts.n = 1;
        my_bezier_cubic_to_lines(x0, y0, cx1, cy1, cx2, cy2, x1, y1, 0.25f,
                                 16, link_pts_emit, &pts, NULL);
        {
          float acc = 0.0f, total = 0.0f, target;
          float tt = fmodf(v->flow_offset / 160.0f, 1.0f);
          int k;
          for (k = 1; k < pts.n; k++) {
            float ddx = pts.xs[k] - pts.xs[k - 1];
            float ddy = pts.ys[k] - pts.ys[k - 1];
            total += sqrtf(ddx * ddx + ddy * ddy);
          }
          target = tt * (total > 0.0f ? total : 1.0f);
          for (k = 1; k < pts.n && acc < target; k++) {
            float ddx = pts.xs[k] - pts.xs[k - 1];
            float ddy = pts.ys[k] - pts.ys[k - 1];
            float seg = sqrtf(ddx * ddx + ddy * ddy);
            if (acc + seg >= target && seg > 1e-6f) {
              float f = (target - acc) / seg;
              bx = pts.xs[k - 1] + ddx * f;
              by = pts.ys[k - 1] + ddy * f;
              break;
            }
            acc += seg;
          }
        }
        my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(c));
        my_vgcanvas_begin_path(vg);
        my_node_path_circle(vg, bx, by, 4.0f / v->zoom);
        my_vgcanvas_fill(vg);
      }
    }
  }
  /* link preview follows the cursor (magnet-snapped when a target is
   * in range; the snapped socket gets a highlight ring) */
  if (v->preview.active && v->preview.out_node != NULL) {
    int32_t ix0 = 0, iy0 = 0;
    if (my_node_socket_center(v->preview.out_node, MY_SOCKET_OUT,
                              v->preview.out_slot, &ix0, &iy0)) {
      float tx = (float)v->preview.cur_x;
      float ty = (float)v->preview.cur_y;
      if (v->preview.magnet_node != NULL) {
        int32_t mx = 0, my = 0;
        if (my_node_socket_center(v->preview.magnet_node, MY_SOCKET_IN,
                                  v->preview.magnet_slot, &mx, &my)) {
          tx = (float)mx;
          ty = (float)my;
        }
      }
      {
        float dx = fabsf(tx - (float)ix0) * 0.5f;
        if (dx < 40.0f) {
          dx = 40.0f;
        }
        /* no arrowhead on the preview (it would chase the cursor) */
        nv_stroke_link(widget, vg, (float)ix0, (float)iy0, (float)ix0 + dx,
                       (float)iy0, tx - dx, ty, tx, ty, "preview",
                       0x70C0E8FFu);
      }
    }
  }
  /* M21b: the magnet ring moved to the overlay paint (it must sit ABOVE
   * the nodes and their selection borders, which paint after us) */
}

/* ---------------- overlay: rubber band + minimap (M20b) ----------------
 * A floating child painted AFTER the nodes; it resets the canvas CTM
 * (soft CTM is absolute-settable: scale setter + inverse translate). */

#define NV_MINIMAP_W 160
#define NV_MINIMAP_H 100

/** @brief Visible bottom-right extent of the view in VIEW-LOCAL coords
 * (M21a): the view's own rect intersected with every ancestor's clip
 * (my_widget_paint clips children to the parent rect). When the view
 * overflows its container — e.g. a CSD content container 36px shorter
 * than the window while the app sized the view for the full window —
 * the minimap anchors to the VISIBLE bottom-right instead of the
 * clipped-away rect corner. Pure translations only (no scaling between
 * widget rects). */
static void nv_visible_extent(const my_widget_t* w, float* out_x1,
                              float* out_y1) {
  float x1 = (float)w->rect.w, y1 = (float)w->rect.h;
  int32_t ox = w->rect.x, oy = w->rect.y; /* view origin, ancestor space */
  const my_widget_t* p = w->parent;
  while (p != NULL) {
    float ex = (float)p->rect.w - (float)ox; /* parent edges, view-local */
    float ey = (float)p->rect.h - (float)oy;
    if (ex < x1) {
      x1 = ex;
    }
    if (ey < y1) {
      y1 = ey;
    }
    ox += p->rect.x;
    oy += p->rect.y;
    p = p->parent;
  }
  *out_x1 = x1 > 0.0f ? x1 : 0.0f;
  *out_y1 = y1 > 0.0f ? y1 : 0.0f;
}

/** @brief Minimap top-left in view-local screen coords (shared by the
 * overlay paint and the DOWN hit test so they never disagree). */
static void nv_minimap_origin(const my_widget_t* w, float* mx, float* my) {
  float x1 = 0.0f, y1 = 0.0f;
  nv_visible_extent(w, &x1, &y1);
  *mx = x1 - (float)NV_MINIMAP_W - 10.0f;
  *my = y1 - (float)NV_MINIMAP_H - 10.0f;
}

/** @brief Dashed rect stroke in screen space (dash 6 / gap 4). */
static void nv_dashed_rect(my_vgcanvas_t* vg, float x, float y, float w,
                           float h, uint32_t rgba) {
  static const float EDGES[4][4] = {{0, 0, 1, 0}, {1, 0, 1, 1},
                                    {1, 1, 0, 1}, {0, 1, 0, 0}};
  int e;
  my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(rgba));
  my_vgcanvas_set_line_width(vg, 1);
  for (e = 0; e < 4; e++) {
    float x0 = x + EDGES[e][0] * w, y0 = y + EDGES[e][1] * h;
    float x1 = x + EDGES[e][2] * w, y1 = y + EDGES[e][3] * h;
    float len = fabsf(x1 - x0) + fabsf(y1 - y0);
    float s;
    for (s = 0.0f; s + 6.0f <= len; s += 10.0f) {
      float t0 = s / len, t1 = (s + 6.0f) / len;
      my_vgcanvas_begin_path(vg);
      my_vgcanvas_move_to(vg, x0 + (x1 - x0) * t0, y0 + (y1 - y0) * t0);
      my_vgcanvas_line_to(vg, x0 + (x1 - x0) * t1, y0 + (y1 - y0) * t1);
      my_vgcanvas_stroke(vg);
    }
  }
}

/** @brief Minimap geometry: canvas bbox of nodes+viewport -> mini rect
 * scale. */
static void nv_minimap_fit(const my_node_view_t* v, float* bx0, float* by0,
                           float* scale) {
  my_widget_t* w = (my_widget_t*)v;
  float x0 = 0.0f, y0 = 0.0f, x1 = (float)w->rect.w, y1 = (float)w->rect.h;
  float vx0, vy0, vx1, vy1;
  size_t i, n = my_widget_child_count(w);
  float bw, bh, s1, s2;
  /* visible canvas region */
  vx0 = (0.0f - v->pan_off_x) / v->zoom;
  vy0 = (0.0f - v->pan_off_y) / v->zoom;
  vx1 = ((float)w->rect.w - v->pan_off_x) / v->zoom;
  vy1 = ((float)w->rect.h - v->pan_off_y) / v->zoom;
  x0 = vx0;
  y0 = vy0;
  x1 = vx1;
  y1 = vy1;
  for (i = 0; i < n; i++) {
    my_widget_t* node = my_widget_get_child(w, i);
    if (node->floating) {
      continue;
    }
    if (node->rect.x < x0) x0 = (float)node->rect.x;
    if (node->rect.y < y0) y0 = (float)node->rect.y;
    if (node->rect.x + node->rect.w > x1) x1 = (float)(node->rect.x + node->rect.w);
    if (node->rect.y + node->rect.h > y1) y1 = (float)(node->rect.y + node->rect.h);
  }
  x0 -= 20.0f;
  y0 -= 20.0f;
  x1 += 20.0f;
  y1 += 20.0f;
  bw = x1 - x0 > 1.0f ? x1 - x0 : 1.0f;
  bh = y1 - y0 > 1.0f ? y1 - y0 : 1.0f;
  s1 = (float)NV_MINIMAP_W / bw;
  s2 = (float)NV_MINIMAP_H / bh;
  *bx0 = x0;
  *by0 = y0;
  *scale = s1 < s2 ? s1 : s2;
}

static void nv_overlay_paint(my_widget_t* ov, my_vgcanvas_t* vg) {
  my_node_view_t* v = (my_node_view_t*)my_widget_get_user_data(ov);
  my_widget_t* w = (my_widget_t*)v;
  /* rect synced by nv_paint (before the child clip; floating, no
   * on_event -> events bubble) */
  /* reset the canvas CTM: absolute scale + translate back to the view's
   * screen origin. The inherited tx is (viewT+pan)/(base*zoom) — computed
   * for the canvas scale — so at zoom != 1 a plain -pan/(b*z) inverse
   * leaves tx = viewT/zoom instead of viewT and the whole screen-space
   * overlay (minimap, rubber band, magnet ring) drifts with the zoom
   * (M23). Bring tx to viewT exactly: */
  {
    my_widget_t* root = w;
    my_widget_t* par;
    float base = 1.0f;
    float vx = (float)w->rect.x, vy = (float)w->rect.y;
    float ddx, ddy;
    while (root->parent != NULL) {
      root = root->parent;
    }
    if (my_str_eq(root->widget_type, "window")) {
      base = ((my_window_t*)root)->scale;
    }
    for (par = w->parent; par != NULL; par = par->parent) {
      vx += (float)par->rect.x;
      vy += (float)par->rect.y;
    }
    if (v->zoom != 1.0f || v->pan_off_x != 0.0f || v->pan_off_y != 0.0f) {
      /* nv_paint left tx = (viewT+pan)/(base*zoom) at scale base*zoom */
      ddx = vx - (vx + v->pan_off_x) / (base * v->zoom);
      ddy = vy - (vy + v->pan_off_y) / (base * v->zoom);
    } else {
      /* no canvas transform: inherited tx is already viewT at scale base */
      ddx = vx - vx / base;
      ddy = vy - vy / base;
    }
    (void)my_vgcanvas_set_scale(vg, base);
    my_vgcanvas_translate(vg, ddx, ddy);
    /* the clip baked by my_widget_paint under the canvas CTM shifts with
     * pan/zoom and clips the screen-space minimap (M22); replace it */
    my_vgcanvas_reset_clip(vg, &(my_rectf_t){0, 0, (float)ov->rect.w,
                                             (float)ov->rect.h});
  }
  /* rubber band (canvas rect -> screen) */
  if (v->banding && v->band_moved) {
    float sx0, sy0, sx1, sy1;
    uint32_t border = my_widget_part_color(w, "node_view", "rubber_band",
                                           MY_STATE_NORMAL, MY_STYLE_FG_COLOR,
                                           0x4090E0FFu);
    uint32_t fill = my_widget_part_color(w, "node_view", "rubber_band",
                                         MY_STATE_NORMAL, MY_STYLE_BG_COLOR,
                                         0x4090E014u); /* ~8%: clearly translucent */
    my_node_view_canvas_to_screen(w, v->band_x0, v->band_y0, &sx0, &sy0);
    my_node_view_canvas_to_screen(w, v->band_x1, v->band_y1, &sx1, &sy1);
    if (sx1 < sx0) {
      float t = sx0;
      sx0 = sx1;
      sx1 = t;
    }
    if (sy1 < sy0) {
      float t = sy0;
      sy0 = sy1;
      sy1 = t;
    }
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(fill));
    my_vgcanvas_fill_rect(vg, &(my_rectf_t){sx0, sy0, sx1 - sx0, sy1 - sy0});
    nv_dashed_rect(vg, sx0, sy0, sx1 - sx0, sy1 - sy0, border);
  }
  /* magnet ring (M21b): painted here in the overlay — AFTER all nodes —
   * so the width-2 ring sits above the (now width-1) selection borders;
   * screen space, radius scales with the zoom like canvas strokes do */
  if (v->preview.magnet_node != NULL) {
    int32_t mcx = 0, mcy = 0;
    if (my_node_socket_center(v->preview.magnet_node, MY_SOCKET_IN,
                              v->preview.magnet_slot, &mcx, &mcy)) {
      float rsx = 0.0f, rsy = 0.0f;
      uint32_t ring = my_widget_part_color(w, "node_socket", "magnet",
                                           MY_STATE_NORMAL, MY_STYLE_BG_COLOR,
                                           0xFFD050FFu);
      my_node_view_canvas_to_screen(w, (float)mcx, (float)mcy, &rsx, &rsy);
      my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(ring));
      my_vgcanvas_set_line_width(vg, 2);
      my_vgcanvas_begin_path(vg);
      my_node_path_circle(vg, rsx, rsy, 9.0f * v->zoom);
      my_vgcanvas_stroke(vg);
    }
  }
  /* minimap (bottom-right of the VISIBLE area, screen space) */
  {
    float mx = 0.0f, my = 0.0f;
    float bx0 = 0.0f, by0 = 0.0f, s = 1.0f;
    uint32_t mbg = my_widget_part_color(w, "node_view", "minimap",
                                        MY_STATE_NORMAL, MY_STYLE_BG_COLOR,
                                        0x000000A0u);
    uint32_t vbc = my_widget_part_color(w, "node_view", "minimap_viewport",
                                        MY_STATE_NORMAL, MY_STYLE_FG_COLOR,
                                        0xFFFFFFFFu);
    size_t i, n;
    nv_minimap_origin(w, &mx, &my);
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(mbg));
    my_vgcanvas_fill_rect(vg, &(my_rectf_t){mx, my, NV_MINIMAP_W,
                                            NV_MINIMAP_H});
    nv_minimap_fit(v, &bx0, &by0, &s);
    /* node blocks */
    n = my_widget_child_count(w);
    for (i = 0; i < n; i++) {
      my_widget_t* node = my_widget_get_child(w, i);
      if (!node->floating) {
        my_vgcanvas_set_fill_color(
            vg, my_color_from_rgba32(my_widget_style_get_color(
                    node, MY_STATE_NORMAL, MY_STYLE_BG_COLOR, 0x3A3A3AFFu)));
        my_vgcanvas_fill_rect(
            vg, &(my_rectf_t){mx + ((float)node->rect.x - bx0) * s,
                              my + ((float)node->rect.y - by0) * s,
                              (float)node->rect.w * s > 2.0f
                                  ? (float)node->rect.w * s
                                  : 2.0f,
                              (float)node->rect.h * s > 2.0f
                                  ? (float)node->rect.h * s
                                  : 2.0f});
      }
    }
    /* viewport frame */
    {
      float vx0 = (0.0f - v->pan_off_x) / v->zoom;
      float vy0 = (0.0f - v->pan_off_y) / v->zoom;
      float vx1 = ((float)w->rect.w - v->pan_off_x) / v->zoom;
      float vy1 = ((float)w->rect.h - v->pan_off_y) / v->zoom;
      /* clamp the viewport frame to the minimap box (M23: it used to
       * fly outside when the canvas viewport exceeded the node span) */
      {
        float fx0 = mx + (vx0 - bx0) * s, fy0 = my + (vy0 - by0) * s;
        float fx1 = fx0 + (vx1 - vx0) * s, fy1 = fy0 + (vy1 - vy0) * s;
        if (fx0 < mx) fx0 = mx;
        if (fy0 < my) fy0 = my;
        if (fx1 > mx + NV_MINIMAP_W) fx1 = mx + NV_MINIMAP_W;
        if (fy1 > my + NV_MINIMAP_H) fy1 = my + NV_MINIMAP_H;
        if (fx1 > fx0 && fy1 > fy0) {
          my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(vbc));
          my_vgcanvas_set_line_width(vg, 1);
          my_vgcanvas_stroke_rect(vg, &(my_rectf_t){fx0, fy0, fx1 - fx0,
                                                    fy1 - fy0});
        }
      }
    }
  }
}

static const my_widget_vtable_t s_overlay_vtable = {nv_overlay_paint, NULL,
                                                    NULL, NULL};

/** @brief Jump the viewport center to a canvas point (minimap click). */
static void nv_center_on(my_node_view_t* v, float cx, float cy) {
  my_widget_t* w = (my_widget_t*)v;
  v->pan_off_x = (float)w->rect.w / 2.0f - cx * v->zoom;
  v->pan_off_y = (float)w->rect.h / 2.0f - cy * v->zoom;
  my_widget_invalidate(w, NULL);
}

/* ---------------- events ---------------- */

/** @brief Magnet scan: nearest INPUT socket within NV_MAGNET_DIST of
 * the preview cursor (canvas coords); updates preview.magnet_*. */
static void nv_magnet_scan(my_node_view_t* v, float cx, float cy) {
  size_t ci, cn = my_widget_child_count((my_widget_t*)v);
  float best = NV_MAGNET_DIST * NV_MAGNET_DIST;
  my_widget_t* best_node = NULL;
  size_t best_slot = 0;
  for (ci = 0; ci < cn; ci++) {
    my_widget_t* node = my_widget_get_child((my_widget_t*)v, ci);
    size_t i, cnt;
    if (node->floating) {
      continue; /* overlay/minimap is not a node (M20b) */
    }
    cnt = my_node_socket_count(node, MY_SOCKET_IN);
    for (i = 0; i < cnt; i++) {
      int32_t sx = 0, sy = 0;
      float dx, dy, d2;
      if (!my_node_socket_center(node, MY_SOCKET_IN, i, &sx, &sy)) {
        continue;
      }
      dx = cx - (float)sx;
      dy = cy - (float)sy;
      d2 = dx * dx + dy * dy;
      if (d2 < best) {
        best = d2;
        best_node = node;
        best_slot = i;
      }
    }
  }
  v->preview.magnet_node = best_node;
  v->preview.magnet_slot = best_node != NULL ? best_slot : 0;
}

/** @brief Node under a canvas point (topmost = last child wins). */
static my_widget_t* nv_node_at(my_node_view_t* v, float cx, float cy,
                               bool* out_titlebar) {
  size_t ci = my_widget_child_count((my_widget_t*)v);
  while (ci > 0) {
    my_widget_t* node;
    ci--;
    node = my_widget_get_child((my_widget_t*)v, ci);
    if (node->floating) {
      continue; /* overlay/minimap is not a node (M20b) */
    }
    if (cx >= node->rect.x && cx < node->rect.x + node->rect.w &&
        cy >= node->rect.y && cy < node->rect.y + node->rect.h) {
      *out_titlebar = cy < node->rect.y + MY_NODE_HEADER_H;
      return node;
    }
  }
  return NULL;
}

/** @brief Embedded interactive widget (slider...) under a CANVAS point,
 * or NULL when the point is on bare node surface (M23c). */
static my_widget_t* nv_embedded_at(my_node_view_t* v, float cx, float cy) {
  bool titlebar = false;
  my_widget_t* node = nv_node_at(v, cx, cy, &titlebar);
  my_widget_t* hit;
  if (node == NULL) {
    return NULL;
  }
  /* node rects live in canvas coords relative to the view, so (cx,cy)
   * IS the parent-space coordinate hit_test expects for the subtree */
  hit = my_widget_hit_test(node, (int32_t)cx, (int32_t)cy);
  if (hit == NULL || hit == node || hit->vtable == NULL ||
      hit->vtable->on_event == NULL) {
    return NULL;
  }
  return hit;
}

/** @brief Deliver a pointer event to an embedded widget with synthesized
 * "global" coords (M23c): children do their own global_to_local math
 * over ancestor rects, which are canvas coords — so the synth global is
 * the canvas point offset by the view's global origin. */
static bool nv_deliver_canvas(my_widget_t* widget, my_widget_t* target,
                              const my_event_t* event, float cx, float cy) {
  my_event_t synth = *event;
  int32_t gx = 0, gy = 0;
  my_widget_local_to_global(widget, &gx, &gy);
  synth.u.pointer.x = (int32_t)cx + gx;
  synth.u.pointer.y = (int32_t)cy + gy;
  return target->vtable->on_event(target, &synth) == MY_RET_OK;
}

static my_ret_t nv_event(my_widget_t* widget, const my_event_t* event) {
  my_node_view_t* v = (my_node_view_t*)widget;
  switch (event->type) {
    case MY_EVENT_POINTER_DOWN: {
      int32_t lx = event->u.pointer.x, ly = event->u.pointer.y;
      float cx, cy;
      my_widget_t* node = NULL;
      size_t slot = 0;
      my_widget_global_to_local(widget, &lx, &ly);
      if (getenv("MYUI_NV_TRACE") != NULL) {
        fprintf(stderr, "[nvtrace] DOWN g=(%d,%d) local=(%d,%d)\n",
                event->u.pointer.x, event->u.pointer.y, lx, ly);
      }
      /* minimap click: jump the viewport (screen space, BEFORE the
       * canvas transform) */
      {
        float mx = 0.0f, my = 0.0f;
        nv_minimap_origin(widget, &mx, &my);
        if ((float)lx >= mx && (float)lx < mx + NV_MINIMAP_W &&
            (float)ly >= my && (float)ly < my + NV_MINIMAP_H) {
          float bx0 = 0.0f, by0 = 0.0f, s = 1.0f;
          nv_minimap_fit(v, &bx0, &by0, &s);
          nv_center_on(v, bx0 + ((float)lx - mx) / s,
                       by0 + ((float)ly - my) / s);
          return MY_RET_OK;
        }
      }
      my_node_view_screen_to_canvas(widget, lx, ly, &cx, &cy);
      if (getenv("MYUI_NV_TRACE") != NULL) {
        fprintf(stderr, "[nvtrace] canvas=(%.1f,%.1f)\n", cx, cy);
      }
      v->child_grab = NULL;
      /* drag out of an output socket: preview */
      if (nv_socket_at(v, (int32_t)cx, (int32_t)cy, MY_SOCKET_OUT, &node,
                       &slot)) {
        v->preview.active = true;
        v->preview.out_node = node;
        v->preview.out_slot = slot;
        v->preview.cur_x = (int32_t)cx;
        v->preview.cur_y = (int32_t)cy;
        v->preview.magnet_node = NULL; /* magnet scans on MOVE only —
                                        * DOWN must not snap */
        my_widget_invalidate(widget, NULL);
        return MY_RET_OK;
      }
      /* drag out of a CONNECTED input socket: pick the link up */
      if (nv_socket_at(v, (int32_t)cx, (int32_t)cy, MY_SOCKET_IN, &node,
                       &slot) &&
          nv_link_find_in(v, node, slot) != NULL) {
        node_link_t* l = nv_link_find_in(v, node, slot);
        my_widget_t* out_node = l->out_node;
        size_t out_slot = l->out_slot;
        my_node_view_disconnect_in(widget, node, slot); /* emits changed */
        v->preview.active = true;
        v->preview.out_node = out_node;
        v->preview.out_slot = out_slot;
        v->preview.cur_x = (int32_t)cx;
        v->preview.cur_y = (int32_t)cy;
        v->preview.magnet_node = NULL; /* magnet scans on MOVE only */
        my_widget_invalidate(widget, NULL);
        return MY_RET_OK;
      }
      /* click a link: select */
      {
        int32_t li = my_node_view_find_link_at(widget, (int32_t)cx,
                                               (int32_t)cy);
        if (li >= 0) {
          v->selected = li;
          nv_select_clear(v);
          nv_flow_sync_timer(v); /* selected link starts marching */
          my_widget_invalidate(widget, NULL);
          return MY_RET_OK;
        }
      }
      /* embedded widget (slider...): only reachable via the view at
       * zoom != 1 (the generic hit_test compares screen coords against
       * canvas rects); deliver in canvas space and grab it (M23c) */
      {
        my_widget_t* emb = nv_embedded_at(v, cx, cy);
        if (emb != NULL && nv_deliver_canvas(widget, emb, event, cx, cy)) {
          v->child_grab = emb;
          return MY_RET_OK;
        }
      }
      /* node: single-select (plain) or toggle (Ctrl); title bar drags
       * (the whole set when the dragged node is in it) */
      {
        bool titlebar = false;
        my_widget_t* hit = nv_node_at(v, cx, cy, &titlebar);
        if (hit != NULL) {
          v->selected = -1;
          nv_flow_sync_timer(v);
          if ((event->u.pointer.modifiers & MY_KEYMOD_CTRL) != 0) {
            nv_select_toggle(v, hit);
          } else if (!my_node_view_is_selected(widget, hit)) {
            nv_select_single(v, hit);
          } else {
            v->selected_node = hit; /* already in the set: keep it */
          }
          if (titlebar) {
            v->drag_node = hit;
            v->drag_cx = cx;
            v->drag_cy = cy;
          }
          my_widget_invalidate(widget, NULL);
          return MY_RET_OK;
        }
      }
      v->selected = -1;
      nv_flow_sync_timer(v);
      /* empty canvas: middle button pans, left button rubber-bands */
      if (event->u.pointer.button == 2) {
        v->panning = true;
        v->pan_x = lx;
        v->pan_y = ly;
      } else {
        v->banding = true;
        v->band_moved = false;
        v->band_x0 = cx;
        v->band_y0 = cy;
        v->band_x1 = cx;
        v->band_y1 = cy;
      }
      return MY_RET_OK;
    }
    case MY_EVENT_POINTER_MOVE: {
      int32_t lx = event->u.pointer.x, ly = event->u.pointer.y;
      float cx, cy;
      my_widget_global_to_local(widget, &lx, &ly);
      my_node_view_screen_to_canvas(widget, lx, ly, &cx, &cy);
      if (v->child_grab != NULL) {
        /* M23c: forward to the grabbed embedded widget (canvas space) */
        nv_deliver_canvas(widget, v->child_grab, event, cx, cy);
        return MY_RET_OK;
      }
      if (v->preview.active) {
        v->preview.cur_x = (int32_t)cx;
        v->preview.cur_y = (int32_t)cy;
        nv_magnet_scan(v, cx, cy); /* magnet updates continuously */
        my_widget_invalidate(widget, NULL);
        return MY_RET_OK;
      }
      if (v->drag_node != NULL) {
        float dx = cx - v->drag_cx;
        float dy = cy - v->drag_cy;
        v->drag_cx = cx;
        v->drag_cy = cy;
        /* multi-select: drag the whole set together */
        if (my_node_view_is_selected(widget, v->drag_node) &&
            my_darray_size(v->selection) > 1) {
          size_t si, sn = my_darray_size(v->selection);
          for (si = 0; si < sn; si++) {
            my_widget_t* m =
                (my_widget_t*)my_darray_get(v->selection, si);
            my_rect_t rect = m->rect;
            rect.x += (int32_t)(dx >= 0.0f ? dx + 0.5f : dx - 0.5f);
            rect.y += (int32_t)(dy >= 0.0f ? dy + 0.5f : dy - 0.5f);
            (void)my_widget_set_layout_rect(m, &rect);
          }
        } else {
          my_rect_t rect = v->drag_node->rect;
          rect.x += (int32_t)(dx >= 0.0f ? dx + 0.5f : dx - 0.5f);
          rect.y += (int32_t)(dy >= 0.0f ? dy + 0.5f : dy - 0.5f);
          (void)my_widget_set_layout_rect(v->drag_node, &rect);
        }
        my_widget_invalidate(widget, NULL);
        return MY_RET_OK;
      }
      if (v->banding) {
        v->band_x1 = cx;
        v->band_y1 = cy;
        if (!v->band_moved &&
            (fabsf(cx - v->band_x0) > 3.0f ||
             fabsf(cy - v->band_y0) > 3.0f)) {
          v->band_moved = true;
        }
        my_widget_invalidate(widget, NULL);
        return MY_RET_OK;
      }
      if (v->panning) {
        my_node_view_pan_by(widget, lx - v->pan_x, ly - v->pan_y);
        v->pan_x = lx;
        v->pan_y = ly;
        return MY_RET_OK;
      }
      return MY_RET_FAIL;
    }
    case MY_EVENT_POINTER_UP:
      if (v->child_grab != NULL) {
        /* M23c: release the embedded-widget grab */
        int32_t lx = event->u.pointer.x, ly = event->u.pointer.y;
        float cx, cy;
        my_widget_global_to_local(widget, &lx, &ly);
        my_node_view_screen_to_canvas(widget, lx, ly, &cx, &cy);
        nv_deliver_canvas(widget, v->child_grab, event, cx, cy);
        v->child_grab = NULL;
        return MY_RET_OK;
      }
      if (v->preview.active) {
        if (v->preview.magnet_node != NULL) {
          /* snapped: connect to the magnet target */
          my_node_view_connect(widget, v->preview.out_node,
                               v->preview.out_slot, v->preview.magnet_node,
                               v->preview.magnet_slot);
        } else {
          int32_t lx = event->u.pointer.x, ly = event->u.pointer.y;
          float cx, cy;
          my_widget_t* node = NULL;
          size_t slot = 0;
          my_widget_global_to_local(widget, &lx, &ly);
          my_node_view_screen_to_canvas(widget, lx, ly, &cx, &cy);
          if (nv_socket_at(v, (int32_t)cx, (int32_t)cy, MY_SOCKET_IN,
                           &node, &slot)) {
            my_node_view_connect(widget, v->preview.out_node,
                                 v->preview.out_slot, node, slot);
          }
        }
        v->preview.active = false;
        v->preview.out_node = NULL;
        v->preview.magnet_node = NULL;
        my_widget_invalidate(widget, NULL);
        return MY_RET_OK;
      }
      if (v->drag_node != NULL) {
        v->drag_node = NULL;
        return MY_RET_OK;
      }
      if (v->banding) {
        if (v->band_moved) {
          /* select every node intersecting the band */
          float bx0 = v->band_x0 < v->band_x1 ? v->band_x0 : v->band_x1;
          float by0 = v->band_y0 < v->band_y1 ? v->band_y0 : v->band_y1;
          float bx1 = v->band_x0 > v->band_x1 ? v->band_x0 : v->band_x1;
          float by1 = v->band_y0 > v->band_y1 ? v->band_y0 : v->band_y1;
          size_t ci, cn = my_widget_child_count(widget);
          nv_select_clear(v);
          for (ci = 0; ci < cn; ci++) {
            my_widget_t* node = my_widget_get_child(widget, ci);
            if (node->floating) {
              continue;
            }
            if (node->rect.x < bx1 && node->rect.x + node->rect.w > bx0 &&
                node->rect.y < by1 && node->rect.y + node->rect.h > by0) {
              my_darray_push(v->selection, node);
            }
          }
          if (my_darray_size(v->selection) > 0) {
            v->selected_node = (my_widget_t*)my_darray_get(
                v->selection, my_darray_size(v->selection) - 1);
          }
        } else {
          nv_select_clear(v); /* click on empty space clears */
        }
        v->banding = false;
        v->band_moved = false;
        my_widget_invalidate(widget, NULL);
        return MY_RET_OK;
      }
      if (v->panning) {
        v->panning = false;
        return MY_RET_OK;
      }
      return MY_RET_FAIL;
    case MY_EVENT_POINTER_WHEEL: {
      /* Blender convention: wheel = zoom anchored at the cursor */
      int32_t lx = event->u.pointer.x, ly = event->u.pointer.y;
      float factor = event->u.pointer.delta > 0 ? 1.1f : 1.0f / 1.1f;
      my_widget_global_to_local(widget, &lx, &ly);
      my_node_view_zoom_at(widget, lx, ly, factor);
      return MY_RET_OK;
    }
    case MY_EVENT_KEY_DOWN:
      if (event->u.key.key == MY_KEY_DELETE ||
          event->u.key.key == MY_KEY_BACKSPACE) {
        /* batch: whole selection set (cascade per node); else the
         * single selected node; else the selected link */
        if (my_darray_size(v->selection) > 0) {
          while (my_darray_size(v->selection) > 0) {
            my_widget_t* m = (my_widget_t*)my_darray_get(v->selection, 0);
            const char* id = my_node_get_id(m);
            my_darray_remove_at(v->selection, 0);
            if (id != NULL) {
              my_node_view_remove_node(widget, id);
            }
          }
          v->selected_node = NULL;
          return MY_RET_OK;
        }
        if (v->selected_node != NULL) {
          const char* id = my_node_get_id(v->selected_node);
          if (id != NULL) {
            my_node_view_remove_node(widget, id);
          }
          return MY_RET_OK;
        }
        if (v->selected >= 0 &&
            (size_t)v->selected < my_darray_size(v->links)) {
          node_link_t* l =
              (node_link_t*)my_darray_get(v->links, (size_t)v->selected);
          my_widget_t* in_node = l->in_node;
          size_t in_slot = l->in_slot;
          v->selected = -1;
          nv_flow_sync_timer(v);
          my_node_view_disconnect_in(widget, in_node, in_slot);
          return MY_RET_OK;
        }
      }
      return MY_RET_FAIL;
    default:
      return MY_RET_FAIL;
  }
}

/* ---------------- lifecycle ---------------- */

static void nv_destroy_chain(my_object_t* obj) {
  my_node_view_t* v = (my_node_view_t*)obj;
  size_t i, n;
  if (v->flow_timer != 0) {
    my_pal_main_loop_t* loop = my_window_loop_of_widget((my_widget_t*)v);
    if (loop != NULL) {
      my_pal_main_loop_remove_timer(loop, v->flow_timer);
    }
    v->flow_timer = 0;
  }
  if (v->links != NULL) {
    n = my_darray_size(v->links);
    for (i = 0; i < n; i++) {
      my_mem_free(obj->allocator, my_darray_get(v->links, i));
    }
    my_darray_destroy(v->links);
  }
  if (v->selection != NULL) {
    my_darray_destroy(v->selection);
  }
  my_widget_destroy((my_widget_t*)v);
  my_object_destroy(obj);
}

static void nv_on_layout(my_widget_t* widget) {
  my_node_view_t* v = (my_node_view_t*)widget;
  if (v->minimap != NULL) {
    (void)my_widget_set_layout_rect(
        v->minimap, &(my_rect_t){0, 0, widget->rect.w, widget->rect.h});
  }
}

static const my_widget_vtable_t s_nv_vtable = {nv_paint, nv_event, nv_on_layout,
                                               NULL};

my_widget_t* my_node_view_create(const my_allocator_t* allocator) {
  my_node_view_t* v =
      (my_node_view_t*)my_mem_calloc(allocator, 1, sizeof(my_node_view_t));
  my_widget_t* overlay;
  if (v == NULL) {
    return NULL;
  }
  if (my_widget_init((my_widget_t*)v, allocator, &s_nv_vtable,
                     "node_view") != MY_RET_OK) {
    my_mem_free(allocator, v);
    return NULL;
  }
  ((my_object_t*)v)->destroy = nv_destroy_chain;
  ((my_widget_t*)v)->widget_type = "node_view"; /* theme selector name */
  v->zoom = 1.0f; /* M20a: identity by default (canvas == screen) */
  v->links = my_darray_create(allocator, 0);
  v->selection = my_darray_create(allocator, 0);
  if (v->links == NULL || v->selection == NULL) {
    my_widget_unref((my_widget_t*)v);
    return NULL;
  }
  v->selected = -1;
  ((my_widget_t*)v)->focusable = true;
  /* overlay child (floating, painted LAST: minimap + rubber band) */
  overlay = my_widget_create(allocator, "nv_overlay");
  if (overlay != NULL) {
    my_widget_subclass_init(overlay, &s_overlay_vtable);
    overlay->floating = true;
    my_widget_set_user_data(overlay, v);
    v->minimap = overlay;
    my_widget_add_child((my_widget_t*)v, overlay);
    my_widget_unref(overlay);
  }
  return (my_widget_t*)v;
}

/** @brief Re-seat the overlay as the LAST child so it really paints
 * after every node (M21b: the magnet ring must sit above selection
 * borders; the overlay is created first, before any node). */
static void nv_overlay_to_front(my_node_view_t* v) {
  my_widget_t* ov = v->minimap;
  if (ov == NULL || ov->parent != (my_widget_t*)v) {
    return;
  }
  my_widget_ref(ov);
  my_widget_remove_child((my_widget_t*)v, ov);
  my_widget_add_child((my_widget_t*)v, ov);
  my_widget_unref(ov); /* the tree owns it again */
}

my_widget_t* my_node_view_add_node(my_widget_t* view, const char* id,
                                   const char* title, const char* category,
                                   int32_t x, int32_t y, int32_t w,
                                   int32_t h) {
  my_widget_t* node;
  if (view == NULL) {
    return NULL;
  }
  node = my_node_create(((my_object_t*)view)->allocator, view, id, title,
                        category);
  if (node == NULL) {
    return NULL;
  }
  /* M21b: w/h == 0 = auto-size to the content (recomputed on add_socket
   * and at paint time); explicit dimensions always win */
  my_node_set_auto_size(node, w == 0, h == 0);
  my_widget_set_rect(node, &(my_rect_t){x, y, w, h});
  if (my_widget_add_child(view, node) != MY_RET_OK) {
    my_widget_unref(node);
    return NULL;
  }
  my_node_auto_size(node); /* initial (title-only) fit, font reachable */
  nv_overlay_to_front((my_node_view_t*)view);
  my_widget_unref(node); /* the tree owns it */
  return node;
}
