#include "editor_audio.h"

#include <audio/audio_edit.h>
#include <audio/audio_wav.h>
#include <editor/editor_internal.h>
#include <editor/editor_test_hooks.h>

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BreakEditorAudioState BreakEditorAudioState;

struct BreakEditorAudioState {
    u32 sample_rate;
    u32 channels;
    u32 frames;
    i16 *samples;
};

typedef struct {
    BreakEditorCmd base;
    u32 before_frames;
    u32 after_frames;
    usize bytes;
    i16 *before;
    i16 *after;
} BreakEditorAudioSnapshotCmd;

static usize audio_state_bytes(const BreakEditorAudioState *audio) {
    return (usize)audio->frames * audio->channels * sizeof(i16);
}

bool break_editor_doc_audio_attach(BreakEditorDoc *doc, u32 sample_rate, u32 channels,
                                   const i16 *samples, u32 frames) {
    if (!doc || doc->audio || sample_rate < 8000u || sample_rate > 192000u ||
        (channels != 1u && channels != 2u) || frames > BREAK_EDITOR_AUDIO_MAX_FRAMES ||
        (!samples && frames != 0u)) {
        return false;
    }
    BreakEditorAudioState *audio = break_editor_test_calloc(sizeof(*audio));
    if (!audio) return false;
    const usize capacity = (usize)BREAK_EDITOR_AUDIO_MAX_FRAMES * channels * sizeof(i16);
    audio->samples = break_editor_test_calloc(capacity);
    if (!audio->samples) {
        free(audio);
        return false;
    }
    audio->sample_rate = sample_rate;
    audio->channels = channels;
    audio->frames = frames;
    if (frames != 0u) memcpy(audio->samples, samples, (usize)frames * channels * sizeof(i16));
    doc->audio = audio;
    doc->audio_revision++;
    doc->dirty = true;
    return true;
}

bool break_editor_doc_audio_attached(const BreakEditorDoc *doc) {
    return doc && doc->audio;
}

u32 break_editor_doc_audio_frames(const BreakEditorDoc *doc) {
    return doc && doc->audio ? doc->audio->frames : 0u;
}

u32 break_editor_doc_audio_sample_rate(const BreakEditorDoc *doc) {
    return doc && doc->audio ? doc->audio->sample_rate : 0u;
}

u32 break_editor_doc_audio_channels(const BreakEditorDoc *doc) {
    return doc && doc->audio ? doc->audio->channels : 0u;
}

const i16 *break_editor_doc_audio_samples(const BreakEditorDoc *doc) {
    return doc && doc->audio ? doc->audio->samples : NULL;
}

u64 break_editor_doc_audio_revision(const BreakEditorDoc *doc) {
    return doc ? doc->audio_revision : 0u;
}

bool break_editor_doc_audio_waveform(const BreakEditorDoc *doc, u32 columns,
                                     i16 *out_min, i16 *out_max) {
    return break_editor_doc_audio_waveform_range(
        doc, 0u, doc && doc->audio ? doc->audio->frames : 0u, columns, out_min, out_max);
}

/* channel == UINT32_MAX merges every channel; otherwise only that one. */
static bool audio_waveform_impl(const BreakEditorDoc *doc, u32 channel, u32 begin, u32 end,
                                u32 columns, i16 *out_min, i16 *out_max) {
    if (!doc || !doc->audio || !out_min || !out_max || columns == 0u ||
        columns > BREAK_EDITOR_AUDIO_WAVEFORM_MAX_COLUMNS || begin >= end ||
        end > doc->audio->frames) {
        return false;
    }
    const BreakEditorAudioState *audio = doc->audio;
    const bool merged = channel == UINT32_MAX;
    if (!merged && channel >= audio->channels) {
        return false;
    }
    const u32 step = merged ? 1u : audio->channels;
    const u32 offset = merged ? 0u : channel;
    const u64 frames = (u64)end - begin;
    for (u32 c = 0u; c < columns; ++c) {
        const u64 first = begin + (u64)c * frames / columns;
        u64 last = begin + (u64)(c + 1u) * frames / columns;
        if (last <= first) last = first + 1u;
        const i16 *sample = audio->samples + first * audio->channels + offset;
        const i16 *stop = audio->samples + last * audio->channels;
        i16 lo = *sample, hi = *sample;
        for (; sample < stop; sample += step) {
            if (*sample < lo) lo = *sample;
            if (*sample > hi) hi = *sample;
        }
        out_min[c] = lo;
        out_max[c] = hi;
    }
    return true;
}

bool break_editor_doc_audio_waveform_range(const BreakEditorDoc *doc, u32 begin, u32 end,
                                           u32 columns, i16 *out_min, i16 *out_max) {
    return audio_waveform_impl(doc, UINT32_MAX, begin, end, columns, out_min, out_max);
}

bool break_editor_doc_audio_waveform_channel(const BreakEditorDoc *doc, u32 channel,
                                             u32 begin, u32 end, u32 columns,
                                             i16 *out_min, i16 *out_max) {
    return channel != UINT32_MAX &&
           audio_waveform_impl(doc, channel, begin, end, columns, out_min, out_max);
}

void break_editor_audio_detach(BreakEditorDoc *doc) {
    if (!doc || !doc->audio) return;
    free(doc->audio->samples);
    free(doc->audio);
    doc->audio = NULL;
    doc->audio_revision++;
}

static void audio_snapshot_destroy(BreakEditorCmd *command) {
    BreakEditorAudioSnapshotCmd *snapshot = (BreakEditorAudioSnapshotCmd *)command;
    free(snapshot->before);
    free(snapshot->after);
    free(snapshot);
}

static bool audio_snapshot_restore(BreakEditorDoc *doc, u32 frames, const i16 *samples,
                                   usize bytes) {
    if (!doc || !doc->audio || (bytes != 0u && !samples)) return false;
    if (bytes != 0u) memcpy(doc->audio->samples, samples, bytes);
    doc->audio->frames = frames;
    doc->audio_revision++;
    return true;
}

static bool audio_snapshot_apply(BreakEditorCmd *command, BreakEditorDoc *doc) {
    BreakEditorAudioSnapshotCmd *snapshot = (BreakEditorAudioSnapshotCmd *)command;
    return audio_snapshot_restore(doc, snapshot->after_frames, snapshot->after, snapshot->bytes);
}

static bool audio_snapshot_revert(BreakEditorCmd *command, BreakEditorDoc *doc) {
    BreakEditorAudioSnapshotCmd *snapshot = (BreakEditorAudioSnapshotCmd *)command;
    return audio_snapshot_restore(doc, snapshot->before_frames, snapshot->before, snapshot->bytes);
}

static void audio_snapshot_describe(const BreakEditorCmd *command, char buf[128]) {
    snprintf(buf, 128, "audio %.96s", command->name);
}

static BreakEditorAudioSnapshotCmd *audio_snapshot_create(BreakEditorDoc *doc,
                                                          const char *operation) {
    BreakEditorAudioSnapshotCmd *snapshot = break_editor_test_calloc(sizeof(*snapshot));
    if (!snapshot) return NULL;
    snapshot->base.apply = audio_snapshot_apply;
    snapshot->base.revert = audio_snapshot_revert;
    snapshot->base.destroy = audio_snapshot_destroy;
    snapshot->base.describe = audio_snapshot_describe;
    snapshot->base.kind = BREAK_EDITOR_CMD_KIND_AUDIO_SNAPSHOT;
    break_editor_name_copy(snapshot->base.name, operation);
    snapshot->before_frames = doc->audio->frames;
    snapshot->after_frames = doc->audio->frames;
    snapshot->bytes = audio_state_bytes(doc->audio);
    if (snapshot->bytes != 0u) {
        snapshot->before = break_editor_test_calloc(snapshot->bytes);
        snapshot->after = break_editor_test_calloc(snapshot->bytes);
        if (!snapshot->before || !snapshot->after) {
            audio_snapshot_destroy(&snapshot->base);
            return NULL;
        }
        memcpy(snapshot->before, doc->audio->samples, snapshot->bytes);
        memcpy(snapshot->after, doc->audio->samples, snapshot->bytes);
    }
    return snapshot;
}

static bool audio_snapshot_commit(BreakEditorAudioSnapshotCmd *snapshot, BreakEditorDoc *doc,
                                  u32 after_frames) {
    snapshot->after_frames = after_frames;
    if (!snapshot->base.apply(&snapshot->base, doc)) {
        audio_snapshot_destroy(&snapshot->base);
        return false;
    }
    break_editor_cmd_stack_push_applied(doc, &snapshot->base);
    doc->dirty = true;
    return true;
}

bool break_editor_doc_audio_trim(BreakEditorDoc *doc, u32 begin, u32 end) {
    if (!doc || !doc->audio || begin > end || end > doc->audio->frames) return false;
    BreakEditorAudioSnapshotCmd *snapshot = audio_snapshot_create(doc, "trim");
    if (!snapshot) return false;
    u32 frames = 0u;
    const AudioResult result = audio_edit_trim_i16(snapshot->after, snapshot->before_frames,
                                                   doc->audio->channels, begin, end, &frames);
    if (result != AUDIO_OK) {
        audio_snapshot_destroy(&snapshot->base);
        return false;
    }
    return audio_snapshot_commit(snapshot, doc, frames);
}

bool break_editor_doc_audio_cut(BreakEditorDoc *doc, u32 begin, u32 end) {
    if (!doc || !doc->audio || begin > end || end > doc->audio->frames) return false;
    BreakEditorAudioSnapshotCmd *snapshot = audio_snapshot_create(doc, "cut");
    if (!snapshot) return false;
    u32 frames = 0u;
    const AudioResult result = audio_edit_cut_i16(snapshot->after, snapshot->before_frames,
                                                  doc->audio->channels, begin, end, &frames);
    if (result != AUDIO_OK) {
        audio_snapshot_destroy(&snapshot->base);
        return false;
    }
    return audio_snapshot_commit(snapshot, doc, frames);
}

bool break_editor_doc_audio_fade(BreakEditorDoc *doc, double fade_in_ms, double fade_out_ms) {
    if (!doc || !doc->audio || !isfinite(fade_in_ms) || !isfinite(fade_out_ms) ||
        fade_in_ms < 0.0 || fade_out_ms < 0.0) {
        return false;
    }
    BreakEditorAudioSnapshotCmd *snapshot = audio_snapshot_create(doc, "fade");
    if (!snapshot) return false;
    const AudioResult result = audio_edit_fade_i16(snapshot->after, snapshot->before_frames,
                                                   doc->audio->channels,
                                                   doc->audio->sample_rate, fade_in_ms,
                                                   fade_out_ms);
    if (result != AUDIO_OK) {
        audio_snapshot_destroy(&snapshot->base);
        return false;
    }
    return audio_snapshot_commit(snapshot, doc, snapshot->before_frames);
}

bool break_editor_doc_audio_normalize(BreakEditorDoc *doc, double target_dbfs) {
    if (!doc || !doc->audio || !isfinite(target_dbfs) || target_dbfs < -120.0 ||
        target_dbfs > 0.0) {
        return false;
    }
    BreakEditorAudioSnapshotCmd *snapshot = audio_snapshot_create(doc, "normalize");
    if (!snapshot) return false;
    const AudioResult result = audio_edit_normalize_i16(snapshot->after, snapshot->before_frames,
                                                        doc->audio->channels, target_dbfs);
    if (result != AUDIO_OK) {
        audio_snapshot_destroy(&snapshot->base);
        return false;
    }
    return audio_snapshot_commit(snapshot, doc, snapshot->before_frames);
}

static bool audio_range_valid(const BreakEditorDoc *doc, u32 begin, u32 end) {
    return doc && doc->audio && begin < end && end <= doc->audio->frames;
}

bool break_editor_doc_audio_fade_range(BreakEditorDoc *doc, u32 begin, u32 end,
                                       double fade_in_ms, double fade_out_ms) {
    if (!audio_range_valid(doc, begin, end) || !isfinite(fade_in_ms) ||
        !isfinite(fade_out_ms) || fade_in_ms < 0.0 || fade_out_ms < 0.0) {
        return false;
    }
    BreakEditorAudioSnapshotCmd *snapshot = audio_snapshot_create(doc, "fade");
    if (!snapshot) return false;
    const u32 channels = doc->audio->channels;
    const AudioResult result =
        audio_edit_fade_i16(snapshot->after + (usize)begin * channels, end - begin, channels,
                            doc->audio->sample_rate, fade_in_ms, fade_out_ms);
    if (result != AUDIO_OK) {
        audio_snapshot_destroy(&snapshot->base);
        return false;
    }
    return audio_snapshot_commit(snapshot, doc, snapshot->before_frames);
}

bool break_editor_doc_audio_normalize_range(BreakEditorDoc *doc, u32 begin, u32 end,
                                            double target_dbfs) {
    if (!audio_range_valid(doc, begin, end) || !isfinite(target_dbfs) ||
        target_dbfs < -120.0 || target_dbfs > 0.0) {
        return false;
    }
    BreakEditorAudioSnapshotCmd *snapshot = audio_snapshot_create(doc, "normalize");
    if (!snapshot) return false;
    const u32 channels = doc->audio->channels;
    const AudioResult result = audio_edit_normalize_i16(
        snapshot->after + (usize)begin * channels, end - begin, channels, target_dbfs);
    if (result != AUDIO_OK) {
        audio_snapshot_destroy(&snapshot->base);
        return false;
    }
    return audio_snapshot_commit(snapshot, doc, snapshot->before_frames);
}

bool break_editor_doc_audio_mix(BreakEditorDoc *doc, const i16 *source,
                                u32 source_frames, double gain) {
    if (!doc || !doc->audio || !isfinite(gain) || gain < -8.0 || gain > 8.0 ||
        (!source && source_frames != 0u)) {
        return false;
    }
    BreakEditorAudioSnapshotCmd *snapshot = audio_snapshot_create(doc, "mix");
    if (!snapshot) return false;
    const AudioResult result = audio_edit_mix_i16(snapshot->after, snapshot->before_frames,
                                                  source, source_frames,
                                                  doc->audio->channels, gain);
    if (result != AUDIO_OK) {
        audio_snapshot_destroy(&snapshot->base);
        return false;
    }
    return audio_snapshot_commit(snapshot, doc, snapshot->before_frames);
}

#define BREAK_EDITOR_WAV_MAX_BYTES (1L << 20)

bool break_editor_doc_audio_attach_wav(BreakEditorDoc *doc, const char *path) {
    if (!doc || doc->audio || !path || path[0] == '\0') return false;
    FILE *file = fopen(path, "rb");
    if (!file) return false;
    if (fseek(file, 0, SEEK_END) != 0) {
        fclose(file);
        return false;
    }
    const long length = ftell(file);
    if (length <= 0 || length > BREAK_EDITOR_WAV_MAX_BYTES) {
        fclose(file);
        return false;
    }
    const usize size = (usize)length;
    u8 *data = break_editor_test_calloc(size);
    if (!data) {
        fclose(file);
        return false;
    }
    if (fseek(file, 0, SEEK_SET) != 0) {
        free(data);
        fclose(file);
        return false;
    }
    const bool read_ok = fread(data, 1u, size, file) == size;
    const bool close_ok = fclose(file) == 0;
    if (!read_ok || !close_ok) {
        free(data);
        return false;
    }
    const usize pcm_capacity = (usize)BREAK_EDITOR_AUDIO_MAX_FRAMES * 2u * sizeof(i16);
    i16 *pcm = break_editor_test_calloc(pcm_capacity);
    if (!pcm) {
        free(data);
        return false;
    }
    AudioWavInfo info;
    const AudioResult result = audio_wav_decode_i16(data, size, &info, pcm,
                                                    BREAK_EDITOR_AUDIO_MAX_FRAMES);
    bool attached = false;
    if (result == AUDIO_OK) {
        attached = break_editor_doc_audio_attach(doc, info.sample_rate, info.channels,
                                                 pcm, info.frames);
    }
    free(pcm);
    free(data);
    return attached;
}

/* rename(2) replaces atomically on POSIX; Windows rename() fails when the
 * destination exists, so it is removed first (best effort, as for scenes). */
static bool editor_audio_rename_replace(const char *tmp, const char *dst) {
#if defined(_WIN32)
    remove(dst);
#endif
    return rename(tmp, dst) == 0;
}

bool break_editor_doc_audio_save_wav(const BreakEditorDoc *doc, const char *path) {
    if (!doc || !doc->audio || !path || path[0] == '\0') return false;
    const BreakEditorAudioState *audio = doc->audio;
    char tmp[1024];
    const int length = snprintf(tmp, sizeof(tmp), "%s.tmp", path);
    if (length < 0 || (usize)length >= sizeof(tmp)) return false;
    usize size = 0u;
    if (audio_wav_encoded_size(audio->channels, audio->frames, &size) != AUDIO_OK) return false;
    u8 *data = break_editor_test_calloc(size);
    if (!data) return false;
    const AudioWavInfo info = {audio->sample_rate, audio->channels, audio->frames};
    usize encoded = 0u;
    bool ok = audio_wav_encode_i16(&info, audio->samples, data, size, &encoded) == AUDIO_OK;
    FILE *file = ok ? fopen(tmp, "wb") : NULL;
    if (file) {
        const bool written = fwrite(data, 1u, encoded, file) == encoded;
        const bool closed = fclose(file) == 0;
        ok = written && closed && editor_audio_rename_replace(tmp, path);
        if (!ok) remove(tmp);
    } else {
        ok = false;
    }
    free(data);
    return ok;
}
