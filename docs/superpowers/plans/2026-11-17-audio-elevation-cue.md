# Spatial PCM streams: elevation cue (2026-11-17)

Status: Done

## Goal
Panning, the rear cue and the interaural delay say nothing about height: a
source above the listener and one below sound the same
(`docs/cross_engine/missing_capabilities.md` §10, "高度提示"). Without HRTF,
a cheap cue is spectral tilt: sound from above keeps more top end (pinna
reflections), sound from below loses it (torso shadow). This slice adds an
opt-in tilt filter that follows the source's height relative to the
listener's up vector.

## Design
- `audio_pcm_stream_set_elevation_cue(as, h, enabled)`: REJECTED for a
  stream without `set_spatial`; INVALID/STALE like the other setters; off at
  open.
- Elevation `e = cos(angle(source - listener, up))` in -1..1; 0 for a source
  on the listener or a zero up vector.
- Tilt amount `s = e * AUDIO_PCM_STREAM_ELEVATION_BOOST` (0.5) above,
  `s = e` below.
- Per channel a one-pole low-pass `lp += a (x - lp)` with a fixed
  `a = 1 - exp(-2 pi AUDIO_PCM_STREAM_ELEVATION_CUTOFF_HZ / 48000)` (7 kHz)
  always runs, and the output is `x + s (x - lp)`: a high-shelf boost
  above, a blend towards the low-pass below (straight below gives `lp`).
  `s = 0` passes the frame exactly; since the low-pass always runs, the cue
  engaging later starts from the current signal.
- The owner thread computes `s` with the other spatial values and publishes
  it as one atomic f32; the mixer reads it once per callback and applies the
  tilt after the rear cue and before the interaural delay. The state is
  mixer-owned like `pos`; open resets it.

## Tests (TDD, `test_audio_extended`)
- arguments: REJECTED without spatial, INVALID handle or system, STALE.
- level with the listener, on the listener, zero up vector: output exactly
  as without the cue, published `s` exactly 0.
- straight below: the step response is the one-pole model.
- straight above: the step response is `x + 0.5 (x - lp)`.
- 30 degrees up and a non-unit up vector: `s = 0.5 * 0.5`.
- the listener turns over: below becomes above.
- a 24 kHz tone below is attenuated, above it is boosted.
- stereo channels keep separate state; reopen resets the cue and state;
  disabling it passes the signal exactly again.

## Not done
HRTF, the elevation cue on event voices.

## Result
- RED: 5 of 6 new tests failed against a stub (level sources pass by design),
  107 existing passed. GREEN: `test_audio_extended` 113/113.
- Mutation: 21 mutants. The `e == 0` early return and the two clamps to
  -1..1 survived; they are redundant (e = 0 already gives s = 0 and the
  cosine of two finite vectors stays within -1..1 up to rounding that the
  filter tolerates), so they were removed. The up-vector sign pattern
  matched twice and was rewritten; it is killed. All others killed.
- Shadow check clean; full trees: see the commit.

