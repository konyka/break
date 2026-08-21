/**
 * @file index_strip.c
 * @brief duanxianxia clone: 12-column index strip (M14b).
 *
 * White card with a 1px #eee bottom edge (the site's drop shadow is
 * faked with a border — no shadow support, see docs/apps/duanxianxia.md).
 * Each column: name (#333) + value (bold, rise red / fall green) +
 * change% (same coloring), all horizontally centered. Columns share the
 * strip width equally (reflowed in on_layout).
 */
#include <stdio.h>

#include "../dxx_data.h"
#include "../dxx_theme.h"
#include "views.h"

typedef struct index_col_t {
  my_widget_t base;
  const dxx_index_quote_t* quote; /**< static table row */
  char value[24];                 /**< formatted */
  char pct[16];
} index_col_t;

static void col_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  index_col_t* col = (index_col_t*)widget;
  uint32_t up_down =
      col->quote->change_pct >= 0 ? DXX_COLOR_UP : DXX_COLOR_DOWN;
  int32_t tw = 0, th = 0;
  float cx = (float)widget->rect.w / 2.0f;
  /* name (12px #333) */
  my_vgcanvas_set_font(vg, NULL, 12);
  if (my_vgcanvas_measure_text(vg, col->quote->name, &tw, &th) != MY_RET_OK) {
    tw = (int32_t)0;
  }
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_TEXT));
  my_vgcanvas_draw_text(vg, col->quote->name, cx - (float)tw / 2.0f, 6);
  /* value (bold, rise/fall color; fake bold = +1px double draw) */
  my_vgcanvas_set_font(vg, NULL, 14);
  if (my_vgcanvas_measure_text(vg, col->value, &tw, &th) != MY_RET_OK) {
    tw = 0;
  }
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(up_down));
  my_vgcanvas_draw_text(vg, col->value, cx - (float)tw / 2.0f, 24);
  my_vgcanvas_draw_text(vg, col->value, cx - (float)tw / 2.0f + 1.0f, 24);
  /* change% (same color) */
  if (my_vgcanvas_measure_text(vg, col->pct, &tw, &th) != MY_RET_OK) {
    tw = 0;
  }
  my_vgcanvas_draw_text(vg, col->pct, cx - (float)tw / 2.0f, 44);
}

/** @brief Strip: white bg + bottom edge; equal columns in on_layout. */
static void strip_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_WHITE));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                          (float)widget->rect.h});
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_LINE));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, (float)widget->rect.h - 1,
                                          (float)widget->rect.w, 1});
}

static void strip_on_layout(my_widget_t* widget) {
  size_t i, n = my_widget_child_count(widget);
  int32_t cw = n > 0 ? widget->rect.w / (int32_t)n : 0;
  for (i = 0; i < n; i++) {
    my_widget_t* c = my_widget_get_child(widget, i);
    (void)my_widget_set_layout_rect(
        c, &(my_rect_t){(int32_t)i * cw, 0, cw, widget->rect.h});
  }
}

static const my_widget_vtable_t s_col_vtable = {col_on_paint, NULL, NULL, NULL};
static const my_widget_vtable_t s_strip_vtable = {strip_on_paint, NULL,
                                                  strip_on_layout, NULL};

my_widget_t* dxx_build_index_strip(my_widget_t* parent) {
  my_widget_t* strip = my_widget_create(NULL, "dxx_index_strip");
  int i;
  strip->vtable = &s_strip_vtable;
  for (i = 0; i < DXX_INDEX_COUNT; i++) {
    index_col_t* col =
        (index_col_t*)my_mem_calloc(NULL, 1, sizeof(index_col_t));
    if (col == NULL) {
      continue;
    }
    if (my_widget_init((my_widget_t*)col, NULL, &s_col_vtable,
                       "dxx_index_col") != MY_RET_OK) {
      my_mem_free(NULL, col);
      continue;
    }
    col->quote = &DXX_INDICES[i];
    snprintf(col->value, sizeof(col->value), "%.2f", col->quote->value);
    snprintf(col->pct, sizeof(col->pct), "%+.2f%%", col->quote->change_pct);
    my_widget_add_child(strip, (my_widget_t*)col);
    my_widget_unref((my_widget_t*)col);
  }
  if (parent != NULL) {
    my_widget_add_child(parent, strip);
  }
  return strip;
}
