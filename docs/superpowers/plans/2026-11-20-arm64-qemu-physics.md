# arm64 QEMU Physics Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add eight rigid-body physics tests to the arm64 lane for an exact 80-test selection.

**Architecture:** Reuse eight generated executable-target QEMU commands. Change only the build target list and one locally anchored CTest alternative.

**Tech Stack:** CMake/CTest, GitHub Actions YAML, Python 3 + PyYAML, QEMU user emulation, Podman Ubuntu 24.04.

## Global Constraints

- Add exactly `test_physics`, `test_physics_replay`, `test_physics_sync`, `test_physics_hinge`, `test_physics_cone_twist`, `test_physics_identity`, `test_ragdoll`, and `test_vehicle`; previous 72 + 8 = 80.
- Use `test_(physics(_replay|_sync|_hinge|_cone_twist|_identity)?|ragdoll|vehicle)$`; the `$` must bind the whole optional suffix group.
- Keep sibling `test_physics_slider` and every future derived name out of the selection.
- Preserve all previous 72 tests, emulator settings, object checks, timeout, and failure propagation.
- Add no dependency, skip, retry, status mask, or assertion relaxation.
- Do not claim cross-architecture determinism, full arm64 CTest, cloth/rope/soft-body/destructible/slider, rendering, Snowflake/QUIC, GPU, or physical-device coverage.

---

### Task 1: CI selection and documentation

**Files:**
- Modify: `.github/workflows/ci.yml:210-229`
- Modify: `docs/Build_Guide.md`
- Modify: `docs/Implementation_Status.md`
- Modify: `docs/design/physics_extended.md`
- Modify: `docs/cross_engine/missing_capabilities.md`
- Create: `docs/superpowers/plans/2026-11-20-arm64-qemu-physics.md`

- [ ] **Step 1: Run the RED selection contract**

The contract parses the workflow, requires the eight build targets after
`test_task_singleton`, requires the exact alternative, asserts that
`test_physics_slider`, `test_physics_extra`, `test_physics_sync_extra`,
`test_ragdoll_extra`, and `test_vehicle_extra` do not match, then requires the
actual native selection to equal an explicit previous-72 set plus the eight
physics names. Expected before editing: FAIL at `missing physics build targets`.

- [ ] **Step 2: Apply the minimal workflow edit**

Append the eight targets to the build command and add the alternative inside the
existing outer capture group. Do not add a global end anchor.

- [ ] **Step 3: Run the GREEN contract**

Expected: `exact 80-test physics selection and anchor contract passed`.

- [ ] **Step 4: Re-run focused native and cross tests**

```bash
ctest --test-dir build-core-app-net --verbose --no-tests=error \
  -R '^test_(physics(_replay|_sync|_hinge|_cone_twist|_identity)?|ragdoll|vehicle)$'
```

Run the same regex against `build-arm64` in the multiarch Ubuntu container after
the workflow dependency step. Require 8/8 and 83/4/13/3/8/5/10/9 on both sides.

- [ ] **Step 5: Append documentation and commit**

Record case counts, the exact 80 selection, the anchor, the within-arm64
determinism boundary, and exclusions. Commit as `ci: run arm64 physics tests`.

### Task 2: Final verification and remote proof

- [ ] **Step 1:** In `build-core-app-net`, run `cmake . && make -j6 && ctest -j4
  --timeout 240 --output-on-failure`; require 455 tests, zero failures, and four
  established platform skips. Run `git diff --check`.
- [ ] **Step 2:** Execute the final workflow run blocks in a clean Ubuntu 24.04
  container with `:z` and runner CMake. Require 80/80, the eight new summaries,
  all old summaries/contracts/e2e, and exactly one existing ptrace setup skip.
- [ ] **Step 3:** Request read-only review of the selection, anchor, sibling
  exclusion, QEMU boundary, and docs. Fix adopted findings test-first. Fetch and
  rebase if needed, rerun affected inputs, and push without force.
- [ ] **Step 4:** Assert the exact-HEAD remote job reports `0 tests failed out of
  80`, the exact 80 names, all old/new evidence, and one existing ptrace setup
  skip. Record URLs, commit, and review in `docs/Implementation_Status.md`,
  commit as `docs: record arm64 physics CI results`, push, and finish clean with
  the broader goal open.
