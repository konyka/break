# Test Fork EINTR Cleanup Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Make `test_waitpid_deadline` retry EINTR and clean up children after other wait errors without changing its public signature or timeout semantics.

**Architecture:** Keep the implementation POSIX-only in `engine/tests/test_fork.h`. Inject wait errors and observe kill only in `test_fork_deadline.c`; share kill/reap logic between timeout and error exits. A real-wait fallback prevents RED from leaking children without hiding missing cleanup.

**Tech Stack:** C11, POSIX `fork/waitpid/kill/nanosleep`, CMake/CTest.

## Global Constraints

- Engine and test code remain C11 with repository/Google naming. No compatibility-engine prefixes, retired domain vocabulary, or role labels.
- No production behavior changes, new dependencies, signal-timing sleeps, or test hooks in product sources.
- `test_waitpid_deadline(pid, status, timeout_ms)` keeps its signature and return meanings: `pid`, 0 on timeout, -1 on other wait errors.
- Never signal an invalid PID or an ECHILD result. Always clear `status` on timeout and error exits.
- Every new behavior gets a real RED before its minimal implementation. Test failures must not leak children or rely on fallback cleanup for success.
- Default Vulkan remains primary; OpenGL remains fallback/image comparison. Linux uses native Wayland only.
- Append existing documentation. Review all Critical/Important findings and re-review fixes. Push `master` directly, no PR.

---

### Task 1: Deterministic wait-error injection and cleanup

**Files:**
- Modify: `engine/tests/test_fork_deadline.c`
- Modify: `engine/tests/test_fork.h`

**Interfaces:**
- Consumes: existing `test_waitpid_deadline(pid_t pid, int *status, unsigned timeout_ms)`.
- Produces: unchanged public signature and return contract; no additional public APIs.

- [ ] **Step 1: Configure the isolated build and add five failing tests**

From the worktree root, configure if `build-test-fork` does not already exist:

```bash
cmake -S engine -B build-test-fork -G Ninja \
  -DENGINE_RHI_BACKEND=vulkan -DMYUI_PAL=dummy -DENGINE_BUILD_TESTS=ON
cmake --build build-test-fork --target test_fork_deadline --parallel 3
./build-test-fork/test_fork_deadline
```

The existing baseline is 5/5. Remove the existing direct `#include "test_fork.h"` near the top of `test_fork_deadline.c`; its first and only inclusion must occur inside the macro region below, not earlier under an include guard. In the existing `#if !defined(_WIN32)` region, place system declarations before macros:

```c
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

static pid_t test_waitpid_inject(pid_t pid, int *status, int options);
static int test_kill_inject(pid_t pid, int signal_number);
#define waitpid test_waitpid_inject
#define kill test_kill_inject
#include "test_fork.h"
#undef waitpid
#undef kill
```

After `#undef`, define the wrappers so their normal paths call real `waitpid` and `kill`. Keep all state translation-unit static:

```c
static unsigned waitpid_inject_calls;
static int waitpid_inject_eintr;
static int waitpid_inject_error;
static unsigned kill_inject_calls;
static int kill_inject_observe_only;

static void test_waitpid_reset_injection(void) {
    waitpid_inject_calls = 0u;
    waitpid_inject_eintr = 0;
    waitpid_inject_error = 0;
    kill_inject_calls = 0u;
    kill_inject_observe_only = 0;
}
```

The wait wrapper increments the count, returns `-1` with the requested errno once, and otherwise calls real `waitpid`. The kill wrapper increments `kill_inject_calls`; when `kill_inject_observe_only != 0`, it returns 0 without forwarding any signal, otherwise it calls real `kill`. Both ECHILD and invalid-PID cases must enable observe-only mode, so a defective helper cannot signal a process group or a reused PID. Only a known live child owned by the test may use real-kill mode.

Add `static int test_waitpid_fallback_reap(pid_t pid)` with a local status variable. It loops on real `waitpid(pid, &local, WNOHANG)`:

- `pid` returned: return 1, meaning fallback performed the reap.
- 0 returned: call real `kill(pid, SIGKILL)`, then retry real blocking `waitpid` only for EINTR and return 1 when reaped.
- EINTR: retry the WNOHANG call.
- ECHILD: return 0, meaning no fallback cleanup was needed.
- Any other error: return -1.

The fallback never kills on `pid`, ECHILD, or an error. It runs before assertions but after result/status/call-count/time capture, and cannot alter the captured status.

Add and register these cases:

1. `waitpid_deadline_retries_eintr_before_normal_exit`: child `_exit(0)`, one injected EINTR. Capture result/status/calls/fallback. Require result `pid`, `WIFEXITED`, exit code 0, at least two wait calls, and fallback result 0.
2. `waitpid_deadline_retries_eintr_before_timeout_cleanup`: child pauses forever, one injected EINTR and a 50 ms deadline. Capture monotonic start, helper result/status/calls, elapsed before fallback, then fallback. Require result 0, `status == 0`, at least two wait calls, fallback result 0, and `elapsed >= 50` with a generous upper bound to avoid a hang. The lower bound must not include fallback time; fallback result 0 proves the helper itself completed the timeout reap.
3. `waitpid_deadline_other_error_kills_and_reaps_child`: child pauses forever, one injected EIO. Capture result/status/calls before fallback. Require result -1, `status == 0`, at least two wait calls, and fallback result 0, proving helper already reaped the child rather than fallback hiding the defect.
4. `waitpid_deadline_echild_clears_status_without_kill`: create and reap a child with real wait, reset injection/status/counters, set `kill_inject_observe_only = 1`, then call the helper on that reaped PID. Require result -1, `status == 0`, and `kill_inject_calls == 0`. The spy must not forward a signal to a potentially reused PID.
5. `waitpid_deadline_invalid_pid_clears_status_without_kill`: PID 0 with one injected EIO and `kill_inject_observe_only = 1`. Require result -1, `status == 0`, and `kill_inject_calls == 0`. Do not fork in this case and do not let a real group signal occur.

- [ ] **Step 2: Verify RED**

Run:

```bash
cmake --build build-test-fork --target test_fork_deadline --parallel 3
./build-test-fork/test_fork_deadline
```

Expected: compilation succeeds. Cases 1–3 fail for their named ownership/timeout/cleanup reasons; cases 4–5 fail because old code leaves `status == -1`, while their no-kill guards also hold. Existing five cases remain green. Fallback output or explicit fallback results must show all injected children were reaped on RED.

- [ ] **Step 3: Implement shared cleanup and EINTR retry**

Add a private static-inline `test_waitpid_kill_and_reap` in `test_fork.h` that sends SIGKILL, retries blocking `waitpid` only for EINTR, and clears `status`. Use it for the existing timeout branch. In the polling loop:

```c
if (r < 0 && errno == EINTR) {
    continue;
}
if (r < 0) {
    if (pid > 0 && errno != ECHILD) {
        test_waitpid_kill_and_reap(pid, status);
    }
    if (status != NULL) {
        *status = 0;
    }
    return -1;
}
return r;
```

Update the public function comment to state that other errors clear status and only valid, non-ECHILD children receive cleanup. Do not alter the 10 ms polling interval, timeout accounting, diagnostic text, or read-deadline helper.

- [ ] **Step 4: Verify GREEN and existing consumers**

Run:

```bash
cmake --build build-test-fork --parallel 3 --target \
  test_fork_deadline test_runtime_io test_runtime_reload test_core_app_diagnostics
./build-test-fork/test_fork_deadline
ctest --test-dir build-test-fork --output-on-failure \
  -R '^(test_fork_deadline|test_runtime_io|test_runtime_reload|test_core_app_diagnostics)$'
```

Expected: `test_fork_deadline` 10/10 and all four CTest entries pass with no children left behind.

- [ ] **Step 5: Commit after task review**

```bash
git add engine/tests/test_fork_deadline.c engine/tests/test_fork.h
git commit -m "test(fork): clean up interrupted waitpid polling"
```

### Task 2: Documentation, independent review, validation, and delivery

**Files:**
- Modify: `docs/Build_Guide.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/cross_engine/missing_capabilities.md`

- [ ] **Step 1: Append the contract and actual evidence**

Document the unchanged signature, EINTR retry, ECHILD/invalid-PID signal guard, shared kill/reap, zeroed error status, five deterministic injections, and actual RED/GREEN counts. Do not imply that qemu-user fork-then-thread hangs or the unrelated Windows scene failure is fixed.

- [ ] **Step 2: Run native and sanitizer validation**

Run the full Vulkan and OpenGL suites, and the four focused tests in ASan+UBSan and TSan trees. Require zero failures. Keep platform-specific skips visible and never convert them into executed passes. Do not claim sanitizer coverage that was not actually run; macOS leak detection is unsupported.

- [ ] **Step 3: Independent review and fixes**

Review retry/error ownership, invalid PID safety, status clearing, timeout preservation, test-only macro scope, fallback PID-reuse safety, and whether fallback can create false GREEN. Fix every Critical/Important through a new RED/GREEN cycle and scoped re-review.

- [ ] **Step 4: Synchronize, push, and verify remote**

```bash
git diff --check
git fetch origin
git rebase origin/master
git push origin HEAD:master
```

Re-run affected tests after any rebase. Verify final CI, windows-d3d12, arm64 selection and Proton ancestry. Record actual run IDs/outcomes without claiming QUIC execution when its credentials are unavailable. Leave `HEAD == origin/master`, a clean main checkout, and no temporary worktree.

## Follow-up review: sustained EINTR deadline

The original Task 3 unconditional `continue` and its instruction not to alter timeout accounting are superseded by this follow-up. They allowed sustained EINTR to bypass the deadline and busy-poll. The current implementation computes a `CLOCK_MONOTONIC` absolute deadline once, sends both EINTR and still-running results through the same deadline check, and retains the 10 ms sleep only as the polling interval. Normal exits and all error-cleanup ownership rules remain unchanged.

Add `waitpid_deadline_sustained_eintr_does_not_extend_timeout`: inject EINTR only into WNOHANG polling for 200 ms while using a 50 ms helper deadline. Keep cleanup waits real, capture result/status/call count/elapsed before the real-wait fallback, require fallback `cleanup=0`, and require elapsed to be at least 50 ms but below the injection window. The old implementation produced 10 passes and one failure out of 11; the fixed test suite is 11/11. Update the earlier five-test/10-test references as historical initial-scope evidence, not the current total.
