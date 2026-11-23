#ifndef TEST_FORK_H
#define TEST_FORK_H

#if !defined(_WIN32)
#include <errno.h>
#include <stdio.h>
#include <poll.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
static inline void test_waitpid_kill_and_reap(pid_t pid, int *status) {
    kill(pid, SIGKILL);
    while (waitpid(pid, status, 0) < 0 && errno == EINTR) {
    }
    if (status != NULL) {
        *status = 0;
    }
}

/* Bounded waits for fork-based tests. A child stuck under an emulator
 * would otherwise block the parent forever and the whole run would die on
 * an outer timeout without naming the case. On glibc under strict C11,
 * includers need _POSIX_C_SOURCE >= 199309L (clock_gettime, nanosleep, kill). Do not set
 * it on Darwin: there it lowers __DARWIN_C_LEVEL and hides snprintf, which
 * test_framework.h uses; the default Darwin level already declares all of
 * these.
 *
 * test_waitpid_deadline returns pid with *status set, 0 when the deadline
 * passed (the child is SIGKILLed and reaped, and *status is zeroed so an
 * "expect a signal" check cannot pass on the kill), or -1 on a waitpid
 * error. Errors clear *status; EINTR is retried without extending the
 * monotonic deadline, while other errors clean up a positive-PID child unless
 * the error is ECHILD. Always check the return value before *status. */
static inline pid_t test_waitpid_deadline(pid_t pid, int *status,
                                          unsigned timeout_ms) {
    const struct timespec step = {0, 10L * 1000L * 1000L};
    struct timespec deadline;
    clock_gettime(CLOCK_MONOTONIC, &deadline);
    deadline.tv_sec += (time_t)(timeout_ms / 1000u);
    deadline.tv_nsec += (long)(timeout_ms % 1000u) * 1000000L;
    if (deadline.tv_nsec >= 1000000000L) {
        deadline.tv_sec++;
        deadline.tv_nsec -= 1000000000L;
    }
    for (;;) {
        struct timespec now;
        pid_t r = waitpid(pid, status, WNOHANG);
        if (r < 0 && errno != EINTR) {
            if (pid > 0 && errno != ECHILD) {
                test_waitpid_kill_and_reap(pid, status);
            }
            if (status != NULL) {
                *status = 0;
            }
            return -1;
        }
        if (r > 0) {
            return r;
        }
        clock_gettime(CLOCK_MONOTONIC, &now);
        if (now.tv_sec > deadline.tv_sec ||
            (now.tv_sec == deadline.tv_sec && now.tv_nsec >= deadline.tv_nsec)) {
            break;
        }
        nanosleep(&step, NULL);
    }
    test_waitpid_kill_and_reap(pid, status);
    printf("CHILD TIMEOUT after %u ms (killed) ", timeout_ms);
    fflush(stdout);
    return 0;
}

/* Bounded read for a parent waiting on a pipe a forked child writes. A
 * blocking read() has the same failure mode as an unbounded waitpid() when
 * the child never reaches its write. Returns the read() result, or -2 when
 * the deadline passed with no data. */
static inline ssize_t test_read_deadline(int fd, void *buf, size_t len,
                                         unsigned timeout_ms) {
    const struct timespec step = {0, 10L * 1000L * 1000L};
    unsigned waited_ms = 0;
    for (;;) {
        struct pollfd pfd;
        int ready;
        pfd.fd = fd;
        pfd.events = POLLIN;
        pfd.revents = 0;
        ready = poll(&pfd, 1, 0);
        if (ready > 0) {
            ssize_t r;
            do {
                r = read(fd, buf, len);
            } while (r < 0 && errno == EINTR);
            return r;
        }
        if (ready < 0 && errno != EINTR) {
            return -1;
        }
        if (waited_ms >= timeout_ms) {
            printf("PIPE TIMEOUT after %u ms ", timeout_ms);
            fflush(stdout);
            return -2;
        }
        nanosleep(&step, NULL);
        waited_ms += 10u;
    }
}
#endif

#endif /* TEST_FORK_H */
