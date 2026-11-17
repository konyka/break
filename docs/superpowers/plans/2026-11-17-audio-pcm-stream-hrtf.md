# Audio: HRTF on spatial PCM streams

Status: Done

## Goal

`audio_hrtf` exists as a standalone module. Let a spatial PCM stream (network
voice, generated audio) be rendered binaurally through an `AudioHrtfSet`.
Event voices follow in the next slice.

## API

- `audio_hrtf_renderer_set_index(r, index)` (`audio_hrtf.h`): same rules as
  `set_direction`, by set index; INVALID for an index out of range.
  `set_direction` becomes nearest + set_index.
- `audio_pcm_stream_set_hrtf(as, handle, set)` (`audio_extended.h`):
  - REJECTED without `set_spatial` (checked first, like the other cues);
    INVALID for a bad handle/system or a set whose sample rate is not
    `AUDIO_PCM_SAMPLE_RATE`; STALE for a closed handle.
  - `set == NULL` detaches. Returns only once the mixer no longer uses the
    previous set (same `reading` handshake as close), so the caller may
    destroy a set after detaching it. A set must outlive its attachment.
  - Off at open.

## Behaviour

- The owner thread computes the source direction in the listener frame
  (right = forward x up, up' = right x forward): azimuth = atan2(x, z),
  elevation = atan2(y, hypot(x, z)), in degrees and clamped; a source on the
  listener or a degenerate frame is straight ahead. It publishes the nearest
  set index (atomic) with the other spatial values.
- The mixer, per callback: if the attached set differs from the renderer's,
  re-initialises the renderer (zero history); then `set_index` with the
  published index (first frame at once, later changes crossfade over 64
  frames). Per output frame the mono downmix `0.5 (l + r)` of the resampled
  frame goes through the renderer; the output times the stream gain replaces
  the stereo result. Panning, rear cue, elevation tilt and the interaural
  delay are not applied while HRTF is attached (their filter states keep
  running, so detaching continues smoothly).

## Tests (`test_audio_extended`, `test_audio_hrtf`)

1. set_index: range check, applies at once before the first frame.
2. Arguments: REJECTED / INVALID (rate, handle, system) / STALE; attach and
   detach OK.
3. A mono stream to the right equals the direct convolution with that
   direction's responses, times the distance gain; panning, ITD, rear and
   elevation cues on make no difference.
4. A stereo stream uses the downmix.
5. Moving the source mid-stream matches a reference renderer fed the same
   input with the same index changes (bit-exact).
6. Direction: rotated listener frame, source above, source on the listener.
7. Detach returns to the normal chain; reopen starts without HRTF.

## Steps

RED (compile failure) -> GREEN -> mutation -> shadow check -> realtime
contract -> three full trees -> docs -> commit, push, CI.

## Result

- `test_audio_hrtf` 9/9, `test_audio_extended` 124/124, the realtime
  contract now covers the renderer (fails with an injected malloc).
- The mixer re-initialises on the attach count alone; comparing the set
  pointer as well was redundant.
- Mutation: 20 of 20 killed after adding the reopen-after-destroy and
  unnormalised listener frame checks. Shadow check rc=0.
- Event voices are next.
