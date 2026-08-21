/**
 * @file ztpool.c
 * @brief duanxianxia clone: 涨停股票池 (promotion ladder) table (M14c).
 *
 * Header row (40px): 进度(60) | 晋级率(85) | "涨停股票池" bold centered
 * + a red 分享图片 button on the right. Six data rows; stock items flow
 * inside the third cell (M14a flow layouter); row height adapts to the
 * flowed content via my_layouter_flow_measure. Cells carry 1px #ddd
 * borders.
 */
#include <stdio.h>
#include <string.h>

#include "myc/my_str.h"

#include "../dxx_data.h"
#include "../dxx_theme.h"
#include "myr/my_lcd_mem.h"
#include "myr/my_vgcanvas_soft.h"
#include "myui/my_layout.h"
#include "myui/widgets/my_dialog.h"
#include "myui/widgets/my_label.h"
#include <stb_image_write.h>
#include "stock_item.h"
#include "views.h"

#define ZTP_HEADER_H 40
#define ZTP_COL1_W 60
#define ZTP_COL2_W 85
#define ZTP_CELL_PAD 6

/** @brief The table widget: adds share-export state to a plain widget. */
typedef struct ztp_table_t {
  my_widget_t base;
  my_window_manager_t* wm; /**< weak */
  char share_path[160];    /**< PNG output path (M14d) */
} ztp_table_t;

typedef struct ztp_cell_t {
  my_widget_t base;
  char text[32];
  uint32_t color;
  int32_t font_size;
  bool bold;
  bool center;
} ztp_cell_t;

/** @brief Cell: right+bottom 1px #ddd borders + optional centered text. */
static void cell_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  ztp_cell_t* c = (ztp_cell_t*)widget;
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(0xDDDDDDFFu));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){(float)widget->rect.w - 1, 0, 1,
                                          (float)widget->rect.h});
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, (float)widget->rect.h - 1,
                                          (float)widget->rect.w, 1});
  if (c->text[0] != '\0') {
    int32_t tw = 0, th = 0;
    float x = 6;
    my_vgcanvas_set_font(vg, NULL, c->font_size);
    if (c->center &&
        my_vgcanvas_measure_text(vg, c->text, &tw, &th) == MY_RET_OK) {
      x = ((float)widget->rect.w - (float)tw) / 2.0f;
    } else if (c->center) {
      x = (float)widget->rect.w / 2.0f -
          (float)strlen(c->text) * 4.0f; /* rough fallback */
    }
    my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(c->color));
    my_vgcanvas_draw_text(vg, c->text, x,
                          ((float)widget->rect.h - (float)c->font_size) / 2.0f);
    if (c->bold) {
      my_vgcanvas_draw_text(vg, c->text, x + 1.0f,
                            ((float)widget->rect.h - (float)c->font_size) /
                                2.0f);
    }
  }
}

static const my_widget_vtable_t s_cell_vtable = {cell_on_paint, NULL, NULL, NULL};

static my_widget_t* cell_create(const char* text, uint32_t color,
                                int32_t font_size, bool bold, bool center) {
  ztp_cell_t* c = (ztp_cell_t*)my_mem_calloc(NULL, 1, sizeof(ztp_cell_t));
  if (c == NULL) {
    return NULL;
  }
  if (my_widget_init((my_widget_t*)c, NULL, &s_cell_vtable, "ztp_cell") !=
      MY_RET_OK) {
    my_mem_free(NULL, c);
    return NULL;
  }
  snprintf(c->text, sizeof(c->text), "%s", text != NULL ? text : "");
  c->color = color;
  c->font_size = font_size;
  c->bold = bold;
  c->center = center;
  return (my_widget_t*)c;
}

/* ---------------- 分享图片 button ---------------- */

static void share_btn_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  int32_t tw = 0, th = 0;
  /* M18b: colors via the theme (class "danger" -> dxx CSS rules);
   * fallbacks keep the site palette when no theme rule hits */
  uint32_t bg = my_widget_style_get_color(
      widget, widget->hovered ? MY_STATE_HOVER : MY_STATE_NORMAL, "bg_color",
      widget->hovered ? 0xC9302CFFu : DXX_COLOR_DANGER);
  uint32_t fg = my_widget_style_get_color(widget, MY_STATE_NORMAL,
                                          "fg_color", DXX_COLOR_WHITE);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(bg));
  my_vgcanvas_fill_rounded_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                                  (float)widget->rect.h},
                                3);
  my_vgcanvas_set_font(vg, NULL, 12);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(fg));
  if (my_vgcanvas_measure_text(vg, "分享图片", &tw, &th) != MY_RET_OK) {
    tw = 4 * 12;
  }
  my_vgcanvas_draw_text(vg, "分享图片",
                        ((float)widget->rect.w - (float)tw) / 2.0f,
                        ((float)widget->rect.h - 12.0f) / 2.0f);
}

static void share_dialog_result(void* ctx, int32_t result) {
  (void)result;
  my_dialog_destroy((my_dialog_t*)ctx);
}

/** @brief Render the table offscreen and write it as a PNG (M14d).
 * Returns the output path on success, NULL on failure. */
static const char* ztp_export_png(ztp_table_t* t, my_font_t* font,
                                  int32_t font_size) {
  my_widget_t* w = (my_widget_t*)t;
  int32_t W = w->rect.w, H = w->rect.h;
  my_lcd_t* lcd;
  my_vgcanvas_t* vg;
  uint8_t* buf;
  uint32_t stride, x, y;
  uint8_t* rgba;
  int ok;
  if (W <= 0 || H <= 0) {
    return NULL;
  }
  lcd = my_lcd_mem_create(NULL, (uint32_t)W, (uint32_t)H,
                          MY_PIXEL_FORMAT_BGRA8888);
  if (lcd == NULL) {
    return NULL;
  }
  vg = my_vgcanvas_soft_create(NULL, lcd);
  if (vg == NULL) {
    my_lcd_destroy(lcd);
    return NULL;
  }
  if (font != NULL) {
    my_vgcanvas_set_font(vg, font, font_size);
  }
  my_vgcanvas_begin_frame(vg, NULL);
  /* white backing: the table's own cells are transparent (on the page
   * the window bg shows through; offscreen we must paint it) */
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_WHITE));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)W, (float)H});
  my_vgcanvas_save(vg);
  /* paint the table as if it sat at the origin */
  my_vgcanvas_translate(vg, -(float)w->rect.x, -(float)w->rect.y);
  my_widget_paint(w, vg);
  my_vgcanvas_restore(vg);
  my_vgcanvas_end_frame(vg);
  buf = my_lcd_mem_get_buffer(lcd);
  stride = my_lcd_mem_get_stride(lcd);
  rgba = (uint8_t*)my_mem_alloc(NULL, (size_t)W * (size_t)H * 4);
  ok = 0;
  if (buf != NULL && rgba != NULL) {
    for (y = 0; y < (uint32_t)H; y++) {
      for (x = 0; x < (uint32_t)W; x++) {
        const uint8_t* p = buf + (size_t)y * stride + (size_t)x * 4;
        uint8_t* q = rgba + ((size_t)y * (size_t)W + (size_t)x) * 4;
        q[0] = p[2]; /* BGRA -> RGBA */
        q[1] = p[1];
        q[2] = p[0];
        q[3] = 255;
      }
    }
    ok = stbi_write_png(t->share_path, W, H, 4, rgba, W * 4);
  }
  my_mem_free(NULL, rgba);
  my_vgcanvas_destroy(vg);
  my_lcd_destroy(lcd);
  return ok != 0 ? t->share_path : NULL;
}

static my_ret_t share_btn_event(my_widget_t* widget, const my_event_t* event) {
  if (event->type == MY_EVENT_POINTER_DOWN) {
    return MY_RET_OK;
  }
  if (event->type == MY_EVENT_POINTER_UP) {
    /* the button's user_data is the table (set in dxx_build_ztpool) */
    ztp_table_t* t = (ztp_table_t*)my_widget_get_user_data(widget);
    my_window_manager_t* wm;
    my_dialog_t* dlg;
    my_widget_t* msg;
    my_widget_t* root;
    const char* out = NULL;
    char text[200];
    if (t == NULL || t->wm == NULL) {
      return MY_RET_OK;
    }
    wm = t->wm;
    root = widget;
    while (root->parent != NULL) {
      root = root->parent;
    }
    if (my_str_eq(root->widget_type, "window")) {
      my_window_t* rw = (my_window_t*)root;
      out = ztp_export_png(t, rw->font, rw->font_size);
    }
    dlg = my_dialog_create(NULL, wm->pal, "分享图片", 300, 120);
    if (my_str_eq(root->widget_type, "window") &&
        ((my_window_t*)root)->font != NULL) {
      my_window_set_font(dlg->win, ((my_window_t*)root)->font,
                         ((my_window_t*)root)->font_size);
    }
    snprintf(text, sizeof(text), "%s",
             out != NULL ? "已生成图片（演示环境）：" : "图片生成失败");
    msg = my_label_create(NULL, text);
    my_widget_set_layout_params(msg, "h:28");
    my_widget_add_child(my_dialog_content(dlg), msg);
    my_widget_unref(msg);
    if (out != NULL) {
      msg = my_label_create(NULL, out);
      my_widget_set_layout_params(msg, "h:28");
      my_widget_add_child(my_dialog_content(dlg), msg);
      my_widget_unref(msg);
    }
    my_dialog_add_button(dlg, "关闭", 0);
    my_dialog_open(dlg, wm, share_dialog_result, dlg);
    return MY_RET_OK;
  }
  return MY_RET_FAIL;
}

static const my_widget_vtable_t s_share_vtable = {share_btn_paint,
                                                  share_btn_event, NULL, NULL};

/* ---------------- table ---------------- */

my_widget_t* dxx_build_ztpool(my_window_manager_t* wm, my_widget_t* parent,
                              int32_t w) {
  ztp_table_t* tt =
      (ztp_table_t*)my_mem_calloc(NULL, 1, sizeof(ztp_table_t));
  my_widget_t* table;
  my_widget_t* hdr;
  my_widget_t* share;
  int32_t y;
  int r;
  if (tt == NULL ||
      my_widget_init((my_widget_t*)tt, NULL, NULL, "dxx_ztpool") !=
          MY_RET_OK) {
    my_mem_free(NULL, tt);
    return NULL;
  }
  tt->wm = wm;
  snprintf(tt->share_path, sizeof(tt->share_path), "ztpool_share.png");
  table = (my_widget_t*)tt;
  /* header row */
  hdr = my_widget_create(NULL, "ztp_header");
  my_widget_set_rect(hdr, &(my_rect_t){0, 0, w, ZTP_HEADER_H});
  my_widget_add_child(table, hdr);
  {
    my_widget_t* c1 = cell_create("进度", DXX_COLOR_TEXT, 13, false, true);
    my_widget_t* c2 = cell_create("晋级率", DXX_COLOR_TEXT, 13, false, true);
    my_widget_t* c3 =
        cell_create("涨停股票池", DXX_COLOR_TEXT, 14, true, true);
    my_widget_set_rect(c1, &(my_rect_t){0, 0, ZTP_COL1_W, ZTP_HEADER_H});
    my_widget_set_rect(c2, &(my_rect_t){ZTP_COL1_W, 0, ZTP_COL2_W, ZTP_HEADER_H});
    my_widget_set_rect(c3, &(my_rect_t){ZTP_COL1_W + ZTP_COL2_W, 0,
                                        w - ZTP_COL1_W - ZTP_COL2_W,
                                        ZTP_HEADER_H});
    my_widget_add_child(hdr, c1);
    my_widget_add_child(hdr, c2);
    my_widget_add_child(hdr, c3);
    my_widget_unref(c1);
    my_widget_unref(c2);
    my_widget_unref(c3);
  }
  share = my_widget_create(NULL, "ztp_share");
  share->vtable = &s_share_vtable;
  my_widget_set_user_data(share, tt); /* the table (has wm + share path) */
  my_widget_set_style_class(share, "danger"); /* M18b: hits the CSS rule */
  my_widget_set_rect(share, &(my_rect_t){w - 86, 7, 76, 26});
  my_widget_add_child(hdr, share);
  my_widget_unref(share);
  my_widget_unref(hdr);

  y = ZTP_HEADER_H;
  for (r = 0; r < DXX_POOL_ROW_COUNT; r++) {
    const dxx_pool_row_t* row = &DXX_POOL_ROWS[r];
    my_widget_t* roww = my_widget_create(NULL, "ztp_row");
    my_widget_t* c1 = cell_create(row->progress, DXX_COLOR_TEXT, 13, false,
                                  true);
    my_widget_t* c2 = cell_create(row->rate, DXX_COLOR_TEXT, 13, false, true);
    my_widget_t* c3 = my_widget_create(NULL, "ztp_stocks");
    int32_t flow_h;
    int32_t row_h;
    int i;
    /* stock items flow inside cell 3 */
    my_widget_set_rect(c3, &(my_rect_t){0, 0, w - ZTP_COL1_W - ZTP_COL2_W -
                                                  2 * ZTP_CELL_PAD,
                                        0});
    my_widget_set_layouter(c3, my_layouter_flow_create(NULL, 6, 4,
                                                       MY_FLOW_ALIGN_LEFT));
    for (i = 0; i < row->stock_count; i++) {
      const dxx_stock_t* s = &row->stocks[i];
      my_widget_t* it = dxx_stock_item_create(NULL, s, wm);
      char params[40];
      if (it == NULL) {
        continue;
      }
      snprintf(params, sizeof(params), "w:%d h:%d",
               (int)dxx_stock_item_width(s), DXX_STOCK_ITEM_HEIGHT);
      my_widget_set_layout_params(it, params);
      my_widget_add_child(c3, it);
      my_widget_unref(it);
    }
    flow_h = my_layouter_flow_measure(c3);
    row_h = flow_h + 2 * ZTP_CELL_PAD;
    if (row_h < ZTP_HEADER_H) {
      row_h = ZTP_HEADER_H;
    }
    my_widget_set_rect(c3, &(my_rect_t){ZTP_COL1_W + ZTP_COL2_W + ZTP_CELL_PAD,
                                        ZTP_CELL_PAD,
                                        w - ZTP_COL1_W - ZTP_COL2_W -
                                            2 * ZTP_CELL_PAD,
                                        flow_h});
    my_widget_set_rect(c1, &(my_rect_t){0, 0, ZTP_COL1_W, row_h});
    my_widget_set_rect(c2, &(my_rect_t){ZTP_COL1_W, 0, ZTP_COL2_W, row_h});
    /* c3 carries no border; draw cell border via a backing widget */
    {
      my_widget_t* c3bg = cell_create("", DXX_COLOR_TEXT, 13, false, false);
      my_widget_set_rect(c3bg, &(my_rect_t){ZTP_COL1_W + ZTP_COL2_W, 0,
                                            w - ZTP_COL1_W - ZTP_COL2_W,
                                            row_h});
      my_widget_add_child(roww, c3bg);
      my_widget_unref(c3bg);
    }
    my_widget_add_child(roww, c1);
    my_widget_add_child(roww, c2);
    my_widget_add_child(roww, c3);
    my_widget_unref(c1);
    my_widget_unref(c2);
    my_widget_unref(c3);
    my_widget_set_rect(roww, &(my_rect_t){0, y, w, row_h});
    my_widget_add_child(table, roww);
    my_widget_unref(roww);
    y += row_h;
  }
  my_widget_set_rect(table, &(my_rect_t){0, 0, w, y});
  if (parent != NULL) {
    my_widget_add_child(parent, table);
  }
  return table;
}

void dxx_ztpool_set_share_path(my_widget_t* table, const char* path) {
  ztp_table_t* tt = (ztp_table_t*)table;
  if (table != NULL && path != NULL) {
    snprintf(tt->share_path, sizeof(tt->share_path), "%s", path);
  }
}
