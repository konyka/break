#pragma once

#include <core/types.h>
#include <audio/audio.h>

/*
 * Audio Streaming System
 *
 * Streams large audio files (WAV/OGG/MP3) straight from disk via miniaudio's
 * MA_SOUND_FLAG_STREAM instead of decoding the whole file into memory. Each
 * stream is a spatializable source so the demo can place sounds in the world
 * and let distance attenuation roll off naturally.
 */

#define AUDIO_STREAM_MAX_SOURCES    16

typedef enum {
    AUDIO_STREAM_IDLE = 0,
    AUDIO_STREAM_PLAYING,
    AUDIO_STREAM_PAUSED,
    AUDIO_STREAM_STOPPED,
    AUDIO_STREAM_END_OF_FILE
} AudioStreamState;

typedef struct {
    char             path[256];
    AudioStreamState state;
    u32              source_id;    /* AudioSystem source id (>0), 0 == none */
    bool             active;
    bool             looping;
    bool             spatial;
    f32              volume;
    Vec3             position;
    f32              min_dist, max_dist, rolloff;
} AudioStream;

typedef struct {
    AudioStream      streams[AUDIO_STREAM_MAX_SOURCES];
    i32              free_next[AUDIO_STREAM_MAX_SOURCES]; /* free-list next pointers */
    u32              stream_count;
    i32              next_free;       /* O(1) free-list head (-1 = full) */
    AudioSystem     *audio;           /* parent audio system */
    bool             ready;
} AudioStreamManager;

/* Initialize/shutdown the streaming manager */
bool audio_stream_init(AudioStreamManager *mgr, AudioSystem *audio);
void audio_stream_shutdown(AudioStreamManager *mgr);

/* Open and start streaming a 2D audio file. Returns stream index or -1. */
i32 audio_stream_open(AudioStreamManager *mgr, const char *path, f32 volume, bool looping);

/* Open and start streaming a spatialized (3D) audio file at a world position. */
i32 audio_stream_open_3d(AudioStreamManager *mgr, const char *path, Vec3 position,
                         f32 volume, bool looping,
                         f32 min_dist, f32 max_dist, f32 rolloff);

/* Control playback */
void audio_stream_play(AudioStreamManager *mgr, i32 stream_idx);
void audio_stream_pause(AudioStreamManager *mgr, i32 stream_idx);
void audio_stream_stop(AudioStreamManager *mgr, i32 stream_idx);
void audio_stream_set_position(AudioStreamManager *mgr, i32 stream_idx, Vec3 position);

/* Update: poll playback state each frame (miniaudio refills internally). */
void audio_stream_update(AudioStreamManager *mgr);

/* Get state */
AudioStreamState audio_stream_get_state(AudioStreamManager *mgr, i32 stream_idx);
f32 audio_stream_get_volume(AudioStreamManager *mgr, i32 stream_idx);
void audio_stream_set_volume(AudioStreamManager *mgr, i32 stream_idx, f32 volume);

/* Estimated attenuation gain for this stream given a listener position. */
f32 audio_stream_attenuation(AudioStreamManager *mgr, i32 stream_idx, Vec3 listener_pos);

/* Playback position of the stream in seconds. */
f32 audio_stream_cursor_seconds(AudioStreamManager *mgr, i32 stream_idx);
