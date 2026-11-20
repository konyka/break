# macOS Cocoa Lane Parallelism Cap Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Stop the unbounded `make -j` in `lane-native-surface-cocoa` from exhausting the macOS runner's process limit.

---

- [x] **Step 1:** `build-core-app-net/cocoa_parallel_contract.py` on the old workflow; expected FAIL at the bare `--parallel` in the `dxx_break` build.
- [x] **Step 2:** Replace both bare `--parallel` flags in that lane with `--parallel "$(sysctl -n hw.ncpu)"`.
- [x] **Step 3:** Re-run the contract; expected `cocoa parallel contract passed: 2 build steps capped at hw.ncpu`.
- [ ] **Step 4:** Push; confirm `macOS Cocoa + MoltenVK (Clang)` succeeds on the exact HEAD and that its log shows a numeric `-j`; record the URL.
