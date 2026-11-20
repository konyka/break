#ifndef TEST_FORK_H
#define TEST_FORK_H

#if !defined(_WIN32)
#include <errno.h>
#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
/* Bounded waitpid for fork-based tests. A child stuck under an emulator
 * would otherwise block the parent forever and the whole run would die on
 * an outer timeout without naming the case. Returns pid with *status set,
 * 0 when the deadline passed (the child is SIGKILLed and reaped), or -1 on
 * a waitpid error. */
static inline pid_t test_waitpid_deadline(pid_t pid, int *status,
                                          unsigned timeout_ms) {
    const struct timespec step = {0, 10L * 1000L * 1000L};
    unsigned waited_ms = 0;
    for (;;) {
        pid_t r = waitpid(pid, status, WNOHANG);
        if (r != 0) {
            return r;
        }
        if (waited_ms >= timeout_ms) {
            break;
        }
        nanosleep(&step, NULL);
        waited_ms += 10u;
    }
    kill(pid, SIGKILL);
    while (waitpid(pid, status, 0) < 0 && errno == EINTR) {
    }
    printf("CHILD TIMEOUT after %u ms (killed) ", timeout_ms);
    fflush(stdout);
    return 0;
}
#endif

#endif /* TEST_FORK_H */
