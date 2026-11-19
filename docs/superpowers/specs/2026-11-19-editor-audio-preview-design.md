# Design: editor audio preview playback

## Problem

The editor's Audio page (2026-11-19-editor-audio-waveform) shows the
document's PCM attachment but cannot play it. "播放" is the first item left
in `docs/cross_engine/missing_capabilities.md` (sections 10/12) after the
waveform page. The engine already has a lock-free PCM stream
(`audio_pcm_stream_open_rate` / `write_i16` / `queued` / `close`,
`src/audio/audio_extended.h`) mixed by the audio device callback.

## Change

Preview model (`engine/apps/editor/editor_audio_preview.{h,c}`, tested in
`test_editor_shell`):

- `BreakEditorAudioSink`: a small vtable the preview writes to — `open(user,
  sample_rate, channels)`, `write(user, samples, frames, *written)`,
  `queued(user, *frames)`, `close(user)`. Tests use a fake sink; the editor
  app uses the PCM stream sink below.
- `break_editor_audio_preview_play(preview, doc)`: copies the attachment (at
  most `BREAK_EDITOR_AUDIO_MAX_FRAMES`, so no allocation after create), opens
  the sink and starts at frame 0. False, leaving the state stopped, without a
  sink, without an attachment or with zero frames, or when the sink does not
  open. Playing while already playing restarts.
- `pump`: writes as many frames as the sink accepts from the cursor. The
  optional sink callback `tail_frames` reports frames the output holds back
  at the end (a resampler's lookahead): the preview writes that many frames of
  silence after the clip and, once everything is written and no more than the
  tail is queued, closes the sink and stops by itself.
- `stop`: closes the sink and stops; a no-op when stopped.
- `position_frames`: frames written minus frames still queued, at most the
  clip length (device latency is not included), 0 when stopped; length and
  rate are also 0 when stopped.
- The copy is a snapshot, so an edit during playback would play stale audio:
  the panel stops the preview when the attachment revision changes.

Shell:

- The Audio page gets a Play/Stop button (`editor-audio-play`, label
  "Play"/"Stop", "播放"/"停止"). The tick pumps the preview, stops it on a
  revision change and keeps the button label in step. While playing the info
  line ends with " | <position> / <length> s".
- `break_editor_shell_set_audio_sink(shell, sink, user)`: sets the sink
  (NULL: none, stops a running preview). Without a sink, Play logs "no audio
  output" and nothing starts.
- Accessors: `break_editor_shell_audio_playing`,
  `break_editor_shell_audio_play` (same as the button).

PCM stream sink (`engine/apps/editor/editor_audio_sink.{h,c}`, its own test
`test_editor_audio_sink` on the FAKE backend):

- `break_editor_audio_stream_sink()` returns a sink vtable whose `user` is a
  `BreakEditorAudioStreamSink` (initialised with
  `break_editor_audio_stream_sink_init(sink, as)`), backed by
  `audio_pcm_stream_open_rate` on the master bus at volume 1, with the
  sink's resampler (`resample`, LINEAR after init). Its tail is 2 frames for
  LINEAR and `AUDIO_PCM_STREAM_SINC_LOOKAHEAD + 1` for SINC: the mixer never
  consumes the last frames of a stream whose rate does not divide 48 kHz,
  because the interpolation still needs them. Rendering the
  FAKE system after a write yields the written samples / 32768 (48 kHz, so no
  resampling). Opening twice without close closes the first stream.
- `editor_main.c` creates an `AudioSystem` (default backend; FAKE during an
  input-script replay) at start-up and passes the sink to the shell; when it
  does not open, the editor runs without audio output.

## Tests

- `test_editor_shell` (fake sink that accepts at most N frames per write and
  drains on demand): Play without a sink logs and stays stopped; Play writes
  the samples in order across several pumps; position follows the drain; the
  preview stops by itself when everything is written and drained and closes
  the sink once; Stop closes; an edit during playback stops it; a sink that
  refuses to open leaves it stopped; detaching the sink stops it; the button
  label and info suffix follow the state and the language.
- `test_editor_audio_sink`: open/write/queued/close against the FAKE backend
  with rendered output checked sample by sample; invalid arguments.

## Out of scope

Seeking, looping, playing a selection, volume, a play cursor on the waveform.

## Result

- Preview: the new `test_editor_shell` case failed against a stub preview, then 209/209. Sink: both `test_editor_audio_sink` cases failed against a stub sink, then 2/2 (FAKE backend, rendered output checked sample by sample; opening more than `AUDIO_PCM_STREAM_MAX` times without close would exhaust the engine's streams).
- Mutations, each failing a test: pump ignoring the sink's accepted count, no self-stop after the drain, position ignoring the queue, no stop on a revision change, stop not closing the sink, the stream sink not closing the previous stream on open.
- `editor_main.c` creates the default `AudioSystem` after the shell and destroys it after the shell; without a device the editor runs and Play logs "no audio output".
- Review (Not ready, fixed): at 44.1 kHz and every other rate that does not divide 48 kHz, the mixer kept the last 1 (LINEAR) or 8 (SINC) frames for interpolation, `queued` never reached 0 and playback never stopped by itself. The sink now reports a tail, the preview pads the clip with that much silence and stops once only the tail is queued; the position is clamped to the clip. New `test_editor_audio_sink` case plays a clip to the end through the real stream at 8000, 22050, 44100, 48000, 88200, 96000 and 192000 Hz with both resamplers (failed before the fix). Mutations: tail 0 and SINC tail 2 both fail it; the clamp is pinned by a shell case. The test block moved above the `test_audio_capture` comment; replays use the FAKE backend. The ring is 16384 stream-rate frames (about 85 ms at 192 kHz) refilled once per tick, so a long stall at very high rates can underrun.
