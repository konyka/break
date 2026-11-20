# arm64 QEMU Lane Time Budget Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Raise the arm64 lane's outer CTest guard from 300 to 600 seconds without changing the selection or the job cap.

**Architecture:** One-token edit in the workflow run block and the mirrored guide command.

## Global Constraints

- Selection stays at 152; per-test `TIMEOUT` properties and `timeout-minutes: 25` unchanged.
- No `-j`, retry, skip, or mask.

---

- [x] **Step 1:** `build-core-app-net/lane_budget_contract.py` on the old workflow; expected FAIL at `old 300 s guard still present`.
- [x] **Step 2:** Replace `timeout 300 ctest` with `timeout 600 ctest` in `.github/workflows/ci.yml` and `docs/Build_Guide.md`.
- [x] **Step 3:** Re-run the contract; expected `lane budget contract passed: 600 s guard, 25 min cap, 152 tests`.
- [ ] **Step 4:** Clean-container workflow run on an idle host: 152/152, one ptrace setup skip.
- [ ] **Step 5:** Push; confirm the exact-HEAD remote job succeeds with `assert_arm64_log.py <log> 152`; record the URL.
