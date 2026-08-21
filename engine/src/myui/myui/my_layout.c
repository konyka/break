/**
 * @file my_layout.c
 * @brief Layout params parser + default and linear layouters.
 */
#include "myui/my_layout.h"

#include <stdlib.h>
#include <string.h>

#include "myc/my_str.h"

/* ---------------- params parser ---------------- */

static my_ret_t parse_axis_value(const char* spec, my_layout_mode_t* mode,
                                 float* value) {
  char* end = NULL;
  float v = strtof(spec, &end);
  if (end == spec) {
    return MY_RET_INVALID_PARAMS;
  }
  if (*end == '\0') {
    *mode = MY_LAYOUT_PX;
  } else if (strcmp(end, "%") == 0) {
    *mode = MY_LAYOUT_PERCENT;
  } else if (strcmp(end, "f") == 0) {
    *mode = MY_LAYOUT_FLEX;
  } else {
    return MY_RET_INVALID_PARAMS;
  }
  *value = v;
  return MY_RET_OK;
}

my_ret_t my_layout_params_parse(const char* str, my_layout_params_t* out) {
  my_layout_params_t p;
  const char* cur;
  if (out == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  memset(&p, 0, sizeof(p));
  if (str == NULL || *str == '\0') {
    *out = p;
    return MY_RET_OK;
  }
  cur = str;
  while (*cur != '\0') {
    my_layout_mode_t* mode;
    float* value;
    char token[32];
    size_t len;
    const char* colon;
    while (*cur == ' ') {
      cur++;
    }
    if (*cur == '\0') {
      break;
    }
    len = 0;
    while (cur[len] != '\0' && cur[len] != ' ') {
      len++;
    }
    if (len == 0 || len >= sizeof(token)) {
      return MY_RET_INVALID_PARAMS;
    }
    memcpy(token, cur, len);
    token[len] = '\0';
    cur += len;
    colon = strchr(token, ':');
    if (colon == NULL || colon == token || colon[1] == '\0') {
      return MY_RET_INVALID_PARAMS;
    }
    if (colon - token == 1 && token[0] == 'w') {
      mode = &p.w_mode;
      value = &p.w_value;
    } else if (colon - token == 1 && token[0] == 'h') {
      mode = &p.h_mode;
      value = &p.h_value;
    } else {
      return MY_RET_INVALID_PARAMS;
    }
    if (parse_axis_value(colon + 1, mode, value) != MY_RET_OK) {
      return MY_RET_INVALID_PARAMS;
    }
  }
  *out = p;
  return MY_RET_OK;
}

my_ret_t my_widget_set_layout_params(my_widget_t* widget, const char* params) {
  my_layout_params_t p;
  my_ret_t ret;
  if (widget == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  ret = my_layout_params_parse(params, &p);
  if (ret != MY_RET_OK) {
    return ret;
  }
  if (widget->layout_params.w_mode == p.w_mode &&
      widget->layout_params.w_value == p.w_value &&
      widget->layout_params.h_mode == p.h_mode &&
      widget->layout_params.h_value == p.h_value) {
    return MY_RET_OK;
  }
  widget->layout_params = p;
  my_widget_request_layout(widget->parent != NULL ? widget->parent : widget);
  my_widget_invalidate(widget->parent != NULL ? widget->parent : widget, NULL);
  return MY_RET_OK;
}

/* ---------------- default layouter ---------------- */

static void default_layout(my_layouter_t* self, my_widget_t* parent) {
  (void)self;
  (void)parent; /* absolute positioning: rects are the truth */
}

my_layouter_t* my_layouter_default(void) {
  static my_layouter_t s_default = {default_layout, NULL};
  return &s_default;
}

/* ---------------- linear layouter ---------------- */

typedef struct my_layouter_linear_t {
  my_layouter_t base;
  const my_allocator_t* allocator;
  bool horizontal;
  int32_t spacing;
} my_layouter_linear_t;

/** @brief Resolve one axis size from a mode/value pair. */
static int32_t axis_size(my_layout_mode_t mode, float value, bool is_main,
                         int32_t content_main, int32_t content_cross,
                         int32_t remaining, float flex_total,
                         int32_t fallback) {
  switch (mode) {
    case MY_LAYOUT_PX:
      return (int32_t)value;
    case MY_LAYOUT_PERCENT: {
      int32_t base = is_main ? content_main : content_cross;
      return (int32_t)(base * value / 100.0f);
    }
    case MY_LAYOUT_FLEX:
      if (is_main) {
        return flex_total > 0.0f ? (int32_t)(remaining * value / flex_total) : 0;
      }
      return content_cross; /* cross-axis flex = fill */
    case MY_LAYOUT_AUTO:
    default:
      /* main AUTO: keep current size; cross AUTO: fill the parent */
      return is_main ? fallback : content_cross;
  }
}

static void linear_layout(my_layouter_t* self, my_widget_t* parent) {
  my_layouter_linear_t* lin = (my_layouter_linear_t*)self;
  bool horz = lin->horizontal;
  int32_t content_main = horz ? parent->rect.w : parent->rect.h;
  int32_t content_cross = horz ? parent->rect.h : parent->rect.w;
  int32_t fixed_total = 0;
  int32_t visible_count = 0;
  float flex_total = 0.0f;
  int32_t remaining;
  int32_t cursor = 0;
  size_t i, n = my_widget_child_count(parent);

  /* pass 1: fixed sizes + flex weights */
  for (i = 0; i < n; i++) {
    my_widget_t* c = my_widget_get_child(parent, i);
    const my_layout_params_t* p;
    my_layout_mode_t mode;
    float value;
    if (!c->visible || c->floating) {
      continue; /* floating children keep their absolute rect (M13c) */
    }
    p = &c->layout_params;
    mode = horz ? p->w_mode : p->h_mode;
    value = horz ? p->w_value : p->h_value;
    visible_count++;
    if (mode == MY_LAYOUT_PX) {
      fixed_total += (int32_t)value;
    } else if (mode == MY_LAYOUT_PERCENT) {
      fixed_total += (int32_t)(content_main * value / 100.0f);
    } else if (mode == MY_LAYOUT_FLEX) {
      flex_total += value;
    } else {
      fixed_total += horz ? c->rect.w : c->rect.h; /* AUTO: current size */
    }
  }
  if (visible_count > 1) {
    fixed_total += lin->spacing * (visible_count - 1);
  }
  remaining = content_main - fixed_total;
  if (remaining < 0) {
    remaining = 0;
  }

  /* pass 2: assign rects (direct field write to avoid re-marking) */
  for (i = 0; i < n; i++) {
    my_widget_t* c = my_widget_get_child(parent, i);
    const my_layout_params_t* p;
    int32_t main_size, cross_size;
    if (!c->visible || c->floating) {
      continue;
    }
    p = &c->layout_params;
    main_size = axis_size(horz ? p->w_mode : p->h_mode,
                          horz ? p->w_value : p->h_value, true, content_main,
                          content_cross, remaining, flex_total,
                          horz ? c->rect.w : c->rect.h);
    cross_size = axis_size(horz ? p->h_mode : p->w_mode,
                           horz ? p->h_value : p->w_value, false, content_main,
                           content_cross, remaining, flex_total,
                           horz ? c->rect.h : c->rect.w);
    {
      my_rect_t rect = c->rect;
      if (horz) {
        rect.x = cursor;
        rect.w = main_size;
        rect.h = cross_size;
      } else {
        rect.y = cursor;
        rect.h = main_size;
        rect.w = cross_size;
      }
      (void)my_widget_set_layout_rect(c, &rect);
    }
    cursor += main_size + lin->spacing;
  }
}

static void linear_destroy(my_layouter_t* self) {
  my_layouter_linear_t* lin = (my_layouter_linear_t*)self;
  my_mem_free(lin->allocator, lin);
}

my_layouter_t* my_layouter_linear_create(const my_allocator_t* allocator,
                                         bool horizontal, int32_t spacing) {
  my_layouter_linear_t* lin =
      (my_layouter_linear_t*)my_mem_calloc(allocator, 1, sizeof(my_layouter_linear_t));
  if (lin == NULL) {
    return NULL;
  }
  lin->base.layout = linear_layout;
  lin->base.destroy = linear_destroy;
  lin->allocator = allocator;
  lin->horizontal = horizontal;
  lin->spacing = spacing;
  return (my_layouter_t*)lin;
}

/* ---------------- flow layouter (M14a) ---------------- */

typedef struct my_layouter_flow_t {
  my_layouter_t base;
  const my_allocator_t* allocator;
  int32_t h_spacing;
  int32_t v_spacing;
  my_flow_align_t align;
} my_layouter_flow_t;

/** @brief Child size under flow: PX/% from params, AUTO (=current rect)
 * for everything else (FLEX is meaningless in flow). */
static void flow_child_size(my_widget_t* parent, my_widget_t* c, int32_t* out_w,
                            int32_t* out_h) {
  const my_layout_params_t* p = &c->layout_params;
  switch (p->w_mode) {
    case MY_LAYOUT_PX:
      *out_w = (int32_t)p->w_value;
      break;
    case MY_LAYOUT_PERCENT:
      *out_w = (int32_t)(parent->rect.w * p->w_value / 100.0f);
      break;
    default:
      *out_w = c->rect.w;
      break;
  }
  switch (p->h_mode) {
    case MY_LAYOUT_PX:
      *out_h = (int32_t)p->h_value;
      break;
    case MY_LAYOUT_PERCENT:
      *out_h = (int32_t)(parent->rect.h * p->h_value / 100.0f);
      break;
    default:
      *out_h = c->rect.h;
      break;
  }
}

/** @brief Shift row [first, last) horizontally per the align setting. */
static void flow_align_row(my_layouter_flow_t* fl, my_widget_t* parent,
                           size_t first, size_t last, int32_t row_w) {
  int32_t off;
  size_t j;
  if (fl->align != MY_FLOW_ALIGN_CENTER) {
    return;
  }
  off = (parent->rect.w - row_w) / 2;
  if (off <= 0) {
    return;
  }
  for (j = first; j < last; j++) {
    my_widget_t* c = my_widget_get_child(parent, j);
    if (c->visible && !c->floating) {
      my_rect_t rect = c->rect;
      rect.x += off;
      (void)my_widget_set_layout_rect(c, &rect);
    }
  }
}

/** @brief Walk the rows; assign=true also writes child rects (and marks
 * them dirty). Returns the total content height. */
static int32_t flow_run(my_layouter_flow_t* fl, my_widget_t* parent,
                        bool assign) {
  size_t i, n = my_widget_child_count(parent);
  size_t row_first = 0;
  int32_t x = 0, y = 0, row_h = 0, row_w = 0;
  bool row_empty = true;
  for (i = 0; i < n; i++) {
    my_widget_t* c = my_widget_get_child(parent, i);
    int32_t cw, ch;
    if (!c->visible || c->floating) {
      continue;
    }
    flow_child_size(parent, c, &cw, &ch);
    if (!row_empty && x + cw > parent->rect.w) {
      /* close the current row, wrap */
      if (assign) {
        flow_align_row(fl, parent, row_first, i, row_w);
      }
      y += row_h + fl->v_spacing;
      x = 0;
      row_h = 0;
      row_w = 0;
      row_empty = true;
      row_first = i;
    }
    if (assign) {
      my_rect_t rect = my_rect_init(x, y, cw, ch);
      (void)my_widget_set_layout_rect(c, &rect);
    }
    x += cw + fl->h_spacing;
    row_w = x - fl->h_spacing; /* width without the trailing spacing */
    if (ch > row_h) {
      row_h = ch;
    }
    row_empty = false;
  }
  if (!row_empty) {
    if (assign) {
      flow_align_row(fl, parent, row_first, n, row_w);
    }
    y += row_h;
  }
  return y;
}

static void flow_layout(my_layouter_t* self, my_widget_t* parent) {
  flow_run((my_layouter_flow_t*)self, parent, true);
}

static void flow_destroy(my_layouter_t* self) {
  my_layouter_flow_t* fl = (my_layouter_flow_t*)self;
  my_mem_free(fl->allocator, fl);
}

my_layouter_t* my_layouter_flow_create(const my_allocator_t* allocator,
                                       int32_t h_spacing, int32_t v_spacing,
                                       my_flow_align_t align) {
  my_layouter_flow_t* fl =
      (my_layouter_flow_t*)my_mem_calloc(allocator, 1, sizeof(my_layouter_flow_t));
  if (fl == NULL) {
    return NULL;
  }
  fl->base.layout = flow_layout;
  fl->base.destroy = flow_destroy;
  fl->allocator = allocator;
  fl->h_spacing = h_spacing;
  fl->v_spacing = v_spacing;
  fl->align = align;
  return (my_layouter_t*)fl;
}

int32_t my_layouter_flow_measure(my_widget_t* parent) {
  if (parent == NULL || parent->layouter == NULL ||
      parent->layouter->layout != flow_layout) {
    return 0;
  }
  return flow_run((my_layouter_flow_t*)parent->layouter, parent, false);
}

/* ---------------- attach / run ---------------- */

my_ret_t my_widget_set_layouter(my_widget_t* widget, my_layouter_t* layouter) {
  if (widget == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (widget->layouter == layouter) {
    return MY_RET_OK;
  }
  if (widget->layouter != NULL && widget->layouter->destroy != NULL) {
    widget->layouter->destroy(widget->layouter);
  }
  widget->layouter = layouter;
  my_widget_request_layout(widget);
  my_widget_invalidate(widget, NULL);
  return MY_RET_OK;
}

static void my_widget_relayout_impl(my_widget_t* widget, bool force) {
  size_t i, n;
  if (widget == NULL ||
      (!force && !widget->need_layout && !widget->subtree_need_layout)) {
    return;
  }
  if (force || widget->need_layout) {
    widget->need_layout = false;
    /* M24c: content-driven measurement runs first, so an on_measure hook
     * settles the widget's own state before arranging children. */
    if (widget->vtable != NULL && widget->vtable->on_measure != NULL) {
      widget->vtable->on_measure(widget);
    }
    if (widget->layouter != NULL && widget->layouter->layout != NULL) {
      widget->layouter->layout(widget->layouter, widget);
    }
    if (widget->vtable != NULL && widget->vtable->on_layout != NULL) {
      widget->vtable->on_layout(widget);
    }
  }
  widget->subtree_need_layout = false;
  n = my_widget_child_count(widget);
  for (i = 0; i < n; i++) {
    my_widget_t* child = my_widget_get_child(widget, i);
    if (force || child->need_layout || child->subtree_need_layout) {
      my_widget_relayout_impl(child, force);
    }
  }
  for (i = 0; i < n; i++) {
    my_widget_t* child = my_widget_get_child(widget, i);
    if (child->need_layout || child->subtree_need_layout) {
      widget->subtree_need_layout = true;
      break;
    }
  }
}

void my_widget_relayout(my_widget_t* widget) {
  my_widget_relayout_impl(widget, true);
}

void my_widget_relayout_pending(my_widget_t* widget) {
  my_widget_relayout_impl(widget, false);
}
