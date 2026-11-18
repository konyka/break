# Core App Voice Lane Implementation Plan

**Goal:** Run `CoreAppVoice` inside the `core_app` executable behind `--voice off|fake|device`, as a coordinator subsystem whose frames the CoreAppThread consumes, per `docs/superpowers/specs/2026-11-18-core-app-voice-lane-design.md`.

**Architecture:** A `CoreAppVoiceMode` config field selects the lane. `core_app.c` owns a `CoreAppVoiceLane` struct (component pointer, optional private FAKE playback, counters). Subsystem `voice` sits at index 1 (between `network` and `audio`) so its stop/drain/destroy run before audio destroys the borrowed device.

## Task 1: RED executable contract

Files: `engine/tests/test_core_app_voice_lane.cmake`, `engine/CMakeLists.txt`.

- [x] Write the cmake test: fake 100-tick run with ready/stopped ordering, `produced >= 160`, `consumed == produced`, `dropped == 0`, `sequence_gaps == 0`, `peak > 0`, zero overruns; a byte-identical repeat; no `event=voice` without the flag; exit 2 for `--voice=bogus` and `--voice=device --audio=record`.
- [x] Register `test_core_app_voice_lane` (labels `headless;core_app;audio`). Confirm RED: the executable rejects `--voice` as an unknown argument.

## Task 2: GREEN CLI and lane

Files: `engine/apps/core_app/core_app.h`, `main.c`, `core_app.c`.

- [x] Add `CoreAppVoiceMode {OFF, FAKE, DEVICE}` and `voice_mode`; parse `--voice`, reject device without `--audio=device`, list it in `--help`.
- [x] After audio start: fake creates a FAKE playback system plus FAKE-capture voice and starts manual mode; device borrows `app->audio.system` (unavailable when NULL), uses default capture and the worker. Trace `ready`/`unavailable`; `--require-device` turns unavailable into exit 77, otherwise the lane is off.
- [x] Per tick after the audio drain: fake injects/render 800 frames of the 440 Hz tone and pumps; every mode pops all frames, checks sequence continuity and peak.
- [x] Register subsystem `voice` (coordinator capacity 5): stop_producers stops the component, drain pops the rest, destroy destroys the component and FAKE playback and writes `stopped`. Mirror it in rollback before audio.
- [x] Run the test to GREEN, then the existing core_app lifecycle/naming/ctest contracts.

## Task 3: Device lane test

- [x] Add `tests/test_core_app_voice_device.cmake` (label `audio_device`, `SKIP_RETURN_CODE 77`, RUN_SERIAL) asserting ready/stopped, `produced > 0`, `consumed == produced`, `sequence_gaps == 0`. Run it on this host and record the result honestly (pass or skip).

## Task 4: Verification and delivery

- [x] ASan+UBSan and TSan runs of the voice lane test. Mutations: skip pop (consumed≠produced), skip inject (produced 0), wrong subsystem order (TSan/ASan or ordering failure), skip sequence check.
- [x] Terminology check on added lines, `git diff --check`, independent review.
- [x] Docs: `docs/design/core_app_integration.md`, `docs/design/audio_extended.md`, `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, and the core_app CLI section of the build guide if it lists flags.
- [x] `/tmp/full_trees.sh` (expected counts each +1 or +2), push `master`, check CI, windows-d3d12, proton-d3d12 including MSVC `/W4 /WX`.

## Result

- Tasks 1 to 4 are done. The `destroy` step of Task 2 moved to `join` after review (see the spec's revisions). The device test uses `sequence_gaps <= dropped`.
- Review fixes: worker failure while running fails the run with `stage=voice`; `capture=<name>` on the ready line; Null capture backend reads as unavailable; only UNAVAILABLE takes the unavailable path; TSan suppressions narrowed to `called_from_lib:libpulsecommon-*.so` and `called_from_lib:libpulse.so.0`.
- Added tests: `test_core_app_voice` case 7 (a capture device that cannot start is UNAVAILABLE, RED then GREEN), `test_audio_capture` backend name case, `test_core_app_voice_null` (forced Null capture: exit 77 when required, lane off otherwise, never ready).
- Local results: `ctest -L core_app` 38/38 with 3 existing nm skips; device lane on PulseAudio "内置音频 模拟立体声" passes with `produced == consumed`; ASan+UBSan 5/5 for the voice, capture and audio device tests; TSan voice_device and audio_device 3/3 runs each with zero warnings under the narrowed suppressions, while no suppressions and `race_top` both still fail.
- Mutations caught: skip consumed, skip pump, skip peak, skip tick, gap always, skip Null check, skip worker check, capture name forced to none. Surviving and accepted: skip sequence check and skip drain (the FAKE lane never gaps and consumes everything every tick), voice/audio index swap (caught only by the local ASan device run, since CI has no audio device), treating every device start error as unavailable (FAKE cannot produce a non-UNAVAILABLE device start error).
- Not tested: the rollback path with a live voice lane, and borrowed-device shutdown order on CI hosts without an audio device.
- Second review (Not ready on one Important item) fixed: the null test now skips on a host without playback (checked with `PULSE_SERVER=unix:/nonexistent ALSA_CONFIG_PATH=/nonexistent`: Skipped); `--voice-null-capture` requires `--voice=device` (lane test asserts exit 2 with a CLI diagnostic, RED before the guard); FAKE UNAVAILABLE maps to FAILED; capture name buffer 128 bytes; suppression uses `libpulsecommon-*.so` (TSan voice_device, audio_device, voice_null 3/3 each, zero warnings).
- Still untested through the executable: a worker failure while running (`reason=worker`); only the component-level worker error is tested. A worker that fails after the last tick shows `stage=shutdown` without a `reason=worker` line; the exit code is still a failure.
