#include "core_app_audio.h"

#include <platform/time.h>

#include <inttypes.h>
#include <string.h>

/* Bounded wait for the probe tone at shutdown: 400 polls of 5 ms. */
#define CORE_APP_AUDIO_PROBE_POLLS 400u
#define CORE_APP_AUDIO_PROBE_POLL_US 5000u

static bool sound_kind(CoreAppAudioCommandKind kind) {
    return kind == CORE_APP_AUDIO_LISTENER || kind == CORE_APP_AUDIO_PLAY_3D ||
           kind == CORE_APP_AUDIO_POSITION || kind == CORE_APP_AUDIO_STOP;
}

static const char *sound_kind_name(CoreAppAudioCommandKind kind) {
    switch (kind) {
        case CORE_APP_AUDIO_LISTENER: return "listener";
        case CORE_APP_AUDIO_PLAY_3D: return "play_3d";
        case CORE_APP_AUDIO_POSITION: return "position";
        case CORE_APP_AUDIO_STOP: return "stop";
    }
    return "unknown";
}

static void sound_reset(CoreAppAudio *audio, CoreAppAudioBackend mode) {
    memset(audio, 0, sizeof(*audio));
    audio->mode = mode;
    audio->next_sequence = 1u;
    audio->admission_open = true;
    audio->producing = true;
}

/* Only a PLAY_3D owns a slot. POSITION and STOP resolve to a slot the level
 * already plays on, so a command from an unloaded level never allocates a
 * fresh slot and never touches the new level's source. */
static u32 sound_claim_slot(CoreAppAudio *audio, u64 generation) {
    for (u32 i = 0u; i < CORE_APP_AUDIO_SOURCE_SLOTS; ++i) {
        if (audio->play_slots[i].slot != CORE_APP_AUDIO_SOURCE_INVALID &&
            audio->play_slots[i].generation == generation) {
            return audio->play_slots[i].slot;
        }
    }
    for (u32 i = 0u; i < CORE_APP_AUDIO_SOURCE_SLOTS; ++i) {
        if (audio->play_slots[i].slot == CORE_APP_AUDIO_SOURCE_INVALID) {
            audio->play_slots[i].slot = i + 1u;
            audio->play_slots[i].generation = generation;
            return audio->play_slots[i].slot;
        }
    }
    u32 index = audio->next_slot % CORE_APP_AUDIO_SOURCE_SLOTS;
    audio->next_slot++;
    audio->play_slots[index].slot = index + 1u;
    audio->play_slots[index].generation = generation;
    return audio->play_slots[index].slot;
}

static u32 sound_lookup_slot(const CoreAppAudio *audio, u64 generation) {
    for (u32 i = 0u; i < CORE_APP_AUDIO_SOURCE_SLOTS; ++i) {
        if (audio->play_slots[i].slot != CORE_APP_AUDIO_SOURCE_INVALID &&
            audio->play_slots[i].generation == generation) {
            return audio->play_slots[i].slot;
        }
    }
    return CORE_APP_AUDIO_SOURCE_INVALID;
}

static bool sound_slot_matches(const CoreAppAudio *audio, u32 slot, u64 generation) {
    if (slot == CORE_APP_AUDIO_SOURCE_INVALID) return false;
    for (u32 i = 0u; i < CORE_APP_AUDIO_SOURCE_SLOTS; ++i) {
        if (audio->play_slots[i].slot == slot) {
            return audio->play_slots[i].generation == generation;
        }
    }
    return false;
}

static void sound_retire_slot(CoreAppAudio *audio, u32 slot, u64 generation) {
    for (u32 i = 0u; i < CORE_APP_AUDIO_SOURCE_SLOTS; ++i) {
        if (audio->play_slots[i].slot == slot &&
            audio->play_slots[i].generation == generation) {
            audio->play_slots[i].slot = CORE_APP_AUDIO_SOURCE_INVALID;
            return;
        }
    }
}

BreakRuntimeError core_app_audio_start(CoreAppAudio *audio, FILE *trace) {
    if (!audio || !trace) return BREAK_RUNTIME_INVALID;
    sound_reset(audio, CORE_APP_AUDIO_BACKEND_RECORD);
    audio->trace = trace;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_audio_start_null(CoreAppAudio *audio) {
    if (!audio) return BREAK_RUNTIME_INVALID;
    sound_reset(audio, CORE_APP_AUDIO_BACKEND_NULL);
    return BREAK_RUNTIME_OK;
}

static bool sound_backend_is_device(const char *name) {
    return strcmp(name, "Null") != 0 && strcmp(name, "fake") != 0 && strcmp(name, "none") != 0;
}

static bool sound_set_path(CoreAppAudio *audio, const char *asset_root) {
    if (!asset_root) return false;
    int written = snprintf(audio->sound_path, sizeof(audio->sound_path), "%s/tone.wav",
                           asset_root);
    return written > 0 && (usize)written < sizeof(audio->sound_path);
}

/* Takes ownership of system. On a trace failure the system is destroyed. */
static BreakRuntimeError sound_attach(CoreAppAudio *audio, FILE *trace, AudioSystem *system,
                                      u32 probe) {
    audio->system = system;
    audio->probe_source = probe;
    snprintf(audio->device_backend, sizeof(audio->device_backend), "%s",
             audio_system_backend_name(system));
    (void)audio_system_device_name(system, audio->device_name, sizeof(audio->device_name));
    if (fprintf(trace, "COREAPPTRACE version=1 event=audio mode=device result=ready "
                       "backend=%s device=%s probe_source=%u\n",
                audio->device_backend, audio->device_name, probe) < 0 ||
        fflush(trace) != 0) {
        audio_system_destroy(system);
        audio->system = NULL;
        audio->trace = NULL;
        return BREAK_RUNTIME_FAILED;
    }
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_audio_start_system(CoreAppAudio *audio, FILE *trace,
                                              AudioSystem *system, const char *asset_root) {
    if (!audio || !trace || !system) return BREAK_RUNTIME_INVALID;
    sound_reset(audio, CORE_APP_AUDIO_BACKEND_DEVICE);
    if (!sound_set_path(audio, asset_root)) return BREAK_RUNTIME_INVALID;
    audio->trace = trace;
    return sound_attach(audio, trace, system, 0u);
}

BreakRuntimeError core_app_audio_start_device_backend(CoreAppAudio *audio, FILE *trace,
                                                      bool require_device,
                                                      const char *asset_root,
                                                      AudioBackend backend) {
    if (!audio || !trace) return BREAK_RUNTIME_INVALID;
    sound_reset(audio, CORE_APP_AUDIO_BACKEND_DEVICE);
    audio->trace = trace;
    AudioSystem *system = audio_system_create_ex(backend);
    const char *backend_name = audio_system_backend_name(system);
    if (system && sound_backend_is_device(backend_name)) {
        u32 probe = 0u;
        if (sound_set_path(audio, asset_root)) {
            probe = audio_play(system, audio->sound_path, 0.25f, false);
        }
        if (probe == 0u) {
            audio_system_destroy(system);
            (void)fprintf(trace, "COREAPPTRACE version=1 event=audio mode=device "
                                 "result=failed reason=probe\n");
            (void)fflush(trace);
            audio->trace = NULL;
            return BREAK_RUNTIME_FAILED;
        }
        return sound_attach(audio, trace, system, probe);
    }
    /* No playback device: either nothing opened, or only miniaudio's Null
     * backend did. Neither may be reported as a device. The backend name is a
     * static string, so it outlives the destroyed system. */
    if (system) audio_system_destroy(system);
    if (fprintf(trace, "COREAPPTRACE version=1 event=audio mode=device "
                       "result=unavailable backend=%s fallback=%s\n",
                backend_name, require_device ? "none" : "null") < 0 ||
        fflush(trace) != 0) {
        audio->trace = NULL;
        return BREAK_RUNTIME_FAILED;
    }
    if (require_device) return BREAK_RUNTIME_UNAVAILABLE;
    audio->mode = CORE_APP_AUDIO_BACKEND_NULL;
    audio->device_fallbacks = 1u;
    return BREAK_RUNTIME_UNAVAILABLE;
}

BreakRuntimeError core_app_audio_start_device(CoreAppAudio *audio, FILE *trace,
                                              bool require_device, const char *asset_root) {
    return core_app_audio_start_device_backend(audio, trace, require_device, asset_root,
                                               AUDIO_BACKEND_DEFAULT);
}

BreakRuntimeError core_app_audio_enqueue_at(CoreAppAudio *audio, CoreAppAudioCommandKind kind,
                                            u64 generation, Vec3 position) {
    if (!audio || generation == 0u || !sound_kind(kind)) return BREAK_RUNTIME_INVALID;
    if (!audio->admission_open || !audio->producing || audio->queue_closed) {
        return BREAK_RUNTIME_CLOSED;
    }
    if (audio->count >= CORE_APP_AUDIO_QUEUE_CAPACITY) {
        audio->overloads++;
        return BREAK_RUNTIME_OVERLOAD;
    }
    u32 tail = (audio->head + audio->count) % CORE_APP_AUDIO_QUEUE_CAPACITY;
    CoreAppAudioCommand *command = &audio->commands[tail];
    memset(command, 0, sizeof(*command));
    command->kind = kind;
    command->generation = generation;
    command->position = position;
    command->sequence = audio->next_sequence++;
    if (kind == CORE_APP_AUDIO_PLAY_3D) {
        command->source = sound_claim_slot(audio, generation);
    } else if (kind == CORE_APP_AUDIO_POSITION || kind == CORE_APP_AUDIO_STOP) {
        command->source = sound_lookup_slot(audio, generation);
    }
    audio->count++;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_audio_enqueue(CoreAppAudio *audio, CoreAppAudioCommandKind kind,
                                         u64 generation) {
    return core_app_audio_enqueue_at(audio, kind, generation, vec3(0.0f, 0.0f, 0.0f));
}

/* Applies one admitted command to the device. POSITION and STOP have already
 * passed the generation check, so their slot belongs to this level. */
static void sound_apply_device(CoreAppAudio *audio, const CoreAppAudioCommand *command) {
    AudioSystem *system = audio->system;
    if (command->kind == CORE_APP_AUDIO_LISTENER) {
        audio_set_listener(system, command->position, vec3(0.0f, 0.0f, -1.0f),
                           vec3(0.0f, 1.0f, 0.0f));
        audio->device_listener_updates++;
        return;
    }
    if (command->source == CORE_APP_AUDIO_SOURCE_INVALID ||
        command->source > CORE_APP_AUDIO_SOURCE_SLOTS) {
        audio->device_failures++;
        return;
    }
    u32 *handle = &audio->device_sources[command->source - 1u];
    if (command->kind == CORE_APP_AUDIO_PLAY_3D) {
        /* A reused slot still holds the displaced source: stop it so the
         * device never keeps a source no level can address any more. */
        if (*handle != 0u) {
            audio_stop(system, *handle);
            *handle = 0u;
            audio->device_evictions++;
        }
        u32 started = audio_play_3d_source(system, audio->sound_path, command->position, 0.5f,
                                           false);
        if (started == 0u) {
            audio->device_failures++;
        } else {
            *handle = started;
            audio->device_plays++;
        }
    } else if (command->kind == CORE_APP_AUDIO_POSITION) {
        if (*handle != 0u) {
            audio_source_set_position(system, *handle, command->position);
            audio->device_moves++;
        }
    } else if (command->kind == CORE_APP_AUDIO_STOP) {
        if (*handle != 0u) {
            audio_stop(system, *handle);
            *handle = 0u;
            audio->device_stops++;
        }
    }
}

static BreakRuntimeError sound_consume(CoreAppAudio *audio, const CoreAppAudioCommand *command,
                                       bool device) {
    if (command->kind == CORE_APP_AUDIO_POSITION || command->kind == CORE_APP_AUDIO_STOP) {
        if (!sound_slot_matches(audio, command->source, command->generation)) {
            audio->stale_commands++;
            return BREAK_RUNTIME_OK;
        }
        if (command->kind == CORE_APP_AUDIO_STOP) {
            sound_retire_slot(audio, command->source, command->generation);
        }
    }
    if (device) sound_apply_device(audio, command);
    if (!audio->trace) return BREAK_RUNTIME_OK;
    if (fprintf(audio->trace,
                "COREAPPTRACE version=1 event=audio kind=%s generation=%" PRIu64
                " sequence=%" PRIu64 " source=%u\n",
                sound_kind_name(command->kind), command->generation, command->sequence,
                command->source) < 0 ||
        fflush(audio->trace) != 0) {
        return BREAK_RUNTIME_FAILED;
    }
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError sound_drain(CoreAppAudio *audio, u32 budget, bool device) {
    while (budget > 0u && audio->count > 0u) {
        CoreAppAudioCommand command = audio->commands[audio->head];
        BreakRuntimeError result = sound_consume(audio, &command, device);
        if (result != BREAK_RUNTIME_OK) return result;
        audio->head = (audio->head + 1u) % CORE_APP_AUDIO_QUEUE_CAPACITY;
        audio->count--;
        budget--;
    }
    return audio->count == 0u ? BREAK_RUNTIME_OK : BREAK_RUNTIME_TIMEOUT;
}

BreakRuntimeError core_app_audio_drain_record(CoreAppAudio *audio, u32 budget) {
    if (!audio || !audio->trace) return BREAK_RUNTIME_INVALID;
    return sound_drain(audio, budget, false);
}

BreakRuntimeError core_app_audio_drain_null(CoreAppAudio *audio, u32 budget) {
    if (!audio) return BREAK_RUNTIME_INVALID;
    return sound_drain(audio, budget, false);
}

BreakRuntimeError core_app_audio_drain_device(CoreAppAudio *audio, u32 budget) {
    if (!audio || !audio->system) return BREAK_RUNTIME_INVALID;
    return sound_drain(audio, budget, true);
}

BreakRuntimeError core_app_audio_stop_admission(CoreAppAudio *audio) {
    if (!audio) return BREAK_RUNTIME_INVALID;
    audio->admission_open = false;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_audio_stop_producers(CoreAppAudio *audio) {
    if (!audio) return BREAK_RUNTIME_INVALID;
    audio->producing = false;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_audio_close_queues(CoreAppAudio *audio) {
    if (!audio) return BREAK_RUNTIME_INVALID;
    audio->queue_closed = true;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_audio_join(CoreAppAudio *audio) {
    if (!audio) return BREAK_RUNTIME_INVALID;
    if (audio->count != 0u) return BREAK_RUNTIME_TIMEOUT;
    audio->joined = true;
    return BREAK_RUNTIME_OK;
}

/* Waits (bounded) for the probe tone, records how far the device actually
 * played it, then stops the source and closes the device. */
static BreakRuntimeError sound_close_device(CoreAppAudio *audio) {
    if (!audio->system) return BREAK_RUNTIME_OK;
    bool has_probe = audio->probe_source != 0u;
    bool complete = false;
    f32 played = 0.0f;
    if (has_probe) {
        for (u32 poll = 0u; poll < CORE_APP_AUDIO_PROBE_POLLS; ++poll) {
            if (audio_source_at_end(audio->system, audio->probe_source)) {
                complete = true;
                break;
            }
            time_sleep_us(CORE_APP_AUDIO_PROBE_POLL_US);
        }
        played = audio_source_cursor_seconds(audio->system, audio->probe_source);
        audio_source_stop(audio->system, audio->probe_source);
    }
    /* Destroying the system releases every source still held in a slot. */
    audio_system_destroy(audio->system);
    audio->system = NULL;
    audio->probe_source = 0u;
    memset(audio->device_sources, 0, sizeof(audio->device_sources));
    if (!audio->trace) return BREAK_RUNTIME_OK;
    if (fprintf(audio->trace,
                "COREAPPTRACE version=1 event=audio mode=device result=stopped backend=%s "
                "probe_complete=%u probe_seconds=%.3f failures=%" PRIu64
                " listener_updates=%" PRIu64 " plays=%" PRIu64 " moves=%" PRIu64
                " stops=%" PRIu64 " evictions=%" PRIu64 "\n",
                audio->device_backend, complete ? 1u : 0u, (double)played,
                audio->device_failures, audio->device_listener_updates, audio->device_plays,
                audio->device_moves, audio->device_stops, audio->device_evictions) < 0 ||
        fflush(audio->trace) != 0) {
        return BREAK_RUNTIME_FAILED;
    }
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_audio_destroy(CoreAppAudio *audio) {
    if (!audio) return BREAK_RUNTIME_INVALID;
    if (!audio->joined || audio->count != 0u) return BREAK_RUNTIME_REJECTED;
    BreakRuntimeError result = sound_close_device(audio);
    audio->trace = NULL;
    return result;
}
