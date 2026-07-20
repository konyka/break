#pragma once
#include <core/types.h>
#include <math/math.h>

#define AUDIO_MAX_DEVICES 16
#define AUDIO_MAX_SOURCES 32

typedef struct AudioSource AudioSource;

typedef struct {
    char name[128];
    char id[64];        /* device identifier (used for ma_device_id) */
    bool is_default;
} AudioDeviceInfo;

typedef struct {
    void       *engine;
    AudioSource *sources;
    u32         source_count;
    u32         source_cap;
    Vec3        listener_pos;
    Vec3        listener_forward;
    Vec3        listener_up;

    /* Free-list for audio source slot reuse */
    u32         free_list[AUDIO_MAX_SOURCES];
    u32         free_count;

    /* Device info cache */
    AudioDeviceInfo devices[AUDIO_MAX_DEVICES];
    u32             device_count;
    bool            devices_enumerated;  /* true after first enumeration */
    char            current_device[128];
} AudioSystem;

AudioSystem *audio_system_create(void);
void         audio_system_destroy(AudioSystem *as);
void         audio_system_update(AudioSystem *as, Vec3 listener_pos, Vec3 forward, Vec3 up);

u32          audio_play(AudioSystem *as, const char *path, f32 volume, bool looping);
void         audio_play_3d(AudioSystem *as, const char *path, Vec3 position, f32 volume, bool looping);
void         audio_stop(AudioSystem *as, u32 source_id);
void         audio_set_listener(AudioSystem *as, Vec3 pos, Vec3 forward, Vec3 up);

/* ---- Streaming playback (miniaudio MA_SOUND_FLAG_STREAM) ----
 * Decodes from disk on the fly instead of loading the whole file. */
u32          audio_play_streamed(AudioSystem *as, const char *path, f32 volume,
                                 bool looping, bool spatial, Vec3 position);

/* ---- Per-source 3D / playback controls ---- */
void         audio_source_set_position(AudioSystem *as, u32 source_id, Vec3 position);
void         audio_source_set_attenuation(AudioSystem *as, u32 source_id,
                                          f32 min_dist, f32 max_dist, f32 rolloff);
void         audio_source_set_volume(AudioSystem *as, u32 source_id, f32 volume);
void         audio_source_start(AudioSystem *as, u32 source_id);
void         audio_source_stop(AudioSystem *as, u32 source_id);
bool         audio_source_at_end(AudioSystem *as, u32 source_id);
f32          audio_source_cursor_seconds(AudioSystem *as, u32 source_id);

/* Pure inverse-distance attenuation gain (matches miniaudio's inverse model),
 * exposed so it can be unit tested and shown in tooling. dist is clamped to
 * [min_dist, max_dist]; returns a gain in [0, 1]. */
static inline f32 audio_attenuation_gain(f32 dist, f32 min_dist,
                                         f32 max_dist, f32 rolloff) {
    if (min_dist < 0.0001f) min_dist = 0.0001f;
    if (max_dist < min_dist) max_dist = min_dist;
    f32 d = dist;
    if (d < min_dist) d = min_dist;
    if (d > max_dist) d = max_dist;
    f32 denom = min_dist + rolloff * (d - min_dist);
    if (denom <= 0.0001f) return 0.0f;
    f32 g = min_dist / denom;
    if (g > 1.0f) g = 1.0f;
    if (g < 0.0f) g = 0.0f;
    return g;
}

/* Device enumeration */
u32          audio_get_device_count(AudioSystem *sys);
bool         audio_get_device_info(AudioSystem *sys, u32 index, AudioDeviceInfo *out);

/* Device selection: records selection for next audio_system_create.
 * Returns false because miniaudio does not support runtime hot-swap;
 * caller must destroy and re-create the AudioSystem to apply. */
bool         audio_set_device(AudioSystem *sys, const char *device_id);

/* Returns currently selected device name (or "default") */
const char  *audio_get_current_device(AudioSystem *sys);
