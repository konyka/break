# Delay-Line Crossfade Design

Status: Implemented and locally verified

## Purpose

Add optional click-free delay transitions to `AudioDelayLine` while preserving the existing immediate-change behavior by default and retaining linear/sinc mode semantics.

## Approaches considered

1. **Two history readers with a bounded linear crossfade (selected).** Uses the existing ring, works for linear and sinc, needs no allocation and supports arbitrary chunks.
2. **Rebuild the AEC or recreate the delay line on every change.** Loses history and adds allocation/lifecycle coupling; rejected.
3. **A separate mixer-level smoothing wrapper.** Would duplicate delay history and make existing callers opt into a different ownership path; rejected.

## API

Add:

```c
AudioResult audio_delay_line_set_crossfade_frames(AudioDelayLine *line, u32 frames);
u32 audio_delay_line_crossfade_frames(const AudioDelayLine *line);
```

- NULL setter returns `AUDIO_INVALID`; NULL accessor returns zero. Accept 0..48000 frames. Create defaults to zero, which preserves every existing immediate transition.
- A nonzero setting applies to subsequent delay changes. The setting itself may change only while no fade is active; otherwise return `AUDIO_REJECTED` without changing state.
- Delay setters validate the target normally, then return `AUDIO_REJECTED` without changing state if a fade is active. An unchanged target with no active fade is a successful no-op.
- `audio_delay_line_set_sinc` likewise returns `AUDIO_REJECTED` during an active fade; otherwise its behavior is unchanged.

## Processing

Keep `fade_from`, `fade_total` and `fade_remaining` in the existing owner-thread object. When a valid new target differs and the configured duration is nonzero, start a fade from the previous target on the next processed frame.

For fade step `s=1..N`, compute both old and new delayed values from the same current history and blend with `old*(1-s/N) + new*s/N`. The first frame therefore includes the new target by `1/N`, and frame N is exactly the new target. Linear results use the existing `nearbyint`; sinc results use its round-then-saturate conversion after blending.

The current input is written before both reads, preserving the existing zero-delay and in-place rules. Sinc's D+8 latency applies to both readers. Chunk boundaries do not affect the sequence. No crossfade occurs when duration is zero or the target is unchanged.

## Tests

Add three tests to the existing 18-test delay-estimator suite:

1. Crossfade config/NULL/accessor validation, default immediate behavior, unchanged-target no-op and rejection of retarget/mode/config changes during an active fade.
2. Hand-computed linear fade values, exact final target, in-place operation and arbitrary-chunk equivalence; zero-duration behavior remains byte-identical to the old implementation.
3. A sinc fade matches an independent dual-reader reference, preserves D+8 latency and saturates a full-scale blended overshoot.

Run targeted weight/step/rejection/saturating mutations, ASan+UBSan, strict warnings, terminology checks, independent review and three-tree verification before push.

## Limits

Mono only. An active fade rejects rather than queues retargeting; no automatic AEC reset, multichannel coupling, adaptive duration or real acoustic validation is added. Core app reference capture and voice-worker integration remain separate projects.
