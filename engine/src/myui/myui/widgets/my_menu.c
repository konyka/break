/**
 * @file my_menu.c
 * @brief Popup / context menu implementation (M13c).
 *
 * Widget tree per open level: a full-window floating overlay (eats
 * outside clicks -> dismiss) with the menu box as its child; items are
 * box children. The overlay is `floating` (layouters skip it; rect set
 * absolutely) and the LAST child of the window root (hit test / paint
 * priority).
 */
#include "myui/widgets/my_menu.h"

#include <stdlib.h>
#include <string.h>

#include "myc/my_darray.h"
#include "myc/my_str.h"
#include "myui/my_layout.h"

#define MENU_MAX_DEPTH 3
#define MENU_ITEM_H 24
#define MENU_PAD 4

typedef struct menu_item_t {
  char* text;
  int32_t id;
  my_menu_t* sub; /**< child menu (owned by the PARENT model) */
} menu_item_t;

struct my_menu_t {
  const my_allocator_t* allocator;
  my_darray_t* items;        /**< menu_item_t* */
  my_menu_t* parent;         /**< weak: cascade parent */
  my_menu_t* open_sub;       /**< weak: currently open child */
  my_window_t* win;          /**< weak while open */
  my_widget_t* overlay;      /**< in the window tree while open */
  my_widget_t* box;
  my_menu_select_cb cb;
  void* cb_ctx;
  int32_t active;            /**< highlighted item index (-1 none) */
  int32_t hover_index;       /**< last hovered item index (-1 none) */
  int32_t max_depth;    /**< cascade depth limit, default 3 */
  uint32_t hover_timer; /**< pending submenu open timer id */
};

/* ---------------- item widget ---------------- */

typedef struct menu_item_widget_t {
  my_widget_t base;
  my_menu_t* menu;   /**< weak */
  menu_item_t* item; /**< weak */
  int32_t index;
} menu_item_widget_t;

static void menu_item_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  menu_item_widget_t* iw = (menu_item_widget_t*)widget;
  uint32_t fg = my_widget_style_get_color(widget, MY_STATE_NORMAL,
                                          MY_STYLE_FG_COLOR, 0x212121FFu);
  uint32_t bg = my_widget_style_get_color(
      widget, iw->index == iw->menu->active ? MY_STATE_HOVER : MY_STATE_NORMAL,
      MY_STYLE_BG_COLOR, 0xF5F5F5FFu);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(bg));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                          (float)widget->rect.h});
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(fg));
  {
    /* 13px menu font, optically centered: baseline at h/2 + 0.25*ascent
     * (the old (h-8)/2 assumed an 8px line and clipped 16px text) */
    my_font_t* f = NULL;
    int32_t ascent = 0;
    float ty;
    my_vgcanvas_set_font(vg, NULL, 13);
    my_window_font_of_widget(widget, &f, NULL);
    if (f != NULL) {
      ascent = my_font_ascent(f, 13);
    }
    ty = ascent > 0 ? (float)widget->rect.h / 2.0f - 0.75f * (float)ascent
                    : ((float)widget->rect.h - 13.0f) / 2.0f;
    my_vgcanvas_draw_text(vg, iw->item->text, 8, ty);
    if (iw->item->sub != NULL) {
      my_vgcanvas_draw_text(vg, ">", (float)widget->rect.w - 14, ty);
    }
  }
}

static void menu_close_all(my_menu_t* m) {
  while (m->parent != NULL) {
    m = m->parent;
  }
  my_menu_dismiss(m);
}

static void menu_open_sub(my_menu_t* parent, menu_item_t* item,
                          int32_t item_y);
static void menu_cancel_hover_timer(my_menu_t* m);

typedef struct hover_open_ctx_t {
  my_menu_t* menu;
  menu_item_t* item;
  int32_t item_y;
} hover_open_ctx_t;

static my_ret_t menu_hover_open_cb(void* ctx) {
  hover_open_ctx_t* h = (hover_open_ctx_t*)ctx;
  my_menu_t* m = h->menu;
  if (m != NULL && m->win != NULL && m->overlay != NULL &&
      m->open_sub != h->item->sub) {
    menu_open_sub(m, h->item, h->item_y);
  }
  if (m != NULL) {
    m->hover_timer = 0;
  }
  my_mem_free(h->menu != NULL ? h->menu->allocator : NULL, h);
  return MY_RET_FAIL; /* one-shot */
}

static my_ret_t menu_item_event(my_widget_t* widget, const my_event_t* event) {
  menu_item_widget_t* iw = (menu_item_widget_t*)widget;
  if (event->type == MY_EVENT_POINTER_DOWN) {
    iw->menu->active = iw->index;
    my_widget_invalidate(widget->parent, NULL);
    return MY_RET_OK;
  }
  if (event->type == MY_EVENT_POINTER_UP) {
    if (iw->item->sub != NULL) {
      menu_cancel_hover_timer(iw->menu);
      menu_open_sub(iw->menu, iw->item, widget->rect.y);
    } else {
      my_menu_select_cb cb = iw->menu->cb;
      void* cb_ctx = iw->menu->cb_ctx;
      int32_t id = iw->item->id;
      menu_close_all(iw->menu);
      if (cb != NULL) {
        cb(cb_ctx, id);
      }
    }
    return MY_RET_OK;
  }
  if (event->type == MY_EVENT_POINTER_MOVE) {
    if (iw->menu->active != iw->index) {
      iw->menu->active = iw->index;
      my_widget_invalidate(widget->parent, NULL);
    }
    if (iw->menu->hover_index != iw->index) {
      iw->menu->hover_index = iw->index;
      menu_cancel_hover_timer(iw->menu);
      if (iw->item->sub != NULL) {
        hover_open_ctx_t* h =
            (hover_open_ctx_t*)my_mem_calloc(iw->menu->allocator, 1,
                                              sizeof(*h));
        if (h != NULL) {
          h->menu = iw->menu;
          h->item = iw->item;
          h->item_y = widget->rect.y;
          iw->menu->hover_timer = my_pal_main_loop_add_timer(
              iw->menu->win->loop, menu_hover_open_cb, h, 120);
        }
      } else if (iw->menu->open_sub != NULL) {
        my_menu_dismiss(iw->menu->open_sub);
        iw->menu->open_sub = NULL;
      }
    }
    return MY_RET_OK;
  }
  return MY_RET_FAIL;
}

static const my_widget_vtable_t s_menu_item_vtable = {menu_item_paint,
                                                      menu_item_event, NULL, NULL};

/* ---------------- overlay / box ---------------- */

static void menu_overlay_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  (void)widget;
  (void)vg; /* fully transparent: clicks pass to children/none */
}

static void menu_box_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  uint32_t bg = my_widget_style_get_color(widget, MY_STATE_NORMAL,
                                          MY_STYLE_BG_COLOR, 0xFAFAFAFFu);
  uint32_t border = my_widget_style_get_color(widget, MY_STATE_NORMAL,
                                              MY_STYLE_BORDER_COLOR, 0x9E9E9EFFu);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(bg));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                          (float)widget->rect.h});
  my_vgcanvas_set_stroke_color(vg, my_color_from_rgba32(border));
  my_vgcanvas_set_line_width(vg, 1);
  my_vgcanvas_stroke_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                            (float)widget->rect.h});
}

static my_ret_t menu_box_event(my_widget_t* widget, const my_event_t* event) {
  if (event->type == MY_EVENT_POINTER_MOVE) {
    my_menu_t* m = (my_menu_t*)my_widget_get_user_data(widget);
    if (m != NULL && m->hover_index != -1) {
      menu_cancel_hover_timer(m);
      m->hover_index = -1;
    }
    return MY_RET_OK;
  }
  (void)event;
  return MY_RET_OK; /* clicks inside the box background are eaten */
}

static const my_widget_vtable_t s_menu_box_vtable = {menu_box_paint,
                                                     menu_box_event, NULL, NULL};

/* ---------------- popup plumbing ---------------- */

static int32_t menu_box_width(my_menu_t* m) {
  size_t i, n = my_darray_size(m->items);
  int32_t w = 80;
  for (i = 0; i < n; i++) {
    menu_item_t* it = (menu_item_t*)my_darray_get(m->items, i);
    int32_t tw;
    if (m->win != NULL && m->win->font != NULL) {
      /* real measure at the 13px menu font */
      my_font_measure(m->win->font, it->text, 13, &tw, NULL);
    } else {
      const char* p;
      tw = 0; /* codepoint-aware fallback (CJK != 1 byte) */
      for (p = it->text; *p != '\0';) {
        uint32_t cp = my_utf8_next(&p);
        tw += cp < 0x80 ? 7 : 13;
      }
    }
    tw += 28;
    if (it->sub != NULL) {
      tw += 12; /* submenu arrow */
    }
    if (tw > w) {
      w = tw;
    }
  }
  return w;
}

/** @brief Dismiss this menu's overlay only (not children). */
static void menu_close_overlay(my_menu_t* m) {
  if (m->overlay != NULL && m->win != NULL) {
    my_widget_remove_child(my_window_widget(m->win), m->overlay);
    my_widget_unref(m->overlay); /* tree held it; we drop ours */
    m->overlay = NULL;
    m->box = NULL;
    m->win = NULL;
  }
}

static void menu_cancel_hover_timer(my_menu_t* m) {
  if (m == NULL || m->hover_timer == 0) {
    return;
  }
  if (m->win != NULL && m->win->loop != NULL) {
    my_pal_main_loop_remove_timer(m->win->loop, m->hover_timer);
  }
  m->hover_timer = 0;
}

void my_menu_dismiss(my_menu_t* menu) {
  my_menu_t* parent;
  my_widget_t* parent_overlay;
  my_window_t* win;
  if (menu == NULL) {
    return;
  }
  parent = menu->parent;
  parent_overlay =
      (parent != NULL && parent->overlay != NULL) ? parent->overlay : NULL;
  win = menu->win; /* captured before menu_close_overlay clears it */
  menu_cancel_hover_timer(menu);
  menu->hover_index = -1;
  if (menu->open_sub != NULL) {
    my_menu_dismiss(menu->open_sub);
    menu->open_sub = NULL;
  }
  menu_close_overlay(menu);
  if (parent_overlay != NULL && win != NULL) {
    my_event_dispatcher_set_focus(&win->dispatcher, parent_overlay);
  }
}

my_widget_t* my_menu_widget(my_menu_t* menu) {
  return menu != NULL ? menu->overlay : NULL;
}

static my_ret_t menu_popup_at(my_menu_t* m, int32_t x, int32_t y);

static void menu_open_sub(my_menu_t* parent, menu_item_t* item,
                          int32_t item_y) {
  int32_t bx = 0;
  if (parent->open_sub == item->sub) {
    return; /* already open */
  }
  if (parent->open_sub != NULL) {
    my_menu_dismiss(parent->open_sub);
  }
  parent->open_sub = item->sub;
  if (parent->box != NULL && parent->win != NULL) {
    bx = parent->box->rect.x + parent->box->rect.w;
    item->sub->cb = parent->cb;
    item->sub->cb_ctx = parent->cb_ctx;
    item->sub->win = parent->win;
    item->sub->parent = parent;
    menu_popup_at(item->sub, bx,
                  parent->box->rect.y + item_y);
  }
}

static my_ret_t menu_key_event(my_widget_t* widget, const my_event_t* event);

/** @brief Popup overlay vtable: eats outside clicks, key nav. */
static my_ret_t menu_overlay_on_event(my_widget_t* widget,
                                      const my_event_t* event) {
  my_menu_t* m;
  if (widget == NULL || widget->parent == NULL) {
    return MY_RET_FAIL;
  }
  /* the menu pointer is stored on the box child (set at popup) */
  m = NULL;
  if (my_widget_child_count(widget) > 0) {
    my_widget_t* box = my_widget_get_child(widget, 0);
    m = (my_menu_t*)my_widget_get_user_data(box);
  }
  if (m == NULL) {
    return MY_RET_FAIL;
  }
  if (event->type == MY_EVENT_POINTER_DOWN) {
    my_menu_dismiss(m); /* clicked outside the box */
    return MY_RET_OK;
  }
  if (event->type == MY_EVENT_KEY_DOWN) {
    return menu_key_event(widget, event);
  }
  if (event->type == MY_EVENT_POINTER_MOVE) {
    /* The overlay is full-window; the box is the interactive region. If the
     * cursor leaves the box, dismiss this submenu so the parent menu can
     * receive hover events over its own items. */
    my_widget_t* box = NULL;
    if (my_widget_child_count(widget) > 0) {
      box = my_widget_get_child(widget, 0);
    }
    if (box != NULL) {
      int32_t px = event->u.pointer.x;
      int32_t py = event->u.pointer.y;
      if (px < box->rect.x || px >= box->rect.x + box->rect.w ||
          py < box->rect.y || py >= box->rect.y + box->rect.h) {
        my_menu_dismiss(m);
        return MY_RET_FAIL;
      }
    }
    return MY_RET_OK;
  }
  return MY_RET_OK; /* swallow everything else while open */
}

static const my_widget_vtable_t s_menu_overlay_vtable = {
    menu_overlay_paint, menu_overlay_on_event, NULL, NULL};

static my_ret_t menu_key_event(my_widget_t* widget, const my_event_t* event) {
  my_widget_t* box = my_widget_get_child(widget, 0);
  my_menu_t* m = (my_menu_t*)my_widget_get_user_data(box);
  size_t n = my_darray_size(m->items);
  switch (event->u.key.key) {
    case MY_KEY_DOWN:
      m->active = m->active + 1 < (int32_t)n ? m->active + 1 : 0;
      my_widget_invalidate(box, NULL);
      return MY_RET_OK;
    case MY_KEY_UP:
      m->active = m->active > 0 ? m->active - 1 : (int32_t)n - 1;
      my_widget_invalidate(box, NULL);
      return MY_RET_OK;
    case MY_KEY_RETURN:
      if (m->active >= 0 && m->active < (int32_t)n) {
        menu_item_t* it =
            (menu_item_t*)my_darray_get(m->items, (size_t)m->active);
        if (it->sub != NULL) {
          menu_open_sub(m, it, m->active * MENU_ITEM_H);
        } else {
          my_menu_select_cb cb = m->cb;
          void* cb_ctx = m->cb_ctx;
          menu_close_all(m);
          if (cb != NULL) {
            cb(cb_ctx, it->id);
          }
        }
      }
      return MY_RET_OK;
    case MY_KEY_ESCAPE:
      my_menu_dismiss(m);
      return MY_RET_OK;
    default:
      return MY_RET_OK;
  }
}

static my_ret_t menu_popup_at(my_menu_t* m, int32_t x, int32_t y) {
  my_widget_t* root;
  my_widget_t* ov;
  my_widget_t* box;
  size_t i, n;
  int32_t bw, bh;
  if (m->win == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  root = my_window_widget(m->win);
  n = my_darray_size(m->items);
  if (n == 0) {
    return MY_RET_FAIL;
  }
  bw = menu_box_width(m);
  bh = (int32_t)n * MENU_ITEM_H + 2 * MENU_PAD;
  /* edge flip: keep the box inside the window */
  if (x + bw > root->rect.w) {
    x = root->rect.w - bw;
  }
  if (y + bh > root->rect.h) {
    y = root->rect.h - bh;
  }
  if (x < 0) {
    x = 0;
  }
  if (y < 0) {
    y = 0;
  }

  ov = my_widget_create(m->allocator, "menu_overlay");
  box = my_widget_create(m->allocator, "menu_box");
  if (ov == NULL || box == NULL) {
    if (ov != NULL) {
      my_widget_unref(ov);
    }
    if (box != NULL) {
      my_widget_unref(box);
    }
    return MY_RET_OOM;
  }
  my_widget_subclass_init(ov, &s_menu_overlay_vtable);
  ov->floating = true;
  ov->focusable = true;
  my_widget_set_rect(ov, &(my_rect_t){0, 0, root->rect.w, root->rect.h});
  my_widget_subclass_init(box, &s_menu_box_vtable);
  my_widget_set_rect(box, &(my_rect_t){x, y, bw, bh});
  my_widget_set_user_data(box, m);

  for (i = 0; i < n; i++) {
    menu_item_t* it = (menu_item_t*)my_darray_get(m->items, i);
    menu_item_widget_t* iw = (menu_item_widget_t*)my_mem_calloc(
        m->allocator, 1, sizeof(menu_item_widget_t));
    if (iw == NULL) {
      continue;
    }
    if (my_widget_init((my_widget_t*)iw, m->allocator, &s_menu_item_vtable,
                       "menu_item") != MY_RET_OK) {
      my_mem_free(m->allocator, iw);
      continue;
    }
    iw->menu = m;
    iw->item = it;
    iw->index = (int32_t)i;
    my_widget_set_rect((my_widget_t*)iw,
                       &(my_rect_t){0, MENU_PAD + (int32_t)i * MENU_ITEM_H,
                                    bw, MENU_ITEM_H});
    my_widget_add_child(box, (my_widget_t*)iw);
    my_widget_unref((my_widget_t*)iw);
  }
  my_widget_add_child(ov, box);
  my_widget_unref(box);
  my_widget_add_child(root, ov); /* last child = on top */
  m->overlay = ov;
  m->box = box;
  m->active = -1;
  my_event_dispatcher_set_focus(&m->win->dispatcher, ov);
  my_widget_invalidate(root, NULL);
  return MY_RET_OK;
}

my_ret_t my_menu_popup(my_window_t* win, my_menu_t* menu, int32_t x,
                       int32_t y, my_menu_select_cb cb, void* ctx) {
  if (win == NULL || menu == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (menu->overlay != NULL) {
    my_menu_dismiss(menu);
  }
  menu->win = win;
  menu->cb = cb;
  menu->cb_ctx = ctx;
  return menu_popup_at(menu, x, y);
}

/* ---------------- model ---------------- */

my_menu_t* my_menu_create(const my_allocator_t* allocator) {
  my_menu_t* m = (my_menu_t*)my_mem_calloc(allocator, 1, sizeof(my_menu_t));
  if (m == NULL) {
    return NULL;
  }
  m->allocator = allocator;
  m->items = my_darray_create(allocator, 0);
  m->active = -1;
  m->hover_index = -1;
  m->max_depth = MENU_MAX_DEPTH;
  if (m->items == NULL) {
    my_mem_free(allocator, m);
    return NULL;
  }
  return m;
}

void my_menu_set_max_depth(my_menu_t* menu, int32_t depth) {
  if (menu == NULL) {
    return;
  }
  menu->max_depth = depth < 1 ? 1 : depth;
}

int32_t my_menu_max_depth(const my_menu_t* menu) {
  return menu != NULL ? menu->max_depth : MENU_MAX_DEPTH;
}

void my_menu_destroy(my_menu_t* menu) {
  size_t i, n;
  if (menu == NULL) {
    return;
  }
  my_menu_dismiss(menu);
  n = my_darray_size(menu->items);
  for (i = 0; i < n; i++) {
    menu_item_t* it = (menu_item_t*)my_darray_get(menu->items, i);
    if (it->sub != NULL) {
      my_menu_destroy(it->sub);
    }
    my_mem_free(menu->allocator, it->text);
    my_mem_free(menu->allocator, it);
  }
  my_darray_destroy(menu->items);
  my_mem_free(menu->allocator, menu);
}

my_ret_t my_menu_add_item(my_menu_t* menu, const char* text, int32_t id) {
  menu_item_t* it;
  if (menu == NULL || text == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  it = (menu_item_t*)my_mem_calloc(menu->allocator, 1, sizeof(menu_item_t));
  if (it == NULL) {
    return MY_RET_OOM;
  }
  it->text = my_strdup(menu->allocator, text);
  it->id = id;
  if (it->text == NULL || my_darray_push(menu->items, it) != MY_RET_OK) {
    my_mem_free(menu->allocator, it->text);
    my_mem_free(menu->allocator, it);
    return MY_RET_OOM;
  }
  return MY_RET_OK;
}

my_menu_t* my_menu_add_submenu(my_menu_t* menu, const char* text) {
  menu_item_t* it;
  my_menu_t* sub;
  size_t depth = 1;
  my_menu_t* p;
  int32_t max_depth;
  if (menu == NULL || text == NULL) {
    return NULL;
  }
  max_depth = my_menu_max_depth(menu);
  for (p = menu->parent; p != NULL; p = p->parent) {
    depth++;
  }
  if ((int32_t)depth >= max_depth) {
    return NULL; /* cascade depth cap (documented) */
  }
  sub = my_menu_create(menu->allocator);
  if (sub == NULL) {
    return NULL;
  }
  sub->parent = menu;
  sub->max_depth = max_depth; /* inherit depth limit from parent */
  it = (menu_item_t*)my_mem_calloc(menu->allocator, 1, sizeof(menu_item_t));
  if (it == NULL) {
    my_menu_destroy(sub);
    return NULL;
  }
  it->text = my_strdup(menu->allocator, text);
  it->sub = sub;
  if (it->text == NULL || my_darray_push(menu->items, it) != MY_RET_OK) {
    my_mem_free(menu->allocator, it->text);
    my_mem_free(menu->allocator, it);
    my_menu_destroy(sub);
    return NULL;
  }
  return sub;
}
