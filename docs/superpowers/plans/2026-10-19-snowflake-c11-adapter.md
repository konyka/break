# Snowflake C11 Network Adapter Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [x]`) syntax for tracking.

**Goal:** Integrate Break's C11 runtime with Snowflake's passive reactor through a tested opaque-handle adapter supporting dedicated reactor threads and deterministic step mode.

**Architecture:** Add a C11 Break adapter that owns lifecycle, bounded inbound/outbound queues, protocol-envelope validation, and Snowflake status translation. Snowflake remains the owner of sockets, epoll/io_uring/kqueue/IOCP, connections, parser execution, and transport queues; GameThread remains the owner of sessions, ECS, World, and Lua.

**Tech Stack:** C11, CMake, CTest, Snowflake C API at `/home/timeshift/opensource/snowflake`, existing Break task/queue/error conventions, GCC/Clang, ASan/TSan where supported.

## Global Constraints

- Keep the Break core C11; do not add C++ to the adapter.
- Do not reimplement sockets, epoll, io_uring, kqueue, IOCP, Snowflake connection management, or Snowflake transport queues.
- Do not expose Snowflake concrete structs in Break public headers.
- Only one thread may drive each Snowflake reactor.
- Snowflake callbacks may validate, copy/transfer bounded payloads, update metrics, and enqueue events; they may not call Lua, mutate ECS/World, call UI/RHI, or block on GameThread.
- GameThread owns sessions and gameplay state.
- Step mode is required for deterministic tests and editor-local preview.
- Thread mode is required for production server execution.
- Every behavior must have a CTest test before implementation changes are accepted.
- Do not silently fall back to an unrelated transport when Snowflake is unavailable.
- No commits or remote pushes are part of this plan; integration is a separate explicit action.
- The former single-agent serial restriction is removed. Keep dependent implementation tasks ordered, but run independent read-only reviews, platform checks, documentation checks, and isolated test lanes in parallel when they do not write the same files.

---

## File Map

Create:

- `engine/src/network/break_net_adapter.h` — public opaque C11 adapter API, mode/config/status/event types.
- `engine/src/network/break_net_adapter.c` — lifecycle, Snowflake reactor ownership, driver thread, stop/join state machine.
- `engine/src/network/break_net_message.h` — bounded inbound/outbound message records and ownership helpers.
- `engine/src/network/break_net_message.c` — message allocation, copy, release, queue-facing helpers.
- `engine/src/network/break_net_protocol.h` — envelope constants, validation result and parser-facing declarations.
- `engine/src/network/break_net_protocol.c` — length/version/ID/sequence validation without gameplay decoding.
- `engine/tests/test_break_net_adapter.c` — lifecycle, mode, ownership, queue, callback isolation, protocol tests.
- `docs/design/snowflake_c11_adapter.md` — implementation-facing API, ownership, threading, and shutdown documentation.

Modify:

- `engine/CMakeLists.txt` — add the adapter sources and Snowflake dependency option/target wiring using the repository's existing CMake conventions.
- `engine/tests/CMakeLists.txt` or the existing test registration location — add `test_break_net_adapter`.
- `engine/CMakePresets.json` or the existing dependency configuration file only if the current project has a checked-in Snowflake path/cache variable convention; otherwise use a documented `SNOWFLAKE_SOURCE_DIR` cache variable in `engine/CMakeLists.txt`.

Do not modify `/home/timeshift/opensource/snowflake`.

---

## Task 1: Establish the failing contract tests

**Files:**
- Create: `engine/tests/test_break_net_adapter.c`
- Modify: `engine/tests/CMakeLists.txt` or current test registration file
- Inspect: `engine/tests/test_framework.h`, `engine/tests/test_task.c`, `engine/tests/test_network.c`, `engine/CMakeLists.txt`

**Interfaces:**
- Consumes: current test framework and Snowflake availability configuration.
- Produces: named tests that define the adapter contract before implementation.

- [x] **Step 1: Read the existing test registration and assertion conventions**

Run:

```bash
sed -n '1,240p' engine/tests/test_framework.h
sed -n '1,220p' engine/tests/test_network.c
sed -n '1,220p' engine/CMakeLists.txt
```

Record the existing test entry-point and CTest naming convention in the implementation notes.

- [x] **Step 2: Write failing lifecycle tests**

Add tests with explicit names:

```c
static void test_break_net_adapter_rejects_null_config(void);
static void test_break_net_adapter_step_lifecycle(void);
static void test_break_net_adapter_rejects_duplicate_start(void);
static void test_break_net_adapter_stop_is_idempotent(void);
static void test_break_net_adapter_thread_lifecycle(void);
static void test_break_net_adapter_requires_snowflake(void);
```

The tests must call the planned public names and fail to compile before the header exists.

- [x] **Step 3: Run the new test target and confirm the expected failure**

Run:

```bash
cmake -S engine -B engine/build-break-net-contract -DENGINE_BUILD_TESTS=ON -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/snowflake
cmake --build engine/build-break-net-contract --target test_break_net_adapter -j2
```

Expected: configuration or compilation failure because the adapter header/implementation is not present. Do not treat a missing Snowflake dependency as a passing result.

- [x] **Step 4: Keep the failing test source buildable once the adapter target is added**

Use only C11 headers and the opaque adapter API. Do not include Snowflake headers in the test.

---

## Task 2: Add the C11 public contract and message types

**Files:**
- Create: `engine/src/network/break_net_adapter.h`
- Create: `engine/src/network/break_net_message.h`
- Create: `engine/src/network/break_net_protocol.h`
- Test: `engine/tests/test_break_net_adapter.c`

**Interfaces:**
- Consumes: Task 1 test names.
- Produces: `BreakNetReactor`, `BreakNetDriveMode`, `BreakNetReactorConfig`, lifecycle functions, bounded message view and validation result types.

- [x] **Step 1: Define opaque handles and mode/config types**

Use the approved signatures:

```c
typedef struct BreakNetReactor BreakNetReactor;
typedef struct BreakNetConnection BreakNetConnection;

typedef enum BreakNetDriveMode {
    BREAK_NET_DRIVE_THREAD = 0,
    BREAK_NET_DRIVE_STEP = 1
} BreakNetDriveMode;

typedef struct BreakNetReactorConfig {
    BreakNetDriveMode drive_mode;
    int logical_index;
    uint32_t max_connections;
    int empty_connection_timeout_ms;
    uint32_t watchdog_interval_ms;
    uint32_t step_timeout_ms;
} BreakNetReactorConfig;
```

Include `extern "C"` guards only for C++ consumers; do not add C++ implementation code.

- [x] **Step 2: Define lifecycle functions and explicit status semantics**

Add:

```c
BreakNetReactor *break_net_reactor_create(const BreakNetReactorConfig *config);
void break_net_reactor_destroy(BreakNetReactor *reactor);
bool break_net_reactor_start(BreakNetReactor *reactor);
bool break_net_reactor_step(BreakNetReactor *reactor, int timeout_ms);
bool break_net_reactor_stop(BreakNetReactor *reactor, uint32_t timeout_ms);
bool break_net_reactor_is_ready(const BreakNetReactor *reactor);
```

Document that `step` and Snowflake run APIs are single-driver operations and that destroy requires a stopped reactor.

- [x] **Step 3: Define bounded message records without gameplay fields**

Define a message view with `message_id`, `protocol_version`, `sequence`, `data`, and `size`; define a configurable maximum payload and an owned message record for queue transfer. The view is borrowed and the owned record is released by Break.

- [x] **Step 4: Define protocol validation results**

Define a C enum distinguishing `OK`, `INVALID_LENGTH`, `UNSUPPORTED_VERSION`, `UNKNOWN_MESSAGE`, `INVALID_SEQUENCE`, and `OVER_LIMIT`. Keep validation independent of session and ECS.

- [x] **Step 5: Run header-only compile tests**

Run:

```bash
cmake --build engine/build-break-net-contract --target test_break_net_adapter -j2
```

Expected: failure moves from missing declarations to missing implementation symbols. This confirms the public contract is consumed by tests.

---

## Task 3: Wire Snowflake into CMake without a fallback

**Files:**
- Modify: `engine/CMakeLists.txt`
- Modify: current test registration file
- Test: `engine/tests/test_break_net_adapter.c`

**Interfaces:**
- Consumes: public C11 headers from Task 2.
- Produces: `break_net` target linked to Snowflake C target or a documented imported target.

- [x] **Step 1: Inspect Snowflake exported target names**

Run:

```bash
grep -RInE 'add_library\(|install\(EXPORT|snow::|snowflake::' /home/timeshift/opensource/snowflake/src /home/timeshift/opensource/snowflake/CMakeLists.txt /home/timeshift/opensource/snowflake/cmake | head -160
```

Use the actual target name found in the source; do not invent a target.

- [x] **Step 2: Add a cache variable and fail-closed dependency check**

Add `SNOWFLAKE_SOURCE_DIR` as a CMake path option or use an existing repository convention. If the adapter is enabled and Snowflake is missing, configuration must fail with a message naming the required path. Do not build a hidden local socket implementation.

- [x] **Step 3: Add the `break_net` static target**

Include the three adapter source units and link the actual Snowflake target plus the existing Break core dependencies. Keep the target C11 and expose only Break include directories publicly.

- [x] **Step 4: Register the contract test**

Add `test_break_net_adapter` to CTest with the same timeout and label conventions as existing network tests.

- [x] **Step 5: Verify fail-closed and enabled configuration**

Run:

```bash
cmake -S engine -B /tmp/break-net-missing -DENGINE_BUILD_TESTS=ON -DBREAK_ENABLE_SNOWFLAKE=ON -DSNOWFLAKE_SOURCE_DIR=/does/not/exist
```

Expected: configuration fails with an explicit Snowflake dependency error.

Then configure with the real source directory and verify the target is generated.

---

## Task 4: Implement step-mode lifecycle with TDD

**Files:**
- Modify: `engine/src/network/break_net_adapter.c`
- Modify: `engine/src/network/break_net_message.c`
- Modify: `engine/tests/test_break_net_adapter.c`

**Interfaces:**
- Consumes: Snowflake `snow_net_thread_create`, `snow_net_thread_step`, `snow_net_thread_terminate`, readiness/inspection APIs found in the headers.
- Produces: deterministic `BREAK_NET_DRIVE_STEP` lifecycle.

- [x] **Step 1: Implement the minimal state machine**

Use explicit states: `CREATED`, `STARTED`, `STOPPING`, `STOPPED`, `FAILED`. Reject start from any state other than `CREATED`; make stop from `STOPPED` idempotent; do not destroy while `STARTED` or `STOPPING`.

- [x] **Step 2: Initialize Snowflake only after start**

Create/configure the Snowflake reactor in the adapter lifecycle according to the actual Snowflake API. Keep the Snowflake pointer private to the `.c` file.

- [x] **Step 3: Drive one step only from the caller**

`break_net_reactor_step` must check mode and state, call the Snowflake step API once, translate failure, and return without executing game logic.

- [x] **Step 4: Implement stop wake-up and cleanup**

In step mode, issue Snowflake terminate/close operations according to its documented lifecycle, drain owned Break queues, and transition to `STOPPED`.

- [x] **Step 5: Run focused tests**

Run:

```bash
cmake --build engine/build-break-net-contract --target test_break_net_adapter -j2
ctest --test-dir engine/build-break-net-contract -R break_net_adapter --output-on-failure
```

Expected: all step-mode lifecycle tests pass; thread-mode tests remain skipped or fail only at the not-yet-implemented thread-mode assertion.

---

## Task 5: Implement inbound/outbound queue ownership

**Files:**
- Modify: `engine/src/network/break_net_message.c`
- Modify: `engine/src/network/break_net_adapter.c`
- Modify: `engine/src/network/break_net_message.h`
- Modify: `engine/tests/test_break_net_adapter.c`

**Interfaces:**
- Consumes: existing Break queue/task conventions and Snowflake parser/send context APIs.
- Produces: bounded inbound event queue and outbound send command queue with explicit copy/transfer ownership.

- [x] **Step 1: Write ownership tests**

Test that an inbound payload remains valid after the Snowflake callback returns, that releasing it frees exactly once, that an outbound caller buffer may be changed immediately after submission, and that queue-full returns a distinct overload result.

- [x] **Step 2: Implement inbound owned-message allocation**

Copy only the bounded payload and envelope metadata during the Snowflake callback. Use the existing Break allocator/error conventions; reject over-limit allocations before allocating.

- [x] **Step 3: Implement GameThread polling**

Add an internal poll/drain function used by later GameThread integration. It must return owned messages in FIFO order and never call a gameplay handler from the reactor thread.

- [x] **Step 4: Implement outbound command ownership**

Copy payload data into an owned command or transfer an explicitly owned buffer. The reactor thread converts it to Snowflake's send context and releases the Break command only after conversion succeeds or fails.

- [x] **Step 5: Run queue tests under sanitizers where supported**

Run:

```bash
cmake -S engine -B engine/build-break-net-asan -DENGINE_BUILD_TESTS=ON -DBREAK_ENABLE_SNOWFLAKE=ON -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/snowflake -DENGINE_SANITIZE_ADDRESS=ON
cmake --build engine/build-break-net-asan --target test_break_net_adapter -j2
ctest --test-dir engine/build-break-net-asan -R break_net_adapter --output-on-failure
```

Expected: no leak, double free, or use-after-free report.

---

## Task 6: Implement envelope validation and connection events

**Files:**
- Modify: `engine/src/network/break_net_protocol.c`
- Modify: `engine/src/network/break_net_adapter.c`
- Modify: `engine/tests/test_break_net_adapter.c`

**Interfaces:**
- Consumes: protocol validation result types from Task 2 and Snowflake parser callback surface.
- Produces: a validated `BreakNetMessageView` and connection-open/close events for later Session Manager work.

- [x] **Step 1: Write table-driven protocol tests**

Cover minimum header, zero payload, exact maximum payload, one-byte-over-limit, unsupported version, unknown ID, duplicate sequence, backward sequence, and excessive sequence jump. Assert that rejected inputs do not enter the inbound queue.

- [x] **Step 2: Implement overflow-safe length checks**

Check every addition/multiplication before it is evaluated; reject malformed lengths without reading beyond the received buffer.

- [x] **Step 3: Implement version and sequence policy**

Keep per-connection sequence state in the adapter-owned connection context. Do not store it in Snowflake's connection object or expose it to callers.

- [x] **Step 4: Translate Snowflake connection events**

Convert accepted/closed/transport-error notifications to owned Break events. Do not assign gameplay session identity yet.

- [x] **Step 5: Run protocol tests; record fuzz boundary**

Run the focused CTest target and the existing packet fuzz/test target if available. The focused protocol and sanitizer cases pass; fuzz smoke targets were not run because they were not built in the recorded full lane, which remains a verification limitation rather than an adapter implementation gap.

---

## Task 7: Add dedicated host-thread mode

**Files:**
- Modify: `engine/src/network/break_net_adapter.c`
- Modify: `engine/tests/test_break_net_adapter.c`
- Inspect: `engine/src/core/platform_thread.h` and current task/thread lifecycle code

**Interfaces:**
- Consumes: Break platform thread API and Snowflake run/terminate APIs.
- Produces: production `BREAK_NET_DRIVE_THREAD` mode with deterministic shutdown.

- [x] **Step 1: Write thread-mode lifecycle tests**

Assert that start returns only after the host thread is created, ready becomes observable, stop wakes the run loop within the configured timeout, join completes, and destroy after join is safe.

- [x] **Step 2: Implement the host thread entry point**

The entry point calls exactly one Snowflake run/step loop, records readiness and terminal error atomically, and never touches GameThread-owned state.

- [x] **Step 3: Implement stop/join ordering**

Set the adapter stop flag, invoke Snowflake terminate through its supported cross-context path, wait for the host thread, then release Snowflake resources. On timeout, return failure and keep ownership explicit rather than freeing live reactor state.

- [x] **Step 4: Add race-focused tests**

Test concurrent stop requests, stop during startup, and send submission while stopping. Assert no deadlock and no use-after-free.

- [x] **Step 5: Run thread sanitizer where supported**

Run the adapter test under the repository's TSan configuration. Expected: no data race in lifecycle flags, readiness publication, queue ownership, or stop/join state.

---

## Task 8: Documentation and integration validation

**Files:**
- Create: `docs/design/snowflake_c11_adapter.md`
- Modify: `docs/Architecture_Overview.md`
- Modify: `docs/Implementation_Status.md`
- Test: all adapter and existing network tests

**Interfaces:**
- Consumes: final adapter headers and verified test behavior.
- Produces: implementation documentation and build/test evidence for later Session/Replication work.

- [x] **Step 1: Document the final public API**

Record exact signatures, ownership, thread restrictions, state transitions, Snowflake dependency, step/thread modes, shutdown order, status mapping, and forbidden callback behavior.

- [x] **Step 2: Add architecture diagrams**

Include Mermaid diagrams for reactor ownership, inbound path, outbound path, and shutdown/drain ordering. Keep diagrams consistent with the actual implementation and do not claim Snowflake creates the host thread.

- [x] **Step 3: Run the standard engine validation and record known failures**

Run:

```bash
cmake -S engine -B engine/build-break-net-final -DENGINE_BUILD_TESTS=ON -DBREAK_ENABLE_SNOWFLAKE=ON -DSNOWFLAKE_SOURCE_DIR=/home/timeshift/opensource/snowflake
cmake --build engine/build-break-net-final -j2
ctest --test-dir engine/build-break-net-final --output-on-failure
```

Focused adapter/Session lanes pass. The recorded full CTest run has known failures in unrelated `test_myui_text_layout` Hebrew boundary and `test_vulkan` golden drift, while five fuzz smoke targets were not built and therefore were not run; these remain explicit validation limits.

- [x] **Step 4: Run platform-specific validation available on the host**

Run Linux validation now. Keep Windows, macOS, iOS, Android, and Steam Deck commands documented for their native CI lanes; do not claim them verified on a Linux host.

- [x] **Step 5: Update project status**

Recorded the Snowflake source path, focused normal/ASan/TSan results, real loopback E2E scope, bounded-stop semantics, and known platform/feature limitations. Later subsystems remain explicitly unimplemented.

---

## Completion Gate

This plan is complete only when:

- The adapter builds as C11.
- Snowflake is the only transport implementation.
- Step mode and dedicated reactor-thread mode both pass lifecycle tests.
- Inbound and outbound ownership tests pass under sanitizers where supported.
- Protocol malformed-input tests pass.
- Stop/join/drain behavior is tested.
- Existing Break tests remain green.
- Documentation matches the actual passive Snowflake reactor contract.
- No ECS, Lua, editor, online-update, or security feature is falsely represented as complete.
