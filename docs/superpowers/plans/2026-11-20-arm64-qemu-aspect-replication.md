# arm64 QEMU Aspect Replication Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add aspect, aspect replication, and fragment replication tests to the arm64 lane for an exact 31-test selection.

**Architecture:** Reuse executable-target emulation; no product/test changes or new dependencies are needed. Extend only build/regex configuration and evidence docs.

**Tech Stack:** CMake/CTest, QEMU user emulation, GitHub Actions YAML, Python 3 + PyYAML, Podman Ubuntu 24.04.

## Global Constraints

- Add three tests with totals 12/9/12; preserve previous 28 and exactly one existing integrity setup skip.
- No Snowflake/QUIC claims, new skips, retries, filtering, status masking, or full-suite/device claims.

---

### Task 1: CI and evidence

**Files:** `.github/workflows/ci.yml`, `docs/Build_Guide.md`, `docs/Implementation_Status.md`, `docs/design/runtime_network.md`, `docs/cross_engine/missing_capabilities.md`.

- [ ] **Step 1: Preserve cross proof and run RED contract**

Retain unmodified cross 3/3 with 12/9/12 in 0.26 seconds. Require via PyYAML a build command ending in `test_break_online_aspect test_break_online_aspect_replication test_break_replication_fragment`, a regex adding `test_break_online_aspect|test_break_replication_fragment`, and an actual native selection equal to previous 28 plus the three new names, size 31. Expected RED on old build command.

- [ ] **Step 2: Apply minimal CI edit**

Append the three targets in that order. Add `test_break_online_aspect` and `test_break_replication_fragment` alternatives to the existing regex; aspect prefix selects both aspect tests. Keep every other workflow input unchanged.

- [ ] **Step 3: Verify GREEN and native full suite**

Rerun contract for exact 31/PASS. Run `cmake . && make -j6 && ctest -j4 --timeout 240 --output-on-failure` in `build-core-app-net`; expected 455 tests, zero failures, four established skips. Run `git diff --check`.

- [ ] **Step 4: Update docs and commit**

Record unified 31 coverage and 12/9/12 totals, direct target-only QEMU execution, no new skip, and unchanged Snowflake/QUIC/core_app limits. Commit as `ci: run arm64 aspect replication tests` including this plan.

### Task 2: Final verification and remote proof

- [ ] **Step 1: Clean container**

Fetch/rebase if needed without discarding independent work. Run final workflow scripts in a fresh Ubuntu container; require 31 targets, object checks, 31/31, every old/new summary, and exactly one existing integrity skip.

- [ ] **Step 2: Review and push**

Request read-only review of exact selection, dependency gates, failure propagation, and docs; fix adopted findings test-first. Push normally and wait for exact HEAD's arm64 job.

- [ ] **Step 3: Assert and record remote evidence**

Require `0 tests failed out of 31`, all old summaries, new 12/9/12, all tools/contracts/e2e, and exactly one existing integrity skip. Add run/job URLs and commit to implementation status, commit as `docs: record arm64 aspect CI results`, and push. Finish clean with `HEAD == origin/master`; keep broader goal open.
