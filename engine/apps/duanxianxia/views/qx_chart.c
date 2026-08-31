/**
 * @file qx_chart.c
 * @brief Chart widget implementation (M15).
 *
 * Line mode: white card, 5 horizontal grid lines, y ticks (min/mid/max),
 * x time ticks (09:30/11:30/13:00/15:00), title top-left, polyline
 * stroked in the site red #E64C62 (2px, backend AA applies).
 * Bar mode: center axis + signed buckets (red above / green below).
 */
#include "qx_chart.h"

#include <stdio.h>

#include "myui/my_window.h"
#include "myr/my_font.h"
#include "../dxx_data.h"

#include "../dxx_theme.h"

#define CHART_PAD_L 36
#define CHART_PAD_B 20
#define CHART_PAD_T 24
#define CHART_PAD_R 8
#define CHART_GRID_LINES 5

typedef struct dxx_chart_t {
  my_widget_t base;
  dxx_chart_mode_t mode;
  char name[32];
  const float* points;            /**< borrowed */
  const char* const* labels;      /**< borrowed bucket labels (bar mode) */
  int count;
  float ymin;
  float ymax;
} dxx_chart_t;

static void chart_grid(my_widget_t* widget, my_vgcanvas_t* vg, int32_t plot_w,
                       int32_t plot_h) {
  int i;
  (void)widget;
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_LINE));
  for (i = 0; i < CHART_GRID_LINES; i++) {
    float y = (float)CHART_PAD_T +
              (float)plot_h * (float)i / (float)(CHART_GRID_LINES - 1);
    my_vgcanvas_fill_rect(vg, &(my_rectf_t){(float)CHART_PAD_L, y,
                                            (float)plot_w, 1});
  }
}

static void chart_line_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  dxx_chart_t* c = (dxx_chart_t*)widget;
  int32_t plot_w = widget->rect.w - CHART_PAD_L - CHART_PAD_R;
  int32_t plot_h = widget->rect.h - CHART_PAD_T - CHART_PAD_B;
  char buf[24];
  int i;
  /* title */
  my_vgcanvas_set_font(vg, NULL, 12);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_TEXT));
  my_vgcanvas_draw_text(vg, c->name, CHART_PAD_L, 6);
  if (plot_w <= 0 || plot_h <= 0) {
    return;
  }
  chart_grid(widget, vg, plot_w, plot_h);
  /* y ticks: min / mid / max */
  my_vgcanvas_set_font(vg, NULL, 10);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_MUTED));
  snprintf(buf, sizeof(buf), "%.0f", (double)c->ymax);
  my_vgcanvas_draw_text(vg, buf, 2, CHART_PAD_T - 5);
  snprintf(buf, sizeof(buf), "%.0f", (double)((c->ymin + c->ymax) / 2.0f));
  my_vgcanvas_draw_text(vg, buf, 2.0f, (float)(CHART_PAD_T + plot_h / 2 - 5));
  snprintf(buf, sizeof(buf), "%.0f", (double)c->ymin);
  my_vgcanvas_draw_text(vg, buf, 2.0f, (float)(CHART_PAD_T + plot_h - 5));
  /* x time ticks */
  {
    static const char* const T[] = {"09:30", "11:30", "13:00", "15:00"};
    for (i = 0; i < 4; i++) {
      float x = (float)CHART_PAD_L + (float)plot_w * (float)i / 3.0f - 14.0f;
      my_vgcanvas_draw_text(vg, T[i], x,
                            (float)(CHART_PAD_T + plot_h + 5));
    }
  }
  /* polyline */
  if (c->points != NULL && c->count > 0 && c->ymax > c->ymin) {
    float span = c->ymax - c->ymin;
    my_vgcanvas_set_stroke_color(vg,
                                 my_color_from_rgba32(DXX_COLOR_PRIMARY));
    my_vgcanvas_set_line_width(vg, 2);
    my_vgcanvas_begin_path(vg);
    for (i = 0; i < c->count; i++) {
      float x = (float)CHART_PAD_L +
                (c->count > 1
                     ? (float)plot_w * (float)i / (float)(c->count - 1)
                     : (float)plot_w / 2.0f);
      float v = c->points[i];
      float y;
      if (v < c->ymin) {
        v = c->ymin;
      }
      if (v > c->ymax) {
        v = c->ymax;
      }
      y = (float)CHART_PAD_T +
          (float)plot_h * (1.0f - (v - c->ymin) / span);
      if (i == 0) {
        my_vgcanvas_move_to(vg, x, y);
      } else {
        my_vgcanvas_line_to(vg, x, y);
      }
    }
    my_vgcanvas_stroke(vg);
  }
}

/* echarts 风格横向分布条形（对齐原站 qxlive 的 zf 图）：类别标签在左、
 * 桶色 跌停 #C4E7CF / 跌档 #4FB771 / 平盘 #ACB0C0 / 涨档 #E5562C、
 * 数值标签在条形右端，无坐标轴/网格线。 */
#define DIST_LABEL_W 44
#define DIST_VALUE_W 34
static const uint32_t DIST_COLORS[DXX_DIST_COUNT] = {
    0xC4E7CFFFu, 0x4FB771FFu, 0x4FB771FFu, 0x4FB771FFu,
    0x4FB771FFu, 0xACB0C0FFu, 0xE5562CFFu, 0xE5562CFFu,
    0xE5562CFFu, 0xE5562CFFu, 0xE5562CFFu,
};

static void chart_bar_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  dxx_chart_t* c = (dxx_chart_t*)widget;
  int32_t plot_w = widget->rect.w - DIST_LABEL_W - DIST_VALUE_W - 10;
  int32_t plot_h = widget->rect.h - 6;
  float max_v = 1.0f;
  float row_h;
  int i;
  my_font_t* f = NULL;
  int32_t ascent = 0;
  if (c->points == NULL || c->count <= 0 || plot_w <= 0 || plot_h <= 0) {
    return;
  }
  for (i = 0; i < c->count; i++) {
    float v = c->points[i] < 0 ? -c->points[i] : c->points[i];
    if (v > max_v) {
      max_v = v;
    }
  }
  my_vgcanvas_set_font(vg, NULL, 11);
  my_window_font_of_widget(widget, &f, NULL);
  if (f != NULL) {
    ascent = my_font_ascent(f, 11);
  }
  row_h = (float)plot_h / (float)c->count;
  for (i = 0; i < c->count; i++) {
    float v = c->points[i] < 0 ? -c->points[i] : c->points[i];
    float bw = v / max_v * ((float)plot_w - 4.0f);
    float y = 3.0f + (float)i * row_h;
    float bh = row_h * 0.62f;
    float ty = ascent > 0 ? y + row_h / 2.0f - 0.75f * (float)ascent
                          : y + (row_h - 11.0f) / 2.0f;
    char val[16];
    const char* label =
        (c->labels != NULL && i < c->count) ? c->labels[i] : "";
    /* category label (left) */
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_MUTED));
    my_vgcanvas_draw_text(vg, label, 6.0f, ty);
    /* bar */
    my_vgcanvas_set_fill_color(
        vg, my_color_from_rgba32(DIST_COLORS[i % DXX_DIST_COUNT]));
    my_vgcanvas_fill_rect(vg,
                          &(my_rectf_t){(float)DIST_LABEL_W, y, bw, bh});
    /* value label at the bar's right end */
    snprintf(val, sizeof(val), "%d", (int32_t)v);
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_TEXT));
    my_vgcanvas_draw_text(vg, val, (float)DIST_LABEL_W + bw + 3.0f, ty);
  }
}

static void chart_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  dxx_chart_t* c = (dxx_chart_t*)widget;
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_WHITE));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                          (float)widget->rect.h});
  my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(DXX_COLOR_LINE));
  my_vgcanvas_set_line_width(vg, 1);
  my_vgcanvas_stroke_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                            (float)widget->rect.h});
  if (c->mode == DXX_CHART_BAR) {
    chart_bar_paint(widget, vg);
  } else {
    chart_line_paint(widget, vg);
  }
}

static const my_widget_vtable_t s_chart_vtable = {chart_on_paint, NULL, NULL, NULL};

my_widget_t* dxx_chart_create(const my_allocator_t* allocator,
                              dxx_chart_mode_t mode) {
  dxx_chart_t* c =
      (dxx_chart_t*)my_mem_calloc(allocator, 1, sizeof(dxx_chart_t));
  if (c == NULL) {
    return NULL;
  }
  if (my_widget_init((my_widget_t*)c, allocator, &s_chart_vtable,
                     "dxx_chart") != MY_RET_OK) {
    my_mem_free(allocator, c);
    return NULL;
  }
  c->mode = mode;
  return (my_widget_t*)c;
}

void dxx_chart_set_series(my_widget_t* chart, const char* name,
                          const float* points, int count, float ymin,
                          float ymax) {
  dxx_chart_t* c = (dxx_chart_t*)chart;
  if (chart == NULL) {
    return;
  }
  snprintf(c->name, sizeof(c->name), "%s", name != NULL ? name : "");
  c->points = points;
  c->count = count;
  c->ymin = ymin;
  c->ymax = ymax;
  my_widget_invalidate(chart, NULL);
}

void dxx_chart_set_labels(my_widget_t* chart, const char* const* labels) {
  dxx_chart_t* c = (dxx_chart_t*)chart;
  if (chart != NULL) {
    c->labels = labels;
    my_widget_invalidate(chart, NULL);
  }
}

const char* dxx_chart_get_series_name(my_widget_t* chart) {
  dxx_chart_t* c = (dxx_chart_t*)chart;
  if (chart == NULL || c->name[0] == '\0') {
    return NULL;
  }
  return c->name;
}
