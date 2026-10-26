#include "test_framework.h"
#include "mypal/break/my_pal_break.h"
#include "myui/my_ui_command.h"
#include <core/platform_thread.h>
#include <platform/time.h>
#include <stdatomic.h>

#define TIMER_PRODUCERS 4u
#define TIMER_PER_PRODUCER 64u
#define TIMER_REQUEST_COUNT (TIMER_PRODUCERS * TIMER_PER_PRODUCER)
#define TIMER_WAIT_LIMIT_US 5000000u

typedef struct timed_request_t {
  my_pal_main_loop_t* loop;
  uint32_t interval_ms;
  uint64_t due_us;
  int64_t latency_us;
  atomic_int fired;
  atomic_int destroyed;
  atomic_int add_failed;
} timed_request_t;

typedef struct timed_producer_t {
  my_pal_main_loop_t* loop;
  timed_request_t* requests;
  atomic_int failures;
} timed_producer_t;

static my_ret_t timed_one_shot(void* context) {
  timed_request_t* request = (timed_request_t*)context;
  int64_t now = (int64_t)time_microseconds();
  request->latency_us = now - (int64_t)request->due_us;
  atomic_fetch_add(&request->fired, 1);
  return MY_RET_FAIL;
}

static my_ret_t timed_command_execute(void* context) {
  timed_request_t* request = (timed_request_t*)context;
  request->due_us = time_microseconds() + (uint64_t)request->interval_ms * 1000u;
  if (my_pal_main_loop_add_timer(request->loop, timed_one_shot, request,
                                 request->interval_ms) == 0u) {
    atomic_fetch_add(&request->add_failed, 1);
    return MY_RET_FAIL;
  }
  return MY_RET_OK;
}

static void timed_command_destroy(void* context) {
  timed_request_t* request = (timed_request_t*)context;
  atomic_fetch_add(&request->destroyed, 1);
}

static my_ret_t timed_command_event(void* context, my_pal_window_t* window,
                                    const my_event_t* event) {
  (void)context;
  (void)window;
  if (event->type != MY_EVENT_COMMAND) return MY_RET_FAIL;
  my_ui_command_dispatch((my_ui_command_t*)event->u.command.data);
  return MY_RET_OK;
}

static PLATFORM_THREAD_RET timed_producer_run(PLATFORM_THREAD_ARG argument) {
  timed_producer_t* producer = (timed_producer_t*)argument;
  uint32_t i;
  for (i = 0; i < TIMER_PER_PRODUCER; ++i) {
    my_ui_command_t* command = my_ui_command_create(
        NULL, timed_command_execute, &producer->requests[i],
        timed_command_destroy);
    my_ret_t result;
    if (command == NULL) {
      atomic_fetch_add(&producer->failures, 1);
      continue;
    }
    result = my_ui_command_submit(producer->loop, command);
    if (result != MY_RET_OK) atomic_fetch_add(&producer->failures, 1);
    my_ui_command_unref(command);
  }
  return PLATFORM_THREAD_RETURN;
}

static int timed_latency_compare(const void* left, const void* right) {
  int64_t a = *(const int64_t*)left;
  int64_t b = *(const int64_t*)right;
  return a < b ? -1 : a > b ? 1 : 0;
}

static int64_t timed_percentile(const int64_t* values, uint32_t count,
                                uint32_t percent) {
  return values[(count - 1u) * percent / 100u];
}

static bool timed_run_case(uint32_t interval_ms) {
  my_pal_t* pal = my_pal_break_create(NULL, (Platform*)(uintptr_t)1, NULL);
  my_pal_main_loop_t* loop = pal != NULL ? my_pal_main_loop_create(pal) : NULL;
  timed_request_t requests[TIMER_REQUEST_COUNT];
  timed_producer_t producers[TIMER_PRODUCERS];
  PlatformThread threads[TIMER_PRODUCERS];
  int64_t latencies[TIMER_REQUEST_COUNT];
  uint32_t created = 0u;
  uint32_t expected;
  uint32_t fired = 0u;
  uint32_t destroyed = 0u;
  uint32_t failures = 0u;
  uint32_t i;
  uint64_t deadline;
  bool success;

  if (loop == NULL) {
    if (pal != NULL) my_pal_destroy(pal);
    return false;
  }
  memset(requests, 0, sizeof(requests));
  memset(producers, 0, sizeof(producers));
  for (i = 0; i < TIMER_REQUEST_COUNT; ++i) {
    requests[i].loop = loop;
    requests[i].interval_ms = interval_ms;
    atomic_init(&requests[i].fired, 0);
    atomic_init(&requests[i].destroyed, 0);
    atomic_init(&requests[i].add_failed, 0);
  }
  (void)my_pal_set_event_handler(pal, timed_command_event, NULL);
  for (i = 0; i < TIMER_PRODUCERS; ++i) {
    producers[i].loop = loop;
    producers[i].requests = &requests[i * TIMER_PER_PRODUCER];
    atomic_init(&producers[i].failures, 0);
    if (!platform_thread_create(&threads[i], timed_producer_run,
                                &producers[i])) {
      break;
    }
    created++;
  }

  expected = created * TIMER_PER_PRODUCER;
  deadline = time_microseconds() + TIMER_WAIT_LIMIT_US;
  while (fired + destroyed < expected * 2u &&
         time_microseconds() < deadline) {
    if (my_pal_break_pump(loop) == 0u) {
      time_sleep_us(100u);
    } else {
      platform_thread_yield();
    }
    fired = 0u;
    destroyed = 0u;
    for (i = 0; i < expected; ++i) {
      fired += (uint32_t)atomic_load(&requests[i].fired);
      destroyed += (uint32_t)atomic_load(&requests[i].destroyed);
    }
  }
  for (i = 0; i < created; ++i) platform_thread_join(threads[i]);
  for (i = 0; i < expected * 4u && my_pal_break_pump(loop) != 0u; ++i) {
  }
  my_pal_main_loop_destroy(loop);
  my_pal_destroy(pal);

  fired = 0u;
  destroyed = 0u;
  for (i = 0; i < expected; ++i) {
    fired += (uint32_t)atomic_load(&requests[i].fired);
    destroyed += (uint32_t)atomic_load(&requests[i].destroyed);
    failures += (uint32_t)atomic_load(&requests[i].add_failed);
    latencies[i] = requests[i].latency_us;
  }
  for (i = 0; i < created; ++i) failures += (uint32_t)atomic_load(&producers[i].failures);
  printf("timer_concurrent,interval_ms=%u,created=%u,fired=%u,destroyed=%u,failures=%u\n",
         interval_ms, created, fired, destroyed, failures);
  success = created == TIMER_PRODUCERS && failures == 0u &&
            fired == TIMER_REQUEST_COUNT && destroyed == TIMER_REQUEST_COUNT;
  if (success) {
    qsort(latencies, expected, sizeof(latencies[0]), timed_latency_compare);
    printf("timer_concurrent_latency,interval_ms=%u,p50=%lld,p95=%lld,p99=%lld,max=%lld\n",
           interval_ms,
           (long long)timed_percentile(latencies, expected, 50u),
           (long long)timed_percentile(latencies, expected, 95u),
           (long long)timed_percentile(latencies, expected, 99u),
           (long long)latencies[expected - 1u]);
  }
  return success;
}

TEST(concurrent_timer_requests_are_timely_and_complete)
{
  ASSERT_TRUE(timed_run_case(1u));
  ASSERT_TRUE(timed_run_case(5u));
  ASSERT_TRUE(timed_run_case(16u));
  ASSERT_TRUE(timed_run_case(100u));
}

TEST_MAIN_BEGIN()
  time_init();
  RUN_TEST(concurrent_timer_requests_are_timely_and_complete);
TEST_MAIN_END()
