#include "test_framework.h"
#include "mypal/screen/my_pal_screen.h"
#include "myui/my_ui_command.h"
#include <core/platform_thread.h>
#include <platform/time.h>
#include <screen/screen.h>
#include <stdatomic.h>

static atomic_int screen_wake_count;

int __real_screen_send_event(screen_context_t context, screen_event_t event,
                             pid_t pid);
int __wrap_screen_send_event(screen_context_t context, screen_event_t event,
                             pid_t pid) {
  atomic_fetch_add_explicit(&screen_wake_count, 1, memory_order_relaxed);
  return __real_screen_send_event(context, event, pid);
}

#define SCREEN_PRODUCERS 4u
#define SCREEN_COMMANDS_PER_PRODUCER 64u
#define SCREEN_COMMAND_COUNT (SCREEN_PRODUCERS * SCREEN_COMMANDS_PER_PRODUCER)
#define SCREEN_STRESS_TIMEOUT_US 5000000u

typedef struct screen_stress_t screen_stress_t;

typedef struct screen_request_t {
  screen_stress_t* state;
  uint64_t due_us;
  int64_t latency_us;
  uint32_t interval_ms;
  uint32_t producer;
  uint32_t sequence;
} screen_request_t;

typedef struct screen_producer_t {
  screen_stress_t* state;
  uint32_t producer;
} screen_producer_t;

struct screen_stress_t {
  my_pal_main_loop_t* loop;
  screen_request_t requests[SCREEN_COMMAND_COUNT];
  screen_producer_t producers[SCREEN_PRODUCERS];
  uint32_t producer_next[SCREEN_PRODUCERS];
  uint32_t order_errors;
  atomic_int commands;
  atomic_int fired;
  atomic_int destroyed;
  atomic_int failures;
  atomic_int finished;
  uint64_t deadline_us;
  bool timed_out;
};

#define SCREEN_TIMER_EARLY_TOLERANCE_US 1000
#define SCREEN_TIMER_P99_BUDGET_US 25000
#define SCREEN_TIMER_MAX_BUDGET_US 250000

static void screen_stress_check_complete(screen_stress_t* state) {
  if (atomic_load_explicit(&state->finished, memory_order_acquire) ==
          (int)SCREEN_PRODUCERS &&
      atomic_load_explicit(&state->commands, memory_order_acquire) ==
          (int)SCREEN_COMMAND_COUNT &&
      atomic_load_explicit(&state->fired, memory_order_acquire) ==
          (int)SCREEN_COMMAND_COUNT &&
      atomic_load_explicit(&state->destroyed, memory_order_acquire) ==
          (int)SCREEN_COMMAND_COUNT) {
    (void)my_pal_main_loop_quit(state->loop);
  }
}

static my_ret_t screen_request_timer(void* context) {
  screen_request_t* request = (screen_request_t*)context;
  request->latency_us = (int64_t)time_microseconds() - (int64_t)request->due_us;
  if (request->latency_us < -SCREEN_TIMER_EARLY_TOLERANCE_US ||
      request->latency_us > SCREEN_TIMER_MAX_BUDGET_US) {
    atomic_fetch_add_explicit(&request->state->failures, 1,
                              memory_order_release);
  }
  atomic_fetch_add_explicit(&request->state->fired, 1, memory_order_release);
  screen_stress_check_complete(request->state);
  return MY_RET_FAIL;
}

static my_ret_t screen_request_execute(void* context) {
  screen_request_t* request = (screen_request_t*)context;
  screen_stress_t* state = request->state;
  if (state->producer_next[request->producer] != request->sequence) {
    state->order_errors++;
  } else {
    state->producer_next[request->producer]++;
  }
  request->due_us =
      (time_microseconds() / 1000u + (uint64_t)request->interval_ms) * 1000u;
  if (my_pal_main_loop_add_timer(state->loop, screen_request_timer, request,
                                 request->interval_ms) == 0u) {
    atomic_fetch_add_explicit(&state->failures, 1, memory_order_release);
  }
  atomic_fetch_add_explicit(&state->commands, 1, memory_order_release);
  return MY_RET_OK;
}

static void screen_request_destroy(void* context) {
  screen_request_t* request = (screen_request_t*)context;
  atomic_fetch_add_explicit(&request->state->destroyed, 1,
                            memory_order_release);
}

static my_ret_t screen_stress_event(void* context, my_pal_window_t* window,
                                    const my_event_t* event) {
  (void)context;
  (void)window;
  if (event->type == MY_EVENT_COMMAND) {
    my_ui_command_dispatch((my_ui_command_t*)event->u.command.data);
  }
  return MY_RET_OK;
}

static PLATFORM_THREAD_RET screen_producer_run(PLATFORM_THREAD_ARG argument) {
  screen_producer_t* producer = (screen_producer_t*)argument;
  screen_stress_t* state = producer->state;
  uint32_t i;
  for (i = 0u; i < SCREEN_COMMANDS_PER_PRODUCER; ++i) {
    screen_request_t* request =
        &state->requests[producer->producer * SCREEN_COMMANDS_PER_PRODUCER + i];
    my_ui_command_t* command = my_ui_command_create(
        NULL, screen_request_execute, request, screen_request_destroy);
    if (command == NULL ||
        my_ui_command_submit(state->loop, command) != MY_RET_OK) {
      atomic_fetch_add_explicit(&state->failures, 1, memory_order_release);
    }
    my_ui_command_unref(command);
  }
  atomic_fetch_add_explicit(&state->finished, 1, memory_order_release);
  return PLATFORM_THREAD_RETURN;
}

static my_ret_t screen_stress_watchdog(void* context) {
  screen_stress_t* state = (screen_stress_t*)context;
  state->timed_out = true;
  (void)my_pal_main_loop_quit(state->loop);
  return MY_RET_FAIL;
}

static int screen_latency_compare(const void* left, const void* right) {
  int64_t a = *(const int64_t*)left;
  int64_t b = *(const int64_t*)right;
  return a < b ? -1 : a > b ? 1 : 0;
}

static int64_t screen_latency_percentile(const int64_t* values, uint32_t count,
                                         uint32_t percentile) {
  return values[(count - 1u) * percentile / 100u];
}

static bool screen_run_concurrency(uint32_t interval_ms) {
  my_pal_t* pal = my_pal_create(NULL);
  screen_stress_t state;
  PlatformThread threads[SCREEN_PRODUCERS];
  int64_t latencies[SCREEN_COMMAND_COUNT];
  uint32_t created = 0u;
  uint32_t i;
  uint64_t started_us;
  uint64_t elapsed_us;
  bool success;
  if (pal == NULL || my_pal_screen_native_context(pal) == NULL) {
    if (pal != NULL) my_pal_destroy(pal);
    return false;
  }
  memset(&state, 0, sizeof(state));
  state.loop = my_pal_main_loop_create(pal);
  if (state.loop == NULL) {
    my_pal_destroy(pal);
    return false;
  }
  state.deadline_us = time_microseconds() + SCREEN_STRESS_TIMEOUT_US;
  for (i = 0u; i < SCREEN_COMMAND_COUNT; ++i) {
    state.requests[i].state = &state;
    state.requests[i].interval_ms = interval_ms;
    state.requests[i].producer = i / SCREEN_COMMANDS_PER_PRODUCER;
    state.requests[i].sequence = i % SCREEN_COMMANDS_PER_PRODUCER;
  }
  (void)my_pal_set_event_handler(pal, screen_stress_event, NULL);
  if (my_pal_main_loop_add_timer(state.loop, screen_stress_watchdog, &state,
                                 SCREEN_STRESS_TIMEOUT_US / 1000u) == 0u) {
    my_pal_main_loop_destroy(state.loop);
    my_pal_destroy(pal);
    return false;
  }
  atomic_store_explicit(&screen_wake_count, 0, memory_order_relaxed);
  started_us = time_microseconds();
  for (i = 0u; i < SCREEN_PRODUCERS; ++i) {
    state.producers[i].state = &state;
    state.producers[i].producer = i;
    if (!platform_thread_create(&threads[i], screen_producer_run,
                                &state.producers[i])) {
      break;
    }
    created++;
  }
  if (created == SCREEN_PRODUCERS) {
    if (my_pal_main_loop_run(state.loop) != MY_RET_OK) {
      atomic_fetch_add_explicit(&state.failures, 1, memory_order_release);
    }
  } else {
    atomic_fetch_add_explicit(&state.failures, 1, memory_order_release);
  }
  elapsed_us = time_microseconds() - started_us;
  for (i = 0u; i < created; ++i) platform_thread_join(threads[i]);
  my_pal_main_loop_destroy(state.loop);
  my_pal_destroy(pal);
  success = created == SCREEN_PRODUCERS && !state.timed_out &&
            atomic_load_explicit(&state.failures, memory_order_acquire) == 0 &&
            atomic_load_explicit(&state.commands, memory_order_acquire) ==
                (int)SCREEN_COMMAND_COUNT &&
            atomic_load_explicit(&state.fired, memory_order_acquire) ==
                (int)SCREEN_COMMAND_COUNT &&
            atomic_load_explicit(&state.destroyed, memory_order_acquire) ==
                (int)SCREEN_COMMAND_COUNT &&
            state.order_errors == 0u &&
            atomic_load_explicit(&screen_wake_count, memory_order_relaxed) <=
                (int)(SCREEN_COMMAND_COUNT / SCREEN_PRODUCERS);
  printf("screen_timer_concurrency,interval_ms=%u,threads=%u,commands=%d,"
         "fired=%d,destroyed=%d,failures=%d,order_errors=%u,wakeups=%d,"
         "elapsed_us=%llu,timed_out=%d\n",
         interval_ms, created, atomic_load(&state.commands),
         atomic_load(&state.fired), atomic_load(&state.destroyed),
         atomic_load(&state.failures), state.order_errors,
         atomic_load(&screen_wake_count), (unsigned long long)elapsed_us,
         state.timed_out ? 1 : 0);
  if (success) {
    for (i = 0u; i < SCREEN_COMMAND_COUNT; ++i) {
      latencies[i] = state.requests[i].latency_us;
    }
    qsort(latencies, SCREEN_COMMAND_COUNT, sizeof(latencies[0]),
          screen_latency_compare);
    success =
        screen_latency_percentile(latencies, SCREEN_COMMAND_COUNT, 99u) <=
            SCREEN_TIMER_P99_BUDGET_US &&
        latencies[SCREEN_COMMAND_COUNT - 1u] <= SCREEN_TIMER_MAX_BUDGET_US;
    printf("screen_timer_latency,interval_ms=%u,p50=%lld,p95=%lld,p99=%lld,"
           "max=%lld,budget_ok=%d\n",
           interval_ms,
           (long long)screen_latency_percentile(latencies, SCREEN_COMMAND_COUNT,
                                                50u),
           (long long)screen_latency_percentile(latencies, SCREEN_COMMAND_COUNT,
                                                95u),
           (long long)screen_latency_percentile(latencies, SCREEN_COMMAND_COUNT,
                                                99u),
           (long long)latencies[SCREEN_COMMAND_COUNT - 1u], success ? 1 : 0);
  }
  return success;
}

TEST(screen_command_timer_concurrency)
{
  ASSERT_TRUE(screen_run_concurrency(1u));
  ASSERT_TRUE(screen_run_concurrency(5u));
  ASSERT_TRUE(screen_run_concurrency(16u));
  ASSERT_TRUE(screen_run_concurrency(100u));
}

typedef struct nested_command_state_t {
  my_pal_main_loop_t* loop;
  my_ret_t submit_result;
  my_ret_t run_result;
  int parent_executed;
  int child_executed;
  int parent_destroyed;
  int child_destroyed;
  bool timed_out;
} nested_command_state_t;

static my_ret_t screen_nested_child_execute(void* context) {
  nested_command_state_t* state = (nested_command_state_t*)context;
  state->child_executed++;
  (void)my_pal_main_loop_quit(state->loop);
  return MY_RET_OK;
}

static void screen_nested_child_destroy(void* context) {
  ((nested_command_state_t*)context)->child_destroyed++;
}

static my_ret_t screen_nested_parent_execute(void* context) {
  nested_command_state_t* state = (nested_command_state_t*)context;
  my_ui_command_t* child;
  state->parent_executed++;
  child = my_ui_command_create(NULL, screen_nested_child_execute, state,
                               screen_nested_child_destroy);
  if (child == NULL) {
    state->submit_result = MY_RET_OOM;
    (void)my_pal_main_loop_quit(state->loop);
    return MY_RET_OK;
  }
  state->submit_result = my_ui_command_submit(state->loop, child);
  my_ui_command_unref(child);
  if (state->submit_result != MY_RET_OK) {
    (void)my_pal_main_loop_quit(state->loop);
  }
  return MY_RET_OK;
}

static void screen_nested_parent_destroy(void* context) {
  ((nested_command_state_t*)context)->parent_destroyed++;
}

static my_ret_t screen_nested_timeout(void* context) {
  nested_command_state_t* state = (nested_command_state_t*)context;
  state->timed_out = true;
  (void)my_pal_main_loop_quit(state->loop);
  return MY_RET_FAIL;
}

TEST(screen_nested_commands_share_pending_wakeup)
{
  my_pal_t* pal = my_pal_create(NULL);
  my_pal_main_loop_t* loop;
  my_ui_command_t* parent;
  nested_command_state_t state;
  my_ret_t parent_submit;
  ASSERT_NOT_NULL(pal);
  memset(&state, 0, sizeof(state));
  state.submit_result = MY_RET_FAIL;
  loop = my_pal_main_loop_create(pal);
  if (loop == NULL) my_pal_destroy(pal);
  ASSERT_NOT_NULL(loop);
  state.loop = loop;
  (void)my_pal_set_event_handler(pal, screen_stress_event, NULL);
  if (my_pal_main_loop_add_timer(loop, screen_nested_timeout, &state, 1000u) ==
      0u) {
    my_pal_main_loop_destroy(loop);
    my_pal_destroy(pal);
    ASSERT_TRUE(false);
    return;
  }
  parent = my_ui_command_create(NULL, screen_nested_parent_execute, &state,
                                screen_nested_parent_destroy);
  if (parent == NULL) {
    my_pal_main_loop_destroy(loop);
    my_pal_destroy(pal);
    ASSERT_TRUE(false);
    return;
  }
  atomic_store_explicit(&screen_wake_count, 0, memory_order_relaxed);
  parent_submit = my_ui_command_submit(loop, parent);
  my_ui_command_unref(parent);
  state.run_result = my_pal_main_loop_run(loop);
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);
  printf("screen_nested_wakeup,parent_submit=%d,child_submit=%d,run_result=%d,"
         "parent_executed=%d,child_executed=%d,parent_destroyed=%d,"
         "child_destroyed=%d,wakeups=%d,timed_out=%d\n",
         parent_submit, state.submit_result, state.run_result,
         state.parent_executed, state.child_executed, state.parent_destroyed,
         state.child_destroyed,
         atomic_load_explicit(&screen_wake_count, memory_order_relaxed),
         state.timed_out ? 1 : 0);
  ASSERT_EQ(parent_submit, MY_RET_OK);
  ASSERT_EQ(state.submit_result, MY_RET_OK);
  ASSERT_EQ(state.run_result, MY_RET_OK);
  ASSERT_EQ(state.parent_executed, 1);
  ASSERT_EQ(state.child_executed, 1);
  ASSERT_EQ(state.parent_destroyed, 1);
  ASSERT_EQ(state.child_destroyed, 1);
  ASSERT_FALSE(state.timed_out);
  ASSERT_EQ(atomic_load_explicit(&screen_wake_count, memory_order_relaxed), 2);
}

static my_ret_t screen_destroy_batch_parent_execute(void* context) {
  nested_command_state_t* state = (nested_command_state_t*)context;
  state->parent_executed++;
  my_pal_main_loop_destroy(state->loop);
  state->loop = NULL;
  return MY_RET_OK;
}

static my_ret_t screen_destroy_batch_child_execute(void* context) {
  nested_command_state_t* state = (nested_command_state_t*)context;
  state->child_executed++;
  return MY_RET_OK;
}

TEST(screen_destroy_discards_detached_successors)
{
  my_pal_t* pal = my_pal_create(NULL);
  my_ui_command_t* parent;
  my_ui_command_t* child;
  nested_command_state_t state;
  my_ret_t parent_submit;
  my_ret_t child_submit;
  ASSERT_NOT_NULL(pal);
  memset(&state, 0, sizeof(state));
  state.loop = my_pal_main_loop_create(pal);
  if (state.loop == NULL) my_pal_destroy(pal);
  ASSERT_NOT_NULL(state.loop);
  (void)my_pal_set_event_handler(pal, screen_stress_event, NULL);
  if (my_pal_main_loop_add_timer(state.loop, screen_nested_timeout, &state,
                                 1000u) == 0u) {
    my_pal_main_loop_destroy(state.loop);
    my_pal_destroy(pal);
    ASSERT_TRUE(false);
    return;
  }
  parent = my_ui_command_create(NULL, screen_destroy_batch_parent_execute,
                                &state, screen_nested_parent_destroy);
  child = my_ui_command_create(NULL, screen_destroy_batch_child_execute,
                               &state, screen_nested_child_destroy);
  if (parent == NULL || child == NULL) {
    my_ui_command_unref(parent);
    my_ui_command_unref(child);
    my_pal_main_loop_destroy(state.loop);
    my_pal_destroy(pal);
    ASSERT_TRUE(false);
    return;
  }
  parent_submit = my_ui_command_submit(state.loop, parent);
  child_submit = my_ui_command_submit(state.loop, child);
  my_ui_command_unref(parent);
  my_ui_command_unref(child);
  state.run_result = my_pal_main_loop_run(state.loop);
  if (state.loop != NULL) my_pal_main_loop_destroy(state.loop);
  my_pal_destroy(pal);
  printf("screen_destroy_batch,parent_submit=%d,child_submit=%d,run_result=%d,"
         "parent_executed=%d,child_executed=%d,parent_destroyed=%d,"
         "child_destroyed=%d,timed_out=%d\n",
         parent_submit, child_submit, state.run_result, state.parent_executed,
         state.child_executed, state.parent_destroyed, state.child_destroyed,
         state.timed_out ? 1 : 0);
  ASSERT_EQ(parent_submit, MY_RET_OK);
  ASSERT_EQ(child_submit, MY_RET_OK);
  ASSERT_EQ(state.run_result, MY_RET_OK);
  ASSERT_EQ(state.parent_executed, 1);
  ASSERT_EQ(state.child_executed, 0);
  ASSERT_EQ(state.parent_destroyed, 1);
  ASSERT_EQ(state.child_destroyed, 1);
  ASSERT_FALSE(state.timed_out);
}

int main(void)
{
  my_pal_t* probe;
  setvbuf(stdout, NULL, _IONBF, 0);
  time_init();
  probe = my_pal_create(NULL);
  if (probe == NULL || my_pal_screen_native_context(probe) == NULL) {
    if (probe != NULL) my_pal_destroy(probe);
    printf("SKIP: no usable QNX Screen service\n");
    return getenv("BREAK_QNX_SCREEN_REQUIRED") != NULL ? 1 : 77;
  }
  my_pal_destroy(probe);
  printf("=== Running Tests ===\n");
  RUN_TEST(screen_command_timer_concurrency);
  RUN_TEST(screen_nested_commands_share_pending_wakeup);
  RUN_TEST(screen_destroy_discards_detached_successors);
  printf("\n=== Results: %d passed, %d failed, %d total ===\n",
         g_test_pass, g_test_fail, g_test_count);
  return g_test_fail > 0 ? 1 : 0;
}
