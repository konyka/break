# arm64 QEMU C++20 Parity and Misc Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add the C++20 Compose parity family, the public-API C++20 gate, the Cry-style prototype and the fork-deadline helper test to the arm64 lane for an exact 219-test selection.

**Architecture:** Reuse the generated QEMU commands and the toolchain's existing `aarch64-linux-gnu-g++` (GCC 13.3, already identified at configure time). Append seven build targets and seven flat exact-name alternatives; the full `-R` expression stays at 31 capture groups.

**Tech Stack:** C11/C++20, CMake/CTest, GitHub Actions YAML, Ubuntu 24.04 multiarch, QEMU user emulation, Python 3 + PyYAML contracts.

## Global Constraints

- Previous 212 + 7 = 219. Alternatives: `test_mycompose_cpp20_c_fixture$|test_mycompose_cpp20$|test_mycompose_cpp20_header$|test_mycompose_cpp20_noexcept$|test_public_api_cpp20$|test_core_style_prototype$|test_fork_deadline$`.
- Result shapes: cpp20_c_fixture 1 case, cpp20 14 cases, core_style_prototype 3 cases, fork_deadline 5 cases (23 counted cases). cpp20_header, cpp20_noexcept and public_api_cpp20 print no `=== Results` line; they pass by exit code 0 (compile-time `static_assert`/concept checks plus one live call each), so the log assertion only verifies they appear in the passed list.
- `test_mycompose_cpp20` links the C11 fixture object, so it checks the real C/C++ ABI on arm64; `test_mycompose_cpp20_noexcept` builds with `-fno-exceptions`.
- `test_fork_deadline` forks children and kills a stuck child after 200 ms. This is the deadline helper that guards `test_runtime_io`/`test_runtime_reload`; running it under qemu-user checks the helper itself, with the known qemu-user fork-then-thread hang root cause still open.
- Exclude `test_input_extended_single_cpu`, `test_rhi_device_type`, `test_rhi_native`, `test_mycompose_gpu_*`, `test_packer_roundtrip`, editor shell/Lua/fonts/settings, plugin loading and prefix-derived names.
- No product/test-source edits, dependencies, skips, retries, masks or assertion relaxation. Append documentation; preserve history. Verified commits go directly to `master`.

---

### Task 1: Pin and implement the exact selection

**Files:**
- Create locally (ignored): `build-core-app-net/cpp20_selection_contract.py`
- Modify: `.github/workflows/ci.yml`, `docs/Build_Guide.md`

- [x] **Step 1:** Contract requires the build suffix `test_input_extended` + seven targets, the seven flat alternatives at the end, at most 31 groups, no `Too many parentheses`, exact native sets 212/219 with a seven-element difference, guide/workflow byte equality and a 219 intro count. Negative probes include every excluded name above.
- [x] **Step 2:** Run it on the current workflow; require RED at `missing cpp20 build targets`.
- [x] **Step 3:** Append targets and alternatives in workflow and guide; update the 1.5 title, intro and current-count paragraph to 219, keeping 212 as history.
- [x] **Step 4:** Selection and lane-budget contracts GREEN, valid YAML, clean `git diff --check`.

### Task 2: Verify native and arm64 behavior

- [x] **Step 1:** Native focused 7/7 with 1/14/3/5 counted cases and exit 0 for the three uncounted tests.
- [x] **Step 2:** Clean Ubuntu 24.04 container: build and run the seven arm64 targets under QEMU; require 7/7 with identical counts; confirm `test_fork_deadline` finishes without `CHILD TIMEOUT`/`PIPE TIMEOUT` beyond its own intended 200 ms cases.
- [x] **Step 3:** Native full suite; require 456 tests, zero failures, four established platform skips.
- [x] **Step 4:** Clean non-root container running the exact workflow steps; require 219/219, all counted per-test numbers, all contracts/e2e, one ptrace setup skip, no root-permission skip. Because `test_fork_deadline` deliberately prints `CHILD TIMEOUT after 200 ms`, `PIPE TIMEOUT after 200 ms` and `CHILD TIMEOUT after 0 ms`, run `build-core-app-net/assert_timeout_markers.py` on the log: it requires those three markers exactly, all from `test_fork_deadline`, so any other timeout marker still fails the evidence check.

### Task 3: Review, push and record evidence

- [x] **Step 1:** Read-only independent review; reproduce and fix every Critical/Important finding.
- [x] **Step 2:** Commit `ci: run arm64 cpp20 parity tests`, push, monitor the full CI and Windows D3D12 workflows.
- [ ] **Step 3:** Download the raw arm64 log and assert 219 with all counted per-test numbers.
- [ ] **Step 4:** Append local/remote receipts and remaining gaps to `docs/Implementation_Status.md` and `docs/cross_engine/missing_capabilities.md`; check off completed steps.
