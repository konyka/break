# Design: mute one channel in the audio preview

Solo (`2026-11-19-editor-audio-solo-design.md`) answers "what does this
channel alone sound like". The inverse question — "what does the mix sound
like without this channel" — needs a mute, and for a stereo clip the two are
not interchangeable: soloing the left channel plays it in both outputs
(centred), while muting the right one keeps the left where it is and leaves
the right silent.

## Change

Preview (`apps/editor/editor_audio_preview.h`, `.c`):

- `break_editor_audio_preview_set_mute(preview, channel)` and
  `break_editor_audio_preview_mute(preview)`, with
  `BREAK_EDITOR_AUDIO_MUTE_NONE` (UINT32_MAX) meaning "nothing muted", the
  state after create.
- With a muted channel, the copy taken at Play zeroes that channel and
  leaves the others in place; the channel count and the position mapping are
  unchanged.
- A mute index at or above the clip's channel count is ignored at Play, like
  an out-of-range solo.
- Mute and solo are independent fields but cannot both act: solo already
  replaces every channel with one, so when a solo is in effect the mute is
  not applied. The preview keeps both values; only the application is
  ordered (solo first, and if it applied, mute is skipped).

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- `break_editor_shell_audio_set_mute(shell, channel)` /
  `break_editor_shell_audio_mute(shell)`.
- An `editor-audio-mute` button on the view row cycling the same way the
  Solo button does (none -> 0 -> 1 -> none for stereo, none -> 0 -> none
  for mono), labelled "Mute" / "Mute L" / "Mute R" / "Mute <n>" through the
  i18n table.
- An attachment change resets the mute, like the solo.

## Tests

`test_editor_shell` through the fake sink, a stereo clip with a loud left
and a louder right channel:

- No mute: both channels go out unchanged.
- Mute channel 1: the left samples stay, the right are zero.
- Mute channel 0: the mirror image.
- An out-of-range mute plays as if none.
- With both a solo and a mute set, the solo wins (both outputs carry the
  soloed channel, not silence).
- A mono clip with channel 0 muted is silent.
- The button cycles and relabels, and an attachment change resets it.

## Out of scope

Muting several channels at once, a mute in the drawing (the lanes keep
showing the data), a mid-playback change, more than two channels.

## Result

Delivered as designed. `test_editor_shell` 225/225, the case failing to link
first.

Mutations, each failing the test: the mute branch never taken, the channel
offset dropped from the write, the `mute < channels` range check replaced by
"any mute set", the reset on an attachment change removed, the solo branch
made conditional on no mute (which would let the mute win), and the cycle
jumping from channel 0 to none.

The range-check mutation first survived: with a single-frame assertion, an
out-of-range index writes into a later frame's samples and the first frame
still reads correctly. The case now checks every frame of the out-of-range
run, which is also the honest statement of what "ignored" has to mean.

Solo and Mute now share `audio_panel_label_channel` and
`audio_panel_cycle_channel`; the Solo slice's hand-written versions were
replaced rather than copied, so the two buttons cannot drift apart.
