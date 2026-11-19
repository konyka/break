#pragma once
/* Plays a snapshot of the document's PCM attachment through a sink (design
 * 2026-11-19-editor-audio-preview). The preview copies the attachment on
 * play, then each pump writes as many frames as the sink accepts, followed by
 * the sink's silent tail; once the queue is down to that tail, it closes the
 * sink and stops.
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
    /* Optional (NULL = 0): frames the output holds back at the end of a
     * stream (a resampler's lookahead). The preview writes that many frames
     * of silence after the clip and counts the clip as heard once no more
     * than that many are queued. */
    u32 (*tail_frames)(void *user);
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
/* play from `start_frame` (clamped to the last frame); play is
 * play_from(..., 0). */
bool break_editor_audio_preview_play_from(BreakEditorAudioPreview *preview,
                                          const BreakEditorDoc *doc, u32 start_frame);
/* Plays [start_frame, end_frame) only (end clamped to the clip; false when
 * start is not below it). Position and length are clip frames, so length
 * reports the range end. play_from is play_range(start, UINT32_MAX). */
bool break_editor_audio_preview_play_range(BreakEditorAudioPreview *preview,
                                           const BreakEditorDoc *doc, u32 start_frame,
                                           u32 end_frame);
/* Playing: restarts from `frame` (queued audio is dropped). Stopped: only
 * sets the cursor. Returns whether it plays afterwards. */
bool break_editor_audio_preview_seek(BreakEditorAudioPreview *preview,
                                     const BreakEditorDoc *doc, u32 frame);
/* Where the next Play starts: set by a stopped seek, 0 after playback ends
 * by itself or after break_editor_audio_preview_reset_cursor. */
u32 break_editor_audio_preview_cursor_frames(const BreakEditorAudioPreview *preview);
void break_editor_audio_preview_reset_cursor(BreakEditorAudioPreview *preview);
/* Writes what the sink accepts; stops (closing the sink) once everything is
 * written and drained, or when the sink reports an error. */
void break_editor_audio_preview_pump(BreakEditorAudioPreview *preview);
void break_editor_audio_preview_stop(BreakEditorAudioPreview *preview);
bool break_editor_audio_preview_playing(const BreakEditorAudioPreview *preview);
/* Clip frame the output has reached: the start frame plus frames consumed
 * (written minus queued), at most the clip length; device latency is not
 * included. 0 when stopped. */
u32 break_editor_audio_preview_position_frames(const BreakEditorAudioPreview *preview);
/* Length and rate of the clip being played; 0 when stopped. */
u32 break_editor_audio_preview_length_frames(const BreakEditorAudioPreview *preview);
u32 break_editor_audio_preview_sample_rate(const BreakEditorAudioPreview *preview);
