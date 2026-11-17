# Event voices: interaural time difference (2026-11-17)

Status: Done

## Goal
`audio_pcm_stream_set_interaural_delay` delays the far ear of a spatial PCM
stream. Spatial event voices should get the same cue, opted in per event.

## Design
- `AudioEventDesc.interaural_delay` requires `spatial`, otherwise
  `audio_event_register` returns `AUDIO_INVALID`.
- The signed frame count comes from the stream's `interaural_delay_frames`
  (Woodworth model, 0..31, positive delays the left ear); 0 when the event
  has the cue off.
- Same protocol as the pan and the rear cue. START carries the initial
  count (`spatial_itd`) and does not write the snapshot. Later position and
  listener updates store `itd_snapshot = spatial_pack(revision, frames)`
  before the gain CAS. The mixer takes a count only with the gain revision
  it belongs to, so a RESTART's new count never reaches the old epoch's PCM.
- Each voice has its own 64-frame delay line, zeroed when START is drained.
  The delay sits after the rear cue and before gain and pan, as for
  streams. Streams and voices share one push helper.
- `spatial_publish` takes the count as a new argument.

## Tests (TDD, `test_audio_extended`)
- `event_interaural_delay_requires_spatial`
- far ear late by 31 frames on the right and on the left; in front, behind
  and on the listener the output equals the cue off, bit for bit.
- the listener turning removes the delay; moving the source back to the
  side delays real history (a looping clip), not zeros.
- RESTART keeps the old count on held PCM, and the new epoch's line starts
  from silence.
- a count stored for a revision not yet published is not used.
- a stereo clip delays the far ear's own channel.

## Not done
HRTF, elevation cues. (Delay changes are smoothed: see
`2026-11-17-audio-itd-crossfade.md`.)

## Result
- RED: the new tests failed to compile (no desc field, no voice state,
  `spatial_publish` without the count). GREEN: `test_audio_extended` 105/105.
- Mutation: 16 mutants on the voice path, 1 survived the first round
  (reading the snapshot without checking the event's flag). A test now
  stores a count under the revision the mixer adopts next on a voice with
  the cue off; the mutant is killed, 16/16. The 7 stream mutants were rerun
  on the shared `itd_line_push`, 7/7 killed.

