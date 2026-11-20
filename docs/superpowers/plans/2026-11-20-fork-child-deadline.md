# Fork-Child Deadline Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Turn an unbounded parent `waitpid` in two fork-then-abort tests into a bounded wait that fails the case by name.

**Architecture:** New POSIX-only header `engine/tests/test_fork.h` with `test_waitpid_deadline`; a new `test_fork_deadline` executable tests it; two existing cases switch to it.

---

- [x] **Step 1:** Write `engine/tests/test_fork_deadline.c` (normal exit, SIGABRT, stuck child killed and reaped) and register it; build fails on the missing function (RED).
- [x] **Step 2:** Implement `test_waitpid_deadline` in `engine/tests/test_fork.h` (10 ms `WNOHANG` poll, `SIGKILL` + reap with `EINTR` retry, diagnostic line, return 0).
- [x] **Step 3:** `test_fork_deadline` 3/3 (GREEN).
- [x] **Step 4:** Switch `test_runtime_io` case 15 and `test_runtime_reload` case 23 to a 30-second deadline; both suites pass natively.
- [x] **Step 4b (review fix):** Add `test_read_deadline` (RED: two new `test_fork_deadline` cases fail to compile), bound the io case's stage-pipe read, zero `*status` on timeout; `test_fork_deadline` 5/5.
- [x] **Step 5:** Native full regression: 456 tests, zero failures, four established skips.
- [x] **Step 6:** Cross focused run of the three executables in a clean container.
- [ ] **Step 7:** Read-only review, push, confirm the exact-HEAD arm64 job (152) and record.
