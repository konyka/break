# Core App Crash Context Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Add an opt-in `core_app --crash-context DIR` path that publishes sanitized RHI, network, and input snapshots into real crash records without changing default behavior or adding upload behavior.

**Architecture:** `core_app_runtime` publishes borrowed, neutral snapshots through optional hooks on `CoreAppThread`. A separate `core_app_diagnostics` library owns `break_crash` installation, formatting, publication, and cleanup; only the `core_app` executable links it. Tests distinguish pure input reduction, real sink/crash capture, and full-process lifecycle.

**Tech Stack:** C11, CMake/CTest, existing `core_app`, `break_crash`, `BreakCrashSummary`, POSIX signal/fork tests, test-only LD_PRELOAD fault injection.

## Global Constraints

- Default runs do not install crash handlers, create a spool, or publish context. No upload adapter or upload call is added.
- `core_app_runtime`, `core_app_asset_bake`, `engine`, existing demos, and the editor do not directly link `break_crash`.
- Only `CoreAppThread` produces snapshots. No locks, cross-thread reads, heap allocation, raw key codes, text, coordinates, addresses, connection identifiers, or credentials.
- `BREAK_ENABLE_CRASH=OFF` keeps `core_app` buildable and rejects `--crash-context` as unavailable. Windows stub installation fails explicitly.
- Default Vulkan; OpenGL remains fallback/image comparison. Linux uses native Wayland only.
- Follow repository and Google naming. Do not introduce compatibility-engine prefixes, retired domain vocabulary, or role labels.
- Append documentation rather than rewriting historical records. No PR; push `master` only after reviews and validation.
- Design authority: `docs/superpowers/specs/2026-11-22-core-app-crash-context-design.md`.

## File Structure

- `engine/apps/core_app/core_app.h`: neutral snapshot and borrowed hooks.
- `engine/apps/core_app/core_app_input.{h,c}`: reduce a real input frame to counts/status only.
- `engine/apps/core_app/core_app.c`: configuration validation and owner-thread publication.
- `engine/apps/core_app/core_app_diagnostics.{h,c}`: crash installation, formatting, publication, cleanup.
- `engine/apps/core_app/main.c`: opt-in CLI and guaranteed cleanup.
- `engine/tests/test_core_app_runtime.c`: input reduction and invalid-hook tests.
- `engine/tests/test_core_app_diagnostics.c`: sink and real child-crash tests.
- `engine/tests/core_app_crash_record.c`: recovered-record verifier used by the full-process CMake test.
- `engine/tests/test_core_app_crash_context.cmake`: real `core_app` crash lifecycle.
- `engine/tests/test_core_app_lifecycle_preload.c`: test-only frame-triggered `SIGABRT`.
- `engine/tests/test_core_app_target_contract.cmake`: CLI, build, and link contracts.
- `engine/CMakeLists.txt`: formal optional library, executable link gate, tests.

---

### Task 1: Neutral snapshot and runtime publication

**Files:**
- Modify: `engine/apps/core_app/core_app.h`
- Modify: `engine/apps/core_app/core_app_input.h`
- Modify: `engine/apps/core_app/core_app_input.c`
- Modify: `engine/apps/core_app/core_app.c`
- Test: `engine/tests/test_core_app_runtime.c`

**Interfaces:**
- Produces:

```c
typedef struct CoreAppInputDiagnostics {
    u32 tick;
    u32 key_down_count;
    u32 pad_connected_count;
    u32 touch_count;
    u32 gesture_count;
    u32 touch_status;
    u32 haptic_status;
} CoreAppInputDiagnostics;

void core_app_input_diagnostics(const CoreAppInputFrame *frame,
                                CoreAppInputDiagnostics *out);

typedef struct CoreAppDiagnosticsSnapshot {
    u32 tick;
    const char *rhi_backend;
    const char *gpu_name;
    bool network_live;
    u64 network_events_seen;
    u64 network_events_dropped;
    u32 key_down_count;
    u32 pad_connected_count;
    u32 touch_count;
    u32 gesture_count;
    u32 touch_status;
    u32 haptic_status;
} CoreAppDiagnosticsSnapshot;

typedef void (*CoreAppDiagnosticsPublishFn)(
    void *user, const CoreAppDiagnosticsSnapshot *snapshot);
typedef struct CoreAppDiagnosticsHooks {
    void *user;
    CoreAppDiagnosticsPublishFn publish;
} CoreAppDiagnosticsHooks;
```

`CoreAppConfig` gains `const CoreAppDiagnosticsHooks *diagnostics`.

- [ ] **Step 1: Write failing input and configuration tests**

Add `input_diagnostics_reduces_real_frame_to_counts_and_status` to `test_core_app_runtime.c`: create a real `CoreAppInput`, begin tick 7, apply one held key and one pad connection, obtain `CoreAppInputFrame`, then require tick 7, one held key, one connected pad, zero touches/gestures, and current status values. Call with NULL output and require a safe no-op. Add `invalid_diagnostics_hooks_fail_before_io`:

```c
CoreAppDiagnosticsHooks hooks = {0};
CoreAppConfig config = {0};
config.diagnostics = &hooks;
int exit_code = 0;
ASSERT_EQ(core_app_run(&config, &exit_code), BREAK_RUNTIME_FAILED);
ASSERT_EQ(exit_code, 2);
```

The invalid configuration must be rejected before scenario/asset file access.

- [ ] **Step 2: Verify RED**

```bash
cmake --build build-current-vk --target test_core_app_runtime -j2
```

Expected: missing `CoreAppInputDiagnostics`, `CoreAppDiagnosticsHooks`, `core_app_input_diagnostics`, or `CoreAppConfig.diagnostics` compilation failure.

- [ ] **Step 3: Implement minimal neutral reduction and publication**

`core_app_input_diagnostics` zeros the output then copies tick/status, counts held/pressed keys in all 512 slots, connected pads, and frame touch/gesture counts. It never exposes raw key codes, coordinates, or source IDs.

Validate non-NULL hooks have a non-NULL callback in `core_app_run`'s existing configuration block. Add a static publication helper that returns immediately without hooks. It reads `CoreAppGpu.backend_name/device_name` only when live, otherwise fixed `record`/`none`, current network counters, and calls `core_app_input_frame` + `core_app_input_diagnostics`, then copies the helper's scalar fields into the flat snapshot. Publish tick 0 after `runtime_running` and at the end of every completed tick after `app_voice_tick`. Do not publish from workers or during teardown.

- [ ] **Step 4: Verify GREEN**

```bash
cmake --build build-current-vk --target test_core_app_runtime -j2
./build-current-vk/test_core_app_runtime
```

Expected: all previous cases plus the two new cases pass. Full runtime publication is proved end-to-end in Task 3.

- [ ] **Step 5: Commit after task review**

```bash
git add engine/apps/core_app/core_app.h engine/apps/core_app/core_app_input.h \
  engine/apps/core_app/core_app_input.c engine/apps/core_app/core_app.c \
  engine/tests/test_core_app_runtime.c
git commit -m "feat(core-app): publish neutral diagnostics snapshots"
```

### Task 2: Diagnostics sink and real crash-record verifier

**Files:**
- Create: `engine/apps/core_app/core_app_diagnostics.h`
- Create: `engine/apps/core_app/core_app_diagnostics.c`
- Create: `engine/tests/test_core_app_diagnostics.c`
- Create: `engine/tests/core_app_crash_record.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: Task 1's `CoreAppDiagnosticsSnapshot`.
- Produces:

```c
bool core_app_diagnostics_start(const char *spool_root);
void core_app_diagnostics_stop(void);
void core_app_diagnostics_publish(
    void *user, const CoreAppDiagnosticsSnapshot *snapshot);
```

- [ ] **Step 1: Write failing sink and crash tests**

`test_core_app_diagnostics.c` uses a snapshot with `rhi_backend="vulkan"`, `gpu_name="Device/Name"`, network counters 7/2, and input tick 4/key count 1. Verify the formatted blob has `[rhi]`, `[net]`, `[input]`, sanitized `Device_Name`, `seen=7`, `dropped=2`, `tick=4`, and `keys=1`. NULL snapshot is a no-op.

On POSIX, fork a child that executes `core_app_diagnostics_start(root)`, publishes the snapshot, and raises `SIGSEGV`. The parent uses `test_waitpid_deadline(pid, &status, 30000u)` and requires `WTERMSIG(status) == SIGSEGV`. Open the spool, require one pending record, parse it with `break_crash_record_parse`, and compare the context blob field-by-field. Use a helper that frees the spool, parsed record, and bytes on every exit. Windows expects `core_app_diagnostics_start` to return false and does not claim a captured record.

`core_app_crash_record.c` accepts exactly `<spool-root> <expected-tick>` and performs the same recovery, requiring `backend=record`, `gpu=none`, `live=false`, `tick=<expected>`, `keys=1`, and no `/`, `\\`, or newline inside values. It returns distinct nonzero codes for usage, recovery, parse, and contract failures so CMake cannot confuse them.

- [ ] **Step 2: Verify RED**

Add the formal `core_app_diagnostics` target and `test_core_app_diagnostics` registration, then:

```bash
cmake -S engine -B build-core-app-diagnostics \
  -DENGINE_RHI_BACKEND=vulkan -DMYUI_PAL=dummy -DENGINE_BUILD_TESTS=ON
cmake --build build-core-app-diagnostics --target test_core_app_diagnostics -j2
```

Expected: missing `core_app_diagnostics.h` or source compilation failure before implementation.

- [ ] **Step 3: Implement bounded installation and formatting**

`start` rejects NULL/empty roots and delegates to `break_crash_install`; `stop` clears the blob then uninstalls. `publish` uses a stack `BreakCrashSummary` and a `BREAK_CRASH_CONTEXT_BLOB_MAX + 1` buffer. Emit:

```text
[rhi]
backend=<rhi_backend>
gpu=<gpu_name>
[net]
live=<true|false>
seen=<u64>
dropped=<u64>
[input]
tick=<u32>
keys=<key_down_count>
pads=<pad_connected_count>
touches=<touch_count>
gestures=<gesture_count>
touch_status=<u32>
haptic_status=<u32>
```

Use fixed-size numeric buffers and existing summary sanitization. Do not allocate, upload, or read any path/address/credential.

Register the library and test. Only `core_app` links `core_app_diagnostics` when `TARGET break_crash`; set `CORE_APP_CRASH_CONTEXT=1/0` on that executable. `core_app_runtime` remains unchanged by this link rule.

- [ ] **Step 4: Verify GREEN**

```bash
cmake --build build-core-app-diagnostics --target test_core_app_diagnostics -j2
./build-core-app-diagnostics/test_core_app_diagnostics
```

Expected: formatting and real child-crash cases pass with bounded waits and no sanitizer diagnostics.

- [ ] **Step 5: Commit after task review**

```bash
git add engine/apps/core_app/core_app_diagnostics.h \
  engine/apps/core_app/core_app_diagnostics.c \
  engine/tests/test_core_app_diagnostics.c \
  engine/tests/core_app_crash_record.c engine/CMakeLists.txt
git commit -m "feat(core-app): capture sanitized crash context"
```

### Task 3: CLI and full-process crash lifecycle

**Files:**
- Modify: `engine/apps/core_app/main.c`
- Modify: `engine/tests/test_core_app_lifecycle_preload.c`
- Modify: `engine/tests/test_core_app_target_contract.cmake`
- Create: `engine/tests/test_core_app_crash_context.cmake`
- Modify: `engine/CMakeLists.txt` only if Task 2 did not register the new script

**Interfaces:**
- Consumes: Task 1 hooks and Task 2 installation/publication/verifier.
- Produces: CLI `--crash-context DIR` and CTest `test_core_app_crash_context`.

- [ ] **Step 1: Write failing CLI and real-process tests**

Extend the target contract: help lists `--crash-context DIR`; empty DIR fails; an invalid spool root fails before runtime; default execution creates no spool; the binary has no `break_crash_upload_http` symbols. A nested `BREAK_ENABLE_CRASH=OFF` configure must still build `core_app` and reject the option as unavailable.

Create `test_core_app_crash_context.cmake`: on supported native Linux, generate a scenario that loads a level, holds `w` for two frames, and quits on tick 3. Run the real executable with `--render=record --audio=record --crash-context <root>` and test-only preload `CORE_APP_TEST_ABORT_ON_FRAME=2`. Require `SIGABRT`, invoke `core_app_crash_record <root> 1`, and require verifier success. Non-preload platforms report this full-process case as not run; never translate it into a pass.

- [ ] **Step 2: Verify RED**

```bash
cmake --build build-core-app-diagnostics --target core_app core_app_crash_record -j2
ctest --test-dir build-core-app-diagnostics --output-on-failure \
  -R '^(test_core_app_target_contract|test_core_app_crash_context)$'
```

Expected: unknown/malformed `--crash-context` and no crash lifecycle, not a missing fixture.

- [ ] **Step 3: Implement CLI cleanup and test-only fault trigger**

Parse `--crash-context` using `take_value`; empty or unavailable values fail. After all other argument validation, create hooks, call `core_app_diagnostics_start`, publish an initial snapshot with requested render backend, `gpu_name="pending"`, and zeroed counters, then call `core_app_run`. Call `core_app_diagnostics_stop` exactly once before returning, while preserving the original result.

In the preload only, count `vfprintf` messages containing `event=frame frame=`. After forwarding the requested frame to the real function, call `abort()` when `CORE_APP_TEST_ABORT_ON_FRAME` matches. This is test-only injection; add no production crash option or test hook.

- [ ] **Step 4: Verify GREEN**

```bash
cmake --build build-core-app-diagnostics --target core_app core_app_crash_record -j2
ctest --test-dir build-core-app-diagnostics --output-on-failure \
  -R '^(test_core_app_diagnostics|test_core_app_target_contract|test_core_app_crash_context)$'
```

Expected: sink, CLI, and real `SIGABRT` record verification pass. Independently run default `core_app --help` and the `BREAK_ENABLE_CRASH=OFF` contract.

- [ ] **Step 5: Commit after task review**

```bash
git add engine/apps/core_app/main.c engine/tests/test_core_app_lifecycle_preload.c \
  engine/tests/test_core_app_target_contract.cmake \
  engine/tests/test_core_app_crash_context.cmake engine/CMakeLists.txt
git commit -m "feat(core-app): add opt-in crash context lifecycle"
```

### Task 4: Documentation, independent review, and delivery

- [ ] **Step 1: Append contracts and exact evidence**

Append `docs/design/crash_reporting.md`, `docs/design/crash_symbolization.md`, `docs/cross_engine/missing_capabilities.md`, `docs/Implementation_Status.md`, `docs/Build_Guide.md`, and `docs/testing/cross_platform_matrix.md`. Include default-off behavior, privacy field allowlist, initial `pending` snapshot, tick publication, install/stop order, unsupported platforms, no-upload boundary, and actual RED/GREEN/test counts.

- [ ] **Step 2: Independent review and fixes**

Request read-only spec and quality reviews of all changes and test the named risks: default link closure, teardown after every early return, stale borrowed strings, hook thread identity, raw input/network leakage, child timeout cleanup, and false-positive recovery assertions. Fix every Critical/Important finding through a new RED/GREEN cycle and scoped re-review.

- [ ] **Step 3: Full local and platform validation**

Run focused tests, complete Vulkan/OpenGL suites, ASan/UBSan nongraphics + fuzz, relevant TSan, root/default build contracts, and available Windows/macOS/arm64 lanes. Real `SIGABRT` full-process evidence is native Linux only; do not claim Windows/macOS capture from formatting tests. Preserve existing platform skips and document unavailable physical devices.

- [ ] **Step 4: Synchronize, push, and verify remote**

```bash
git diff --check
git fetch origin
git rebase origin/master
git push origin HEAD:master
```

Re-run affected tests after any rebase. Verify CI, windows-d3d12, QUIC when triggered, and Proton artifact ancestry. Append actual run IDs/outcomes to the status documents, push that receipt update, verify its final workflows, and leave `HEAD == origin/master` with a clean tree and no temporary worktree.
