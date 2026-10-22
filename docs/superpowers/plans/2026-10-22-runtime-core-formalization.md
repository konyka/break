# Runtime Core Formalization and Stage 2 Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Promote the existing ECS/network focused slices into explicit production targets, then add a C11 Runtime Core ownership/message/IO coordination layer without prematurely implementing Lua, editor, online update, crash upload, anti-cheat, or World Partition.

**Architecture:** Stage 2 has two ordered phases. Phase A creates formal libraries for the already-tested ECS snapshot/schema/delta/AoI/replication/fragment and optional Snowflake adapter/session code without forcing Snowflake into the base `engine` library. Phase B adds Runtime Core contracts for lifecycle coordination, owned bounded messages, PAL/thread coordination, formal task submission, IO/VFS requests, hot reload coordination, and profiler collection. The existing compatibility APIs remain behavior-compatible while the new formal facade uses explicit ownership, non-blocking overload errors, and a single shutdown coordinator.

**Tech Stack:** C11 engine core; C++11 framework/application; existing CMake targets; existing `platform_thread.h`, TaskSystem, VFS, async loader, filewatch, profiler, Lua build artifacts, myui, and optional Snowflake `snow::net`; GCC/Clang; CTest; ASan/UBSan/TSan.

## Global Constraints

- C11 remains the runtime core language; C++11 remains the application/editor layer.
- Lua is the planned runtime scripting language, but Stage 2 defines only a boundary and does not implement `BreakLuaRuntime`.
- Runtime Core formal queues return non-blocking `BREAK_RUNTIME_OVERLOAD` when full.
- Network/IO/Audio/RHI hot paths never inline or wait for queue space in the formal facade.
- Legacy Task queue-full inline behavior remains unchanged and is documented separately from the formal facade.
- The global Runtime lifecycle is `CREATED -> STARTING -> RUNNING -> QUIESCING -> DRAINING -> STOPPING -> STOPPED/FAILED`.
- Subsystem states are local mappings and must not create a competing global lifecycle.
- Shutdown is coordinated by one owner: stop admission, stop producers, close mailboxes, drain bounded completions/close watermarks, join workers, then destroy IO/Network/RHI/PAL.
- A timeout retains live ownership and allows the same coordinator to retry; it must not free objects used by a live worker or reactor.
- Network wire fragments are capped at 64 KiB; one fragment assembly is capped at 16 MiB; internal messages and asset blobs use separate budgets.
- All new public handles are opaque C11 types with explicit borrowed/owned lifetime rules.
- Snapshot/World mutation remains GameThread-owned; network callbacks never call World, ECS, Lua, UI, or RHI.
- Normal, ASan/UBSan, and TSan focused tests are required for each promoted target; fuzz smoke targets are explicitly built before `ctest -L fuzz`.
- Focused/test-only status must never be described as formal engine/demo runtime integration.

---

## File and Target Map

### Phase A: formal target boundary

- Modify: `engine/CMakeLists.txt` — add formal, dependency-separated targets and keep test-only fault-injection macros test-local.
- Create: `engine/src/ecs/replication_runtime.h` — formal aggregate include/target contract for schema, snapshot, delta, and publication ownership; no implementation state.
- Create: `engine/src/network/break_replication_core.c` only if a non-Snowflake target needs a shared source boundary; otherwise keep existing source files and define target composition in CMake.
- Modify: `engine/tests/test_ecs_replication.c` — link against the formal ECS replication target instead of compiling implementation sources directly.
- Modify: `engine/tests/test_break_replication_fragment.c` — link against the formal fragment target.
- Modify: `engine/tests/test_break_net_adapter.c`, `test_break_session.c`, and `test_break_replication.c` — link against the optional `break_net` target.
- Modify: `docs/Architecture_Overview.md`, `docs/Implementation_Status.md`, `docs/design/ecs_snapshot_replication_aoi.md`, `docs/design/session_protocol.md`, `docs/design/snowflake_c11_adapter.md` — record the new target graph and remaining runtime integration boundaries.

### Phase B: Runtime Core

- Create: `engine/src/runtime/runtime_types.h` — formal error enum, lifecycle enum, queue/message metadata types using `u8/u16/u32/u64/usize` from `engine/src/core/types.h`.
- Create: `engine/src/runtime/runtime_coordinator.h/.c` — one-owner global lifecycle coordinator and ordered shutdown.
- Create: `engine/src/runtime/runtime_message.h/.c` — owned message envelope, borrowed view, release functions, checked size validation, correlation/sequence metadata.
- Create: `engine/src/runtime/runtime_queue.h/.c` — bounded MPSC/SPSC-compatible queue contract with non-blocking overload, reserved control capacity, FIFO and ownership transfer.
- Create: `engine/src/runtime/runtime_thread.h/.c` — formal wrapper around `platform_thread.h` with owner registration, completion condition, bounded wait and join ownership.
- Create: `engine/src/runtime/runtime_task.h/.c` — formal task submission facade over existing TaskSystem; legacy `task_submit` behavior remains untouched.
- Create: `engine/src/runtime/runtime_io.h/.c` — formal IO request/completion handles over existing VFS/async loader; completion waits are deadline/shutdown interruptible.
- Create: `engine/src/runtime/runtime_reload.h/.c` — design-level integration boundary for existing filewatch/hotreload, with staging/validate/commit/failed-keep-old state; no Lua VM implementation.
- Create: `engine/src/runtime/runtime_profiler.h/.c` — owner-thread event submission and collector bridge over existing profiler.
- Create: `engine/tests/test_runtime_core.c` — lifecycle, queue, ownership, overload, shutdown, timeout, stale generation, and error mapping tests.
- Create: `engine/tests/test_runtime_io.c` — VFS/async completion ownership, queue-full, cancel, deadline, and shutdown tests.
- Create: `engine/tests/test_runtime_reload.c` — file event coalescing, stale generation, failed-keep-old, commit ordering, and shutdown tests.
- Modify: `engine/CMakeLists.txt` — add `runtime_core` formal target and tests without linking Snowflake into the base `engine` target.
- Modify: `docs/design/runtime_*.md`, `docs/Architecture_Overview.md`, `docs/Implementation_Status.md` — record delivered versus remaining boundaries.

---

### Task 1: Formalize ECS and non-Snowflake replication targets

**Files:**
- Modify: `engine/CMakeLists.txt:319-403,1788-3280`
- Create: `engine/src/ecs/replication_runtime.h`
- Modify: `engine/tests/test_ecs_replication.c`, `engine/tests/test_break_replication_fragment.c`
- Test: existing ECS/replication focused tests

**Interfaces:**
- Produces a formal `break_ecs_replication` static target containing `replication_schema.c`, `world_snapshot.c`, `world_delta.c`, and the ECS-owned transaction helpers required by delta apply.
- Produces a formal `break_replication_core` target containing `break_aoi.c`, `break_replication.c`, and `break_replication_fragment.c`, with no Snowflake dependency.
- Keeps `BREAK_WORLD_DELTA_TESTING=1` private to test targets.

- [ ] Write a CMake contract test or configure assertion that `ENGINE_BUILD_TESTS=OFF` still produces the formal non-Snowflake replication libraries.
- [ ] Run a deliberately failing configure/build before adding the target composition, proving the current implementation sources are test-only.
- [ ] Add the target definitions without adding them to `engine` until their public dependency direction is explicit; link focused tests to the new targets instead of listing `.c` files directly.
- [ ] Build `test_ecs`, `test_ecs_replication`, and `test_break_replication_fragment` through the new targets.
- [ ] Run normal, ASan/UBSan, and TSan focused tests; reject any missing executable as a validation failure.
- [ ] Update CMake comments and architecture/status docs to distinguish formal optional libraries from `engine` and demo consumers.
- [ ] Review the target graph for duplicate compilation of `break_replication_fragment.c` and remove duplicate source ownership where safe.

### Task 2: Formalize optional Snowflake network/session target

**Files:**
- Modify: `engine/CMakeLists.txt:291-308,3230-3280`
- Modify: `engine/tests/test_break_net_adapter.c`, `test_break_session.c`, `test_break_replication.c`
- Modify: `docs/design/snowflake_c11_adapter.md`, `docs/design/session_protocol.md`

**Interfaces:**
- Produces `break_net` when `BREAK_ENABLE_SNOWFLAKE=ON`, independent of `ENGINE_BUILD_TESTS`.
- Keeps `engine` transport-neutral; consumers opt into `break_net` and `snow::net` explicitly.
- Preserves `break_net_reactor_set_acceptor`, `break_net_reactor_send`, `break_session_manager_attach_reactor`, and the existing loopback contracts.

- [ ] Add a CMake configure test with Snowflake enabled and tests disabled; verify `break_net` is generated and the base `engine` target remains transport-neutral.
- [ ] Add a fail-closed configure test for missing `SNOWFLAKE_SOURCE_DIR`.
- [ ] Move the adapter-backed test executables to link the formal `break_net` target rather than relying on a target defined only inside the test block.
- [ ] Build and run the real loopback adapter/session tests in normal, ASan/UBSan, and TSan trees.
- [ ] Record that `engine_demo` and `dxx_break` do not consume `break_net` until a separate production application integration task explicitly adds it.

### Task 3: Define Runtime Core types and lifecycle coordinator

**Files:**
- Create: `engine/src/runtime/runtime_types.h`
- Create: `engine/src/runtime/runtime_coordinator.h/.c`
- Create: `engine/tests/test_runtime_core.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
```c
typedef enum BreakRuntimeError {
    BREAK_RUNTIME_OK = 0,
    BREAK_RUNTIME_INVALID,
    BREAK_RUNTIME_CLOSED,
    BREAK_RUNTIME_OVERLOAD,
    BREAK_RUNTIME_OOM,
    BREAK_RUNTIME_TIMEOUT,
    BREAK_RUNTIME_STALE,
    BREAK_RUNTIME_REJECTED,
    BREAK_RUNTIME_FAILED
} BreakRuntimeError;

typedef enum BreakRuntimeState {
    BREAK_RUNTIME_CREATED = 0,
    BREAK_RUNTIME_STARTING,
    BREAK_RUNTIME_RUNNING,
    BREAK_RUNTIME_QUIESCING,
    BREAK_RUNTIME_DRAINING,
    BREAK_RUNTIME_STOPPING,
    BREAK_RUNTIME_STOPPED,
    BREAK_RUNTIME_FAILED
} BreakRuntimeState;
```

- [ ] Write RED tests for legal lifecycle transitions, invalid transitions, timeout retaining ownership, retrying stop from `STOPPING`, and sticky `FAILED` admission behavior.
- [ ] Implement the coordinator as a Game/Main owner object; no mutex is used to make arbitrary multi-owner mutation legal.
- [ ] Implement explicit subsystem admission/drain/join callbacks in a bounded table; callbacks must run in the documented order and return `BreakRuntimeError`.
- [ ] Make timeout return `BREAK_RUNTIME_TIMEOUT` without freeing live resources.
- [ ] Run normal/ASan/TSan `test_runtime_core` and update the lifecycle diagrams.

### Task 4: Implement owned messages, bounded queues, and formal task facade

**Files:**
- Create: `engine/src/runtime/runtime_message.h/.c`
- Create: `engine/src/runtime/runtime_queue.h/.c`
- Create: `engine/src/runtime/runtime_task.h/.c`
- Modify: `engine/tests/test_runtime_core.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
```c
typedef struct BreakRuntimeMessageView {
    u16 kind;
    u16 version;
    u32 flags;
    u64 sequence;
    const void *data;
    usize size;
} BreakRuntimeMessageView;

typedef struct BreakRuntimeOwnedMessage BreakRuntimeOwnedMessage;
BreakRuntimeError break_runtime_message_copy(
    const BreakRuntimeMessageView *view,
    BreakRuntimeOwnedMessage **out_message);
void break_runtime_message_release(BreakRuntimeOwnedMessage *message);
```

- [ ] Write RED tests for borrowed-to-owned copy, NULL/size overflow, double release rejection in test builds, FIFO order, reserved control capacity, overload, and stale generation.
- [ ] Implement queue nodes that own payloads and never retain stack/World/Lua/Snowflake/UI pointers.
- [ ] Keep legacy TaskSystem behavior unchanged; implement a separate formal task submit API that returns overload instead of inline execution when its formal queue is full.
- [ ] Add shutdown wakeup to queue waiters; formal APIs never wait for capacity on Network/IO/Audio/RHI paths.
- [ ] Run normal/ASan/TSan queue and task tests, including failure injection for allocation and queue-full paths.

### Task 5: Implement formal PAL/thread and IO/VFS facade

**Files:**
- Create: `engine/src/runtime/runtime_thread.h/.c`
- Create: `engine/src/runtime/runtime_io.h/.c`
- Create: `engine/tests/test_runtime_io.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
```c
typedef struct BreakRuntimeThread BreakRuntimeThread;
typedef struct BreakRuntimeIoRequest BreakRuntimeIoRequest;

BreakRuntimeError break_runtime_thread_start(
    BreakRuntimeThread *thread);
BreakRuntimeError break_runtime_thread_stop(
    BreakRuntimeThread *thread, u32 timeout_ms);

BreakRuntimeError break_runtime_io_submit(
    BreakRuntimeIoRequest **out_request,
    const char *path,
    u32 flags,
    u64 deadline_ns);
BreakRuntimeError break_runtime_io_cancel(BreakRuntimeIoRequest *request);
BreakRuntimeError break_runtime_io_poll_completion(
    BreakRuntimeIoRequest *request,
    BreakRuntimeOwnedMessage **out_completion);
void break_runtime_io_request_release(BreakRuntimeIoRequest *request);
```

- [ ] Write RED tests for thread start/stop timeout, owner completion, IO completion ownership, cancel-before-start, stale generation, queue overload, and shutdown interruption.
- [ ] Wrap existing `platform_thread.h` without exposing OS handles in public headers.
- [ ] Adapt existing VFS/async loader only through a formal completion bridge; compatibility loader waits remain unchanged.
- [ ] Make completion waits deadline- and shutdown-interruptible; never invoke GameThread callbacks on IO workers.
- [ ] Run normal/ASan/TSan and a VFS/asset-focused build.

### Task 6: Implement reload and profiler formal boundaries

**Files:**
- Create: `engine/src/runtime/runtime_reload.h/.c`
- Create: `engine/src/runtime/runtime_profiler.h/.c`
- Create: `engine/tests/test_runtime_reload.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**
```c
typedef struct BreakRuntimeReload BreakRuntimeReload;
typedef u64 BreakRuntimeReloadRequest;

typedef enum BreakRuntimeReloadState {
    BREAK_RUNTIME_RELOAD_LOADING = 0,
    BREAK_RUNTIME_RELOAD_VALIDATING,
    BREAK_RUNTIME_RELOAD_COMMITTED,
    BREAK_RUNTIME_RELOAD_FAILED_KEEP_OLD,
    BREAK_RUNTIME_RELOAD_CANCELLED,
    BREAK_RUNTIME_RELOAD_TIMEOUT,
    BREAK_RUNTIME_RELOAD_OOM
} BreakRuntimeReloadState;

BreakRuntimeError break_runtime_reload_request(
    BreakRuntimeReload *reload,
    const char *path,
    BreakRuntimeReloadRequest *out_request);
BreakRuntimeError break_runtime_reload_poll(
    BreakRuntimeReload *reload,
    BreakRuntimeReloadRequest request,
    BreakRuntimeReloadState *out_state);
BreakRuntimeError break_runtime_reload_cancel(
    BreakRuntimeReload *reload,
    BreakRuntimeReloadRequest request);
```

- [ ] Write RED tests for file event coalescing, staging/validation failure preserving old data, stale generation, cancel/timeout/OOM, queue overload, exactly-once completion, and shutdown.
- [ ] Integrate existing filewatch/hotreload only through owner-thread commit; do not implement Lua VM in this task.
- [ ] Define profiler event ownership and collector handoff over existing `profiler.c`; no profiler callback may block a hot path.
- [ ] Run normal/ASan/TSan reload/profiler tests and document the Lua Stage 3 dependency.

### Task 7: Formal target validation and documentation closeout

**Files:**
- Modify: `engine/CMakeLists.txt`
- Modify: all `docs/design/runtime_*.md`
- Modify: `docs/Architecture_Overview.md`, `docs/Implementation_Status.md`
- Modify: `docs/superpowers/plans/2026-10-22-runtime-expansion-todo.md`

- [ ] Configure a clean normal tree with tests and Snowflake enabled; build every formal ECS/network/runtime target explicitly.
- [ ] Configure clean ASan/UBSan and TSan trees; build the same target list explicitly and run focused CTest.
- [ ] Explicitly build all five fuzz targets and run `ctest -L fuzz`; record target paths and result counts.
- [ ] Run full non-graphics/non-fuzz CTest after the complete normal build; classify graphics failures, skipped platform gates, and unrelated failures separately.
- [ ] Run `git diff --check` and verify every design document agrees with actual target graph and delivered interfaces.
- [ ] Mark only evidence-backed todo items complete; leave Stage 3 Lua, Stage 4 editor, Stage 5 online/crash/security, and Stage 6 graphics lifecycle as separate pending plans.

## Cross-cutting Review Gates

- Every task must include RED evidence before production code and GREEN normal/ASan/TSan evidence afterward.
- No task may expose a raw `World *`, `Archetype *`, `Chunk *`, OS thread handle, Snowflake connection, Lua VM pointer, or RHI handle through a new public formal facade.
- Any new capacity must have both count and byte overflow checks, a bounded failure result, and a test for preserving old state.
- Any shutdown path must have a producer-stop point, queue-drain rule, owner join rule, timeout behavior, and retry/cleanup owner.
- Formal target promotion must not silently change legacy compatibility API behavior.
- A task is complete only after focused code review, documentation update, and `git diff --check`.
