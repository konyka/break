# Editor Audio Document Implementation Plan

> **For agentic workers:** REQUIRED SUB-SKILL: Use superpowers:subagent-driven-development (recommended) or superpowers:executing-plans to implement this plan task-by-task. Steps use checkbox (`- [ ]`) syntax for tracking.

Status: Complete

**Goal:** Add optional PCM attachments to `BreakEditorDoc` with exact undoable trim/cut/fade/normalize/mix commands.

**Architecture:** `editor_audio.c` owns a fixed-capacity attachment and snapshot-command implementation. Commands reuse the existing document stack, conservative origin conflicts and dirty state; apply/revert only copy precomputed bytes.

**Tech Stack:** C11, existing editor command stack, `audio_edit`, CMake/CTest, libm.

## Global Constraints

- Follow `docs/superpowers/specs/2026-11-18-editor-audio-document-design.md`.
- `BREAK_EDITOR_AUDIO_MAX_FRAMES=65536`; mono/stereo; 8000..192000 Hz.
- Validation/OOM leaves document, PCM and history unchanged; apply/revert allocate nothing.
- No UI, media file codec, scene format, asset-browser or remote-protocol change.

### Task 1: Public surface and RED

**Files:** create `engine/src/editor/editor_audio.h`, `engine/src/editor/editor_audio.c`, `engine/tests/test_editor_audio.c`; modify `engine/src/editor/editor_internal.h`, `engine/src/editor/editor_doc.c`, `engine/src/editor/editor_scene.c`, `engine/CMakeLists.txt`.

- [x] Declare the exact attach/accessor/edit API from the spec and add the audio command kind/state lifecycle hooks.
- [x] Add `editor_audio.c` plus `audio_edit.c` to production/test editor libraries; register `test_editor_audio` with `headless;editor` labels and update the target contract.
- [x] Add five tests for attach/reset/load, trim/cut undo/redo, fade/normalize/mix, origin/drop-oldest behavior, and invalid/OOM/over-cap atomicity.
- [x] Reconfigure and build/run the new target; observed RED on the new document entry points.

### Task 2: Attachment and snapshot commands

**Files:** modify `engine/src/editor/editor_audio.c` and the lifecycle/internal files above.

- [x] Implement fixed-capacity attach/accessors and detach on reset/successful scene load/destroy without changing unrelated scene data.
- [x] Implement a snapshot command with before/after buffers and frame counts; destroy releases both, apply/revert copy bytes without allocation, and `touched=NULL` gives conservative origin conflicts.
- [x] Route all five operations through their real `audio_edit` primitive on the after-copy, then apply/push/mark dirty. Validate every range/scalar before snapshot allocation and every allocation before document mutation.
- [x] Rebuild/run `test_editor_audio`; observed 5/5. Production `break_editor`, existing editor command/scene tests and the updated target contract pass.

### Task 3: Verification and delivery

**Files:** update `docs/design/audio_extended.md`, `docs/Implementation_Status.md`, `docs/cross_engine/missing_capabilities.md`, and this slice's spec/plan.

- [x] Mutate before/after copy routing, frame counts, origin conflict tagging, detach and snapshot destruction; all fail focused tests or ASan.
- [x] Run focused ASan+UBSan, OOM sweeps and strict `-Wall -Wextra -Wshadow -Wdouble-promotion -pedantic` checks for changed sources.
- [x] Run added-line terminology checks and independent read-only review; all findings were fixed and re-review is Ready.
- [x] Incrementally update documents and commit as `editor: add undoable PCM document edits`.
- [x] Run `/tmp/full_trees.sh`; observed 431/431, 431/431 and 439/439 because one CTest target is added. Verify actual counts, push `master` after green and inspect both new CI runs.

## Result

Implementation, review and verification are complete. Normal and ASan+UBSan tests pass 5/5, strict warnings and terminology checks are clean, six normal mutants and the snapshot-leak mutant are killed. Review found target-contract, prevalidation and origin-success gaps; all were fixed and scoped re-review is Ready. The three full trees pass 431/431, 431/431 and 439/439. Remote CI inspection follows the push.
