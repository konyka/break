/**
 * @file qx_stats.c
 * @brief duanxianxia clone: qxlive stats grid + emotion card (M15).
 *
 * 3 rows x 4 stat buttons (bootstrap btn-sm look: rounded, colored or
 * white-with-border); the three curve-backed buttons (情绪指标/涨停家数/
 * 跌停家数) switch the main line chart and stay highlighted (darkened
 * background); 量能 logs only (demo placeholder). The card layout:
 * title bar, centered 16px subtitle, stats grid, distribution bar chart
 * (left) + main line chart (right), feed list below.
 */
#include <stdio.h>
#include <string.h>

#include "../dxx_data.h"
#include "../dxx_theme.h"
#include "myr/my_font.h"
#include "myui/my_window.h"
#include "qx_chart.h"
#include "views.h"

#define STAT_ROWS 3
#define STAT_COLS 4
#define STAT_H 28
#define STAT_ROW_GAP 20
#define SUBTITLE_H 30
#define CHART_AREA_Y (34 + SUBTITLE_H + STAT_ROWS *(STAT_H + STAT_ROW_GAP) + 8)

typedef struct qx_card_t qx_card_t;

typedef struct stat_btn_t {
  my_widget_t base;
  const dxx_stat_t* stat; /**< static */
  qx_card_t* card;        /**< weak */
  int index;
  bool active;
  bool pressed;
  uint64_t down_ms;          /**< press time (min display time) */
  uint32_t release_timer;    /**< pending delayed release (0 = none) */
} stat_btn_t;

/* keep the pressed visual on screen for at least this long (ms); with
 * 30fps frame coalescing a quick click would otherwise never paint it */
#define STAT_PRESS_MIN_MS 120

static my_ret_t stat_release_cb(void* ctx) {
  stat_btn_t* b = (stat_btn_t*)ctx;
  b->release_timer = 0;
  b->pressed = false;
  my_widget_invalidate((my_widget_t*)b, NULL);
  return MY_RET_FAIL; /* one-shot */
}

static void stat_release(stat_btn_t* b) {
  my_pal_t* pal = my_window_pal_of_widget((my_widget_t*)b);
  my_pal_main_loop_t* loop = my_window_loop_of_widget((my_widget_t*)b);
  uint64_t now = pal != NULL ? my_pal_time_now_ms(pal) : 0;
  if (loop != NULL && pal != NULL && now - b->down_ms < STAT_PRESS_MIN_MS) {
    if (b->release_timer == 0) {
      b->release_timer = my_pal_main_loop_add_timer(
          loop, stat_release_cb, b,
          (uint32_t)(STAT_PRESS_MIN_MS - (now - b->down_ms)));
    }
    return;
  }
  b->pressed = false;
}

struct qx_card_t {
  my_widget_t base;
  my_widget_t* line_chart;                 /**< weak */
  my_widget_t* btns[DXX_STAT_COUNT];       /**< weak */
};

/** @brief Darken an rgba32 color to 85% (active state). */
static uint32_t darken(uint32_t c) {
  uint32_t r = (c >> 24) & 0xFF, g = (c >> 16) & 0xFF, b = (c >> 8) & 0xFF;
  r = r * 85 / 100;
  g = g * 85 / 100;
  b = b * 85 / 100;
  return (r << 24) | (g << 16) | (b << 8) | (c & 0xFFu);
}

/** @brief Darken an rgba32 color to 93% (hover state, subtler than active). */
static uint32_t darken_hover(uint32_t c) {
  uint32_t r = (c >> 24) & 0xFF, g = (c >> 16) & 0xFF, b = (c >> 8) & 0xFF;
  r = r * 93 / 100;
  g = g * 93 / 100;
  b = b * 93 / 100;
  return (r << 24) | (g << 16) | (b << 8) | (c & 0xFFu);
}

static void stat_btn_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  stat_btn_t* b = (stat_btn_t*)widget;
  const dxx_stat_t* s = b->stat;
  uint32_t bg;
  bool white_bg;
  int32_t tw = 0, th = 0;
  int32_t vw = 0;
  float x;
  float y = ((float)widget->rect.h - 13.0f) / 2.0f;
  my_font_t* wfont = NULL;
  int32_t ascent = 0;
  if (b->active) {
    bg = darken(s->bg); /* active wins over the transient press frame */
  } else if (b->pressed) {
    bg = darken(darken(s->bg)); /* held down: deepest (bootstrap active) */
  } else {
    bg = s->bg;
  }
  if (!b->active && !b->pressed && widget->hovered) {
    bg = darken_hover(bg); /* hover feedback (M16) */
  }
  white_bg = s->bg == DXX_COLOR_WHITE; /* border decision uses base color */
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(bg));
  my_vgcanvas_fill_rounded_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                                  (float)widget->rect.h},
                                3);
  if (white_bg) {
    my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(0xCCCCCCFFu));
    my_vgcanvas_set_line_width(vg, 1);
    my_vgcanvas_stroke_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                              (float)widget->rect.h});
  }
  /* "label：value" centered (both axes); value colored separately */
  my_vgcanvas_set_font(vg, NULL, 13);
  {
    char label[48];
    snprintf(label, sizeof(label), "%s%s", s->label,
             s->value != NULL ? "：" : "");
    if (my_vgcanvas_measure_text(vg, label, &tw, &th) != MY_RET_OK) {
      /* fallback estimate must count codepoints, not bytes (CJK) */
      const char* p;
      tw = 0;
      for (p = label; *p != '\0';) {
        uint32_t cp = my_utf8_next(&p);
        tw += cp < 0x80 ? 7 : 13;
      }
      th = 13;
    }
    if (s->value != NULL) {
      if (my_vgcanvas_measure_text(vg, s->value, &vw, &th) != MY_RET_OK) {
        vw = (int32_t)strlen(s->value) * 7;
      }
    }
    x = ((float)widget->rect.w - (float)(tw + vw)) / 2.0f;
    y = th > 0 ? ((float)widget->rect.h - (float)th) / 2.0f : y;
    /* optical vertical centering: glyphs sit at baseline - ~0.75*ascent;
     * plain line-box centering leaves the text visibly low */
    my_window_font_of_widget(widget, &wfont, NULL);
    if (wfont != NULL) {
      ascent = my_font_ascent(wfont, 13);
      if (ascent > 0) {
        y = (float)widget->rect.h / 2.0f - 0.75f * (float)ascent;
      }
    }
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(s->fg));
    my_vgcanvas_draw_text(vg, label, x, y);
    if (s->value != NULL) {
      my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(s->value_color));
      my_vgcanvas_draw_text(vg, s->value, x + (float)tw, y);
    }
  }
}

static void stat_set_active(stat_btn_t* b, bool active) {
  b->active = active;
  my_widget_invalidate((my_widget_t*)b, NULL);
}

static void stat_btn_destroy(my_object_t* obj) {
  stat_btn_t* b = (stat_btn_t*)obj;
  if (b->release_timer != 0) {
    my_pal_main_loop_t* loop = my_window_loop_of_widget((my_widget_t*)b);
    if (loop != NULL) {
      my_pal_main_loop_remove_timer(loop, b->release_timer);
    }
    b->release_timer = 0;
  }
  my_widget_destroy((my_widget_t*)b);
  my_object_destroy(obj);
}

static my_ret_t stat_btn_event(my_widget_t* widget, const my_event_t* event) {
  stat_btn_t* b = (stat_btn_t*)widget;
  if (event->type == MY_EVENT_POINTER_DOWN) {
    my_pal_t* pal;
    if (b->release_timer != 0) { /* a fresh press cancels a pending release */
      my_pal_main_loop_t* loop = my_window_loop_of_widget(widget);
      if (loop != NULL) {
        my_pal_main_loop_remove_timer(loop, b->release_timer);
      }
      b->release_timer = 0;
    }
    pal = my_window_pal_of_widget(widget);
    b->down_ms = pal != NULL ? my_pal_time_now_ms(pal) : 0;
    b->pressed = true;
    my_widget_invalidate(widget, NULL); /* pressed visual (M16) */
    return MY_RET_OK;
  }
  if (event->type == MY_EVENT_POINTER_UP) {
    int32_t lx = event->u.pointer.x, ly = event->u.pointer.y;
    bool inside;
    if (!b->pressed) {
      return MY_RET_FAIL;
    }
    stat_release(b); /* pressed stays until min display time elapsed */
    my_widget_invalidate(widget, NULL);
    my_widget_global_to_local(widget, &lx, &ly);
    inside = lx >= 0 && ly >= 0 && lx < widget->rect.w && ly < widget->rect.h;
    if (inside) {
      const dxx_series_t* sr;
      if (b->stat->series < 0) {
        printf("dxx: stat '%s' clicked (demo placeholder)\n", b->stat->label);
        return MY_RET_OK;
      }
      /* switch the main chart + move the highlight */
      sr = &DXX_SERIES[b->stat->series];
      dxx_chart_set_series(b->card->line_chart, sr->name, sr->points,
                           sr->count, sr->ymin, sr->ymax);
      {
        int i;
        for (i = 0; i < DXX_STAT_COUNT; i++) {
          stat_set_active((stat_btn_t*)b->card->btns[i], i == b->index);
        }
      }
    }
    return MY_RET_OK;
  }
  return MY_RET_FAIL;
}

static const my_widget_vtable_t s_stat_btn_vtable = {stat_btn_paint,
                                                     stat_btn_event, NULL, NULL};

/* ---------------- card assembly ---------------- */

static void qx_card_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  int32_t tw = 0, th = 0;
  const char* subtitle = "交易日：09:16:00开始更新";
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_WHITE));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                          (float)widget->rect.h});
  my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(DXX_COLOR_LINE));
  my_vgcanvas_set_line_width(vg, 1);
  my_vgcanvas_stroke_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                            (float)widget->rect.h});
  /* title bar */
  my_vgcanvas_set_font(vg, NULL, 14);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_TEXT));
  my_vgcanvas_draw_text(vg, "情绪直播", 10, 9);
  my_vgcanvas_draw_text(vg, "情绪直播", 11, 9); /* fake bold */
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_LINE));
  my_vgcanvas_fill_rect(vg,
                        &(my_rectf_t){0, 33, (float)widget->rect.w, 1});
  /* centered 16px bold subtitle */
  my_vgcanvas_set_font(vg, NULL, 16);
  if (my_vgcanvas_measure_text(vg, subtitle, &tw, &th) != MY_RET_OK) {
    tw = 16 * 16;
  }
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_TEXT));
  my_vgcanvas_draw_text(vg, subtitle,
                        ((float)widget->rect.w - (float)tw) / 2.0f, 40);
  my_vgcanvas_draw_text(vg, subtitle,
                        ((float)widget->rect.w - (float)tw) / 2.0f + 1.0f, 40);
}

static const my_widget_vtable_t s_qx_card_vtable = {qx_card_paint, NULL, NULL, NULL};

my_widget_t* dxx_build_emotion_card(my_widget_t* parent, int32_t x, int32_t y,
                                    int32_t w, int32_t h) {
  qx_card_t* card =
      (qx_card_t*)my_mem_calloc(NULL, 1, sizeof(qx_card_t));
  my_widget_t* bar_chart;
  my_widget_t* line_chart;
  my_scroll_view_t* feed;
  int i;
  int32_t inner_w = w - 16;
  int32_t bw = (inner_w - 8) / 4; /* distribution chart ~1/4 */
  if (card == NULL ||
      my_widget_init((my_widget_t*)card, NULL, &s_qx_card_vtable,
                     "dxx_qx_card") != MY_RET_OK) {
    my_mem_free(NULL, card);
    return NULL;
  }
  my_widget_set_rect((my_widget_t*)card, &(my_rect_t){x, y, w, h});

  /* stats grid: 3 rows x 4, row pitch = button 28 + gap 20 */
  for (i = 0; i < DXX_STAT_COUNT; i++) {
    int row = i / STAT_COLS, col = i % STAT_COLS;
    int32_t cw = (inner_w - (STAT_COLS - 1) * 10) / STAT_COLS;
    stat_btn_t* b =
        (stat_btn_t*)my_mem_calloc(NULL, 1, sizeof(stat_btn_t));
    if (b == NULL ||
        my_widget_init((my_widget_t*)b, NULL, &s_stat_btn_vtable,
                       "qx_stat") != MY_RET_OK) {
      my_mem_free(NULL, b);
      continue;
    }
    b->stat = &DXX_STATS[i];
    b->card = card;
    b->index = i;
    ((my_object_t*)b)->destroy = stat_btn_destroy;
    b->active = i == 0; /* 情绪指标 selected by default */
    my_widget_set_rect((my_widget_t*)b,
                       &(my_rect_t){8 + col * (cw + 10),
                                    34 + SUBTITLE_H + 6 +
                                        row * (STAT_H + STAT_ROW_GAP),
                                    cw, STAT_H});
    my_widget_add_child((my_widget_t*)card, (my_widget_t*)b);
    my_widget_unref((my_widget_t*)b);
    card->btns[i] = (my_widget_t*)b;
  }

  /* charts: distribution (left) + main line (right) */
  bar_chart = dxx_chart_create(NULL, DXX_CHART_BAR);
  my_widget_set_rect(bar_chart,
                     &(my_rect_t){8, CHART_AREA_Y, bw, 275});
  dxx_chart_set_series(bar_chart, "涨幅分布", DXX_DIST, DXX_DIST_COUNT, 0, 0);
  dxx_chart_set_labels(bar_chart, DXX_DIST_LABELS);
  my_widget_add_child((my_widget_t*)card, bar_chart);
  my_widget_unref(bar_chart);
  line_chart = dxx_chart_create(NULL, DXX_CHART_LINE);
  my_widget_set_rect(line_chart, &(my_rect_t){8 + bw + 8, CHART_AREA_Y,
                                              inner_w - bw - 8, 300});
  dxx_chart_set_series(line_chart, DXX_SERIES[0].name, DXX_SERIES[0].points,
                       DXX_SERIES[0].count, DXX_SERIES[0].ymin,
                       DXX_SERIES[0].ymax);
  my_widget_add_child((my_widget_t*)card, line_chart);
  my_widget_unref(line_chart);
  card->line_chart = line_chart;

  /* feed list below the charts */
  feed = dxx_feed_list_create(DXX_LIVE_EMOTION, DXX_LIVE_EMOTION_COUNT,
                              inner_w);
  my_widget_set_rect((my_widget_t*)feed,
                     &(my_rect_t){8, CHART_AREA_Y + 300 + 8, inner_w,
                                  h - (CHART_AREA_Y + 300 + 8) - 8});
  my_widget_add_child((my_widget_t*)card, (my_widget_t*)feed);
  my_widget_unref((my_widget_t*)feed);

  if (parent != NULL) {
    my_widget_add_child(parent, (my_widget_t*)card);
  }
  return (my_widget_t*)card;
}
