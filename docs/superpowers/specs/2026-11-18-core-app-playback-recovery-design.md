# Core App Playback Device Recovery Design

## Goal

When the playback device of a core_app device-mode run is lost (unplugged, disabled, taken by the system), the audio owner reopens the default output device and keeps playing instead of going silent for the rest of the run. Sources, buses, the listener and the playback reference tap survive the reopen because they live in the engine's node graph, not in the device. Only a device that stays unopenable for a bounded number of attempts fails the run.

## Scope

In scope:

- `AudioSystem` gains loss detection and an in-place reopen:
  - `bool audio_system_lost(const AudioSystem *as)`: true once a simulated loss was posted, or once the real device has stayed out of the started state for at least 250 ms (`AUDIO_DEVICE_LOSS_GRACE_US`; backends stop and restart a device on their own, for example a PulseAudio suspend or a WASAPI reroute). False for NULL and for a FAKE system that was not marked lost.
  - `AudioResult audio_system_reopen(AudioSystem *as)`: uninitializes the engine's device and initializes the default playback device in the same memory with the same channel count and sample rate, then starts it. A device the backend already restarted is left alone and OK is returned without counting a recovery. OK clears the lost flag. `u64 audio_system_recoveries(const AudioSystem *as)` counts the reopens that replaced the device. FAILED leaves the system lost (and, after a real failure, with no device: backend and device names then report "none"). FAKE systems have no device: reopen only clears the flag. INVALID for NULL. Owner thread only; never concurrent with `audio_system_backend_name`, `audio_system_device_name` or `audio_system_destroy`.
  - `AudioResult audio_system_simulate_event(AudioSystem *as, AudioSystemEvent event)`, FAKE and NULL backends only: `AUDIO_SYSTEM_EVENT_DEVICE_LOST` marks the system lost; `AUDIO_SYSTEM_EVENT_REOPEN_REFUSED` makes the next reopen return FAILED and change nothing (one refusal per event). REJECTED for the DEFAULT backend, INVALID for NULL or an unknown event.
- To make the reopen possible, `audio_system_create_ex` passes its own data callback (`ma_engine_read_pcm_frames` on the engine) to `ma_engine_init`; the device's user data stays the engine. No notification callback is used: miniaudio posts no stop notification when a backend fails to stop a stream whose device went away, so the device state decides.
- `CoreAppAudio` (device mode) checks `audio_system_lost` before it applies queued commands, on the owner thread or in the synchronous drain. While lost it reopens at most once per check and no sooner than `reopen_interval_ms` after the previous attempt (monotonic clock; 0 means every check). A success counts `device_recoveries` and resets the consecutive count; a failure counts `device_reopen_failures`. When the consecutive failures reach `max_reopen_failures` the drain (or the owner error) becomes `BREAK_RUNTIME_FAILED`, which fails the frame as any device error does today. Commands keep reaching the system while it is lost, so sources started during the gap play once the device returns.
- Defaults set at start: 100 ms and 50 attempts (about 5 s). `max_reopen_failures = 0` disables recovery: a lost device then fails the next drain at once.
- The device-mode `result=stopped` trace line appends `device_recoveries=N device_reopen_failures=M` after `owner_thread`.

Out of scope: switching to a named device, re-routing notifications, a separate reopen thread, restoring a device that failed to start inside a reopen beyond reporting it lost, drift between the new device and the capture device.

## Threads

The audio owner thread is the only caller of every AudioSystem function after start, so it is also the only caller of `audio_system_reopen`. The voice worker reads only the reference ring, which belongs to the system and not the device, so a reopen does not disturb it. No notification callback is installed, so nothing posted by the old device during its uninitialization reaches the system. A reopen does pause the reference ring: the voice pump compares `audio_system_recoveries` with the value it saw last and, when it changed, drops the captured frames beyond the reference backlog and resets the processor, so the echo canceller does not pair new capture with old reference. Each reopen attempt blocks the owner for as long as the backend takes to open a device; 50 x 100 ms is a lower bound, and a full queue answers producers with OVERLOAD meanwhile.

## Testing

`test_audio`:

1. NULL backend: not lost after create; `DEVICE_LOST` makes it lost; reopen returns OK, clears it, keeps backend "Null", and the reopened device renders (the reference tap receives frames after the reopen).
2. FAKE backend: a refused reopen returns FAILED and keeps the system lost; the next reopen succeeds; each event refuses once.
3. Validation: DEFAULT backend simulate is REJECTED, NULL arguments are INVALID or false, an unknown event is INVALID.

`test_core_app_runtime` (FAKE system):

4. Synchronous drain with interval 0: a lost system is reopened during the drain, `device_recoveries=1`, and the stopped trace line reports it.
5. Two refusals with a limit of three: two drains return OK with failures 1 and 2, the third reopens; after a recovery three more refusals fail the third drain with FAILED.
6. A 10 s interval: a second drain right after a refused attempt does not try again.
7. Owner thread: a loss is recovered by the owner and every device call stays on the owner.
8. Existing stopped-line contracts gain the two fields.
9. Mutations: never calling reopen, never resetting the consecutive count, ignoring the interval. Each must fail a test.

## Revisions during implementation

- `audio_system_create_ex` now creates and owns a context for every device backend, not only NULL. With the default backend miniaudio let the device own its context, and the engine and its resource manager keep that context's log, so a reopen would free it under them. The reopened device uses the same context.
- `audio_system_device_name` returns false for a device left closed by a failed reopen.
- `test_audio` gained `default_playback_reopen_keeps_rendering`: on a host with a real output it reopens the default device and checks that the reference tap receives frames again; it also checks that simulate is REJECTED for DEFAULT. Hosts without any backend skip it. Under TSan it uses `tests/core_app_audio_device_tsan.supp`, like the core_app device tests, for the libpulse race.
- Mutations: no reopen call fails 3 tests, no consecutive-count reset fails 1, ignoring the interval fails 1 (`test_core_app_runtime`).
- Verified: `build-core-app-net` full ctest 446/446; ASan+UBSan and TSan trees pass the nine audio and core_app voice/audio tests; the real PulseAudio contract reports `device_recoveries=0 device_reopen_failures=0`.
- Review (Not ready) fixes:
  - The DEFAULT backend lost miniaudio's backend fallback when the system started to own the context. `audio_engine_init_with_context` now walks `ma_get_enabled_backends` in order, a context plus `ma_engine_init` per backend, like `ma_device_init_ex`; NULL tries only the null backend.
  - iOS keeps the playback session category (`ma_ios_session_category_playback`) on the owned context.
  - Loss is decided by device state with a 250 ms grace period instead of a stop notification, so a backend that restarts its own device (WASAPI reroute) is not reopened; `audio_system_reopen` leaves an already started device alone.
  - The voice lane follows playback reopens through `audio_system_recoveries` (see Threads). `CoreAppVoiceStats.playback_recoveries` counts them, and the voice `result=stopped` trace line appends `playback_recoveries=N` after `capture_reopen_failures`; the fake lane contract requires 0, the device contract accepts any count.
  - Failure paths gained tests: a NULL device stopped past the grace period, a device the backend restarted, a device closed by a failed reopen reporting no names.
  - The owner-blocking cost of a slow reopen is documented in `core_app_audio.h`, not moved to a separate thread.
- Final counts: `test_audio` 36 (7 new), `test_core_app_runtime` 53 (4 new), `test_core_app_voice` 13 (1 new: `a_playback_reopen_drops_capture_that_has_no_reference`).
- Mutations after the review: skipping `voice_follow_playback_reopen` in the pump fails `test_core_app_voice` (capture/reference mismatch); removing the "already started" branch of `audio_system_reopen` fails `a_device_restarted_by_the_backend_is_not_lost_or_reopened`.
- Second review (Ready) minors: the grace period runs on miniaudio's monotonic `ma_timer` instead of `timespec_get(TIME_UTC)`; `audio_reopen_device` documents the remaining WASAPI window between the started check and `ma_device_uninit`; the default-device test prints `(skipped: no playback backend)` on hosts without output.
