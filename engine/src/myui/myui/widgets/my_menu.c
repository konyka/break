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
#include "myui/my_window_manager.h"

#define MENU_MAX_DEPTH 3
#define MENU_ITEM_H 24
#define MENU_PAD 4

typedef struct menu_item_t {
  char* text;
  int32_t id;
  my_menu_t* sub; /**< child menu (owned by the PARENT model) */
} menu_item_t;

typedef struct hover_open_ctx_t hover_open_ctx_t;

static my_menu_t* menu_root(my_menu_t* menu);

typedef struct menu_callback_state_t {
  const my_allocator_t* allocator;
  my_menu_select_cb callback;
  my_menu_context_destroy_fn destroy_ctx;
  void* context;
  my_emitter_context_lease_t* lease;
} menu_callback_state_t;

struct my_menu_t {
  const my_allocator_t* allocator;
  my_darray_t* items;        /**< menu_item_t* */
  my_menu_t* parent;         /**< weak: cascade parent */
  my_menu_t* open_sub;       /**< weak: currently open child */
  my_window_t* win;          /**< weak while open */
  my_window_manager_t* wm;   /**< weak while open */
  uint32_t wm_destroy_listener_id;
  uint32_t window_close_listener_id;
  my_widget_t* overlay;      /**< weak: owned by the window tree while open */
  my_widget_t* box;
  my_menu_select_cb cb;
  void* cb_ctx;
  menu_callback_state_t* callback_state;
  int32_t active;            /**< highlighted item index (-1 none) */
  int32_t hover_index;       /**< last hovered item index (-1 none) */
  int32_t max_depth;    /**< cascade depth limit, default 3 */
  uint32_t hover_timer; /**< pending submenu open timer id */
  hover_open_ctx_t* hover_ctx; /**< owned: pending hover timer ctx (freed on
                                    fire by the callback, on cancel by
                                    menu_cancel_hover_timer) */
  uint32_t operation_depth;
  bool destroy_requested;
  bool destroying;
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

static void menu_destroy_internal(my_menu_t* menu);
static void menu_destroy_now(my_menu_t* menu);

static void menu_open_sub(my_menu_t* parent, menu_item_t* item,
                          int32_t item_y);
static void menu_cancel_hover_timer(my_menu_t* m);

static void menu_operation_end(my_menu_t* menu);

static void menu_operation_begin(my_menu_t* menu) {
  if (menu != NULL) {
    menu->operation_depth++;
  }
}

static void menu_operation_end(my_menu_t* menu) {
  if (menu == NULL || menu->operation_depth == 0) {
    return;
  }
  menu->operation_depth--;
  if (menu->operation_depth == 0 && menu->destroy_requested &&
      !menu->destroying) {
    menu->destroy_requested = false;
    menu_destroy_now(menu);
  }
}

static my_menu_t* menu_root(my_menu_t* menu) {
  while (menu != NULL && menu->parent != NULL) {
    menu = menu->parent;
  }
  return menu;
}

static void menu_callback_state_destroy(menu_callback_state_t* state) {
  if (state == NULL) {
    return;
  }
  if (state->destroy_ctx != NULL) {
    state->destroy_ctx(state->context);
  }
  my_emitter_context_lease_unref(state->lease);
  my_mem_free(state->allocator, state);
}

static menu_callback_state_t* menu_callback_state_detach(my_menu_t* menu) {
  my_menu_t* root = menu_root(menu);
  menu_callback_state_t* state;
  if (root == NULL) {
    return NULL;
  }
  state = root->callback_state;
  root->callback_state = NULL;
  root->cb = NULL;
  root->cb_ctx = NULL;
  return state;
}

static void menu_dispatch_selection(my_menu_t* menu, int32_t id) {
  my_menu_select_cb cb;
  void* context;
  menu_callback_state_t* state;

  if (menu == NULL) {
    return;
  }
  cb = menu->cb;
  context = menu->cb_ctx;
  state = menu_callback_state_detach(menu);
  if (state != NULL) {
    cb = state->callback;
    context = state->context;
    if (state->lease != NULL) {
      if (!my_emitter_context_lease_is_valid(state->lease)) {
        cb = NULL;
      } else {
        context = my_emitter_context_lease_context(state->lease);
      }
    }
  }
  menu_close_all(menu);
  if (cb != NULL) {
    cb(context, id);
  }
  menu_callback_state_destroy(state);
}

static void menu_on_window_close(void* ctx) {
  my_menu_t* m = (my_menu_t*)ctx;
  if (m == NULL) {
    return;
  }
  m->window_close_listener_id = 0;
  if (m->overlay != NULL) {
    my_menu_dismiss(m);
  } else {
    menu_cancel_hover_timer(m);
    m->win = NULL;
    m->wm = NULL;
  }
}

static void menu_on_manager_destroy(void* ctx) {
  my_menu_t* m = (my_menu_t*)ctx;
  if (m == NULL) {
    return;
  }
  if (m->overlay != NULL) {
    my_menu_dismiss(m);
  }
  m->wm = NULL;
  m->wm_destroy_listener_id = 0;
}

struct hover_open_ctx_t {
  my_menu_t* menu;
  menu_item_t* item;
  int32_t item_y;
};

static my_ret_t menu_hover_open_cb(void* ctx) {
  hover_open_ctx_t* h = (hover_open_ctx_t*)ctx;
  my_menu_t* m = h->menu;
  if (m != NULL && m->win != NULL && m->overlay != NULL &&
      m->open_sub != h->item->sub) {
    menu_open_sub(m, h->item, h->item_y);
  }
  if (m != NULL) {
    m->hover_timer = 0;
    m->hover_ctx = NULL; /* ownership returns here; freed just below */
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
      int32_t id = iw->item->id;
      menu_dispatch_selection(iw->menu, id);
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
          if (iw->menu->win != NULL && iw->menu->win->loop != NULL) {
            iw->menu->hover_timer = my_pal_main_loop_add_timer(
                iw->menu->win->loop, menu_hover_open_cb, h, 120);
          }
          if (iw->menu->hover_timer != 0) {
            iw->menu->hover_ctx = h; /* timer owns it until fire/cancel */
          } else {
            my_mem_free(iw->menu->allocator, h); /* no loop / arm failed */
          }
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
    int64_t tw64;
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
    tw64 = (int64_t)tw + 28;
    if (it->sub != NULL) {
      tw64 += 12; /* submenu arrow */
    }
    tw = tw64 > INT32_MAX ? INT32_MAX : tw64 < 0 ? 0 : (int32_t)tw64;
    if (tw > w) {
      w = tw;
    }
  }
  return w;
}

/** @brief Dismiss this menu's overlay only (not children). */
static void menu_close_overlay(my_menu_t* m) {
  my_window_t* win = m != NULL ? m->win : NULL;
  if (m->overlay != NULL && m->win != NULL) {
    /* the tree owns the only overlay ref: removal destroys it, and its
     * destroy chain clears m->overlay/box/win (kept below for clarity) */
    my_widget_remove_child(my_window_widget(m->win), m->overlay);
    m->overlay = NULL;
    m->box = NULL;
  }
  if (win != NULL && m->window_close_listener_id != 0) {
    (void)my_window_remove_close_listener(win, m->window_close_listener_id);
    m->window_close_listener_id = 0;
  }
  m->win = NULL;
  if (m->wm != NULL && m->wm_destroy_listener_id != 0) {
    (void)my_window_manager_remove_destroy_listener(
        m->wm, m->wm_destroy_listener_id);
    m->wm_destroy_listener_id = 0;
  }
  m->wm = NULL;
}

static void menu_cancel_hover_timer(my_menu_t* m) {
  if (m == NULL || m->hover_timer == 0) {
    return;
  }
  if (m->win != NULL && m->win->loop != NULL) {
    my_pal_main_loop_remove_timer(m->win->loop, m->hover_timer);
  }
  m->hover_timer = 0;
  /* The one-shot callback frees the ctx when it FIRES; a cancelled timer
   * never runs, so the pending ctx is freed here instead. */
  if (m->hover_ctx != NULL) {
    my_mem_free(m->allocator, m->hover_ctx);
    m->hover_ctx = NULL;
  }
}

/** @brief Overlay destroy chain: window teardown destroys the overlay in
 * place (my_widget_destroy unrefs children directly — no remove_child, so
 * the model is never dismissed). Drop the model's weak refs and cancel the
 * pending hover timer while win->loop is still valid, otherwise the model
 * keeps dangling win/overlay/box pointers and the shared main loop keeps a
 * timer whose ctx dereferences the freed window. */
static void menu_overlay_destroy_chain(my_object_t* obj) {
  my_widget_t* ov = (my_widget_t*)obj;
  my_menu_t* m = NULL;
  menu_callback_state_t* callback_state = NULL;
  if (my_widget_child_count(ov) > 0) {
    m = (my_menu_t*)my_widget_get_user_data(my_widget_get_child(ov, 0));
  }
  if (m != NULL && m->overlay == ov) {
    menu_operation_begin(m);
    menu_cancel_hover_timer(m);
    if (m->win != NULL && m->window_close_listener_id != 0) {
      (void)my_window_remove_close_listener(m->win,
                                            m->window_close_listener_id);
      m->window_close_listener_id = 0;
    }
    if (m->wm != NULL && m->wm_destroy_listener_id != 0) {
      (void)my_window_manager_remove_destroy_listener(
          m->wm, m->wm_destroy_listener_id);
      m->wm_destroy_listener_id = 0;
    }
    m->window_close_listener_id = 0;
    m->overlay = NULL;
    m->box = NULL;
    m->win = NULL;
    m->wm = NULL;
    if (menu_root(m) == m) {
      callback_state = menu_callback_state_detach(m);
    }
    menu_callback_state_destroy(callback_state);
    menu_operation_end(m);
  }
  my_widget_destroy(ov);
  my_object_destroy(obj);
}

void my_menu_dismiss(my_menu_t* menu) {
  my_menu_t* parent;
  my_widget_t* parent_overlay;
  my_window_t* win;
  if (menu == NULL) {
    return;
  }
  menu_operation_begin(menu);
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
  menu_operation_end(menu);
}

my_widget_t* my_menu_widget(my_menu_t* menu) {
  return menu != NULL ? menu->overlay : NULL;
}

static my_ret_t menu_popup_at(my_menu_t* m, int32_t x, int32_t y);

static void menu_open_sub(my_menu_t* parent, menu_item_t* item,
                          int32_t item_y) {
  int32_t bx = 0;
  int32_t by;
  if (parent->open_sub == item->sub) {
    return; /* already open */
  }
  if (parent->open_sub != NULL) {
    my_menu_dismiss(parent->open_sub);
  }
  parent->open_sub = item->sub;
  if (parent->box != NULL && parent->win != NULL) {
    bx = my_rect_offset_i32(parent->box->rect.x, parent->box->rect.w);
    by = my_rect_offset_i32(parent->box->rect.y, item_y);
    item->sub->cb = parent->cb;
    item->sub->cb_ctx = parent->cb_ctx;
    item->sub->callback_state = parent->callback_state;
    item->sub->win = parent->win;
    item->sub->wm = parent->wm;
    item->sub->parent = parent;
    menu_popup_at(item->sub, bx, by);
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
      if (!my_rect_contains(&box->rect, px, py)) {
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
          menu_dispatch_selection(m, it->id);
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
  int64_t bh64;
  int64_t x64, y64;
  if (m->win == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  root = my_window_widget(m->win);
  n = my_darray_size(m->items);
  if (n == 0) {
    return MY_RET_FAIL;
  }
  bw = menu_box_width(m);
  bh64 = (int64_t)n * MENU_ITEM_H + 2 * MENU_PAD;
  bh = bh64 > INT32_MAX ? INT32_MAX : (int32_t)bh64;
  /* edge flip: keep the box inside the window */
  x64 = x;
  y64 = y;
  if (x64 + bw > root->rect.w) {
    x64 = (int64_t)root->rect.w - bw;
  }
  if (y64 + bh > root->rect.h) {
    y64 = (int64_t)root->rect.h - bh;
  }
  if (x64 < 0) {
    x64 = 0;
  }
  if (y64 < 0) {
    y64 = 0;
  }
  x = x64 > INT32_MAX ? INT32_MAX : (int32_t)x64;
  y = y64 > INT32_MAX ? INT32_MAX : (int32_t)y64;

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
  /* so the model is invalidated even when the window is torn down with the
   * popup still open (no dismiss path runs in that case) */
  ((my_object_t*)ov)->destroy = menu_overlay_destroy_chain;
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
  if (my_widget_add_child(ov, box) != MY_RET_OK) {
    my_widget_unref(box); /* still ours: add_child kept no ref on failure */
    my_widget_unref(ov);
    return MY_RET_OOM;
  }
  my_widget_unref(box);
  if (my_widget_add_child(root, ov) != MY_RET_OK) { /* last child = on top */
    my_widget_unref(ov); /* destroys overlay + box; model never sees them */
    return MY_RET_OOM;
  }
  my_widget_unref(ov); /* tree owns the only ref; m->overlay stays weak, so
                        * window teardown destroys the overlay and its
                        * destroy chain invalidates the model */
  m->overlay = ov;
  m->box = box;
  m->window_close_listener_id = my_window_add_close_listener(
      m->win, menu_on_window_close, m);
  if (m->window_close_listener_id == 0) {
    my_menu_dismiss(m);
    return MY_RET_OOM;
  }
  m->active = -1;
  my_event_dispatcher_set_focus(&m->win->dispatcher, ov);
  my_widget_invalidate(root, NULL);
  return MY_RET_OK;
}

static my_ret_t menu_popup_with_callback(
    my_window_t* win, my_menu_t* menu, int32_t x, int32_t y,
    my_menu_select_cb cb, void* ctx, my_menu_context_destroy_fn destroy_ctx,
    my_emitter_context_lease_t* lease) {
  menu_callback_state_t* callback_state = NULL;
  if (win == NULL || menu == NULL ||
      (lease != NULL && !my_emitter_context_lease_is_valid(lease))) {
    return MY_RET_INVALID_PARAMS;
  }
  if (menu->overlay != NULL) {
    my_menu_dismiss(menu);
  }
  menu->win = win;
  menu->wm = win->wm;
  if (menu->wm != NULL) {
    menu->wm_destroy_listener_id = my_window_manager_add_destroy_listener(
        menu->wm, menu_on_manager_destroy, menu);
    if (menu->wm_destroy_listener_id == 0) {
      menu->win = NULL;
      menu->wm = NULL;
      return MY_RET_OOM;
    }
  }
  if (destroy_ctx != NULL || lease != NULL) {
    callback_state = (menu_callback_state_t*)my_mem_calloc(
        menu->allocator, 1u, sizeof(*callback_state));
    if (callback_state == NULL) {
      if (menu->wm != NULL && menu->wm_destroy_listener_id != 0) {
        (void)my_window_manager_remove_destroy_listener(
            menu->wm, menu->wm_destroy_listener_id);
      }
      menu->wm_destroy_listener_id = 0;
      menu->win = NULL;
      menu->wm = NULL;
      return MY_RET_OOM;
    }
    callback_state->allocator = menu->allocator;
    callback_state->callback = cb;
    callback_state->destroy_ctx = destroy_ctx;
    callback_state->context = ctx;
    callback_state->lease = my_emitter_context_lease_ref(lease);
    if (lease != NULL && callback_state->lease == NULL) {
      my_mem_free(menu->allocator, callback_state);
      if (menu->wm != NULL && menu->wm_destroy_listener_id != 0) {
        (void)my_window_manager_remove_destroy_listener(
            menu->wm, menu->wm_destroy_listener_id);
      }
      menu->wm_destroy_listener_id = 0;
      menu->win = NULL;
      menu->wm = NULL;
      return MY_RET_OOM;
    }
  }
  menu->callback_state = callback_state;
  menu->cb = cb;
  menu->cb_ctx = ctx;
  {
    my_ret_t ret = menu_popup_at(menu, x, y);
    if (ret != MY_RET_OK) {
      if (menu->wm != NULL && menu->wm_destroy_listener_id != 0) {
        (void)my_window_manager_remove_destroy_listener(
            menu->wm, menu->wm_destroy_listener_id);
      }
      menu->wm_destroy_listener_id = 0;
      menu->win = NULL;
      menu->wm = NULL;
      menu_callback_state_destroy(menu_callback_state_detach(menu));
    }
    return ret;
  }
}

my_ret_t my_menu_popup(my_window_t* win, my_menu_t* menu, int32_t x,
                       int32_t y, my_menu_select_cb cb, void* ctx) {
  return menu_popup_with_callback(win, menu, x, y, cb, ctx, NULL, NULL);
}

my_ret_t my_menu_popup_owned(my_window_t* win, my_menu_t* menu, int32_t x,
                             int32_t y, my_menu_select_cb cb, void* ctx,
                             my_menu_context_destroy_fn destroy_ctx) {
  return menu_popup_with_callback(win, menu, x, y, cb, ctx, destroy_ctx, NULL);
}

my_ret_t my_menu_popup_lease(my_window_t* win, my_menu_t* menu, int32_t x,
                             int32_t y, my_menu_select_cb cb,
                             my_emitter_context_lease_t* lease) {
  if (lease == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  return menu_popup_with_callback(win, menu, x, y, cb,
                                  my_emitter_context_lease_context(lease),
                                  NULL, lease);
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

static void menu_destroy_internal(my_menu_t* menu) {
  size_t i, n;
  if (menu == NULL) {
    return;
  }
  if (menu->destroying) {
    return;
  }
  menu->destroying = true;
  my_menu_dismiss(menu);
  n = my_darray_size(menu->items);
  for (i = 0; i < n; i++) {
    menu_item_t* it = (menu_item_t*)my_darray_get(menu->items, i);
    if (it->sub != NULL) {
      it->sub->parent = NULL;
      menu_destroy_internal(it->sub);
    }
    my_mem_free(menu->allocator, it->text);
    my_mem_free(menu->allocator, it);
  }
  my_darray_destroy(menu->items);
  my_mem_free(menu->allocator, menu);
}

static void menu_destroy_now(my_menu_t* menu) {
  my_menu_t* parent;
  size_t i, n;
  if (menu == NULL || menu->destroying) {
    return;
  }
  parent = menu->parent;
  /* Close the parent popup before freeing this menu's item model. */
  if (parent != NULL && parent->overlay != NULL) {
    menu_close_all(parent);
  }
  menu_destroy_internal(menu);
  if (parent == NULL) {
    return;
  }
  if (parent->open_sub == menu) {
    parent->open_sub = NULL;
  }
  n = my_darray_size(parent->items);
  for (i = 0; i < n; i++) {
    menu_item_t* item = (menu_item_t*)my_darray_get(parent->items, i);
    if (item != NULL && item->sub == menu) {
      my_darray_remove_at(parent->items, i);
      my_mem_free(parent->allocator, item->text);
      my_mem_free(parent->allocator, item);
      break;
    }
  }
}

void my_menu_destroy(my_menu_t* menu) {
  if (menu == NULL) {
    return;
  }
  if (menu->destroying) {
    return;
  }
  if (menu->operation_depth != 0) {
    menu->destroy_requested = true;
    return;
  }
  menu_destroy_now(menu);
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
