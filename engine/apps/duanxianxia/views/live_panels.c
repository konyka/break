/**
 * @file live_panels.c
 * @brief duanxianxia clone: two-column live area (M14c).
 *
 * Left card 情绪直播 (750x800); right column (530): 涨停直播 400 /
 * 异动 160 / 股票池 430 / 成交额 250 (+12 gaps). Cards: white bg, 1px
 * #eee edge, bold title bar; feed bodies scroll via my_scroll_view
 * (wheel; nested inside the page-level scroll view — the inner view
 * consumes the wheel, so it never bubbles to the page).
 */
#include <stdio.h>
#include <string.h>

#include "../dxx_data.h"
#include "../dxx_theme.h"
#include "myui/widgets/my_rich_label.h"
#include "myui/widgets/my_scroll_view.h"
#include "nav_item.h" /* dxx_text_estimate */
#include "views.h"

#define CARD_TITLE_H 34
#define FEED_ROW_H 24

/* ---------------- generic card ---------------- */

typedef struct feed_row_t {
  my_widget_t base;
  const char* time; /**< static */
} feed_row_t;

static void card_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  const char* title = (const char*)my_widget_get_user_data(widget);
  int32_t th = 0, tw = 0;
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_WHITE));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                          (float)widget->rect.h});
  my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(DXX_COLOR_LINE));
  my_vgcanvas_set_line_width(vg, 1);
  my_vgcanvas_stroke_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                            (float)widget->rect.h});
  if (title != NULL) {
    my_vgcanvas_set_font(vg, NULL, 14);
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_TEXT));
    my_vgcanvas_draw_text(vg, title, 10, 9);
    my_vgcanvas_draw_text(vg, title, 11, 9); /* fake bold */
    (void)th;
    (void)tw;
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_LINE));
    my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, CARD_TITLE_H - 1,
                                            (float)widget->rect.w, 1});
  }
}

/** @brief Feed row: grey 12px time + rich_label text (keyword colors). */
static void feed_row_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  feed_row_t* r = (feed_row_t*)widget;
  my_vgcanvas_set_font(vg, NULL, 12);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_MUTED));
  my_vgcanvas_draw_text(vg, r->time, 0, ((float)widget->rect.h - 12.0f) / 2.0f);
}

static const my_widget_vtable_t s_card_vtable = {card_on_paint, NULL, NULL, NULL};
static const my_widget_vtable_t s_feed_row_vtable = {feed_row_paint, NULL,
                                                     NULL, NULL};

/* red keywords / green keywords for the feed text highlight */
static const char* const KW_UP[] = {"涨停", "触板", "封板", "回封",
                                    "火箭发射", "封板", NULL};
static const char* const KW_DOWN[] = {"跳水", "翻绿", "走弱", "下跌", NULL};

static uint32_t keyword_color(const char* at, size_t* out_len) {
  const char* const* k;
  for (k = KW_UP; *k != NULL; k++) {
    if (strncmp(at, *k, strlen(*k)) == 0) {
      *out_len = strlen(*k);
      return DXX_COLOR_UP;
    }
  }
  for (k = KW_DOWN; *k != NULL; k++) {
    if (strncmp(at, *k, strlen(*k)) == 0) {
      *out_len = strlen(*k);
      return DXX_COLOR_DOWN;
    }
  }
  return 0;
}

/** @brief Add text to the rich label, coloring keyword occurrences. */
static void feed_add_text(my_widget_t* rl, const char* text) {
  const char* p = text;
  while (*p != '\0') {
    size_t kw_len = 0;
    uint32_t kw = keyword_color(p, &kw_len);
    if (kw != 0) {
      char seg[16];
      memcpy(seg, p, kw_len);
      seg[kw_len] = '\0';
      my_rich_label_add_segment(rl, seg, kw, false);
      p += kw_len;
    } else {
      /* plain run until the next keyword (or end) */
      const char* start = p;
      char seg[128];
      size_t len;
      p++; /* advance one UTF-8 char */
      while ((*p & 0xC0) == 0x80) {
        p++;
      }
      while (*p != '\0') {
        size_t dummy;
        if (keyword_color(p, &dummy) != 0) {
          break;
        }
        p++;
        while ((*p & 0xC0) == 0x80) {
          p++;
        }
      }
      len = (size_t)(p - start);
      if (len >= sizeof(seg)) {
        len = sizeof(seg) - 1;
      }
      memcpy(seg, start, len);
      seg[len] = '\0';
      my_rich_label_add_segment(rl, seg, DXX_COLOR_TEXT, false);
    }
  }
}

/** @brief Feed list (time + keyword-colored text rows) inside a
 * scroll_view; w = list width. Shared by the plain feed cards and the
 * emotion card (M15). */
my_scroll_view_t* dxx_feed_list_create(const dxx_live_item_t* items,
                                          int count, int32_t w) {
  my_scroll_view_t* sv = my_scroll_view_create(NULL);
  my_widget_t* content = my_widget_create(NULL, "feed_content");
  int i;
  for (i = 0; i < count; i++) {
    feed_row_t* row =
        (feed_row_t*)my_mem_calloc(NULL, 1, sizeof(feed_row_t));
    my_widget_t* rl;
    if (row == NULL) {
      continue;
    }
    if (my_widget_init((my_widget_t*)row, NULL, &s_feed_row_vtable,
                       "feed_row") != MY_RET_OK) {
      my_mem_free(NULL, row);
      continue;
    }
    row->time = items[i].time;
    my_widget_set_rect((my_widget_t*)row,
                       &(my_rect_t){0, i * FEED_ROW_H, w, FEED_ROW_H});
    rl = my_rich_label_create(NULL);
    my_widget_set_rect(rl, &(my_rect_t){52, 0, w - 52, FEED_ROW_H});
    feed_add_text(rl, items[i].text);
    my_widget_add_child((my_widget_t*)row, rl);
    my_widget_unref(rl);
    my_widget_add_child(content, (my_widget_t*)row);
    my_widget_unref((my_widget_t*)row);
  }
  my_scroll_view_set_content(sv, content);
  my_scroll_view_set_content_height(sv, count * FEED_ROW_H);
  my_widget_unref(content);
  return sv;
}

/** @brief Build a scrolling feed card; returns the card widget. */
static my_widget_t* feed_card(my_widget_t* parent, int32_t x, int32_t y,
                              int32_t w, int32_t h, const char* title,
                              const dxx_live_item_t* items, int count) {
  my_widget_t* card = my_widget_create(NULL, "dxx_card");
  my_scroll_view_t* sv = dxx_feed_list_create(items, count, w - 16);
  card->vtable = &s_card_vtable;
  my_widget_set_user_data(card, (void*)title);
  my_widget_set_rect(card, &(my_rect_t){x, y, w, h});
  my_widget_set_rect((my_widget_t*)sv,
                     &(my_rect_t){8, CARD_TITLE_H + 4, w - 16,
                                  h - CARD_TITLE_H - 12});
  my_widget_add_child(card, (my_widget_t*)sv);
  my_widget_unref((my_widget_t*)sv);
  my_widget_add_child(parent, card);
  return card;
}

/* ---------------- 股票池 card (4-col table) ---------------- */

#define WATCH_COLS 4
static const int32_t WATCH_COL_W[WATCH_COLS] = {70, 90, 70, 70};

typedef struct watch_row_t {
  my_widget_t base;
  const dxx_watch_row_t* row;
  bool header;
} watch_row_t;

static void watch_row_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  watch_row_t* wr = (watch_row_t*)widget;
  char speed[16];
  char turn[16];
  const char* texts[WATCH_COLS];
  uint32_t colors[WATCH_COLS];
  int c;
  float x = 0;
  float y = ((float)widget->rect.h - 12.0f) / 2.0f;
  my_vgcanvas_set_font(vg, NULL, 12);
  if (wr->header) {
    texts[0] = "代码";
    texts[1] = "名称";
    texts[2] = "涨速";
    texts[3] = "换手";
    for (c = 0; c < WATCH_COLS; c++) {
      colors[c] = DXX_COLOR_MUTED;
    }
  } else {
    snprintf(speed, sizeof(speed), "%+.2f%%", wr->row->speed_pct);
    snprintf(turn, sizeof(turn), "%.2f%%", wr->row->turnover_pct);
    texts[0] = wr->row->code;
    texts[1] = wr->row->name;
    texts[2] = speed;
    texts[3] = turn;
    colors[0] = DXX_COLOR_MUTED;
    colors[1] = DXX_COLOR_TEXT;
    colors[2] = wr->row->speed_pct >= 0 ? DXX_COLOR_UP : DXX_COLOR_DOWN;
    colors[3] = DXX_COLOR_MUTED;
  }
  for (c = 0; c < WATCH_COLS; c++) {
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(colors[c]));
    my_vgcanvas_draw_text(vg, texts[c], x + 4, y);
    x += (float)WATCH_COL_W[c];
  }
}

static const my_widget_vtable_t s_watch_row_vtable = {watch_row_paint, NULL,
                                                      NULL, NULL};

static my_widget_t* watch_card(my_widget_t* parent, int32_t x, int32_t y,
                               int32_t w, int32_t h) {
  my_widget_t* card = my_widget_create(NULL, "dxx_card");
  my_scroll_view_t* sv = my_scroll_view_create(NULL);
  my_widget_t* content = my_widget_create(NULL, "watch_content");
  int i;
  card->vtable = &s_card_vtable;
  my_widget_set_user_data(card, (void*)"股票池");
  my_widget_set_rect(card, &(my_rect_t){x, y, w, h});
  my_widget_set_rect((my_widget_t*)sv,
                     &(my_rect_t){8, CARD_TITLE_H + 4, w - 16,
                                  h - CARD_TITLE_H - 12});
  for (i = 0; i < DXX_WATCH_COUNT + 1; i++) {
    watch_row_t* row =
        (watch_row_t*)my_mem_calloc(NULL, 1, sizeof(watch_row_t));
    if (row == NULL) {
      continue;
    }
    if (my_widget_init((my_widget_t*)row, NULL, &s_watch_row_vtable,
                       "watch_row") != MY_RET_OK) {
      my_mem_free(NULL, row);
      continue;
    }
    row->header = i == 0;
    row->row = i > 0 ? &DXX_WATCH[i - 1] : NULL;
    my_widget_set_rect((my_widget_t*)row,
                       &(my_rect_t){0, i * FEED_ROW_H, w - 16, FEED_ROW_H});
    my_widget_add_child(content, (my_widget_t*)row);
    my_widget_unref((my_widget_t*)row);
  }
  my_scroll_view_set_content(sv, content);
  my_scroll_view_set_content_height(sv, (DXX_WATCH_COUNT + 1) * FEED_ROW_H);
  my_widget_unref(content);
  my_widget_add_child(card, (my_widget_t*)sv);
  my_widget_unref((my_widget_t*)sv);
  my_widget_add_child(parent, card);
  return card;
}

/* ---------------- 成交额 card ---------------- */

static void amount_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  int32_t tw = 0, th = 0;
  float cx = (float)widget->rect.w / 2.0f;
  my_vgcanvas_set_font(vg, NULL, 28);
  if (my_vgcanvas_measure_text(vg, DXX_AMOUNT_MAIN, &tw, &th) != MY_RET_OK) {
    tw = dxx_text_estimate(DXX_AMOUNT_MAIN, 28);
  }
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_UP));
  my_vgcanvas_draw_text(vg, DXX_AMOUNT_MAIN, cx - (float)tw / 2.0f, 60);
  my_vgcanvas_draw_text(vg, DXX_AMOUNT_MAIN, cx - (float)tw / 2.0f + 1.0f,
                        60); /* fake bold */
  my_vgcanvas_set_font(vg, NULL, 12);
  if (my_vgcanvas_measure_text(vg, DXX_AMOUNT_SUB, &tw, &th) != MY_RET_OK) {
    tw = dxx_text_estimate(DXX_AMOUNT_SUB, 12);
  }
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_MUTED));
  my_vgcanvas_draw_text(vg, DXX_AMOUNT_SUB, cx - (float)tw / 2.0f, 100);
}

static const my_widget_vtable_t s_amount_vtable = {amount_on_paint, NULL,
                                                   NULL, NULL};

static my_widget_t* amount_card(my_widget_t* parent, int32_t x, int32_t y,
                                int32_t w, int32_t h) {
  my_widget_t* card = my_widget_create(NULL, "dxx_card");
  my_widget_t* body = my_widget_create(NULL, "amount_body");
  card->vtable = &s_card_vtable;
  my_widget_set_user_data(card, (void*)"成交额");
  my_widget_set_rect(card, &(my_rect_t){x, y, w, h});
  body->vtable = &s_amount_vtable;
  my_widget_set_rect(body, &(my_rect_t){8, CARD_TITLE_H + 4, w - 16,
                                        h - CARD_TITLE_H - 12});
  my_widget_add_child(card, body);
  my_widget_unref(body);
  my_widget_add_child(parent, card);
  return card;
}

/* ---------------- area ---------------- */

int32_t dxx_build_live_area(my_widget_t* parent, int32_t x, int32_t y,
                            int32_t w) {
  int32_t left_w = 750;
  int32_t right_x = x + left_w + 20;
  int32_t right_w = w - left_w - 20; /* 530 */
  int32_t right_h = 400 + 12 + 160 + 12 + 430 + 12 + 250; /* 1276 */
  int32_t ry = y;
  /* M15: emotion card = stats grid + charts + feed; stretched to match
   * the right column height */
  dxx_build_emotion_card(parent, x, y, left_w, right_h);
  feed_card(parent, right_x, ry, right_w, 400, "涨停直播", DXX_LIVE_ZT,
            DXX_LIVE_ZT_COUNT);
  ry += 400 + 12;
  feed_card(parent, right_x, ry, right_w, 160, "异动", DXX_LIVE_YIDONG,
            DXX_LIVE_YIDONG_COUNT);
  ry += 160 + 12;
  watch_card(parent, right_x, ry, right_w, 430);
  ry += 430 + 12;
  amount_card(parent, right_x, ry, right_w, 250);
  ry += 250;
  return ry - y; /* = right column height (1276) */
}
