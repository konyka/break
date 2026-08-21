#include "mypal/break/my_pal_break.h"

#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>

#include "myc/my_str.h"
#include "platform/time.h"
#include "platform/platform_text.h"

typedef struct break_pal_t {
  my_pal_t base;
  const my_allocator_t *allocator;
  Platform *platform;
  my_pal_event_handler_t handler;
  void *handler_ctx;
  my_pal_window_t *primary_window;
} break_pal_t;

typedef struct break_window_t {
  my_pal_window_t base;
  break_pal_t *pal;
  const my_allocator_t *allocator;
  char *title;
  int32_t x;
  int32_t y;
  int32_t w;
  int32_t h;
  bool primary;
} break_window_t;

typedef struct break_queued_event_t break_queued_event_t;

typedef struct break_loop_t {
  my_pal_main_loop_t base;
  break_pal_t *pal;
  const my_allocator_t *allocator;
  my_timer_manager_t *timers;
  break_queued_event_t *event_head;
  break_queued_event_t *event_tail;
  atomic_flag event_lock;
  atomic_bool quit;
} break_loop_t;

struct break_queued_event_t {
  my_event_t event;
  char *ime_text;
  struct break_queued_event_t *next;
};

static break_pal_t *break_pal_from(my_pal_t *pal) {
  return (break_pal_t *)pal;
}

static uint64_t break_timer_now(void *ctx) {
  break_pal_t *pal = (break_pal_t *)ctx;
  (void)pal;
  return time_microseconds() / 1000u;
}

static my_ret_t break_win_set_title(my_pal_window_t *win, const char *title) {
  break_window_t *w = (break_window_t *)win;
  char *copy = my_strdup(w->allocator, title);
  if (title != NULL && copy == NULL) return MY_RET_OOM;
  my_mem_free(w->allocator, w->title);
  w->title = copy;
  return MY_RET_OK;
}

static my_ret_t break_win_resize(my_pal_window_t *win, int32_t width,
                                 int32_t height) {
  break_window_t *w = (break_window_t *)win;
  if (width <= 0 || height <= 0) return MY_RET_INVALID_PARAMS;
  w->w = width;
  w->h = height;
  return MY_RET_OK;
}

static my_ret_t break_win_show(my_pal_window_t *win) {
  (void)win;
  return MY_RET_OK;
}

static my_ret_t break_win_get_size(my_pal_window_t *win, int32_t *w,
                                   int32_t *h) {
  break_window_t *window = (break_window_t *)win;
  if (w != NULL) *w = window->w;
  if (h != NULL) *h = window->h;
  return MY_RET_OK;
}

static my_lcd_t *break_win_get_lcd(my_pal_window_t *win) {
  (void)win;
  return NULL;
}

static void break_win_destroy(my_pal_window_t *win) {
  break_window_t *w = (break_window_t *)win;
  if (w != NULL) {
    if (w->pal->primary_window == win) w->pal->primary_window = NULL;
    my_mem_free(w->allocator, w->title);
    my_mem_free(w->allocator, w);
  }
}

static my_pal_gl_t *break_win_gl_enable(my_pal_window_t *win) {
  (void)win;
  return NULL;
}

static void break_win_ime_set_enabled(my_pal_window_t *win, bool enabled) {
  platform_ime_set_enabled(((break_window_t *)win)->pal->platform, enabled);
}

static void break_win_ime_set_surrounding(my_pal_window_t *win,
                                          const char *utf8, int32_t cursor,
                                          int32_t anchor) {
  platform_ime_set_surrounding(((break_window_t *)win)->pal->platform, utf8,
                               cursor, anchor);
}

static void break_win_ime_set_spot(my_pal_window_t *win, int32_t x, int32_t y) {
  platform_ime_set_spot(((break_window_t *)win)->pal->platform, x, y);
}

static my_ret_t break_win_move(my_pal_window_t *win, int32_t x, int32_t y) {
  break_window_t *w = (break_window_t *)win;
  w->x = x;
  w->y = y;
  return MY_RET_OK;
}

static my_ret_t break_win_begin_move(my_pal_window_t *win) {
  break_window_t *w = (break_window_t *)win;
  if (!w->primary) return MY_RET_NOT_SUPPORTED;
  return platform_window_begin_move(w->pal->platform)
             ? MY_RET_OK
             : MY_RET_NOT_SUPPORTED;
}

static my_ret_t break_win_set_cursor(my_pal_window_t *win, my_cursor_t cursor) {
  PlatformCursor platform_cursor;
  switch (cursor) {
    case MY_CURSOR_ARROW:
      platform_cursor = PLATFORM_CURSOR_ARROW;
      break;
    case MY_CURSOR_TEXT:
      platform_cursor = PLATFORM_CURSOR_TEXT;
      break;
    case MY_CURSOR_HAND:
      platform_cursor = PLATFORM_CURSOR_HAND;
      break;
    default:
      return MY_RET_INVALID_PARAMS;
  }
  return platform_cursor_set(((break_window_t *)win)->pal->platform,
                             platform_cursor)
             ? MY_RET_OK
             : MY_RET_NOT_SUPPORTED;
}

static const my_pal_window_vtable_t s_break_window_vtable = {
    break_win_set_title, break_win_resize, break_win_show, break_win_get_size,
    break_win_get_lcd, break_win_destroy, break_win_gl_enable,
    break_win_ime_set_enabled, break_win_ime_set_surrounding,
    break_win_ime_set_spot, break_win_move,
    break_win_begin_move,
    break_win_set_cursor, NULL, NULL};

static my_pal_window_t *break_window_create(my_pal_t *pal, int32_t w, int32_t h,
                                            const char *title) {
  break_pal_t *p = break_pal_from(pal);
  break_window_t *win;
  win = (break_window_t *)my_mem_calloc(p->allocator, 1, sizeof(break_window_t));
  if (win == NULL) return NULL;
  win->base.vtable = &s_break_window_vtable;
  win->pal = p;
  win->allocator = p->allocator;
  win->w = w;
  win->h = h;
  win->primary = false;
  win->title = my_strdup(p->allocator, title);
  if (title != NULL && win->title == NULL) {
    my_mem_free(p->allocator, win);
    return NULL;
  }
  if (p->primary_window == NULL) {
    p->primary_window = (my_pal_window_t *)win;
    win->primary = true;
  }
  return (my_pal_window_t *)win;
}

static my_ret_t break_loop_post_event(my_pal_main_loop_t *loop,
                                      const my_event_t *event) {
  break_loop_t *l = (break_loop_t *)loop;
  break_queued_event_t *queued;
  if (event == NULL) return MY_RET_INVALID_PARAMS;
  queued = (break_queued_event_t *)my_mem_calloc(l->allocator, 1, sizeof(*queued));
  if (queued == NULL) return MY_RET_OOM;
  queued->event = *event;
  if ((event->type == MY_EVENT_IME_PREEDIT ||
       event->type == MY_EVENT_IME_COMMIT) &&
      event->u.ime.text != NULL) {
    queued->ime_text = my_strdup(l->allocator, event->u.ime.text);
    if (queued->ime_text == NULL) {
      my_mem_free(l->allocator, queued);
      return MY_RET_OOM;
    }
    queued->event.u.ime.text = queued->ime_text;
  }
  while (atomic_flag_test_and_set_explicit(&l->event_lock,
                                           memory_order_acquire)) {
  }
  if (l->event_tail != NULL)
    l->event_tail->next = queued;
  else
    l->event_head = queued;
  l->event_tail = queued;
  atomic_flag_clear_explicit(&l->event_lock, memory_order_release);
  return MY_RET_OK;
}

static uint32_t break_loop_dispatch_events(break_loop_t *l) {
  uint32_t count = 0;
  for (;;) {
    break_queued_event_t *queued;
    while (atomic_flag_test_and_set_explicit(&l->event_lock,
                                             memory_order_acquire)) {
    }
    if (l->event_head == NULL) {
      atomic_flag_clear_explicit(&l->event_lock, memory_order_release);
      break;
    }
    queued = l->event_head;
    l->event_head = queued->next;
    if (l->event_head == NULL) l->event_tail = NULL;
    atomic_flag_clear_explicit(&l->event_lock, memory_order_release);
    if (l->pal->handler != NULL) {
      (void)l->pal->handler(l->pal->handler_ctx, NULL, &queued->event);
    }
    my_mem_free(l->allocator, queued->ime_text);
    my_mem_free(l->allocator, queued);
    count++;
  }
  return count;
}

static my_ret_t break_loop_run(my_pal_main_loop_t *loop) {
  break_loop_t *l = (break_loop_t *)loop;
  atomic_store_explicit(&l->quit, false, memory_order_release);
  while (!atomic_load_explicit(&l->quit, memory_order_acquire)) {
    if (my_pal_break_pump(loop) == 0) break;
  }
  return MY_RET_OK;
}

static my_ret_t break_loop_quit(my_pal_main_loop_t *loop) {
  atomic_store_explicit(&((break_loop_t *)loop)->quit, true,
                        memory_order_release);
  return MY_RET_OK;
}

static uint32_t break_loop_add_timer(my_pal_main_loop_t *loop,
                                     my_timer_callback_t callback, void *ctx,
                                     uint32_t interval_ms) {
  return my_timer_add(((break_loop_t *)loop)->timers, callback, ctx,
                      interval_ms);
}

static my_ret_t break_loop_remove_timer(my_pal_main_loop_t *loop, uint32_t id) {
  return my_timer_remove(((break_loop_t *)loop)->timers, id);
}

static void break_loop_destroy(my_pal_main_loop_t *loop) {
  break_loop_t *l = (break_loop_t *)loop;
  if (l != NULL) {
    break_queued_event_t *queued;
    while (l->event_head != NULL) {
      queued = l->event_head;
      l->event_head = queued->next;
      my_mem_free(l->allocator, queued->ime_text);
      my_mem_free(l->allocator, queued);
    }
    l->event_tail = NULL;
    my_timer_manager_destroy(l->timers);
    my_mem_free(l->allocator, l);
  }
}

static const my_pal_main_loop_vtable_t s_break_loop_vtable = {
    break_loop_run,          break_loop_quit,        break_loop_post_event,
    break_loop_add_timer,    break_loop_remove_timer, break_loop_destroy};

static my_pal_main_loop_t *break_main_loop_create(my_pal_t *pal) {
  break_pal_t *p = break_pal_from(pal);
  break_loop_t *l = (break_loop_t *)my_mem_calloc(
      p->allocator, 1, sizeof(break_loop_t));
  if (l == NULL) return NULL;
  l->base.vtable = &s_break_loop_vtable;
  l->pal = p;
  l->allocator = p->allocator;
  atomic_init(&l->quit, false);
  atomic_flag_clear(&l->event_lock);
  l->timers = my_timer_manager_create(p->allocator, break_timer_now, p);
  if (l->timers == NULL) {
    break_loop_destroy((my_pal_main_loop_t *)l);
    return NULL;
  }
  return (my_pal_main_loop_t *)l;
}

static uint64_t break_time_now_ms(my_pal_t *pal) {
  (void)pal;
  return time_microseconds() / 1000u;
}

static my_ret_t break_set_event_handler(my_pal_t *pal,
                                        my_pal_event_handler_t handler,
                                        void *ctx) {
  break_pal_t *p = break_pal_from(pal);
  p->handler = handler;
  p->handler_ctx = ctx;
  return MY_RET_OK;
}

static my_ret_t break_clipboard_set(my_pal_t *pal, const char *text) {
  break_pal_t *p = break_pal_from(pal);
  if (text == NULL) return MY_RET_INVALID_PARAMS;
  return platform_clipboard_set_text(p->platform, text)
             ? MY_RET_OK
             : MY_RET_NOT_SUPPORTED;
}

static my_ret_t break_clipboard_get(my_pal_t *pal, char *buf, size_t size) {
  break_pal_t *p = break_pal_from(pal);
  PlatformClipboardResult result;
  char *text = NULL;
  if (buf == NULL || size == 0) return MY_RET_INVALID_PARAMS;
  result = platform_clipboard_get_text_alloc(p->platform, &text);
  if (result == PLATFORM_CLIPBOARD_PENDING) return MY_RET_PENDING;
  if (result != PLATFORM_CLIPBOARD_READY) return MY_RET_NOT_FOUND;
  (void)platform_utf8_copy(buf, size, text);
  free(text);
  return MY_RET_OK;
}

static my_ret_t break_clipboard_get_alloc(my_pal_t *pal,
                                          const my_allocator_t *allocator,
                                          char **out) {
  break_pal_t *p = break_pal_from(pal);
  char *text;
  PlatformClipboardResult result;
  if (out == NULL) return MY_RET_INVALID_PARAMS;
  *out = NULL;
  text = NULL;
  result = platform_clipboard_get_text_alloc(p->platform, &text);
  if (result == PLATFORM_CLIPBOARD_READY) {
    *out = my_strdup(allocator, text);
    free(text);
    return *out != NULL ? MY_RET_OK : MY_RET_OOM;
  }
  if (result == PLATFORM_CLIPBOARD_PENDING) return MY_RET_PENDING;
  return MY_RET_NOT_FOUND;
}

static float break_get_scale(my_pal_t *pal) {
  return platform_get_content_scale(break_pal_from(pal)->platform);
}

static bool break_needs_csd(my_pal_t *pal) {
  return platform_needs_client_decoration(break_pal_from(pal)->platform);
}

static void break_pal_destroy(my_pal_t *pal) {
  break_pal_t *p = break_pal_from(pal);
  if (p != NULL) {
    my_mem_free(p->allocator, p);
  }
}

static const my_pal_vtable_t s_break_pal_vtable = {
    break_window_create, break_main_loop_create, break_time_now_ms,
    break_set_event_handler, break_clipboard_set, break_clipboard_get,
    break_clipboard_get_alloc, break_get_scale, break_pal_destroy,
    break_needs_csd};

my_pal_t *my_pal_break_create(const my_allocator_t *allocator, Platform *platform,
                              RHIDevice *device) {
  break_pal_t *p;
  (void)device;
  if (platform == NULL) return NULL;
  p = (break_pal_t *)my_mem_calloc(allocator, 1, sizeof(break_pal_t));
  if (p == NULL) return NULL;
  p->base.vtable = &s_break_pal_vtable;
  p->allocator = allocator;
  p->platform = platform;
  return (my_pal_t *)p;
}

uint32_t my_pal_break_fire_timers(my_pal_main_loop_t *loop) {
  if (loop == NULL || loop->vtable != &s_break_loop_vtable) return 0;
  return my_timer_manager_fire(((break_loop_t *)loop)->timers);
}

uint32_t my_pal_break_pump(my_pal_main_loop_t *loop) {
  break_loop_t *l;
  if (loop == NULL || loop->vtable != &s_break_loop_vtable) return 0;
  l = (break_loop_t *)loop;
  return break_loop_dispatch_events(l) + my_timer_manager_fire(l->timers);
}
