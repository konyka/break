/**
 * @file my_node.c
 * @brief Node widget implementation (M19b).
 */
#include "myui/widgets/my_node.h"
#include "myui/widgets/my_node_view.h"

#include <string.h>

#include "myc/my_darray.h"
#include "myc/my_str.h"
#include "myui/my_theme.h"
#include "myui/my_window.h"

typedef struct node_socket_t {
  my_socket_dir_t dir;
  char* name;        /**< owned */
  uint32_t color;    /**< rgba32 model fallback */
} node_socket_t;

typedef struct my_node_t {
  my_widget_t base;
  my_widget_t* view; /**< weak */
  char* id;          /**< owned */
  char* title;       /**< owned */
  my_darray_t* sockets; /**< node_socket_t* (inputs then outputs) */
  bool auto_w;          /**< width tracks the content (M21b) */
  bool auto_h;          /**< height tracks the content (M21b) */
} my_node_t;

/* auto-size layout constants (M21b) */
#define MY_NODE_MARGIN 8    /**< side/bottom padding */
#define MY_NODE_MIN_W 80    /**< auto width floor */
#define MY_NODE_TITLE_PT 13 /**< title font size (matches node_paint) */
#define MY_NODE_SOCKET_PT 12

/* circle/rounded-rect via 4 cubic arcs (kappa = 0.5523; vgcanvas has no
 * arc primitive — M19a curve_to makes this exact enough) */
#define MY_KAPPA 0.5523f

/** @brief Append a circle path (does NOT begin_path). */
void my_node_path_circle(my_vgcanvas_t* vg, float cx, float cy, float r) {
  float k = MY_KAPPA * r;
  my_vgcanvas_move_to(vg, cx + r, cy);
  my_vgcanvas_curve_to(vg, cx + r, cy + k, cx + k, cy + r, cx, cy + r);
  my_vgcanvas_curve_to(vg, cx - k, cy + r, cx - r, cy + k, cx - r, cy);
  my_vgcanvas_curve_to(vg, cx - r, cy - k, cx - k, cy - k, cx, cy - r);
  my_vgcanvas_curve_to(vg, cx + k, cy - r, cx + r, cy - k, cx + r, cy);
  my_vgcanvas_close_path(vg);
}

/** @brief Begin a rounded-rect path (corners are cubic arcs). */
static void node_path_rounded_rect(my_vgcanvas_t* vg, float x, float y,
                                   float w, float h, float r) {
  float k = MY_KAPPA * r;
  my_vgcanvas_begin_path(vg);
  my_vgcanvas_move_to(vg, x + r, y);
  my_vgcanvas_line_to(vg, x + w - r, y);
  my_vgcanvas_curve_to(vg, x + w - r + k, y, x + w, y + r - k, x + w, y + r);
  my_vgcanvas_line_to(vg, x + w, y + h - r);
  my_vgcanvas_curve_to(vg, x + w, y + h - r + k, x + w - r + k, y + h,
                       x + w - r, y + h);
  my_vgcanvas_line_to(vg, x + r, y + h);
  my_vgcanvas_curve_to(vg, x + r - k, y + h, x, y + h - r + k, x, y + h - r);
  my_vgcanvas_line_to(vg, x, y + r);
  my_vgcanvas_curve_to(vg, x, y + r - k, x + r - k, y, x + r, y);
  my_vgcanvas_close_path(vg);
}

/* ---------------- auto size (M21b) ---------------- */

/** @brief Text width with the window font at the node paint sizes; the
 * 7px/cell estimate (same fallback as node_paint) when no window/font
 * is reachable (detached unit-test trees). */
static int32_t node_text_w(my_widget_t* node, const char* text,
                           int32_t pt) {
  my_font_t* font = NULL;
  int32_t fsize = 0, w = 0, h = 0;
  if (text == NULL) {
    return 0;
  }
  my_window_font_of_widget(node, &font, &fsize);
  (void)fsize; /* node_paint pins its own point sizes */
  if (font != NULL && my_font_measure(font, text, pt, &w, &h) == MY_RET_OK) {
    return w;
  }
  return (int32_t)strlen(text) * 7;
}

void my_node_set_auto_size(my_widget_t* node, bool auto_w, bool auto_h) {
  my_node_t* n;
  if (node == NULL) {
    return;
  }
  n = (my_node_t*)node;
  n->auto_w = auto_w;
  n->auto_h = auto_h;
}

void my_node_auto_size(my_widget_t* node) {
  my_node_t* n;
  size_t i, cnt;
  size_t in_cnt, out_cnt, rows;
  int32_t w = MY_NODE_MIN_W;
  int32_t h;
  bool changed = false;
  if (node == NULL) {
    return;
  }
  n = (my_node_t*)node;
  if (!n->auto_w && !n->auto_h) {
    return; /* explicit size always wins */
  }
  if (n->title != NULL) {
    int32_t tw = node_text_w(node, n->title, MY_NODE_TITLE_PT) +
                 2 * MY_NODE_MARGIN;
    if (tw > w) {
      w = tw;
    }
  }
  cnt = my_darray_size(n->sockets);
  in_cnt = my_node_socket_count(node, MY_SOCKET_IN);
  out_cnt = my_node_socket_count(node, MY_SOCKET_OUT);
  rows = in_cnt > out_cnt ? in_cnt : out_cnt;
  /* widest socket row: dot diameter + gap + name per side, an inner gap
   * when the row carries both directions, plus side margins */
  {
    size_t ri;
    for (ri = 0; ri < rows; ri++) {
      size_t seen_in = 0, seen_out = 0;
      int32_t rw = 0;
      bool has_in = false, has_out = false;
      for (i = 0; i < cnt; i++) {
        node_socket_t* s = (node_socket_t*)my_darray_get(n->sockets, i);
        if (s->dir == MY_SOCKET_IN && seen_in++ == ri) {
          rw += 2 * MY_NODE_SOCKET_R + MY_NODE_MARGIN +
                node_text_w(node, s->name, MY_NODE_SOCKET_PT);
          has_in = true;
        }
        if (s->dir == MY_SOCKET_OUT && seen_out++ == ri) {
          rw += 2 * MY_NODE_SOCKET_R + MY_NODE_MARGIN +
                node_text_w(node, s->name, MY_NODE_SOCKET_PT);
          has_out = true;
        }
      }
      if (has_in && has_out) {
        rw += MY_NODE_MARGIN; /* inner gap between the two labels */
      }
      rw += 2 * MY_NODE_MARGIN;
      if (rw > w) {
        w = rw;
      }
    }
  }
  h = MY_NODE_HEADER_H + (int32_t)rows * MY_NODE_ROW_H;
  /* embedded children (declared rects): widen/lower to contain them */
  cnt = my_widget_child_count(node);
  for (i = 0; i < cnt; i++) {
    my_widget_t* ch = my_widget_get_child(node, i);
    int32_t cw = ch->rect.x + ch->rect.w + MY_NODE_MARGIN;
    int32_t cb = ch->rect.y + ch->rect.h;
    if (cw > w) {
      w = cw;
    }
    if (cb > h) {
      h = cb;
    }
  }
  h += MY_NODE_MARGIN;
  {
    my_rect_t rect = node->rect;
    if (n->auto_w) {
      rect.w = w;
    }
    if (n->auto_h) {
      rect.h = h;
    }
    changed = rect.w != node->rect.w || rect.h != node->rect.h;
    if (changed) {
      (void)my_widget_set_layout_rect(node, &rect);
      my_widget_request_layout(node->parent != NULL ? node->parent : node);
    }
  }
  if (changed) {
    my_widget_invalidate(node, NULL);
  }
}

static void node_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  my_node_t* n = (my_node_t*)widget;
  size_t i, cnt;
  /* M21b: recompute lazily so embedded children added after the last
   * socket still size the node (one frame of lag at most) */
  if (n->auto_w || n->auto_h) {
    my_node_auto_size(widget);
  }
  /* body */
  uint32_t body = my_widget_style_get_color(widget, MY_STATE_NORMAL,
                                            MY_STYLE_BG_COLOR, 0x3A3A3AFFu);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(body));
  my_vgcanvas_fill_rounded_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                                  (float)widget->rect.h},
                                4);
  node_path_rounded_rect(vg, 1, 1, (float)widget->rect.w - 2,
                         (float)widget->rect.h - 2, 4);
  {
    /* plain node edge (the SELECTION border is drawn separately at the
     * very end of node_paint so it sits above the header fill and the
     * sockets instead of being covered by them) */
    uint32_t border = my_widget_part_color(
        widget, "node", NULL, MY_STATE_NORMAL, MY_STYLE_BORDER_COLOR, 0x1E1E1EFFu);
    my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(border));
    my_vgcanvas_set_line_width(vg, 1);
    my_vgcanvas_stroke(vg);
  }
  /* header (category色: CSS `node.<category> .header` hits via the
   * node's style_class; .header is a CLASS selector) */
  {
    uint32_t hc = my_widget_part_color(widget, NULL, "header",
                                       MY_STATE_NORMAL, MY_STYLE_BG_COLOR,
                                       0x525252FFu);
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(hc));
    my_vgcanvas_fill_rounded_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                                    MY_NODE_HEADER_H},
                                  4);
    my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, MY_NODE_HEADER_H / 2,
                                            (float)widget->rect.w,
                                            MY_NODE_HEADER_H / 2});
    if (n->title != NULL) {
      /* M24b: was a hardcoded white; now theme-overridable via the
       * header part (e.g. `node.<category> .header { color: ... }`),
       * same fallback value -> identical pixels by default */
      uint32_t tc = my_widget_part_color(widget, NULL, "header",
                                         MY_STATE_NORMAL, MY_STYLE_FG_COLOR,
                                         0xFFFFFFFFu);
      my_vgcanvas_set_font(vg, NULL, 13);
      my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(tc));
      my_vgcanvas_draw_text(vg, n->title, 8, 5);
    }
  }
  /* sockets: inputs at the left edge, outputs at the right edge */
  cnt = my_darray_size(n->sockets);
  for (i = 0; i < cnt; i++) {
    node_socket_t* s = (node_socket_t*)my_darray_get(n->sockets, i);
    size_t slot = 0;
    size_t j;
    int32_t cx, cy;
    /* slot index within its direction */
    for (j = 0; j < i; j++) {
      node_socket_t* o = (node_socket_t*)my_darray_get(n->sockets, j);
      if (o->dir == s->dir) {
        slot++;
      }
    }
    cy = MY_NODE_HEADER_H + (int32_t)slot * MY_NODE_ROW_H + MY_NODE_ROW_H / 2;
    cx = s->dir == MY_SOCKET_IN ? 0 : widget->rect.w;
    {
      const char* scls = s->dir == MY_SOCKET_IN ? "input" : "output";
      uint32_t sc = my_widget_part_color(
          widget, "node_socket", scls,
          MY_STATE_NORMAL, MY_STYLE_BG_COLOR, s->color);
      /* M24b: socket ring was a hardcoded 0x1E1E1EFF; now theme-overridable
       * (`node_socket.input/.output { border-color: ... }`), same fallback */
      uint32_t ring = my_widget_part_color(widget, "node_socket", scls,
                                           MY_STATE_NORMAL,
                                           MY_STYLE_BORDER_COLOR, 0x1E1E1EFFu);
      my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(sc));
      my_vgcanvas_begin_path(vg);
      my_node_path_circle(vg, (float)cx, (float)cy, MY_NODE_SOCKET_R);
      my_vgcanvas_fill(vg);
      my_vgcanvas_begin_path(vg);
      my_node_path_circle(vg, (float)cx, (float)cy, MY_NODE_SOCKET_R);
      my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(ring));
      my_vgcanvas_set_line_width(vg, 1);
      my_vgcanvas_stroke(vg);
    }
    /* socket name */
    if (s->name != NULL) {
      /* M24b: was a hardcoded 0xCCCCCCFF; now theme-overridable
       * (`node_socket.input/.output { color: ... }`), same fallback */
      uint32_t nc = my_widget_part_color(
          widget, "node_socket", s->dir == MY_SOCKET_IN ? "input" : "output",
          MY_STATE_NORMAL, MY_STYLE_FG_COLOR, 0xCCCCCCFFu);
      my_vgcanvas_set_font(vg, NULL, 12);
      my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(nc));
      if (s->dir == MY_SOCKET_IN) {
        my_vgcanvas_draw_text(vg, s->name, 10, (float)(cy - 6));
      } else {
        int32_t tw = 0, th = 0;
        if (my_vgcanvas_measure_text(vg, s->name, &tw, &th) != MY_RET_OK) {
          tw = (int32_t)strlen(s->name) * 7;
        }
        my_vgcanvas_draw_text(vg, s->name, (float)(widget->rect.w - 10 - tw),
                              (float)(cy - 6));
      }
    }
  }
  /* selection border, drawn LAST so it sits above everything the node
   * paints (M22 follow-up: it is part of the node, so it always tracks
   * the node's own transform — no cross-layer coordinate matching) */
  if (n->view != NULL && my_node_view_is_selected(n->view, widget)) {
    uint32_t sc = my_widget_part_color(widget, "node", "selected",
                                       MY_STATE_NORMAL, MY_STYLE_BORDER_COLOR,
                                       0xE0A030FFu);
    my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(sc));
    my_vgcanvas_set_line_width(vg, 2);
    my_vgcanvas_stroke_rect(vg, &(my_rectf_t){1, 1, (float)widget->rect.w - 2,
                                              (float)widget->rect.h - 2});
  }
}

static my_ret_t node_event(my_widget_t* widget, const my_event_t* event) {
  /* M20a: the node is pure paint — ALL pointer logic lives in the view
   * (single canvas/screen transform point); bubble everything. */
  (void)widget;
  (void)event;
  return MY_RET_FAIL;
}

static void node_destroy_chain(my_object_t* obj) {
  my_node_t* n = (my_node_t*)obj;
  size_t i, cnt = 0;
  if (n->sockets != NULL) {
    cnt = my_darray_size(n->sockets);
    for (i = 0; i < cnt; i++) {
      node_socket_t* s = (node_socket_t*)my_darray_get(n->sockets, i);
      my_mem_free(obj->allocator, s->name);
      my_mem_free(obj->allocator, s);
    }
    my_darray_destroy(n->sockets);
  }
  my_mem_free(obj->allocator, n->id);
  my_mem_free(obj->allocator, n->title);
  my_widget_destroy((my_widget_t*)n);
  my_object_destroy(obj);
}

/** @brief M24c: content-driven measurement hook — same logic as the
 * paint-time lazy fallback (kept in node_paint), triggered earlier via
 * my_widget_relayout so auto-sized nodes settle before layout. */
static void node_on_measure(my_widget_t* widget) {
  my_node_auto_size(widget); /* no-op unless auto_w/auto_h (M21b) */
}

static const my_widget_vtable_t s_node_vtable = {node_paint, node_event, NULL,
                                                 node_on_measure};

my_widget_t* my_node_create(const my_allocator_t* allocator,
                            my_widget_t* view, const char* id,
                            const char* title, const char* category) {
  my_node_t* n = (my_node_t*)my_mem_calloc(allocator, 1, sizeof(my_node_t));
  if (n == NULL) {
    return NULL;
  }
  if (my_widget_init((my_widget_t*)n, allocator, &s_node_vtable, "node") !=
      MY_RET_OK) {
    my_mem_free(allocator, n);
    return NULL;
  }
  ((my_object_t*)n)->destroy = node_destroy_chain;
  ((my_widget_t*)n)->widget_type = "node"; /* theme selector name */
  n->view = view;
  n->id = my_strdup(allocator, id);
  n->title = my_strdup(allocator, title);
  n->sockets = my_darray_create(allocator, 0);
  if (n->sockets == NULL) {
    my_widget_unref((my_widget_t*)n);
    return NULL;
  }
  if (category != NULL) {
    my_widget_set_style_class((my_widget_t*)n, category);
  }
  return (my_widget_t*)n;
}

my_ret_t my_node_add_socket(my_widget_t* node, my_socket_dir_t dir,
                            const char* name, uint32_t type_color) {
  my_node_t* n = (my_node_t*)node;
  node_socket_t* s;
  if (node == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  s = (node_socket_t*)my_mem_calloc(((my_object_t*)node)->allocator, 1,
                                    sizeof(node_socket_t));
  if (s == NULL) {
    return MY_RET_OOM;
  }
  s->dir = dir;
  s->name = my_strdup(((my_object_t*)node)->allocator, name);
  s->color = type_color;
  if (name != NULL && s->name == NULL) {
    my_mem_free(((my_object_t*)node)->allocator, s);
    return MY_RET_OOM;
  }
  if (my_darray_push(n->sockets, s) != MY_RET_OK) {
    my_mem_free(((my_object_t*)node)->allocator, s->name);
    my_mem_free(((my_object_t*)node)->allocator, s);
    return MY_RET_OOM;
  }
  my_node_auto_size(node); /* M21b: content changed -> maybe grow */
  my_widget_invalidate(node, NULL);
  return MY_RET_OK;
}

size_t my_node_socket_count(const my_widget_t* node, my_socket_dir_t dir) {
  const my_node_t* n = (const my_node_t*)node;
  size_t i, cnt, hit = 0;
  if (node == NULL) {
    return 0;
  }
  cnt = my_darray_size(n->sockets);
  for (i = 0; i < cnt; i++) {
    const node_socket_t* s = (const node_socket_t*)my_darray_get(n->sockets, i);
    if (s->dir == dir) {
      hit++;
    }
  }
  return hit;
}

bool my_node_socket_center(const my_widget_t* node, my_socket_dir_t dir,
                           size_t slot, int32_t* out_x, int32_t* out_y) {
  const my_node_t* n = (const my_node_t*)node;
  size_t i, cnt, seen = 0;
  if (node == NULL) {
    return false;
  }
  cnt = my_darray_size(n->sockets);
  for (i = 0; i < cnt; i++) {
    const node_socket_t* s = (const node_socket_t*)my_darray_get(n->sockets, i);
    if (s->dir == dir) {
      if (seen == slot) {
        *out_x = node->rect.x +
                 (dir == MY_SOCKET_IN ? 0 : node->rect.w);
        *out_y = node->rect.y + MY_NODE_HEADER_H + (int32_t)slot * MY_NODE_ROW_H +
                 MY_NODE_ROW_H / 2;
        return true;
      }
      seen++;
    }
  }
  return false;
}

const char* my_node_get_id(const my_widget_t* node) {
  return node != NULL ? ((const my_node_t*)node)->id : NULL;
}

uint32_t my_node_socket_type_color(const my_widget_t* node,
                                   my_socket_dir_t dir, size_t slot) {
  const my_node_t* n;
  size_t i, cnt, seen = 0;
  if (node == NULL) {
    return 0;
  }
  n = (const my_node_t*)node;
  cnt = my_darray_size(n->sockets);
  for (i = 0; i < cnt; i++) {
    const node_socket_t* s = (const node_socket_t*)my_darray_get(n->sockets, i);
    if (s->dir == dir) {
      if (seen == slot) {
        return s->color;
      }
      seen++;
    }
  }
  return 0;
}
