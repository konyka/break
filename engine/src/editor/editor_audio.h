#pragma once
/* Optional short PCM attachment for BreakEditorDoc, with snapshot-based
 * undo/redo through the document's existing command stack. Owner thread. */

#include <audio/audio.h>
#include <editor/editor_doc.h>

#define BREAK_EDITOR_AUDIO_MAX_FRAMES 65536u

/* Non-undoable initial content; fails when an attachment already exists.
 * Copies the samples and marks the document dirty. */
bool break_editor_doc_audio_attach(BreakEditorDoc *doc, u32 sample_rate, u32 channels,
                                   const i16 *samples, u32 frames);
/* Reads a bounded PCM16 mono/stereo WAV file and attaches it as initial content.
 * False leaves document and history unchanged. */
bool break_editor_doc_audio_attach_wav(BreakEditorDoc *doc, const char *path);
bool break_editor_doc_audio_attached(const BreakEditorDoc *doc);
u32 break_editor_doc_audio_frames(const BreakEditorDoc *doc);
u32 break_editor_doc_audio_sample_rate(const BreakEditorDoc *doc);
u32 break_editor_doc_audio_channels(const BreakEditorDoc *doc);
/* Borrowed until an audio edit, reset/load or document destruction. */
const i16 *break_editor_doc_audio_samples(const BreakEditorDoc *doc);

/* One snapshot command per successful edit; false leaves PCM/history unchanged. */
bool break_editor_doc_audio_trim(BreakEditorDoc *doc, u32 begin, u32 end);
bool break_editor_doc_audio_cut(BreakEditorDoc *doc, u32 begin, u32 end);
bool break_editor_doc_audio_fade(BreakEditorDoc *doc, double fade_in_ms,
                                 double fade_out_ms);
bool break_editor_doc_audio_normalize(BreakEditorDoc *doc, double target_dbfs);
bool break_editor_doc_audio_mix(BreakEditorDoc *doc, const i16 *source,
                                u32 source_frames, double gain);
