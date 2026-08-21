/**
 * @file my_pal_dummy.c
 * @brief Dummy PAL port: headless windows + manual event queue + fake clock.
 */
#include "mypal/dummy/my_pal_dummy.h"

#include "myc/my_darray.h"
#include "myc/my_str.h"
#include "myr/my_lcd_mem.h"

#include <string.h>

/* ---------------- platform ---------------- */

typedef struct dummy_pal_t {
  my_pal_t base;
  const my_allocator_t* allocator;
  uint64_t now_ms;                    /**< injectable fake clock */
  my_pal_event_handler_t handler;
  void* handler_ctx;
  char* clipboard;                    /**< in-memory clipboard text */
  float scale;                        /**< injectable (M12c, default 1) */
  bool needs_csd;  /**< injectable (M16, default false = zero regression) */
} dummy_pal_t;

static dummy_pal_t* pal_from(my_pal_t* pal) {
  return (dummy_pal_t*)pal;
}

/* ---------------- window ---------------- */

typedef struct dummy_window_t {
  my_pal_window_t base;
  dummy_pal_t* pal;
  const my_allocator_t* allocator;
  int32_t w;
  int32_t h;
  char* title;
  bool shown;
  bool ime_enabled;
  char ime_surrounding[256];
  int32_t ime_cursor;
  int32_t ime_anchor;
  my_lcd_t* lcd;
  int32_t ime_spot_x; /**< last ime_set_spot (M13a, for tests) */
  int32_t ime_spot_y;
  int32_t pos_x; /**< last move (M13c, for tests) */
  int32_t pos_y;
  uint32_t begin_move_count; /**< begin_move calls (M16, for tests) */
  my_cursor_t cursor;        /**< last set_cursor (M21a, for tests) */
} dummy_window_t;

static my_ret_t dummy_win_set_title(my_pal_window_t* win, const char* title) {
  dummy_window_t* w = (dummy_window_t*)win;
  char* copy = my_strdup(w->allocator, title);
  if (title != NULL && copy == NULL) {
    return MY_RET_OOM;
  }
  my_mem_free(w->allocator, w->title);
  w->title = copy;
  return MY_RET_OK;
}

static my_ret_t dummy_win_resize(my_pal_window_t* win, int32_t width, int32_t height) {
  dummy_window_t* w = (dummy_window_t*)win;
  dummy_pal_t* p = (dummy_pal_t*)w->pal;
  my_lcd_t* lcd;
  if (width <= 0 || height <= 0) {
    return MY_RET_INVALID_PARAMS;
  }
  /* sizes are logical (M12c): the lcd is the physical buffer */
  lcd = my_lcd_mem_create(w->allocator,
                          (uint32_t)(width * p->scale + 0.5f),
                          (uint32_t)(height * p->scale + 0.5f),
                          MY_PIXEL_FORMAT_BGRA8888);
  if (lcd == NULL) {
    return MY_RET_OOM;
  }
  my_lcd_destroy(w->lcd);
  w->lcd = lcd;
  w->w = width;
  w->h = height;
  return MY_RET_OK;
}

static my_ret_t dummy_win_show(my_pal_window_t* win) {
  ((dummy_window_t*)win)->shown = true;
  return MY_RET_OK;
}

static my_ret_t dummy_win_get_size(my_pal_window_t* win, int32_t* w, int32_t* h) {
  dummy_window_t* win_ = (dummy_window_t*)win;
  if (w != NULL) {
    *w = win_->w;
  }
  if (h != NULL) {
    *h = win_->h;
  }
  return MY_RET_OK;
}

static my_lcd_t* dummy_win_get_lcd(my_pal_window_t* win) {
  return ((dummy_window_t*)win)->lcd;
}

static void dummy_win_destroy(my_pal_window_t* win) {
  dummy_window_t* w = (dummy_window_t*)win;
  if (w != NULL) {
    my_lcd_destroy(w->lcd);
    my_mem_free(w->allocator, w->title);
    my_mem_free(w->allocator, w);
  }
}

static my_pal_gl_t* dummy_win_gl_enable(my_pal_window_t* win) {
  (void)win;
  return NULL; /* dummy port: no GL support (headless) */
}

static void dummy_win_ime_set_enabled(my_pal_window_t* win, bool enabled) {
  ((dummy_window_t*)win)->ime_enabled = enabled;
}

static void dummy_win_ime_set_surrounding(my_pal_window_t* win,
                                          const char* utf8, int32_t cursor,
                                          int32_t anchor) {
  dummy_window_t* window = (dummy_window_t*)win;
  snprintf(window->ime_surrounding, sizeof(window->ime_surrounding), "%s",
           utf8 != NULL ? utf8 : "");
  window->ime_cursor = cursor;
  window->ime_anchor = anchor;
}

static void dummy_win_ime_set_spot(my_pal_window_t* win, int32_t x,
                                   int32_t y) {
  dummy_window_t* w = (dummy_window_t*)win;
  w->ime_spot_x = x; /* recorded for tests (M13a) */
  w->ime_spot_y = y;
}

static my_ret_t dummy_win_move(my_pal_window_t* win, int32_t x, int32_t y) {
  dummy_window_t* w = (dummy_window_t*)win;
  w->pos_x = x; /* recorded for tests (M13c) */
  w->pos_y = y;
  return MY_RET_OK;
}

static my_ret_t dummy_win_begin_move(my_pal_window_t* win) {
  dummy_window_t* w = (dummy_window_t*)win;
  w->begin_move_count++; /* recorded for tests (M16) */
  return MY_RET_OK;
}

static my_ret_t dummy_win_set_cursor(my_pal_window_t* win,
                                     my_cursor_t cursor) {
  dummy_window_t* w = (dummy_window_t*)win;
  if (cursor < MY_CURSOR_ARROW || cursor > MY_CURSOR_HAND) {
    return MY_RET_INVALID_PARAMS;
  }
  w->cursor = cursor; /* recorded for tests (M21a) */
  return MY_RET_OK;
}

static bool dummy_needs_csd(my_pal_t* pal) {
  return pal_from(pal)->needs_csd; /* injectable test hook (M16) */
}

static const my_pal_window_vtable_t s_dummy_window_vtable = {
    dummy_win_set_title, dummy_win_resize,  dummy_win_show,
    dummy_win_get_size,  dummy_win_get_lcd, dummy_win_destroy,
    dummy_win_gl_enable, dummy_win_ime_set_enabled,
    dummy_win_ime_set_surrounding, dummy_win_ime_set_spot,
    dummy_win_move,      dummy_win_begin_move,
    dummy_win_set_cursor, NULL /* gl_enable_api: dummy has no GL (M25a) */,
    NULL /* vk_create_surface: dummy has no Vulkan (M25b) */};

static my_pal_window_t* dummy_window_create(my_pal_t* pal, int32_t w, int32_t h,
                                            const char* title) {
  dummy_pal_t* p = pal_from(pal);
  dummy_window_t* win;
  if (w <= 0 || h <= 0) {
    return NULL;
  }
  win = (dummy_window_t*)my_mem_calloc(p->allocator, 1, sizeof(dummy_window_t));
  if (win == NULL) {
    return NULL;
  }
  win->base.vtable = &s_dummy_window_vtable;
  win->pal = p;
  win->allocator = p->allocator;
  win->w = w;
  win->h = h;
  /* sizes are logical (M12c): the lcd is the physical buffer */
  win->lcd = my_lcd_mem_create(p->allocator,
                               (uint32_t)(w * p->scale + 0.5f),
                               (uint32_t)(h * p->scale + 0.5f),
                               MY_PIXEL_FORMAT_BGRA8888);
  if (win->lcd == NULL) {
    my_mem_free(p->allocator, win);
    return NULL;
  }
  if (title != NULL && dummy_win_set_title((my_pal_window_t*)win, title) != MY_RET_OK) {
    dummy_win_destroy((my_pal_window_t*)win);
    return NULL;
  }
  return (my_pal_window_t*)win;
}

/* ---------------- main loop ---------------- */

typedef struct queued_event_t {
  my_event_t event;
  my_pal_window_t* window; /**< NULL for posted events */
} queued_event_t;

typedef struct dummy_loop_t {
  my_pal_main_loop_t base;
  dummy_pal_t* pal;
  const my_allocator_t* allocator;
  my_darray_t* queue; /**< queued_event_t* */
  my_timer_manager_t* timers;
  bool quit;
} dummy_loop_t;

static uint64_t dummy_timer_now(void* ctx) {
  return ((dummy_pal_t*)ctx)->now_ms;
}

static my_ret_t dummy_loop_post_event(my_pal_main_loop_t* loop,
                                      const my_event_t* event) {
  dummy_loop_t* l = (dummy_loop_t*)loop;
  queued_event_t* qe;
  if (event == NULL) {
    return MY_RET_INVALID_PARAMS;
  }
  qe = (queued_event_t*)my_mem_calloc(l->allocator, 1, sizeof(queued_event_t));
  if (qe == NULL) {
    return MY_RET_OOM;
  }
  qe->event = *event;
  qe->window = NULL;
  if (my_darray_push(l->queue, qe) != MY_RET_OK) {
    my_mem_free(l->allocator, qe);
    return MY_RET_OOM;
  }
  return MY_RET_OK;
}

/** @brief Dispatch one queued event, FIFO. Returns false when queue is empty. */
static bool dummy_loop_pump_one(dummy_loop_t* l) {
  queued_event_t* qe;
  if (my_darray_size(l->queue) == 0) {
    return false;
  }
  qe = (queued_event_t*)my_darray_get(l->queue, 0);
  my_darray_remove_at(l->queue, 0);
  if (l->pal->handler != NULL) {
    l->pal->handler(l->pal->handler_ctx, qe->window, &qe->event);
  }
  my_mem_free(l->allocator, qe);
  return true;
}

static my_ret_t dummy_loop_run(my_pal_main_loop_t* loop) {
  dummy_loop_t* l = (dummy_loop_t*)loop;
  l->quit = false;
  while (!l->quit) {
    if (!dummy_loop_pump_one(l)) {
      /* starved: dummy loop does not block; fire due timers, then exit
       * when nothing more can happen with a frozen clock */
      if (my_timer_manager_fire(l->timers) == 0) {
        break;
      }
    }
  }
  return MY_RET_OK;
}

static my_ret_t dummy_loop_quit(my_pal_main_loop_t* loop) {
  ((dummy_loop_t*)loop)->quit = true;
  return MY_RET_OK;
}

static uint32_t dummy_loop_add_timer(my_pal_main_loop_t* loop,
                                     my_timer_callback_t callback, void* ctx,
                                     uint32_t interval_ms) {
  return my_timer_add(((dummy_loop_t*)loop)->timers, callback, ctx, interval_ms);
}

static my_ret_t dummy_loop_remove_timer(my_pal_main_loop_t* loop, uint32_t id) {
  return my_timer_remove(((dummy_loop_t*)loop)->timers, id);
}

static void dummy_loop_destroy(my_pal_main_loop_t* loop) {
  dummy_loop_t* l = (dummy_loop_t*)loop;
  queued_event_t* qe;
  if (l == NULL) {
    return;
  }
  while (my_darray_size(l->queue) > 0) {
    qe = (queued_event_t*)my_darray_get(l->queue, 0);
    my_darray_remove_at(l->queue, 0);
    my_mem_free(l->allocator, qe);
  }
  my_darray_destroy(l->queue);
  my_timer_manager_destroy(l->timers);
  my_mem_free(l->allocator, l);
}

static const my_pal_main_loop_vtable_t s_dummy_loop_vtable = {
    dummy_loop_run,          dummy_loop_quit,        dummy_loop_post_event,
    dummy_loop_add_timer,    dummy_loop_remove_timer, dummy_loop_destroy};

static my_pal_main_loop_t* dummy_main_loop_create(my_pal_t* pal) {
  dummy_pal_t* p = pal_from(pal);
  dummy_loop_t* l = (dummy_loop_t*)my_mem_calloc(p->allocator, 1, sizeof(dummy_loop_t));
  if (l == NULL) {
    return NULL;
  }
  l->base.vtable = &s_dummy_loop_vtable;
  l->pal = p;
  l->allocator = p->allocator;
  l->queue = my_darray_create(p->allocator, 0);
  l->timers = my_timer_manager_create(p->allocator, dummy_timer_now, p);
  if (l->queue == NULL || l->timers == NULL) {
    dummy_loop_destroy((my_pal_main_loop_t*)l);
    return NULL;
  }
  return (my_pal_main_loop_t*)l;
}

uint32_t my_pal_main_loop_pump_n(my_pal_main_loop_t* loop, uint32_t n) {
  dummy_loop_t* l;
  uint32_t pumped = 0;
  if (loop == NULL || loop->vtable != &s_dummy_loop_vtable) {
    return 0;
  }
  l = (dummy_loop_t*)loop;
  while (pumped < n && dummy_loop_pump_one(l)) {
    pumped++;
  }
  return pumped;
}

/* ---------------- platform vtable ---------------- */

static uint64_t dummy_time_now_ms(my_pal_t* pal) {
  return pal_from(pal)->now_ms;
}

static my_ret_t dummy_set_event_handler(my_pal_t* pal,
                                        my_pal_event_handler_t handler, void* ctx) {
  dummy_pal_t* p = pal_from(pal);
  p->handler = handler;
  p->handler_ctx = ctx;
  return MY_RET_OK;
}

static my_ret_t dummy_clipboard_set(my_pal_t* pal, const char* text) {
  dummy_pal_t* p = pal_from(pal);
  char* copy = my_strdup(p->allocator, text);
  if (text != NULL && copy == NULL) {
    return MY_RET_OOM;
  }
  my_mem_free(p->allocator, p->clipboard);
  p->clipboard = copy;
  return MY_RET_OK;
}

static my_ret_t dummy_clipboard_get(my_pal_t* pal, char* buf, size_t size) {
  dummy_pal_t* p = pal_from(pal);
  if (buf == NULL || size == 0) {
    return MY_RET_INVALID_PARAMS;
  }
  if (p->clipboard == NULL) {
    return MY_RET_NOT_FOUND;
  }
  snprintf(buf, size, "%s", p->clipboard);
  return MY_RET_OK;
}

static my_ret_t dummy_clipboard_get_alloc(my_pal_t* pal,
                                          const my_allocator_t* allocator,
                                          char** out) {
  dummy_pal_t* p = pal_from(pal);
  if (out == NULL) return MY_RET_INVALID_PARAMS;
  *out = my_strdup(allocator, p->clipboard);
  if (p->clipboard == NULL) return MY_RET_NOT_FOUND;
  return *out != NULL ? MY_RET_OK : MY_RET_OOM;
}

static float dummy_get_scale(my_pal_t* pal) {
  return pal_from(pal)->scale;
}

static void dummy_pal_destroy(my_pal_t* pal) {
  dummy_pal_t* p = pal_from(pal);
  if (p != NULL) {
    my_mem_free(p->allocator, p->clipboard);
    my_mem_free(p->allocator, p);
  }
}

static const my_pal_vtable_t s_dummy_pal_vtable = {
    dummy_window_create, dummy_main_loop_create, dummy_time_now_ms,
    dummy_set_event_handler, dummy_clipboard_set, dummy_clipboard_get,
    dummy_clipboard_get_alloc, dummy_get_scale, dummy_pal_destroy,
    dummy_needs_csd};

void my_pal_dummy_set_scale_factor(my_pal_t* pal, float scale) {
  if (pal != NULL && scale > 0.0f) {
    pal_from(pal)->scale = scale;
  }
}

void my_pal_dummy_get_ime_spot(my_pal_window_t* win, int32_t* x,
                               int32_t* y) {
  dummy_window_t* w = (dummy_window_t*)win;
  if (w == NULL) {
    return;
  }
  if (x != NULL) {
    *x = w->ime_spot_x;
  }
  if (y != NULL) {
    *y = w->ime_spot_y;
  }
}

void my_pal_dummy_inject_event(my_pal_t* pal, my_pal_window_t* win,
                               const my_event_t* event) {
  dummy_pal_t* p = pal_from(pal);
  if (p != NULL && p->handler != NULL) {
    p->handler(p->handler_ctx, win, event);
  }
}

my_pal_t* my_pal_dummy_create(const my_allocator_t* allocator) {
  dummy_pal_t* p = (dummy_pal_t*)my_mem_calloc(allocator, 1, sizeof(dummy_pal_t));
  if (p == NULL) {
    return NULL;
  }
  p->base.vtable = &s_dummy_pal_vtable;
  p->allocator = allocator;
  p->scale = 1.0f;
  return (my_pal_t*)p;
}

void my_pal_dummy_set_now_ms(my_pal_t* pal, uint64_t now_ms) {
  if (pal != NULL && pal->vtable == &s_dummy_pal_vtable) {
    pal_from(pal)->now_ms = now_ms;
  }
}

void my_pal_dummy_set_needs_csd(my_pal_t* pal, bool needs) {
  if (pal != NULL && pal->vtable == &s_dummy_pal_vtable) {
    pal_from(pal)->needs_csd = needs;
  }
}

uint32_t my_pal_dummy_begin_move_count(my_pal_window_t* win) {
  return win != NULL ? ((dummy_window_t*)win)->begin_move_count : 0;
}

my_cursor_t my_pal_dummy_get_cursor(my_pal_window_t* win) {
  return win != NULL ? ((dummy_window_t*)win)->cursor : MY_CURSOR_ARROW;
}

bool my_pal_dummy_get_ime_enabled(my_pal_window_t* win) {
  return win != NULL && ((dummy_window_t*)win)->ime_enabled;
}

void my_pal_dummy_get_ime_surrounding(my_pal_window_t* win, char* utf8,
                                      size_t size, int32_t* cursor,
                                      int32_t* anchor) {
  dummy_window_t* window = (dummy_window_t*)win;
  if (window == NULL) return;
  if (utf8 != NULL && size > 0) {
    snprintf(utf8, size, "%s", window->ime_surrounding);
  }
  if (cursor != NULL) *cursor = window->ime_cursor;
  if (anchor != NULL) *anchor = window->ime_anchor;
}
