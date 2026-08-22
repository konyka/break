/**
 * @file my_dialog.c
 * @brief Modal dialog window implementation (M13c).
 */
#include "myui/widgets/my_dialog.h"

#include "myc/my_darray.h"
#include "myc/my_str.h"
#include "myui/my_layout.h"
#include "myui/widgets/my_button.h"

/** @brief Per-button closure: click -> close with this result. */
typedef struct dialog_btn_ctx_t {
  my_dialog_t* dlg;
  int32_t result;
} dialog_btn_ctx_t;

/** @brief Extra dialog state hung on the content widget's name slot is
 * avoided; this struct is referenced by the emitter closures. */
typedef struct dialog_state_t {
  my_dialog_t pub;
  my_darray_t* btn_ctxs; /**< dialog_btn_ctx_t* (owned) */
} dialog_state_t;

/* content container: paints the dialog background */
static void dialog_content_paint(my_widget_t* widget, my_vgcanvas_t* vg) {
  uint32_t bg = my_widget_style_get_color(widget, MY_STATE_NORMAL,
                                          MY_STYLE_BG_COLOR, 0xF5F5F5FFu);
  my_vgcanvas_set_fill_color(vg, my_color_from_rgba32(bg));
  my_vgcanvas_fill_rect(vg, &(my_rectf_t){0, 0, (float)widget->rect.w,
                                          (float)widget->rect.h});
}

static const my_widget_vtable_t s_dialog_content_vtable = {
    dialog_content_paint, NULL, NULL, NULL};

static void dialog_report(my_dialog_t* dlg, int32_t result) {
  my_dialog_result_cb cb = dlg->on_result;
  dlg->on_result = NULL; /* one-shot: guard against re-entry */
  if (cb != NULL) {
    cb(dlg->cb_ctx, result);
  }
}

static void dialog_close_now(my_dialog_t* dlg, int32_t result) {
  my_window_manager_t* wm = dlg->wm;
  size_t i, n;
  if (wm != NULL) {
    n = my_darray_size(wm->windows);
    for (i = 0; i < n; i++) {
      my_window_t* w = (my_window_t*)my_darray_get(wm->windows, i);
      if (w != dlg->win && w->scrim) {
        w->scrim = false;
        my_widget_invalidate((my_widget_t*)w, NULL);
      }
    }
      my_window_manager_close(wm, dlg->win); /* drops the wm's ref only */
      /* dlg->win stays valid (creator's ref): my_dialog_destroy() drops it,
     * which finally destroys the window and its PAL window. NULL-ing it
     * here leaked the window (ghost surface on wayland). */
  }
  dlg->wm = NULL;
  dialog_report(dlg, result);
}

void my_dialog_close(my_dialog_t* dlg, int32_t result) {
  if (dlg == NULL || dlg->closing) {
    return;
  }
  dlg->closing = true;
  dialog_close_now(dlg, result);
}

static void dialog_on_key(void* ctx, const char* event, void* data) {
  my_dialog_t* dlg = (my_dialog_t*)ctx;
  const my_event_t* e = (const my_event_t*)data;
  if (my_str_eq(event, "key_down") && e != NULL &&
      e->u.key.key == MY_KEY_ESCAPE) {
    my_dialog_close(dlg, MY_DIALOG_CANCEL);
  }
}

static void dialog_on_button(void* ctx, const char* event, void* data) {
  dialog_btn_ctx_t* bc = (dialog_btn_ctx_t*)ctx;
  (void)event;
  (void)data;
  my_dialog_close(bc->dlg, bc->result);
}

my_dialog_t* my_dialog_create(const my_allocator_t* allocator, my_pal_t* pal,
                              const char* title, int32_t w, int32_t h) {
  dialog_state_t* st;
  my_dialog_t* dlg;
  my_widget_t* root;
  if (pal == NULL || w <= 0 || h <= 0) {
    return NULL;
  }
  st = (dialog_state_t*)my_mem_calloc(allocator, 1, sizeof(dialog_state_t));
  if (st == NULL) {
    return NULL;
  }
  dlg = &st->pub;
  dlg->allocator = allocator;
  dlg->win = my_window_create(allocator, pal, w, h, title);
  st->btn_ctxs = my_darray_create(allocator, 0);
  if (dlg->win == NULL || st->btn_ctxs == NULL) {
    my_darray_destroy(st->btn_ctxs);
    if (dlg->win != NULL) {
      my_widget_unref((my_widget_t*)dlg->win);
    }
    my_mem_free(allocator, st);
    return NULL;
  }
  root = my_window_widget(dlg->win);
  my_widget_set_layouter(root, my_layouter_linear_create(allocator, false, 0));

  dlg->content = my_widget_create(allocator, "dialog_content");
  my_widget_subclass_init((my_widget_t*)dlg->content,
                          &s_dialog_content_vtable);
  ((my_widget_t*)dlg->content)->focusable = true; /* ESC target */
  my_widget_set_layouter(dlg->content,
                         my_layouter_linear_create(allocator, false, 8));
  my_widget_set_layout_params(dlg->content, "w:1f h:1f");

  dlg->btn_row = my_widget_create(allocator, "dialog_buttons");
  my_widget_set_layouter(dlg->btn_row,
                         my_layouter_linear_create(allocator, true, 8));
  my_widget_set_layout_params(dlg->btn_row, "w:1f h:40");

  my_widget_add_child(root, dlg->content);
  my_widget_add_child(root, dlg->btn_row);
  my_widget_unref(dlg->content);
  my_widget_unref(dlg->btn_row);

  my_widget_on(dlg->content, "key_down", dialog_on_key, dlg);
  return dlg;
}

my_widget_t* my_dialog_content(my_dialog_t* dlg) {
  return dlg != NULL ? dlg->content : NULL;
}

my_widget_t* my_dialog_widget(my_dialog_t* dlg) {
  return dlg != NULL ? my_window_widget(dlg->win) : NULL;
}

my_ret_t my_dialog_add_button(my_dialog_t* dlg, const char* text,
                              int32_t result) {
  dialog_state_t* st = (dialog_state_t*)dlg;
  dialog_btn_ctx_t* bc;
  my_widget_t* btn;
  if (dlg == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  bc = (dialog_btn_ctx_t*)my_mem_alloc(dlg->allocator, sizeof(*bc));
  btn = my_button_create(dlg->allocator, text);
  if (bc == NULL || btn == NULL) {
    my_mem_free(dlg->allocator, bc);
    if (btn != NULL) {
      my_widget_unref(btn);
    }
    return MY_RET_OOM;
  }
  bc->dlg = dlg;
  bc->result = result;
  if (my_darray_push(st->btn_ctxs, bc) != MY_RET_OK) {
    my_mem_free(dlg->allocator, bc);
    my_widget_unref(btn);
    return MY_RET_OOM;
  }
  my_widget_set_layout_params(btn, "w:96 h:32");
  my_widget_on(btn, "click", dialog_on_button, bc);
  my_widget_add_child(dlg->btn_row, btn);
  my_widget_unref(btn);
  return MY_RET_OK;
}

my_ret_t my_dialog_open(my_dialog_t* dlg, my_window_manager_t* wm,
                        my_dialog_result_cb cb, void* ctx) {
  my_window_t* below;
  int32_t pw = 0, ph = 0;
  if (dlg == NULL || wm == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  dlg->wm = wm;
  dlg->closing = false;
  dlg->on_result = cb;
  dlg->cb_ctx = ctx;
  below = my_window_manager_top(wm);
  if (below != NULL) {
    below->scrim = true;
    my_widget_invalidate((my_widget_t*)below, NULL);
    /* center over the window below (ports that can move windows) */
    my_pal_window_get_size(below->pal_window, &pw, &ph);
    my_pal_window_move(dlg->win->pal_window,
                       pw / 2 - dlg->win->base.rect.w / 2,
                       ph / 2 - dlg->win->base.rect.h / 2);
  }
  dlg->win->modal = true;
  /* ESC lands on the content container even without a focused button */
  my_event_dispatcher_set_focus(&dlg->win->dispatcher, dlg->content);
  return my_window_manager_open(wm, dlg->win);
}

void my_dialog_destroy(my_dialog_t* dlg) {
  dialog_state_t* st = (dialog_state_t*)dlg;
  size_t i, n;
  if (dlg == NULL) {
    return;
  }
  n = my_darray_size(st->btn_ctxs);
  for (i = 0; i < n; i++) {
    my_mem_free(dlg->allocator, my_darray_get(st->btn_ctxs, i));
  }
  my_darray_destroy(st->btn_ctxs);
  /* Drop the creator's window ref. The manager owns a separate ref while
   * the dialog is open. */
  if (dlg->win != NULL) {
    my_widget_unref((my_widget_t*)dlg->win);
  }
  my_mem_free(dlg->allocator, st);
}
