# Fork-Child Deadline for Abort Tests Design

## Context

Two tests in the arm64 lane fork a child, start runtime worker threads in it,
and expect the child to abort on a contract violation:
`test_runtime_io` case 15 (`io_request_double_release_aborts`) and
`test_runtime_reload` case 23 (`reload_destroy_requires_shutdown_aborts`).
Under qemu-user 8.2.2 on a loaded host, the child occasionally never finishes:
both of its threads sit in futex waits and the parent blocks forever in
`waitpid(pid, &status, 0)`. The lane then fails only when the outer
`timeout 600` kills the whole CTest run, with no message naming the case. The
root cause is not yet isolated; minimal fork/thread/abort reproductions and the
upstream QEMU issue 358 program do not hang.

The parent's unbounded wait is a defect in the tests regardless of the cause:
a stuck child must fail its own case quickly and name what happened.

## Approaches

1. Add a bounded wait helper in a new `engine/tests/test_fork.h` that polls
   `waitpid(WNOHANG)` until a deadline, then sends `SIGKILL`, reaps the child,
   and reports a timeout. Recommended: no new dependency, works on every POSIX
   target that already runs these tests, and other fork tests can reuse it.
2. Use `alarm()` in the parent. Rejected: process-wide signal state and a
   handler that must longjmp out of `waitpid`.
3. Retry the case. Rejected: it hides the hang.

## Design

`engine/tests/test_fork.h` (POSIX only; kept out of `test_framework.h` so the
318 files that include it see no new headers or feature-macro requirements)
provides:

```c
/* Returns pid on success with *status filled, 0 on deadline (child killed
 * and reaped), -1 on waitpid error. */
static inline pid_t test_waitpid_deadline(pid_t pid, int *status,
                                          unsigned timeout_ms);
```

It polls every 10 ms with `nanosleep`. On deadline it calls `kill(pid,
SIGKILL)`, then a blocking `waitpid` to reap, prints
`CHILD TIMEOUT after <ms> ms (killed)`, and returns 0. Both cases use it with a
30-second deadline, far above their native (<1 s) and QEMU (~1 s) durations,
and assert the return equals `pid`, so a hang becomes a named case failure.

## TDD

A new `test_fork_deadline` executable checks the helper:
1. A child that exits 7 returns `pid` with `WEXITSTATUS == 7`.
2. A child that aborts returns `pid` with `WTERMSIG == SIGABRT`.
3. A child that sleeps forever returns 0 within the deadline plus slack, and the
   child is reaped (a second `waitpid` fails with `ECHILD`).
It fails to compile before the helper exists (RED), then passes (GREEN). The
two abort cases switch to the helper; their existing assertions are unchanged.

## Verification and Boundaries

Native full regression (455 + 1 = 456 tests), focused native and cross runs of
the three executables, and the clean-container workflow. The new test is not
added to the arm64 selection in this slice. This bounds the hang; it does not
fix the qemu-user root cause, which stays recorded as open.
