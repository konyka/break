#include "test_framework.h"
#include "mypal/screen/my_pal_screen.h"
#include "myui/my_ui_command.h"
#include <screen/screen.h>
#include <errno.h>
#include <stdint.h>

#define CHECK(x) do { \
  if (!(x)) { \
    printf("  FAIL: %s:%d: %s\n", __FILE__, __LINE__, #x); \
    g_test_fail++; \
  } \
} while (0)

typedef enum fault_t {
  FAULT_NONE = 0,
  FAULT_CONTEXT_CREATE,
  FAULT_EVENT_CREATE_FIRST,
  FAULT_EVENT_CREATE_SECOND,
  FAULT_EVENT_PROPERTY,
  FAULT_WINDOW_CREATE,
  FAULT_WINDOW_PROPERTY,
  FAULT_WINDOW_CREATE_BUFFERS,
  FAULT_WINDOW_DESTROY_BUFFERS,
  FAULT_DEQUEUE,
  FAULT_GET_POINTER,
  FAULT_GET_STRIDE,
  FAULT_POST,
  FAULT_SEND,
  FAULT_FLUSH,
  FAULT_TITLE,
  FAULT_GET_EVENT_EINTR,
  FAULT_GET_EVENT_ERROR
} fault_t;

static fault_t fault;
static int fault_property = -1;
static int injected_errno = EIO;
static int event_creates;
static int dequeue_calls;
static int enqueue_calls;
static int native_flag_errors;
static int destroyed_contexts;
static int destroyed_windows;
static int destroyed_events;
static int null_destroys;

static bool take_fault(fault_t expected) {
  if (fault != expected) return false;
  fault = FAULT_NONE;
  errno = injected_errno;
  return true;
}

static void reset_faults(void) {
  fault = FAULT_NONE;
  fault_property = -1;
  injected_errno = EIO;
  event_creates = 0;
  dequeue_calls = 0;
  enqueue_calls = 0;
  native_flag_errors = 0;
  destroyed_contexts = 0;
  destroyed_windows = 0;
  destroyed_events = 0;
  null_destroys = 0;
}

int __real_screen_create_context(screen_context_t *ctx, int flags);
int __real_screen_create_event(screen_event_t *event);
int __real_screen_set_event_property_iv(screen_event_t event, int property,
                                        const int *value);
int __real_screen_create_window(screen_window_t *window,
                                screen_context_t context);
int __real_screen_set_window_property_iv(screen_window_t window, int property,
                                         const int *value);
int __real_screen_set_window_property_cv(screen_window_t window, int property,
                                         int length, const char *value);
int __real_screen_create_window_buffers(screen_window_t window, int count);
int __real_screen_destroy_window_buffers(screen_window_t window);
int __real_screen_dequeue_window_render_buffer(screen_buffer_t *buffer,
                                               screen_window_t window, int flags);
int __real_screen_enqueue_render_buffer(screen_buffer_t buffer);
int __real_screen_get_buffer_property_pv(screen_buffer_t buffer, int property,
                                         void **value);
int __real_screen_get_buffer_property_iv(screen_buffer_t buffer, int property,
                                         int *value);
int __real_screen_post_window(screen_window_t window, screen_buffer_t buffer,
                              int count, const int *rects, int flags);
int __real_screen_send_event(screen_context_t context, screen_event_t event,
                             pid_t pid);
int __real_screen_flush_context(screen_context_t context, int flags);
int __real_screen_get_event(screen_context_t context, screen_event_t event,
                            uint64_t timeout);
int __real_screen_destroy_context(screen_context_t context);
int __real_screen_destroy_window(screen_window_t window);
int __real_screen_destroy_event(screen_event_t event);

int __wrap_screen_create_context(screen_context_t *ctx, int flags) {
  if (take_fault(FAULT_CONTEXT_CREATE)) return -1;
  return __real_screen_create_context(ctx, flags);
}

int __wrap_screen_create_event(screen_event_t *event) {
  event_creates++;
  if (take_fault(event_creates == 1 ? FAULT_EVENT_CREATE_FIRST
                                    : FAULT_EVENT_CREATE_SECOND)) {
    return -1;
  }
  return __real_screen_create_event(event);
}

int __wrap_screen_set_event_property_iv(screen_event_t event, int property,
                                        const int *value) {
  if (take_fault(FAULT_EVENT_PROPERTY)) return -1;
  return __real_screen_set_event_property_iv(event, property, value);
}

int __wrap_screen_create_window(screen_window_t *window,
                                screen_context_t context) {
  if (take_fault(FAULT_WINDOW_CREATE)) return -1;
  return __real_screen_create_window(window, context);
}

int __wrap_screen_set_window_property_iv(screen_window_t window, int property,
                                         const int *value) {
  if (property == fault_property && take_fault(FAULT_WINDOW_PROPERTY)) return -1;
  return __real_screen_set_window_property_iv(window, property, value);
}

int __wrap_screen_set_window_property_cv(screen_window_t window, int property,
                                         int length, const char *value) {
  if (take_fault(FAULT_TITLE)) return -1;
  return __real_screen_set_window_property_cv(window, property, length, value);
}

int __wrap_screen_create_window_buffers(screen_window_t window, int count) {
  if (take_fault(FAULT_WINDOW_CREATE_BUFFERS)) return -1;
  return __real_screen_create_window_buffers(window, count);
}

int __wrap_screen_destroy_window_buffers(screen_window_t window) {
  if (take_fault(FAULT_WINDOW_DESTROY_BUFFERS)) return -1;
  return __real_screen_destroy_window_buffers(window);
}

int __wrap_screen_dequeue_window_render_buffer(screen_buffer_t *buffer,
                                               screen_window_t window, int flags) {
  dequeue_calls++;
  if (flags != SCREEN_DONT_BLOCK) native_flag_errors++;
  if (take_fault(FAULT_DEQUEUE)) {
    errno = EWOULDBLOCK;
    return -1;
  }
  return __real_screen_dequeue_window_render_buffer(buffer, window, flags);
}

int __wrap_screen_enqueue_render_buffer(screen_buffer_t buffer) {
  enqueue_calls++;
  return __real_screen_enqueue_render_buffer(buffer);
}

int __wrap_screen_get_buffer_property_pv(screen_buffer_t buffer, int property,
                                         void **value) {
  if (take_fault(FAULT_GET_POINTER)) return -1;
  return __real_screen_get_buffer_property_pv(buffer, property, value);
}

int __wrap_screen_get_buffer_property_iv(screen_buffer_t buffer, int property,
                                         int *value) {
  if (take_fault(FAULT_GET_STRIDE)) return -1;
  return __real_screen_get_buffer_property_iv(buffer, property, value);
}

static int last_post_count;
static int last_post_rect[4];

int __wrap_screen_post_window(screen_window_t window, screen_buffer_t buffer,
                              int count, const int *rects, int flags) {
  if (flags != SCREEN_DONT_BLOCK) native_flag_errors++;
  last_post_count = count;
  if (count > 0 && rects != NULL) {
    memcpy(last_post_rect, rects, sizeof(last_post_rect));
  } else {
    memset(last_post_rect, 0, sizeof(last_post_rect));
  }
  if (take_fault(FAULT_POST)) return -1;
  return __real_screen_post_window(window, buffer, count, rects, flags);
}

int __wrap_screen_send_event(screen_context_t context, screen_event_t event,
                             pid_t pid) {
  if (take_fault(FAULT_SEND)) return -1;
  return __real_screen_send_event(context, event, pid);
}

int __wrap_screen_flush_context(screen_context_t context, int flags) {
  if (take_fault(FAULT_FLUSH)) return -1;
  return __real_screen_flush_context(context, flags);
}

int __wrap_screen_get_event(screen_context_t context, screen_event_t event,
                            uint64_t timeout) {
  if (take_fault(FAULT_GET_EVENT_EINTR)) {
    errno = EINTR;
    return -1;
  }
  if (take_fault(FAULT_GET_EVENT_ERROR)) return -1;
  return __real_screen_get_event(context, event, timeout);
}

int __wrap_screen_destroy_context(screen_context_t context) {
  if (context == NULL) {
    null_destroys++;
    return -1;
  }
  destroyed_contexts++;
  return __real_screen_destroy_context(context);
}

int __wrap_screen_destroy_window(screen_window_t window) {
  if (window == NULL) {
    null_destroys++;
    return -1;
  }
  destroyed_windows++;
  return __real_screen_destroy_window(window);
}

int __wrap_screen_destroy_event(screen_event_t event) {
  if (event == NULL) {
    null_destroys++;
    return -1;
  }
  destroyed_events++;
  return __real_screen_destroy_event(event);
}

typedef struct checked_allocator_t {
  my_allocator_t base;
  my_allocator_t* debug;
  size_t calls;
  size_t fail_at;
} checked_allocator_t;

static bool allocation_fails(checked_allocator_t* state) {
  state->calls++;
  return state->calls == state->fail_at;
}

static void* checked_alloc(void* context, size_t size) {
  if (allocation_fails((checked_allocator_t*)context)) return NULL;
  return my_mem_alloc(NULL, size);
}

static void* checked_calloc(void* context, size_t count, size_t size) {
  if (allocation_fails((checked_allocator_t*)context)) return NULL;
  return my_mem_calloc(NULL, count, size);
}

static void* checked_realloc(void* context, void* pointer, size_t size) {
  if (allocation_fails((checked_allocator_t*)context)) return NULL;
  return my_mem_realloc(NULL, pointer, size);
}

static void checked_free(void* context, void* pointer) {
  (void)context;
  my_mem_free(NULL, pointer);
}

static my_allocator_t* checked_open(checked_allocator_t* state) {
  memset(state, 0, sizeof(*state));
  state->fail_at = SIZE_MAX;
  state->base.ctx = state;
  state->base.alloc = checked_alloc;
  state->base.calloc = checked_calloc;
  state->base.realloc = checked_realloc;
  state->base.free = checked_free;
  state->debug = my_allocator_debug_create(&state->base);
  CHECK(state->debug != NULL);
  return state->debug;
}

static void checked_fail_next(checked_allocator_t* state) {
  state->fail_at = state->calls + 1u;
}

static void checked_close(checked_allocator_t* state) {
  if (state->debug != NULL) {
    CHECK(my_allocator_debug_leak_count(state->debug) == 0);
    my_allocator_debug_destroy(state->debug);
    state->debug = NULL;
  }
}

static void check_native_balance(int contexts, int windows, int events) {
  if (destroyed_contexts != contexts || destroyed_windows != windows ||
      destroyed_events != events || null_destroys != 0) {
    printf("  native cleanup actual=%d/%d/%d/null=%d expected=%d/%d/%d/0\n",
           destroyed_contexts, destroyed_windows, destroyed_events, null_destroys,
           contexts, windows, events);
  }
  CHECK(destroyed_contexts == contexts);
  CHECK(destroyed_windows == windows);
  CHECK(destroyed_events == events);
  CHECK(null_destroys == 0);
}

static void check_failed_pal(fault_t injected, int contexts, int events) {
  checked_allocator_t allocator;
  my_allocator_t* debug = checked_open(&allocator);
  my_pal_t* pal;
  reset_faults();
  fault = injected;
  pal = my_pal_create(debug);
  CHECK(pal == NULL);
  if (pal != NULL) my_pal_destroy(pal);
  check_native_balance(contexts, 0, events);
  checked_close(&allocator);
}

static void check_failed_window(fault_t injected, int property) {
  checked_allocator_t allocator;
  my_allocator_t* debug = checked_open(&allocator);
  my_pal_t* pal = my_pal_create(debug);
  my_pal_window_t* window;
  CHECK(pal != NULL);
  if (pal == NULL) {
    checked_close(&allocator);
    return;
  }
  reset_faults();
  fault = injected;
  fault_property = property;
  window = my_pal_window_create(pal, 64, 48, "failure window");
  CHECK(window == NULL);
  if (window != NULL) my_pal_window_destroy(window);
  my_pal_destroy(pal);
  check_native_balance(1, injected == FAULT_WINDOW_CREATE ? 0 : 1, 2);
  CHECK(null_destroys == 0);
  checked_close(&allocator);
}

typedef struct command_state_t {
  int executed;
  int destroyed;
} command_state_t;

static my_ret_t command_execute(void* context) {
  ((command_state_t*)context)->executed++;
  return MY_RET_OK;
}

static void command_destroy(void* context) {
  ((command_state_t*)context)->destroyed++;
}

static my_ret_t command_event(void* context, my_pal_window_t* window,
                              const my_event_t* event) {
  (void)context;
  (void)window;
  if (event->type == MY_EVENT_COMMAND) {
    my_ui_command_dispatch((my_ui_command_t*)event->u.command.data);
  }
  return MY_RET_OK;
}

static my_ret_t quit_timer(void* context) {
  (void)my_pal_main_loop_quit((my_pal_main_loop_t*)context);
  return MY_RET_FAIL;
}

typedef struct buffer_retry_state_t {
  my_pal_main_loop_t* loop;
  my_lcd_t* lcd;
  int attempts;
  int timer_errors;
  my_ret_t first_result;
  my_ret_t retry_result;
  my_ret_t post_result;
} buffer_retry_state_t;

static my_ret_t buffer_retry_timer(void* context) {
  buffer_retry_state_t* state = (buffer_retry_state_t*)context;
  state->attempts++;
  if (state->attempts == 1) {
    state->first_result = my_lcd_begin_frame(state->lcd, NULL);
    if (state->first_result == MY_RET_OK) {
      state->post_result = my_lcd_end_frame(state->lcd);
    }
    if (my_pal_main_loop_add_timer(state->loop, buffer_retry_timer, state, 1u) ==
        0u) {
      state->timer_errors++;
      (void)my_pal_main_loop_quit(state->loop);
    }
  } else {
    state->retry_result = my_lcd_begin_frame(state->lcd, NULL);
    if (state->retry_result == MY_RET_OK) {
      state->post_result = my_lcd_end_frame(state->lcd);
    }
    (void)my_pal_main_loop_quit(state->loop);
  }
  return MY_RET_FAIL;
}

TEST(screen_unavailable_buffer_allows_timer_progress)
{
  checked_allocator_t allocator;
  my_allocator_t* debug = checked_open(&allocator);
  my_pal_t* pal = my_pal_create(debug);
  my_pal_window_t* window = NULL;
  my_pal_main_loop_t* loop = NULL;
  buffer_retry_state_t state = {0};
  CHECK(pal != NULL);
  if (pal == NULL) {
    checked_close(&allocator);
    return;
  }
  reset_faults();
  window = my_pal_window_create(pal, 64, 48, "buffer pending");
  CHECK(window != NULL);
  loop = my_pal_main_loop_create(pal);
  CHECK(loop != NULL);
  state.loop = loop;
  if (window != NULL) state.lcd = my_pal_window_get_lcd(window);
  CHECK(state.lcd != NULL);
  if (state.lcd != NULL) {
    CHECK(my_lcd_begin_frame(state.lcd, NULL) == MY_RET_OK);
    CHECK(my_lcd_end_frame(state.lcd) == MY_RET_OK);
  }
  fault = FAULT_DEQUEUE;
  if (loop != NULL) {
    CHECK(my_pal_main_loop_add_timer(loop, buffer_retry_timer, &state, 1u) != 0u);
    CHECK(my_pal_main_loop_run(loop) == MY_RET_OK);
  }
  CHECK(state.attempts == 2);
  CHECK(state.timer_errors == 0);
  CHECK(state.first_result == MY_RET_PENDING);
  CHECK(state.retry_result == MY_RET_OK);
  CHECK(state.post_result == MY_RET_OK);
  CHECK(native_flag_errors == 0);
  if (loop != NULL) my_pal_main_loop_destroy(loop);
  if (window != NULL) my_pal_window_destroy(window);
  my_pal_destroy(pal);
  check_native_balance(1, 1, 2);
  checked_close(&allocator);
}

TEST(screen_post_pending_preserves_unposted_damage)
{
  const my_rect_t regions[3] = {{2, 3, 4, 5}, {20, 21, 4, 5}, {40, 35, 4, 5}};
  checked_allocator_t allocator;
  my_allocator_t* debug = checked_open(&allocator);
  my_pal_t* pal = my_pal_create(debug);
  my_pal_window_t* window = NULL;
  my_lcd_t* lcd = NULL;
  uint32_t stride = 0u;
  uint8_t* pixels = NULL;
  CHECK(pal != NULL);
  if (pal == NULL) {
    checked_close(&allocator);
    return;
  }
  reset_faults();
  window = my_pal_window_create(pal, 64, 48, "post pending history");
  CHECK(window != NULL);
  if (window != NULL) lcd = my_pal_window_get_lcd(window);
  CHECK(lcd != NULL);
  if (lcd == NULL) {
    if (window != NULL) my_pal_window_destroy(window);
    my_pal_destroy(pal);
    checked_close(&allocator);
    return;
  }
  CHECK(my_lcd_begin_frame(lcd, &regions[0]) == MY_RET_OK);
  CHECK(my_lcd_fill_rect(lcd, &regions[0], my_color_rgba(31, 31, 31, 255)) ==
        MY_RET_OK);
  injected_errno = EWOULDBLOCK;
  fault = FAULT_POST;
  CHECK(my_lcd_end_frame(lcd) == MY_RET_PENDING);
  CHECK(my_pal_screen_test_post_count(window) == 0u);
  CHECK(my_lcd_begin_frame(lcd, &regions[1]) == MY_RET_OK);
  pixels = my_lcd_get_buffer(lcd);
  stride = my_lcd_get_stride(lcd);
  CHECK(pixels != NULL && stride >= 64u * 4u);
  if (pixels != NULL && stride >= 64u * 4u) {
    CHECK(pixels[(size_t)regions[0].y * stride + (size_t)regions[0].x * 4u] ==
          31u);
  }
  CHECK(my_lcd_fill_rect(lcd, &regions[1], my_color_rgba(47, 47, 47, 255)) ==
        MY_RET_OK);
  CHECK(my_lcd_end_frame(lcd) == MY_RET_OK);
  CHECK(last_post_count == 1);
  CHECK(last_post_rect[0] == 2 && last_post_rect[1] == 3 &&
        last_post_rect[2] == 22 && last_post_rect[3] == 23);
  CHECK(my_lcd_begin_frame(lcd, &regions[2]) == MY_RET_OK);
  pixels = my_lcd_get_buffer(lcd);
  stride = my_lcd_get_stride(lcd);
  CHECK(pixels != NULL && stride >= 64u * 4u);
  if (pixels != NULL && stride >= 64u * 4u) {
    CHECK(pixels[(size_t)regions[0].y * stride + (size_t)regions[0].x * 4u] ==
          31u);
    CHECK(pixels[(size_t)regions[1].y * stride + (size_t)regions[1].x * 4u] ==
          47u);
  }
  CHECK(my_lcd_fill_rect(lcd, &regions[2], my_color_rgba(63, 63, 63, 255)) ==
        MY_RET_OK);
  CHECK(my_lcd_end_frame(lcd) == MY_RET_OK);
  CHECK(my_pal_screen_test_post_count(window) == 2u);
  CHECK(native_flag_errors == 0);
  CHECK(enqueue_calls == 0);
  my_pal_window_destroy(window);
  my_pal_destroy(pal);
  check_native_balance(1, 1, 2);
  checked_close(&allocator);
}

TEST(screen_pal_creation_failures_clean_up)
{
  check_failed_pal(FAULT_CONTEXT_CREATE, 0, 0);
  check_failed_pal(FAULT_EVENT_CREATE_FIRST, 1, 0);
  check_failed_pal(FAULT_EVENT_CREATE_SECOND, 1, 1);
  check_failed_pal(FAULT_EVENT_PROPERTY, 1, 2);
}

TEST(screen_window_creation_failures_clean_up)
{
  check_failed_window(FAULT_WINDOW_CREATE, -1);
  check_failed_window(FAULT_WINDOW_PROPERTY, SCREEN_PROPERTY_SIZE);
  check_failed_window(FAULT_WINDOW_PROPERTY, SCREEN_PROPERTY_FORMAT);
  check_failed_window(FAULT_WINDOW_PROPERTY, SCREEN_PROPERTY_USAGE);
  check_failed_window(FAULT_WINDOW_PROPERTY, SCREEN_PROPERTY_VISIBLE);
  check_failed_window(FAULT_WINDOW_CREATE_BUFFERS, -1);
  check_failed_window(FAULT_DEQUEUE, -1);
  check_failed_window(FAULT_GET_POINTER, -1);
  check_failed_window(FAULT_GET_STRIDE, -1);
}

TEST(screen_window_oom_cleans_up)
{
  size_t i;
  for (i = 0; i < 5u; ++i) {
    checked_allocator_t allocator;
    my_allocator_t* debug = checked_open(&allocator);
    my_pal_t* pal = my_pal_create(debug);
    my_pal_window_t* window;
    CHECK(pal != NULL);
    if (pal == NULL) {
      checked_close(&allocator);
      continue;
    }
    reset_faults();
    allocator.fail_at = allocator.calls + i + 1u;
    window = my_pal_window_create(pal, 64, 48, "OOM window");
    CHECK(window == NULL);
    if (window != NULL) my_pal_window_destroy(window);
    CHECK(my_allocator_debug_leak_count(debug) == 1);
    my_pal_destroy(pal);
    if (destroyed_windows != (i == 0u ? 0 : 1)) {
      printf("  OOM iteration=%zu destroyed_windows=%d\n", i, destroyed_windows);
    }
    check_native_balance(1, i == 0u ? 0 : 1, 2);
    checked_close(&allocator);
  }
}

TEST(screen_title_failures_preserve_storage)
{
  checked_allocator_t allocator;
  my_allocator_t* debug = checked_open(&allocator);
  my_pal_t* pal = my_pal_create(debug);
  my_pal_window_t* window;
  CHECK(pal != NULL);
  if (pal == NULL) {
    checked_close(&allocator);
    return;
  }
  reset_faults();
  window = my_pal_window_create(pal, 64, 48, "original");
  CHECK(window != NULL);
  if (window == NULL) {
    my_pal_destroy(pal);
    checked_close(&allocator);
    return;
  }
  fault = FAULT_TITLE;
  CHECK(my_pal_window_set_title(window, "replacement") == MY_RET_FAIL);
  fault = FAULT_FLUSH;
  CHECK(my_pal_window_set_title(window, "replacement") == MY_RET_FAIL);
  checked_fail_next(&allocator);
  CHECK(my_pal_window_set_title(window, "replacement") == MY_RET_OOM);
  CHECK(my_allocator_debug_leak_count(debug) == 6);
  CHECK(my_pal_window_set_title(window, "replacement") == MY_RET_OK);
  CHECK(my_allocator_debug_leak_count(debug) == 6);
  my_pal_window_destroy(window);
  my_pal_destroy(pal);
  check_native_balance(1, 1, 2);
  checked_close(&allocator);
}

TEST(screen_loop_oom_cleans_up)
{
  size_t i;
  for (i = 0; i < 4u; ++i) {
    checked_allocator_t allocator;
    my_allocator_t* debug = checked_open(&allocator);
    my_pal_t* pal = my_pal_create(debug);
    my_pal_main_loop_t* loop;
    CHECK(pal != NULL);
    if (pal == NULL) {
      checked_close(&allocator);
      continue;
    }
    checked_fail_next(&allocator);
    loop = my_pal_main_loop_create(pal);
    CHECK(loop == NULL);
    if (loop != NULL) my_pal_main_loop_destroy(loop);
    CHECK(my_allocator_debug_leak_count(debug) == 1);
    my_pal_destroy(pal);
    CHECK(my_allocator_debug_leak_count(debug) == 0);
    checked_close(&allocator);
  }
}

TEST(screen_frame_failures_retry_without_buffer_leaks)
{
  checked_allocator_t allocator;
  my_allocator_t* debug = checked_open(&allocator);
  my_pal_t* pal = my_pal_create(debug);
  my_pal_window_t* window;
  my_lcd_t* lcd;
  CHECK(pal != NULL);
  if (pal == NULL) {
    checked_close(&allocator);
    return;
  }
  reset_faults();
  window = my_pal_window_create(pal, 64, 48, "frame failures");
  CHECK(window != NULL);
  if (window == NULL) {
    my_pal_destroy(pal);
    checked_close(&allocator);
    return;
  }
  lcd = my_pal_window_get_lcd(window);
  CHECK(lcd != NULL);
  fault = FAULT_POST;
  CHECK(my_lcd_begin_frame(lcd, NULL) == MY_RET_OK);
  CHECK(my_lcd_end_frame(lcd) == MY_RET_FAIL);
  CHECK(my_pal_screen_test_post_count(window) == 0u);
  CHECK(dequeue_calls == 1);
  CHECK(my_lcd_begin_frame(lcd, NULL) == MY_RET_OK);
  CHECK(my_lcd_end_frame(lcd) == MY_RET_OK);
  CHECK(my_pal_screen_test_post_count(window) == 1u);
  CHECK(dequeue_calls == 1);
  fault = FAULT_DEQUEUE;
  CHECK(my_lcd_begin_frame(lcd, NULL) == MY_RET_PENDING);
  CHECK(my_lcd_begin_frame(lcd, NULL) == MY_RET_OK);
  CHECK(my_lcd_end_frame(lcd) == MY_RET_OK);
  CHECK(my_pal_screen_test_post_count(window) == 2u);
  CHECK(enqueue_calls == 0u);
  CHECK(my_lcd_begin_frame(lcd, NULL) == MY_RET_OK);
  CHECK(my_lcd_end_frame(lcd) == MY_RET_OK);
  CHECK(my_pal_screen_test_post_count(window) == 3u);
  my_pal_window_destroy(window);
  my_pal_destroy(pal);
  check_native_balance(1, 1, 2);
  checked_close(&allocator);
}

TEST(screen_cold_buffer_failures_recover_on_resize)
{
  const fault_t cold_faults[2] = {FAULT_GET_POINTER, FAULT_GET_STRIDE};
  uint32_t i;
  for (i = 0u; i < 2u; ++i) {
    checked_allocator_t allocator;
    my_allocator_t* debug = checked_open(&allocator);
    my_pal_t* pal = my_pal_create(debug);
    my_pal_window_t* window;
    my_lcd_t* lcd;
    CHECK(pal != NULL);
    if (pal == NULL) {
      checked_close(&allocator);
      continue;
    }
    reset_faults();
    window = my_pal_window_create(pal, 64, 48, "cold buffer failures");
    CHECK(window != NULL);
    if (window == NULL) {
      my_pal_destroy(pal);
      checked_close(&allocator);
      continue;
    }
    lcd = my_pal_window_get_lcd(window);
    CHECK(lcd != NULL);
    if (lcd != NULL) {
      CHECK(my_lcd_begin_frame(lcd, NULL) == MY_RET_OK);
      CHECK(my_lcd_end_frame(lcd) == MY_RET_OK);
    }
    reset_faults();
    fault = cold_faults[i];
    CHECK(my_pal_window_resize(window, 32, 24) == MY_RET_FAIL);
    CHECK(my_pal_window_get_lcd(window) == NULL);
    CHECK(enqueue_calls == 1u);
    CHECK(my_pal_window_resize(window, 32, 24) == MY_RET_OK);
    lcd = my_pal_window_get_lcd(window);
    CHECK(lcd != NULL && my_lcd_get_width(lcd) == 32u);
    if (lcd != NULL) {
      CHECK(my_lcd_begin_frame(lcd, NULL) == MY_RET_OK);
      CHECK(my_lcd_end_frame(lcd) == MY_RET_OK);
    }
    my_pal_window_destroy(window);
    my_pal_destroy(pal);
    check_native_balance(1, 1, 2);
    checked_close(&allocator);
  }
}

TEST(screen_resize_failures_have_safe_recovery)
{
  checked_allocator_t allocator;
  my_allocator_t* debug = checked_open(&allocator);
  my_pal_t* pal = my_pal_create(debug);
  my_pal_window_t* window;
  my_lcd_t* lcd;
  int32_t width = 0;
  int32_t height = 0;
  CHECK(pal != NULL);
  if (pal == NULL) {
    checked_close(&allocator);
    return;
  }
  reset_faults();
  window = my_pal_window_create(pal, 64, 48, "resize failures");
  CHECK(window != NULL);
  if (window == NULL) {
    my_pal_destroy(pal);
    checked_close(&allocator);
    return;
  }
  lcd = my_pal_window_get_lcd(window);
  fault = FAULT_WINDOW_PROPERTY;
  fault_property = SCREEN_PROPERTY_SIZE;
  CHECK(my_pal_window_resize(window, 32, 24) == MY_RET_FAIL);
  CHECK(my_pal_window_get_lcd(window) == lcd);
  CHECK(my_lcd_get_width(lcd) == 64u);
  fault = FAULT_WINDOW_CREATE_BUFFERS;
  CHECK(my_pal_window_resize(window, 32, 24) == MY_RET_FAIL);
  CHECK(my_pal_window_get_lcd(window) == NULL);
  CHECK(my_lcd_begin_frame(lcd, NULL) == MY_RET_FAIL);
  CHECK(my_lcd_get_buffer(lcd) == NULL);
  CHECK(my_pal_window_resize(window, 32, 24) == MY_RET_OK);
  lcd = my_pal_window_get_lcd(window);
  CHECK(lcd != NULL && my_lcd_get_width(lcd) == 32u);
  fault = FAULT_WINDOW_PROPERTY;
  fault_property = SCREEN_PROPERTY_BUFFER_SIZE;
  CHECK(my_pal_window_resize(window, 40, 30) == MY_RET_FAIL);
  CHECK(my_pal_window_get_lcd(window) == NULL);
  CHECK(my_lcd_begin_frame(lcd, NULL) == MY_RET_FAIL);
  CHECK(my_lcd_get_buffer(lcd) == NULL);
  CHECK(my_pal_window_resize(window, 40, 30) == MY_RET_OK);
  lcd = my_pal_window_get_lcd(window);
  CHECK(lcd != NULL && my_lcd_get_width(lcd) == 40u);
  fault = FAULT_WINDOW_DESTROY_BUFFERS;
  CHECK(my_pal_window_resize(window, 48, 32) == MY_RET_FAIL);
  CHECK(my_pal_window_get_lcd(window) == NULL);
  CHECK(my_pal_window_resize(window, 48, 32) == MY_RET_OK);
  lcd = my_pal_window_get_lcd(window);
  CHECK(lcd != NULL && my_lcd_get_width(lcd) == 48u);
  checked_fail_next(&allocator);
  CHECK(my_pal_window_resize(window, 40, 30) == MY_RET_OOM);
  CHECK(my_pal_window_get_lcd(window) == NULL);
  CHECK(my_pal_window_resize(window, 40, 30) == MY_RET_OK);
  lcd = my_pal_window_get_lcd(window);
  CHECK(lcd != NULL && my_lcd_get_width(lcd) == 40u);
  fault = FAULT_FLUSH;
  CHECK(my_pal_window_resize(window, 20, 20) == MY_RET_FAIL);
  CHECK(my_pal_window_get_lcd(window) == NULL);
  CHECK(my_pal_window_resize(window, 20, 20) == MY_RET_OK);
  lcd = my_pal_window_get_lcd(window);
  CHECK(lcd != NULL && my_lcd_get_width(lcd) == 20u);
  CHECK(my_pal_window_get_size(window, &width, &height) == MY_RET_OK);
  CHECK(width == 20 && height == 20);
  my_pal_window_destroy(window);
  my_pal_destroy(pal);
  check_native_balance(1, 1, 2);
  checked_close(&allocator);
}

TEST(screen_queue_oom_does_not_release_caller_command)
{
  checked_allocator_t allocator;
  my_allocator_t* debug = checked_open(&allocator);
  my_pal_t* pal = my_pal_create(debug);
  my_pal_main_loop_t* loop;
  command_state_t state = {0, 0};
  my_ui_command_t* command;
  CHECK(pal != NULL);
  if (pal == NULL) {
    checked_close(&allocator);
    return;
  }
  loop = my_pal_main_loop_create(pal);
  CHECK(loop != NULL);
  command = my_ui_command_create(NULL, command_execute, &state, command_destroy);
  CHECK(command != NULL);
  checked_fail_next(&allocator);
  CHECK(my_ui_command_submit(loop, command) == MY_RET_OOM);
  CHECK(state.destroyed == 0);
  my_ui_command_unref(command);
  CHECK(state.destroyed == 1);
  CHECK(state.executed == 0);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
  checked_close(&allocator);
}

TEST(screen_queue_wake_failure_does_not_double_release)
{
  checked_allocator_t allocator;
  my_allocator_t* debug = checked_open(&allocator);
  my_pal_t* pal = my_pal_create(debug);
  my_pal_main_loop_t* loop;
  command_state_t state = {0, 0};
  my_ui_command_t* command;
  CHECK(pal != NULL);
  if (pal == NULL) {
    checked_close(&allocator);
    return;
  }
  loop = my_pal_main_loop_create(pal);
  CHECK(loop != NULL);
  command = my_ui_command_create(NULL, command_execute, &state, command_destroy);
  CHECK(command != NULL);
  fault = FAULT_SEND;
  CHECK(my_ui_command_submit(loop, command) == MY_RET_FAIL);
  CHECK(state.destroyed == 0);
  my_ui_command_unref(command);
  CHECK(my_pal_main_loop_add_timer(loop, quit_timer, loop, 1u) != 0u);
  CHECK(my_pal_main_loop_run(loop) == MY_RET_OK);
  CHECK(state.destroyed == 1);
  my_pal_main_loop_destroy(loop);
  CHECK(state.destroyed == 1);
  CHECK(state.executed == 0);
  my_pal_destroy(pal);
  checked_close(&allocator);
}

TEST(screen_queue_destroy_releases_pending_command)
{
  checked_allocator_t allocator;
  my_allocator_t* debug = checked_open(&allocator);
  my_pal_t* pal = my_pal_create(debug);
  my_pal_main_loop_t* loop;
  command_state_t state = {0, 0};
  my_ui_command_t* command;
  CHECK(pal != NULL);
  if (pal == NULL) {
    checked_close(&allocator);
    return;
  }
  (void)my_pal_set_event_handler(pal, command_event, NULL);
  loop = my_pal_main_loop_create(pal);
  CHECK(loop != NULL);
  command = my_ui_command_create(NULL, command_execute, &state, command_destroy);
  CHECK(command != NULL);
  CHECK(my_ui_command_submit(loop, command) == MY_RET_OK);
  my_ui_command_unref(command);
  my_pal_main_loop_destroy(loop);
  CHECK(state.destroyed == 1);
  CHECK(state.executed == 0);
  my_pal_destroy(pal);
  checked_close(&allocator);
}

TEST(screen_get_event_eintr_and_error_paths)
{
  checked_allocator_t allocator;
  my_allocator_t* debug = checked_open(&allocator);
  my_pal_t* pal = my_pal_create(debug);
  my_pal_main_loop_t* loop;
  CHECK(pal != NULL);
  if (pal == NULL) {
    checked_close(&allocator);
    return;
  }
  reset_faults();
  loop = my_pal_main_loop_create(pal);
  CHECK(loop != NULL);
  CHECK(my_pal_main_loop_add_timer(loop, quit_timer, loop, 1u) != 0u);
  fault = FAULT_GET_EVENT_EINTR;
  CHECK(my_pal_main_loop_run(loop) == MY_RET_OK);
  my_pal_main_loop_destroy(loop);
  loop = my_pal_main_loop_create(pal);
  CHECK(loop != NULL);
  fault = FAULT_GET_EVENT_ERROR;
  CHECK(my_pal_main_loop_run(loop) == MY_RET_FAIL);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
  check_native_balance(1, 0, 2);
  checked_close(&allocator);
}

typedef struct reentrant_command_state_t {
  my_pal_main_loop_t* loop;
  command_state_t child;
  my_ret_t child_submit_result;
} reentrant_command_state_t;

static my_ret_t reentrant_execute(void* context) {
  (void)context;
  return MY_RET_OK;
}

static void reentrant_destroy(void* context) {
  reentrant_command_state_t* state = (reentrant_command_state_t*)context;
  my_ui_command_t* child = my_ui_command_create(
      NULL, command_execute, &state->child, command_destroy);
  if (child == NULL) {
    state->child_submit_result = MY_RET_OOM;
    return;
  }
  state->child_submit_result = my_ui_command_submit(state->loop, child);
  my_ui_command_unref(child);
}

TEST(screen_queue_destroy_unlocks_before_payload_destructors)
{
  checked_allocator_t allocator;
  my_allocator_t* debug = checked_open(&allocator);
  my_pal_t* pal = my_pal_create(debug);
  my_pal_main_loop_t* loop;
  reentrant_command_state_t state = {0};
  my_ui_command_t* command;
  CHECK(pal != NULL);
  if (pal == NULL) {
    checked_close(&allocator);
    return;
  }
  loop = my_pal_main_loop_create(pal);
  CHECK(loop != NULL);
  state.loop = loop;
  command = my_ui_command_create(NULL, reentrant_execute, &state,
                                 reentrant_destroy);
  CHECK(command != NULL);
  CHECK(my_ui_command_submit(loop, command) == MY_RET_OK);
  my_ui_command_unref(command);
  my_pal_main_loop_destroy(loop);
  CHECK(state.child_submit_result == MY_RET_PENDING);
  CHECK(state.child.destroyed == 1);
  CHECK(state.child.executed == 0);
  my_pal_destroy(pal);
  checked_close(&allocator);
}

int main(int argc, char** argv)
{
  my_pal_t* probe;
  const char* test_filter = argc > 1 ? argv[1] : NULL;
  if (argc > 2) return 2;
  setvbuf(stdout, NULL, _IONBF, 0);
  reset_faults();
  probe = my_pal_create(NULL);
  if (probe == NULL) {
    printf("SKIP: no usable QNX Screen service\n");
    return getenv("BREAK_QNX_SCREEN_REQUIRED") != NULL ? 1 : 77;
  }
  my_pal_destroy(probe);
#define RUN_SCREEN_TEST(name) do { \
  if (test_filter == NULL || strcmp(test_filter, #name) == 0) RUN_TEST(name); \
} while (0)
  printf("=== Running Tests ===\n");
  RUN_SCREEN_TEST(screen_pal_creation_failures_clean_up);
  RUN_SCREEN_TEST(screen_window_creation_failures_clean_up);
  RUN_SCREEN_TEST(screen_window_oom_cleans_up);
  RUN_SCREEN_TEST(screen_title_failures_preserve_storage);
  RUN_SCREEN_TEST(screen_loop_oom_cleans_up);
  RUN_SCREEN_TEST(screen_frame_failures_retry_without_buffer_leaks);
  RUN_SCREEN_TEST(screen_unavailable_buffer_allows_timer_progress);
  RUN_SCREEN_TEST(screen_post_pending_preserves_unposted_damage);
  RUN_SCREEN_TEST(screen_cold_buffer_failures_recover_on_resize);
  RUN_SCREEN_TEST(screen_resize_failures_have_safe_recovery);
  RUN_SCREEN_TEST(screen_queue_oom_does_not_release_caller_command);
  RUN_SCREEN_TEST(screen_queue_wake_failure_does_not_double_release);
  RUN_SCREEN_TEST(screen_queue_destroy_releases_pending_command);
  RUN_SCREEN_TEST(screen_queue_destroy_unlocks_before_payload_destructors);
  RUN_SCREEN_TEST(screen_get_event_eintr_and_error_paths);
  printf("\n=== Results: %d passed, %d failed, %d total ===\n",
         g_test_pass, g_test_fail, g_test_count);
  return g_test_fail > 0 ? 1 : 0;
}
