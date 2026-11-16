# Spatial PCM streams: stereo panning (2026-11-16)

Status: Done. RED: the 5 new `test_audio_extended` tests failed on a stub
that only looked up the handle. GREEN: `test_audio_extended` 68/68,
`test_voice_playback` 4/4, the four `test_audio*` ctest entries pass.
20 mutations, all killed (4 survived first: the zero-distance guard, the
dot product normalisation, the y term and the stored enable flag; the
tests now reject NaN output, use a rolled listener with non-unit vectors,
and move a stream after panning is turned off). ASan+UBSan and three TSan
runs: no reports.

## Goal
A spatial PCM stream (network voice) only gets a distance gain: a source to
the listener's left sounds the same as one to the right
(`docs/cross_engine/missing_capabilities.md` §10 lists 声像/HRTF as
missing). This slice adds constant-power stereo panning from the listener's
orientation. HRTF stays out of scope.

## Design
- `audio_pcm_stream_set_panning(as, h, enabled)`: opt-in per stream, off at
  open, so streams and tests that exist keep their output. REJECTED for a
  stream without `set_spatial` (same rule as `set_position`); STALE /
  INVALID like the other stream calls. Disabling restores equal gains of 1.
- Listener right vector = `forward x up` (forward -Z, up +Y gives +X, the
  miniaudio / OpenGL convention). `pan = dot(unit(source - listener),
  unit(right))`, clamped to [-1, 1]; 0 when the source sits on the listener
  or the basis is degenerate (forward parallel to up).
- Constant-power law: `theta = (pan + 1) * pi / 4`, left `cos(theta)`,
  right `sin(theta)`. Centre is -3 dB on each side (0.7071), a hard-side
  source is 1 on that side and 0 on the other. Front and back are not told
  apart (no HRTF, no delay).
- Left and right gains are published together in one 64-bit atomic
  (`pan_bits`, two f32 bit patterns) so the mixer never sees a half update;
  computed on the owner thread in `pcm_stream_publish_spatial`, which
  already runs on `set_spatial`, `set_position` and listener updates.
- Mixer: the left output sample is scaled by the left gain and the right by
  the right gain; a mono stream is duplicated first, so it pans.

## Tests (TDD, `test_audio_extended`)
- arguments: REJECTED before `set_spatial`, INVALID for null / zero handle,
  STALE after close.
- hard right / hard left / straight ahead, with the distance gain.
- 45 degrees front-right: cos / sin of 3*pi/8 (computed in the test).
- listener turns: the same source moves from centre to hard left.
- stereo stream: each channel is scaled by its side's gain.
- disable restores equal gains; reopen starts with panning off.
- degenerate: source on the listener, forward parallel to up -> centre.
- streams without panning: unchanged (the existing spatial tests).

## Not done
HRTF, interaural delay, front/back cues, panning for clip events (the
extended event voices), surround output.
