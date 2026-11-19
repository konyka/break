# Design: timeline ruler on the Audio page

## Problem

The waveform has no time scale: the only times shown are the info line's
position and selection. "时间线" is the last interaction gap of the waveform
editor (`docs/cross_engine/missing_capabilities.md`, section 10/12).

## Change

A tick model in `apps/editor/editor_panel_audio.c`, so the labels and
positions are tested without painting:

- `editor_panel_audio_ticks(panel, *out)` fills a bounded
  `EditorAudioTicks` (at most 32 entries) describing the ruler for the
  current clip and widget width: each tick has a frame, an x in pixels and a
  label.
- The step is the smallest value from a fixed ladder (1, 2, 5, 10, 20, 50,
  100, 200, 500 ms, then 1, 2, 5, 10, 20, 30, 60, 120, 300 s) that keeps the
  ticks at least 60 px apart, so labels never overlap. With no attachment,
  zero frames or a width below 1 px the count is 0.
- Labels: "<s>.<ms> s" below 10 s (for example "0.250 s"), "<m>:<ss>" from
  10 s (for example "1:30"), always the exact tick time. The ruler's time
  span is bounded by `BREAK_EDITOR_AUDIO_MAX_FRAMES` (8.192 s at 8 kHz), so
  the minute form only appears for low sample rates.
- The first tick is at frame 0; the last one is the last multiple of the
  step inside the clip.
- The page shows the ruler as a 16 px strip (`editor-audio-ruler`) directly
  above the waveform, repainted with it: a line at each tick and the label
  to its right, in the theme's secondary text colour.

## Tests

`test_editor_shell`: with a 0.5 s clip at the default width the step is a
ladder value whose spacing is the first at least 60 px (the next smaller one
would be narrower), every tick lies inside the clip at
`frame * width / frames`, the labels are the exact tick times, and the count
matches the step; the longest clip at 8 kHz steps by 1 s; the count is 0
without an attachment; the strip exists, matches the waveform width and
paints.

## Out of scope

Zoom and scroll (the ruler always spans the whole clip), snapping the
selection to ticks, beat or sample units.

## Result

- RED: the new `test_editor_shell` case failed with no ruler widget, then 214/214.
- Mutations, each failing the test: the 60 px rule dropped (smallest step always), a tick at `frames` (outside the clip), the x position off by one, the seconds/minutes threshold wrong.
