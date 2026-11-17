# PCM WAV Document Import Design

Status: Implemented and locally verified

## Purpose

Allow the editor's PCM attachment to import real RIFF/WAVE files without relying on miniaudio's playback-only decoder or mixing file I/O with binary parsing.

## Approaches considered

1. **Allocation-free binary parser plus editor file adapter (selected).** The parser is independently fuzzable; the adapter owns bounded file buffers and calls the existing attach operation.
2. **Decode directly through the playback system.** Couples an offline document to device state and offers no clean buffer-validation boundary; rejected.
3. **Hand-parse directly in `editor_audio.c`.** Smaller file count but mixes filesystem failures, RIFF validation and document mutation; rejected.

## Parser API

Add `audio_wav.h`:

```c
typedef struct {
    u32 sample_rate;
    u32 channels;
    u32 frames;
} AudioWavInfo;

AudioResult audio_wav_decode_i16(const void *data, usize size, AudioWavInfo *info,
                                 i16 *samples, u32 frame_capacity);
```

The function allocates nothing and writes `info`, `samples` and actual output only after the complete file is validated. Invalid layout/unsupported format/overflow/insufficient capacity returns `AUDIO_INVALID`; NULL data/info and invalid signal pointers are rejected. A zero-frame file may use a NULL sample buffer.

## Accepted RIFF subset

- Little-endian `RIFF`/`WAVE`; `riff_size + 8` must exactly equal the input size and fit `usize`.
- Iterate chunks with `chunk_size` and the required pad byte for odd sizes; no overflow, truncation or out-of-file pad is accepted.
- Exactly one `fmt ` and one `data` chunk, in that order. `fmt` size at least 16: format tag 1, mono/stereo, rate 8000..192000, 16 bits, `block_align == channels*2`, and `byte_rate == sample_rate*block_align`. Extra fmt bytes are skipped.
- Data size is a multiple of block alignment and frames fit `u32` and `frame_capacity`. The parser has no fixed frame limit; the editor adapter enforces its 65536-frame limit. PCM samples are decoded explicitly as little-endian i16, independent of host alignment/endianness.
- Unknown chunks are safely skipped. Duplicate/misordered required chunks, trailing bytes outside RIFF and all non-PCM/compressed variants are rejected.

## Editor import

Add:

```c
bool break_editor_doc_audio_attach_wav(BreakEditorDoc *doc, const char *path);
```

The adapter requires no existing attachment and a nonempty path. It reads at most 1 MiB into editor-owned temporary storage, parses into a bounded PCM temporary, then calls `break_editor_doc_audio_attach`. All buffers are freed on every result. File/open/seek/read/size, parse, attach and allocation failures return false without changing the document or history.

The imported attachment is non-undoable initial content, exactly like direct attach. Later edits use the existing snapshot history. No asset-browser action, VFS, media saving, playback or remote protocol is added.

## Tests

- Add `test_audio_wav`: mono/stereo known samples, fmt extension and unknown odd/even chunks, zero frames, and a table of malformed sizes/signatures/format/tag/rate/alignment/capacity/duplicate/truncated inputs.
- Add one `test_editor_audio` case (5→6): real temporary WAV import, exact metadata/PCM, undo after a later trim, and missing/malformed/already-attached/OOM import failure atomicity.
- Add a manual `fuzz_audio_wav` target; run deterministic malformed-input smoke plus ASan+UBSan.
- Mutate chunk-length/padding, endian conversion, format checks and adapter rollback. Run strict warnings, terminology checks, independent review and three-tree verification before push.

## Limits

Only uncompressed PCM16 mono/stereo RIFF/WAVE. No float/8/24/32-bit, extensible, ADPCM, metadata interpretation, sample-rate conversion, VFS, waveform UI or media export. The 1 MiB adapter cap and 65536-frame document limit are intentional for this slice.
