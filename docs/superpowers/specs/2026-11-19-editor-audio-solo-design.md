# Design: solo one channel in the audio preview

The page now draws a lane per channel
(`2026-11-19-editor-audio-channels-design.md`), so a problem on one channel
is visible — but Play still sends both channels to the output, so it cannot
be heard on its own. Checking "is the right channel really dead or is it my
speaker" needs a way to play one channel.

## Change

Preview (`apps/editor/editor_audio_preview.h`, `.c`):

- `break_editor_audio_preview_set_solo(preview, channel)` and
  `break_editor_audio_preview_solo(preview)`, with
  `BREAK_EDITOR_AUDIO_SOLO_NONE` (UINT32_MAX) meaning "every channel", the
  state after create.
- With a solo channel on a stereo clip, the copy taken at Play holds that
  channel's samples in both output channels, so the clip is heard centred
  rather than from one side. The sink is still opened with the clip's own
  channel count, so nothing downstream has to care.
- A solo index at or above the clip's channel count is ignored at Play
  (treated as no solo), rather than refusing to play.
- The solo takes effect at the next Play, like the copy itself; it is not
  applied to audio already queued.

Panel (`apps/editor/editor_panel_audio.c`, `test_editor_shell`):

- `break_editor_shell_audio_set_solo(shell, channel)` /
  `break_editor_shell_audio_solo(shell)` forwarding to the preview.
- An `editor-audio-solo` button on the view row cycling none -> 0 -> 1 ->
  none for a stereo clip, and none -> 0 -> none for mono. Its label shows
  the state ("Solo", "Solo L", "Solo R" for stereo; "Solo" / "Solo 1" for
  mono), through the i18n table like the other labels.
- An attachment change resets the solo to none.

## Tests

- `test_editor_shell` (preview through the fake sink): a stereo clip with a
  silent left channel and a loud right one; with no solo the written frames
  interleave both; with channel 1 soloed both output channels carry the loud
  samples; with channel 0 soloed both are silent; an out-of-range solo plays
  as if none; a mono clip with channel 0 soloed is unchanged; the button
  cycles and relabels, and an attachment change resets it.

## Out of scope

Muting a channel (the inverse of solo), a per-lane mute in the drawing, a
mid-playback solo change, more than two channels.

## Result

Delivered as designed. `test_editor_shell` 224/224, the case failing to link
first.

Mutations, each failing the test: the solo branch never taken, the channel
offset dropped from the sample read, the `solo < channels` range check
replaced by "any solo set", the button's cycle jumping from channel 0 to
none, the reset on an attachment change removed, and the stereo L/R label
rule bypassed.

The label is built in the panel rather than read from a table of its own:
`BREAK_EDITOR_TR_AUDIO_SOLO_FMT` ("Solo %u" / "独奏 %u") covers mono and any
index beyond R, while the stereo case uses the two dedicated keys, so the
Chinese labels read 独奏左/独奏右 rather than a number.
