# Framework Runtime Bus Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

**Goal:** Deliver an opt-in C++20 application class that owns a bounded subscription and dispatches validated IO completion notices on its `Tick()` thread without changing the default application.

**Architecture:** `RuntimeBusApplication` derives from `BaseApplication` in a separate `common_runtime` static library. The application borrows a bus, owns its queue and subscriber id, and leaves process-wide IO and bus ownership with the caller. Root build integration remains default-off; engine tests consume the formal production library.

**Tech Stack:** C11 runtime C API, C++20 framework, CMake 3.25+, CTest, existing `runtime_core` bounded bus/queue/message/IO notice APIs.

## Global Constraints

- Default Vulkan; OpenGL remains the final fallback and image comparison backend. Linux uses native Wayland only.
- Engine stays C11; framework and its tests compile as C++20. Public C calls retain their C ABI.
- Do not change `BaseApplication`, `ApplicationInterface`, `empty/empty_application.cc`, or default `empty` behavior.
- Use repository naming and Google style; no new compatibility-prefixed identifiers, retired domain vocabulary, or role labels.
- `common_runtime` is opt-in. `engine`, existing demos, and default `empty` must not link it.
- Preserve existing documents by appending new dated sections; do not rewrite historical records.
- Do not create a PR. Commit locally during implementation and push `master` only after final validation.
- Design: `docs/superpowers/specs/2026-11-22-framework-runtime-bus-design.md`.

## File Structure

- Create `framework/common/runtime_bus_application.h`: public derived application API and value-type statistics.
- Create `framework/common/runtime_bus_application.cc`: subscription lifecycle, nonblocking drain, typed dispatch.
- Modify `framework/common/CMakeLists.txt`: preserve `common`; define `common_runtime` only when runtime dependencies exist.
- Modify `CMakeLists.txt`: default-off runtime option and root contract test registration.
- Modify `engine/CMakeLists.txt`: include framework sources for engine tests and register the C++20 behavior test.
- Create `engine/tests/test_framework_runtime_bus.cpp`: real production-library behavior and ABI tests.
- Create `framework/common/test_runtime_build_contract.cmake`: configure/build default and opt-in root trees and assert target availability.
- Append `docs/design/runtime_message_model.md`, `docs/cross_engine/missing_capabilities.md`, `docs/Implementation_Status.md`, and `docs/Build_Guide.md` after implementation.

---

### Task 1: Optional application bridge and behavior tests

**Files:**
- Create: `framework/common/runtime_bus_application.h`
- Create: `framework/common/runtime_bus_application.cc`
- Modify: `framework/common/CMakeLists.txt`
- Modify: `engine/CMakeLists.txt`
- Test: `engine/tests/test_framework_runtime_bus.cpp`

**Interfaces:**
- Consumes: `break_runtime_bus_subscribe`, `break_runtime_bus_unsubscribe`, `break_runtime_queue_create`, `break_runtime_queue_poll`, `break_runtime_queue_destroy`, `break_runtime_io_notice_view`, `break_runtime_message_release`.
- Produces:

```cpp
namespace bk {
struct RuntimeBusApplicationStats {
  std::uint64_t io_notices{0};
  std::uint64_t malformed_notices{0};
};

class RuntimeBusApplication : public BaseApplication {
 public:
  ~RuntimeBusApplication() override;
  BreakRuntimeError AttachRuntimeBus(BreakRuntimeBus* bus);
  void DetachRuntimeBus();
  int Init() override;
  void DeInit() override;
  void Tick() override;
  RuntimeBusApplicationStats runtime_bus_stats() const;

 protected:
  virtual void OnRuntimeIoNotice(const BreakRuntimeIoNotice& notice);
};
}
```

- [ ] **Step 1: Write the failing C++20 tests**

Create a small test runner with named functions and a `CHECK` macro. Use a `RecordingApplication` subclass that copies each notice into `std::vector<BreakRuntimeIoNotice>` and records `std::this_thread::get_id()`. Test these separately:

```cpp
bool default_lifecycle_is_unchanged();
bool attachment_and_initialization_reject_invalid_transitions();
bool missing_kind_and_full_subscriber_table_allow_retry();
bool valid_notices_dispatch_in_order_on_the_tick_thread();
bool malformed_notices_are_counted_and_released();
bool detach_deinit_and_destructor_unsubscribe();
bool a_full_queue_reports_drops_without_blocking();
bool production_io_attachment_and_parser_link_from_cpp20();
bool concurrent_publish_and_tick_are_race_free();
```

Publish exact 24-byte little-endian payloads through `break_runtime_bus_publish`. Use `break_runtime_io_attach_bus(bus)` for the production kind setup and detach the global IO bus before destroying it. For a wrong version, create a test kind with the same numeric kind and `max_version=2`; for wrong kind parsing, call `break_runtime_io_notice_view` directly because a correctly subscribed bus cannot deliver another kind. Include wrong size and null payload cases. For subscriber-table retry, fill all 32 subscriptions, verify `BREAK_RUNTIME_OVERLOAD`, unsubscribe and destroy one queue, then call `Init()` again and require success.

Add the test target after `runtime_core_test` is defined. Link `common_runtime`, `Threads::Threads`, and the platform-required math/system libraries already used by `test_core_app_voice`. Set `CXX_STANDARD 20` and `CXX_STANDARD_REQUIRED ON`. Add a `headless;runtime_core;framework` CTest label.

- [ ] **Step 2: Verify RED**

Run:

```bash
cmake -S engine -B build-framework-runtime-vk \
  -DENGINE_RHI_BACKEND=vulkan -DMYUI_PAL=dummy \
  -DENGINE_BUILD_TESTS=ON -DCMAKE_BUILD_TYPE=Debug
cmake --build build-framework-runtime-vk --target test_framework_runtime_bus -j2
```

Expected: compilation fails because `runtime_bus_application.h` or its API does not exist. Do not add implementation before recording this failure.

- [ ] **Step 3: Implement the minimal lifecycle and dispatch**

Use these invariants:

```cpp
BreakRuntimeError RuntimeBusApplication::AttachRuntimeBus(BreakRuntimeBus* bus) {
  if (!bus) return BREAK_RUNTIME_INVALID;
  if (initialized_ || runtime_bus_) return BREAK_RUNTIME_REJECTED;
  runtime_bus_ = bus;
  return BREAK_RUNTIME_OK;
}
```

`Init()` rejects a duplicate call, resets statistics for a new attempt, calls the base implementation, then creates `{64u, 16u}` queue configuration and subscribes with name `framework.application.io`. On any failure, unsubscribe if needed, destroy the queue, clear subscriber state, restore `initialized_=false`, call base `DeInit()`, and return the original error. Keep `runtime_bus_` for retry.

`Tick()` calls the base entry and polls until empty or closed. Hold each owned message with `std::unique_ptr<BreakRuntimeOwnedMessage, void (*)(BreakRuntimeOwnedMessage*)>` so every exit releases it. Valid notices increment `io_notices` before `OnRuntimeIoNotice`; parse failures increment only `malformed_notices`.

`DetachRuntimeBus()` unsubscribes before destroying the queue and clears the borrowed bus last. `DeInit()` calls detach, marks uninitialized, and invokes base cleanup. The destructor calls `DeInit()`. Do not allocate a thread, call global IO attach/shutdown, or add catch-all message dispatch.

- [ ] **Step 4: Verify GREEN and existing runtime regressions**

```bash
cmake --build build-framework-runtime-vk --target test_framework_runtime_bus test_runtime_bus test_runtime_io -j2
ctest --test-dir build-framework-runtime-vk --output-on-failure \
  -R '^(test_framework_runtime_bus|test_runtime_bus|test_runtime_io)$'
```

Expected: all selected tests pass with no sanitizer diagnostics or warnings introduced by the new target.

- [ ] **Step 5: Main-thread commit after review**

```bash
git add framework/common/runtime_bus_application.h \
  framework/common/runtime_bus_application.cc framework/common/CMakeLists.txt \
  engine/CMakeLists.txt engine/tests/test_framework_runtime_bus.cpp
git commit -m "feat(framework): consume runtime IO notices"
```

### Task 2: Root build option and dependency isolation contract

**Files:**
- Modify: `CMakeLists.txt`
- Test: `framework/common/test_runtime_build_contract.cmake`

**Interfaces:**
- Consumes: `common_runtime` from Task 1 only for the enabled build; the default test is independent.
- Produces: cache option `BREAK_FRAMEWORK_ENABLE_RUNTIME=OFF`; root CTest `test_framework_runtime_build_contract`.

- [ ] **Step 1: Write the failing build contract**

The CMake script receives `SOURCE_DIR` and `BINARY_DIR`. It configures a fresh default tree with `BREAK_FRAMEWORK_ENABLE_RUNTIME=OFF` and `BUILD_TESTING=OFF`, builds `empty`, then attempts target `common_runtime` and requires that target to be absent. It configures a second tree with `BREAK_FRAMEWORK_ENABLE_RUNTIME=ON`, `ENGINE_BUILD_TESTS=OFF`, and `BUILD_TESTING=OFF`, and requires `common_runtime` to build. It also checks `empty` still builds in the enabled tree without being relinked to the bridge.

- [ ] **Step 2: Verify default isolation before integration and enabled RED**

```bash
cmake -S . -B build-framework-contract
ctest --test-dir build-framework-contract --output-on-failure \
  -R '^test_framework_runtime_build_contract$'
```

Expected: the default section passes; the enabled section fails because the runtime option or `common_runtime` is absent. Do not treat an expected disabled-target absence as a test failure.

- [ ] **Step 3: Add minimal root integration**

Declare `option(BREAK_FRAMEWORK_ENABLE_RUNTIME "Enable the optional C++ runtime bus bridge" OFF)` before adding framework sources. When enabled, default `ENGINE_BUILD_TESTS` to `OFF` only if the caller has not defined it, then `add_subdirectory(engine)`. Include CTest and register the contract with source/binary paths and a `framework;platform_contract` label. Keep `add_subdirectory(empty)` unchanged.

- [ ] **Step 4: Verify both root paths**

```bash
cmake -S . -B build-framework-default -DBUILD_TESTING=OFF
cmake --build build-framework-default --target empty -j2
cmake -S . -B build-framework-runtime -DBUILD_TESTING=OFF \
  -DBREAK_FRAMEWORK_ENABLE_RUNTIME=ON -DENGINE_BUILD_TESTS=OFF \
  -DENGINE_RHI_BACKEND=vulkan -DMYUI_PAL=dummy
cmake --build build-framework-runtime --target common_runtime empty -j2
ctest --test-dir build-framework-contract --output-on-failure \
  -R '^test_framework_runtime_build_contract$'
```

Expected: default and enabled builds succeed; the bridge target exists only in the enabled tree; `empty` remains unchanged.

- [ ] **Step 5: Main-thread commit after review**

```bash
git add CMakeLists.txt framework/common/test_runtime_build_contract.cmake
git commit -m "build(framework): add opt-in runtime bridge"
```

### Task 3: Documentation and independent review

**Files:**
- Append: `docs/design/runtime_message_model.md`
- Append: `docs/cross_engine/missing_capabilities.md`
- Append: `docs/Implementation_Status.md`
- Append: `docs/Build_Guide.md`

- [ ] **Step 1: Add a build and usage example**

Show an `ApplicationInterface` entry point using a `RuntimeBusApplication` subclass, `break_runtime_io_attach_bus` before `Init()`, owner-thread `Tick()`, application `DeInit()`, IO shutdown/detach, then bus destruction. State that full applications stop IO producers before destroying the bus and that the class itself does not own that global sequence.

- [ ] **Step 2: Append exact implementation evidence**

Record the queue capacity, borrowed/owned handles, failure retry, typed callback thread, malformed counters, target names, test count, C++20 standard correction, and unchanged default dependency boundary. Replace no historical statement; add a dated final paragraph explaining which older “not implemented” statement this batch resolves.

- [ ] **Step 3: Request independent read-only review**

Provide the design, plan, and exact diff. Require inspection of all early returns, bus/queue destruction ordering, callback/message lifetime, CMake static link order, and tests that could pass vacuously. Address every confirmed finding through a new RED/GREEN cycle.

### Task 4: Verification and remote delivery

- [ ] **Step 1: Run focused normal, ASan/UBSan, and TSan lanes**

Build the same `test_framework_runtime_bus` production target in each tree. Include `test_runtime_bus`, `test_runtime_io`, `test_runtime_core`, and `test_public_api_cpp20`; run the framework root contract and default `empty` executable with a bounded timeout. TSan must include a producer thread publishing while the owner drains, followed by synchronized detach.

- [ ] **Step 2: Run full local regression**

Run the complete Vulkan and OpenGL CTest suites, ASan/UBSan nongraphics suite, all registered fuzz smoke tests, and relevant TSan tests using the established build-tree settings. Use `git diff --check` and inspect the final diff. Record exact totals and conditional skips; never classify an unrun lane as passed.

- [ ] **Step 3: Review, commit, synchronize, and push**

```bash
git status --short --branch
git log --oneline origin/master..HEAD
git fetch origin
git rebase origin/master
# Re-run affected tests if rebase changes any file.
git push origin HEAD:master
```

Resolve every conflict without dropping either side's still-valid requirements. Do not push if any required test is red or unreviewed.

- [ ] **Step 4: Verify remote workflows and append receipts**

Verify CI, native Windows D3D12, and Proton D3D12 workflows for the pushed commit; run the macOS lane through the established credentialed path without exposing environment-secret values. Append run identifiers and outcomes to `docs/Implementation_Status.md`, commit and push that documentation update, then verify its workflows and clean `HEAD == origin/master` state.
