#include "test_framework.h"
#include <platform/time.h>
#include <core/platform_thread.h>
#include <stdatomic.h>

#if defined(PLATFORM_THREAD_POSIX) && !defined(__APPLE__)
#include <errno.h>
#include <time.h>

static int sleep_calls;
static int sleep_error;
static bool sleep_saw_remaining;
static long sleep_request_ns[4];

int __real_nanosleep(const struct timespec *request, struct timespec *remaining);

int __wrap_nanosleep(const struct timespec *request, struct timespec *remaining)
{
    int call = sleep_calls;
    if (call < 4) {
        sleep_request_ns[call] = (long)(request->tv_sec * 1000000000L +
                                       request->tv_nsec);
    }
    sleep_calls++;
    if (sleep_error == EINTR && sleep_calls <= 2) {
        if (remaining != NULL) {
            sleep_saw_remaining = true;
            remaining->tv_sec = 0;
            remaining->tv_nsec = sleep_calls == 1 ? 750000L : 250000L;
        }
        errno = EINTR;
        return -1;
    }
    if (sleep_error == EINTR) return 0;
    errno = sleep_error;
    return -1;
}

TEST(posix_sleep_retries_eintr_with_remaining_time)
{
    sleep_calls = 0;
    sleep_error = EINTR;
    sleep_saw_remaining = false;
    memset(sleep_request_ns, 0, sizeof(sleep_request_ns));
    time_sleep_us(1500u);
    ASSERT_EQ(sleep_calls, 3);
    ASSERT_TRUE(sleep_saw_remaining);
    ASSERT_EQ(sleep_request_ns[0], 1500000L);
    ASSERT_EQ(sleep_request_ns[1], 750000L);
    ASSERT_EQ(sleep_request_ns[2], 250000L);
}

TEST(posix_sleep_permanent_error_does_not_spin)
{
    sleep_calls = 0;
    sleep_error = EINVAL;
    sleep_saw_remaining = false;
    time_sleep_us(1500u);
    ASSERT_EQ(sleep_calls, 1);
}
#endif

TEST(future_time_delta_does_not_underflow)
{
    u64 future = time_microseconds() + 1000000u;
    ASSERT_FLOAT_EQ(time_delta_since(future), 0.0, 0.0);
}

static _Atomic int clock_failures;

static PLATFORM_THREAD_RET clock_reader(PLATFORM_THREAD_ARG argument)
{
    u64 previous;
    int i;
    (void)argument;
    previous = time_microseconds();
    for (i = 0; i < 20000; i++) {
        u64 now = time_microseconds();
        if (now < previous) atomic_fetch_add(&clock_failures, 1);
        previous = now;
    }
    return PLATFORM_THREAD_RETURN;
}

TEST(clock_reads_are_monotonic_across_threads)
{
    PlatformThread threads[4];
    int created = 0;
    int i;
    atomic_store(&clock_failures, 0);
    for (i = 0; i < 4; i++) {
        if (!platform_thread_create(&threads[i], clock_reader, NULL)) break;
        created++;
    }
    ASSERT_EQ(created, 4);
    for (i = 0; i < created; i++) platform_thread_join(threads[i]);
    ASSERT_EQ(atomic_load(&clock_failures), 0);
}

TEST_MAIN_BEGIN()
    time_init();
    RUN_TEST(future_time_delta_does_not_underflow);
#if defined(PLATFORM_THREAD_POSIX) && !defined(__APPLE__)
    RUN_TEST(posix_sleep_retries_eintr_with_remaining_time);
    RUN_TEST(posix_sleep_permanent_error_does_not_spin);
#endif
    RUN_TEST(clock_reads_are_monotonic_across_threads);
TEST_MAIN_END()
