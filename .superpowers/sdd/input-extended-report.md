# P7 Extended Input Delivery Report

Status: DONE, with the platform/runtime limitations listed below.

Branch: `cry-wave2-input` (local commit only; no push or PR).

## Delivered

- Added versioned `InputExtended` sidecars without changing `engine/src/platform/input.h` or `InputState` layout.
- Added bounded press/move/release/cancel touch events, 16 active points, 32 frame events, stable slot+generation ids, same-frame OS-id reuse, normalized coordinates, and explicit overflow/drop reporting.
- Added deterministic tap, long-press, swipe, and two-touch pinch/rotation gestures with bounded event storage.
- Added 32-slot haptic command/result protocol, request ids and pad generations, 8-command drain budget, range validation, disconnect/no-feedback degradation, and stale-result rejection after reconnect. A nonnull request-id output is required so accepted commands cannot become unrecoverable permanent slots.
- Added thread-safe producers using a C11 atomic-flag lock. Producers only queue POD commands; the platform polling thread executes device callbacks outside the lock. No hot-path allocation was added.
- Added real evdev `FF_RUMBLE` upload/start/stop with writable/read-only and non-FF fallback, effect cleanup, and connection serials.
- Added real XInput SetState/GetCapabilities loading, motor commands, no-feedback/disconnect mapping, polling-thread duration expiry, and shutdown stop.
- Wired X11 XI2 touch events, Wayland `wl_touch`, and Win32 `WM_TOUCH` into the sidecar, including focus/hierarchy/seat/capability/capture cancellation. Cocoa/mobile/Screen expose the same sidecar lifecycle/getter without claiming new native touch or haptics.
- Added Linux and Windows fake-device suites and preserved the existing Win32 runtime test registration. No RHI source or default backend policy was changed.

## RED evidence observed

1. Initial touch test compile failed because `platform/input_extended.h` and `input_extended.c` did not exist.
2. Haptic test compile failed because command/status/result APIs and constants were absent.
3. evdev fake test compile failed because `feedback_available`, `effect_id`, and `linux_device_haptic` were absent.
4. X11 runtime test compile failed because `platform_input_extended` and the sidecar version API were absent.
5. A runtime RED for null haptic request-id output returned success instead of `INPUT_EXT_INVALID`; the implementation was then fixed and the test passed.
6. The first concurrent test attempt also exposed a test protocol deadlock: completed results were not retrieved until all producers exited. The fixture was corrected so producers retrieve their own results while the main thread alone executes the fake device; the real queue then passed normal and TSan tests.

The XInput duration test was written before its implementation but was not executed as a separate pre-fix binary. It is compiled in the Windows lane, not claimed as independently observed runtime RED.

## GREEN and regression evidence

All builds used `-j3`.

- Normal focused: 9/9 tests passed (`test_input`, `test_input_extended`, `test_gamepad_linux_feedback`, Screen/mobile direct-source tests, and mobile host).
- ASan+UBSan focused: the same 9/9 passed with `detect_leaks=1`, `halt_on_error=1`, and UBSan stack traces enabled; no sanitizer findings.
- TSan focused: the same 9/9 passed with `halt_on_error=1`; no race findings. The haptic test includes 4 producers x 64 commands with 256 real fake executions/results.
- Wayland: real engine build passed; native `test_platform_wayland_runtime` passed 6/6.
- X11: real engine and runtime test built. The new sidecar/window test passed. The full runtime suite still reports pre-existing fullscreen failures on the current display/WM; a clean `git archive HEAD` baseline built at `build-input-x11-baseline/build` fails in the same fullscreen area. No fullscreen code was changed or suppressed.
- Win32 cross compilation: `zig cc -target x86_64-windows-gnu` successfully built the Windows engine, `test_input_extended.exe`, `test_gamepad_win_feedback.exe`, and `test_platform_win32_runtime.exe`. `file` identifies all three as x86-64 PE32+ Windows executables.
- Static review: Clang analyzer completed on `input_extended.c` and `gamepad_linux.c` without diagnostics. `git diff --check` passed.
- `docs/Implementation_Status.md` and `engine/src/platform/input.h` are unchanged.

## Mutation evidence

`build-input-mutations/run_mutations.py` created independent build-tree copies of the production sidecar, compiled each with strict warnings, and ran the real focused suite. Every mutation failed in its intended test:

- cancel deactivation broken -> `cancel_deactivates_without_completion_gesture` failed;
- id generation increment removed -> same-frame id reuse test failed;
- normalized coordinate range check removed -> range transaction test failed;
- disconnect completion removed -> pending disconnect test failed;
- full haptic queue rejection removed -> capacity/result reuse test failed.

No mutated source was added to the commit.

## Review findings addressed

- Required request-id output to prevent unrecoverable completed-result slots.
- Added XInput duration expiry and shutdown motor stop instead of ignoring duration.
- Limited `WM_CAPTURECHANGED` cancellation to touches; it no longer releases unrelated held keys.
- Removed nonportable `XI_TouchCancel`; X11 uses focus and hierarchy cancellation instead.
- Completed Wayland touch teardown on capability removal, seat removal, create failure, and normal destroy.

No unresolved Critical/Important finding remains from the final read-only self-review.

## Limitations / unverified

- No physical touchscreen or force-feedback controller was available. Real hardware delivery, vibration feel, and OS-specific touch hardware behavior remain unverified.
- Windows source and tests were genuinely cross-compiled, but no Windows runtime/Wine was available. The PE test executables, including the XInput fake suite and Win32 runtime suite, were not executed.
- The current X11 display/WM prevents a clean full-runtime pass in both baseline and modified trees; only the P7-related X11 assertions and compilation are evidenced here.
- Cocoa and real mobile native builds were not run. Their existing direct-source/simulated tests passed; no new native touch or haptic support is claimed for them.

## Fix round 1 — review findings

Status: DONE. All five Important findings and both Minor findings are addressed in production code and direct native-handler tests.

### Fixes

- XI2 and WM_TOUCH up events now use last valid coordinates through `input_extended_touch_end`, so out-of-window and negative up positions always release.
- XI2 source identity combines `sourceid` and `detail`; two devices can share a detail value without colliding.
- XI2 and Wayland events use dispatch-time `time_microseconds()/1000` for down/move/up and gesture updates. Wrapping OS u32 timestamps are not mixed with the local monotonic epoch.
- Oversize WM_TOUCH batches, query failure, and origin conversion failure cancel all active touches; oversize retains its overload count and every path closes the native handle.
- The Windows fake disconnect assertion uses `&id`; a separate NULL assertion requires `INPUT_EXT_INVALID`.
- `test_gamepad_win_feedback_portable` executes the real `gamepad_win.c` on non-Windows hosts with a complete fake native ABI and deterministic clock. The portable XInput suite, not just a PE compile, passes 4/4.
- Production handlers `x11_touch_event`, `wayland_touch_down/motion/up`, and `win32_touch_message` receive direct native fixtures for down/move/up/cancel, out-of-window positions, same-frame id reuse, device id collisions, rejected batches, and time-wrap cases. The real X11/Wayland/Win32 event loops call these same handlers.

### RED observed

The portable XInput target first failed at `test_gamepad_win_feedback.c:78`: NULL output was expected to return disconnected but the API correctly returned `INPUT_EXT_INVALID`. After splitting the assertions, the same target passed 4/4.

The three native test groups were also compiled before their handlers existed and failed respectively on missing `platform/x11_touch.h`, `platform/wayland_touch.h`, and `platform/win32_touch.h`. After implementation, XI2 passed 5/5, Wayland 4/4, and WM_TOUCH 4/4. The mutations below additionally prove the tests fail on the reviewed old behaviors.

### Exact GREEN commands and results

Normal build and test:

```bash
cmake --build build-input-normal -j3 --target test_input test_input_extended test_gamepad_linux_feedback test_gamepad_win_feedback_portable test_x11_touch test_wayland_touch test_win32_touch test_platform_screen_simulated test_platform_mobile_layer_ios test_platform_mobile_layer_android test_platform_mobile_layer_harmonyos test_platform_mobile_layer_qnx test_engine_mobile_host
ctest --test-dir build-input-normal --output-on-failure --timeout 60 -R '^(test_input|test_input_extended|test_gamepad_linux_feedback|test_gamepad_win_feedback_portable|test_x11_touch|test_wayland_touch|test_win32_touch|test_platform_screen_simulated|test_platform_mobile_layer_(ios|android|harmonyos|qnx)|test_engine_mobile_host)$'
```

Result: 13/13 CTest targets passed, including portable XInput 4/4, XI2 5/5, Wayland 4/4, and WM_TOUCH 4/4.

ASan+UBSan build used the same target list with `ENGINE_USE_ASAN=ON` and `ENGINE_USE_UBSAN=ON`, then:

```bash
ASAN_OPTIONS=detect_leaks=1:halt_on_error=1 UBSAN_OPTIONS=halt_on_error=1:print_stacktrace=1 ctest --test-dir build-input-asan --output-on-failure --timeout 90 -R '^(test_input|test_input_extended|test_gamepad_linux_feedback|test_gamepad_win_feedback_portable|test_x11_touch|test_wayland_touch|test_win32_touch|test_platform_screen_simulated|test_platform_mobile_layer_(ios|android|harmonyos|qnx)|test_engine_mobile_host)$'
```

Result: 13/13 passed; no ASan, leak, or UBSan findings.

TSan build used the same target list with `ENGINE_USE_TSAN=ON`, then:

```bash
TSAN_OPTIONS=halt_on_error=1 ctest --test-dir build-input-tsan --output-on-failure --timeout 90 -R '^(test_input|test_input_extended|test_gamepad_linux_feedback|test_gamepad_win_feedback_portable|test_x11_touch|test_wayland_touch|test_win32_touch|test_platform_screen_simulated|test_platform_mobile_layer_(ios|android|harmonyos|qnx)|test_engine_mobile_host)$'
```

Result: 13/13 passed; no race findings.

Native Wayland:

```bash
cmake --build build-input-wayland -j3 --target engine test_platform_wayland_runtime test_wayland_touch
ctest --test-dir build-input-wayland --output-on-failure --timeout 60 -R '^(test_wayland_touch|test_platform_wayland_runtime)$'
```

Result: both CTest targets passed; the native Wayland runtime itself passed 6/6.

Native Win32 cross build:

```bash
cmake --build build-input-win32 -j3 --target test_input_extended test_gamepad_win_feedback test_platform_win32_runtime test_win32_touch
file build-input-win32/test_win32_touch.exe
```

Result: all four targets built; `test_win32_touch.exe` is an x86-64 PE32+ Windows executable. No Windows runtime was available to execute it.

X11 native runtime command:

```bash
cmake --build build-input-normal -j3 --target engine test_platform_x11_runtime
ctest --test-dir build-input-normal --output-on-failure --timeout 60 -R '^test_platform_x11_runtime$'
```

Result: the window/sidecar test passed, but the CTest target remains red in pre-existing fullscreen assertions on the current display/WM. The clean baseline runtime also fails there. No fullscreen test or assertion was skipped or weakened.

Static checks:

```bash
clang --analyze -std=c11 -DENGINE_X11_XINPUT2=1 -Iengine/src -Xanalyzer -analyzer-output=text engine/src/platform/x11_touch.c -o /dev/null
clang --analyze -std=c11 -Iengine/src -Xanalyzer -analyzer-output=text engine/src/platform/wayland_touch.c -o /dev/null
clang --analyze -std=c11 -Iengine/src -Iengine/tests/fake_windows -Xanalyzer -analyzer-output=text engine/src/platform/win32_touch.c -o /dev/null
git diff --check
```

Result: all completed without diagnostics/errors.

### Round 1 mutation evidence

```bash
python3 build-input-mutations/run_mutations.py
python3 build-input-mutations/run_fix_round1.py
```

The original five mutations still failed in their intended tests. Six new build-tree mutations also compiled and failed behaviorally: XI2 out-of-window UP, XI2 detail-only identity, XI2 OS-time mixing, Wayland OS-time mixing, Win32 out-of-window UP, and Win32 rejected-batch no-cancel. No mutated source is committed.

### Round 1 limitations

Physical touch/haptic hardware and native Windows execution remain unverified. The portable suites execute real production handlers/backends with native-layout fakes; they are not presented as physical-device or native Windows runtime evidence.
