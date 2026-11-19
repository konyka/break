#include "editor_audio_preview.h"

#include <editor/editor_audio.h>

#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#define EDITOR_PREVIEW_MAX_TAIL 64u

struct BreakEditorAudioPreview {
    const BreakEditorAudioSink *sink; /* borrowed */
    void *user;
    bool playing;
    u32 sample_rate;
    u32 channels;
    u32 frames;  /* length of the copy */
    u32 written; /* clip index of the next frame to write (clip, then the silent tail) */
    u32 tail;    /* silent frames after the clip (sink's tail_frames) */
    u32 start;   /* clip frame the copy starts at */
    u32 cursor;  /* where the next play starts */
    bool to_clip_end; /* the playing range ends at the clip end */
    bool loop;        /* re-arm the range instead of stopping at its end */
    i16 *pcm;    /* BREAK_EDITOR_AUDIO_MAX_FRAMES x 2 */
};

BreakEditorAudioPreview *break_editor_audio_preview_create(void) {
    BreakEditorAudioPreview *preview =
        (BreakEditorAudioPreview *)calloc(1u, sizeof(BreakEditorAudioPreview));
    if (preview == NULL) {
        return NULL;
    }
    preview->pcm = (i16 *)calloc((usize)(BREAK_EDITOR_AUDIO_MAX_FRAMES + EDITOR_PREVIEW_MAX_TAIL) * 2u,
                                 sizeof(i16));
    if (preview->pcm == NULL) {
        free(preview);
        return NULL;
    }
    return preview;
}

void break_editor_audio_preview_destroy(BreakEditorAudioPreview *preview) {
    if (preview == NULL) {
        return;
    }
    break_editor_audio_preview_stop(preview);
    free(preview->pcm);
    free(preview);
}

void break_editor_audio_preview_set_sink(BreakEditorAudioPreview *preview,
                                         const BreakEditorAudioSink *sink, void *user) {
    if (preview == NULL) {
        return;
    }
    break_editor_audio_preview_stop(preview);
    preview->sink = sink;
    preview->user = sink != NULL ? user : NULL;
}

bool break_editor_audio_preview_has_sink(const BreakEditorAudioPreview *preview) {
    return preview != NULL && preview->sink != NULL;
}

bool break_editor_audio_preview_play(BreakEditorAudioPreview *preview,
                                     const BreakEditorDoc *doc) {
    return break_editor_audio_preview_play_from(preview, doc, 0u);
}

bool break_editor_audio_preview_play_from(BreakEditorAudioPreview *preview,
                                          const BreakEditorDoc *doc, u32 start_frame) {
    return break_editor_audio_preview_play_range(preview, doc, start_frame, UINT32_MAX);
}

bool break_editor_audio_preview_play_range(BreakEditorAudioPreview *preview,
                                           const BreakEditorDoc *doc, u32 start_frame,
                                           u32 end_frame) {
    if (preview == NULL) {
        return false;
    }
    break_editor_audio_preview_stop(preview);
    const u32 clip_frames = break_editor_doc_audio_frames(doc);
    /* only [0, end) is copied: the silent tail follows the range's end */
    const u32 frames = end_frame < clip_frames ? end_frame : clip_frames;
    const u32 channels = break_editor_doc_audio_channels(doc);
    const i16 *samples = break_editor_doc_audio_samples(doc);
    if (preview->sink == NULL || samples == NULL || frames == 0u ||
        frames > BREAK_EDITOR_AUDIO_MAX_FRAMES || (channels != 1u && channels != 2u)) {
        return false;
    }
    u32 tail = preview->sink->tail_frames != NULL ? preview->sink->tail_frames(preview->user) : 0u;
    if (tail > EDITOR_PREVIEW_MAX_TAIL) tail = EDITOR_PREVIEW_MAX_TAIL;
    if (end_frame != UINT32_MAX && start_frame >= frames) {
        return false;
    }
    const u32 start = start_frame < frames ? start_frame : frames - 1u;
    memcpy(preview->pcm, samples, (usize)frames * channels * sizeof(i16));
    memset(preview->pcm + (usize)frames * channels, 0, (usize)tail * channels * sizeof(i16));
    preview->sample_rate = break_editor_doc_audio_sample_rate(doc);
    preview->channels = channels;
    preview->frames = frames;
    preview->tail = tail;
    preview->start = start;
    preview->written = start;
    preview->to_clip_end = frames == clip_frames;
    if (!preview->sink->open(preview->user, preview->sample_rate, channels)) {
        return false;
    }
    preview->playing = true;
    return true;
}

void break_editor_audio_preview_set_loop(BreakEditorAudioPreview *preview, bool loop) {
    if (preview != NULL) {
        preview->loop = loop;
    }
}

bool break_editor_audio_preview_loop(const BreakEditorAudioPreview *preview) {
    return preview != NULL && preview->loop;
}

/* Writes what the sink accepts from the cursor; stops on a sink error. */
static void preview_pump_write(BreakEditorAudioPreview *preview) {
    const u32 total = preview->frames + preview->tail;
    if (preview->written < total) {
        u32 accepted = 0u;
        if (!preview->sink->write(preview->user,
                                  preview->pcm + (usize)preview->written * preview->channels,
                                  total - preview->written, &accepted) ||
            accepted > total - preview->written) {
            break_editor_audio_preview_stop(preview);
            return;
        }
        preview->written += accepted;
    }
}

void break_editor_audio_preview_pump(BreakEditorAudioPreview *preview) {
    if (preview == NULL || !preview->playing) {
        return;
    }
    const u32 total = preview->frames + preview->tail;
    preview_pump_write(preview);
    if (!preview->playing) {
        return;
    }
    if (preview->written == total) {
        u32 queued = 0u;
        if (!preview->sink->queued(preview->user, &queued) || queued <= preview->tail) {
            if (preview->loop) {
                /* start the same range again; the sink stays open, so its
                 * ring is reset by the write that follows */
                preview->written = preview->start;
                preview_pump_write(preview);
                return;
            }
            break_editor_audio_preview_stop(preview);
            if (preview->to_clip_end) {
                preview->cursor = 0u; /* played to the end: the next play starts over */
            }
        }
    }
}

void break_editor_audio_preview_stop(BreakEditorAudioPreview *preview) {
    if (preview == NULL || !preview->playing) {
        return;
    }
    preview->playing = false;
    preview->sink->close(preview->user);
}

bool break_editor_audio_preview_playing(const BreakEditorAudioPreview *preview) {
    return preview != NULL && preview->playing;
}

u32 break_editor_audio_preview_position_frames(const BreakEditorAudioPreview *preview) {
    u32 queued = 0u;
    if (preview == NULL || !preview->playing) {
        return 0u;
    }
    if (!preview->sink->queued(preview->user, &queued) ||
        queued > preview->written - preview->start) {
        return preview->start;
    }
    const u32 consumed = preview->written - queued;
    return consumed < preview->frames ? consumed : preview->frames;
}

u32 break_editor_audio_preview_length_frames(const BreakEditorAudioPreview *preview) {
    return preview != NULL && preview->playing ? preview->frames : 0u;
}

u32 break_editor_audio_preview_sample_rate(const BreakEditorAudioPreview *preview) {
    return preview != NULL && preview->playing ? preview->sample_rate : 0u;
}

bool break_editor_audio_preview_seek(BreakEditorAudioPreview *preview,
                                     const BreakEditorDoc *doc, u32 frame) {
    const u32 frames = break_editor_doc_audio_frames(doc);
    if (preview == NULL) {
        return false;
    }
    preview->cursor = frames == 0u ? 0u : (frame < frames ? frame : frames - 1u);
    if (preview->playing) {
        /* inside the playing range: keep its end; outside: to the clip end */
        const u32 end = preview->frames;
        if (preview->cursor >= preview->start && preview->cursor < end) {
            return break_editor_audio_preview_play_range(preview, doc, preview->cursor, end);
        }
        return break_editor_audio_preview_play_from(preview, doc, preview->cursor);
    }
    return false;
}

u32 break_editor_audio_preview_cursor_frames(const BreakEditorAudioPreview *preview) {
    return preview != NULL ? preview->cursor : 0u;
}

void break_editor_audio_preview_reset_cursor(BreakEditorAudioPreview *preview) {
    if (preview != NULL) {
        preview->cursor = 0u;
    }
}
