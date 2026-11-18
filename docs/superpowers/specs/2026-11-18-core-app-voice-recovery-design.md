# Core App Voice Capture Recovery Design

## Goal

When the capture device of the core_app voice lane is lost (unplugged, disabled, taken by the system), the lane reopens the default input device and continues instead of ending the run. Only a device that stays unavailable for a bounded number of attempts fails the lane, as today.

## Scope

In scope:

- `CoreAppVoiceConfig` gains `u32 reopen_interval_ms` and `u32 max_reopen_failures`. Zero `max_reopen_failures` keeps today's behaviour (a lost device makes `pump` return `BREAK_RUNTIME_UNAVAILABLE` at once), so existing callers and tests that zero the config are unchanged.
- `core_app_voice_pump`, while the capture is lost and recovery is enabled: at most one `audio_capture_reopen(capture, NULL)` per call, and none until `reopen_interval_ms` has passed since the previous attempt (monotonic clock; 0 means every call). Success: `capture_recoveries++`, the consecutive failure count resets, the reference backlog rendered while nothing was captured is discarded (it has no matching capture), the voice processor is reset, and pumping continues in the same call. Failure: `capture_reopen_failures++` and the consecutive count grows; pump returns OK with no packet until the count reaches `max_reopen_failures`, then UNAVAILABLE (the worker stops with that error, as today).
- `CoreAppVoiceStats` appends `capture_recoveries` and `capture_reopen_failures`.
- `audio_capture_simulate_event` gains `AUDIO_CAPTURE_EVENT_REOPEN_REFUSED` (FAKE and NULL backends only): each event makes one later `audio_capture_reopen` return AUDIO_FAILED and leave the capture lost. This is the only way to test the failure path without hardware.
- core_app (device mode) configures 100 ms and 50 attempts (about 5 s). The voice `result=stopped` trace line appends `capture_recoveries=N capture_reopen_failures=M`; fake mode reports 0 and 0.

Out of scope: choosing another named device, recovering the playback reference device, recovery in fake mode (its capture is never lost), drift compensation, real acoustic tests.

## Threads

`audio_capture_reopen` is an owner-thread call. In threaded mode the worker is the only caller of `pump`, so it reopens from the worker; in manual mode the pumping thread does. The device callback still only writes the ring and the lost flag.

## Testing (`test_core_app_voice`, `test_audio_capture`)

1. `test_audio_capture`: `REOPEN_REFUSED` makes the next reopen fail once and keeps `audio_capture_lost` true; the reopen after it succeeds and clears it; DEFAULT backend REJECTED as for the other events.
2. Manual mode: lose the device while playback keeps rendering three packets, pump recovers (recoveries=1), the reference backlog drops below one packet, and packets continue with consecutive sequences.
3. Manual mode with two refusals and `max_reopen_failures = 3`: two pumps return OK with failures=1,2, the third reopen succeeds; with three refusals the third pump returns UNAVAILABLE.
4. `reopen_interval_ms`: with a 10 s interval, a second pump right after a refused attempt does not try again (failures stays 1).
5. Threaded mode: a loss while the worker runs is recovered and the worker error stays OK; frames keep coming.
6. Recovery disabled (zero config): the existing `worker_error_and_capture_backend_are_visible_while_running` still sees UNAVAILABLE.
7. `test_core_app_voice_device.cmake` and the network voice driver accept the two new fields.
8. Mutations: no reopen call; failure count never resets; reference backlog not discarded (test 2 checks the backlog). Each must fail a test.

## Revisions during implementation

- Test 2 checks the dropped reference backlog directly. After review, `a_reopened_capture_processes_like_a_fresh_pipeline` also compares the first packet after a reopen with a new aligner and processor fed the same input; it fails when the processor reset or the stale-capture discard is removed.
- After review, a reopen also discards capture frames left in the ring from before the loss; they end before the gap and would pair with the wrong reference. The aligner has no reset and keeps its delay estimate, which settles again on the new frames.
- After review, core_app reads the capture device name before the worker starts, because a reopen on the worker rewrites it.
- The fake lane's `result=stopped` line must report `capture_recoveries=0 capture_reopen_failures=0` (`test_core_app_voice_lane.cmake`); the device driver accepts any value.
- Mutations: no reopen call fails 3 tests, no failure-count reset fails 1, no backlog discard fails 1, no processor reset fails 1, no stale-capture discard fails 1 (`test_core_app_voice`).
- Sanitizers on 2026-11-18: ASan+UBSan (`build-voice-recovery-asan`) passes the five voice tests; TSan (`build-voice-recovery-tsan`) passes four of them and reproduces the same `test_core_app_voice_null` failure on an untouched HEAD TSan build — a race inside libpulse's context (`pa_packet_new_data` against `ma_worker_thread`), not in this change.
- Follow-up: `test_core_app_voice_null` now uses `tests/core_app_audio_device_tsan.supp` like the other two real-device tests; with it the TSan tree passes all six voice and device tests.
