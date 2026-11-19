# Core App: switch the voice capture device at runtime

## Problem

`--voice-capture-device NAME` picks the input at start, and the voice worker reopens it after a loss, but a running core_app cannot move to another microphone. The playback side gained a runtime switch (`audio-device`); capture has none.

## Design

- **Scenario**: `<tick> voice-capture-device <name>` and `<tick> voice-capture-device`. Same name rules as `audio-device` (rest of the line after one space, 1..127 bytes, no leading or trailing space, no 0x00–0x1F or 0x7F). No name selects the default input. New kind `CORE_APP_SCENARIO_VOICE_CAPTURE_DEVICE`, name in `event.path`.
- **Voice layer**: `core_app_voice_request_capture_device(voice, name)` writes the name into a one-slot mailbox (name buffer + `atomic_bool pending`). INVALID for NULL voice; REJECTED for a name of 128 bytes or more or a voice that is not started; OVERLOAD while an earlier request is still pending. Any single requesting thread; the pumping thread consumes it.
- `core_app_voice_pump` handles a pending request before the loss check: `audio_capture_reopen(capture, name)` with no fallback to the default.
  - OK: the stored `capture_device_name` becomes the new name (a later loss reopens it), stale capture and reference frames are dropped, the processor is reset, `consecutive_reopen_failures` is cleared, `capture_switches` counts.
  - REJECTED (unknown name, a name with the FAKE backend): `capture_switch_rejected` counts; the old device keeps running.
  - Other results: `capture_switch_failures` counts. If that left the capture lost, the existing recovery reopens the stored (old) name.
  - The slot is released (`pending` = false, release order) after the counters are updated.
- **Stats**: `CoreAppVoiceStats` gains `capture_switches`, `capture_switch_rejected`, `capture_switch_failures`.
- **core_app**: the scenario event calls the request. Without a voice lane it traces `event=voice_capture_device result=rejected tick=N reason=mode`; REJECTED traces `reason=name` (too long), OVERLOAD `reason=overload`, INVALID `reason=invalid`. An accepted request is remembered; `app_voice_tick` compares the three counters after its pump and, when one moved, traces `event=voice_capture_device result=switched device=<name>|default`, `result=rejected reason=device_name` or `result=failed`. Whitespace in the traced name becomes `_`. In fake mode the pump runs on the CoreAppThread in the same tick, so the trace is deterministic; in device mode the line appears on the first tick after the worker handled it. A request still pending at stop gets no result line.
- **Trace**: the voice `result=stopped` line appends `capture_switches=N capture_switch_rejected=M capture_switch_failures=K`.

## Testing

1. `test_core_app_runtime`: scenario parsing for the new command (with spaces, no name, too long, control byte).
2. `test_core_app_voice`: NULL capture backend; switch to "NULL Capture Device" (OK), to "no such microphone" (REJECTED, old device still produces), back to the default; a second request while one is pending is OVERLOAD; a request before start and a 128-byte name are REJECTED; a lost capture after the switch reopens the switched name.
3. `test_core_app_voice_lane.cmake` (fake): `voice-capture-device` switches to the default, `voice-capture-device x` is rejected (`reason=device_name`), the stopped line carries 1/1/0, two runs stay byte-identical; without `--voice` the event traces `reason=mode`.
4. `test_core_app_voice_device.cmake` (real devices): a scenario with an unknown name and then the default; both result lines appear in order and the run exits 0.
5. Mutations: an unknown name falls back to the default; a request while pending overwrites instead of OVERLOAD; the slot is never released.

Out of scope: listing input devices from the CLI, a UI or console entry, mixing several inputs.

## Result

- RED then GREEN: scenario parsing (1 test in `test_core_app_runtime`), the voice mailbox (2 tests in `test_core_app_voice`), the fake-lane contract and the real-device contract. On this host the unknown name was refused, the default input reopened, and produced equalled consumed.
- Mutations: an unknown name falling back to the default; a pending request being overwritten; the slot never being released. Each fails at least one test.
- Deviation: core_app also refuses a second request while the first has no traced result yet (`reason=overload`), so each accepted request gets exactly one result line.
- Independent review: Ready. Fixed after it: an accepted request that the pump never reached before stop now traces `result=failed reason=stopped` at join (new lane-contract case, RED then GREEN), so the one-result-per-request rule holds; a `_Static_assert` ties the two name buffers to the same size. Known limits: result lines carry no tick; `reason=name` / `reason=invalid` are defensive; the real-device contract could see `reason=overload` if one real reopen took longer than ~2900 fixed-step ticks.
