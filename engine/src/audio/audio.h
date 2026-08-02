#pragma once
#include <core/types.h>
#include <math/math.h>

#define AUDIO_MAX_DEVICES 16
#define AUDIO_MAX_SOURCES 32

/* R435: fixed-size mixing bus table. Slot 0 is the master bus and always
 * exists; AUDIO_BUS_INVALID is the error sentinel for audio_bus_create
 * (same UINT32_MAX convention as audio_acquire_slot). */
#define AUDIO_MAX_BUSES   8
#define AUDIO_BUS_MASTER  0u
#define AUDIO_BUS_INVALID UINT32_MAX

typedef struct AudioSource AudioSource;

typedef struct {
    char name[32];
    f32  gain; /* >= 0; 0 mutes the bus, >1 amplifies */
} AudioBus;

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

    /* R435: mixing bus table; lives and dies with the AudioSystem
     * (reset in audio_system_create). buses[0] is the master bus. */
    AudioBus        buses[AUDIO_MAX_BUSES];
    u32             bus_count;
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

/* R435: pure effective-gain composition for the mixing bus chain:
 * source volume x bus gain x master gain. Every factor is clamped to be
 * non-negative (a negative gain is meaningless; 0 mutes). No upper clamp —
 * amplification is allowed, matching the existing volume policy. Exposed as
 * a static inline so it can be unit tested headless. */
static inline f32 audio_effective_gain(f32 volume, f32 bus_gain,
                                       f32 master_gain) {
    if (volume < 0.0f) volume = 0.0f;
    if (bus_gain < 0.0f) bus_gain = 0.0f;
    if (master_gain < 0.0f) master_gain = 0.0f;
    return volume * bus_gain * master_gain;
}

/* ---- R435: mixing buses ----
 * Create a named bus; returns its id (>= 1) or AUDIO_BUS_INVALID when the
 * table is full / args are invalid. Bus 0 (master) always exists. */
u32          audio_bus_create(AudioSystem *as, const char *name);
/* Set a bus fader; gain is clamped to >= 0. Invalid bus id: no-op.
 * Re-applies the effective gain on every active source routed to the bus. */
void         audio_bus_set_gain(AudioSystem *as, u32 bus, f32 gain);
/* Query a bus fader; an invalid bus id falls back to the master gain. */
f32          audio_bus_gain(AudioSystem *as, u32 bus);
/* Route a source through a bus; an invalid bus id falls back to master.
 * Re-applies the effective gain immediately. */
void         audio_source_set_bus(AudioSystem *as, u32 source_id, u32 bus);

/* Device enumeration */
u32          audio_get_device_count(AudioSystem *sys);
bool         audio_get_device_info(AudioSystem *sys, u32 index, AudioDeviceInfo *out);

/* Device selection: records selection for next audio_system_create.
 * Returns false because miniaudio does not support runtime hot-swap;
 * caller must destroy and re-create the AudioSystem to apply. */
bool         audio_set_device(AudioSystem *sys, const char *device_id);

/* Returns currently selected device name (or "default") */
const char  *audio_get_current_device(AudioSystem *sys);
