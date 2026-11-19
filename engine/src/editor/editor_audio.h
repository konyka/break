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
/* Writes the current attachment as a canonical PCM16 WAV file: encoded in
 * memory, written to "<path>.tmp", then renamed over path, so a failure never
 * leaves a partial file at path. False without an attachment, for a NULL or
 * empty path, or on any allocation or I/O failure (the temporary file is
 * removed). Never changes the document, its history or its dirty flag. */
bool break_editor_doc_audio_save_wav(const BreakEditorDoc *doc, const char *path);
bool break_editor_doc_audio_attached(const BreakEditorDoc *doc);
u32 break_editor_doc_audio_frames(const BreakEditorDoc *doc);
u32 break_editor_doc_audio_sample_rate(const BreakEditorDoc *doc);
u32 break_editor_doc_audio_channels(const BreakEditorDoc *doc);
/* Borrowed until an audio edit, reset/load or document destruction. */
const i16 *break_editor_doc_audio_samples(const BreakEditorDoc *doc);

#define BREAK_EDITOR_AUDIO_WAVEFORM_MAX_COLUMNS 4096u
/* Changes whenever the attachment changes: attach, each committed edit, undo
 * and redo of an audio command, detach (reset/load). Stored in the document,
 * so it never repeats across attachments. 0 for NULL. */
u64 break_editor_doc_audio_revision(const BreakEditorDoc *doc);
/* Min/max over all channels for `columns` contiguous frame ranges: column c
 * covers [c*frames/columns, (c+1)*frames/columns); an empty range (columns >
 * frames) uses the frame at c*frames/columns. False, writing nothing, for
 * NULL arguments, no attachment, zero frames or columns outside
 * 1..BREAK_EDITOR_AUDIO_WAVEFORM_MAX_COLUMNS. Read-only. */
bool break_editor_doc_audio_waveform(const BreakEditorDoc *doc, u32 columns,
                                     i16 *out_min, i16 *out_max);
/* The same over frames [begin, end) only (the whole clip for 0..frames);
 * false and nothing written for an empty or out-of-clip range. */
bool break_editor_doc_audio_waveform_range(const BreakEditorDoc *doc, u32 begin, u32 end,
                                           u32 columns, i16 *out_min, i16 *out_max);
/* The same over one channel's samples only, so a stereo clip can be drawn
 * as two traces. False and nothing written for a channel at or above the
 * clip's channel count, plus the cases above. */
bool break_editor_doc_audio_waveform_channel(const BreakEditorDoc *doc, u32 channel,
                                             u32 begin, u32 end, u32 columns,
                                             i16 *out_min, i16 *out_max);

/* Largest absolute sample and RMS over frames [begin, end), across every
 * channel, as doubles in [0, 32768]. False and nothing written for the same
 * invalid ranges as the waveform functions. Read-only. */
bool break_editor_doc_audio_peak_range(const BreakEditorDoc *doc, u32 begin, u32 end,
                                       double *out_peak, double *out_rms);

/* Largest absolute value of the signal reconstructed at 4x the sample rate
 * over frames [begin, end), per channel (dBTP measurement). May exceed
 * 32768: a reconstruction can overshoot full scale. Same invalid ranges as
 * above. Read-only. */
bool break_editor_doc_audio_true_peak_range(const BreakEditorDoc *doc, u32 begin, u32 end,
                                            double *out_peak);

/* Gated integrated loudness of frames [begin, end) in LUFS, following
 * ITU-R BS.1770-4's structure (K-weighting, 400 ms blocks with 75% overlap,
 * -70 LUFS absolute gate then a -10 LU relative gate). Coefficients are
 * derived for the clip's own sample rate. False and nothing written for the
 * invalid ranges above and for a range shorter than one block; a silent
 * range reports the -70 floor. Read-only. */
#define BREAK_EDITOR_AUDIO_LUFS_FLOOR (-70.0)
bool break_editor_doc_audio_loudness_range(const BreakEditorDoc *doc, u32 begin, u32 end,
                                           double *out_lufs);
/* Short-term loudness: the last 3 seconds of [begin, end) in LUFS. False
 * for a range shorter than that window. */
bool break_editor_doc_audio_short_term_range(const BreakEditorDoc *doc, u32 begin, u32 end,
                                             double *out_lufs);
/* Loudness range (EBU R128) in LU, from 3-second windows stepped by 1 s:
 * the 95th percentile minus the 10th, after a -70 LUFS absolute gate and a
 * -20 LU relative gate. False for a range with fewer than two surviving
 * windows. */
bool break_editor_doc_audio_loudness_range_lra(const BreakEditorDoc *doc, u32 begin,
                                               u32 end, double *out_lra);

/* One snapshot command per successful edit; false leaves PCM/history unchanged. */
bool break_editor_doc_audio_trim(BreakEditorDoc *doc, u32 begin, u32 end);
bool break_editor_doc_audio_cut(BreakEditorDoc *doc, u32 begin, u32 end);
bool break_editor_doc_audio_fade(BreakEditorDoc *doc, double fade_in_ms,
                                 double fade_out_ms);
bool break_editor_doc_audio_normalize(BreakEditorDoc *doc, double target_dbfs);
/* fade / normalize applied to frames [begin, end) only (the normalize peak
 * is measured there); frames outside are unchanged. One undoable snapshot
 * command each; false and no change for an empty or out-of-clip range or the
 * whole-clip calls' invalid arguments. */
bool break_editor_doc_audio_fade_range(BreakEditorDoc *doc, u32 begin, u32 end,
                                       double fade_in_ms, double fade_out_ms);
bool break_editor_doc_audio_normalize_range(BreakEditorDoc *doc, u32 begin, u32 end,
                                            double target_dbfs);
bool break_editor_doc_audio_mix(BreakEditorDoc *doc, const i16 *source,
                                u32 source_frames, double gain);
