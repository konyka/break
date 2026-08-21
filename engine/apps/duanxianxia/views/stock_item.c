/**
 * @file stock_item.c
 * @brief Stock item implementation (M14c).
 */
#include "stock_item.h"

#include <stdio.h>
#include <string.h>

#include "../dxx_theme.h"
#include "myc/my_str.h"
#include "myui/my_layout.h"
#include "myui/widgets/my_dialog.h"
#include "myui/widgets/my_label.h"
#include "nav_item.h" /* dxx_text_estimate */

/* badge colors per market (approximation — the site's badge colors are
 * set in JS and not statically available; see docs/apps/duanxianxia.md) */
#define DXX_BADGE_SH 0xE64C62FFu
#define DXX_BADGE_SZ 0x347DFAFFu
#define DXX_BADGE_CY 0xEC971FFFu
#define DXX_BADGE_KC 0x9B59B6FFu
#define DXX_BADGE_BJ 0x17A2B8FFu

#define DXX_BROKEN_ORANGE 0xEC971FFFu
#define DXX_ITEM_HOVER 0xF0F0F0FFu

typedef struct stock_item_t {
  my_widget_t base;
  const dxx_stock_t* stock;  /**< static snapshot row */
  my_window_manager_t* wm;   /**< weak: dialog host */
  char pct[16];              /**< "[+10.04%]" */
  bool pressed;
} stock_item_t;

static const char* market_letter(dxx_market_t m) {
  static const char* const L[] = {"沪", "深", "创", "科", "北"};
  return L[(int)m];
}

static uint32_t market_color(dxx_market_t m) {
  static const uint32_t C[] = {DXX_BADGE_SH, DXX_BADGE_SZ, DXX_BADGE_CY,
                               DXX_BADGE_KC, DXX_BADGE_BJ};
  return C[(int)m];
}

static uint32_t state_color(const dxx_stock_t* s) {
  if (s->state == DXX_ST_SUCCESS) {
    return DXX_COLOR_UP;
  }
  if (s->state == DXX_ST_BROKEN) {
    return DXX_BROKEN_ORANGE;
  }
  return DXX_COLOR_DOWN;
}

static const char* state_text(const dxx_stock_t* s) {
  return s->state == DXX_ST_SUCCESS
             ? "成"
             : s->state == DXX_ST_BROKEN ? "炸" : "败";
}

int32_t dxx_stock_item_width(const dxx_stock_t* stock) {
  int32_t w = 2 + 18 + 4; /* padding + badge + gap */
  w += dxx_text_estimate(stock->name, 13) + 6;
  w += 8 * 7; /* "[+10.04%]" at 12px */
  if (stock->theme != NULL) {
    w += 6 + dxx_text_estimate(stock->theme, 12);
  }
  return w + 6;
}

static void stock_item_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  stock_item_t* it = (stock_item_t*)widget;
  const dxx_stock_t* s = it->stock;
  uint32_t name_c = state_color(s);
  uint32_t pct_c = s->change_pct >= 0 ? DXX_COLOR_UP : DXX_COLOR_DOWN;
  float x = 2;
  int32_t tw = 0, th = 0;
  if (widget->hovered) {
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_ITEM_HOVER));
    my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                            (float)widget->rect.h});
  }
  /* badge: rounded 18x16, white market letter */
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(market_color(s->market)));
  my_vgcanvas_fill_rounded_rect(
      vg, &(my_rectf_t){x, ((float)widget->rect.h - 16.0f) / 2.0f, 18, 16}, 3);
  my_vgcanvas_set_font(vg, NULL, 11);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_WHITE));
  my_vgcanvas_draw_text(vg, market_letter(s->market), x + 3,
                        ((float)widget->rect.h - 11.0f) / 2.0f);
  x += 18 + 4;
  /* name (成 = red fake bold) */
  my_vgcanvas_set_font(vg, NULL, 13);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(name_c));
  my_vgcanvas_draw_text(vg, s->name, x, ((float)widget->rect.h - 13.0f) / 2.0f);
  if (s->state == DXX_ST_SUCCESS) {
    my_vgcanvas_draw_text(vg, s->name, x + 1.0f,
                          ((float)widget->rect.h - 13.0f) / 2.0f);
  }
  if (my_vgcanvas_measure_text(vg, s->name, &tw, &th) != MY_RET_OK) {
    tw = dxx_text_estimate(s->name, 13);
  }
  x += (float)tw + 6;
  /* [change%] 12px rise/fall */
  my_vgcanvas_set_font(vg, NULL, 12);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(pct_c));
  my_vgcanvas_draw_text(vg, it->pct, x, ((float)widget->rect.h - 12.0f) / 2.0f);
  if (my_vgcanvas_measure_text(vg, it->pct, &tw, &th) != MY_RET_OK) {
    tw = (int32_t)strlen(it->pct) * 7;
  }
  x += (float)tw + 6;
  /* theme 12px #999 */
  if (s->theme != NULL) {
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_MUTED));
    my_vgcanvas_draw_text(vg, s->theme, x,
                          ((float)widget->rect.h - 12.0f) / 2.0f);
  }
}

/** @brief Close callback: destroy the card dialog. */
static void stock_card_result(void* ctx, int32_t result) {
  (void)result;
  my_dialog_destroy((my_dialog_t*)ctx);
}

/** @brief Click -> stock card dialog (real snapshot data). */
static void stock_item_open_card(stock_item_t* it) {
  const dxx_stock_t* s = it->stock;
  my_dialog_t* dlg = my_dialog_create(NULL, it->wm->pal, s->name, 300, 180);
  my_widget_t* content;
  my_widget_t* line;
  char buf[96];
  if (dlg == NULL) {
    return;
  }
  content = my_dialog_content(dlg);
  {
    /* the dialog window needs a font: inherit the item's root window's */
    my_widget_t* root = (my_widget_t*)it;
    while (root->parent != NULL) {
      root = root->parent;
    }
    if (my_str_eq(root->widget_type, "window")) {
      my_window_t* rw = (my_window_t*)root;
      if (rw->font != NULL) {
        my_window_set_font(dlg->win, rw->font, rw->font_size);
      }
    }
  }
  snprintf(buf, sizeof(buf), "[%s] %s  %s", market_letter(s->market), s->name,
           state_text(s));
  line = my_label_create(NULL, buf);
  my_widget_set_layout_params(line, "h:28");
  my_widget_add_child(content, line);
  my_widget_unref(line);
  snprintf(buf, sizeof(buf), "涨幅 %+.2f%%", s->change_pct);
  line = my_label_create(NULL, buf);
  my_widget_set_layout_params(line, "h:28");
  my_widget_add_child(content, line);
  my_widget_unref(line);
  snprintf(buf, sizeof(buf), "题材 %s", s->theme != NULL ? s->theme : "无");
  line = my_label_create(NULL, buf);
  my_widget_set_layout_params(line, "h:28");
  my_widget_add_child(content, line);
  my_widget_unref(line);
  my_dialog_add_button(dlg, "关闭", 0);
  my_dialog_open(dlg, it->wm, stock_card_result, dlg);
}

static my_ret_t stock_item_event(my_widget_t* widget, const my_event_t* event) {
  stock_item_t* it = (stock_item_t*)widget;
  if (event->type == MY_EVENT_POINTER_DOWN) {
    it->pressed = true;
    return MY_RET_OK;
  }
  if (event->type == MY_EVENT_POINTER_UP) {
    int32_t lx = event->u.pointer.x, ly = event->u.pointer.y;
    bool inside;
    if (!it->pressed) {
      return MY_RET_FAIL;
    }
    it->pressed = false;
    my_widget_global_to_local(widget, &lx, &ly);
    inside = lx >= 0 && ly >= 0 && lx < widget->rect.w && ly < widget->rect.h;
    if (inside) {
      stock_item_open_card(it);
    }
    return MY_RET_OK;
  }
  return MY_RET_FAIL;
}

static const my_widget_vtable_t s_stock_item_vtable = {stock_item_paint,
                                                       stock_item_event, NULL, NULL};

my_widget_t* dxx_stock_item_create(const my_allocator_t* allocator,
                                   const dxx_stock_t* stock,
                                   my_window_manager_t* wm) {
  stock_item_t* it;
  char tip[128];
  if (stock == NULL) {
    return NULL;
  }
  it = (stock_item_t*)my_mem_calloc(allocator, 1, sizeof(stock_item_t));
  if (it == NULL) {
    return NULL;
  }
  if (my_widget_init((my_widget_t*)it, allocator, &s_stock_item_vtable,
                     "dxx_stock") != MY_RET_OK) {
    my_mem_free(allocator, it);
    return NULL;
  }
  it->stock = stock;
  it->wm = wm;
  snprintf(it->pct, sizeof(it->pct), "[%+.2f%%]", stock->change_pct);
  snprintf(tip, sizeof(tip), "%s %s %+.2f%% %s", stock->name,
           state_text(stock), stock->change_pct,
           stock->theme != NULL ? stock->theme : "无题材");
  my_widget_set_tooltip((my_widget_t*)it, tip);
  return (my_widget_t*)it;
}
