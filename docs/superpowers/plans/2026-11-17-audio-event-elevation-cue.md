# Event voices: elevation cue (2026-11-17)

Status: Done

## Goal
Spatial PCM streams have an elevation cue (`audio_pcm_stream_set_elevation_cue`);
event voices do not (`docs/cross_engine/missing_capabilities.md` §10,
"事件 voice 的高度提示"). This slice gives spatial events the same tilt.

## Design
- `AudioEventDesc.elevation_cue`: requires `spatial`, otherwise
  `audio_event_register` returns `AUDIO_INVALID`.
- The tilt amount comes from the same `elevation_amount` as streams; 0 when
  the flag is off.
- Same protocol as the rear cue: the START command carries the initial
  amount (`spatial_tilt`) and does not write `tilt_snapshot`. Later
  `audio_voice_set_position` and listener updates store
  `tilt_snapshot = (revision, s)` before the gain snapshot CAS. The mixer
  takes it only when its revision matches the gain revision it adopts and
  the event has the cue on, so a RESTART's new amount never reaches PCM of
  the old epoch.
- Each voice has its own per-channel low-pass state, zeroed when START is
  consumed. The low-pass always runs, the output is `x + s (x - lp)`, after
  the rear cue and before the interaural delay, as for streams.

## Tests (TDD, `test_audio_extended`)
- register: INVALID without `spatial`, OK with it.
- level source, source on the listener: output bit-identical to no cue.
- straight below / above: step response of the stream model, gain applied.
- follows the listener: listener update and `set_position` change `s`.
- RESTART keeps the old amount on held PCM; the new epoch starts from a
  zero state.
- an amount stored for an unpublished revision is not used.
- stereo channels keep separate state.

## Not done
HRTF.

## Result
- RED: 6 of 7 new tests failed (level sources pass by design), 113 existing
  passed. GREEN: `test_audio_extended` 120/120.
- Mutation: 19 mutants. The mixer's `elevation_cue` flag check survived: an
  event without the cue always publishes 0, so the check and the voice flag
  were removed. The low-pass gating survived until the follow test checked
  that a level frame advances the state. One stream pattern matched twice
  and was rewritten. All then killed; the stream mutation set still passes.
- Shadow check clean.

