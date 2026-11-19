#pragma once
#include <core/types.h>
#include <math/math.h>

#define AUDIO_MAX_DEVICES 16
#define AUDIO_MAX_SOURCES 32

typedef enum {
    AUDIO_OK = 0,
    AUDIO_INVALID,
    AUDIO_STALE,
    AUDIO_OVERLOAD,
    AUDIO_REJECTED,
    AUDIO_FAILED
} AudioResult;

typedef enum {
    AUDIO_BACKEND_DEFAULT = 0,
    AUDIO_BACKEND_NULL,
    AUDIO_BACKEND_FAKE
} AudioBackend;

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
    void       *extended;
    AudioBackend backend;
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
AudioSystem *audio_system_create_ex(AudioBackend backend);
/* Name of the playback backend the system actually opened, as miniaudio
 * reports it ("PulseAudio", "ALSA", "WASAPI", "Null", ...). A FAKE system has
 * no device and reports "fake"; a NULL system pointer reports "none". The
 * string is static and never freed. */
const char  *audio_system_backend_name(const AudioSystem *as);
/* Writes the name of the playback device the system opened into out and
 * returns true. Returns false and writes "none" (when out has room) for a
 * NULL system, a FAKE system or a device that reports no name. */
bool         audio_system_device_name(const AudioSystem *as, char *out, usize capacity);
void         audio_system_destroy(AudioSystem *as);

/* Playback devices of a backend: DEFAULT the system's, NULL miniaudio's
 * null device ("NULL Playback Device"), FAKE none. Writes up to `capacity`
 * entries (id is the index as decimal text) and returns how many exist,
 * which may exceed capacity; 0 when the backend cannot be enumerated, the
 * backend is invalid, or `out` is NULL with capacity > 0. */
u32          audio_system_list_devices(AudioBackend backend, AudioDeviceInfo *out, u32 capacity);
/* audio_system_create_ex opening the playback device with this name (as
 * audio_system_list_devices reports it); DEFAULT tries its backends in
 * miniaudio's order and opens the first one that has the name. NULL or ""
 * opens the default device. REJECTED for a FAKE backend with a name or a
 * name no backend has, FAILED when the system does not open, INVALID for a
 * NULL out or an invalid backend. *out is written only on success. */
AudioResult  audio_system_create_named(AudioBackend backend, const char *device_name,
                                       AudioSystem **out);
/* Opens the named playback device (NULL or "": the default) while the old
 * one keeps playing, then closes the old one and starts the new one in its
 * place. Sources, buses, the listener and the reference tap are kept. OK
 * selects the name for later reopens and counts one in
 * audio_system_recoveries. REJECTED for a name no device has (or any name
 * on FAKE) and for a name of 128 bytes or more. FAILED when the new device
 * does not open (nothing changes) or does not start: then the previous
 * selection is kept and the previous device is opened again, without a
 * recovery count; if that does not open or start either, the system stays
 * without a playing device until audio_system_reopen succeeds. A FAKE
 * system only clears the selection. INVALID for NULL. The owner thread,
 * like audio_system_reopen. */
AudioResult  audio_system_switch_device(AudioSystem *as, const char *device_name);
/* The selected playback device name into out; false and "" when the
 * default is selected or for NULL. */
bool         audio_system_selected_device(const AudioSystem *as, char *out, usize capacity);

typedef enum {
    AUDIO_SYSTEM_EVENT_DEVICE_LOST = 0,
    /* Simulation only: the next audio_system_reopen fails with AUDIO_FAILED
     * and changes nothing. Each event refuses one reopen. */
    AUDIO_SYSTEM_EVENT_REOPEN_REFUSED,
} AudioSystemEvent;

/* The playback device has stayed out of the started state for 250 ms
 * (unplugged, disabled, taken by the system, or left closed by a failed
 * reopen), or a loss was simulated. Shorter stops, such as a backend's own
 * reroute, are not losses. False for NULL. The owner thread. */
bool         audio_system_lost(const AudioSystem *as);
/* Successful reopens of a lost device so far. Any thread: a reader of the
 * reference tap uses a change to drop frames that straddle the gap. */
u64          audio_system_recoveries(const AudioSystem *as);
/* Closes the playback device and opens the selected one (the default when
 * none is selected or no device has the selected name any more; the
 * selection is kept) in its place with the same format, then starts it. Sources, buses, the listener and the reference
 * tap are kept. OK clears the lost state and counts a recovery; FAILED
 * keeps it (after a real failure the system has no device until a later
 * reopen succeeds). A device that is started again, because the backend
 * restarted it, is left alone and OK is returned without a recovery. A FAKE
 * system has no device and only clears a simulated loss. INVALID for NULL. The
 * owner thread; never concurrent with audio_system_backend_name,
 * audio_system_device_name or audio_system_destroy. */
AudioResult  audio_system_reopen(AudioSystem *as);
/* FAKE and NULL backends only (tests). INVALID for NULL or an unknown event,
 * REJECTED for the DEFAULT backend. */
AudioResult  audio_system_simulate_event(AudioSystem *as, AudioSystemEvent event);
void         audio_system_update(AudioSystem *as, Vec3 listener_pos, Vec3 forward, Vec3 up);

u32          audio_play(AudioSystem *as, const char *path, f32 volume, bool looping);
void         audio_play_3d(AudioSystem *as, const char *path, Vec3 position, f32 volume, bool looping);
/* audio_play_3d that returns the source handle (0 on failure), so the caller
 * can move or stop exactly the source it started. */
u32          audio_play_3d_source(AudioSystem *as, const char *path, Vec3 position,
                                  f32 volume, bool looping);
void         audio_stop(AudioSystem *as, u32 source_id);
void         audio_set_listener(AudioSystem *as, Vec3 pos, Vec3 forward, Vec3 up);

/* ---- Compatibility file playback ----
 * The complete file is decoded when opened; the audio callback reads PCM only. */
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

/* Optional final-mix reference: fixed 48 kHz mono i16, one producer and one
 * consumer. Start/stop preserve buffered frames; reset requires stopped. */
#define AUDIO_REFERENCE_RING_FRAMES 16384u
AudioResult audio_reference_start(AudioSystem *as);
AudioResult audio_reference_stop(AudioSystem *as);
AudioResult audio_reference_reset(AudioSystem *as);
AudioResult audio_reference_read_i16(AudioSystem *as, i16 *out, u32 max_frames,
                                     u32 *out_frames);
u32          audio_reference_available(const AudioSystem *as);
u64          audio_reference_overruns(const AudioSystem *as);

/* Device enumeration */
u32          audio_get_device_count(AudioSystem *sys);
bool         audio_get_device_info(AudioSystem *sys, u32 index, AudioDeviceInfo *out);

/* Device selection: records selection for next audio_system_create.
 * Returns false because miniaudio does not support runtime hot-swap;
 * caller must destroy and re-create the AudioSystem to apply. */
bool         audio_set_device(AudioSystem *sys, const char *device_id);

/* Returns currently selected device name (or "default") */
const char  *audio_get_current_device(AudioSystem *sys);
