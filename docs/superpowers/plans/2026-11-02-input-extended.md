# Extended Input Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [x]`) syntax for tracking.

**Goal:** Deliver bounded multi-touch/gesture input and thread-safe gamepad haptic commands, wired through X11, Wayland, Win32, evdev, and XInput without changing `InputState` ABI.

**Architecture:** A versioned `InputExtended` sidecar lives beside each window's `InputState`. Touch events update fixed per-frame arrays on the platform thread; haptic producers only claim fixed command slots, and the platform thread executes them through a real or fake backend.

**Tech Stack:** C11, CTest, `test_framework.h`, XInput2, Wayland `wl_touch`, Win32 `WM_TOUCH`, Linux evdev force feedback, Windows XInput, ASan/UBSan/TSan.

## Global Constraints

- Follow P7 and sections 4, 6, and 8 of `docs/superpowers/specs/2026-11-02-cry-capability-completion-design.md`.
- Do not change `InputState` layout, push, open a PR, edit `docs/Implementation_Status.md`, or modify unrelated modules.
- Use hard capacities 16 touches, 32 touch events, 16 gestures, 32 haptic commands, drain budget 8, and duration <=5000 ms. Overflow is returned and counted, never silently truncated.
- No hot-path allocation. No OS device call while holding the haptic lock or from a producer thread.
- Write and observe each focused test fail before its implementation. Build with `-j3`; keep all existing Windows test registration and strict warnings.
- Physical-device and unavailable native Windows validation must remain explicit limitations.

---

### Task 1: Touch state, events, and gestures

**Files:**
- Create: `engine/src/platform/input_extended.h`
- Create: `engine/src/platform/input_extended.c`
- Create: `engine/tests/test_input_extended.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**

```c
typedef u64 InputTouchId;
typedef enum { INPUT_TOUCH_PRESS, INPUT_TOUCH_MOVE, INPUT_TOUCH_RELEASE,
               INPUT_TOUCH_CANCEL, INPUT_TOUCH_HELD } InputTouchPhase;
InputExtResult input_extended_touch(InputExtended *, InputTouchPhase, i64 source_id,
                                 f32 x, f32 y, u64 time_ms, InputTouchId *);
InputExtResult input_extended_touch_pixels(InputExtended *, InputTouchPhase,
                                        i64, f32, f32, u32, u32, u64, InputTouchId *);
InputExtResult input_extended_touch_end(InputExtended *, i64 source_id,
                                     bool cancel, u64 time_ms);
InputExtResult input_extended_cancel_all(InputExtended *, u64 time_ms);
void input_extended_new_frame(InputExtended *);
void input_extended_update(InputExtended *, u64 time_ms);
```

- [x] **Step 1: Write failing touch/gesture tests**

Use literal timestamps and coordinates. Include one test per production break: lost release/cancel deactivation, missing generation increment, accepting NaN/out-of-window input, exceeding 16 touches or 32 events, stale move, tap/long-press/swipe thresholds, two-touch scale/rotation, and gesture overflow. For example:

```c
InputTouchId first, second;
ASSERT_EQ(input_extended_touch(&s, INPUT_TOUCH_PRESS, 7, .2f, .3f, 10, &first), INPUT_EXT_OK);
ASSERT_EQ(input_extended_touch_end(&s, 7, false, 20), INPUT_EXT_OK);
ASSERT_EQ(input_extended_touch(&s, INPUT_TOUCH_PRESS, 7, .4f, .5f, 30, &second), INPUT_EXT_OK);
ASSERT_NEQ(first, second);
ASSERT_EQ(s.touch_events[1].id, first);
ASSERT_EQ(s.touch_events[2].id, second);
```

- [x] **Step 2: Verify RED**

Run: `cc -std=c11 -Iengine/src -Iengine/tests -Iengine/external engine/tests/test_input_extended.c engine/src/platform/input_extended.c -lm -o build-input-red/test_input_extended`
Expected: failure because the new sidecar API/implementation is absent. After a header exists, every new behavior must also have a runtime mutation failure rather than relying on this compile failure as the only evidence.

- [x] **Step 3: Implement minimal bounded touch/gesture state**

Implement fixed arrays, slot/generation handles, event recording, per-frame transitions, terminal cancellation, coordinate validation, and the four gesture families from `docs/design/input_extended.md`. Do not add allocation or platform dependencies.

- [x] **Step 4: Verify GREEN**

Run: `cmake -S engine -B build-input-normal -DENGINE_RHI_BACKEND=opengl -DBREAK_ENABLE_CRYPTO=OFF -DBREAK_ENABLE_CRASH=OFF && cmake --build build-input-normal -j3 --target test_input_extended test_input && ctest --test-dir build-input-normal --output-on-failure -R '^(test_input_extended|test_input)$'`
Expected: all focused tests pass with `-Werror` enabled.

### Task 2: Haptic command queue and fake device

**Files:**
- Modify: `engine/src/platform/input_extended.h`
- Modify: `engine/src/platform/input_extended.c`
- Modify: `engine/tests/test_input_extended.c`

**Interfaces:**

```c
InputExtResult input_extended_request_haptic(InputExtended *, u32 pad,
                                          f32 low, f32 high, u32 duration_ms,
                                          u64 *out_request_id);
InputExtResult input_extended_haptic_result(InputExtended *, u64 request_id);
InputExtResult input_extended_haptic_pump(InputExtended *, InputHapticExecuteFn,
                                       void *context);
void input_extended_backend_pad(InputExtended *, u32 pad, bool connected,
                                bool feedback, u32 connection_serial);
```

- [x] **Step 1: Add failing fake-device and capacity tests**

Test invalid strengths/duration, disconnected/no-feedback requests, 32 accepted commands followed by overload, pending disconnect, stale generation after reconnect, exact motor/duration delivery, executor failure, and result retrieval freeing a slot. Add four native test threads (Win32 or pthread) producing 64 requests each while the main thread pumps a deterministic fake; assert 256 real executor calls and 256 successful results.

- [x] **Step 2: Verify RED**

Run the Task 1 focused binary before haptic implementation. Expected: compile failure for the new haptic API, followed later by behavioral disconnect/capacity mutation failures.

- [x] **Step 3: Implement command/result slots**

Use an atomic-flag lock around POD fields only. Capture pad generation on submit, limit each pump to 8 calls, never execute under the lock, and retain final status until result retrieval.

- [x] **Step 4: Verify normal and thread sanitizer GREEN**

Run the Task 1 command, then configure `build-input-tsan` with `-DENGINE_USE_TSAN=ON` and run `test_input_extended`. Expected: all tests pass and TSan reports no races.

### Task 3: Real Linux and Windows feedback backends

**Files:**
- Modify: `engine/src/platform/gamepad_linux.h`
- Modify: `engine/src/platform/gamepad_linux.c`
- Modify: `engine/src/platform/gamepad_win.c`
- Modify: `engine/tests/test_input_extended.c`

**Interfaces:**

```c
void gamepad_feedback_poll(InputExtended *extended);
```

- [x] **Step 1: Add backend-contract RED checks**

Use the fake executor to pin the shared statuses and exact strength conversion inputs. Add compile-time backend coverage to the normal X11/Wayland and available Windows builds. Do not remove or bypass `test_platform_win32_runtime`.

- [x] **Step 2: Implement evdev feedback**

Probe writable FF_RUMBLE support, retain ordinary read-only fallback, execute upload/start/stop only in `gamepad_feedback_poll`, and clean up effects on disconnect.

- [x] **Step 3: Implement XInput feedback**

Load SetState/GetCapabilities dynamically, track connection serials and feedback flags, map disconnected/unsupported/failure, and execute only during feedback polling.

- [x] **Step 4: Verify real backend compilation and focused behavior**

Run X11 and Wayland `engine` builds with `-j3`; run `test_input_extended`. Build the Windows target when a Windows toolchain exists, otherwise record that native Windows compile/runtime is unavailable. No hardware claim is allowed.

### Task 4: Platform sidecar and native touch wiring

**Files:**
- Modify: `engine/src/platform/platform.h`
- Modify: `engine/src/platform/window_x11.c`
- Modify: `engine/src/platform/window_wayland.c`
- Modify: `engine/src/platform/window_win32.c`
- Modify: `engine/src/platform/window_cocoa.m`
- Modify: `engine/src/platform/window_mobile.c`
- Modify: `engine/src/platform/window_screen.c`
- Modify: `engine/tests/test_platform_x11_runtime.c`
- Modify: `engine/tests/test_platform_win32_runtime.c`
- Modify: `engine/CMakeLists.txt`

**Interfaces:**

```c
InputExtended *platform_input_extended(Platform *);
```

- [x] **Step 1: Add platform access RED tests**

In X11 and Win32 runtime tests, create the real window and assert `platform_input_extended(platform)` is nonnull, version 1, and initially empty. Keep the tests registered on their native platforms. Compile first to observe the missing API failure.

- [x] **Step 2: Add sidecar lifecycle everywhere**

Own and initialize the sidecar in every backend, advance it with `input_new_frame`, and expose the same getter. Update direct-source mobile/Screen test targets with `input_extended.c` so no platform loses symbols.

- [x] **Step 3: Wire native events**

Select XI2 touch events, add the complete `wl_touch_listener`, and register/process `WM_TOUCH` as specified in the design. Cancel on focus/capability/seat loss and update gestures from `time_microseconds()/1000`. Call `gamepad_feedback_poll` after ordinary gamepad polling.

- [x] **Step 4: Verify platform GREEN**

Run normal X11 focused tests and build the Wayland engine. Run native runtime tests only when a display exists; preserve return code 77 semantics for no display. Compile/run Win32 tests on Windows when available and otherwise report the missing lane honestly.

### Task 5: Mutation, review, and delivery

**Files:**
- Create: `.superpowers/sdd/input-extended-report.md`

- [x] **Step 1: Run sanitizer and regression matrix**

Run focused normal, ASan+UBSan, and TSan tests, all with `-j3`. Include existing `test_input` and direct-source platform tests affected by the new sidecar.

- [x] **Step 2: Prove five behavioral mutations fail**

In separate build-tree copies, independently break cancel deactivation, id generation, coordinate range validation, disconnect completion, and haptic full-queue rejection. Compile/run the real test suite against each copy and require failure. Restore nothing in the source tree because only copies are mutated.

- [x] **Step 3: Perform read-only review and fix findings**

Review the complete diff for lifetime, races, ABI, queue semantics, native event cleanup, and Windows compilation. Fix every Critical/Important finding with a new RED regression test, then rerun affected lanes.

- [x] **Step 4: Write evidence report and commit**

Record exact commands/results, RED/GREEN and mutation evidence, unavailable hardware/Windows lanes, and review findings. Run `git diff --check`, inspect `git status`, and commit only P7 files on `cry-wave2-input`; do not push or create a PR.
