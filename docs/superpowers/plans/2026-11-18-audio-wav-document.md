# PCM WAV Document Import Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: In progress

**Goal:** Import validated PCM16 mono/stereo RIFF/WAVE files into the editor's undoable PCM attachment.

**Architecture:** An allocation-free `audio_wav` parser validates the complete buffer before decoding. A bounded editor adapter owns file/PCM temporary buffers and commits through the existing attach API.

**Tech Stack:** C11, RIFF little-endian parsing, `BreakEditorDoc`, CMake/CTest and a manual fuzz target.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-18-audio-wav-document-design.md`.
- Parse without allocation; reject every malformed/overflow/truncated/unsupported layout before writing outputs.
- Adapter limit 1 MiB; document limit 65536 frames; import failure leaves document/history unchanged.
- No VFS, playback, waveform UI, export or remote-protocol work.

### Task 1: Parser/adapter APIs and RED

**Files:** create `engine/src/audio/audio_wav.{h,c}`, `engine/tests/test_audio_wav.c`, `engine/tests/fuzz_audio_wav.c`; modify `engine/src/editor/editor_audio.{h,c}`, `engine/tests/test_editor_audio.c`, `engine/CMakeLists.txt`.

- [ ] Declare the exact parser and `break_editor_doc_audio_attach_wav` interfaces from the spec.
- [ ] Register `test_audio_wav` with `headless;audio`, add the parser to production/test libraries, and add manual `fuzz_audio_wav` without a new CTest entry.
- [ ] Add parser tests for mono/stereo, extended fmt, unknown odd/even chunks, zero frames and the full malformed-input table; add one editor import/undo/failure/OOM test (5→6).
- [ ] Reconfigure/build both test targets; expected RED is undefined `audio_wav_decode_i16` and `break_editor_doc_audio_attach_wav` only.

### Task 2: Validation, decoding and import

**Files:** modify `engine/src/audio/audio_wav.c` and `engine/src/editor/editor_audio.c`.

- [ ] Implement checked little-endian reads, RIFF size equality, chunk/pad iteration, single ordered fmt/data, PCM format/rate/alignment/capacity checks and explicit i16 decode.
- [ ] Implement bounded file read and PCM temporary allocation with editor OOM hooks; decode, attach, then free all temporaries on every path.
- [ ] Rebuild/run `test_audio_wav` and `test_editor_audio`; expected 4/4 and 6/6. Build production editor and fuzz targets.

### Task 3: Fuzz, verification and delivery

**Files:** update `docs/design/audio_extended.md`, `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, the editor-audio spec/plan and this slice's spec/plan.

- [ ] Mutate RIFF size, chunk/pad bounds, format/alignment checks, little-endian decode and adapter rollback; every mutation must fail focused tests or sanitizer/fuzz.
- [ ] Run both suites under ASan+UBSan and `fuzz_audio_wav` with deterministic mixed valid/malformed inputs; run strict `-Wall -Wextra -Wshadow -Wdouble-promotion -pedantic` checks.
- [ ] Run added-line terminology checks and independent read-only review; fix Critical/Important findings through failing tests first.
- [ ] Incrementally update documents and commit as `editor: import PCM WAV attachments`.
- [ ] Run `/tmp/full_trees.sh`; expected 432/432, 432/432 and 440/440 because only `test_audio_wav` is added. Verify actual counts, push `master` after green and inspect both new CI runs.

## Result

Design and plan only; implementation and RED have not started.
