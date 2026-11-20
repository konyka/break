# arm64 QEMU Headless World Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add the fifteen `headless;world` tests to the arm64 lane for an exact 179-test selection.

**Architecture:** Reuse fifteen generated QEMU commands. Append fifteen build targets after `test_break_flow_runtime` and add one new locally anchored alternative.

## Global Constraints

- Previous 164 + 15 = 179. Do not select `test_mesh_gpu_gl` or `test_world_presentation_gl`.
- Alternative: `test_(vegetation|time_of_day|visarea|decal|voxel|road)$|test_world_(stream(_job|_world)?|mesh_fake|presentation|presenter_fake)$|test_mesh_(stage|buffer|gpu)$`.
- No product/test-source edits, dependency, skip, retry, mask, or assertion relaxation.

---

- [x] **Step 1:** `build-core-app-net/world_selection_contract.py` on the old workflow; expected FAIL at `missing world build targets`.
- [x] **Step 2:** Append the fifteen targets and the alternative in `.github/workflows/ci.yml` and `docs/Build_Guide.md`.
- [x] **Step 3:** Re-run the contract; expected `exact 179-test headless world selection and anchor contract passed`.
- [x] **Step 4:** Focused native with the new `-R` (15/15) and unmodified cross baseline (15/15, 29 cases).
- [x] **Step 5:** Native full regression; require 456, zero failures, four established skips.
- [x] **Step 6:** Clean-container workflow; require 179/179 and exactly one ptrace setup skip.
- [ ] **Step 7:** Read-only review; push; `assert_arm64_log.py <log> 179` with all fifteen per-test counts; record.
