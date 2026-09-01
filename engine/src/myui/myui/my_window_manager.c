/**
 * @file my_window_manager.c
 * @brief Window stack manager + my_app_run entry point.
 */
#include <stdio.h>
#include <stdlib.h>
#include "myui/my_window_manager.h"

#include "myui/my_animator.h"

/* ---------------- event routing from PAL ---------------- */

static my_window_t* wm_find_window(my_window_manager_t* wm,
                                   my_pal_window_t* pal_window) {
  size_t i, n = my_darray_size(wm->windows);
  for (i = 0; i < n; i++) {
    my_window_t* win = (my_window_t*)my_darray_get(wm->windows, i);
    if (win->pal_window == pal_window) {
      return win;
    }
  }
  return NULL;
}

static bool wm_is_pointer_event(my_event_type_t type) {
  return type == MY_EVENT_POINTER_DOWN || type == MY_EVENT_POINTER_MOVE ||
         type == MY_EVENT_POINTER_UP || type == MY_EVENT_POINTER_WHEEL;
}

static bool wm_is_input_event(my_event_type_t type) {
  return wm_is_pointer_event(type) || type == MY_EVENT_KEY_DOWN ||
         type == MY_EVENT_KEY_UP || type == MY_EVENT_IME_PREEDIT ||
         type == MY_EVENT_IME_COMMIT ||
         type == MY_EVENT_IME_DELETE_SURROUNDING;
}

static void wm_refresh_scrims(my_window_manager_t* wm) {
  size_t i;
  size_t n = my_darray_size(wm->windows);
  for (i = 0; i < n; i++) {
    my_window_t* win = (my_window_t*)my_darray_get(wm->windows, i);
    bool scrim = i + 1 < n &&
                 ((my_window_t*)my_darray_get(wm->windows, i + 1))->modal;
    if (win->scrim != scrim) {
      win->scrim = scrim;
      my_widget_invalidate((my_widget_t*)win, NULL);
    }
  }
}

static void wm_invalidate_below(my_window_manager_t* wm, size_t top_index,
                                const my_rect_t* bounds) {
  size_t i;
  for (i = 0; i < top_index; i++) {
    my_window_t* win = (my_window_t*)my_darray_get(wm->windows, i);
    my_rect_t clipped;
    if (my_rect_intersect(&((my_widget_t*)win)->rect, bounds, &clipped)) {
      (void)my_dirty_rects_add(&win->dirty, &clipped);
    }
  }
}

static void wm_release_window_at(my_window_manager_t* wm, size_t index) {
  my_window_t* win = (my_window_t*)my_darray_get(wm->windows, index);
  my_rect_t old_bounds;
  if (win == NULL) {
    return;
  }
  old_bounds = ((my_widget_t*)win)->rect;
  wm_invalidate_below(wm, index, &old_bounds);
  my_darray_remove_at(wm->windows, index);
  wm->windows_epoch++;
  if (wm->surface_pointer_grab == win) {
    wm->surface_pointer_grab = NULL;
  }
  if (wm->surface_focus_window == win) {
    wm->surface_focus_window = NULL;
  }
  /* Unref BEFORE detaching loop/anim_mgr: the destroy chain cancels the
   * tip timer, stops animations, and lets descendant destroy chains
   * (node_view flow timer, button release timer) re-resolve win->loop —
   * all of them need these fields still valid, otherwise the shared main
   * loop keeps timers that fire on freed objects. A window that survives
   * via outside refs simply keeps valid pointers. */
  my_widget_unref((my_widget_t*)win);
  wm_refresh_scrims(wm);
  if (wm->surface_focus_window == NULL) {
    wm->surface_focus_window = my_window_manager_top(wm);
  }
}

static my_ret_t wm_on_pal_event(void* ctx, my_pal_window_t* pal_window,
                                const my_event_t* event) {
  my_window_manager_t* wm = (my_window_manager_t*)ctx;
  my_window_t* win;
  my_window_t* top;
  if (pal_window == NULL) {
    top = my_window_manager_top(wm);
    return top != NULL ? my_window_on_pal_event(top, event) : MY_RET_OK;
  }
  win = wm_find_window(wm, pal_window);
  if (win == NULL) {
    if (getenv("MYUI_WL_TRACE") != NULL &&
        (event->type == MY_EVENT_POINTER_DOWN ||
         event->type == MY_EVENT_POINTER_UP)) {
      fprintf(stderr, "[wltrace] wm route: pal_window=%p NOT FOUND type=%d\n",
              (void*)pal_window, (int)event->type);
    }
    return MY_RET_OK;
  }
  if (getenv("MYUI_WL_TRACE") != NULL &&
      (event->type == MY_EVENT_POINTER_DOWN ||
       event->type == MY_EVENT_POINTER_UP)) {
    my_window_t* t = my_window_manager_top(wm);
    fprintf(stderr,
            "[wltrace] wm route: win=%p top=%p top_modal=%d type=%d xy=(%d,%d)\n",
            (void*)win, (void*)t, t != NULL ? (int)t->modal : -1,
            (int)event->type, event->u.pointer.x, event->u.pointer.y);
  }
  if (event->type == MY_EVENT_QUIT) {
    my_window_manager_close(wm, win);
    return MY_RET_OK;
  }
  /* modal enforcement (M13c): while a modal window is on top, input
   * events go only to it; lower windows are veiled and blocked */
  top = my_window_manager_top(wm);
  if (top != NULL && top->modal && win != top && wm_is_input_event(event->type)) {
    return MY_RET_OK;
  }
  return my_window_on_pal_event(win, event);
}

my_ret_t my_window_manager_on_pal_event(my_window_manager_t* wm,
                                        my_pal_window_t* pal_window,
                                        const my_event_t* event) {
  if (wm == NULL || event == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  return wm_on_pal_event(wm, pal_window, event);
}

my_ret_t my_window_manager_dispatch_surface_event(
    my_window_manager_t* wm, const my_event_t* event) {
  my_window_t* target = NULL;
  my_window_t* top;
  size_t i;
  if (wm == NULL || event == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (event->type == MY_EVENT_RESIZE) {
    return my_window_manager_resize_surface(wm, event->u.resize.w,
                                            event->u.resize.h);
  }
  top = my_window_manager_top(wm);
  if (top == NULL) {
    return MY_RET_NOT_FOUND;
  }
  if (event->type == MY_EVENT_QUIT) {
    return my_window_manager_close(wm, top);
  }
  if (!wm_is_pointer_event(event->type)) {
    target = top;
    if (top->modal) {
      wm->surface_focus_window = top;
    } else if (wm->surface_focus_window != NULL) {
      target = wm->surface_focus_window;
    }
    if (wm_is_input_event(event->type) || event->type == MY_EVENT_USER) {
      return my_window_on_pal_event(target, event);
    }
    return MY_RET_OK;
  }
  if ((event->type == MY_EVENT_POINTER_MOVE ||
       event->type == MY_EVENT_POINTER_UP) &&
      wm->surface_pointer_grab != NULL) {
    target = wm->surface_pointer_grab;
  } else if (top->modal) {
    target = top;
  } else {
    i = my_darray_size(wm->windows);
    while (i > 0) {
      my_window_t* candidate;
      i--;
      candidate = (my_window_t*)my_darray_get(wm->windows, i);
      if (my_widget_hit_test((my_widget_t*)candidate, event->u.pointer.x,
                             event->u.pointer.y) != NULL) {
        target = candidate;
        break;
      }
    }
  }
  if (event->type == MY_EVENT_POINTER_DOWN) {
    wm->surface_pointer_grab = target;
    wm->surface_focus_window = target;
  }
  if (target != NULL) {
    (void)my_window_on_pal_event(target, event);
  }
  if (event->type == MY_EVENT_POINTER_UP) {
    wm->surface_pointer_grab = NULL;
  }
  return MY_RET_OK;
}

my_ret_t my_window_manager_resize_surface(my_window_manager_t* wm,
                                          int32_t width, int32_t height) {
  my_event_t event;
  size_t i;
  size_t n;
  if (wm == NULL || width <= 0 || height <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  n = my_darray_size(wm->windows);
  if (n == 0) {
    return MY_RET_NOT_FOUND;
  }
  event = my_event_init(MY_EVENT_RESIZE);
  event.u.resize.w = width;
  event.u.resize.h = height;
  {
    my_window_t* root = (my_window_t*)my_darray_get(wm->windows, 0);
    (void)my_pal_window_resize(root->pal_window, width, height);
    (void)my_window_on_pal_event(root, &event);
  }
  for (i = 1; i < n; i++) {
    my_window_t* below = (my_window_t*)my_darray_get(wm->windows, i - 1);
    my_window_t* win = (my_window_t*)my_darray_get(wm->windows, i);
    my_widget_t* below_root = (my_widget_t*)below;
    my_widget_t* root = (my_widget_t*)win;
    if (win->modal) {
      my_rect_t old_bounds = root->rect;
      my_rect_t new_bounds = root->rect;
      new_bounds.x =
          below_root->rect.x + (below_root->rect.w - root->rect.w) / 2;
      new_bounds.y =
          below_root->rect.y + (below_root->rect.h - root->rect.h) / 2;
      wm_invalidate_below(wm, i, &old_bounds);
      (void)my_widget_set_rect(root, &new_bounds);
      (void)my_pal_window_move(win->pal_window, new_bounds.x, new_bounds.y);
    }
  }
  return MY_RET_OK;
}

bool my_window_manager_refresh_scales(my_window_manager_t* wm) {
  size_t i;
  bool changed = false;
  if (wm == NULL) {
    return false;
  }
  for (i = 0; i < my_darray_size(wm->windows); i++) {
    changed = my_window_refresh_scale(
                  (my_window_t*)my_darray_get(wm->windows, i)) ||
              changed;
  }
  return changed;
}

/* ---------------- lifecycle ---------------- */

/** @brief ~60fps repaint tick: paint every window that collected dirty
 * rects since the last frame (no-op for clean windows). Covers redraws
 * triggered outside event dispatch (animations, timers, model changes). */
static my_ret_t wm_paint_tick(void* ctx) {
  my_window_manager_t* wm = (my_window_manager_t*)ctx;
  my_window_t** windows = NULL;
  size_t i, n = 0;
  uint64_t epoch;
  if (my_window_manager_snapshot_windows(wm, &windows, &n) != MY_RET_OK) {
    return MY_RET_OK;
  }
  epoch = wm->windows_epoch;
  for (i = 0; i < n; i++) {
    if (wm->windows_epoch != epoch) {
      break;
    }
    my_window_paint(windows[i]);
  }
  my_window_manager_release_snapshot(wm, windows, n);
  return MY_RET_OK;
}

my_window_manager_t* my_window_manager_create(const my_allocator_t* allocator,
                                              my_pal_t* pal,
                                              my_pal_main_loop_t* loop) {
  my_window_manager_t* wm;
  if (pal == NULL || loop == NULL) {
    return NULL;
  }
  wm = (my_window_manager_t*)my_mem_calloc(allocator, 1,
                                           sizeof(my_window_manager_t));
  if (wm == NULL) {
    return NULL;
  }
  wm->allocator = allocator;
  wm->pal = pal;
  wm->loop = loop;
  wm->windows = my_darray_create(allocator, 0);
  wm->anim_mgr = my_animator_manager_create(allocator, pal, loop);
  if (wm->windows == NULL || wm->anim_mgr == NULL) {
    my_darray_destroy(wm->windows);
    my_animator_manager_destroy(wm->anim_mgr);
    my_mem_free(allocator, wm);
    return NULL;
  }
  wm->auto_paint = true;
  wm->paint_timer_id = my_pal_main_loop_add_timer(loop, wm_paint_tick, wm, 33);
  my_pal_set_event_handler(pal, wm_on_pal_event, wm);
  return wm;
}

my_ret_t my_window_manager_open(my_window_manager_t* wm, my_window_t* win) {
  if (wm == NULL || win == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  if (my_darray_push(wm->windows, my_widget_ref((my_widget_t*)win)) !=
      MY_RET_OK) {
    my_widget_unref((my_widget_t*)win);
    return MY_RET_OOM;
  }
  wm->windows_epoch++;
  ((my_widget_t*)win)->anim_mgr = wm->anim_mgr;
  win->loop = wm->loop;
  win->wm = wm; /* M16: CSD close button routes through this */
  wm->surface_focus_window = win;
  my_pal_window_show(win->pal_window);
  my_widget_invalidate((my_widget_t*)win, NULL);
  if (wm->on_open != NULL) {
    wm->on_open(wm, win, wm->on_open_ctx);
  }
  return MY_RET_OK;
}

my_ret_t my_window_manager_close(my_window_manager_t* wm, my_window_t* win) {
  size_t i, n;
  if (wm == NULL || win == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  n = my_darray_size(wm->windows);
  for (i = 0; i < n; i++) {
    if (my_darray_get(wm->windows, i) == win) {
      wm_release_window_at(wm, i);
      if (my_darray_size(wm->windows) == 0) {
        wm->quit_requested = true;
        my_pal_main_loop_quit(wm->loop);
      }
      return MY_RET_OK;
    }
  }
  return MY_RET_NOT_FOUND;
}

my_window_t* my_window_manager_top(my_window_manager_t* wm) {
  size_t n;
  if (wm == NULL) {
    return NULL;
  }
  n = my_darray_size(wm->windows);
  return n > 0 ? (my_window_t*)my_darray_get(wm->windows, n - 1) : NULL;
}

my_ret_t my_window_manager_back_to_home(my_window_manager_t* wm) {
  if (wm == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  while (my_darray_size(wm->windows) > 1) {
    wm_release_window_at(wm, my_darray_size(wm->windows) - 1);
  }
  wm_refresh_scrims(wm);
  return MY_RET_OK;
}

size_t my_window_manager_count(my_window_manager_t* wm) {
  return wm != NULL ? my_darray_size(wm->windows) : 0;
}

my_ret_t my_window_manager_snapshot_windows(my_window_manager_t* wm,
                                            my_window_t***out_windows,
                                            size_t* out_count) {
  my_window_t** windows;
  size_t i;
  size_t n;
  if (wm == NULL || out_windows == NULL || out_count == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  *out_windows = NULL;
  *out_count = 0;
  n = my_darray_size(wm->windows);
  if (n == 0) {
    return MY_RET_OK;
  }
  windows = (my_window_t**)my_mem_alloc(wm->allocator,
                                        n * sizeof(my_window_t*));
  if (windows == NULL) {
    return MY_RET_OOM;
  }
  for (i = 0; i < n; i++) {
    windows[i] = (my_window_t*)my_widget_ref(
        (my_widget_t*)my_darray_get(wm->windows, i));
  }
  *out_windows = windows;
  *out_count = n;
  return MY_RET_OK;
}

void my_window_manager_release_snapshot(my_window_manager_t* wm,
                                        my_window_t** windows, size_t count) {
  size_t i;
  if (wm == NULL || windows == NULL) {
    return;
  }
  for (i = 0; i < count; i++) {
    my_widget_unref((my_widget_t*)windows[i]);
  }
  my_mem_free(wm->allocator, windows);
}

uint64_t my_window_manager_windows_epoch(const my_window_manager_t* wm) {
  return wm != NULL ? wm->windows_epoch : 0;
}

void my_window_manager_set_on_open(my_window_manager_t* wm,
                                   my_window_on_open_t cb, void* ctx) {
  if (wm != NULL) {
    wm->on_open = cb;
    wm->on_open_ctx = ctx;
  }
}

void my_window_manager_set_auto_paint(my_window_manager_t* wm, bool on) {
  if (wm == NULL) {
    return;
  }
  if (on && wm->paint_timer_id == 0) {
    wm->paint_timer_id = my_pal_main_loop_add_timer(wm->loop, wm_paint_tick,
                                                    wm, 33);
  } else if (!on && wm->paint_timer_id > 0) {
    my_pal_main_loop_remove_timer(wm->loop, wm->paint_timer_id);
    wm->paint_timer_id = 0;
  }
  wm->auto_paint = on;
}

void my_window_manager_destroy(my_window_manager_t* wm) {
  if (wm == NULL) {
    return;
  }
  my_pal_set_event_handler(wm->pal, NULL, NULL);
  if (wm->paint_timer_id > 0) {
    my_pal_main_loop_remove_timer(wm->loop, wm->paint_timer_id);
    wm->paint_timer_id = 0;
  }
  /* windows first: their destroy chains cancel animations via anim_mgr */
  while (my_darray_size(wm->windows) > 0) {
    wm_release_window_at(wm, my_darray_size(wm->windows) - 1);
  }
  my_animator_manager_destroy(wm->anim_mgr);
  wm->anim_mgr = NULL;
  my_darray_destroy(wm->windows);
  my_mem_free(wm->allocator, wm);
}

/* ---------------- application entry ---------------- */

my_ret_t my_app_run(my_pal_t* pal, my_app_window_factory_t factory, void* ctx) {
  my_pal_main_loop_t* loop;
  my_window_manager_t* wm;
  my_window_t* win;
  if (pal == NULL || factory == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  loop = my_pal_main_loop_create(pal);
  wm = my_window_manager_create(NULL, pal, loop);
  if (loop == NULL || wm == NULL) {
    my_window_manager_destroy(wm);
    my_pal_main_loop_destroy(loop);
    return MY_RET_OOM;
  }
  win = factory(pal, ctx);
  if (win == NULL) {
    my_window_manager_destroy(wm);
    my_pal_main_loop_destroy(loop);
    return MY_RET_FAIL;
  }
  my_window_manager_open(wm, win);
  my_widget_unref((my_widget_t*)win); /* manager holds the only ref now */
  my_pal_main_loop_run(loop);
  my_window_manager_destroy(wm);
  my_pal_main_loop_destroy(loop);
  return MY_RET_OK;
}
