# Core App Voice Lane Design

## Goal

Run the existing `CoreAppVoice` PCM pump inside the real `core_app` executable: a CLI switch, a coordinator subsystem with ordered shutdown, a deterministic FAKE lane for CI and a real capture-device lane. The CoreAppThread consumes every produced `BreakVoiceFrame` and reports verifiable diagnostics in the trace.

## Scope

In scope:

- `--voice off|fake|device` (default `off`). `off` leaves every existing trace byte-identical.
- `fake`: the voice component owns a private FAKE playback `AudioSystem` as its reference source and FAKE capture. Each fixed tick the CoreAppThread injects 800 frames (16.667 ms at 48 kHz) of a deterministic 440 Hz tone at amplitude 0.25, renders 800 frames of the FAKE playback, and pumps manually. No worker thread, so record traces stay deterministic.
- `device`: requires `--audio=device`. The voice borrows the opened playback device's `AudioSystem` and uses `AUDIO_BACKEND_DEFAULT` capture with the dedicated worker. If the playback lane fell back to null, or capture cannot open, the trace records `result=unavailable`; with `--require-device` the run exits 77 like the audio device lane.
- Each tick after the audio drain, the CoreAppThread pops every queued frame, checks that sequences increase by one, and tracks the peak absolute sample.
- Coordinator subsystem `voice` registered between `network` and `audio`: `stop_producers` stops the pump (joining the worker), `drain` pops what remains, `destroy` destroys the component, then the private FAKE playback, and writes the summary. Because subsystems run in index order per phase, the voice stops before audio destroys the borrowed device. Rollback after a partial start follows the same order.

Out of scope (later slices): encoding/sending over the network transport, device recovery, tail flush, drift compensation, acoustic validation.

## Trace

```
COREAPPTRACE version=1 event=voice mode=fake result=ready frames=480
COREAPPTRACE version=1 event=voice mode=device result=ready frames=480 capture=<name>
COREAPPTRACE version=1 event=voice mode=device result=unavailable reason=playback|capture fallback=none|off
COREAPPTRACE version=1 event=voice mode=<m> result=stopped produced=P consumed=C dropped=D sequence_gaps=G peak=K capture_overruns=X reference_overruns=Y
```

`ready` precedes `runtime_running`; `stopped` follows it and precedes `runtime_stopped`.

## Errors

- Unknown `--voice` value, or `--voice=device` without `--audio=device`: CLI error, exit 2.
- Voice create/start failure in `fake`: startup failure, normal rollback.
- A pump, pop or stop error during the run: `stage=voice`, run fails.

## Testing

`tests/test_core_app_voice_lane.cmake` runs the real executable:

1. `--voice=fake` 100-tick record run: ready/stopped ordering; `produced >= 160`, `consumed == produced`, `dropped == 0`, `sequence_gaps == 0`, `peak > 0`, zero overruns.
2. A second identical run yields a byte-identical trace.
3. A run without `--voice` contains no `event=voice`.
4. `--voice=bogus` and `--voice=device --audio=record` exit 2.

`tests/test_core_app_voice_device.cmake` (label `audio_device`, skip code 77) runs `--audio=device --voice=device --require-device` and checks ready/stopped, `consumed == produced`, `sequence_gaps == 0` and `produced > 0`.

## Assumptions

- Auto mode allows no clarifying questions, so `off` is the default to keep existing traces and CI unchanged.
- The FAKE lane exists for deterministic CI evidence; it proves the PCM pump runs end to end inside the app, not that a microphone works.

## Revisions after independent review

The first review returned Not ready. The design changed as follows; the sections above stay as the original record.

- **Teardown phase.** The component and the private FAKE playback are destroyed in the subsystem's `join` callback, not in `destroy`. The audio owner thread closes the borrowed device in audio's own `join` callback, and `voice` has the lower index, so `voice` join runs first. Moving teardown to `destroy` produced a heap-use-after-free under ASan on the device test.
- **Sequence rule on a device.** The device test accepts `sequence_gaps <= dropped` instead of `sequence_gaps == 0`: a full queue drops the newest packet and the sequence still advances, so every drop can produce one gap.
- **Capture name.** The DEVICE `ready` line ends with `capture=<name>`. Spaces, tabs and line breaks in the name become `_`, because trace parsers split fields on spaces. FAKE reports `capture=fake`; a missing name is `none`, and the device test rejects `none`.
- **Null capture backend.** miniaudio falls back to its Null backend when no real capture backend initializes. That device delivers silence forever, so the lane treats `audio_capture_backend_name() == "Null"` as no microphone: `result=unavailable reason=capture`, exit 77 with `--require-device`, lane off otherwise. `--voice-null-capture` forces this backend so the branch is testable on a host that has a microphone.
- **Unavailable classification.** The component maps a capture device that cannot be opened or started (`AUDIO_FAILED`) to `BREAK_RUNTIME_UNAVAILABLE`. The lane takes the unavailable path only for UNAVAILABLE or a Null backend; any other start error is a normal startup failure.
- **Failure while running.** A DEVICE worker that stops with an error (for example a lost capture device) writes `event=voice mode=device result=failed reason=worker` and fails the run with `stage=voice` and `BREAK_RUNTIME_FAILED`. It is not mapped to exit 77: the device was present at start, so this is a defect of the run. `stop_producers` likewise turns UNAVAILABLE into FAILED.
- **Second review.** `--voice-null-capture` without `--voice=device` is a CLI error (exit 2). A FAKE start error that is UNAVAILABLE becomes FAILED, so FAKE never exits 77. `test_core_app_voice_null` skips (exit 77, `CORE_APP_VOICE_NULL_UNAVAILABLE`) on a host without a playback device instead of failing. The capture name buffer is 128 bytes, matching the source buffer, so a long UTF-8 name is not cut inside a character. The TSan suppression matches `libpulsecommon-*.so`.
