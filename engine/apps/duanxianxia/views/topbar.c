/**
 * @file topbar.c
 * @brief duanxianxia clone: the 50px #444 topbar (M14b).
 *
 * Layout (from the site's index.html): logo text + 4 dropdown groups
 * (竞价/挖掘/复盘/热点) + flat items (语音快讯/看盘插件 orange/涨停表现/
 * 龙虎榜/PC端版面 yellow bold/联系客服), 1px #666 dividers between
 * items, and 注册 / 登录 on the right. Dropdowns open my_menu popups;
 * item selection only logs for now (navigation is M14d).
 */
#include <stdio.h>
#include <string.h>

#include "../dxx_theme.h"
#include "nav_item.h"
#include "views.h"

#define TOPBAR_H DXX_TOPBAR_H
#define NAV_FONT 14

typedef struct topbar_paint_t {
  my_widget_t base;
} topbar_paint_t;

static void topbar_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_TOPBAR));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                          (float)widget->rect.h});
}

/** @brief 1px vertical divider (#666), vertically centered. */
static void divider_on_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  float y = ((float)widget->rect.h - 20.0f) / 2.0f;
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(DXX_COLOR_NAV_DIV));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, y, 1, 20});
}

static const my_widget_vtable_t s_topbar_vtable = {topbar_on_paint, NULL,
                                                   NULL, NULL};
static const my_widget_vtable_t s_divider_vtable = {divider_on_paint, NULL,
                                                    NULL, NULL};

static const char* const MENU_JINGJIA[] = {"竞价异动", "竞价强度"};
static const char* const MENU_WAJUE[] = {"个股挖掘", "概念检索", "研报检索"};
static const char* const MENU_FUPAN[] = {"每日复盘", "板块轮动", "龙头高度",
                                         "连板天梯"};
static const char* const MENU_REDIAN[] = {"热点聚焦", "聚合热搜"};

static const char* const* MENU_NAMES[DXX_MENU_COUNT] = {
    MENU_JINGJIA, MENU_WAJUE, MENU_FUPAN, MENU_REDIAN};
static const int MENU_COUNTS[DXX_MENU_COUNT] = {2, 3, 4, 2};

static void on_menu_select(void* ctx, int32_t id) {
  struct dxx_trigger_t* tr = (struct dxx_trigger_t*)ctx;
  const char* name = "?";
  if (tr->menu_index >= 0 && id >= 0 && id < MENU_COUNTS[tr->menu_index]) {
    name = MENU_NAMES[tr->menu_index][id];
  }
  if (tr->tb->nav_cb != NULL) {
    tr->tb->nav_cb(tr->tb->nav_ctx, name);
  }
  dxx_topbar_set_active(tr->tb, name);
}

static void on_trigger_click(void* ctx, const char* event, void* data) {
  struct dxx_trigger_t* tr = (struct dxx_trigger_t*)ctx;
  int32_t x = 0, y;
  (void)event;
  (void)data;
  if (tr->menu_index < 0) {
    if (tr->tb->nav_cb != NULL) {
      tr->tb->nav_cb(tr->tb->nav_ctx, tr->log_name);
    }
    dxx_topbar_set_active(tr->tb, tr->log_name);
    return;
  }
  y = tr->anchor->rect.h;
  my_widget_local_to_global(tr->anchor, &x, &y);
  my_menu_popup(tr->win, tr->tb->menus[tr->menu_index], x, y, on_menu_select,
                tr);
}

static my_menu_t* build_menu(const char* const* items, int count) {
  my_menu_t* m = my_menu_create(NULL);
  int i;
  for (i = 0; i < count; i++) {
    my_menu_add_item(m, items[i], i);
  }
  return m;
}

static const char* const DROPDOWN_NAMES[DXX_MENU_COUNT] = {"竞价▼", "挖掘▼",
                                                           "复盘▼", "热点▼"};

void dxx_topbar_set_nav_handler(dxx_topbar_t* tb, dxx_nav_cb cb, void* ctx) {
  if (tb != NULL) {
    tb->nav_cb = cb;
    tb->nav_ctx = ctx;
  }
}

void dxx_topbar_set_active(dxx_topbar_t* tb, const char* name) {
  int i, j;
  if (tb == NULL || name == NULL) {
    return;
  }
  for (i = 0; i < 16; i++) {
    struct dxx_trigger_t* tr = &tb->triggers[i];
    bool active = false;
    if (tr->anchor == NULL) {
      break;
    }
    if (tr->menu_index < 0) {
      active = tr->log_name != NULL && strcmp(tr->log_name, name) == 0;
    } else {
      for (j = 0; j < MENU_COUNTS[tr->menu_index]; j++) {
        if (strcmp(MENU_NAMES[tr->menu_index][j], name) == 0) {
          active = true;
          break;
        }
      }
    }
    dxx_nav_item_set_color(tr->anchor,
                           active ? DXX_COLOR_PRIMARY : tr->base_color);
  }
}

static int add_item(dxx_topbar_t* tb, my_window_t* win, int x, int y,
                    const char* text, uint32_t color, bool bold,
                    int menu_index) {
  my_widget_t* it = dxx_nav_item_create(NULL, text, color, bold, NAV_FONT,
                                        DXX_COLOR_NAV_HOVER);
  int w = dxx_text_estimate(text, NAV_FONT) + 2 * 8;
  struct dxx_trigger_t* tr;
  int idx = 0;
  my_widget_set_rect(it, &(my_rect_t){x, y, w, TOPBAR_H - 14});
  my_widget_add_child(tb->bar, it);
  /* find a free trigger slot */
  while (idx < 16 && tb->triggers[idx].anchor != NULL) {
    idx++;
  }
  if (idx < 16) {
    tr = &tb->triggers[idx];
    tr->win = win;
    tr->tb = tb;
    tr->menu_index = menu_index;
    tr->anchor = it;
    tr->log_name = text;
    tr->base_color = color;
    my_widget_on(it, "click", on_trigger_click, tr);
  }
  my_widget_unref(it);
  return x + w;
}

static int add_divider(dxx_topbar_t* tb, int x, int y) {
  my_widget_t* d = my_widget_create(NULL, "nav_divider");
  d->vtable = &s_divider_vtable;
  my_widget_set_rect(d, &(my_rect_t){x, y, 1, TOPBAR_H - 14});
  my_widget_add_child(tb->bar, d);
  my_widget_unref(d);
  return x + 1;
}

void dxx_build_topbar(my_window_t* win, my_widget_t* parent,
                      dxx_topbar_t* out) {
  int x = 10;
  int y = 7;
  int i;
  static const struct {
    const char* text;
    uint32_t color;
    bool bold;
  } FLATS[] = {
      {"语音快讯", 0xFFFFFFFFu, false}, {"看盘插件", 0xFFA500FFu, false},
      {"涨停表现", 0xFFFFFFFFu, false}, {"龙虎榜", 0xFFFFFFFFu, false},
      {"PC端版面", 0xFFFF00FFu, true},  {"联系客服", 0xFFFFFFFFu, false},
  };
  memset(out, 0, sizeof(*out));
  out->bar = my_widget_create(NULL, "dxx_topbar");
  out->bar->vtable = &s_topbar_vtable;
  my_widget_set_rect(out->bar,
                     &(my_rect_t){0, 0, parent->rect.w, TOPBAR_H});
  my_widget_add_child(parent, out->bar);

  out->menus[0] = build_menu(MENU_JINGJIA, 2);
  out->menus[1] = build_menu(MENU_WAJUE, 3);
  out->menus[2] = build_menu(MENU_FUPAN, 4);
  out->menus[3] = build_menu(MENU_REDIAN, 2);

  /* logo (site uses a 150px image; text stand-in, see docs) — click
   * returns to the home page */
  {
    my_widget_t* logo = dxx_nav_item_create(NULL, "短线侠", DXX_COLOR_WHITE,
                                            true, 20, 0);
    struct dxx_trigger_t* tr = &out->triggers[0];
    my_widget_set_rect(logo, &(my_rect_t){x, 0, 120, TOPBAR_H});
    my_widget_add_child(out->bar, logo);
    tr->win = win;
    tr->tb = out;
    tr->menu_index = -1;
    tr->anchor = logo;
    tr->log_name = "首页";
    tr->base_color = DXX_COLOR_WHITE;
    my_widget_on(logo, "click", on_trigger_click, tr);
    my_widget_unref(logo);
    x += 120 + 10;
  }
  for (i = 0; i < DXX_MENU_COUNT; i++) {
    x = add_item(out, win, x, y, DROPDOWN_NAMES[i], DXX_COLOR_WHITE, false, i);
    x = add_divider(out, x + 4, y) + 4;
  }
  for (i = 0; i < 6; i++) {
    x = add_item(out, win, x, y, FLATS[i].text, FLATS[i].color, FLATS[i].bold,
                 -1);
    if (i < 5) {
      x = add_divider(out, x + 4, y) + 4;
    }
  }
  /* right side: 注册 / 登录 */
  {
    int rx = parent->rect.w - 10 - 90;
    add_item(out, win, rx, y, "注册", DXX_COLOR_WHITE, false, -1);
    add_item(out, win, rx + 45, y, "登录", DXX_COLOR_WHITE, false, -1);
  }
}

void dxx_topbar_destroy(dxx_topbar_t* tb) {
  int i;
  if (tb == NULL) {
    return;
  }
  for (i = 0; i < DXX_MENU_COUNT; i++) {
    my_menu_destroy(tb->menus[i]);
    tb->menus[i] = NULL;
  }
}
