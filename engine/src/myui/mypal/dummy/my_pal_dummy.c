/**
 * @file my_pal_dummy.c
 * @brief Dummy PAL port: headless windows + manual event queue + fake clock.
 */
#include "mypal/dummy/my_pal_dummy.h"

#include "myc/my_str.h"
#include "myr/my_lcd_mem.h"

#include <stdatomic.h>
#include <string.h>

/* ---------------- platform ---------------- */

typedef struct dummy_pal_t {
  my_pal_t base;
  const my_allocator_t* allocator;
  uint64_t now_ms;                    /**< injectable fake clock */
  uint64_t time_step_ms;              /**< test-only query increment */
  uint32_t time_query_count;          /**< test-only clock call counter */
  my_pal_event_handler_t handler;
  void* handler_ctx;
  char* clipboard;                    /**< in-memory clipboard text */
  uint32_t clipboard_pending_reads;   /**< test-only async read budget */
  float scale;                        /**< injectable (M12c, default 1) */
  bool needs_csd;  /**< injectable (M16, default false = zero regression) */
  struct dummy_media_provider_t *media_provider;
} dummy_pal_t;

typedef struct dummy_media_provider_t {
  const my_allocator_t *allocator;
  my_pal_media_context_t media;
  uint32_t known;
} dummy_media_provider_t;

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

static my_ret_t dummy_get_media_context(void* context,
                                        my_pal_media_context_ex_t* out) {
  dummy_media_provider_t* provider = (dummy_media_provider_t*)context;
  if (out == NULL) return MY_RET_INVALID_PARAMS;
  out->base = provider->media;
  out->known = provider->known;
  return MY_RET_OK;
}

static void dummy_release_media_context(void* context) {
  dummy_media_provider_t *provider = (dummy_media_provider_t *)context;
  if (provider != NULL) {
    my_mem_free(provider->allocator, provider);
  }
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
  char* ime_text;          /**< owned copy for posted IME events */
  struct queued_event_t* next;
} queued_event_t;

typedef struct dummy_loop_t {
  my_pal_main_loop_t base;
  dummy_pal_t* pal;
  const my_allocator_t* allocator;
  queued_event_t* event_head;
  queued_event_t* event_tail;
  my_timer_manager_t* timers;
  atomic_flag event_lock;
  atomic_bool accepting_events;
  atomic_bool quit;
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
  if ((event->type == MY_EVENT_IME_PREEDIT ||
       event->type == MY_EVENT_IME_COMMIT) &&
      event->u.ime.text != NULL) {
    qe->ime_text = my_strdup(l->allocator, event->u.ime.text);
    if (qe->ime_text == NULL) {
      my_mem_free(l->allocator, qe);
      return MY_RET_OOM;
    }
    qe->event.u.ime.text = qe->ime_text;
  }
  while (atomic_flag_test_and_set_explicit(&l->event_lock,
                                           memory_order_acquire)) {
  }
  if (!atomic_load_explicit(&l->accepting_events, memory_order_relaxed)) {
    atomic_flag_clear_explicit(&l->event_lock, memory_order_release);
    my_mem_free(l->allocator, qe->ime_text);
    my_mem_free(l->allocator, qe);
    return MY_RET_PENDING;
  }
  if (l->event_tail != NULL)
    l->event_tail->next = qe;
  else
    l->event_head = qe;
  l->event_tail = qe;
  atomic_flag_clear_explicit(&l->event_lock, memory_order_release);
  return MY_RET_OK;
}

/** @brief Dispatch one queued event, FIFO. Returns false when queue is empty. */
static bool dummy_loop_pump_one(dummy_loop_t* l) {
  queued_event_t* qe;
  while (atomic_flag_test_and_set_explicit(&l->event_lock,
                                           memory_order_acquire)) {
  }
  if (l->event_head == NULL) {
    atomic_flag_clear_explicit(&l->event_lock, memory_order_release);
    return false;
  }
  qe = l->event_head;
  l->event_head = qe->next;
  if (l->event_head == NULL) l->event_tail = NULL;
  atomic_flag_clear_explicit(&l->event_lock, memory_order_release);
  if (l->pal->handler != NULL) {
    l->pal->handler(l->pal->handler_ctx, qe->window, &qe->event);
  }
  my_event_release_payload(&qe->event);
  my_mem_free(l->allocator, qe->ime_text);
  my_mem_free(l->allocator, qe);
  return true;
}

static my_ret_t dummy_loop_run(my_pal_main_loop_t* loop) {
  dummy_loop_t* l = (dummy_loop_t*)loop;
  atomic_store_explicit(&l->quit, false, memory_order_release);
  while (!atomic_load_explicit(&l->quit, memory_order_acquire)) {
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
  atomic_store_explicit(&((dummy_loop_t*)loop)->quit, true,
                        memory_order_release);
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
  while (atomic_flag_test_and_set_explicit(&l->event_lock,
                                           memory_order_acquire)) {
  }
  atomic_store_explicit(&l->accepting_events, false, memory_order_release);
  while (l->event_head != NULL) {
    qe = l->event_head;
    l->event_head = qe->next;
    my_mem_free(l->allocator, qe->ime_text);
    my_event_release_payload(&qe->event);
    my_mem_free(l->allocator, qe);
  }
  l->event_tail = NULL;
  atomic_flag_clear_explicit(&l->event_lock, memory_order_release);
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
  l->timers = my_timer_manager_create(p->allocator, dummy_timer_now, p);
  atomic_flag_clear(&l->event_lock);
  atomic_init(&l->accepting_events, true);
  atomic_init(&l->quit, false);
  if (l->timers == NULL) {
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
  dummy_pal_t* dummy = pal_from(pal);
  uint64_t now = dummy->now_ms;
  if (dummy->time_query_count != UINT32_MAX) {
    dummy->time_query_count++;
  }
  if (UINT64_MAX - dummy->now_ms < dummy->time_step_ms) {
    dummy->now_ms = UINT64_MAX;
  } else {
    dummy->now_ms += dummy->time_step_ms;
  }
  return now;
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
  *out = NULL;
  if (p->clipboard_pending_reads > 0u) {
    p->clipboard_pending_reads--;
    return MY_RET_PENDING;
  }
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
    my_pal_unregister_media_provider(pal);
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

void my_pal_dummy_set_media_context(my_pal_t* pal,
                                    const my_pal_media_context_t* context) {
  if (pal == NULL || context == NULL) return;
  pal_from(pal)->media_provider->media = *context;
  pal_from(pal)->media_provider->media.capabilities &= MY_PAL_MEDIA_CAP_ALL;
  pal_from(pal)->media_provider->known = 0u;
}

void my_pal_dummy_set_media_context_ex(
    my_pal_t* pal, const my_pal_media_context_ex_t* context) {
  if (pal == NULL || context == NULL) return;
  pal_from(pal)->media_provider->media = context->base;
  pal_from(pal)->media_provider->media.capabilities &= MY_PAL_MEDIA_CAP_ALL;
  pal_from(pal)->media_provider->known = context->known & MY_PAL_MEDIA_KNOWN_ALL;
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
  dummy_media_provider_t* media_provider;
  if (p == NULL) {
    return NULL;
  }
  media_provider = (dummy_media_provider_t *)my_mem_calloc(
      allocator, 1, sizeof(*media_provider));
  if (media_provider == NULL) {
    my_mem_free(allocator, p);
    return NULL;
  }
  p->base.vtable = &s_dummy_pal_vtable;
  p->allocator = allocator;
  p->scale = 1.0f;
  p->media_provider = media_provider;
  media_provider->allocator = allocator;
  media_provider->media.screen = true;
  media_provider->media.capabilities = MY_PAL_MEDIA_CAP_COLOR_SRGB;
  media_provider->known = MY_PAL_MEDIA_KNOWN_HOVER |
                          MY_PAL_MEDIA_KNOWN_POINTER |
                          MY_PAL_MEDIA_KNOWN_ANY_POINTER |
                          MY_PAL_MEDIA_KNOWN_COLOR_GAMUT;
  {
    const my_pal_media_provider_t provider = {
        sizeof(provider), MY_PAL_MEDIA_PROVIDER_ABI_VERSION,
        dummy_get_media_context, media_provider, dummy_release_media_context};
    if (my_pal_register_media_provider((my_pal_t*)p, &provider) != MY_RET_OK) {
      my_mem_free(allocator, media_provider);
      my_mem_free(allocator, p);
      return NULL;
    }
  }
  return (my_pal_t*)p;
}

void my_pal_dummy_set_now_ms(my_pal_t* pal, uint64_t now_ms) {
  if (pal != NULL && pal->vtable == &s_dummy_pal_vtable) {
    pal_from(pal)->now_ms = now_ms;
  }
}

void my_pal_dummy_set_clipboard_pending_reads(my_pal_t* pal, uint32_t count) {
  if (pal != NULL && pal->vtable == &s_dummy_pal_vtable) {
    pal_from(pal)->clipboard_pending_reads = count;
  }
}

void my_pal_dummy_set_time_step_ms(my_pal_t* pal, uint64_t step_ms) {
  if (pal != NULL && pal->vtable == &s_dummy_pal_vtable) {
    pal_from(pal)->time_step_ms = step_ms;
  }
}

void my_pal_dummy_reset_time_query_count(my_pal_t* pal) {
  if (pal != NULL && pal->vtable == &s_dummy_pal_vtable) {
    pal_from(pal)->time_query_count = 0u;
  }
}

uint32_t my_pal_dummy_time_query_count(const my_pal_t* pal) {
  if (pal == NULL || pal->vtable != &s_dummy_pal_vtable) return 0u;
  return ((const dummy_pal_t*)pal)->time_query_count;
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
