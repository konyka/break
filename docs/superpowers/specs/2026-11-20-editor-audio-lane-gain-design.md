# Design: per-lane amplitude zoom

The amplitude zoom (`2026-11-19-editor-audio-gain-design.md`) is one factor
for the whole page. A stereo clip whose channels differ by 20 dB — a loud
dialogue track and a quiet room tone, say — cannot show both envelopes at
once: the factor that reveals one flattens or clips the other.

## Change

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- The gain becomes per lane, stored as one factor per lane (up to the 2
  lanes the document allows). The existing page-wide calls keep working:
  `editor_panel_audio_set_gain` sets every lane, and
  `editor_panel_audio_gain` reports lane 0's.
- `break_editor_shell_audio_set_lane_gain(shell, lane, gain)` and
  `break_editor_shell_audio_lane_gain(shell, lane)` address one lane, with
  the same power-of-two snap and [1, 32] clamp. An out-of-range lane is
  rejected (returns 0 and changes nothing).
- `break_editor_shell_audio_fit_lane_gain(shell, lane)` fits one lane to its
  own visible peak; `..._fit_gain` keeps fitting every lane, each to its own
  peak, which is what makes the two channels comparable in one look.
- The paint and the dB grid use the lane's own factor, so each lane's grid
  moves with that lane.
- An attachment change resets every lane to 1x, as before.
- The info line's "<n>x" suffix shows lane 0's factor when the lanes agree,
  and "<a>x/<b>x" when they do not, so a per-lane setting is visible.

## Tests

`test_editor_shell`:

- A stereo clip with a loud left and a quiet right channel: fitting the page
  gives the two lanes different factors, each matching its own peak.
- `set_lane_gain` on one lane leaves the other alone; the page-wide setter
  sets both; an out-of-range lane returns 0 and changes nothing.
- `lane_gain(0)` equals `gain()` after a page-wide set.
- The grid of lane 1 follows lane 1's factor (its entries are the levels
  that fit at that factor, not lane 0's).
- The info line reads "4x" when both lanes are 4, and "4x/8x" when they
  differ.
- An attachment change puts both back to 1.

## Out of scope

More than two lanes, a per-lane solo or mute (those already exist on the
preview), remembering a lane's factor across attachments.

## Result

Delivered as designed. `test_editor_shell` 228/228, the case failing to link
first.

Mutations, each failing the test: the paint scale using lane 0's factor for
every lane, an out-of-range lane clamped to 0 instead of rejected, the info
suffix always treating the lanes as uniform, the page-wide fit calling the
per-lane fit with 0 every time, and the page-wide setter writing lane 0 every
time.

**The grid model had to grow a lane index.** It recorded lane 0's lines only,
so "each lane's grid uses that lane's factor" had no observable consequence
and the paint-scale mutation survived. The model now records every lane and
`break_editor_shell_audio_grid_lane` reports which lane an entry belongs to;
the grid case asserts the lane of each entry, and the lane-gain case checks
that lane 1 at 8x draws a different level set than lane 0 at 1x.
`EDITOR_AUDIO_GRID_MAX` went from 8 to 16 for the second lane.
