# arm64 QEMU Animation Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add the eight registered animation tests to the arm64 lane for an exact 94-test selection.

**Architecture:** Reuse eight generated executable-target QEMU commands. Append eight build targets after `test_character` and add one new locally anchored alternative; leave every earlier alternative untouched.

**Tech Stack:** CMake/CTest, GitHub Actions YAML, Python 3 + PyYAML, QEMU user emulation, Podman Ubuntu 24.04.

## Global Constraints

- Add exactly `test_animation`, `test_anim_pose_authority`, `test_anim_morph`, `test_anim_facial`, `test_anim_compression`, `test_anim_locomotion`, `test_skeleton_socket`, `test_anim_aim`; previous 86 + 8 = 94.
- Use the alternative `test_(animation|anim_(pose_authority|morph|facial|compression|locomotion|aim)|skeleton_socket)$`.
- Do not edit product code, test sources, or earlier alternatives. Add no dependency, skip, retry, mask, or assertion relaxation.

---

### Task 1: CI selection and documentation

- [x] **Step 1:** Run `build-core-app-net/animation_selection_contract.py` against the old workflow. Expected: FAIL at `missing animation build targets`.
- [x] **Step 2:** Append the eight targets and the alternative in `.github/workflows/ci.yml` and the mirrored `docs/Build_Guide.md` command.
- [x] **Step 3:** Re-run the contract; expected `exact 94-test animation selection and anchor contract passed`. Confirm the guide regex is byte-identical to the workflow.
- [ ] **Step 4:** Re-run focused native and cross with the new alternative; require 8/8 and 37/2/10/8/13/1/1/1.
- [x] **Step 5:** Append status, design, and missing-capability evidence. Commit as `ci: run arm64 animation tests`.

### Task 2: Final verification and remote proof

- [ ] **Step 1:** Native full regression in `build-core-app-net`; require 455, zero failures, four established skips.
- [ ] **Step 2:** Final clean-container workflow; require 94/94 and exactly one existing ptrace setup skip.
- [ ] **Step 3:** Read-only review; fix adopted findings test-first. Fetch/rebase if needed and push without force.
- [ ] **Step 4:** Run `build-core-app-net/assert_arm64_log.py <log> 94 test_animation=37` on the exact-HEAD remote log. Record URLs, commit as `docs: record arm64 animation CI results`, and push.
