# Bounded Stop Review Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Prevent step-mode stop from destroying a Snowflake reactor while a step is executing, and make bounded-stop evidence and documentation precise.

**Architecture:** The adapter lifecycle mutex protects admission and publication of `step_active`; the step call releases it before invoking Snowflake and broadcasts completion afterward. Stop waits on the lifecycle condition only until its monotonic-style deadline, returning false with ownership retained on timeout. A test-only delay hook makes the concurrent contract deterministic without changing Snowflake or Session production logic.

**Tech Stack:** C11, pthreads/Windows condition variables, Snowflake C adapter, existing focused CTest binaries, ASan and TSan.

## Global Constraints

- Do not modify Snowflake sources.
- Do not modify Session production logic.
- Do not call Snowflake step while holding the lifecycle mutex.
- On bounded timeout, retain `STOPPING` and live reactor ownership for a later stop.
- Do not use `time(NULL)` or wall-clock elapsed values for timeout assertions.

---

### Task 1: Add step-driver lifecycle coordination

**Files:**
- Modify: `engine/src/network/break_net_adapter.h`
- Modify: `engine/src/network/break_net_adapter.c`

- [x] Add the test-only step-delay declaration and adapter fields for active-step state and one-shot delay.
- [x] Make `break_net_reactor_step` atomically claim the existing driver guard, publish `step_active` under `lifecycle_mutex`, snapshot `snow_thread`, unlock before delay/Snowflake, and clear/broadcast completion afterward.
- [x] Add a condition-based bounded wait that stop uses when `step_active` is true; preserve reactor ownership if the deadline expires.

### Task 2: Add deterministic concurrent regression coverage

**Files:**
- Modify: `engine/tests/test_break_net_adapter.c`

- [x] Add a pthread step driver helper and monotonic `clock_gettime(CLOCK_MONOTONIC)` measurement.
- [x] Add `break_net_adapter_step_stop_timeout_waits_for_active_step`: delay the next step, run it concurrently, assert short stop returns false quickly and preserves pending ownership, join the step, then complete stop.
- [x] Remove `time(NULL)`/wall-clock elapsed assertions from bounded-stop coverage and register the new test.

### Task 3: Update protocol and verification records

**Files:**
- Modify: `docs/design/session_protocol.md`
- Modify: `docs/superpowers/sdd/2026-10-19-snowflake-c11-adapter/task-outbound-report.md`

- [x] Document bounded deadline and retained-resource semantics for both thread and step modes, including the no-lock-around-Snowflake rule.
- [x] Update adapter verification counts to 29/29 for normal, ASan, and TSan, and state Session focused lanes pass without claiming production Session changes.

### Task 4: Verify all requested lanes

- [x] Build/run normal adapter focused test (29/29).
- [x] Build/run ASan adapter focused test (29/29).
- [x] Build/run TSan adapter focused test (29/29).
- [x] Build/run normal, ASan, and TSan Session focused tests (20/20 each).
- [x] Run `git diff --check` and confirm no Snowflake/Session production files changed.
