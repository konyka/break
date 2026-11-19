# Core App Runtime Playback Device Switch Design

## Goal

A running core_app can switch its playback device by command, without restarting: sources, buses, the listener and the voice reference tap keep going. The command comes from the scenario file, so it is deterministic and testable; any later UI or console only has to enqueue the same request.

## Scenario command

`TICK audio-device NAME` switches to the device called NAME; `TICK audio-device` (no name) switches back to the default device. NAME is the rest of the line after the command and one space, so names with spaces work ("NULL Playback Device"). It must be 1..127 bytes (the audio layer refuses 128 and more) and contain no control characters; otherwise the scenario is invalid. New kind `CORE_APP_SCENARIO_AUDIO_DEVICE`; the name is stored in `event.path`.

## Runtime

- `core_app_audio_request_device(audio, name)` enqueues a `CORE_APP_AUDIO_SWITCH_DEVICE` command carrying the name (NULL or "" for the default). Device mode only: in record and null modes it returns `REJECTED` and enqueues nothing. Queue full: `OVERLOAD`, like any other command. The command needs no generation.
- The owner thread (or the caller's drain when there is no owner) calls `audio_system_switch_device`, so the call stays on the thread that owns the system. Ordering with the other commands is the queue order.
- Results: OK counts `device_switches` and traces `event=audio_device result=switched device=NAME` (`default` for the default); REJECTED counts `device_switch_rejected` and traces `result=rejected reason=device_name`; FAILED counts `device_switch_failures` and traces `result=failed`. None of them stops the run: after a refused switch the old device keeps playing, and a failed one that left no device is handled by the existing playback recovery.
- core_app: the scenario event calls the request. In record and null modes it traces `event=audio_device result=rejected tick=N reason=mode` and continues. An overloaded queue traces `reason=overload`.
- The device `result=stopped` line appends `device_switches`, `device_switch_rejected`, `device_switch_failures`.

## Testing

1. `test_core_app_runtime`: scenario parsing (name with spaces, no name, 128-byte name, control character); a NULL-backend system with an owner thread switches to "NULL Playback Device", refuses "no such speaker", switches back to the default, every call made on the owner, the stopped line carries 2/1/0; record mode returns REJECTED.
2. `test_core_app_named_device` (host with a playback device): a scenario that switches to the default device's name, then to an unknown name, then back to the default; the run exits 0 with `switched device=<name>`, `rejected reason=device_name`, `switched device=default` and `device_switches=2 device_switch_rejected=1`. Without a device the contract checks the record-mode rejection only.
3. Mutations: the switch made off the owner; an unknown name treated as a switch; record mode accepting the request.

Out of scope: switching the capture device at runtime, a UI or console that issues the command.

## Result

- RED then GREEN: scenario parsing (2 tests), owner-thread switch and record-mode rejection (2 tests), the record-mode and real-device contract in `test_core_app_named_device`. On this host PulseAudio "内置音频 模拟立体声" switched by name at runtime and back to the default.
- Spec change: the name must also not start or end with a space (the line is split on single spaces, so a leading or trailing one would be invisible in the trace).
- Mutations: unknown name treated as a switch; record mode accepting the request; the switch made on the caller instead of the owner. Each fails at least one test.
- Full suite 451/451; ASan+UBSan and TSan trees 10/10.
- Independent review: Ready. Changes made after it: whitespace in the switched device name is traced as `_` so the line still splits on spaces; a successful switch resets `consecutive_reopen_failures`; an invalid request traces `reason=invalid`; the scenario fuzzer gained six audio-device substitutions. The ready line still prints the raw name (pre-existing format the named-device contract parses); recorded as a known limit.
