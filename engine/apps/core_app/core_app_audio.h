#pragma once

#include <audio/audio.h>
#include <core/types.h>
#include <runtime/runtime_types.h>

#include <stdio.h>

#define CORE_APP_AUDIO_QUEUE_CAPACITY 256u
#define CORE_APP_AUDIO_SOURCE_SLOTS 8u
#define CORE_APP_AUDIO_SOURCE_INVALID 0u

typedef enum CoreAppAudioCommandKind {
    CORE_APP_AUDIO_LISTENER = 1,
    CORE_APP_AUDIO_PLAY_3D = 2,
    CORE_APP_AUDIO_POSITION = 3,
    CORE_APP_AUDIO_STOP = 4
} CoreAppAudioCommandKind;

typedef enum CoreAppAudioBackend {
    CORE_APP_AUDIO_BACKEND_RECORD = 0,
    CORE_APP_AUDIO_BACKEND_NULL,
    CORE_APP_AUDIO_BACKEND_DEVICE
} CoreAppAudioBackend;

typedef struct CoreAppAudioCommand {
    u64 generation;
    u64 sequence;
    Vec3 position;
    CoreAppAudioCommandKind kind;
    u32 source;
} CoreAppAudioCommand;

typedef struct CoreAppAudioSlot {
    u32 slot;
    u64 generation;
} CoreAppAudioSlot;

typedef struct CoreAppAudio {
    CoreAppAudioCommand commands[CORE_APP_AUDIO_QUEUE_CAPACITY];
    CoreAppAudioSlot play_slots[CORE_APP_AUDIO_SOURCE_SLOTS];
    FILE *trace;
    /* Device mode only: the opened playback system and the probe source that
     * proves the device consumed frames. NULL in record and null modes. */
    AudioSystem *system;
    u32 probe_source;
    /* Device handle behind each play slot (index = slot - 1), 0 when idle. */
    u32 device_sources[CORE_APP_AUDIO_SOURCE_SLOTS];
    u64 device_listener_updates;
    u64 device_plays;
    u64 device_moves;
    u64 device_stops;
    u64 device_evictions;
    u64 device_failures;
    char device_backend[32];
    char device_name[128];
    char sound_path[1024];
    u64 next_sequence;
    u64 overloads;
    u64 stale_commands;
    u64 device_fallbacks;
    u32 next_slot;
    u32 head;
    u32 count;
    CoreAppAudioBackend mode;
    bool admission_open;
    bool producing;
    bool queue_closed;
    bool joined;
} CoreAppAudio;

BreakRuntimeError core_app_audio_start(CoreAppAudio *audio, FILE *trace);
BreakRuntimeError core_app_audio_start_null(CoreAppAudio *audio);
/* Opens the default playback device. A system that only reaches miniaudio's
 * Null backend, or that has no device at all, is reported as unavailable:
 * a required device then returns UNAVAILABLE, an optional one degrades to the
 * null pump. A real device plays asset_root/tone.wav once as a probe. */
BreakRuntimeError core_app_audio_start_device(CoreAppAudio *audio, FILE *trace,
                                              bool require_device, const char *asset_root);
/* Same contract with an explicit engine backend; tests force NULL or FAKE to
 * exercise the unavailable path deterministically. */
BreakRuntimeError core_app_audio_start_device_backend(CoreAppAudio *audio, FILE *trace,
                                                      bool require_device,
                                                      const char *asset_root,
                                                      AudioBackend backend);
/* Takes ownership of an already created system and drives it from the
 * command queue; no probe tone is played. Returns INVALID (system not taken)
 * for a missing argument or an asset path that does not fit; on any later
 * failure the system is destroyed. */
BreakRuntimeError core_app_audio_start_system(CoreAppAudio *audio, FILE *trace,
                                              AudioSystem *system, const char *asset_root);
BreakRuntimeError core_app_audio_enqueue(CoreAppAudio *audio, CoreAppAudioCommandKind kind,
                                         u64 generation);
/* enqueue with a world position: the listener position for LISTENER, the
 * source position for PLAY_3D and POSITION; ignored for STOP. */
BreakRuntimeError core_app_audio_enqueue_at(CoreAppAudio *audio, CoreAppAudioCommandKind kind,
                                            u64 generation, Vec3 position);
BreakRuntimeError core_app_audio_drain_record(CoreAppAudio *audio, u32 budget);
BreakRuntimeError core_app_audio_drain_null(CoreAppAudio *audio, u32 budget);
/* Device mode: each command becomes the matching AudioSystem call. INVALID
 * when no device system is attached. */
BreakRuntimeError core_app_audio_drain_device(CoreAppAudio *audio, u32 budget);
BreakRuntimeError core_app_audio_stop_admission(CoreAppAudio *audio);
BreakRuntimeError core_app_audio_stop_producers(CoreAppAudio *audio);
BreakRuntimeError core_app_audio_close_queues(CoreAppAudio *audio);
BreakRuntimeError core_app_audio_join(CoreAppAudio *audio);
BreakRuntimeError core_app_audio_destroy(CoreAppAudio *audio);
