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
