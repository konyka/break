# arm64 QEMU Compose/myui Integration, Render CPU and Input Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add seven existing pure-CPU test executables to the arm64 lane for an exact 212-test selection.

**Architecture:** Reuse the generated QEMU commands. Append seven build targets and seven flat exact-name alternatives; the full `-R` expression stays at 31 capture groups.

**Tech Stack:** C11, CMake/CTest, GitHub Actions YAML, Ubuntu 24.04 multiarch, QEMU user emulation, Python 3 + PyYAML contracts.

## Global Constraints

- Previous 205 + 7 = 212. Alternatives: `test_mycompose_myui$|test_mycompose_widget_primitives$|test_render_features$|test_rt_trace$|test_rhi_tlas_instance_encode$|test_rhi_metal_format_mapping$|test_input_extended$`.
- Case counts: mycompose_myui 18, mycompose_widget_primitives 7, render_features 4, rt_trace 2, rhi_tlas_instance_encode 2, rhi_metal_format_mapping 5, input_extended 21, total 59.
- Dependencies: the two Compose/myui tests link `mycompose_myui`/`myui_core`, the dummy PAL and threads (headless window objects only); render_features compiles `render_features.c`; rt_trace links `engine_rhi_headless` and the RHI core sources; tlas encode compiles `rhi_validation.c`; metal format mapping compiles `shader_io.c`/`log.c` and runs five platform-free cases (the MSL reflection case is compiled only on Apple Metal builds); input_extended compiles `input_extended.c` with threads.
- Exclude `test_input_extended_single_cpu` (sets CPU affinity, `RUN_SERIAL`), `test_rhi_device_type` (needs Vulkan headers), `test_rhi_native`, all `test_mycompose_cpp20*`, `test_mycompose_gpu_*`, `test_packer_roundtrip` (host tool driver) and prefix-derived names.
- Keep the expression at most 31 capture groups; no new group.
- No product/test-source edits, dependencies, skips, retries, masks or assertion relaxation. Append documentation; preserve history. Verified commits go directly to `master`.

---

### Task 1: Pin and implement the exact selection

**Files:**
- Create locally (ignored): `build-core-app-net/ui_render_cpu_selection_contract.py`
- Modify: `.github/workflows/ci.yml`, `docs/Build_Guide.md`

- [x] **Step 1:** Contract requires the build suffix `test_shader_io` + seven targets, the seven flat alternatives at the end, at most 31 groups, no `Too many parentheses`, exact native sets 205/212 with a seven-element difference, guide/workflow byte equality and a 212 intro count. Negative probes include every excluded name above.
- [x] **Step 2:** Run it on the current workflow; require RED at `missing ui/render cpu build targets`.
- [x] **Step 3:** Append targets and alternatives in workflow and guide; update the 1.5 title, intro and current-count paragraph to 212, keeping 205 as history.
- [x] **Step 4:** Selection and lane-budget contracts GREEN, valid YAML, clean `git diff --check`.

### Task 2: Verify native and arm64 behavior

- [x] **Step 1:** Native focused 7/7 with 18/7/4/2/2/5/21.
- [x] **Step 2:** Clean Ubuntu 24.04 container: build and run the seven arm64 targets under QEMU; require 7/7 with identical counts.
- [x] **Step 3:** Native full suite; require 456 tests, zero failures, four established platform skips.
- [x] **Step 4:** Clean non-root container running the exact workflow steps; require 212/212, all 32 per-test counts, all contracts/e2e, one ptrace setup skip, no root-permission skip.

### Task 3: Review, push and record evidence

- [x] **Step 1:** Read-only independent review; reproduce and fix every Critical/Important finding.
- [ ] **Step 2:** Commit `ci: run arm64 ui and render cpu tests`, push, monitor the full CI and Windows D3D12 workflows.
- [ ] **Step 3:** Download the raw arm64 log and assert 212 with all 32 per-test counts.
- [ ] **Step 4:** Append local/remote receipts and remaining gaps (single-CPU input variant, Vulkan device-type probe, GPU rendering, real input devices) to `docs/Implementation_Status.md` and `docs/cross_engine/missing_capabilities.md`; check off completed steps.
