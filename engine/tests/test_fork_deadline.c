#include "test_framework.h"

#if !defined(_WIN32)
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

static pid_t test_waitpid_inject(pid_t pid, int *status, int options);
static int test_kill_inject(pid_t pid, int signal_number);
#define waitpid test_waitpid_inject
#define kill test_kill_inject
#include "test_fork.h"
#undef waitpid
#undef kill

static unsigned waitpid_inject_calls;
static int waitpid_inject_eintr;
static long long waitpid_inject_eintr_until_ms;
static int waitpid_inject_error;
static unsigned kill_inject_calls;
static int kill_inject_observe_only;

static long long monotonic_ms(void);

static void test_waitpid_reset_injection(void)
{
    waitpid_inject_calls = 0u;
    waitpid_inject_eintr = 0;
    waitpid_inject_eintr_until_ms = 0;
    waitpid_inject_error = 0;
    kill_inject_calls = 0u;
    kill_inject_observe_only = 0;
}

static pid_t test_waitpid_inject(pid_t pid, int *status, int options)
{
    waitpid_inject_calls++;
    if (options == WNOHANG && waitpid_inject_eintr_until_ms > 0) {
        if (monotonic_ms() < waitpid_inject_eintr_until_ms) {
            errno = EINTR;
            return (pid_t)-1;
        }
        waitpid_inject_eintr_until_ms = 0;
    }
    if (waitpid_inject_eintr != 0) {
        waitpid_inject_eintr = 0;
        errno = EINTR;
        return (pid_t)-1;
    }
    if (waitpid_inject_error != 0) {
        int error = waitpid_inject_error;
        waitpid_inject_error = 0;
        errno = error;
        return (pid_t)-1;
    }
    return waitpid(pid, status, options);
}

static int test_kill_inject(pid_t pid, int signal_number)
{
    kill_inject_calls++;
    if (kill_inject_observe_only != 0) {
        return 0;
    }
    return kill(pid, signal_number);
}

static int test_waitpid_fallback_reap(pid_t pid)
{
    int local_status = 0;
    for (;;) {
        pid_t r = waitpid(pid, &local_status, WNOHANG);
        if (r == pid) {
            return 1;
        }
        if (r == 0) {
            if (kill(pid, SIGKILL) != 0) {
                return -1;
            }
            do {
                r = waitpid(pid, &local_status, 0);
            } while (r < 0 && errno == EINTR);
            if (r == pid) {
                return 1;
            }
            if (r < 0 && errno == ECHILD) {
                return 0;
            }
            return -1;
        }
        if (errno == EINTR) {
            continue;
        }
        if (errno == ECHILD) {
            return 0;
        }
        return -1;
    }
}

static long long monotonic_ms(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (long long)ts.tv_sec * 1000LL + ts.tv_nsec / 1000000LL;
}

TEST(waitpid_deadline_reports_normal_exit)
{
    int status = 0;
    pid_t pid = fork();
    if (pid == 0) {
        _exit(7);
    }
    ASSERT_TRUE(pid > 0);
    ASSERT_EQ(test_waitpid_deadline(pid, &status, 5000u), pid);
    ASSERT_TRUE(WIFEXITED(status));
    ASSERT_EQ(WEXITSTATUS(status), 7);
}

TEST(waitpid_deadline_reports_abort_signal)
{
    int status = 0;
    pid_t pid = fork();
    if (pid == 0) {
        abort();
    }
    ASSERT_TRUE(pid > 0);
    ASSERT_EQ(test_waitpid_deadline(pid, &status, 5000u), pid);
    ASSERT_TRUE(WIFSIGNALED(status));
    ASSERT_EQ(WTERMSIG(status), SIGABRT);
}

TEST(waitpid_deadline_kills_and_reaps_stuck_child)
{
    int status = 0;
    long long start;
    long long elapsed;
    pid_t pid = fork();
    if (pid == 0) {
        for (;;) {
            pause();
        }
    }
    ASSERT_TRUE(pid > 0);
    start = monotonic_ms();
    status = -1;
    ASSERT_EQ(test_waitpid_deadline(pid, &status, 200u), (pid_t)0);
    elapsed = monotonic_ms() - start;
    ASSERT_EQ(status, 0);
    ASSERT_TRUE(elapsed >= 200);
    ASSERT_TRUE(elapsed < 5000);
    errno = 0;
    ASSERT_EQ(waitpid(pid, &status, WNOHANG), (pid_t)-1);
    ASSERT_EQ(errno, ECHILD);
}

TEST(waitpid_deadline_retries_eintr_before_normal_exit)
{
    int status = -1;
    unsigned calls;
    int fallback;
    pid_t result;
    pid_t pid;
    test_waitpid_reset_injection();
    pid = fork();
    if (pid == 0) {
        _exit(0);
    }
    ASSERT_TRUE(pid > 0);
    waitpid_inject_eintr = 1;
    result = test_waitpid_deadline(pid, &status, 5000u);
    calls = waitpid_inject_calls;
    fallback = test_waitpid_fallback_reap(pid);
    printf("INJECTION cleanup=%d result=%d status=%d calls=%u\n",
           fallback, (int)result, status, calls);
    ASSERT_EQ(result, pid);
    ASSERT_TRUE(WIFEXITED(status));
    ASSERT_EQ(WEXITSTATUS(status), 0);
    ASSERT_TRUE(calls >= 2u);
    ASSERT_EQ(fallback, 0);
}

TEST(waitpid_deadline_retries_eintr_before_timeout_cleanup)
{
    int status = -1;
    unsigned calls;
    int fallback;
    long long start;
    long long elapsed;
    pid_t result;
    pid_t pid;
    test_waitpid_reset_injection();
    pid = fork();
    if (pid == 0) {
        for (;;) {
            pause();
        }
    }
    ASSERT_TRUE(pid > 0);
    waitpid_inject_eintr = 1;
    start = monotonic_ms();
    result = test_waitpid_deadline(pid, &status, 50u);
    elapsed = monotonic_ms() - start;
    calls = waitpid_inject_calls;
    fallback = test_waitpid_fallback_reap(pid);
    printf("INJECTION cleanup=%d result=%d status=%d calls=%u elapsed=%lld\n",
           fallback, (int)result, status, calls, elapsed);
    ASSERT_EQ(result, (pid_t)0);
    ASSERT_EQ(status, 0);
    ASSERT_TRUE(calls >= 2u);
    ASSERT_EQ(fallback, 0);
    ASSERT_TRUE(elapsed >= 50);
    ASSERT_TRUE(elapsed < 5000);
}

TEST(waitpid_deadline_sustained_eintr_does_not_extend_timeout)
{
    int status = -1;
    unsigned calls;
    int fallback;
    long long start;
    long long elapsed;
    pid_t result;
    pid_t pid;
    test_waitpid_reset_injection();
    pid = fork();
    if (pid == 0) {
        for (;;) {
            pause();
        }
    }
    ASSERT_TRUE(pid > 0);
    start = monotonic_ms();
    waitpid_inject_eintr_until_ms = start + 200;
    result = test_waitpid_deadline(pid, &status, 50u);
    elapsed = monotonic_ms() - start;
    calls = waitpid_inject_calls;
    fallback = test_waitpid_fallback_reap(pid);
    printf("INJECTION cleanup=%d result=%d status=%d calls=%u elapsed=%lld\n",
           fallback, (int)result, status, calls, elapsed);
    ASSERT_EQ(result, (pid_t)0);
    ASSERT_EQ(status, 0);
    ASSERT_TRUE(calls >= 2u);
    ASSERT_EQ(fallback, 0);
    ASSERT_TRUE(elapsed >= 50);
    ASSERT_TRUE(elapsed < 200);
}

TEST(waitpid_deadline_other_error_kills_and_reaps_child)
{
    int status = -1;
    unsigned calls;
    int fallback;
    pid_t result;
    pid_t pid;
    test_waitpid_reset_injection();
    pid = fork();
    if (pid == 0) {
        for (;;) {
            pause();
        }
    }
    ASSERT_TRUE(pid > 0);
    waitpid_inject_error = EIO;
    result = test_waitpid_deadline(pid, &status, 5000u);
    calls = waitpid_inject_calls;
    fallback = test_waitpid_fallback_reap(pid);
    printf("INJECTION cleanup=%d result=%d status=%d calls=%u\n",
           fallback, (int)result, status, calls);
    ASSERT_EQ(result, (pid_t)-1);
    ASSERT_EQ(status, 0);
    ASSERT_TRUE(calls >= 2u);
    ASSERT_EQ(fallback, 0);
}

TEST(waitpid_deadline_echild_clears_status_without_kill)
{
    int status = 0;
    unsigned kill_calls;
    pid_t result;
    pid_t reaped;
    pid_t pid;
    test_waitpid_reset_injection();
    pid = fork();
    if (pid == 0) {
        _exit(0);
    }
    ASSERT_TRUE(pid > 0);
    do {
        reaped = waitpid(pid, &status, 0);
    } while (reaped < 0 && errno == EINTR);
    if (reaped != pid) {
        (void)test_waitpid_fallback_reap(pid);
    }
    ASSERT_EQ(reaped, pid);
    test_waitpid_reset_injection();
    kill_inject_observe_only = 1;
    status = -1;
    result = test_waitpid_deadline(pid, &status, 0u);
    kill_calls = kill_inject_calls;
    test_waitpid_reset_injection();
    ASSERT_EQ(result, (pid_t)-1);
    ASSERT_EQ(status, 0);
    ASSERT_EQ(kill_calls, 0u);
}

TEST(waitpid_deadline_invalid_pid_clears_status_without_kill)
{
    int status = -1;
    unsigned kill_calls;
    pid_t result;
    test_waitpid_reset_injection();
    kill_inject_observe_only = 1;
    waitpid_inject_error = EIO;
    result = test_waitpid_deadline((pid_t)0, &status, 0u);
    kill_calls = kill_inject_calls;
    test_waitpid_reset_injection();
    ASSERT_EQ(result, (pid_t)-1);
    ASSERT_EQ(status, 0);
    ASSERT_EQ(kill_calls, 0u);
}

TEST(read_deadline_returns_byte_from_child)
{
    int fds[2];
    int status = 0;
    unsigned char byte = 0u;
    pid_t pid;
    ASSERT_EQ(pipe(fds), 0);
    pid = fork();
    if (pid == 0) {
        unsigned char out = (unsigned char)'R';
        close(fds[0]);
        if (write(fds[1], &out, 1u) != 1) {
            _exit(3);
        }
        _exit(0);
    }
    ASSERT_TRUE(pid > 0);
    close(fds[1]);
    ASSERT_EQ(test_read_deadline(fds[0], &byte, 1u, 5000u), (ssize_t)1);
    ASSERT_EQ(byte, (unsigned char)'R');
    close(fds[0]);
    ASSERT_EQ(test_waitpid_deadline(pid, &status, 5000u), pid);
}

TEST(read_deadline_times_out_when_writer_stalls)
{
    int fds[2];
    int status = 0;
    unsigned char byte = 0u;
    long long start;
    long long elapsed;
    pid_t pid;
    ASSERT_EQ(pipe(fds), 0);
    pid = fork();
    if (pid == 0) {
        close(fds[0]);
        for (;;) {
            pause();
        }
    }
    ASSERT_TRUE(pid > 0);
    close(fds[1]);
    start = monotonic_ms();
    ASSERT_EQ(test_read_deadline(fds[0], &byte, 1u, 200u), (ssize_t)-2);
    elapsed = monotonic_ms() - start;
    ASSERT_TRUE(elapsed >= 200);
    ASSERT_TRUE(elapsed < 5000);
    close(fds[0]);
    ASSERT_EQ(test_waitpid_deadline(pid, &status, 0u), (pid_t)0);
}

TEST(tmp_rejects_truncated_path) {
    int status = 0;
    pid_t pid = fork();
    if (pid == 0) {
        char path[31];
        (void)test_tmp(path, sizeof(path),
                       "same_prefix_with_a_very_long_suffix_a");
        _exit(0);
    }
    ASSERT_TRUE(pid > 0);
    ASSERT_EQ(test_waitpid_deadline(pid, &status, 5000u), pid);
    ASSERT_TRUE(WIFSIGNALED(status));
    ASSERT_EQ(WTERMSIG(status), SIGABRT);
}

TEST(tmp_truncation_uses_distinct_compact_fallbacks) {
    char first[32];
    char second[32];
    char expected[64];
    (void)test_tmp(first, sizeof(first),
                   "same_prefix_with_a_very_long_suffix_a");
    (void)test_tmp(second, sizeof(second),
                   "same_prefix_with_a_very_long_suffix_b");
    ASSERT_TRUE(strcmp(first, second) != 0);
    snprintf(expected, sizeof(expected), "/tmp/break_8073d8d7_%d",
             (int)TEST_GETPID());
    ASSERT_TRUE(strcmp(first, expected) == 0);
    snprintf(expected, sizeof(expected), "/tmp/break_8173da6a_%d",
             (int)TEST_GETPID());
    ASSERT_TRUE(strcmp(second, expected) == 0);
    snprintf(expected, sizeof(expected), "/tmp/break_x_%d",
             (int)TEST_GETPID());
    (void)test_tmp(first, sizeof(first), "x");
    ASSERT_TRUE(strcmp(first, expected) == 0);
}

TEST(tmp_rejects_truncated_parent_path) {
    int status = 0;
    pid_t pid = fork();
    if (pid == 0) {
        char path[32];
        (void)test_tmp(path, sizeof(path), "parent_with_a_long_suffix/file");
        _exit(0);
    }
    ASSERT_TRUE(pid > 0);
    ASSERT_EQ(test_waitpid_deadline(pid, &status, 5000u), pid);
    ASSERT_TRUE(WIFSIGNALED(status));
    ASSERT_EQ(WTERMSIG(status), SIGABRT);
}

TEST(tmp_rejects_truncated_backslash_parent_path) {
    int status = 0;
    pid_t pid = fork();
    if (pid == 0) {
        char path[32];
        (void)test_tmp(path, sizeof(path), "parent_with_a_long_suffix\\file");
        _exit(0);
    }
    ASSERT_TRUE(pid > 0);
    ASSERT_EQ(test_waitpid_deadline(pid, &status, 5000u), pid);
    ASSERT_TRUE(WIFSIGNALED(status));
    ASSERT_EQ(WTERMSIG(status), SIGABRT);
}
#endif

TEST_MAIN_BEGIN()
#if !defined(_WIN32)
    RUN_TEST(waitpid_deadline_reports_normal_exit);
    RUN_TEST(waitpid_deadline_reports_abort_signal);
    RUN_TEST(waitpid_deadline_kills_and_reaps_stuck_child);
    RUN_TEST(waitpid_deadline_retries_eintr_before_normal_exit);
    RUN_TEST(waitpid_deadline_retries_eintr_before_timeout_cleanup);
    RUN_TEST(waitpid_deadline_sustained_eintr_does_not_extend_timeout);
    RUN_TEST(waitpid_deadline_other_error_kills_and_reaps_child);
    RUN_TEST(waitpid_deadline_echild_clears_status_without_kill);
    RUN_TEST(waitpid_deadline_invalid_pid_clears_status_without_kill);
    RUN_TEST(read_deadline_returns_byte_from_child);
    RUN_TEST(read_deadline_times_out_when_writer_stalls);
    RUN_TEST(tmp_rejects_truncated_path);
    RUN_TEST(tmp_truncation_uses_distinct_compact_fallbacks);
    RUN_TEST(tmp_rejects_truncated_parent_path);
    RUN_TEST(tmp_rejects_truncated_backslash_parent_path);
#endif
TEST_MAIN_END()
