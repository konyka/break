/**
 * @file my_rich_label.c
 * @brief Rich text label implementation (M14a).
 */
#include "myui/widgets/my_rich_label.h"

#include <string.h>

#include "myc/my_darray.h"
#include "myc/my_str.h"

typedef struct rich_seg_t {
  char* text;     /**< owned */
  uint32_t rgba;  /**< segment color */
  bool bold;      /**< fake bold: double-draw with 1px x-offset */
} rich_seg_t;

typedef struct my_rich_label_t {
  my_widget_t base;
  my_darray_t* segs; /**< rich_seg_t* */
} my_rich_label_t;

/** @brief Segment width: vg font measure, 8px-cell fallback. */
static int32_t seg_width(my_vgcanvas_t* vg, const rich_seg_t* s, int32_t* out_h) {
  int32_t tw = 0, th = 0;
  if (vg != NULL &&
      my_vgcanvas_measure_text(vg, s->text, &tw, &th) == MY_RET_OK) {
    if (out_h != NULL) {
      *out_h = th;
    }
    return tw;
  }
  if (out_h != NULL) {
    *out_h = 8;
  }
  return (int32_t)strlen(s->text) * 8;
}

static void rich_label_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  my_rich_label_t* rl = (my_rich_label_t*)widget;
  uint32_t bg = my_widget_style_get_color(widget, MY_STATE_NORMAL, MY_STYLE_BG_COLOR,
                                          0x00000000u);
  size_t i, n;
  float x = 0.0f;
  if ((bg & 0xFFu) != 0) {
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(bg));
    my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                            (float)widget->rect.h});
  }
  n = my_darray_size(rl->segs);
  for (i = 0; i < n; i++) {
    rich_seg_t* s = (rich_seg_t*)my_darray_get(rl->segs, i);
    int32_t th = 8;
    int32_t tw = seg_width(vg, s, &th);
    float y = ((float)widget->rect.h - (float)th) / 2.0f;
    if (x >= (float)widget->rect.w) {
      break; /* fully clipped already: skip the rest */
    }
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(s->rgba));
    my_vgcanvas_draw_text(vg, s->text, x, y);
    if (s->bold) {
      /* fake bold (no synthetic emboldening in the backends): draw the
       * same glyphs again shifted 1px to the right */
      my_vgcanvas_draw_text(vg, s->text, x + 1.0f, y);
      tw += 1;
    }
    x += (float)tw;
  }
}

static void rich_label_destroy_chain(my_object_t* obj) {
  my_rich_label_t* rl = (my_rich_label_t*)obj;
  my_rich_label_clear((my_widget_t*)rl);
  my_darray_destroy(rl->segs);
  my_widget_destroy((my_widget_t*)rl);
  my_object_destroy(obj);
}

static const my_widget_vtable_t s_rich_label_vtable = {rich_label_on_paint,
                                                       NULL, NULL, NULL};

my_widget_t* my_rich_label_create(const my_allocator_t* allocator) {
  my_rich_label_t* rl =
      (my_rich_label_t*)my_mem_calloc(allocator, 1, sizeof(my_rich_label_t));
  if (rl == NULL) {
    return NULL;
  }
  if (my_widget_init((my_widget_t*)rl, allocator, &s_rich_label_vtable,
                     "rich_label") != MY_RET_OK) {
    my_mem_free(allocator, rl);
    return NULL;
  }
  ((my_object_t*)rl)->destroy = rich_label_destroy_chain;
  rl->segs = my_darray_create(allocator, 0);
  if (rl->segs == NULL) {
    my_widget_unref((my_widget_t*)rl);
    return NULL;
  }
  return (my_widget_t*)rl;
}

my_ret_t my_rich_label_add_segment(my_widget_t* label, const char* text,
                                   uint32_t rgba_color, bool bold) {
  my_rich_label_t* rl = (my_rich_label_t*)label;
  rich_seg_t* s;
  if (label == NULL || text == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  s = (rich_seg_t*)my_mem_calloc(((my_object_t*)label)->allocator, 1,
                                 sizeof(rich_seg_t));
  if (s == NULL) {
    return MY_RET_OOM;
  }
  s->text = my_strdup(((my_object_t*)label)->allocator, text);
  s->rgba = rgba_color;
  s->bold = bold;
  if (s->text == NULL || my_darray_push(rl->segs, s) != MY_RET_OK) {
    my_mem_free(((my_object_t*)label)->allocator, s->text);
    my_mem_free(((my_object_t*)label)->allocator, s);
    return MY_RET_OOM;
  }
  my_widget_invalidate(label, NULL);
  return MY_RET_OK;
}

void my_rich_label_clear(my_widget_t* label) {
  my_rich_label_t* rl = (my_rich_label_t*)label;
  size_t i, n;
  if (label == NULL) {
    return;
  }
  n = my_darray_size(rl->segs);
  for (i = 0; i < n; i++) {
    rich_seg_t* s = (rich_seg_t*)my_darray_get(rl->segs, i);
    my_mem_free(((my_object_t*)label)->allocator, s->text);
    my_mem_free(((my_object_t*)label)->allocator, s);
  }
  my_darray_clear(rl->segs);
  my_widget_invalidate(label, NULL);
}

int32_t my_rich_label_content_width(my_widget_t* label) {
  my_rich_label_t* rl = (my_rich_label_t*)label;
  size_t i, n;
  int32_t w = 0;
  if (label == NULL) {
    return 0;
  }
  n = my_darray_size(rl->segs);
  for (i = 0; i < n; i++) {
    rich_seg_t* s = (rich_seg_t*)my_darray_get(rl->segs, i);
    w += (int32_t)strlen(s->text) * 8 + (s->bold ? 1 : 0);
  }
  return w;
}
