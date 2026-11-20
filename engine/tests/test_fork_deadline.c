#include "test_framework.h"
#include "test_fork.h"

#if !defined(_WIN32)
#include <errno.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

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
    ASSERT_EQ(test_waitpid_deadline(pid, &status, 200u), (pid_t)0);
    elapsed = monotonic_ms() - start;
    ASSERT_TRUE(elapsed >= 200);
    ASSERT_TRUE(elapsed < 5000);
    errno = 0;
    ASSERT_EQ(waitpid(pid, &status, WNOHANG), (pid_t)-1);
    ASSERT_EQ(errno, ECHILD);
}
#endif

TEST_MAIN_BEGIN()
#if !defined(_WIN32)
    RUN_TEST(waitpid_deadline_reports_normal_exit);
    RUN_TEST(waitpid_deadline_reports_abort_signal);
    RUN_TEST(waitpid_deadline_kills_and_reaps_stuck_child);
#endif
TEST_MAIN_END()
