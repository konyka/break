# arm64 QEMU System, Shader I/O and Editor Misc Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add five existing pure-CPU test executables to the arm64 lane for an exact 205-test selection.

**Architecture:** Reuse the generated QEMU commands. Append five build targets and five flat exact-name alternatives; the full `-R` expression stays at 31 capture groups.

**Tech Stack:** C11, CMake/CTest, GitHub Actions YAML, Ubuntu 24.04 multiarch, QEMU user emulation, Python 3 + PyYAML contracts.

## Global Constraints

- Previous 200 + 5 = 205. Alternatives: `test_break_cvar$|test_break_xml$|test_editor_flow$|test_editor_image$|test_shader_io$`.
- Case counts: break_cvar 12, break_xml 13, editor_flow 3, editor_image 7, shader_io 59, total 94.
- Dependencies: break_cvar/xml link `break_system` (configured because the lane already builds `break_integrity`; cvar compiles `platform_fs.c` inline); editor_flow links `break_editor_test`; editor_image links `break_editor_test` and `stb_image_write`; shader_io compiles `shader_io.c` and `log.c`. None forks, starts threads, loads plugins or reads the environment.
- `test_shader_io` reads shader and engine sources through `../shaders`, `../src` and a `__FILE__`-relative fallback; most of its 59 cases are source-structure checks and its arm64 pass is not GPU or shader-compiler evidence.
- Exclude `test_break_plugin`, `test_break_plugin_unsupported`, `test_break_system_target_contract`, `test_editor_plugin_load`, `test_editor_input_script`, `test_editor_fonts`, `test_editor_settings` and prefix-derived names.
- Keep the expression at most 31 capture groups; no new group.
- No product/test-source edits, dependencies, skips, retries, masks or assertion relaxation. Append documentation; preserve history. Verified commits go directly to `master`.

---

### Task 1: Pin and implement the exact selection

**Files:**
- Create locally (ignored): `build-core-app-net/system_misc_selection_contract.py`
- Modify: `.github/workflows/ci.yml`, `docs/Build_Guide.md`

- [x] **Step 1:** Contract requires the build suffix `test_mycompose_async test_break_cvar test_break_xml test_editor_flow test_editor_image test_shader_io`, the five flat alternatives at the end, at most 31 groups, no `Too many parentheses`, exact native sets 200/205 with a five-element difference, guide/workflow byte equality and a 205 intro count. Negative probes include every excluded name above plus `test_shader_io_extra`.
- [x] **Step 2:** Run it on the current workflow; require RED at `missing system/misc build targets`.
- [x] **Step 3:** Append targets and alternatives in workflow and guide; update the 1.5 title, intro and current-count paragraph to 205, keeping 200 as history.
- [x] **Step 4:** Selection and lane-budget contracts GREEN, valid YAML, clean `git diff --check`.

### Task 2: Verify native and arm64 behavior

- [x] **Step 1:** Native focused 5/5 with 12/13/3/7/59.
- [x] **Step 2:** Clean Ubuntu 24.04 container: build and run the five arm64 targets under QEMU; require 5/5 with identical counts.
- [x] **Step 3:** Native full suite; require 456 tests, zero failures, four established platform skips.
- [x] **Step 4:** Clean non-root container running the exact workflow steps; require 205/205, all 25 per-test counts, all contracts/e2e, one ptrace setup skip, no root-permission skip.

### Task 3: Review, push and record evidence

- [x] **Step 1:** Read-only independent review; reproduce and fix every Critical/Important finding.
- [ ] **Step 2:** Commit `ci: run arm64 system and shader io tests`, push, monitor the full CI and Windows D3D12 workflows.
- [ ] **Step 3:** Download the raw arm64 log and assert 205 with all 25 per-test counts.
- [ ] **Step 4:** Append local/remote receipts and remaining gaps (plugin dynamic loading, editor fonts/settings/input script, GPU shader compilation) to `docs/Implementation_Status.md` and `docs/cross_engine/missing_capabilities.md`; check off completed steps.
