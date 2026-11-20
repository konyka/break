# arm64 QEMU Core App Offline Tests Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add core_app network unit and deterministic offline tests to the arm64 lane for an exact 33-test selection.

**Architecture:** Use executable-target emulation for the unit test and a dedicated optional `CORE_APP_RUNNER` for direct core_app launches in the host CMake driver. Select exactly unit/offline, excluding unregistered cross transport scenarios and native loopback/voice modes.

**Tech Stack:** CMake/CTest, core_app, QEMU user emulation, GitHub Actions YAML, Python 3 + PyYAML, Podman Ubuntu 24.04.

## Global Constraints

- Add two tests: network unit 25 cases and offline deterministic/no-network-symbol test; exact total 33.
- Do not select loopback/voice/start-failure/net-transport tests in this slice.
- Preserve native direct execution, existing target-aware NM, and all prior 31 tests/skips.
- No new dependency, skip, retry, filtering, masking, or full-suite/device/QUIC claims.

---

### Task 1: Core app runner

**Files:** `engine/CMakeLists.txt:5380-5390`, `engine/tests/test_core_app_network.cmake`.

- [ ] **Step 1: Preserve RED**

Retain direct unit 25/25 and offline direct-exec failure with NETWORK_TRANSPORT=OFF and target NM already correct.

- [ ] **Step 2: Add optional runner**

Forward after offline `CORE_APP`:

```cmake
            "-DCORE_APP_RUNNER=${CMAKE_CROSSCOMPILING_EMULATOR}"
```

Replace every `COMMAND "${CORE_APP}"` in the driver with:

```cmake
COMMAND ${CORE_APP_RUNNER} "${CORE_APP}"
```

This covers offline, start-failure helper, and network server sites without prefixing NM, NET_CLIENT, trace tools, or host CMake.

- [ ] **Step 3: Verify native and cross focused tests**

Native from `build-core-app-net`: configure/build `test_core_app_network core_app`, then `ctest --verbose --no-tests=error -R '^test_core_app_network(_offline)?$'`; require 2/2 and 25/25 with direct core_app. Cross in the emulator-configured Ubuntu tree: build same targets and run same regex; require 2/2, unit 25/25, deterministic offline and no-network symbol scan, no skip 77.

- [ ] **Step 4: Commit**

`test: support emulated core app offline` for the two files.

### Task 2: CI and evidence

**Files:** `.github/workflows/ci.yml`, `docs/Build_Guide.md`, `docs/Implementation_Status.md`, `docs/design/core_app_integration.md`, `docs/cross_engine/missing_capabilities.md`.

- [ ] **Step 1: Run RED CI contract**

Require build command ending `test_core_app_network core_app`, regex alternative `test_core_app_network($|_offline)`, and actual native selection previous 31 plus exactly unit/offline = 33. Explicitly assert no `test_core_app_network_loopback`, voice, start-failure, or net-transport name is selected. Expected RED on old build.

- [ ] **Step 2: Apply minimal CI edit**

Append `test_core_app_network core_app` and add `test_core_app_network($|_offline)` to the existing regex. Keep all other inputs unchanged.

- [ ] **Step 3: Verify GREEN/full native**

Rerun exact 33/PASS and exclusion checks. Run native full `cmake . && make -j6 && ctest -j4 --timeout 240 --output-on-failure`; expected 455 tests, zero failures, four established skips. Run `git diff --check`.

- [ ] **Step 4: Update docs and commit**

Record 25-case unit, deterministic offline traces/no-network symbols, exact 33 selection and excluded transport modes. Commit CI/docs/plan as `ci: run arm64 core app offline tests`.

### Task 3: Final verification and remote proof

- [ ] **Step 1:** Run final clean-container workflow after fetch/rebase if needed; require 33 targets, 33/33, all old summaries, unit 25/25, offline success, exactly one existing integrity skip.
- [ ] **Step 2:** Request read-only review of runner scope, exact regex/exclusions, native compatibility, and docs; fix adopted findings test-first.
- [ ] **Step 3:** Push and assert remote `0 tests failed out of 33`, all old/new evidence, and exactly one existing integrity skip. Add run/job URLs/commit to implementation status, commit as `docs: record arm64 core app CI results`, push, and finish clean with broader goal open.
