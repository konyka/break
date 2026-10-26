#include "test_framework.h"
#include "mypal/my_timer.h"
#include <platform/time.h>

#define TIMER_PENDING_DEFAULT 10000u
#define TIMER_ROUNDS_DEFAULT 5u

typedef struct pending_bench_t {
  my_timer_manager_t* manager;
  uint64_t now;
  uint64_t callback_us;
  uint32_t* ids;
  uint32_t count;
  uint32_t added;
  uint32_t failures;
} pending_bench_t;

static uint64_t pending_now(void* context) {
  return ((pending_bench_t*)context)->now;
}

static my_ret_t pending_noop(void* context) {
  (void)context;
  return MY_RET_FAIL;
}

static my_ret_t pending_add_batch(void* context) {
  pending_bench_t* bench = (pending_bench_t*)context;
  uint64_t start = time_microseconds();
  uint32_t i;
  for (i = 0; i < bench->count; ++i) {
    bench->ids[i] = my_timer_add(bench->manager, pending_noop, NULL, 1u);
    if (bench->ids[i] == 0u) {
      bench->failures++;
      break;
    }
    bench->added++;
  }
  bench->callback_us = time_microseconds() - start;
  return MY_RET_OK;
}

static uint32_t pending_env_u32(const char* name, uint32_t fallback,
                               uint32_t maximum) {
  const char* text = getenv(name);
  unsigned long value;
  if (text == NULL || *text == '\0') return fallback;
  value = strtoul(text, NULL, 10);
  if (value == 0) return fallback;
  if (value > maximum) return maximum;
  return (uint32_t)value;
}

TEST(timer_pending_batch_commit_baseline)
{
  uint32_t count = pending_env_u32("QNX_TIMER_PENDING_COUNT",
                                   TIMER_PENDING_DEFAULT, 100000u);
  uint32_t rounds = pending_env_u32("QNX_TIMER_PERF_ROUNDS",
                                    TIMER_ROUNDS_DEFAULT, 100u);
  uint32_t round;
  for (round = 0; round < rounds; ++round) {
    pending_bench_t bench;
    uint64_t start;
    uint64_t total;
    memset(&bench, 0, sizeof(bench));
    bench.ids = (uint32_t*)calloc(count, sizeof(uint32_t));
    ASSERT_NOT_NULL(bench.ids);
    bench.count = count;
    bench.manager = my_timer_manager_create(NULL, pending_now, &bench);
    ASSERT_NOT_NULL(bench.manager);
    ASSERT_NEQ(my_timer_add(bench.manager, pending_add_batch, &bench, 1u), 0u);
    bench.now = 1u;
    start = time_microseconds();
    ASSERT_EQ(my_timer_manager_fire(bench.manager), 1u);
    total = time_microseconds() - start;
    ASSERT_EQ(bench.failures, 0u);
    ASSERT_EQ(bench.added, count);
    ASSERT_EQ(my_timer_manager_due_in_ms(bench.manager), 1u);
    printf("timer_pending,round=%u,count=%u,callback_us=%llu,commit_us=%llu,fire_us=%llu\n",
           round, count, (unsigned long long)bench.callback_us,
           (unsigned long long)(total >= bench.callback_us
                                    ? total - bench.callback_us
                                    : 0u),
           (unsigned long long)total);
    my_timer_manager_destroy(bench.manager);
    free(bench.ids);
  }
}

TEST_MAIN_BEGIN()
  time_init();
  RUN_TEST(timer_pending_batch_commit_baseline);
TEST_MAIN_END()
