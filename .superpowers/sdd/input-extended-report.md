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
