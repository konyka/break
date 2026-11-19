#pragma once
/* Plays a snapshot of the document's PCM attachment through a sink (design
 * 2026-11-19-editor-audio-preview). The preview copies the attachment on
 * play, then each pump writes as many frames as the sink accepts; once all
 * frames are written and the sink has drained, it closes the sink and stops.
 * One allocation at create (BREAK_EDITOR_AUDIO_MAX_FRAMES stereo frames).
 * Shell thread only. */

#include <core/types.h>
#include <editor/editor_doc.h>

typedef struct BreakEditorAudioSink {
    bool (*open)(void *user, u32 sample_rate, u32 channels);
    /* Copies up to `frames` interleaved frames; reports how many fit. */
    bool (*write)(void *user, const i16 *samples, u32 frames, u32 *out_written);
    /* Frames written but not played yet. */
    bool (*queued)(void *user, u32 *out_frames);
    void (*close)(void *user);
} BreakEditorAudioSink;

typedef struct BreakEditorAudioPreview BreakEditorAudioPreview;

BreakEditorAudioPreview *break_editor_audio_preview_create(void);
/* Stops first (the sink is closed). */
void break_editor_audio_preview_destroy(BreakEditorAudioPreview *preview);
/* Stops a running preview, then uses `sink` (borrowed; NULL = none). */
void break_editor_audio_preview_set_sink(BreakEditorAudioPreview *preview,
                                         const BreakEditorAudioSink *sink, void *user);
bool break_editor_audio_preview_has_sink(const BreakEditorAudioPreview *preview);
/* Copies the attachment and opens the sink at frame 0; restarts when already
 * playing. False and stopped without a sink, an attachment or frames, or
 * when the sink does not open. */
bool break_editor_audio_preview_play(BreakEditorAudioPreview *preview,
                                     const BreakEditorDoc *doc);
/* Writes what the sink accepts; stops (closing the sink) once everything is
 * written and drained, or when the sink reports an error. */
void break_editor_audio_preview_pump(BreakEditorAudioPreview *preview);
void break_editor_audio_preview_stop(BreakEditorAudioPreview *preview);
bool break_editor_audio_preview_playing(const BreakEditorAudioPreview *preview);
/* Frames heard so far (written minus queued); 0 when stopped. */
u32 break_editor_audio_preview_position_frames(const BreakEditorAudioPreview *preview);
u32 break_editor_audio_preview_length_frames(const BreakEditorAudioPreview *preview);
u32 break_editor_audio_preview_sample_rate(const BreakEditorAudioPreview *preview);
