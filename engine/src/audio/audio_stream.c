#include "audio_stream.h"
#include <core/log.h>
#include <math/math.h>
#include <stdlib.h>
#include <string.h>

/*
 * Real streaming playback: each AudioStream wraps a miniaudio source created
 * with MA_SOUND_FLAG_STREAM (see audio_play_streamed). miniaudio decodes and
 * refills from disk on its mixing thread, so this layer only manages stream
 * slots, 3D placement and playback state. Distance attenuation is applied by
 * miniaudio's inverse model; audio_stream_attenuation mirrors that gain for
 * tooling/diagnostics.
 */

static bool stream_idx_valid(AudioStreamManager *mgr, i32 idx) {
    return mgr && mgr->ready && idx >= 0 && (u32)idx < AUDIO_STREAM_MAX_SOURCES &&
           mgr->streams[idx].active;
}

bool audio_stream_init(AudioStreamManager *mgr, AudioSystem *audio) {
    if (!mgr || !audio) return false;
    memset(mgr, 0, sizeof(*mgr));
    mgr->audio = audio;
    mgr->ready = true;
    /* Build free list: each slot points to the next, last = -1 */
    for (u32 i = 0; i < AUDIO_STREAM_MAX_SOURCES - 1; i++) {
        mgr->free_next[i] = (i32)(i + 1);
    }
    mgr->free_next[AUDIO_STREAM_MAX_SOURCES - 1] = -1;
    mgr->next_free = 0;
    LOG_INFO("AudioStream: initialized (%u max streams, miniaudio-backed)",
             AUDIO_STREAM_MAX_SOURCES);
    return true;
}

void audio_stream_shutdown(AudioStreamManager *mgr) {
    if (!mgr || !mgr->ready) return;
    for (u32 i = 0; i < AUDIO_STREAM_MAX_SOURCES; i++) {
        AudioStream *s = &mgr->streams[i];
        if (s->active && s->source_id > 0 && mgr->audio) {
            audio_stop(mgr->audio, s->source_id);
        }
        s->active = false;
        s->state = AUDIO_STREAM_IDLE;
    }
    LOG_INFO("AudioStream: shutdown");
    mgr->ready = false;
}

static i32 stream_alloc_slot(AudioStreamManager *mgr) {
    /* O(1): pop from free list */
    if (mgr->next_free < 0) return -1;
    i32 idx = mgr->next_free;
    mgr->next_free = mgr->free_next[idx];
    return idx;
}

i32 audio_stream_open(AudioStreamManager *mgr, const char *path, f32 volume, bool looping) {
    if (!mgr || !mgr->ready || !path) return -1;
    i32 idx = stream_alloc_slot(mgr);
    if (idx < 0) return -1;

    u32 sid = audio_play_streamed(mgr->audio, path, volume, looping, false, vec3(0, 0, 0));
    if (sid == 0) {
        LOG_WARN("AudioStream: failed to open '%s'", path);
        /* R107-1: return slot to free list on failure to prevent slot exhaustion */
        mgr->free_next[idx] = mgr->next_free;
        mgr->next_free = idx;
        return -1;
    }

    AudioStream *s = &mgr->streams[idx];
    memset(s, 0, sizeof(*s));
    strncpy(s->path, path, sizeof(s->path) - 1);
    s->path[sizeof(s->path) - 1] = '\0';
    s->source_id = sid;
    s->active = true;
    s->looping = looping;
    s->volume = volume;
    s->spatial = false;
    s->state = AUDIO_STREAM_PLAYING;
    mgr->stream_count++;
    return idx;
}

i32 audio_stream_open_3d(AudioStreamManager *mgr, const char *path, Vec3 position,
                         f32 volume, bool looping,
                         f32 min_dist, f32 max_dist, f32 rolloff) {
    if (!mgr || !mgr->ready || !path) return -1;
    i32 idx = stream_alloc_slot(mgr);
    if (idx < 0) return -1;

    u32 sid = audio_play_streamed(mgr->audio, path, volume, looping, true, position);
    if (sid == 0) {
        LOG_WARN("AudioStream: failed to open '%s' (3D)", path);
        /* R107-1: return slot to free list on failure to prevent slot exhaustion */
        mgr->free_next[idx] = mgr->next_free;
        mgr->next_free = idx;
        return -1;
    }
    audio_source_set_attenuation(mgr->audio, sid, min_dist, max_dist, rolloff);

    AudioStream *s = &mgr->streams[idx];
    memset(s, 0, sizeof(*s));
    strncpy(s->path, path, sizeof(s->path) - 1);
    s->path[sizeof(s->path) - 1] = '\0';
    s->source_id = sid;
    s->active = true;
    s->looping = looping;
    s->volume = volume;
    s->spatial = true;
    s->position = position;
    s->min_dist = min_dist;
    s->max_dist = max_dist;
    s->rolloff = rolloff;
    s->state = AUDIO_STREAM_PLAYING;
    mgr->stream_count++;
    return idx;
}

void audio_stream_play(AudioStreamManager *mgr, i32 stream_idx) {
    if (!stream_idx_valid(mgr, stream_idx)) return;
    AudioStream *s = &mgr->streams[stream_idx];
    audio_source_start(mgr->audio, s->source_id);
    s->state = AUDIO_STREAM_PLAYING;
}

void audio_stream_pause(AudioStreamManager *mgr, i32 stream_idx) {
    if (!stream_idx_valid(mgr, stream_idx)) return;
    AudioStream *s = &mgr->streams[stream_idx];
    /* R241: audio_stop() uninits the sound and frees the slot; use the pause-only
     * primitive so the cursor/source survive and audio_stream_play() can resume. */
    audio_source_stop(mgr->audio, s->source_id);
    s->state = AUDIO_STREAM_PAUSED;
}

void audio_stream_stop(AudioStreamManager *mgr, i32 stream_idx) {
    if (!stream_idx_valid(mgr, stream_idx)) return;
    AudioStream *s = &mgr->streams[stream_idx];
    if (s->source_id > 0 && mgr->audio) audio_stop(mgr->audio, s->source_id);
    s->state = AUDIO_STREAM_STOPPED;
    s->active = false;
    if (mgr->stream_count > 0) mgr->stream_count--;
    /* O(1): push slot back to free list */
    mgr->free_next[stream_idx] = mgr->next_free;
    mgr->next_free = stream_idx;
}

void audio_stream_set_position(AudioStreamManager *mgr, i32 stream_idx, Vec3 position) {
    if (!stream_idx_valid(mgr, stream_idx)) return;
    AudioStream *s = &mgr->streams[stream_idx];
    s->position = position;
    if (s->spatial) audio_source_set_position(mgr->audio, s->source_id, position);
}

void audio_stream_update(AudioStreamManager *mgr) {
    if (!mgr || !mgr->ready) return;
    for (u32 i = 0; i < AUDIO_STREAM_MAX_SOURCES; i++) {
        AudioStream *s = &mgr->streams[i];
        if (!s->active || s->state != AUDIO_STREAM_PLAYING) continue;
        /* miniaudio handles refill/looping; we only detect natural end. */
        if (!s->looping && audio_source_at_end(mgr->audio, s->source_id)) {
            s->state = AUDIO_STREAM_END_OF_FILE;
        }
    }
}

AudioStreamState audio_stream_get_state(AudioStreamManager *mgr, i32 stream_idx) {
    if (!mgr || !mgr->ready || stream_idx < 0 ||
        (u32)stream_idx >= AUDIO_STREAM_MAX_SOURCES) return AUDIO_STREAM_IDLE;
    return mgr->streams[stream_idx].state;
}

f32 audio_stream_get_volume(AudioStreamManager *mgr, i32 stream_idx) {
    if (!mgr || stream_idx < 0 || (u32)stream_idx >= AUDIO_STREAM_MAX_SOURCES) return 0.0f;
    return mgr->streams[stream_idx].volume;
}

void audio_stream_set_volume(AudioStreamManager *mgr, i32 stream_idx, f32 volume) {
    if (!stream_idx_valid(mgr, stream_idx)) return;
    AudioStream *s = &mgr->streams[stream_idx];
    s->volume = volume;
    audio_source_set_volume(mgr->audio, s->source_id, volume);
}

f32 audio_stream_attenuation(AudioStreamManager *mgr, i32 stream_idx, Vec3 listener_pos) {
    if (!stream_idx_valid(mgr, stream_idx)) return 0.0f;
    AudioStream *s = &mgr->streams[stream_idx];
    if (!s->spatial) return 1.0f;
    Vec3 d = vec3_sub(s->position, listener_pos);
    f32 dist = vec3_len(d);
    return audio_attenuation_gain(dist, s->min_dist, s->max_dist, s->rolloff);
}

f32 audio_stream_cursor_seconds(AudioStreamManager *mgr, i32 stream_idx) {
    if (!stream_idx_valid(mgr, stream_idx)) return 0.0f;
    return audio_source_cursor_seconds(mgr->audio, mgr->streams[stream_idx].source_id);
}
