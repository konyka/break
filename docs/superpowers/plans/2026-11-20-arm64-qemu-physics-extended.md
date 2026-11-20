# arm64 QEMU Extended Physics Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add the five remaining physics tests to the arm64 lane for an exact 85-test selection.

**Architecture:** Reuse five generated executable-target QEMU commands. Append five build targets and add one new locally anchored CTest alternative; leave the verified rigid-body alternative untouched.

**Tech Stack:** CMake/CTest, GitHub Actions YAML, Python 3 + PyYAML, QEMU user emulation, Podman Ubuntu 24.04.

## Global Constraints

- Add exactly `test_physics_slider`, `test_cloth`, `test_rope`, `test_soft_body`, and `test_destructible`; previous 80 + 5 = 85.
- Use the separate alternative `test_(physics_slider|cloth|rope|soft_body|destructible)$`.
- Do not edit the rigid-body alternative, product code, or test sources.
- Add no dependency, skip, retry, status mask, or assertion relaxation.
- Record that each module has a single scenario; do not widen the tests in this slice.

---

### Task 1: CI selection and documentation

- [ ] **Step 1:** Run the selection contract against the old workflow. It requires the five targets after `test_vehicle`, the exact alternative, rejection of `*_extra` names, and an explicit previous-80 + five set. Expected: FAIL at `missing extended physics build targets`.
- [ ] **Step 2:** Append the five targets and add the alternative in `.github/workflows/ci.yml` and the mirrored `docs/Build_Guide.md` command.
- [ ] **Step 3:** Re-run the contract; expected `exact 85-test extended physics selection and anchor contract passed`. Confirm the guide regex is byte-identical to the workflow.
- [ ] **Step 4:** Re-run focused native and cross: `ctest --verbose --no-tests=error -R '^test_(physics_slider|cloth|rope|soft_body|destructible)$'`; require 5/5 on both.
- [ ] **Step 5:** Append status, design, and missing-capability evidence. Commit as `ci: run arm64 extended physics tests`.

### Task 2: Final verification and remote proof

- [ ] **Step 1:** Native full `cmake . && make -j6 && ctest -j4 --timeout 240 --output-on-failure` in `build-core-app-net`; require 455, zero failures, four established skips.
- [ ] **Step 2:** Final clean-container workflow; require 85/85 and exactly one existing ptrace setup skip.
- [ ] **Step 3:** Read-only review; fix adopted findings test-first. Fetch/rebase if needed and push without force.
- [ ] **Step 4:** Run `build-core-app-net/assert_arm64_log.py <log> 85` on the exact-HEAD remote log. Record URLs, commit as `docs: record arm64 extended physics CI results`, and push.
