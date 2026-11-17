# Editor Audio Document Design

Status: Implemented and locally verified

## Purpose

Connect the existing offline PCM editing primitives to `BreakEditorDoc` and its real undo/redo history, without adding UI or file-format work to the same slice.

## Approaches considered

1. **Optional PCM attachment plus snapshot commands (selected).** Reuses the document's existing command stack, origin conflict rules and dirty state; exact before/after bytes make every edit reversible.
2. **A separate audio-only history stack.** Avoids touching the scene document, but duplicates undo/redo/origin/drop-oldest behavior and would complicate later shell integration; rejected.
3. **Entity/component commands for audio samples.** Misuses ECS identity for a non-entity asset and would make sample arrays component-byte payloads; rejected.

## Attachment and accessors

Add `editor_audio.h` with:

- `break_editor_doc_audio_attach(doc, sample_rate, channels, samples, frames)`;
- `break_editor_doc_audio_attached`, `audio_frames`, `audio_sample_rate`, `audio_channels` and borrowed `audio_samples` accessors;
- `audio_trim(begin,end)`, `audio_cut(begin,end)`, `audio_fade(fade_in_ms,fade_out_ms)`, `audio_normalize(target_dbfs)` and `audio_mix(source,source_frames,gain)`.

Attachment is the non-undoable initial-content operation: it requires no existing attachment, copies the input, marks the document dirty, and leaves existing scene history intact. Rate is 8000..192000, channels 1/2, frames 0..65536; samples may be NULL only for zero frames. The state allocates its fixed-capacity sample buffer once, so undo/redo and edits do not grow it.

Reset/destroy detach the attachment and release its storage; successful scene load/reset must not leave stale PCM. Borrowed samples remain valid until an audio command, reset, scene load or document destruction. No scene serialization format change is made.

## Commands

Every edit validates the attachment and arguments, then creates one command containing the exact visible before/after PCM and frame counts. `apply` copies after-state into the attachment; `revert` restores before-state. Neither allocates. A successful new command is pushed through `break_editor_cmd_stack_push_applied` and marks the document dirty.

- Trim/cut call their existing primitive on the after-copy and update its frame count.
- Fade/normalize use the attachment's rate/channels and preserve frame count.
- Mix copies the external source into the after-state through the existing clamped prefix primitive; the command does not retain the source pointer.

Commands use a new audio kind, a NULL `touched` callback (conservative conflict with every origin) and bounded operation descriptions. Allocation/validation failure returns false with document, history and PCM unchanged. Existing stack drop-oldest destroys both snapshots. Per-origin undo/redo works through the existing conservative conflict rule.

## Bounds and tests

`BREAK_EDITOR_AUDIO_MAX_FRAMES` is 65536 for this short-clip slice. Add `test_editor_audio` covering:

1. Attach validation, accessors, replacement rejection and reset/load detach.
2. Trim/cut byte-exact undo/redo and frame counts.
3. Fade/normalize/mix references, dirty state and redo-tail invalidation.
4. Origin-scoped conservative conflicts and drop-oldest snapshot destruction.
5. Invalid ranges, missing attachment, OOM and over-cap failure atomicity.

Run targeted snapshot/routing/revert mutations, ASan+UBSan, strict warnings, terminology checks, independent review and three-tree verification before push.

## Limits

Short mono/stereo clips only; full snapshots intentionally trade memory for simple exact history. No waveform UI, media decoding/encoding, VFS/asset-browser wiring, remote protocol, timeline automation or real listening verification is added. A later slice can add memory-budgeted history without changing editing semantics.
