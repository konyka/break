# AEC and Residual Suppressor Integration Design

Status: Implemented and locally verified

## Purpose

Reuse the AEC's existing Geigel near-end/double-talk decision for residual suppression, with correct per-frame semantics and no caller-side duplicate detector.

## Approaches considered

1. **Read-only AEC state plus a per-frame convenience pipeline (selected).** Exposes the existing decision for custom scheduling and provides a safe block API that internally processes one frame at a time.
2. **Expose only a block-level flag.** A last-frame or any-frame flag cannot correctly represent mixed content throughout a block; rejected as the sole integration.
3. **Duplicate Geigel detection in the residual suppressor.** Adds another threshold/hangover state to configure and risks disagreement with AEC adaptation; rejected.

## AEC state API

Add:

```c
bool audio_echo_canceller_near_end_active(const AudioEchoCanceller *aec);
```

- Return false for NULL, initial/reset state, or disabled detection (`double_talk_threshold==0`).
- Store whether the most recently processed frame either matched the Geigel condition or consumed a pending hangover frame. A detected frame is true even when configured hangover is zero.
- A quiet frame after hangover expiry returns false. Zero-frame and invalid processing calls leave the previous state unchanged; reset clears it.
- Existing adaptation, output PCM, weights, hold counter and chunking behavior remain unchanged.

## Integrated residual pipeline

Add:

```c
void audio_residual_echo_suppressor_process_with_aec(
    AudioResidualEchoSuppressor *suppressor, AudioEchoCanceller *aec,
    const i16 *reference, i16 *capture, u32 frames);
```

For each frame, call the existing AEC process, read `near_end_active`, then call the existing residual suppressor with that flag. A block therefore matches the equivalent manual per-frame sequence exactly.

NULL suppressor/AEC or nonzero-frame NULL signal pointers are no-ops. Zero frames is a no-op. The function performs AEC itself; callers must not also run AEC on the same capture. Existing separate APIs remain available for custom detectors and scheduling.

No allocation, locks, platform calls or new threads are introduced.

## Tests

- Add one AEC test (8→9): NULL/initial/disabled detection, a detected frame with zero hangover, hangover consumption, zero-frame state preservation and reset.
- Add one residual test (7→8): the integrated block matches a manual per-frame reference byte-for-byte, including PCM, path/gain and AEC weights; a final near-end burst opens gain without a caller flag; invalid/zero calls preserve state.
- Mutate detected-state assignment, zero-hangover handling, reset clearing and per-frame wrapper ordering/routing.
- Run ASan+UBSan, strict warnings, terminology checks, independent review and three-tree verification before push.

## Limits

The Geigel detector remains heuristic and configuration-dependent. This slice does not add spectral coherence, multichannel processing, production device wiring or real acoustic validation.
