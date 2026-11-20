# arm64 QEMU Kernel and Flow Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add the twelve kernel/flow tests to the arm64 lane for an exact 164-test selection.

**Architecture:** Reuse eleven generated QEMU commands and one host contract. Append eleven build targets after `test_rule_engine_backward_bindings` and add one new locally anchored alternative.

## Global Constraints

- Previous 152 + 12 = 164; `test_break_kernel_lua` stays selected.
- Alternative: `test_break_kernel_(actor|items|weapons|actions|move|level|area|flow|target_contract)$|test_break_flow_(graph|serial|runtime)$`.
- No product/test-source edits, dependency, skip, retry, mask, or assertion relaxation.

---

- [x] **Step 1:** `build-core-app-net/kernel_flow_selection_contract.py` on the old workflow; expected FAIL at `missing kernel/flow build targets`.
- [x] **Step 2:** Append the eleven targets and the alternative in `.github/workflows/ci.yml` and `docs/Build_Guide.md`.
- [x] **Step 3:** Re-run the contract; expected `exact 164-test kernel/flow selection and anchor contract passed`. Relax the lane-budget contract's fixed 152 to "at least 152".
- [x] **Step 4:** Focused native with the new `-R` (12/12) and unmodified cross baseline (12/12, 62 cases).
- [x] **Step 5:** Native full regression; require 456, zero failures, four established skips.
- [x] **Step 6:** Clean-container workflow; require 164/164 and exactly one ptrace setup skip.
- [x] **Step 7:** Read-only review; push; `assert_arm64_log.py <log> 164` with all eleven per-test counts; record.
