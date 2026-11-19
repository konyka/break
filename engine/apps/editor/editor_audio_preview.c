#include "editor_audio_preview.h"

#include <editor/editor_audio.h>

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
    u32 written; /* frames handed to the sink (clip, then the silent tail) */
    u32 tail;    /* silent frames after the clip (sink's tail_frames) */
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
    if (preview == NULL) {
        return false;
    }
    break_editor_audio_preview_stop(preview);
    const u32 frames = break_editor_doc_audio_frames(doc);
    const u32 channels = break_editor_doc_audio_channels(doc);
    const i16 *samples = break_editor_doc_audio_samples(doc);
    if (preview->sink == NULL || samples == NULL || frames == 0u ||
        frames > BREAK_EDITOR_AUDIO_MAX_FRAMES || (channels != 1u && channels != 2u)) {
        return false;
    }
    u32 tail = preview->sink->tail_frames != NULL ? preview->sink->tail_frames(preview->user) : 0u;
    if (tail > EDITOR_PREVIEW_MAX_TAIL) tail = EDITOR_PREVIEW_MAX_TAIL;
    memcpy(preview->pcm, samples, (usize)frames * channels * sizeof(i16));
    memset(preview->pcm + (usize)frames * channels, 0, (usize)tail * channels * sizeof(i16));
    preview->sample_rate = break_editor_doc_audio_sample_rate(doc);
    preview->channels = channels;
    preview->frames = frames;
    preview->tail = tail;
    preview->written = 0u;
    if (!preview->sink->open(preview->user, preview->sample_rate, channels)) {
        return false;
    }
    preview->playing = true;
    return true;
}

void break_editor_audio_preview_pump(BreakEditorAudioPreview *preview) {
    if (preview == NULL || !preview->playing) {
        return;
    }
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
    if (preview->written == total) {
        u32 queued = 0u;
        if (!preview->sink->queued(preview->user, &queued) || queued <= preview->tail) {
            break_editor_audio_preview_stop(preview);
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
    if (!preview->sink->queued(preview->user, &queued) || queued > preview->written) {
        return 0u;
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
