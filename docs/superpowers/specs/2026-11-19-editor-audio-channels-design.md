# Design: per-channel waveform display

`break_editor_doc_audio_waveform_range` reduces every channel of a frame
into one min/max pair, so a stereo clip is drawn as a single merged trace.
The two channels cannot be told apart, and a problem on one of them (a dead
right channel, a phase inversion) is invisible.

## Change

Core (`src/editor/editor_audio.h`, `.c`, `test_editor_audio`):

- `break_editor_doc_audio_waveform_channel(doc, channel, begin, end, columns,
  out_min, out_max)`: the same per-column min/max, but over one channel's
  samples only. False, writing nothing, for a channel index at or above the
  clip's channel count, plus the same invalid arguments as the existing
  functions.
- `break_editor_doc_audio_waveform_range` keeps its merged behaviour, so
  every existing caller is unaffected.

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- The panel holds columns per channel (up to the 2 the document allows) and
  fills them with the per-channel function.
- A stereo clip draws two stacked lanes, each half the widget's height with
  its own centre line; a mono clip keeps one full-height lane, so the
  existing look does not change for mono.
- The selection band, the cursor line and the ruler are unchanged: they span
  the full height across both lanes.
- `break_editor_shell_audio_lane_count(shell)` reports the number of lanes
  (0 without an attachment), and `break_editor_shell_audio_lane_column(shell,
  lane, i, *min, *max)` reads one lane's column, so the test can check the
  two channels independently. The existing `..._audio_column` keeps reading
  lane 0.

## Tests

- `test_editor_audio`: a stereo clip whose left channel is silent and whose
  right is loud; the per-channel function reports that, the merged one still
  reports the union, and the invalid channel index writes nothing.
- `test_editor_shell`: a mono clip reports one lane; a stereo clip reports
  two, with lane 0 silent and lane 1 loud; the lanes follow the view (zoom
  in and both lanes' columns come from the zoomed part); an attachment
  change from stereo to mono drops back to one lane.

## Out of scope

More than two channels (the document rejects them), a per-channel mute or
solo, independent amplitude zoom per lane, a lane divider style.

## Result

Delivered as designed. `test_editor_audio` 14/14 and `test_editor_shell`
222/222, both after a failing run (the core one failed to link, the panel one
on the missing lane count).

Six mutations each fail a test: the per-channel stride dropped back to 1, the
channel offset dropped, the channel-range guard removed, the lane height not
divided by the lane count, every lane drawn at the same centre line, and the
lane count pinned to 1.

Three things the tests had to account for:

- An existing case (`audio_page_opens_wav_assets_and_follows_edits`) compared
  `audio_column` against the merged whole-clip waveform. With lanes that
  column is channel 0, so the case now compares against
  `..._waveform_channel(doc, 0, ...)` and checks the right lane is its
  negation, which is what that fixture's data actually is.
- A square wave that is constant within a column has `min == max`, so it
  draws as a 1 px line and says nothing about the lane height. The lane test
  alternates the right channel every frame so each column spans a real range.
- Once the view is shorter than the widget is wide, a column holds a single
  frame, so an alternating signal reads either `+amp` or `-amp` rather than
  both. The zoomed assertions allow either.
