# Spatial events: stereo panning (2026-11-16)

Status: Done

## Goal
Spatial PCM streams can pan (`audio_pcm_stream_set_panning`), but spatial
clip events only get a distance gain. This slice gives events the same
constant-power pan, opt-in per event definition.

## Design
- `AudioEventDesc.panned`: needs `spatial`, else `audio_event_register`
  returns `AUDIO_INVALID`. A zeroed desc (every caller that exists, music)
  stays unpanned, so its output is unchanged.
- The pan value (-1 left .. 1 right) uses the same model as streams: the
  source direction against the listener's right vector (`forward x up`);
  centre for a source on the listener or a degenerate basis. Streams and
  events share one `listener_pan` and one `audio_pan_gains`
  (`theta = (pan + 1) pi / 4`, left cos, right sin).
- START carries the initial pan with the initial spatial gain and does not
  store `pan_snapshot`: `spatial_begin_start` moves the gain revision while
  keeping the old gain, and the old epoch may adopt that revision; its PCM
  must keep the old pan as well.
- Later updates (`audio_voice_set_position`, listener moves) keep the
  existing gain snapshot protocol: the publisher first stores
  `pan_snapshot = (revision, pan)` with the revision it is about to
  publish, then CASes the gain snapshot. The mixer, when it adopts gain
  revision R, takes the pan only if `pan_snapshot` also holds R; otherwise
  a newer publish is half done and it keeps the previous pan until it
  adopts that revision. So a restarted voice's new pan never reaches the
  old epoch's PCM, as the gain already does not.
- The mixer scales left and right before the voice DSP chain. Unpanned
  voices skip it.

## Tests (TDD, `test_audio_extended`)
- registration: `panned` without `spatial` is INVALID.
- hard right at trigger, hard left after `set_position`, listener turn.
- restart of a held voice: the old PCM keeps its pan and gain, the new
  epoch gets the new ones.
- half-done publish (pan snapshot one revision ahead): the gain is adopted,
  the pan is kept.
- stereo clip: each channel by its side's gain.
- unpanned spatial events: unchanged (existing tests).

## Not done
HRTF, interaural delay, front/back cues, surround output.

## Result
- RED: 5 new tests failed, 68 existing passed. GREEN: `test_audio_extended`
  73/73, `test_voice_playback` 4/4.
- Mutation: 21 mutants in the first round, 3 survived. Two were redundant
  code (a `pan_snapshot` store in START, the pan-gain init to 1.0 that
  START always overwrites) and were removed; the third (listener pan) got a
  listener-turn-only assertion. Final run: 19 mutants, all killed.
- ASan+UBSan and three TSan runs: no reports.
