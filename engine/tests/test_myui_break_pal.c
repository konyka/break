#include "test_framework.h"

#include "mypal/break/my_pal_break.h"
#include "mypal/dummy/my_pal_dummy.h"
#include "myui/my_ui_command.h"
#include "ui/myui_break.h"

#include <stdint.h>

#if !defined(_WIN32)
#include <pthread.h>
#include <sched.h>
#include <stdatomic.h>
#endif

static int g_events;
static int g_first_marker;
static int g_second_marker;
static my_pal_window_t *g_windows[2];
static my_event_type_t g_types[2];
static void *g_data[2];
static void *g_expected_data[256];
static int g_expected_count;
static bool g_fifo_ok;
static char g_received_ime_text[32];

typedef struct command_test_context_t {
  int execute_count;
  int destroy_count;
} command_test_context_t;

static my_ret_t command_test_execute(void *context);
static void command_test_destroy(void *context);

#if !defined(_WIN32)
typedef struct command_race_worker_t {
  my_pal_main_loop_t *loop;
  my_ui_command_scope_t *scope;
  command_test_context_t *contexts;
  int count;
  atomic_int *finished;
  atomic_int submitted;
  atomic_int rejected;
} command_race_worker_t;

static void *command_race_worker(void *context) {
  command_race_worker_t *worker = (command_race_worker_t *)context;
  int i;
  for (i = 0; i < worker->count; i++) {
    my_ui_command_t *command = my_ui_command_create(
        NULL, command_test_execute, &worker->contexts[i],
        command_test_destroy);
    my_ret_t ret;
    if (command == NULL) {
      atomic_fetch_add_explicit(&worker->rejected, 1, memory_order_relaxed);
      continue;
    }
    ret = my_ui_command_submit_scoped(worker->loop, worker->scope, command);
    if (ret == MY_RET_OK) {
      atomic_fetch_add_explicit(&worker->submitted, 1, memory_order_relaxed);
    } else {
      atomic_fetch_add_explicit(&worker->rejected, 1, memory_order_relaxed);
    }
    my_ui_command_unref(command);
  }
  if (worker->finished != NULL) {
    atomic_fetch_add_explicit(worker->finished, 1, memory_order_release);
  }
  return NULL;
}

typedef struct command_pump_state_t {
  my_pal_main_loop_t *loop;
  atomic_int *finished;
  int worker_count;
} command_pump_state_t;

static void *command_pump_worker(void *context) {
  command_pump_state_t *state = (command_pump_state_t *)context;
  while (atomic_load_explicit(state->finished, memory_order_acquire) <
         state->worker_count) {
    if (my_pal_main_loop_pump_n(state->loop, 16u) == 0u) {
      sched_yield();
    }
  }
  (void)my_pal_main_loop_pump_n(state->loop, UINT32_MAX);
  return NULL;
}
#endif

static my_ret_t command_test_execute(void *context) {
  command_test_context_t *state = (command_test_context_t *)context;
  state->execute_count++;
  return MY_RET_OK;
}

static void command_test_destroy(void *context) {
  command_test_context_t *state = (command_test_context_t *)context;
  state->destroy_count++;
}

static my_ret_t on_command_event(void *ctx, my_pal_window_t *window,
                                 const my_event_t *event) {
  (void)ctx;
  (void)window;
  if (event == NULL || event->type != MY_EVENT_COMMAND) {
    return MY_RET_FAIL;
  }
  my_ui_command_dispatch((my_ui_command_t *)event->u.command.data);
  return MY_RET_OK;
}

TEST(break_ui_command_executes_once_and_releases_context)
{
  my_pal_t *pal = my_pal_break_create(NULL, (Platform *)(uintptr_t)1, NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  command_test_context_t state = {0, 0};
  my_ui_command_t *command = my_ui_command_create(
      NULL, command_test_execute, &state, command_test_destroy);

  ASSERT_NOT_NULL(command);
  ASSERT_EQ(my_pal_set_event_handler(pal, on_command_event, NULL), MY_RET_OK);
  ASSERT_EQ(my_ui_command_submit(loop, command), MY_RET_OK);
  ASSERT_EQ(my_ui_command_submit(loop, command), MY_RET_PENDING);
  my_ui_command_unref(command);
  ASSERT_EQ(my_pal_break_pump(loop), 1u);
  ASSERT_EQ(state.execute_count, 1);
  ASSERT_EQ(state.destroy_count, 1);

  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(dummy_ui_command_executes_once_and_releases_context)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  command_test_context_t state = {0, 0};
  my_ui_command_t *command = my_ui_command_create(
      NULL, command_test_execute, &state, command_test_destroy);

  ASSERT_NOT_NULL(command);
  ASSERT_EQ(my_pal_set_event_handler(pal, on_command_event, NULL), MY_RET_OK);
  ASSERT_EQ(my_ui_command_submit(loop, command), MY_RET_OK);
  ASSERT_EQ(my_ui_command_submit(loop, command), MY_RET_PENDING);
  my_ui_command_unref(command);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, 1u), 1u);
  ASSERT_EQ(state.execute_count, 1);
  ASSERT_EQ(state.destroy_count, 1);

  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(break_ui_command_cancel_skips_execution)
{
  my_pal_t *pal = my_pal_break_create(NULL, (Platform *)(uintptr_t)1, NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  command_test_context_t state = {0, 0};
  my_ui_command_t *command = my_ui_command_create(
      NULL, command_test_execute, &state, command_test_destroy);

  ASSERT_EQ(my_pal_set_event_handler(pal, on_command_event, NULL), MY_RET_OK);
  ASSERT_EQ(my_ui_command_submit(loop, command), MY_RET_OK);
  ASSERT_EQ(my_ui_command_cancel(command), MY_RET_OK);
  ASSERT_TRUE(my_ui_command_is_cancelled(command));
  my_ui_command_unref(command);
  ASSERT_EQ(my_pal_break_pump(loop), 1u);
  ASSERT_EQ(state.execute_count, 0);
  ASSERT_EQ(state.destroy_count, 1);

  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(dummy_ui_command_destroy_releases_queued_context)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  command_test_context_t state = {0, 0};
  my_ui_command_t *command = my_ui_command_create(
      NULL, command_test_execute, &state, command_test_destroy);

  ASSERT_EQ(my_ui_command_submit(loop, command), MY_RET_OK);
  my_ui_command_unref(command);
  my_pal_main_loop_destroy(loop);
  ASSERT_EQ(state.execute_count, 0);
  ASSERT_EQ(state.destroy_count, 1);
  my_pal_destroy(pal);
}

#if !defined(_WIN32)
TEST(dummy_ui_command_scope_close_races_with_producers)
{
  enum { worker_count = 4, command_count = 64 };
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_ui_command_scope_t *scope = my_ui_command_scope_create(NULL);
  pthread_t threads[worker_count];
  command_race_worker_t workers[worker_count];
  command_test_context_t contexts[worker_count][command_count] = {{{0, 0}}};
  int i;
  int j;
  int created = 0;

  ASSERT_NOT_NULL(scope);
  for (i = 0; i < worker_count; i++) {
    workers[i].loop = loop;
    workers[i].scope = scope;
    workers[i].contexts = contexts[i];
    workers[i].count = command_count;
    workers[i].finished = NULL;
    atomic_init(&workers[i].submitted, 0);
    atomic_init(&workers[i].rejected, 0);
    ASSERT_EQ(pthread_create(&threads[i], NULL, command_race_worker,
                             &workers[i]), 0);
    created++;
  }
  my_ui_command_scope_close(scope);
  for (i = 0; i < created; i++) {
    ASSERT_EQ(pthread_join(threads[i], NULL), 0);
  }
  ASSERT_TRUE(my_ui_command_scope_is_closed(scope));
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, UINT32_MAX),
            (uint32_t)(atomic_load_explicit(&workers[0].submitted,
                                             memory_order_relaxed) +
                       atomic_load_explicit(&workers[1].submitted,
                                            memory_order_relaxed) +
                       atomic_load_explicit(&workers[2].submitted,
                                            memory_order_relaxed) +
                       atomic_load_explicit(&workers[3].submitted,
                                            memory_order_relaxed)));
  for (i = 0; i < worker_count; i++) {
    for (j = 0; j < command_count; j++) {
      ASSERT_EQ(contexts[i][j].destroy_count, 1);
      ASSERT_TRUE(contexts[i][j].execute_count <= 1);
    }
  }
  my_ui_command_scope_unref(scope);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(dummy_ui_command_dispatches_while_producers_submit)
{
  enum { worker_count = 4, command_count = 64 };
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_ui_command_scope_t *scope = my_ui_command_scope_create(NULL);
  pthread_t producers[worker_count];
  pthread_t pump;
  command_race_worker_t workers[worker_count];
  command_test_context_t contexts[worker_count][command_count] = {{{0, 0}}};
  command_pump_state_t pump_state;
  atomic_int finished;
  int i;
  int created = 0;
  int submitted = 0;

  ASSERT_NOT_NULL(scope);
  ASSERT_EQ(my_pal_set_event_handler(pal, on_command_event, NULL), MY_RET_OK);
  atomic_init(&finished, 0);
  pump_state.loop = loop;
  pump_state.finished = &finished;
  pump_state.worker_count = worker_count;
  ASSERT_EQ(pthread_create(&pump, NULL, command_pump_worker, &pump_state), 0);
  for (i = 0; i < worker_count; i++) {
    workers[i].loop = loop;
    workers[i].scope = scope;
    workers[i].contexts = contexts[i];
    workers[i].count = command_count;
    workers[i].finished = &finished;
    atomic_init(&workers[i].submitted, 0);
    atomic_init(&workers[i].rejected, 0);
    ASSERT_EQ(pthread_create(&producers[i], NULL, command_race_worker,
                             &workers[i]), 0);
    created++;
  }
  for (i = 0; i < created; i++) {
    ASSERT_EQ(pthread_join(producers[i], NULL), 0);
    submitted += atomic_load_explicit(&workers[i].submitted,
                                      memory_order_relaxed);
  }
  ASSERT_EQ(pthread_join(pump, NULL), 0);
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, UINT32_MAX), 0u);
  ASSERT_EQ(submitted, worker_count * command_count);
  for (i = 0; i < worker_count; i++) {
    int j;
    for (j = 0; j < command_count; j++) {
      ASSERT_EQ(contexts[i][j].execute_count, 1);
      ASSERT_EQ(contexts[i][j].destroy_count, 1);
    }
  }
  my_ui_command_scope_unref(scope);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}
#endif

static my_ret_t on_ime_event(void *ctx, my_pal_window_t *window,
                             const my_event_t *event) {
  (void)ctx;
  (void)window;
  if (event == NULL || event->type != MY_EVENT_IME_COMMIT ||
      event->u.ime.text == NULL) {
    return MY_RET_FAIL;
  }
  snprintf(g_received_ime_text, sizeof(g_received_ime_text), "%s",
           event->u.ime.text);
  return MY_RET_OK;
}

#if !defined(_WIN32)
typedef struct post_thread_state_t {
  my_pal_main_loop_t *loop;
  int base;
  int count;
  atomic_int posted;
  atomic_bool failed;
} post_thread_state_t;

static void *post_events_thread(void *context) {
  post_thread_state_t *state = (post_thread_state_t *)context;
  int i;
  for (i = 0; i < state->count; i++) {
    my_event_t event = my_event_init(MY_EVENT_USER);
    event.u.user.data = (void *)(uintptr_t)(state->base + i + 1);
    if (my_pal_main_loop_post_event(state->loop, &event) != MY_RET_OK) {
      atomic_store_explicit(&state->failed, true, memory_order_release);
      return NULL;
    }
    atomic_fetch_add_explicit(&state->posted, 1, memory_order_relaxed);
  }
  return NULL;
}

static atomic_int g_concurrent_received;
static atomic_int g_concurrent_sum;

static my_ret_t on_concurrent_event(void *ctx, my_pal_window_t *window,
                                    const my_event_t *event) {
  (void)ctx;
  (void)window;
  if (event == NULL || event->type != MY_EVENT_USER) {
    return MY_RET_FAIL;
  }
  atomic_fetch_add_explicit(&g_concurrent_received, 1, memory_order_relaxed);
  atomic_fetch_add_explicit(
      &g_concurrent_sum, (int)(uintptr_t)event->u.user.data,
      memory_order_relaxed);
  return MY_RET_OK;
}
#endif

typedef struct media_reentrant_state_t {
  my_pal_t *pal;
  my_ret_t register_result;
  uint32_t release_count;
} media_reentrant_state_t;

static void test_media_provider_release(void *context);

static my_ret_t media_reentrant_provider(
    void *context, my_pal_media_context_ex_t *out) {
  media_reentrant_state_t *state = (media_reentrant_state_t *)context;
  const my_pal_media_provider_t replacement = {
      sizeof(replacement), MY_PAL_MEDIA_PROVIDER_ABI_VERSION,
      media_reentrant_provider, context, test_media_provider_release};
  state->register_result =
      my_pal_register_media_provider(state->pal, &replacement);
  if (out == NULL) return MY_RET_INVALID_PARAMS;
  *out = (my_pal_media_context_ex_t){0};
  out->base.screen = true;
  return MY_RET_OK;
}

static my_ret_t media_unregister_reentrant_provider(
    void *context, my_pal_media_context_ex_t *out) {
  media_reentrant_state_t *state = (media_reentrant_state_t *)context;
  my_pal_unregister_media_provider(state->pal);
  if (out == NULL) return MY_RET_INVALID_PARAMS;
  *out = (my_pal_media_context_ex_t){0};
  return MY_RET_OK;
}

static void media_reentrant_release(void *context) {
  media_reentrant_state_t *state = (media_reentrant_state_t *)context;
  state->release_count++;
}

static my_ret_t test_media_provider(void *context,
                                    my_pal_media_context_ex_t *out) {
  bool *called = (bool *)context;
  if (out == NULL) return MY_RET_INVALID_PARAMS;
  *called = true;
  out->base.screen = true;
  out->base.prefers_dark = true;
  out->base.prefers_reduced_motion = false;
  out->base.capabilities = MY_PAL_MEDIA_CAP_HOVER;
  out->known = MY_PAL_MEDIA_KNOWN_HOVER;
  return MY_RET_OK;
}

static void test_media_provider_release(void *context) {
  (void)context;
}

static void test_media_provider_counted_release(void *context) {
  uint32_t *release_count = (uint32_t *)context;
  (*release_count)++;
}

static my_ret_t test_vulkan_provider(void *context, my_pal_window_t *window,
                                     const char *const **names,
                                     uint32_t *count) {
  static const char *const extensions[] = {"VK_KHR_surface",
                                           "VK_KHR_test_surface"};
  bool *called = (bool *)context;
  (void)window;
  if (names == NULL || count == NULL) return MY_RET_INVALID_PARAMS;
  *called = true;
  *names = extensions;
  *count = 2u;
  return MY_RET_OK;
}

static my_ret_t test_vulkan_provider_fail(void *context,
                                          my_pal_window_t *window,
                                          const char *const **names,
                                          uint32_t *count) {
  bool *called = (bool *)context;
  (void)window;
  if (names == NULL || count == NULL) return MY_RET_INVALID_PARAMS;
  *called = true;
  *names = (const char *const *)(uintptr_t)1;
  *count = UINT32_MAX;
  return MY_RET_FAIL;
}

static my_ret_t test_vulkan_provider_malformed(void *context,
                                               my_pal_window_t *window,
                                               const char *const **names,
                                               uint32_t *count) {
  bool *called = (bool *)context;
  (void)window;
  if (names == NULL || count == NULL) return MY_RET_INVALID_PARAMS;
  *called = true;
  *names = NULL;
  *count = 1u;
  return MY_RET_OK;
}

typedef struct vulkan_reentrant_state_t {
  my_pal_t *pal;
  uint32_t release_count;
} vulkan_reentrant_state_t;

static my_ret_t vulkan_unregister_reentrant_provider(
    void *context, my_pal_window_t *window, const char *const **names,
    uint32_t *count) {
  static const char *const extensions[] = {"VK_KHR_surface"};
  vulkan_reentrant_state_t *state =
      (vulkan_reentrant_state_t *)context;
  (void)window;
  if (names == NULL || count == NULL) return MY_RET_INVALID_PARAMS;
  my_pal_unregister_vulkan_provider(state->pal);
  *names = extensions;
  *count = 1u;
  return MY_RET_OK;
}

static void vulkan_reentrant_release(void *context) {
  vulkan_reentrant_state_t *state =
      (vulkan_reentrant_state_t *)context;
  state->release_count++;
}

static void test_vulkan_provider_release(void *context) {
  uint32_t *release_count = (uint32_t *)context;
  (*release_count)++;
}

static my_ret_t test_media_provider_noop(
    void *context, my_pal_media_context_ex_t *out) {
  (void)context;
  if (out == NULL) return MY_RET_INVALID_PARAMS;
  *out = (my_pal_media_context_ex_t){0};
  return MY_RET_OK;
}

static my_ret_t on_event(void *ctx, my_pal_window_t *window,
                         const my_event_t *event) {
  (void)ctx;
  if (g_events < 2) {
    g_windows[g_events] = window;
    g_types[g_events] = event->type;
    g_data[g_events] = event->u.user.data;
  }
  if (g_events >= g_expected_count ||
      event->u.user.data != g_expected_data[g_events]) {
    g_fifo_ok = false;
  }
  g_events += 1;
  return MY_RET_OK;
}

TEST(posted_events_are_fifo_and_dispatched)
{
  my_pal_t *pal = my_pal_break_create(NULL, (Platform *)(uintptr_t)1, NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_event_t first = my_event_init(MY_EVENT_USER);
  my_event_t second = my_event_init(MY_EVENT_USER);

  g_events = 0;
  g_expected_count = 2;
  g_fifo_ok = true;
  first.u.user.data = &g_first_marker;
  second.u.user.data = &g_second_marker;
  g_expected_data[0] = first.u.user.data;
  g_expected_data[1] = second.u.user.data;
  ASSERT_EQ(my_pal_set_event_handler(pal, on_event, NULL), MY_RET_OK);
  ASSERT_EQ(my_pal_main_loop_post_event(loop, &first), MY_RET_OK);
  ASSERT_EQ(my_pal_main_loop_post_event(loop, &second), MY_RET_OK);
  ASSERT_EQ(my_pal_break_pump(loop), 2u);
  ASSERT_EQ(g_events, 2);
  ASSERT_TRUE(g_fifo_ok);
  ASSERT_TRUE(g_windows[0] == NULL);
  ASSERT_TRUE(g_windows[1] == NULL);
  ASSERT_EQ(g_types[0], MY_EVENT_USER);
  ASSERT_EQ(g_types[1], MY_EVENT_USER);
  ASSERT_TRUE(g_data[0] == &g_first_marker);
  ASSERT_TRUE(g_data[1] == &g_second_marker);

  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(posted_event_burst_preserves_fifo)
{
  enum { event_count = 256 };
  my_pal_t *pal = my_pal_break_create(NULL, (Platform *)(uintptr_t)1, NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_event_t event = my_event_init(MY_EVENT_USER);
  int markers[event_count];
  int index;

  g_events = 0;
  g_expected_count = event_count;
  g_fifo_ok = true;
  ASSERT_EQ(my_pal_set_event_handler(pal, on_event, NULL), MY_RET_OK);
  for (index = 0; index < event_count; index++) {
    event.u.user.data = &markers[index];
    g_expected_data[index] = event.u.user.data;
    ASSERT_EQ(my_pal_main_loop_post_event(loop, &event), MY_RET_OK);
  }
  ASSERT_EQ(my_pal_break_pump(loop), (uint32_t)event_count);
  ASSERT_EQ(g_events, event_count);
  ASSERT_TRUE(g_fifo_ok);

  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(posted_events_are_safe_for_concurrent_producers)
{
#if !defined(_WIN32)
  enum { producer_count = 4, events_per_producer = 128 };
  my_pal_t *pal = my_pal_break_create(NULL, (Platform *)(uintptr_t)1, NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  post_thread_state_t states[producer_count];
  pthread_t threads[producer_count];
  int expected_sum = 0;
  int i;

  ASSERT_EQ(my_pal_set_event_handler(pal, on_concurrent_event, NULL),
            MY_RET_OK);
  atomic_init(&g_concurrent_received, 0);
  atomic_init(&g_concurrent_sum, 0);
  for (i = 0; i < producer_count; i++) {
    int j;
    states[i].loop = loop;
    states[i].base = i * events_per_producer;
    states[i].count = events_per_producer;
    atomic_init(&states[i].posted, 0);
    atomic_init(&states[i].failed, false);
    for (j = 0; j < events_per_producer; j++) {
      expected_sum += states[i].base + j + 1;
    }
    ASSERT_EQ(pthread_create(&threads[i], NULL, post_events_thread,
                             &states[i]), 0);
  }
  for (i = 0; i < producer_count; i++) {
    ASSERT_EQ(pthread_join(threads[i], NULL), 0);
    ASSERT_FALSE(atomic_load_explicit(&states[i].failed, memory_order_acquire));
  }
  ASSERT_EQ(my_pal_break_pump(loop),
            (uint32_t)(producer_count * events_per_producer));
  ASSERT_EQ(atomic_load_explicit(&g_concurrent_received, memory_order_relaxed),
            producer_count * events_per_producer);
  ASSERT_EQ(atomic_load_explicit(&g_concurrent_sum, memory_order_relaxed),
            expected_sum);

  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
#else
  /* Windows CI validates the single-producer path; native thread coverage is
   * provided by the platform-specific runner. */
#endif
}

TEST(dummy_posted_events_are_safe_for_concurrent_producers)
{
#if !defined(_WIN32)
  enum { producer_count = 4, events_per_producer = 128 };
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  post_thread_state_t states[producer_count];
  pthread_t threads[producer_count];
  int expected_sum = 0;
  int i;

  ASSERT_EQ(my_pal_set_event_handler(pal, on_concurrent_event, NULL),
            MY_RET_OK);
  atomic_init(&g_concurrent_received, 0);
  atomic_init(&g_concurrent_sum, 0);
  for (i = 0; i < producer_count; i++) {
    int j;
    states[i].loop = loop;
    states[i].base = i * events_per_producer;
    states[i].count = events_per_producer;
    atomic_init(&states[i].posted, 0);
    atomic_init(&states[i].failed, false);
    for (j = 0; j < events_per_producer; j++) {
      expected_sum += states[i].base + j + 1;
    }
    ASSERT_EQ(pthread_create(&threads[i], NULL, post_events_thread,
                             &states[i]), 0);
  }
  for (i = 0; i < producer_count; i++) {
    ASSERT_EQ(pthread_join(threads[i], NULL), 0);
    ASSERT_FALSE(atomic_load_explicit(&states[i].failed, memory_order_acquire));
  }
  ASSERT_EQ(my_pal_main_loop_pump_n(loop,
                                    producer_count * events_per_producer),
            (uint32_t)(producer_count * events_per_producer));
  ASSERT_EQ(atomic_load_explicit(&g_concurrent_received, memory_order_relaxed),
            producer_count * events_per_producer);
  ASSERT_EQ(atomic_load_explicit(&g_concurrent_sum, memory_order_relaxed),
            expected_sum);

  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
#endif
}

TEST(posted_ime_event_owns_text_until_dispatch)
{
  my_pal_t *pal = my_pal_break_create(NULL, (Platform *)(uintptr_t)1, NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_event_t event = my_event_init(MY_EVENT_IME_COMMIT);
  char text[] = "before";

  event.u.ime.text = text;
  ASSERT_EQ(my_pal_set_event_handler(pal, on_ime_event, NULL), MY_RET_OK);
  g_received_ime_text[0] = '\0';
  ASSERT_EQ(my_pal_main_loop_post_event(loop, &event), MY_RET_OK);
  strcpy(text, "after");
  ASSERT_EQ(my_pal_break_pump(loop), 1u);
  ASSERT_TRUE(strcmp(g_received_ime_text, "before") == 0);

  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(dummy_posted_ime_event_owns_text_until_dispatch)
{
  my_pal_t *pal = my_pal_dummy_create(NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);
  my_event_t event = my_event_init(MY_EVENT_IME_COMMIT);
  char text[] = "before";

  event.u.ime.text = text;
  ASSERT_EQ(my_pal_set_event_handler(pal, on_ime_event, NULL), MY_RET_OK);
  g_received_ime_text[0] = '\0';
  ASSERT_EQ(my_pal_main_loop_post_event(loop, &event), MY_RET_OK);
  strcpy(text, "after");
  ASSERT_EQ(my_pal_main_loop_pump_n(loop, 1u), 1u);
  ASSERT_TRUE(strcmp(g_received_ime_text, "before") == 0);

  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(idle_run_returns_without_blocking)
{
  my_pal_t *pal = my_pal_break_create(NULL, (Platform *)(uintptr_t)1, NULL);
  my_pal_main_loop_t *loop = my_pal_main_loop_create(pal);

  ASSERT_EQ(my_pal_main_loop_run(loop), MY_RET_OK);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
}

TEST(embedded_pal_does_not_expose_a_private_vulkan_surface)
{
  my_pal_t *pal = my_pal_break_create(NULL, (Platform *)(uintptr_t)1, NULL);
  my_pal_window_t *window = my_pal_window_create(pal, 100, 100, "test");

  ASSERT_NOT_NULL(window);
  ASSERT_TRUE(my_pal_window_vk_create_surface(window, (void *)(uintptr_t)1) ==
              NULL);
  my_pal_window_destroy(window);
  my_pal_destroy(pal);
}

TEST(pal_public_wrappers_reject_null_objects)
{
  int32_t width = 0;
  int32_t height = 0;
  my_event_t event = my_event_init(MY_EVENT_USER);

  ASSERT_EQ(my_pal_window_set_title(NULL, "null"), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_window_resize(NULL, 10, 10), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_window_show(NULL), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_window_get_size(NULL, &width, &height),
            MY_RET_INVALID_PARAMS);
  ASSERT_TRUE(my_pal_window_get_lcd(NULL) == NULL);
  ASSERT_EQ(my_pal_window_gl_enable(NULL), NULL);
  ASSERT_EQ(my_pal_window_gl_enable_api(NULL, MY_PAL_GL_API_GLES2), NULL);
  ASSERT_TRUE(my_pal_window_vk_create_surface(NULL, NULL) == NULL);
  ASSERT_EQ(my_pal_window_begin_move(NULL), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_window_set_cursor(NULL, MY_CURSOR_ARROW),
            MY_RET_INVALID_PARAMS);

  ASSERT_EQ(my_pal_gl_make_current(NULL), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_gl_swap_buffers(NULL), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_gl_get_size(NULL, &width, &height), MY_RET_INVALID_PARAMS);
  ASSERT_FALSE(my_pal_gl_has_multisample(NULL));

  ASSERT_EQ(my_pal_main_loop_run(NULL), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_main_loop_quit(NULL), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_main_loop_post_event(NULL, &event), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_main_loop_add_timer(NULL, NULL, NULL, 1u), 0u);
  ASSERT_EQ(my_pal_main_loop_remove_timer(NULL, 1u), MY_RET_INVALID_PARAMS);

  ASSERT_EQ(my_pal_window_create(NULL, 10, 10, NULL), NULL);
  ASSERT_EQ(my_pal_main_loop_create(NULL), NULL);
  ASSERT_EQ(my_pal_time_now_ms(NULL), 0u);
  ASSERT_EQ(my_pal_set_event_handler(NULL, NULL, NULL), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_clipboard_set_text(NULL, "null"), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_clipboard_get_text(NULL, NULL, 0u), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_clipboard_get_text_alloc(NULL, NULL, NULL),
            MY_RET_INVALID_PARAMS);
  ASSERT_FLOAT_EQ(my_pal_get_scale_factor(NULL), 1.0f, 0.0001f);
  ASSERT_FALSE(my_pal_needs_client_decoration(NULL));
  ASSERT_EQ(my_pal_get_media_context(NULL, NULL), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_get_media_context(NULL, &(my_pal_media_context_t){0}),
            MY_RET_NOT_SUPPORTED);
}

TEST(pal_optional_wrapper_handles_partial_vtables)
{
  static const my_pal_window_vtable_t window_vtable = {0};
  static const my_pal_main_loop_vtable_t loop_vtable = {0};
  static const my_pal_gl_vtable_t gl_vtable = {0};
  my_pal_window_t window = {&window_vtable};
  my_pal_main_loop_t loop = {&loop_vtable};
  my_pal_gl_t gl = {&gl_vtable};

  ASSERT_TRUE(my_pal_window_gl_enable_api(&window, MY_PAL_GL_API_GLES2) ==
              NULL);
  ASSERT_TRUE(my_pal_window_vk_create_surface(&window, NULL) == NULL);
  ASSERT_EQ(my_pal_window_begin_move(&window), MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_pal_window_set_cursor(&window, MY_CURSOR_ARROW),
            MY_RET_NOT_SUPPORTED);
  ASSERT_EQ(my_pal_gl_make_current(&gl), MY_RET_INVALID_PARAMS);
  ASSERT_FALSE(my_pal_gl_has_multisample(&gl));
  ASSERT_EQ(my_pal_main_loop_run(&loop), MY_RET_INVALID_PARAMS);
  ASSERT_EQ(my_pal_main_loop_add_timer(&loop, NULL, NULL, 1u), 0u);
  {
    static const my_pal_vtable_t pal_vtable = {0};
    my_pal_t pal = {&pal_vtable};
    my_pal_media_context_t media = {true, true, true, UINT32_MAX};
    ASSERT_EQ(my_pal_get_media_context(&pal, &media), MY_RET_NOT_SUPPORTED);
    ASSERT_FALSE(media.screen);
    ASSERT_FALSE(media.prefers_dark);
    ASSERT_FALSE(media.prefers_reduced_motion);
    ASSERT_EQ(media.capabilities, 0u);
  }
}

TEST(pal_media_extension_keeps_legacy_vtable_compatible)
{
  static const my_pal_vtable_t pal_vtable = {0};
  my_pal_t pal = {&pal_vtable};
  my_pal_media_context_ex_t extended = {0};
  my_pal_media_context_t legacy = {0};
  my_pal_media_provider_t provider = {0};
  bool called = false;

  provider.size = sizeof(provider);
  provider.abi_version = MY_PAL_MEDIA_PROVIDER_ABI_VERSION;
  provider.get_context = test_media_provider;
  provider.context = &called;
  provider.release_context = test_media_provider_release;
  ASSERT_EQ(my_pal_register_media_provider(&pal, NULL), MY_RET_INVALID_PARAMS);
  provider.abi_version++;
  ASSERT_EQ(my_pal_register_media_provider(&pal, &provider),
            MY_RET_INVALID_PARAMS);
  provider.abi_version = MY_PAL_MEDIA_PROVIDER_ABI_VERSION;
  ASSERT_EQ(my_pal_register_media_provider(&pal, &provider), MY_RET_OK);
  ASSERT_EQ(my_pal_get_media_context_ex(&pal, &extended), MY_RET_OK);
  ASSERT_TRUE(called);
  ASSERT_TRUE(extended.base.screen);
  ASSERT_EQ(extended.known, MY_PAL_MEDIA_KNOWN_HOVER);
  ASSERT_EQ(my_pal_get_media_context(&pal, &legacy), MY_RET_OK);
  ASSERT_TRUE(legacy.screen);
  ASSERT_EQ(legacy.capabilities, MY_PAL_MEDIA_CAP_HOVER);
  my_pal_unregister_media_provider(&pal);
  ASSERT_EQ(my_pal_get_media_context_ex(&pal, &extended), MY_RET_NOT_SUPPORTED);
}

TEST(pal_media_provider_reentry_does_not_replace_active_callback)
{
  static const my_pal_vtable_t pal_vtable = {0};
  my_pal_t pal = {&pal_vtable};
  media_reentrant_state_t state = {&pal, MY_RET_FAIL, 0u};
  const my_pal_media_provider_t provider = {
      sizeof(provider), MY_PAL_MEDIA_PROVIDER_ABI_VERSION,
      media_reentrant_provider, &state, test_media_provider_release};
  my_pal_media_context_ex_t context = {0};

  ASSERT_EQ(my_pal_register_media_provider(&pal, &provider), MY_RET_OK);
  ASSERT_EQ(my_pal_get_media_context_ex(&pal, &context), MY_RET_OK);
  ASSERT_EQ(state.register_result, MY_RET_PENDING);
  ASSERT_TRUE(context.base.screen);
  my_pal_unregister_media_provider(&pal);
}

TEST(pal_vulkan_provider_validates_abi_and_clears_failed_query)
{
  static const my_pal_vtable_t pal_vtable = {0};
  my_pal_t pal = {&pal_vtable};
  my_pal_vulkan_provider_t provider = {0};
  my_pal_vulkan_instance_extensions_t extensions;
  bool called = false;

  provider.size = sizeof(provider);
  provider.abi_version = MY_PAL_VULKAN_PROVIDER_ABI_VERSION + 1u;
  provider.get_instance_extensions = test_vulkan_provider;
  provider.context = &called;
  provider.release_context = test_media_provider_release;
  ASSERT_EQ(my_pal_register_vulkan_provider(&pal, &provider),
            MY_RET_INVALID_PARAMS);

  provider.abi_version = MY_PAL_VULKAN_PROVIDER_ABI_VERSION;
  ASSERT_EQ(my_pal_register_vulkan_provider(&pal, &provider), MY_RET_OK);
  ASSERT_EQ(my_pal_get_vulkan_instance_extensions(&pal, NULL, &extensions),
            MY_RET_OK);
  ASSERT_TRUE(called);
  ASSERT_EQ(extensions.count, 2u);
  ASSERT_STR_EQ(extensions.names[0], "VK_KHR_surface");
  my_pal_unregister_vulkan_provider(&pal);
  ASSERT_EQ(my_pal_get_vulkan_instance_extensions(&pal, NULL, &extensions),
            MY_RET_NOT_SUPPORTED);

  provider.get_instance_extensions = test_vulkan_provider_fail;
  provider.context = &called;
  ASSERT_EQ(my_pal_register_vulkan_provider(&pal, &provider), MY_RET_OK);
  ASSERT_EQ(my_pal_get_vulkan_instance_extensions(&pal, NULL, &extensions),
            MY_RET_FAIL);
  ASSERT_EQ(extensions.count, 0u);
  my_pal_unregister_vulkan_provider(&pal);
}

TEST(pal_vulkan_provider_replacement_releases_old_context)
{
  static const my_pal_vtable_t pal_vtable = {0};
  my_pal_t pal = {&pal_vtable};
  uint32_t first_release = 0u;
  uint32_t second_release = 0u;
  my_pal_vulkan_provider_t first = {
      sizeof(first), MY_PAL_VULKAN_PROVIDER_ABI_VERSION,
      test_vulkan_provider, &first_release, test_vulkan_provider_release};
  my_pal_vulkan_provider_t second = {
      sizeof(second), MY_PAL_VULKAN_PROVIDER_ABI_VERSION,
      test_vulkan_provider, &second_release, test_vulkan_provider_release};

  ASSERT_EQ(my_pal_register_vulkan_provider(&pal, &first), MY_RET_OK);
  ASSERT_EQ(my_pal_register_vulkan_provider(&pal, &second), MY_RET_OK);
  ASSERT_EQ(first_release, 1u);
  my_pal_unregister_vulkan_provider(&pal);
  ASSERT_EQ(second_release, 1u);
}

TEST(pal_vulkan_provider_rejects_malformed_success_output)
{
  static const my_pal_vtable_t pal_vtable = {0};
  my_pal_t pal = {&pal_vtable};
  bool called = false;
  my_pal_vulkan_instance_extensions_t extensions;
  my_pal_vulkan_provider_t provider = {
      sizeof(provider), MY_PAL_VULKAN_PROVIDER_ABI_VERSION,
      test_vulkan_provider_malformed, &called, test_media_provider_release};

  ASSERT_EQ(my_pal_register_vulkan_provider(&pal, &provider), MY_RET_OK);
  ASSERT_EQ(my_pal_get_vulkan_instance_extensions(&pal, NULL, &extensions),
            MY_RET_INVALID_PARAMS);
  ASSERT_TRUE(called);
  ASSERT_EQ(extensions.count, 0u);
  my_pal_unregister_vulkan_provider(&pal);
}

TEST(pal_vulkan_provider_unregister_defers_release_until_callback_returns)
{
  static const my_pal_vtable_t pal_vtable = {0};
  my_pal_t pal = {&pal_vtable};
  vulkan_reentrant_state_t state = {&pal, 0u};
  my_pal_vulkan_instance_extensions_t extensions;
  const my_pal_vulkan_provider_t provider = {
      sizeof(provider), MY_PAL_VULKAN_PROVIDER_ABI_VERSION,
      vulkan_unregister_reentrant_provider, &state,
      vulkan_reentrant_release};

  ASSERT_EQ(my_pal_register_vulkan_provider(&pal, &provider), MY_RET_OK);
  ASSERT_EQ(my_pal_get_vulkan_instance_extensions(&pal, NULL, &extensions),
            MY_RET_OK);
  ASSERT_EQ(extensions.count, 1u);
  ASSERT_STR_EQ(extensions.names[0], "VK_KHR_surface");
  ASSERT_EQ(state.release_count, 1u);
  ASSERT_EQ(my_pal_get_vulkan_instance_extensions(&pal, NULL, &extensions),
            MY_RET_NOT_SUPPORTED);
}

TEST(pal_media_provider_callback_can_unregister_once)
{
  static const my_pal_vtable_t pal_vtable = {0};
  my_pal_t pal = {&pal_vtable};
  media_reentrant_state_t state = {&pal, MY_RET_FAIL, 0u};
  const my_pal_media_provider_t provider = {
      sizeof(provider), MY_PAL_MEDIA_PROVIDER_ABI_VERSION,
      media_unregister_reentrant_provider, &state, media_reentrant_release};
  my_pal_media_context_ex_t context = {0};

  ASSERT_EQ(my_pal_register_media_provider(&pal, &provider), MY_RET_OK);
  ASSERT_EQ(my_pal_get_media_context_ex(&pal, &context), MY_RET_OK);
  ASSERT_EQ(state.release_count, 1u);
  ASSERT_EQ(my_pal_get_media_context_ex(&pal, &context), MY_RET_NOT_SUPPORTED);
}

TEST(pal_media_provider_unregister_blocks_new_queries)
{
  static const my_pal_vtable_t pal_vtable = {0};
  my_pal_t pal = {&pal_vtable};
  my_pal_media_context_ex_t context = {0};
  bool called = false;
  const my_pal_media_provider_t provider = {
      sizeof(provider), MY_PAL_MEDIA_PROVIDER_ABI_VERSION,
      test_media_provider, &called, test_media_provider_release};

  ASSERT_EQ(my_pal_register_media_provider(&pal, &provider), MY_RET_OK);
  my_pal_unregister_media_provider(&pal);
  ASSERT_EQ(my_pal_get_media_context_ex(&pal, &context), MY_RET_NOT_SUPPORTED);
  ASSERT_FALSE(called);
}

TEST(pal_media_provider_replacement_releases_old_context)
{
  static const my_pal_vtable_t pal_vtable = {0};
  my_pal_t pal = {&pal_vtable};
  my_pal_media_context_ex_t context = {0};
  uint32_t first_release_count = 0u;
  uint32_t second_release_count = 0u;
  const my_pal_media_provider_t first = {
      sizeof(first), MY_PAL_MEDIA_PROVIDER_ABI_VERSION,
      test_media_provider_noop, &first_release_count,
      test_media_provider_counted_release};
  const my_pal_media_provider_t second = {
      sizeof(second), MY_PAL_MEDIA_PROVIDER_ABI_VERSION,
      test_media_provider_noop, &second_release_count,
      test_media_provider_counted_release};

  ASSERT_EQ(my_pal_register_media_provider(&pal, &first), MY_RET_OK);
  ASSERT_EQ(my_pal_register_media_provider(&pal, &second), MY_RET_OK);
  ASSERT_EQ(first_release_count, 1u);
  ASSERT_EQ(my_pal_get_media_context_ex(&pal, &context), MY_RET_OK);
  my_pal_unregister_media_provider(&pal);
  ASSERT_EQ(second_release_count, 1u);
}

#if !defined(_WIN32)
typedef struct media_inflight_state_t {
  atomic_bool entered;
  atomic_bool finish;
  atomic_uint release_count;
} media_inflight_state_t;

static my_ret_t media_inflight_provider(void *context,
                                        my_pal_media_context_ex_t *out) {
  media_inflight_state_t *state = (media_inflight_state_t *)context;
  atomic_store_explicit(&state->entered, true, memory_order_release);
  while (!atomic_load_explicit(&state->finish, memory_order_acquire)) {
    sched_yield();
  }
  if (out == NULL) return MY_RET_INVALID_PARAMS;
  *out = (my_pal_media_context_ex_t){0};
  return MY_RET_OK;
}

static void media_inflight_release(void *context) {
  media_inflight_state_t *state = (media_inflight_state_t *)context;
  atomic_fetch_add_explicit(&state->release_count, 1u, memory_order_relaxed);
}

typedef struct media_query_thread_t {
  my_pal_t *pal;
  my_ret_t result;
} media_query_thread_t;

static void *media_query_thread(void *context) {
  media_query_thread_t *query = (media_query_thread_t *)context;
  my_pal_media_context_ex_t out;
  query->result = my_pal_get_media_context_ex(query->pal, &out);
  return NULL;
}

TEST(pal_media_unregister_defers_release_until_inflight_query_finishes)
{
  static const my_pal_vtable_t pal_vtable = {0};
  my_pal_t pal = {&pal_vtable};
  media_inflight_state_t state;
  media_query_thread_t query = {&pal, MY_RET_FAIL};
  pthread_t thread;
  const my_pal_media_provider_t provider = {
      sizeof(provider), MY_PAL_MEDIA_PROVIDER_ABI_VERSION,
      media_inflight_provider, &state, media_inflight_release};

  atomic_init(&state.entered, false);
  atomic_init(&state.finish, false);
  atomic_init(&state.release_count, 0u);
  ASSERT_EQ(my_pal_register_media_provider(&pal, &provider), MY_RET_OK);
  ASSERT_EQ(pthread_create(&thread, NULL, media_query_thread, &query), 0);
  while (!atomic_load_explicit(&state.entered, memory_order_acquire)) {
    sched_yield();
  }
  my_pal_unregister_media_provider(&pal);
  ASSERT_EQ(atomic_load_explicit(&state.release_count, memory_order_relaxed),
            0u);
  /* A retiring slot cannot be reused for the same PAL while its callback is
   * still running. */
  ASSERT_EQ(my_pal_register_media_provider(&pal, &provider), MY_RET_PENDING);
  atomic_store_explicit(&state.finish, true, memory_order_release);
  ASSERT_EQ(pthread_join(thread, NULL), 0);
  ASSERT_EQ(query.result, MY_RET_OK);
  ASSERT_EQ(atomic_load_explicit(&state.release_count, memory_order_relaxed),
            1u);
  ASSERT_EQ(my_pal_register_media_provider(&pal, &provider), MY_RET_OK);
  my_pal_unregister_media_provider(&pal);
}
#endif

TEST(break_ui_dimensions_fit_signed_myui_contract)
{
  ASSERT_TRUE(break_ui_dimensions_fit_myui(1u, 1u));
  ASSERT_TRUE(break_ui_dimensions_fit_myui((u32)INT32_MAX, 1u));
  ASSERT_TRUE(!break_ui_dimensions_fit_myui((u32)INT32_MAX + 1u, 1u));
  ASSERT_TRUE(!break_ui_dimensions_fit_myui(1u, (u32)INT32_MAX + 1u));
}

TEST_MAIN_BEGIN()
    RUN_TEST(break_ui_command_executes_once_and_releases_context);
    RUN_TEST(dummy_ui_command_executes_once_and_releases_context);
    RUN_TEST(break_ui_command_cancel_skips_execution);
    RUN_TEST(dummy_ui_command_destroy_releases_queued_context);
#if !defined(_WIN32)
    RUN_TEST(dummy_ui_command_scope_close_races_with_producers);
    RUN_TEST(dummy_ui_command_dispatches_while_producers_submit);
#endif
    RUN_TEST(posted_events_are_fifo_and_dispatched);
    RUN_TEST(posted_event_burst_preserves_fifo);
    RUN_TEST(posted_events_are_safe_for_concurrent_producers);
    RUN_TEST(dummy_posted_events_are_safe_for_concurrent_producers);
    RUN_TEST(posted_ime_event_owns_text_until_dispatch);
    RUN_TEST(dummy_posted_ime_event_owns_text_until_dispatch);
    RUN_TEST(idle_run_returns_without_blocking);
    RUN_TEST(embedded_pal_does_not_expose_a_private_vulkan_surface);
    RUN_TEST(pal_public_wrappers_reject_null_objects);
    RUN_TEST(pal_optional_wrapper_handles_partial_vtables);
    RUN_TEST(pal_media_extension_keeps_legacy_vtable_compatible);
    RUN_TEST(pal_media_provider_reentry_does_not_replace_active_callback);
    RUN_TEST(pal_vulkan_provider_validates_abi_and_clears_failed_query);
    RUN_TEST(pal_vulkan_provider_replacement_releases_old_context);
    RUN_TEST(pal_vulkan_provider_rejects_malformed_success_output);
    RUN_TEST(pal_vulkan_provider_unregister_defers_release_until_callback_returns);
    RUN_TEST(pal_media_provider_callback_can_unregister_once);
    RUN_TEST(pal_media_provider_unregister_blocks_new_queries);
    RUN_TEST(pal_media_provider_replacement_releases_old_context);
#if !defined(_WIN32)
    RUN_TEST(pal_media_unregister_defers_release_until_inflight_query_finishes);
#endif
    RUN_TEST(break_ui_dimensions_fit_signed_myui_contract);
TEST_MAIN_END()
