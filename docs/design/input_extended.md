# Extended Input: Touch, Gestures, and Gamepad Feedback

Date: 2026-11-02

## Scope

This is the P7 implementation contract from `docs/superpowers/specs/2026-11-02-cry-capability-completion-design.md`. It adds bounded multi-touch input, common gestures, and gamepad haptic requests without changing the layout of `InputState`. Wayland and Win32 touch messages feed the same sidecar. Linux evdev and Windows XInput execute haptic commands on the platform polling thread. X11 support and its XInput2 backend were removed in 2.0.0; current behavior and pre-2.0.0 implementation evidence are documented separately below.

Cocoa, mobile, and QNX Screen expose the sidecar so the platform API remains linkable, but this change does not claim new native touch or haptic support on those backends. No physical touchscreen or force-feedback device is available for this implementation; hardware validation remains a separate requirement.

## Alternatives

1. **Versioned per-window sidecar (selected).** `Platform` owns an `InputExtended` next to `InputState`, and `platform_input_extended()` returns it. Existing input ABI and consumers remain unchanged. Fixed arrays provide predictable memory use and deterministic tests.
2. Append touch fields to `InputState`. This is smaller code but changes structure size and initialization/layout expectations, so it does not meet the ABI constraint.
3. A process-global input manager. It would simplify backend access but mix independent windows and make ownership, test isolation, and device-thread rules less clear. Rejected.

## Public model

`engine/src/platform/input_extended.h` defines ABI version 1 and these hard limits:

- 16 simultaneously active touch points;
- 32 touch events and 16 gesture events per frame;
- 32 outstanding haptic commands, with at most 8 executed per platform poll;
- haptic duration 0..5000 ms, where zero stops the current effect;
- motor strengths in [0,1], finite coordinates in [0,1].

`InputExtended` starts with `abi_version` and `struct_size`. It contains active touches, per-frame touch/gesture events, per-pad connection/feedback status, and fixed haptic slots. It is initialized before use and is not copied after initialization because its haptic lock is atomic.

A public `InputTouchId` is a nonzero 64-bit handle composed from a slot and a nonzero generation. The OS id remains available as `source_id` but is not the persistent identity. Reusing an OS id allocates a new generation, including release-and-press within one frame. Terminal events retain the old handle while the active slot can be reused.

Touch functions accept either normalized coordinates or finite pixel coordinates plus nonzero dimensions. Negative, NaN, infinite, and greater-than-window coordinates return `INPUT_EXT_INVALID` without changing state. Move/release for an unknown OS id returns `INPUT_EXT_STALE`. A full active array or event queue returns `INPUT_EXT_OVERLOAD`; cumulative drop counters and `touch_last_error` make backend-visible overflow explicit. Terminal events always deactivate the touch even if their event record cannot be queued, preventing stuck input; the failed event record is counted.

Touch phases are press, move, release, and cancel. Active snapshots also use held. `input_extended_new_frame()` clears per-frame events and turns press/move into held. `input_extended_cancel_all()` is used on focus/seat loss and never synthesizes a tap or swipe.

## Gestures

All thresholds use normalized window coordinates and caller-supplied monotonic milliseconds:

- tap: one touch, at most 300 ms, travel at most 0.04;
- long press: one unblocked touch held for at least 500 ms, travel at most 0.04, emitted once;
- swipe: one unblocked touch released within 700 ms with travel at least 0.08; displacement is final minus initial position;
- pinch/rotate: exactly two active touches, reported on motion with centroid, distance ratio, and cumulative angle in radians in [-pi, pi]. A zero initial distance establishes the baseline on the first later nonzero-distance motion.

Starting a second touch blocks tap/long-press/swipe for the whole contact sequence until all touches end. Cancel never produces a completion gesture. Gesture queue overflow is reported and counted; it does not allocate memory.

## Haptic command and completion protocol

`input_extended_request_haptic()` may be called from any thread. It validates range and current pad status, then claims a free slot under a short C11 atomic-flag lock. A nonnull output pointer is required because every accepted command must be retrievable and its result slot must eventually be released. A command contains a nonzero request id, pad index, pad generation, motor strengths, and duration. A full outstanding set returns `INPUT_EXT_OVERLOAD`; disconnected and no-feedback devices return `INPUT_EXT_DISCONNECTED` and `INPUT_EXT_UNSUPPORTED` respectively. No device call occurs in this function.

Only the platform polling thread calls `input_extended_haptic_pump()` and the backend executor. The pump validates the captured generation immediately before execution, marks a slot running, releases the lock, and invokes the executor. Disconnect completes a pending request as disconnected; reconnect with a new connection serial completes an old request as stale. Backend errors become disconnected, unsupported, or failed as appropriate.

A result remains in its slot until `input_extended_haptic_result()` retrieves it. Retrieval returns the final status and frees the slot; an unfinished request returns pending and an unknown/already-retrieved id returns stale. Thus result delivery cannot silently overwrite a newer request. Backend connection serials distinguish two devices that reuse the same numeric pad slot without an intervening public snapshot.

## Real backends

### Wayland

Create/destroy `wl_touch` with seat touch capability. Down/motion normalize surface-local fixed-point coordinates; up uses the last known coordinates. Native `time` is not compared with the local clock: down/motion/up all use dispatch-time `time_microseconds()/1000`, so the wrapping u32 Wayland timestamp cannot distort tap, long-press, or swipe durations. `wl_touch.cancel`, capability removal, and seat removal cancel every active touch through one shared handler. Ignore downs for another surface and release the object during every teardown path.

### Win32

Register the HWND for `WM_TOUCH`. Convert each `TOUCHINPUT` screen position in hundredths of a pixel to client coordinates and normalize with the current client size. Down/move validate their coordinates; up always uses the last valid coordinates so an out-of-window or negative final position cannot leave a stuck touch. Oversize batches, `GetTouchInputInfo` failure, and client-origin conversion failure cancel every active touch before the handle is closed; oversize also retains its overload count. Focus or capture loss cancels all touches without releasing unrelated held keys.

### Linux evdev haptics

Try `O_RDWR|O_NONBLOCK`, then fall back to the existing read-only path. Feedback is available only on a writable device advertising `EV_FF` and `FF_RUMBLE`. The polling thread uploads/reuses one bounded rumble effect per device and writes `EV_FF`; zero duration stops it. Remove the effect when closing the device. Read-only or non-FF devices degrade to unsupported without affecting ordinary gamepad input.

### Windows XInput haptics

Dynamically load `XInputSetState` and optionally `XInputGetCapabilities` beside `XInputGetState`. If capabilities are queryable, honor `XINPUT_CAPS_FFB_SUPPORTED`; otherwise a successful `XInputSetState` remains the capability test. Because XInput has no native duration parameter, the polling thread records a monotonic deadline and sends zero motors on expiry; shutdown also stops any active effect. `ERROR_DEVICE_NOT_CONNECTED` maps to disconnected and other failures to failed. Missing DLL/functions or devices without feedback degrade to unsupported/disconnected while input polling continues.

## Historical X11/XI2 backend (pre-2.0.0)

When XInput2 2.2 or newer is available, select `XI_TouchBegin`, `XI_TouchUpdate`, and `XI_TouchEnd` on the window. Combine `sourceid` and `detail` into the source identity so two devices can reuse a detail value safely. Begin/update normalize `event_x/event_y`; end always uses the last valid coordinates through `input_extended_touch_end`, even when the final native position is outside the window. All events use dispatch-time `time_microseconds()/1000`, the same monotonic epoch as gesture updates, rather than the wrapping XI2 `time`. XI2 has no portable `XI_TouchCancel` event, so focus loss and `XI_HierarchyChanged` cancel all touches. Servers without XI2 touch retain existing keyboard/mouse behavior and report no touches.

## Error handling and ownership

The sidecar uses `INPUT_EXT_OK`, `INVALID`, `OVERLOAD`, `STALE`, `DISCONNECTED`, `UNSUPPORTED`, `FAILED`, `PENDING`, and `REJECTED`. Touch state and platform-private device fields are platform-thread confined. The haptic lock protects only POD queue/status fields and is never held across an OS call. No callback writes another thread's device state. Platform destruction requires the owner to have stopped external producers before freeing the sidecar.

## Verification

Tests use `test_framework.h` and deterministic timestamps. They cover press/move/release/cancel, same-frame id reuse and generations, normalized/pixel range rejection, active/event/gesture capacities, tap/long-press/swipe/pinch/rotation, stale ids, no-feedback and disconnect degradation, stale commands after reconnect, result-slot reuse, and multithreaded producers with a deterministic fake executor.

Each feature group is compiled and run before implementation to capture RED, then run after the minimal implementation for GREEN. Focused suites run in normal, ASan+UBSan, and TSan builds with `-j3`. Current native `wl_fixed_t`/`wl_surface` and `TOUCHINPUT` fixtures inject down/move/up/cancel, out-of-window positions, id reuse, rejected batches, and wrapping OS timestamps into the same production handlers called by each event loop. A portable direct-source build also executes the real XInput backend against a deterministic fake on non-Windows hosts, while the native Windows targets remain registered. A real `zig cc -target x86_64-windows-gnu` cross build compiles the Windows engine, XInput fake tests, WM_TOUCH tests, and Win32 runtime tests; the resulting executables still require a Windows runtime and are not claimed as executed when that lane is unavailable.

Mutation checks deliberately break cancel, id generation, coordinate range checks, disconnect handling, haptic capacity, terminal UP cleanup, rejected-batch cleanup, and dispatch-time selection in separate build-tree copies. Each focused suite must fail for the intended reason. These mutations never enter the committed source.

## Historical verification evidence (pre-2.0.0)

Native `XIDeviceEvent` fixtures injected down/move/up/cancel, out-of-window positions, id reuse, rejected batches, two XI2 devices, and wrapping OS timestamps into the same production XI2 handlers then called by the X11 event loop. XI2 source-identity mutations were also made to fail the focused suite for the intended reason. These tests and mutations are historical evidence only; the X11/XI2 production handlers and their dedicated tests were removed in 2.0.0 and are not claimed to execute now.

Completion evidence distinguishes real implementation and fake/device tests from physical touchscreen, vibration feel, and Windows runtime validation, none of which is implied by unit-test success.
