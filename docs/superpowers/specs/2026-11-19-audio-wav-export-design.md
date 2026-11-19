# Design: PCM16 WAV export for the audio library and the editor

## Problem

`audio_wav_decode_i16` imports PCM16 WAV and `break_editor_doc_audio_attach_wav`
attaches it to an editor document, but nothing writes WAV back: an edited
attachment cannot leave the editor. "导出" (export) is listed as missing in
`docs/cross_engine/missing_capabilities.md` (section 10/12) and
`docs/design/audio_extended.md`.

## Change

- `audio_wav_encoded_size(channels, frames, *out_size)`: 44 + frames * channels
  * 2 bytes; INVALID for channels other than 1/2 or a size above UINT32_MAX - 8.
- `audio_wav_encode_i16(info, samples, out, capacity, *out_size)`: writes the
  canonical 44-byte RIFF/WAVE header (fmt chunk of 16 bytes, PCM, 16 bits) and
  little-endian samples. Validates exactly what the decoder accepts (rate
  8000..192000, 1 or 2 channels); INVALID for NULL, a bad info, NULL samples
  with frames > 0, or a capacity below the encoded size; nothing is written on
  failure. Output decodes back to the same info and samples.
- `break_editor_doc_audio_save_wav(doc, path)`: encodes the current attachment
  and writes it through a temporary file `<path>.tmp` renamed over `path`, so a
  failed write never leaves a truncated file at `path`. False when there is no
  attachment, for NULL/empty path, or on any I/O or allocation failure; the
  document (samples, history, dirty flag) is never changed.

## Tests

- `test_audio_wav`: header bytes of a known mono and stereo file; round trip
  through the decoder for mono/stereo/zero frames; every invalid argument and
  short capacity leaves the output untouched; size overflow.
- `test_editor_audio`: attach, edit, save, re-attach into a fresh document and
  compare samples; no attachment / NULL path / unwritable directory fail without
  changing the document or creating the target; allocation failures are atomic
  and leave no file.

## Out of scope

Other formats (compressed, 24/32-bit, float), VFS integration, waveform UI.

## Result

- Encoder: three new `test_audio_wav` cases failed against stubs, then 7/7. Editor save: the new `test_editor_audio` case failed against a stub, then 7/7.
- Mutations: wrong RIFF size field, capacity check skipped, overflow check skipped, writing the target in place, temporary file kept on failure. Each fails a test; the last one survived until a case where the rename fails (the target is a directory) was added.
- Review (Ready): the suggestion to write through `platform_atomic_writer` was declined. `break_editor` and `break_editor_test` deliberately do not compile `platform_fs.c` (its single owner is the engine target), and `editor_scene.c` saves scenes with the same "<path>.tmp" + rename helper, so the export stays consistent with it. Added regression cases instead: mono round trip, a stale "<path>.tmp" from an earlier crash is truncated rather than appended to, a path whose temporary would exceed `BREAK_EDITOR_SCENE_PATH_CAPACITY` fails without creating anything, and the exact 64-bit RIFF size boundary of `audio_wav_encoded_size`.
