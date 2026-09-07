/**
 * @file my_window_manager.c
 * @brief Window stack manager + my_app_run entry point.
 */
#include <stdio.h>
#include <stdlib.h>
#include "myui/my_window_manager.h"

#include "myui/my_animator.h"
#include "myui/my_ui_command.h"

static void wm_destroy_impl(my_window_manager_t* wm);
static void wm_callback_end(my_window_manager_t* wm);

typedef struct wm_on_open_hook_t {
  my_window_on_open_context_destroy_fn_t destroy_ctx;
  my_emitter_context_lease_t* lease;
  void* context;
} wm_on_open_hook_t;

static void wm_release_on_open_hook_record(wm_on_open_hook_t* record) {
  if (record == NULL) {
    return;
  }
  if (record->destroy_ctx != NULL) {
    record->destroy_ctx(record->context);
  }
  my_emitter_context_lease_unref(record->lease);
}

static my_ret_t wm_retire_on_open_hook(my_window_manager_t* wm) {
  wm_on_open_hook_t* record;
  my_window_on_open_context_destroy_fn_t destroy_ctx;
  my_emitter_context_lease_t* lease;
  void* context;

  if (wm == NULL || wm->on_open == NULL) {
    return MY_RET_OK;
  }
  if (wm->on_open_destroy == NULL && wm->on_open_lease == NULL) {
    wm->on_open = NULL;
    wm->on_open_ctx = NULL;
    return MY_RET_OK;
  }
  if (wm->callback_depth == 0u) {
    destroy_ctx = wm->on_open_destroy;
    lease = wm->on_open_lease;
    context = wm->on_open_ctx;
    wm->on_open = NULL;
    wm->on_open_ctx = NULL;
    wm->on_open_destroy = NULL;
    wm->on_open_lease = NULL;
    if (destroy_ctx != NULL) {
      destroy_ctx(context);
    }
    my_emitter_context_lease_unref(lease);
    return MY_RET_OK;
  }

  record = (wm_on_open_hook_t*)my_mem_calloc(wm->allocator, 1u,
                                             sizeof(*record));
  if (record == NULL) {
    return MY_RET_OOM;
  }
  destroy_ctx = wm->on_open_destroy;
  lease = wm->on_open_lease;
  context = wm->on_open_ctx;
  record->destroy_ctx = destroy_ctx;
  record->lease = lease;
  record->context = context;
  if (my_darray_push(wm->retired_on_open_hooks, record) != MY_RET_OK) {
    my_mem_free(wm->allocator, record);
    return MY_RET_OOM;
  }
  wm->on_open = NULL;
  wm->on_open_ctx = NULL;
  wm->on_open_destroy = NULL;
  wm->on_open_lease = NULL;
  return MY_RET_OK;
}

static void wm_flush_retired_on_open_hooks(my_window_manager_t* wm) {
  while (wm != NULL && my_darray_size(wm->retired_on_open_hooks) > 0u) {
    size_t index = my_darray_size(wm->retired_on_open_hooks) - 1u;
    wm_on_open_hook_t* record = (wm_on_open_hook_t*)my_darray_get(
        wm->retired_on_open_hooks, index);
    my_darray_remove_at(wm->retired_on_open_hooks, index);
    wm_release_on_open_hook_record(record);
    my_mem_free(wm->allocator, record);
  }
}

typedef struct wm_destroy_listener_t {
  uint32_t id;
  my_window_manager_destroy_listener_t callback;
  void* ctx;
  my_window_manager_destroy_context_destroy_fn_t destroy_ctx;
  my_emitter_context_lease_t* lease;
} wm_destroy_listener_t;

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
  my_window_notify_closed(win);
  my_widget_ref((my_widget_t*)win);
  /* Keep the manager fields valid through the destroy chain. If another
   * owner still holds the window, detach after the manager ref is dropped;
   * otherwise release the temporary ref directly and let destruction run. */
  my_widget_unref((my_widget_t*)win);
  if (atomic_load_explicit(&((my_object_t*)win)->ref_count,
                           memory_order_acquire) > 1u) {
    ((my_widget_t*)win)->anim_mgr = NULL;
    win->loop = NULL;
    win->wm = NULL;
  }
  my_widget_unref((my_widget_t*)win);
  wm_refresh_scrims(wm);
  if (wm->surface_focus_window == NULL) {
    wm->surface_focus_window = my_window_manager_top(wm);
  }
}

static my_ret_t wm_on_pal_event_impl(void* ctx, my_pal_window_t* pal_window,
                                     const my_event_t* event) {
  my_window_manager_t* wm = (my_window_manager_t*)ctx;
  my_window_t* win;
  my_window_t* top;
  if (pal_window == NULL) {
    if (event != NULL && event->type == MY_EVENT_COMMAND) {
      my_ui_command_dispatch((my_ui_command_t*)event->u.command.data);
      return MY_RET_OK;
    }
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

static my_ret_t wm_on_pal_event(void* ctx, my_pal_window_t* pal_window,
                                const my_event_t* event) {
  my_window_manager_t* wm = (my_window_manager_t*)ctx;
  my_ret_t result;
  if (wm == NULL || event == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  wm->callback_depth++;
  result = wm_on_pal_event_impl(ctx, pal_window, event);
  wm_callback_end(wm);
  return result;
}

my_ret_t my_window_manager_on_pal_event(my_window_manager_t* wm,
                                        my_pal_window_t* pal_window,
                                        const my_event_t* event) {
  if (wm == NULL || event == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  return wm_on_pal_event(wm, pal_window, event);
}

static my_ret_t wm_dispatch_surface_event_impl(
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

my_ret_t my_window_manager_dispatch_surface_event(
    my_window_manager_t* wm, const my_event_t* event) {
  my_ret_t result;
  if (wm == NULL || event == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  wm->callback_depth++;
  result = wm_dispatch_surface_event_impl(wm, event);
  wm_callback_end(wm);
  return result;
}

static my_ret_t wm_resize_surface_impl(my_window_manager_t* wm,
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
    if (wm->destroy_requested || wm->destroying) {
      break;
    }
    my_window_t* below = (my_window_t*)my_darray_get(wm->windows, i - 1);
    my_window_t* win = (my_window_t*)my_darray_get(wm->windows, i);
    my_widget_t* below_root = (my_widget_t*)below;
    my_widget_t* root = (my_widget_t*)win;
    if (win->modal) {
      my_rect_t old_bounds = root->rect;
      my_rect_t new_bounds = root->rect;
      new_bounds.x = my_rect_center_axis_i32(
          below_root->rect.x, below_root->rect.w, root->rect.w);
      new_bounds.y = my_rect_center_axis_i32(
          below_root->rect.y, below_root->rect.h, root->rect.h);
      wm_invalidate_below(wm, i, &old_bounds);
      (void)my_widget_set_rect(root, &new_bounds);
      (void)my_pal_window_move(win->pal_window, new_bounds.x, new_bounds.y);
    }
  }
  return MY_RET_OK;
}

my_ret_t my_window_manager_resize_surface(my_window_manager_t* wm,
                                          int32_t width, int32_t height) {
  my_ret_t result;
  if (wm == NULL || wm->destroying) {
    return MY_RET_INVALID_PARAMS;
  }
  wm->callback_depth++;
  result = wm_resize_surface_impl(wm, width, height);
  wm_callback_end(wm);
  return result;
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

bool my_window_manager_refresh_media(my_window_manager_t* wm) {
  bool changed = false;
  (void)my_window_manager_refresh_media_ex(wm, &changed);
  return changed;
}

my_ret_t my_window_manager_refresh_media_ex(my_window_manager_t* wm,
                                            bool* out_changed) {
  size_t i;
  if (out_changed == NULL) return MY_RET_INVALID_PARAMS;
  *out_changed = false;
  if (wm == NULL) return MY_RET_INVALID_PARAMS;
  for (i = 0; i < my_darray_size(wm->windows); i++) {
    my_ret_t ret = my_window_refresh_media_style(
        (my_window_t*)my_darray_get(wm->windows, i));
    if (ret == MY_RET_OK) {
      *out_changed = true;
    } else if (ret != MY_RET_NOT_FOUND) {
      return ret;
    }
  }
  return MY_RET_OK;
}

/* ---------------- lifecycle ---------------- */

static void wm_destroy_impl(my_window_manager_t* wm);

static void wm_callback_end(my_window_manager_t* wm) {
  if (wm == NULL || wm->callback_depth == 0u) {
    return;
  }
  wm->callback_depth--;
  if (wm->callback_depth == 0u && wm->retired_on_open_hooks != NULL) {
    wm->callback_depth++;
    wm_flush_retired_on_open_hooks(wm);
    wm->callback_depth--;
  }
  if (wm->callback_depth == 0u && wm->destroy_requested) {
    wm->destroy_requested = false;
    wm_destroy_impl(wm);
  }
}

/** @brief ~60fps repaint tick: paint every window that collected dirty
 * rects since the last frame (no-op for clean windows). Covers redraws
 * triggered outside event dispatch (animations, timers, model changes). */
static my_ret_t wm_paint_tick(void* ctx) {
  my_window_manager_t* wm = (my_window_manager_t*)ctx;
  my_window_t** windows = NULL;
  size_t i, n = 0;
  uint64_t epoch;
  wm->callback_depth++;
  if (my_window_manager_snapshot_windows(wm, &windows, &n) != MY_RET_OK) {
    wm_callback_end(wm);
    return MY_RET_OK;
  }
  epoch = wm->windows_epoch;
  for (i = 0; i < n; i++) {
    if (wm->windows_epoch != epoch || wm->destroy_requested ||
        wm->destroying) {
      break;
    }
    my_window_paint(windows[i]);
  }
  my_window_manager_release_snapshot(wm, windows, n);
  wm_callback_end(wm);
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
  wm->command_scope = my_ui_command_scope_create(allocator);
  wm->windows = my_darray_create(allocator, 0);
  wm->destroy_listeners = my_darray_create(allocator, 0);
  wm->retired_on_open_hooks = my_darray_create(allocator, 0);
  wm->anim_mgr = my_animator_manager_create(allocator, pal, loop);
  if (wm->command_scope == NULL || wm->windows == NULL ||
      wm->destroy_listeners == NULL || wm->retired_on_open_hooks == NULL ||
      wm->anim_mgr == NULL) {
    my_ui_command_scope_unref(wm->command_scope);
    my_darray_destroy(wm->windows);
    my_darray_destroy(wm->destroy_listeners);
    my_darray_destroy(wm->retired_on_open_hooks);
    my_animator_manager_destroy(wm->anim_mgr);
    my_mem_free(allocator, wm);
    return NULL;
  }
  wm->auto_paint = true;
  wm->paint_timer_id = my_pal_main_loop_add_timer(loop, wm_paint_tick, wm, 33);
  my_pal_set_event_handler(pal, wm_on_pal_event, wm);
  return wm;
}

static my_ret_t wm_open_impl(my_window_manager_t* wm, my_window_t* win) {
  size_t i;
  if (wm == NULL || win == NULL || wm->destroying) {
    return MY_RET_INVALID_PARAMS;
  }
  for (i = 0; i < my_darray_size(wm->windows); i++) {
    if (my_darray_get(wm->windows, i) == win) {
      return MY_RET_INVALID_PARAMS;
    }
  }
  if (my_darray_push(wm->windows, my_widget_ref((my_widget_t*)win)) !=
      MY_RET_OK) {
    my_widget_unref((my_widget_t*)win);
    return MY_RET_OOM;
  }
  wm->windows_epoch++;
  ((my_widget_t*)win)->anim_mgr = wm->anim_mgr;
  win->close_notified = false;
  my_ui_command_scope_reopen(win->command_scope);
  win->loop = wm->loop;
  win->wm = wm; /* M16: CSD close button routes through this */
  wm->surface_focus_window = win;
  my_pal_window_show(win->pal_window);
  my_widget_invalidate((my_widget_t*)win, NULL);
  if (wm->on_open != NULL) {
    my_window_on_open_t callback = wm->on_open;
    my_emitter_context_lease_t* lease = wm->on_open_lease;
    my_emitter_context_lease_t* callback_lease =
        lease != NULL ? my_emitter_context_lease_ref(lease) : NULL;
    void* context = lease != NULL
                        ? my_emitter_context_lease_context(callback_lease)
                        : wm->on_open_ctx;
    if (lease == NULL || callback_lease != NULL) {
      if (context != NULL || lease == NULL) {
        callback(wm, win, context);
      }
    }
    my_emitter_context_lease_unref(callback_lease);
  }
  return MY_RET_OK;
}

my_ret_t my_window_manager_open(my_window_manager_t* wm, my_window_t* win) {
  my_ret_t result;
  if (wm == NULL || win == NULL || wm->destroying) {
    return MY_RET_INVALID_PARAMS;
  }
  wm->callback_depth++;
  result = wm_open_impl(wm, win);
  wm_callback_end(wm);
  return result;
}

static my_ret_t wm_close_impl(my_window_manager_t* wm, my_window_t* win) {
  size_t i, n;
  if (wm == NULL || win == NULL || wm->destroying) {
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

my_ret_t my_window_manager_close(my_window_manager_t* wm, my_window_t* win) {
  my_ret_t result;
  if (wm == NULL || win == NULL || wm->destroying) {
    return MY_RET_INVALID_PARAMS;
  }
  wm->callback_depth++;
  result = wm_close_impl(wm, win);
  wm_callback_end(wm);
  return result;
}

my_window_t* my_window_manager_top(my_window_manager_t* wm) {
  size_t n;
  if (wm == NULL) {
    return NULL;
  }
  n = my_darray_size(wm->windows);
  return n > 0 ? (my_window_t*)my_darray_get(wm->windows, n - 1) : NULL;
}

static my_ret_t wm_back_to_home_impl(my_window_manager_t* wm) {
  if (wm == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  while (my_darray_size(wm->windows) > 1) {
    if (wm->destroy_requested || wm->destroying) {
      break;
    }
    wm_release_window_at(wm, my_darray_size(wm->windows) - 1);
  }
  wm_refresh_scrims(wm);
  return MY_RET_OK;
}

my_ret_t my_window_manager_back_to_home(my_window_manager_t* wm) {
  my_ret_t result;
  if (wm == NULL || wm->destroying) {
    return MY_RET_INVALID_PARAMS;
  }
  wm->callback_depth++;
  result = wm_back_to_home_impl(wm);
  wm_callback_end(wm);
  return result;
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
  (void)my_window_manager_set_on_open_owned(wm, cb, ctx, NULL);
}

my_ret_t my_window_manager_set_on_open_owned(
    my_window_manager_t* wm, my_window_on_open_t cb, void* ctx,
    my_window_on_open_context_destroy_fn_t destroy_ctx) {
  if (wm == NULL || wm->destroying || (cb == NULL && destroy_ctx != NULL)) {
    return MY_RET_INVALID_PARAMS;
  }
  if (wm_retire_on_open_hook(wm) != MY_RET_OK) {
    return MY_RET_OOM;
  }
  wm->on_open = cb;
  wm->on_open_ctx = ctx;
  wm->on_open_destroy = destroy_ctx;
  return MY_RET_OK;
}

my_ret_t my_window_manager_set_on_open_lease(
    my_window_manager_t* wm, my_window_on_open_t cb,
    my_emitter_context_lease_t* lease) {
  my_emitter_context_lease_t* retained;
  if (wm == NULL || cb == NULL || lease == NULL || wm->destroying ||
      !my_emitter_context_lease_is_valid(lease)) {
    return MY_RET_INVALID_PARAMS;
  }
  retained = my_emitter_context_lease_ref(lease);
  if (retained == NULL) {
    return MY_RET_OOM;
  }
  if (wm_retire_on_open_hook(wm) != MY_RET_OK) {
    my_emitter_context_lease_unref(retained);
    return MY_RET_OOM;
  }
  wm->on_open = cb;
  wm->on_open_lease = retained;
  return MY_RET_OK;
}

uint32_t my_window_manager_add_destroy_listener(
    my_window_manager_t* wm, my_window_manager_destroy_listener_t callback,
    void* ctx) {
  return my_window_manager_add_destroy_listener_owned(wm, callback, ctx, NULL);
}

uint32_t my_window_manager_add_destroy_listener_owned(
    my_window_manager_t* wm, my_window_manager_destroy_listener_t callback,
    void* ctx, my_window_manager_destroy_context_destroy_fn_t destroy_ctx) {
  wm_destroy_listener_t* listener;
  if (wm == NULL || callback == NULL || wm->destroying) {
    return 0u;
  }
  listener = (wm_destroy_listener_t*)my_mem_calloc(
      wm->allocator, 1, sizeof(wm_destroy_listener_t));
  if (listener == NULL) {
    return 0u;
  }
  listener->id = ++wm->destroy_listener_next_id;
  if (listener->id == 0u) {
    listener->id = ++wm->destroy_listener_next_id;
  }
  listener->callback = callback;
  listener->ctx = ctx;
  listener->destroy_ctx = destroy_ctx;
  if (my_darray_push(wm->destroy_listeners, listener) != MY_RET_OK) {
    my_mem_free(wm->allocator, listener);
    return 0u;
  }
  return listener->id;
}

uint32_t my_window_manager_add_destroy_listener_lease(
    my_window_manager_t* wm, my_window_manager_destroy_listener_t callback,
    my_emitter_context_lease_t* lease) {
  wm_destroy_listener_t* listener;
  if (wm == NULL || callback == NULL || lease == NULL ||
      !my_emitter_context_lease_is_valid(lease) || wm->destroying) {
    return 0u;
  }
  listener = (wm_destroy_listener_t*)my_mem_calloc(
      wm->allocator, 1, sizeof(*listener));
  if (listener == NULL) return 0u;
  listener->id = ++wm->destroy_listener_next_id;
  if (listener->id == 0u) listener->id = ++wm->destroy_listener_next_id;
  listener->lease = my_emitter_context_lease_ref(lease);
  if (listener->lease == NULL) {
    my_mem_free(wm->allocator, listener);
    return 0u;
  }
  listener->callback = callback;
  if (my_darray_push(wm->destroy_listeners, listener) != MY_RET_OK) {
    my_emitter_context_lease_unref(listener->lease);
    my_mem_free(wm->allocator, listener);
    return 0u;
  }
  return listener->id;
}

my_ret_t my_window_manager_remove_destroy_listener(my_window_manager_t* wm,
                                                   uint32_t id) {
  size_t i, n;
  if (wm == NULL || id == 0u) {
    return MY_RET_INVALID_PARAMS;
  }
  n = my_darray_size(wm->destroy_listeners);
  for (i = 0; i < n; i++) {
    wm_destroy_listener_t* listener =
        (wm_destroy_listener_t*)my_darray_get(wm->destroy_listeners, i);
    if (listener->id == id) {
      my_window_manager_destroy_context_destroy_fn_t destroy_ctx =
          listener->destroy_ctx;
      void *ctx = listener->ctx;
      my_emitter_context_lease_t* lease = listener->lease;
      const my_allocator_t *allocator = wm->allocator;
      my_darray_remove_at(wm->destroy_listeners, i);
      my_mem_free(allocator, listener);
      if (destroy_ctx != NULL) {
        destroy_ctx(ctx);
      }
      my_emitter_context_lease_unref(lease);
      return MY_RET_OK;
    }
  }
  return MY_RET_NOT_FOUND;
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

static void wm_destroy_impl(my_window_manager_t* wm) {
  wm_destroy_listener_t* listener;
  if (wm == NULL) {
    return;
  }
  wm->destroying = true;
  my_ui_command_scope_close(wm->command_scope);
  (void)wm_retire_on_open_hook(wm);
  wm_flush_retired_on_open_hooks(wm);
  my_pal_set_event_handler(wm->pal, NULL, NULL);
  if (wm->paint_timer_id > 0) {
    my_pal_main_loop_remove_timer(wm->loop, wm->paint_timer_id);
    wm->paint_timer_id = 0;
  }
  /* Notify borrowed observers while window loop/animation pointers remain
   * valid; they may need to cancel model timers before windows are released. */
  while (my_darray_size(wm->destroy_listeners) > 0) {
    size_t index = my_darray_size(wm->destroy_listeners) - 1u;
    listener = (wm_destroy_listener_t*)my_darray_get(
        wm->destroy_listeners, index);
    my_darray_remove_at(wm->destroy_listeners, index);
    {
      my_window_manager_destroy_listener_t callback = listener->callback;
      my_window_manager_destroy_context_destroy_fn_t destroy_ctx =
          listener->destroy_ctx;
      void *ctx = listener->ctx;
      my_emitter_context_lease_t* lease = listener->lease;
      const my_allocator_t *allocator = wm->allocator;
      my_mem_free(allocator, listener);
      if (lease != NULL) ctx = my_emitter_context_lease_context(lease);
      if (ctx != NULL) callback(ctx);
      if (destroy_ctx != NULL) {
        destroy_ctx(ctx);
      }
      my_emitter_context_lease_unref(lease);
    }
  }
  /* windows next: their destroy chains cancel animations via anim_mgr */
  while (my_darray_size(wm->windows) > 0) {
    wm_release_window_at(wm, my_darray_size(wm->windows) - 1);
  }
  my_animator_manager_destroy(wm->anim_mgr);
  wm->anim_mgr = NULL;
  my_darray_destroy(wm->windows);
  my_darray_destroy(wm->destroy_listeners);
  my_darray_destroy(wm->retired_on_open_hooks);
  my_ui_command_scope_unref(wm->command_scope);
  wm->command_scope = NULL;
  my_mem_free(wm->allocator, wm);
}

void my_window_manager_destroy(my_window_manager_t* wm) {
  if (wm == NULL || wm->destroying) {
    return;
  }
  if (wm->callback_depth != 0u) {
    wm->destroying = true;
    wm->destroy_requested = true;
    return;
  }
  wm_destroy_impl(wm);
}

struct my_ui_command_scope_t* my_window_manager_command_scope_ref(
    my_window_manager_t* wm) {
  return wm != NULL ? my_ui_command_scope_ref(wm->command_scope) : NULL;
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
