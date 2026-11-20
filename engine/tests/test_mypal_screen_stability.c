#include "test_framework.h"
#include "mypal/screen/my_pal_screen.h"
#include "myui/my_ui_command.h"
#include <core/platform_thread.h>
#include <platform/time.h>
#include <screen/screen.h>
#include <errno.h>
#include <pthread.h>
#include <stdatomic.h>
#include <time.h>

#define SCREEN_LIFECYCLE_ROUNDS 500u
#define SCREEN_LIFECYCLE_MAX_FAILED_ROUNDS 8u
#define SCREEN_PRODUCER_COUNT 4u
#define SCREEN_DEFAULT_STRESS_MS 10000u
#define SCREEN_MIN_STRESS_MS 1000u
#define SCREEN_MAX_STRESS_MS 60000u
#define SCREEN_FRAME_INTERVAL_MS 16u
#define SCREEN_WATCHDOG_GRACE_MS 5000u
#define SCREEN_BEGIN_RETRY_LIMIT 2000u
#define SCREEN_BEGIN_TIMEOUT_US 250000u
#define SCREEN_TEST_WIDTH 96u
#define SCREEN_TEST_HEIGHT 64u

#define CHECK(x) do { \
  if (!(x)) { \
    printf("  FAIL: %s:%d: %s\n", __FILE__, __LINE__, #x); \
    g_test_fail++; \
  } \
} while (0)

typedef struct native_stats_t {
  uint64_t context_created;
  uint64_t context_destroyed;
  uint64_t event_created;
  uint64_t event_destroyed;
  uint64_t window_created;
  uint64_t window_destroyed;
  uint64_t buffers_created;
  uint64_t buffers_destroyed;
  uint64_t posts_accepted;
} native_stats_t;

static native_stats_t g_native;

typedef struct native_call_diag_t {
  atomic_ullong calls;
  atomic_ullong errors;
  atomic_ullong would_block;
  atomic_ullong total_us;
  atomic_ullong max_us;
  atomic_int last_error;
} native_call_diag_t;

static native_call_diag_t g_send_diag;
static native_call_diag_t g_post_diag;
static native_call_diag_t g_dequeue_diag;
static native_call_diag_t g_get_event_diag;

static void native_diag_record(native_call_diag_t* diag, int result, int error,
                               uint64_t elapsed_us) {
  uint64_t previous;
  atomic_fetch_add_explicit(&diag->calls, 1ull, memory_order_relaxed);
  atomic_fetch_add_explicit(&diag->total_us, elapsed_us, memory_order_relaxed);
  previous = atomic_load_explicit(&diag->max_us, memory_order_relaxed);
  while (elapsed_us > previous &&
         !atomic_compare_exchange_weak_explicit(&diag->max_us, &previous,
                                                elapsed_us,
                                                memory_order_relaxed,
                                                memory_order_relaxed)) {
  }
  if (result != 0) {
    atomic_fetch_add_explicit(&diag->errors, 1ull, memory_order_relaxed);
    if (error == EWOULDBLOCK) {
      atomic_fetch_add_explicit(&diag->would_block, 1ull, memory_order_relaxed);
    }
    atomic_store_explicit(&diag->last_error, error, memory_order_relaxed);
  }
  errno = error;
}

static void native_diag_reset(native_call_diag_t* diag) {
  atomic_store_explicit(&diag->calls, 0ull, memory_order_relaxed);
  atomic_store_explicit(&diag->errors, 0ull, memory_order_relaxed);
  atomic_store_explicit(&diag->would_block, 0ull, memory_order_relaxed);
  atomic_store_explicit(&diag->total_us, 0ull, memory_order_relaxed);
  atomic_store_explicit(&diag->max_us, 0ull, memory_order_relaxed);
  atomic_store_explicit(&diag->last_error, 0, memory_order_relaxed);
}

static void native_diag_reset_all(void) {
  native_diag_reset(&g_send_diag);
  native_diag_reset(&g_post_diag);
  native_diag_reset(&g_dequeue_diag);
  native_diag_reset(&g_get_event_diag);
}

static void native_diag_print(const char* name, native_call_diag_t* diag) {
  printf("screen_stress_native_call,name=%s,calls=%llu,errors=%llu,"
         "would_block=%llu,total_us=%llu,max_us=%llu,last_error=%d\n", name,
         (unsigned long long)atomic_load_explicit(&diag->calls,
                                                  memory_order_relaxed),
         (unsigned long long)atomic_load_explicit(&diag->errors,
                                                  memory_order_relaxed),
         (unsigned long long)atomic_load_explicit(&diag->would_block,
                                                  memory_order_relaxed),
         (unsigned long long)atomic_load_explicit(&diag->total_us,
                                                  memory_order_relaxed),
         (unsigned long long)atomic_load_explicit(&diag->max_us,
                                                  memory_order_relaxed),
         atomic_load_explicit(&diag->last_error, memory_order_relaxed));
}

static int native_count_success(int result, uint64_t* counter) {
  int error = errno;
  if (result == 0) (*counter)++;
  errno = error;
  return result;
}

int __real_screen_create_context(screen_context_t* context, int flags);
int __real_screen_destroy_context(screen_context_t context);
int __real_screen_create_event(screen_event_t* event);
int __real_screen_destroy_event(screen_event_t event);
int __real_screen_create_window(screen_window_t* window,
                                screen_context_t context);
int __real_screen_destroy_window(screen_window_t window);
int __real_screen_create_window_buffers(screen_window_t window, int count);
int __real_screen_destroy_window_buffers(screen_window_t window);
int __real_screen_post_window(screen_window_t window, screen_buffer_t buffer,
                              int count, const int* rects, int flags);

int __wrap_screen_create_context(screen_context_t* context, int flags) {
  return native_count_success(__real_screen_create_context(context, flags),
                              &g_native.context_created);
}

int __wrap_screen_destroy_context(screen_context_t context) {
  return native_count_success(__real_screen_destroy_context(context),
                              &g_native.context_destroyed);
}

int __wrap_screen_create_event(screen_event_t* event) {
  return native_count_success(__real_screen_create_event(event),
                              &g_native.event_created);
}

int __wrap_screen_destroy_event(screen_event_t event) {
  return native_count_success(__real_screen_destroy_event(event),
                              &g_native.event_destroyed);
}

int __wrap_screen_create_window(screen_window_t* window,
                                screen_context_t context) {
  return native_count_success(__real_screen_create_window(window, context),
                              &g_native.window_created);
}

int __wrap_screen_destroy_window(screen_window_t window) {
  return native_count_success(__real_screen_destroy_window(window),
                              &g_native.window_destroyed);
}

int __wrap_screen_create_window_buffers(screen_window_t window, int count) {
  return native_count_success(__real_screen_create_window_buffers(window, count),
                              &g_native.buffers_created);
}

int __wrap_screen_destroy_window_buffers(screen_window_t window) {
  return native_count_success(__real_screen_destroy_window_buffers(window),
                              &g_native.buffers_destroyed);
}

int __wrap_screen_post_window(screen_window_t window, screen_buffer_t buffer,
                              int count, const int* rects, int flags) {
  uint64_t started_us = time_microseconds();
  int result = native_count_success(
      __real_screen_post_window(window, buffer, count, rects, flags),
      &g_native.posts_accepted);
  int error = errno;
  native_diag_record(&g_post_diag, result, error,
                     time_microseconds() - started_us);
  return result;
}

#ifdef SCREEN_STABILITY_NATIVE_DIAG
int __real_screen_send_event(screen_context_t context, screen_event_t event,
                             pid_t pid);
int __real_screen_dequeue_window_render_buffer(screen_buffer_t* buffer,
                                               screen_window_t window,
                                               int flags);
int __real_screen_get_event(screen_context_t context, screen_event_t event,
                            uint64_t timeout);

int __wrap_screen_send_event(screen_context_t context, screen_event_t event,
                             pid_t pid) {
  uint64_t started_us = time_microseconds();
  int result = __real_screen_send_event(context, event, pid);
  int error = errno;
  native_diag_record(&g_send_diag, result, error,
                     time_microseconds() - started_us);
  return result;
}

int __wrap_screen_dequeue_window_render_buffer(screen_buffer_t* buffer,
                                               screen_window_t window,
                                               int flags) {
  uint64_t started_us = time_microseconds();
  int result = __real_screen_dequeue_window_render_buffer(buffer, window, flags);
  int error = errno;
  native_diag_record(&g_dequeue_diag, result, error,
                     time_microseconds() - started_us);
  return result;
}

int __wrap_screen_get_event(screen_context_t context, screen_event_t event,
                            uint64_t timeout) {
  uint64_t started_us = time_microseconds();
  int result = __real_screen_get_event(context, event, timeout);
  int error = errno;
  native_diag_record(&g_get_event_diag, result, error,
                     time_microseconds() - started_us);
  return result;
}
#endif

static native_stats_t native_since(native_stats_t before) {
  native_stats_t delta;
  delta.context_created = g_native.context_created - before.context_created;
  delta.context_destroyed =
      g_native.context_destroyed - before.context_destroyed;
  delta.event_created = g_native.event_created - before.event_created;
  delta.event_destroyed = g_native.event_destroyed - before.event_destroyed;
  delta.window_created = g_native.window_created - before.window_created;
  delta.window_destroyed = g_native.window_destroyed - before.window_destroyed;
  delta.buffers_created = g_native.buffers_created - before.buffers_created;
  delta.buffers_destroyed = g_native.buffers_destroyed - before.buffers_destroyed;
  delta.posts_accepted = g_native.posts_accepted - before.posts_accepted;
  return delta;
}

static void native_add(native_stats_t* total, native_stats_t delta) {
  total->context_created += delta.context_created;
  total->context_destroyed += delta.context_destroyed;
  total->event_created += delta.event_created;
  total->event_destroyed += delta.event_destroyed;
  total->window_created += delta.window_created;
  total->window_destroyed += delta.window_destroyed;
  total->buffers_created += delta.buffers_created;
  total->buffers_destroyed += delta.buffers_destroyed;
  total->posts_accepted += delta.posts_accepted;
}

static uint32_t native_balance_errors(native_stats_t value,
                                      const char* scope) {
  uint32_t errors = 0;
#define CHECK_NATIVE_BALANCE(created, destroyed, name) \
  if (value.created != value.destroyed) { \
    printf("  native imbalance %s %s: created=%llu destroyed=%llu\n", scope, \
           name, (unsigned long long)value.created, \
           (unsigned long long)value.destroyed); \
    errors++; \
  }
  CHECK_NATIVE_BALANCE(context_created, context_destroyed, "context");
  CHECK_NATIVE_BALANCE(event_created, event_destroyed, "event");
  CHECK_NATIVE_BALANCE(window_created, window_destroyed, "window");
  CHECK_NATIVE_BALANCE(buffers_created, buffers_destroyed, "buffer-set");
#undef CHECK_NATIVE_BALANCE
  return errors;
}

static uint64_t rate_per_second(uint64_t count, uint64_t elapsed_us) {
  if (elapsed_us == 0u) return 0u;
  return count * 1000000u / elapsed_us;
}

typedef struct pixel_buffer_state_t {
  uint8_t* pixels;
} pixel_buffer_state_t;

typedef enum frame_result_t {
  FRAME_RESULT_OK = 0,
  FRAME_RESULT_PENDING,
  FRAME_RESULT_ERROR
} frame_result_t;

typedef struct frame_state_t {
  uint32_t width;
  uint32_t height;
  pixel_buffer_state_t buffers[2];
  uint32_t buffer_count;
  uint8_t outside_shade;
  uint8_t inside_shade;
  uint64_t frames;
  uint64_t prime_frames;
  uint64_t dirty_frames;
  uint64_t reused_frames;
  uint64_t pending;
  uint64_t begin_timeouts;
  uint64_t errors;
} frame_state_t;

static const my_rect_t s_dirty = {7, 9, 16, 12};

static bool pixel_has_shade(const uint8_t* pixel, uint8_t shade) {
  return pixel[0] == shade && pixel[1] == shade && pixel[2] == shade &&
         pixel[3] == 255u;
}

static frame_result_t draw_frame(frame_state_t* state, my_lcd_t* lcd,
                                 const my_rect_t* dirty, uint8_t shade,
                                 bool verify) {
  const my_rect_t full = {0, 0, (int32_t)state->width,
                          (int32_t)state->height};
  const my_rect_t* drawing = dirty != NULL ? dirty : &full;
  my_ret_t result = my_lcd_begin_frame(lcd, dirty);
  pixel_buffer_state_t* slot = NULL;
  uint8_t* pixels;
  uint32_t stride;
  uint32_t i;
  bool valid = true;
  if (result == MY_RET_PENDING) {
    state->pending++;
    return FRAME_RESULT_PENDING;
  }
  if (result != MY_RET_OK) {
    state->errors++;
    return FRAME_RESULT_ERROR;
  }

  pixels = my_lcd_get_buffer(lcd);
  stride = my_lcd_get_stride(lcd);
  if (pixels == NULL || stride < state->width * 4u ||
      my_lcd_get_width(lcd) != state->width ||
      my_lcd_get_height(lcd) != state->height) {
    valid = false;
  }
  for (i = 0u; valid && i < state->buffer_count; ++i) {
    if (state->buffers[i].pixels == pixels) {
      slot = &state->buffers[i];
      break;
    }
  }
  if (valid && slot == NULL) {
    if (!verify && state->buffer_count < 2u) {
      slot = &state->buffers[state->buffer_count++];
      slot->pixels = pixels;
    } else {
      valid = false;
    }
  }
  if (valid && verify) {
    size_t inside_offset = (size_t)s_dirty.y * stride + (size_t)s_dirty.x * 4u;
    if (state->buffer_count != 2u ||
        !pixel_has_shade(pixels, state->outside_shade) ||
        !pixel_has_shade(pixels + inside_offset, state->inside_shade)) {
      valid = false;
    }
  }
  if (valid) {
    result = my_lcd_fill_rect(lcd, drawing,
                              my_color_rgba(shade, shade, shade, 255u));
    if (result != MY_RET_OK) {
      valid = false;
    } else if (dirty != NULL) {
      state->inside_shade = shade;
    } else {
      state->outside_shade = shade;
      state->inside_shade = shade;
    }
  }
  if (!valid) state->errors++;

  result = my_lcd_end_frame(lcd);
  if (result != MY_RET_OK) {
    state->errors++;
    return FRAME_RESULT_ERROR;
  }
  state->frames++;
  if (!valid) return FRAME_RESULT_ERROR;
  if (dirty != NULL) {
    state->dirty_frames++;
    state->reused_frames++;
  } else {
    state->prime_frames++;
  }
  return FRAME_RESULT_OK;
}

static bool draw_frame_bounded(frame_state_t* state, my_lcd_t* lcd,
                               const my_rect_t* dirty, uint8_t shade,
                               bool verify) {
  uint64_t deadline_us = time_microseconds() + SCREEN_BEGIN_TIMEOUT_US;
  uint32_t attempt;
  for (attempt = 0u; attempt < SCREEN_BEGIN_RETRY_LIMIT; ++attempt) {
    frame_result_t result = draw_frame(state, lcd, dirty, shade, verify);
    if (result == FRAME_RESULT_OK) return true;
    if (result == FRAME_RESULT_ERROR) return false;
    if (time_microseconds() >= deadline_us) break;
    time_sleep_us(100u);
  }
  state->begin_timeouts++;
  state->errors++;
  return false;
}

typedef struct lifecycle_stats_t {
  uint32_t attempted;
  uint32_t succeeded;
  uint32_t failed;
  uint32_t live_allocation_errors;
  uint64_t frames;
  uint64_t posts;
  uint64_t errors;
  uint64_t elapsed_us;
  native_stats_t native;
} lifecycle_stats_t;

static void lifecycle_error(uint32_t* errors, uint32_t round,
                            const char* stage) {
  (*errors)++;
  printf("  lifecycle round=%u stage=%s failed\n", round, stage);
}

static bool lifecycle_round(uint32_t round, lifecycle_stats_t* stats) {
  static const int32_t sizes[4][2] = {
      {64, 48}, {80, 60}, {96, 64}, {72, 54}};
  const int32_t* initial = sizes[round % 4u];
  const int32_t* resized = sizes[(round + 1u) % 4u];
  my_allocator_t* debug = NULL;
  my_pal_t* pal = NULL;
  my_pal_main_loop_t* loop = NULL;
  my_pal_window_t* window = NULL;
  my_lcd_t* lcd = NULL;
  frame_state_t frames;
  native_stats_t before = g_native;
  native_stats_t delta;
  uint32_t errors = 0;
  uint32_t public_posts = 0u;
  int swap_interval = 0;
  bool full_lifecycle = false;
  bool ok;
  memset(&frames, 0, sizeof(frames));
  frames.width = (uint32_t)resized[0];
  frames.height = (uint32_t)resized[1];

  debug = my_allocator_debug_create(NULL);
  if (debug == NULL) {
    lifecycle_error(&errors, round, "debug allocator create");
    goto cleanup;
  }
  pal = my_pal_create(debug);
  if (pal == NULL || my_pal_screen_native_context(pal) == NULL) {
    lifecycle_error(&errors, round, "PAL create");
    goto cleanup;
  }
  loop = my_pal_main_loop_create(pal);
  if (loop == NULL) {
    lifecycle_error(&errors, round, "loop create");
    goto cleanup;
  }
  window = my_pal_window_create(pal, initial[0], initial[1],
                                "myui Screen stability lifecycle");
  if (window == NULL || my_pal_screen_native_window(window) == NULL) {
    lifecycle_error(&errors, round, "window create");
    goto cleanup;
  }
  {
    my_ret_t resize_result =
        my_pal_window_resize(window, resized[0], resized[1]);
    if (resize_result != MY_RET_OK) {
      int resize_error = errno;
      int native_size[2] = {0, 0};
      int size_result = screen_get_window_property_iv(
          (screen_window_t)my_pal_screen_native_window(window),
          SCREEN_PROPERTY_SIZE, native_size);
      printf("  lifecycle resize detail: result=%d errno=%d (%s) "
             "size_query=%d native_size=%dx%d requested=%dx%d\n",
             resize_result, resize_error, strerror(resize_error), size_result,
             native_size[0], native_size[1], resized[0], resized[1]);
      lifecycle_error(&errors, round, "resize");
      goto cleanup;
    }
  }
  if (screen_set_window_property_iv(
          (screen_window_t)my_pal_screen_native_window(window),
          SCREEN_PROPERTY_SWAP_INTERVAL, &swap_interval) != 0 ||
      screen_flush_context(
          (screen_context_t)my_pal_screen_native_context(pal), 0) != 0) {
    lifecycle_error(&errors, round, "swap interval zero");
    goto cleanup;
  }
  if (my_pal_window_show(window) != MY_RET_OK) {
    lifecycle_error(&errors, round, "show");
    goto cleanup;
  }
  lcd = my_pal_window_get_lcd(window);
  if (lcd == NULL) {
    lifecycle_error(&errors, round, "get LCD");
    goto cleanup;
  }
  if (!draw_frame_bounded(&frames, lcd, NULL, 32u, false) ||
      !draw_frame_bounded(&frames, lcd, NULL, 48u, false)) {
    printf("  lifecycle round=%u stage=prime failed\n", round);
    goto cleanup;
  }
  if (frames.buffer_count != 2u || frames.buffers[0].pixels ==
                                      frames.buffers[1].pixels) {
    lifecycle_error(&errors, round, "two distinct prime buffers");
    goto cleanup;
  }
  if (!draw_frame_bounded(&frames, lcd, &s_dirty, 64u, true)) {
    printf("  lifecycle round=%u stage=third frame failed\n", round);
    goto cleanup;
  }
  if (frames.frames != 3u || frames.dirty_frames != 1u ||
      frames.reused_frames != 1u) {
    lifecycle_error(&errors, round, "third-frame cache reuse");
    goto cleanup;
  }
  if (my_pal_main_loop_quit(loop) != MY_RET_OK) {
    lifecycle_error(&errors, round, "quit");
    goto cleanup;
  }
  if (my_pal_main_loop_run(loop) != MY_RET_OK) {
    lifecycle_error(&errors, round, "run");
    goto cleanup;
  }
  full_lifecycle = true;

cleanup:
  if (window != NULL) {
    public_posts = my_pal_screen_test_post_count(window);
    if ((uint64_t)public_posts != frames.frames) {
      lifecycle_error(&errors, round, "public post count");
    }
    my_pal_window_destroy(window);
  }
  if (loop != NULL) my_pal_main_loop_destroy(loop);
  if (pal != NULL) my_pal_destroy(pal);
  if (debug != NULL) {
    int live = my_allocator_debug_leak_count(debug);
    if (live != 0) {
      printf("  lifecycle round=%u live allocations after destroy=%d\n", round,
             live);
      errors++;
      stats->live_allocation_errors++;
    }
    my_allocator_debug_destroy(debug);
  }
  delta = native_since(before);
  errors += native_balance_errors(delta, "lifecycle");
  if ((uint64_t)public_posts != frames.frames ||
      delta.posts_accepted != frames.frames) {
    if (delta.posts_accepted != frames.frames) {
      lifecycle_error(&errors, round, "native post count");
    }
  }
  if (full_lifecycle &&
      (delta.context_created != 1u || delta.context_destroyed != 1u ||
       delta.event_created != 2u || delta.event_destroyed != 2u ||
       delta.window_created != 1u || delta.window_destroyed != 1u ||
       delta.buffers_created != 2u || delta.buffers_destroyed != 2u)) {
    lifecycle_error(&errors, round, "expected native handle counts");
  }
  if (frames.errors > UINT32_MAX - errors) {
    errors = UINT32_MAX;
  } else {
    errors += (uint32_t)frames.errors;
  }
  stats->frames += frames.frames;
  stats->posts += public_posts;
  stats->errors += errors;
  native_add(&stats->native, delta);
  ok = full_lifecycle && errors == 0u;
  return ok;
}

TEST(screen_500_complete_lifecycles)
{
  lifecycle_stats_t stats;
  uint32_t round;
  uint64_t started_us;
  memset(&stats, 0, sizeof(stats));
  started_us = time_microseconds();
  for (round = 0u; round < SCREEN_LIFECYCLE_ROUNDS; ++round) {
    bool ok;
    stats.attempted++;
    ok = lifecycle_round(round, &stats);
    if (ok) {
      stats.succeeded++;
    } else {
      stats.failed++;
      if (stats.failed >= SCREEN_LIFECYCLE_MAX_FAILED_ROUNDS) break;
    }
  }
  stats.elapsed_us = time_microseconds() - started_us;
  printf("screen_lifecycle_stability,requested_rounds=%u,attempted=%u,"
         "succeeded=%u,failed=%u,elapsed_us=%llu,frames=%llu,posts=%llu,"
         "native_posts=%llu,commands=0,errors=%llu,live_allocation_errors=%u,"
         "accepted_posts_per_second=%llu,display_fps=not_measured,"
         "swap_interval=0\n",
         SCREEN_LIFECYCLE_ROUNDS, stats.attempted, stats.succeeded,
         stats.failed, (unsigned long long)stats.elapsed_us,
         (unsigned long long)stats.frames, (unsigned long long)stats.posts,
         (unsigned long long)stats.native.posts_accepted,
         (unsigned long long)stats.errors, stats.live_allocation_errors,
         (unsigned long long)rate_per_second(stats.frames, stats.elapsed_us));
  printf("screen_lifecycle_native,contexts=%llu/%llu,events=%llu/%llu,"
         "windows=%llu/%llu,buffer_sets=%llu/%llu\n",
         (unsigned long long)stats.native.context_created,
         (unsigned long long)stats.native.context_destroyed,
         (unsigned long long)stats.native.event_created,
         (unsigned long long)stats.native.event_destroyed,
         (unsigned long long)stats.native.window_created,
         (unsigned long long)stats.native.window_destroyed,
         (unsigned long long)stats.native.buffers_created,
         (unsigned long long)stats.native.buffers_destroyed);
  CHECK(stats.attempted == SCREEN_LIFECYCLE_ROUNDS);
  CHECK(stats.succeeded == SCREEN_LIFECYCLE_ROUNDS);
  CHECK(stats.failed == 0u);
  CHECK(stats.errors == 0u);
  CHECK(stats.live_allocation_errors == 0u);
  CHECK(stats.frames == SCREEN_LIFECYCLE_ROUNDS * 3u);
  CHECK(stats.posts == stats.frames);
  CHECK(stats.native.posts_accepted == stats.frames);
  CHECK(native_balance_errors(stats.native, "lifecycle total") == 0u);
}

typedef struct stress_state_t stress_state_t;

typedef struct command_payload_t {
  stress_state_t* state;
  uint64_t sequence;
  uint32_t producer;
} command_payload_t;

typedef struct producer_stats_t {
  atomic_ullong created;
  atomic_ullong submitted;
  atomic_ullong executed;
  atomic_ullong destroyed;
  atomic_ullong failed;
  uint64_t fifo_next;
  uint64_t fifo_errors;
} producer_stats_t;

typedef struct producer_state_t {
  stress_state_t* state;
  uint32_t id;
  uint64_t next_sequence;
  PlatformThread thread;
} producer_state_t;

struct stress_state_t {
  my_pal_t* pal;
  my_pal_main_loop_t* loop;
  my_pal_window_t* window;
  my_lcd_t* lcd;
  frame_state_t frames;
  producer_state_t producers[SCREEN_PRODUCER_COUNT];
  producer_stats_t stats[SCREEN_PRODUCER_COUNT];
  uint32_t threads_created;
  atomic_bool stop_producers;
  uint32_t duration_ms;
  bool throttled;
  uint64_t started_us;
  uint64_t deadline_us;
  uint64_t run_elapsed_us;
  uint64_t total_elapsed_us;
  uint64_t deadline_notice_us;
  uint64_t deadline_quit_done_us;
  uint64_t watchdog_fire_us;
  uint64_t watchdog_quit_done_us;
  uint64_t first_run_returned_us;
  uint64_t second_run_elapsed_us;
  my_ret_t deadline_quit_result;
  my_ret_t first_run_result;
  my_ret_t second_run_result;
  uint8_t next_shade;
  bool deadline_reached;
  uint32_t setup_errors;
  uint32_t run_errors;
  uint32_t control_errors;
  uint32_t handler_errors;
  uint32_t validation_errors;
  uint32_t public_posts;
  native_stats_t native;
  PlatformThread watchdog_thread;
  PlatformMutex watchdog_mutex;
  PlatformCond watchdog_cond;
  bool watchdog_sync_ready;
  bool watchdog_created;
  bool watchdog_done;
  bool watchdog_fired;
  my_ret_t watchdog_quit_result;
};

static void stress_record_quit(stress_state_t* state, my_ret_t result) {
  if (result != MY_RET_OK) state->control_errors++;
}

static my_ret_t stress_frame_timer(void* context) {
  stress_state_t* state = (stress_state_t*)context;
  frame_result_t result;
  if (time_microseconds() >= state->deadline_us) {
    state->deadline_notice_us = time_microseconds();
    state->deadline_reached = true;
    state->deadline_quit_result = my_pal_main_loop_quit(state->loop);
    state->deadline_quit_done_us = time_microseconds();
    stress_record_quit(state, state->deadline_quit_result);
    return MY_RET_FAIL;
  }
  result = draw_frame(&state->frames, state->lcd, &s_dirty, state->next_shade,
                      true);
  if (result == FRAME_RESULT_PENDING) return MY_RET_OK;
  if (result == FRAME_RESULT_ERROR) {
    stress_record_quit(state, my_pal_main_loop_quit(state->loop));
    return MY_RET_FAIL;
  }
  state->next_shade = state->next_shade >= 224u ? 32u
                                                : (uint8_t)(state->next_shade + 1u);
  return MY_RET_OK;
}

static my_ret_t stress_event_handler(void* context, my_pal_window_t* window,
                                     const my_event_t* event) {
  stress_state_t* state = (stress_state_t*)context;
  (void)window;
  if (event->type == MY_EVENT_COMMAND) {
    if (event->u.command.data == NULL) {
      state->handler_errors++;
    } else {
      my_ui_command_dispatch((my_ui_command_t*)event->u.command.data);
    }
  }
  return MY_RET_OK;
}

static my_ret_t stress_command_execute(void* context) {
  command_payload_t* payload = (command_payload_t*)context;
  stress_state_t* state = payload->state;
  uint32_t producer = payload->producer;
  if (producer >= SCREEN_PRODUCER_COUNT) {
    state->handler_errors++;
    return MY_RET_OK;
  }
  if (state->stats[producer].fifo_next != payload->sequence) {
    state->stats[producer].fifo_errors++;
  }
  state->stats[producer].fifo_next = payload->sequence + 1u;
  atomic_fetch_add_explicit(&state->stats[producer].executed, 1ull,
                            memory_order_relaxed);
  return MY_RET_OK;
}

static void stress_command_destroy(void* context) {
  command_payload_t* payload = (command_payload_t*)context;
  stress_state_t* state = payload->state;
  uint32_t producer = payload->producer;
  if (producer < SCREEN_PRODUCER_COUNT) {
    atomic_fetch_add_explicit(&state->stats[producer].destroyed, 1ull,
                              memory_order_relaxed);
  }
  my_mem_free(NULL, payload);
}

static PLATFORM_THREAD_RET stress_producer_run(PLATFORM_THREAD_ARG argument) {
  producer_state_t* producer = (producer_state_t*)argument;
  stress_state_t* state = producer->state;
  producer_stats_t* stats = &state->stats[producer->id];
  uint32_t batch = 0u;
  while (!atomic_load_explicit(&state->stop_producers, memory_order_acquire)) {
    command_payload_t* payload = (command_payload_t*)my_mem_calloc(
        NULL, 1u, sizeof(*payload));
    my_ui_command_t* command;
    my_ret_t result;
    if (payload == NULL) {
      atomic_fetch_add_explicit(&stats->failed, 1ull, memory_order_relaxed);
      break;
    }
    payload->state = state;
    payload->sequence = producer->next_sequence;
    payload->producer = producer->id;
    command = my_ui_command_create(NULL, stress_command_execute, payload,
                                   stress_command_destroy);
    if (command == NULL) {
      my_mem_free(NULL, payload);
      atomic_fetch_add_explicit(&stats->failed, 1ull, memory_order_relaxed);
      break;
    }
    atomic_fetch_add_explicit(&stats->created, 1ull, memory_order_relaxed);
    result = my_ui_command_submit(state->loop, command);
    if (result == MY_RET_OK) {
      producer->next_sequence++;
      atomic_fetch_add_explicit(&stats->submitted, 1ull, memory_order_relaxed);
    } else {
      atomic_fetch_add_explicit(&stats->failed, 1ull, memory_order_relaxed);
    }
    my_ui_command_unref(command);
    if (result != MY_RET_OK) break;
    if (++batch >= 32u) {
      batch = 0u;
      if (state->throttled) {
        time_sleep_us(100u);
      } else {
        platform_thread_yield();
      }
    }
  }
  return PLATFORM_THREAD_RETURN;
}

static void watchdog_deadline_add_ms(struct timespec* deadline, uint32_t ms) {
  deadline->tv_sec += (time_t)(ms / 1000u);
  deadline->tv_nsec += (long)(ms % 1000u) * 1000000L;
  if (deadline->tv_nsec >= 1000000000L) {
    deadline->tv_sec++;
    deadline->tv_nsec -= 1000000000L;
  }
}

static PLATFORM_THREAD_RET stress_watchdog_run(PLATFORM_THREAD_ARG argument) {
  stress_state_t* state = (stress_state_t*)argument;
  struct timespec deadline;
  bool fire = false;
  if (clock_gettime(CLOCK_REALTIME, &deadline) != 0) {
    fire = true;
  } else {
    watchdog_deadline_add_ms(&deadline,
                             state->duration_ms + SCREEN_WATCHDOG_GRACE_MS);
    platform_mutex_lock(&state->watchdog_mutex);
    while (!state->watchdog_done && !fire) {
      int result = pthread_cond_timedwait(&state->watchdog_cond,
                                          &state->watchdog_mutex, &deadline);
      if (result == ETIMEDOUT) {
        fire = true;
      } else if (result != 0 && result != EINTR) {
        fire = true;
      }
    }
    if (state->watchdog_done) fire = false;
    platform_mutex_unlock(&state->watchdog_mutex);
  }
  if (fire) {
    state->watchdog_fire_us = time_microseconds();
    state->watchdog_fired = true;
    atomic_store_explicit(&state->stop_producers, true, memory_order_release);
    state->watchdog_quit_result = my_pal_main_loop_quit(state->loop);
    state->watchdog_quit_done_us = time_microseconds();
  }
  return PLATFORM_THREAD_RETURN;
}

static bool stress_watchdog_start(stress_state_t* state) {
  platform_mutex_init(&state->watchdog_mutex);
  platform_cond_init(&state->watchdog_cond);
  state->watchdog_sync_ready = true;
  state->watchdog_done = false;
  state->watchdog_fired = false;
  state->watchdog_quit_result = MY_RET_OK;
  state->watchdog_created = platform_thread_create(
      &state->watchdog_thread, stress_watchdog_run, state);
  return state->watchdog_created;
}

static void stress_watchdog_stop(stress_state_t* state) {
  if (state->watchdog_created) {
    platform_mutex_lock(&state->watchdog_mutex);
    state->watchdog_done = true;
    platform_cond_signal(&state->watchdog_cond);
    platform_mutex_unlock(&state->watchdog_mutex);
    platform_thread_join(state->watchdog_thread);
    state->watchdog_created = false;
  }
  if (state->watchdog_sync_ready) {
    platform_cond_destroy(&state->watchdog_cond);
    platform_mutex_destroy(&state->watchdog_mutex);
    state->watchdog_sync_ready = false;
  }
}

static void stress_run(stress_state_t* state) {
  uint32_t i;
  my_ret_t run_result;
  uint64_t run_started_us;
  state->started_us = time_microseconds();
  state->deadline_us = state->started_us + (uint64_t)state->duration_ms * 1000u;
  if (my_pal_main_loop_add_timer(state->loop, stress_frame_timer, state,
                                 SCREEN_FRAME_INTERVAL_MS) == 0u) {
    state->setup_errors++;
    printf("  stress stage=frame timer create failed\n");
    return;
  }
  if (!stress_watchdog_start(state)) {
    state->setup_errors++;
    printf("  stress stage=watchdog create failed\n");
    stress_watchdog_stop(state);
    return;
  }
  atomic_store_explicit(&state->stop_producers, false, memory_order_release);
  for (i = 0u; i < SCREEN_PRODUCER_COUNT; ++i) {
    state->producers[i].state = state;
    state->producers[i].id = i;
    state->producers[i].next_sequence = 0u;
    if (!platform_thread_create(&state->producers[i].thread,
                                stress_producer_run, &state->producers[i])) {
      state->setup_errors++;
      printf("  stress stage=producer create id=%u failed\n", i);
      atomic_store_explicit(&state->stop_producers, true, memory_order_release);
      stress_record_quit(state, my_pal_main_loop_quit(state->loop));
      break;
    }
    state->threads_created++;
  }

  run_started_us = time_microseconds();
  run_result = my_pal_main_loop_run(state->loop);
  state->first_run_result = run_result;
  state->first_run_returned_us = time_microseconds();
  state->run_elapsed_us = state->first_run_returned_us - run_started_us;
  if (run_result != MY_RET_OK) state->run_errors++;
  stress_record_quit(state, my_pal_main_loop_quit(state->loop));
  atomic_store_explicit(&state->stop_producers, true, memory_order_release);
  stress_watchdog_stop(state);
  for (i = 0u; i < state->threads_created; ++i) {
    platform_thread_join(state->producers[i].thread);
  }
  run_started_us = time_microseconds();
  run_result = my_pal_main_loop_run(state->loop);
  state->second_run_result = run_result;
  state->second_run_elapsed_us = time_microseconds() - run_started_us;
  if (run_result != MY_RET_OK) state->run_errors++;
}

static void stress_setup_error(stress_state_t* state, const char* stage) {
  state->setup_errors++;
  printf("  stress stage=%s failed\n", stage);
}

static uint32_t g_stress_duration_ms = SCREEN_DEFAULT_STRESS_MS;

static uint64_t stress_time_delta(uint64_t later, uint64_t earlier) {
  return earlier != 0u && later >= earlier ? later - earlier : 0u;
}

static void run_four_producer_frame_soak(uint32_t duration_ms, bool throttled)
{
  stress_state_t state;
  native_stats_t native_before = g_native;
  uint64_t total_started_us = time_microseconds();
  uint64_t created = 0u;
  uint64_t submitted = 0u;
  uint64_t executed = 0u;
  uint64_t destroyed = 0u;
  uint64_t failed = 0u;
  uint64_t fifo_errors = 0u;
  uint64_t total_errors;
  bool setup_ok = true;
  uint32_t i;
  memset(&state, 0, sizeof(state));
  state.duration_ms = duration_ms;
  state.throttled = throttled;
  state.frames.width = SCREEN_TEST_WIDTH;
  state.frames.height = SCREEN_TEST_HEIGHT;
  state.next_shade = 64u;
  atomic_init(&state.stop_producers, false);
  for (i = 0u; i < SCREEN_PRODUCER_COUNT; ++i) {
    atomic_init(&state.stats[i].created, 0ull);
    atomic_init(&state.stats[i].submitted, 0ull);
    atomic_init(&state.stats[i].executed, 0ull);
    atomic_init(&state.stats[i].destroyed, 0ull);
    atomic_init(&state.stats[i].failed, 0ull);
  }

  state.pal = my_pal_create(NULL);
  if (state.pal == NULL || my_pal_screen_native_context(state.pal) == NULL) {
    stress_setup_error(&state, "PAL create");
    setup_ok = false;
  }
  if (setup_ok) {
    state.loop = my_pal_main_loop_create(state.pal);
    if (state.loop == NULL) {
      stress_setup_error(&state, "loop create");
      setup_ok = false;
    }
  }
  if (setup_ok && my_pal_set_event_handler(state.pal, stress_event_handler,
                                           &state) != MY_RET_OK) {
    stress_setup_error(&state, "event handler");
    setup_ok = false;
  }
  if (setup_ok) {
    state.window = my_pal_window_create(state.pal, SCREEN_TEST_WIDTH,
                                        SCREEN_TEST_HEIGHT,
                                        "myui Screen stability soak");
    if (state.window == NULL ||
        my_pal_screen_native_window(state.window) == NULL) {
      stress_setup_error(&state, "window create");
      setup_ok = false;
    }
  }
  if (setup_ok && my_pal_window_show(state.window) != MY_RET_OK) {
    stress_setup_error(&state, "show");
    setup_ok = false;
  }
  if (setup_ok) {
    state.lcd = my_pal_window_get_lcd(state.window);
    if (state.lcd == NULL) {
      stress_setup_error(&state, "get LCD");
      setup_ok = false;
    }
  }
  if (setup_ok &&
      (!draw_frame_bounded(&state.frames, state.lcd, NULL, 32u, false) ||
       !draw_frame_bounded(&state.frames, state.lcd, NULL, 48u, false))) {
    stress_setup_error(&state, "prime");
    setup_ok = false;
  }
  if (setup_ok &&
      (state.frames.buffer_count != 2u ||
       state.frames.buffers[0].pixels == state.frames.buffers[1].pixels)) {
    stress_setup_error(&state, "two distinct prime buffers");
    setup_ok = false;
  }
  native_diag_reset_all();
  if (setup_ok) stress_run(&state);

  if (state.window != NULL) {
    state.public_posts = my_pal_screen_test_post_count(state.window);
    my_pal_window_destroy(state.window);
  }
  if (state.loop != NULL) my_pal_main_loop_destroy(state.loop);
  if (state.pal != NULL) my_pal_destroy(state.pal);
  state.native = native_since(native_before);
  state.total_elapsed_us = time_microseconds() - total_started_us;

  for (i = 0u; i < SCREEN_PRODUCER_COUNT; ++i) {
    uint64_t p_created = (uint64_t)atomic_load_explicit(
        &state.stats[i].created, memory_order_relaxed);
    uint64_t p_submitted = (uint64_t)atomic_load_explicit(
        &state.stats[i].submitted, memory_order_relaxed);
    uint64_t p_executed = (uint64_t)atomic_load_explicit(
        &state.stats[i].executed, memory_order_relaxed);
    uint64_t p_destroyed = (uint64_t)atomic_load_explicit(
        &state.stats[i].destroyed, memory_order_relaxed);
    uint64_t p_failed = (uint64_t)atomic_load_explicit(
        &state.stats[i].failed, memory_order_relaxed);
    uint64_t p_fifo = state.stats[i].fifo_errors;
    created += p_created;
    submitted += p_submitted;
    executed += p_executed;
    destroyed += p_destroyed;
    failed += p_failed;
    fifo_errors += p_fifo;
    printf("screen_stress_producer,id=%u,created=%llu,submitted=%llu,"
           "executed=%llu,destroyed=%llu,failed=%llu,fifo_errors=%llu\n",
           i, (unsigned long long)p_created, (unsigned long long)p_submitted,
           (unsigned long long)p_executed, (unsigned long long)p_destroyed,
           (unsigned long long)p_failed, (unsigned long long)p_fifo);
    if (p_created != p_destroyed || p_submitted != p_executed ||
        p_created == 0u) {
      state.validation_errors++;
    }
  }
  if ((uint64_t)state.public_posts != state.frames.frames) {
    state.validation_errors++;
    printf("  stress public posts=%u accepted frames=%llu\n", state.public_posts,
           (unsigned long long)state.frames.frames);
  }
  if (state.native.posts_accepted != state.frames.frames) {
    state.validation_errors++;
    printf("  stress native posts=%llu accepted frames=%llu\n",
           (unsigned long long)state.native.posts_accepted,
           (unsigned long long)state.frames.frames);
  }
  state.validation_errors += native_balance_errors(state.native, "stress");
  if (state.frames.buffer_count != 2u || state.frames.dirty_frames == 0u ||
      state.frames.reused_frames != state.frames.dirty_frames) {
    state.validation_errors++;
  }
  if (!state.deadline_reached) state.validation_errors++;
  if (state.threads_created != SCREEN_PRODUCER_COUNT) {
    state.validation_errors++;
  }
  if (state.watchdog_fired) state.validation_errors++;
  if (state.watchdog_fired && state.watchdog_quit_result != MY_RET_OK) {
    state.validation_errors++;
  }
  total_errors = state.setup_errors + state.run_errors + state.control_errors +
                 state.handler_errors + state.validation_errors +
                 state.frames.errors + failed + fifo_errors;
  printf("screen_stress_error_detail,setup=%u,run=%u,control=%u,handler=%u,"
         "validation=%u,frame=%llu,begin_timeouts=%llu,producer_failed=%llu,"
         "fifo=%llu\n",
         state.setup_errors, state.run_errors, state.control_errors,
         state.handler_errors, state.validation_errors,
         (unsigned long long)state.frames.errors,
         (unsigned long long)state.frames.begin_timeouts,
         (unsigned long long)failed, (unsigned long long)fifo_errors);
  printf("screen_stress_schedule,deadline_reached=%d,deadline_quit_result=%d,"
         "deadline_notice_us=%llu,deadline_quit_us=%llu,watchdog_fired=%d,"
         "watchdog_quit_result=%d,watchdog_fire_delay_us=%llu,"
         "watchdog_quit_us=%llu,first_run_result=%d,"
         "first_return_delay_us=%llu,second_run_result=%d,"
         "second_run_elapsed_us=%llu\n",
         state.deadline_reached ? 1 : 0, state.deadline_quit_result,
         (unsigned long long)stress_time_delta(state.deadline_notice_us,
                                               state.started_us),
         (unsigned long long)stress_time_delta(state.deadline_quit_done_us,
                                               state.deadline_notice_us),
         state.watchdog_fired ? 1 : 0, state.watchdog_quit_result,
         (unsigned long long)stress_time_delta(state.watchdog_fire_us,
                                               state.deadline_notice_us),
         (unsigned long long)stress_time_delta(state.watchdog_quit_done_us,
                                               state.watchdog_fire_us),
         state.first_run_result,
         (unsigned long long)stress_time_delta(state.first_run_returned_us,
                                               state.deadline_notice_us),
         state.second_run_result,
         (unsigned long long)state.second_run_elapsed_us);
  native_diag_print("post", &g_post_diag);
#ifdef SCREEN_STABILITY_NATIVE_DIAG
  native_diag_print("send", &g_send_diag);
  native_diag_print("dequeue", &g_dequeue_diag);
  native_diag_print("get_event", &g_get_event_diag);
#endif
  printf("screen_command_frame_soak,mode=%s,requested_ms=%u,elapsed_us=%llu,"
         "run_elapsed_us=%llu,threads=%u,frames=%llu,prime_frames=%llu,"
         "dirty_frames=%llu,pending=%llu,posts=%u,native_posts=%llu,"
         "commands=%llu,submitted=%llu,executed=%llu,destroyed=%llu,"
         "failed=%llu,fifo_errors=%llu,errors=%llu,watchdog_fired=%d,"
         "accepted_posts_per_second=%llu,dirty_accepted_per_run_second=%llu,"
         "display_fps=not_measured,swap_interval=default,producer_batch=32,"
         "producer_pause_us=%u\n",
         state.throttled ? "throttled" : "unthrottled", state.duration_ms,
         (unsigned long long)state.total_elapsed_us,
         (unsigned long long)state.run_elapsed_us, state.threads_created,
         (unsigned long long)state.frames.frames,
         (unsigned long long)state.frames.prime_frames,
         (unsigned long long)state.frames.dirty_frames,
         (unsigned long long)state.frames.pending, state.public_posts,
         (unsigned long long)state.native.posts_accepted,
         (unsigned long long)created, (unsigned long long)submitted,
         (unsigned long long)executed, (unsigned long long)destroyed,
         (unsigned long long)failed, (unsigned long long)fifo_errors,
         (unsigned long long)total_errors, state.watchdog_fired ? 1 : 0,
         (unsigned long long)rate_per_second(state.frames.frames,
                                             state.total_elapsed_us),
         (unsigned long long)rate_per_second(state.frames.dirty_frames,
                                             state.run_elapsed_us),
         state.throttled ? 100u : 0u);
  printf("screen_stress_native,contexts=%llu/%llu,events=%llu/%llu,"
         "windows=%llu/%llu,buffer_sets=%llu/%llu\n",
         (unsigned long long)state.native.context_created,
         (unsigned long long)state.native.context_destroyed,
         (unsigned long long)state.native.event_created,
         (unsigned long long)state.native.event_destroyed,
         (unsigned long long)state.native.window_created,
         (unsigned long long)state.native.window_destroyed,
         (unsigned long long)state.native.buffers_created,
         (unsigned long long)state.native.buffers_destroyed);
  CHECK(total_errors == 0u);
  CHECK(state.frames.frames == (uint64_t)state.public_posts);
  CHECK(state.frames.frames == state.native.posts_accepted);
  CHECK(state.frames.dirty_frames > 0u);
  CHECK(created == destroyed);
  CHECK(submitted == executed);
  CHECK(failed == 0u);
  CHECK(fifo_errors == 0u);
  CHECK(state.deadline_reached);
  CHECK(!state.watchdog_fired);
}

TEST(screen_four_producer_frame_soak)
{
  run_four_producer_frame_soak(g_stress_duration_ms, true);
}

TEST(screen_four_producer_unthrottled_regression)
{
  run_four_producer_frame_soak(1000u, false);
}

static bool parse_stress_duration(uint32_t* duration_ms) {
  const char* text = getenv("BREAK_SCREEN_STRESS_MS");
  const char* p;
  char* end = NULL;
  unsigned long value;
  if (text == NULL) {
    *duration_ms = SCREEN_DEFAULT_STRESS_MS;
    return true;
  }
  if (*text == '\0') return false;
  for (p = text; *p != '\0'; ++p) {
    if (*p < '0' || *p > '9') return false;
  }
  errno = 0;
  value = strtoul(text, &end, 10);
  if (errno == ERANGE || end == text || *end != '\0' ||
      value < SCREEN_MIN_STRESS_MS || value > SCREEN_MAX_STRESS_MS) {
    return false;
  }
  *duration_ms = (uint32_t)value;
  return true;
}

int main(int argc, char** argv)
{
  my_pal_t* probe;
  const char* test_filter = argc > 1 ? argv[1] : NULL;
  if (argc > 2) return 2;
  setvbuf(stdout, NULL, _IONBF, 0);
  if (!parse_stress_duration(&g_stress_duration_ms)) {
    printf("Invalid BREAK_SCREEN_STRESS_MS; expected decimal %u..%u\n",
           SCREEN_MIN_STRESS_MS, SCREEN_MAX_STRESS_MS);
    return 2;
  }
  time_init();
  probe = my_pal_create(NULL);
  if (probe == NULL || my_pal_screen_native_context(probe) == NULL) {
    if (probe != NULL) my_pal_destroy(probe);
    printf("SKIP: no usable QNX Screen service\n");
    return getenv("BREAK_QNX_SCREEN_REQUIRED") != NULL &&
                   strcmp(getenv("BREAK_QNX_SCREEN_REQUIRED"), "1") == 0
               ? 1
               : 77;
  }
  my_pal_destroy(probe);
  memset(&g_native, 0, sizeof(g_native));
  printf("=== Running Tests ===\n");
#define RUN_SCREEN_STABILITY_TEST(name) do { \
  if (test_filter == NULL || strcmp(test_filter, #name) == 0) RUN_TEST(name); \
} while (0)
  RUN_SCREEN_STABILITY_TEST(screen_500_complete_lifecycles);
  RUN_SCREEN_STABILITY_TEST(screen_four_producer_frame_soak);
  RUN_SCREEN_STABILITY_TEST(screen_four_producer_unthrottled_regression);
#undef RUN_SCREEN_STABILITY_TEST
  printf("\n=== Results: %d passed, %d failed, %d total ===\n",
         g_test_pass, g_test_fail, g_test_count);
  return g_test_fail > 0 ? 1 : 0;
}
