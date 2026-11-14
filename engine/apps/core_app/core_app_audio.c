#include "core_app_audio.h"

#include <core/platform_thread.h>
#include <platform/time.h>

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

/* Bounded wait for the probe tone at shutdown: 400 polls of 5 ms. */
#define CORE_APP_AUDIO_PROBE_POLLS 400u
#define CORE_APP_AUDIO_PROBE_POLL_US 5000u

/* Device mode owner thread. The mutex guards the queue (head, count, the
 * commands), the play slots and the counters the producer touches; the
 * device itself and its counters belong to the owner alone. */
typedef struct CoreAppAudioOwner CoreAppAudioOwner;

struct CoreAppAudioOwner {
    PlatformThread thread;
    PlatformMutex mutex;
    PlatformCond work;
    PlatformCond idle;
    PlatformThreadId id;
    BreakRuntimeError error;
    BreakRuntimeError close_result;
    bool started;
    bool stop;
    bool busy;
    bool exited;
    bool joined;
};

static BreakRuntimeError sound_start_owner(CoreAppAudio *audio);

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

static const char *sound_name(CoreAppAudioSound sound) {
    switch (sound) {
        case CORE_APP_AUDIO_SOUND_NONE: return "none";
        case CORE_APP_AUDIO_SOUND_CHASER: return "chaser";
        case CORE_APP_AUDIO_SOUND_ITEM: return "item";
    }
    return "unknown";
}

static bool sound_fits_kind(CoreAppAudioCommandKind kind, CoreAppAudioSound sound) {
    if (kind == CORE_APP_AUDIO_LISTENER) return sound == CORE_APP_AUDIO_SOUND_NONE;
    return sound == CORE_APP_AUDIO_SOUND_CHASER || sound == CORE_APP_AUDIO_SOUND_ITEM;
}

static bool sound_slot_is(const CoreAppAudioSlot *slot, u64 generation,
                          CoreAppAudioSound sound) {
    return slot->slot != CORE_APP_AUDIO_SOURCE_INVALID && slot->generation == generation &&
           slot->sound == sound;
}

/* Only a PLAY_3D owns a slot, one per (generation, sound). POSITION and STOP
 * resolve to the slot that sound of the level already plays on, so a command
 * from an unloaded level never allocates a fresh slot and never touches the
 * new level's sources, and one sound never moves or stops another. */
static u32 sound_claim_slot(CoreAppAudio *audio, u64 generation, CoreAppAudioSound sound) {
    for (u32 i = 0u; i < CORE_APP_AUDIO_SOURCE_SLOTS; ++i) {
        if (sound_slot_is(&audio->play_slots[i], generation, sound)) {
            return audio->play_slots[i].slot;
        }
    }
    u32 index = CORE_APP_AUDIO_SOURCE_SLOTS;
    for (u32 i = 0u; i < CORE_APP_AUDIO_SOURCE_SLOTS; ++i) {
        if (audio->play_slots[i].slot == CORE_APP_AUDIO_SOURCE_INVALID) {
            index = i;
            break;
        }
    }
    if (index == CORE_APP_AUDIO_SOURCE_SLOTS) {
        index = audio->next_slot % CORE_APP_AUDIO_SOURCE_SLOTS;
        audio->next_slot++;
    }
    audio->play_slots[index].slot = index + 1u;
    audio->play_slots[index].generation = generation;
    audio->play_slots[index].sound = sound;
    return audio->play_slots[index].slot;
}

static u32 sound_lookup_slot(const CoreAppAudio *audio, u64 generation,
                             CoreAppAudioSound sound) {
    for (u32 i = 0u; i < CORE_APP_AUDIO_SOURCE_SLOTS; ++i) {
        if (sound_slot_is(&audio->play_slots[i], generation, sound)) {
            return audio->play_slots[i].slot;
        }
    }
    return CORE_APP_AUDIO_SOURCE_INVALID;
}

static bool sound_slot_matches(const CoreAppAudio *audio, u32 slot, u64 generation,
                               CoreAppAudioSound sound) {
    if (slot == CORE_APP_AUDIO_SOURCE_INVALID) return false;
    for (u32 i = 0u; i < CORE_APP_AUDIO_SOURCE_SLOTS; ++i) {
        if (audio->play_slots[i].slot == slot) {
            return audio->play_slots[i].generation == generation &&
                   audio->play_slots[i].sound == sound;
        }
    }
    return false;
}

static void sound_retire_slot(CoreAppAudio *audio, u32 slot, u64 generation,
                              CoreAppAudioSound sound) {
    for (u32 i = 0u; i < CORE_APP_AUDIO_SOURCE_SLOTS; ++i) {
        if (audio->play_slots[i].slot == slot &&
            sound_slot_is(&audio->play_slots[i], generation, sound)) {
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
    static const char *const files[CORE_APP_AUDIO_SOUND_COUNT] = {NULL, "tone.wav",
                                                                 "chime.wav"};
    if (!asset_root) return false;
    for (u32 sound = 0u; sound < CORE_APP_AUDIO_SOUND_COUNT; ++sound) {
        char *path = audio->sound_paths[sound];
        path[0] = '\0';
        if (!files[sound]) continue;
        int written = snprintf(path, sizeof(audio->sound_paths[sound]), "%s/%s", asset_root,
                               files[sound]);
        if (written <= 0 || (usize)written >= sizeof(audio->sound_paths[sound])) return false;
    }
    return true;
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

BreakRuntimeError core_app_audio_start_system_owned(CoreAppAudio *audio, FILE *trace,
                                                    AudioSystem *system,
                                                    const char *asset_root) {
    BreakRuntimeError result = core_app_audio_start_system(audio, trace, system, asset_root);
    if (result != BREAK_RUNTIME_OK) return result;
    return sound_start_owner(audio);
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
            probe = audio_play(system, audio->sound_paths[CORE_APP_AUDIO_SOUND_CHASER],
                               0.25f, false);
        }
        if (probe == 0u) {
            audio_system_destroy(system);
            (void)fprintf(trace, "COREAPPTRACE version=1 event=audio mode=device "
                                 "result=failed reason=probe\n");
            (void)fflush(trace);
            audio->trace = NULL;
            return BREAK_RUNTIME_FAILED;
        }
        BreakRuntimeError attached = sound_attach(audio, trace, system, probe);
        if (attached != BREAK_RUNTIME_OK) return attached;
        return sound_start_owner(audio);
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

static BreakRuntimeError sound_enqueue_locked(CoreAppAudio *audio, CoreAppAudioCommandKind kind,
                                              u64 generation, CoreAppAudioSound sound,
                                              Vec3 position) {
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
    command->sound = sound;
    command->sequence = audio->next_sequence++;
    if (kind == CORE_APP_AUDIO_PLAY_3D) {
        command->source = sound_claim_slot(audio, generation, sound);
    } else if (kind == CORE_APP_AUDIO_POSITION || kind == CORE_APP_AUDIO_STOP) {
        command->source = sound_lookup_slot(audio, generation, sound);
    }
    audio->count++;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_audio_enqueue_sound(CoreAppAudio *audio,
                                               CoreAppAudioCommandKind kind, u64 generation,
                                               CoreAppAudioSound sound, Vec3 position) {
    if (!audio || generation == 0u || !sound_kind(kind) || !sound_fits_kind(kind, sound)) {
        return BREAK_RUNTIME_INVALID;
    }
    CoreAppAudioOwner *owner = audio->owner;
    if (!owner) return sound_enqueue_locked(audio, kind, generation, sound, position);
    platform_mutex_lock(&owner->mutex);
    BreakRuntimeError result = sound_enqueue_locked(audio, kind, generation, sound, position);
    if (result == BREAK_RUNTIME_OK) platform_cond_signal(&owner->work);
    platform_mutex_unlock(&owner->mutex);
    return result;
}

BreakRuntimeError core_app_audio_enqueue_at(CoreAppAudio *audio, CoreAppAudioCommandKind kind,
                                            u64 generation, Vec3 position) {
    CoreAppAudioSound sound = kind == CORE_APP_AUDIO_LISTENER ? CORE_APP_AUDIO_SOUND_NONE
                                                              : CORE_APP_AUDIO_SOUND_CHASER;
    return core_app_audio_enqueue_sound(audio, kind, generation, sound, position);
}

BreakRuntimeError core_app_audio_enqueue(CoreAppAudio *audio, CoreAppAudioCommandKind kind,
                                         u64 generation) {
    return core_app_audio_enqueue_at(audio, kind, generation, vec3(0.0f, 0.0f, 0.0f));
}

/* Applies one admitted command to the device. POSITION and STOP have already
 * passed the generation check, so their slot belongs to this level. */
static bool sound_on_owner(const CoreAppAudio *audio) {
    return audio->owner &&
           platform_thread_id_equal(platform_thread_current_id(), audio->owner->id);
}

static void sound_apply_device(CoreAppAudio *audio, const CoreAppAudioCommand *command) {
    AudioSystem *system = audio->system;
    if (sound_on_owner(audio)) {
        audio->device_calls_on_owner++;
    } else {
        audio->device_calls_off_owner++;
    }
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
        u32 started = audio_play_3d_source(system, audio->sound_paths[command->sound],
                                           command->position, 0.5f, false);
        if (started == 0u) {
            audio->device_failures++;
        } else {
            *handle = started;
            audio->device_plays++;
            audio->device_plays_by_sound[command->sound]++;
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

/* Generation check for POSITION and STOP; a STOP retires its slot. Runs
 * under the owner lock when there is an owner, since enqueue claims slots. */
static bool sound_admit(CoreAppAudio *audio, const CoreAppAudioCommand *command) {
    if (command->kind == CORE_APP_AUDIO_POSITION || command->kind == CORE_APP_AUDIO_STOP) {
        if (!sound_slot_matches(audio, command->source, command->generation,
                                command->sound)) {
            audio->stale_commands++;
            return false;
        }
        if (command->kind == CORE_APP_AUDIO_STOP) {
            sound_retire_slot(audio, command->source, command->generation, command->sound);
        }
    }
    return true;
}

static BreakRuntimeError sound_emit(CoreAppAudio *audio, const CoreAppAudioCommand *command,
                                    bool device) {
    if (device) sound_apply_device(audio, command);
    if (!audio->trace) return BREAK_RUNTIME_OK;
    if (fprintf(audio->trace,
                "COREAPPTRACE version=1 event=audio kind=%s generation=%" PRIu64
                " sequence=%" PRIu64 " source=%u sound=%s\n",
                sound_kind_name(command->kind), command->generation, command->sequence,
                command->source, sound_name(command->sound)) < 0 ||
        fflush(audio->trace) != 0) {
        return BREAK_RUNTIME_FAILED;
    }
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError sound_consume(CoreAppAudio *audio, const CoreAppAudioCommand *command,
                                       bool device) {
    if (!sound_admit(audio, command)) return BREAK_RUNTIME_OK;
    return sound_emit(audio, command, device);
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
    CoreAppAudioOwner *owner = audio->owner;
    if (!owner) return sound_drain(audio, budget, true);
    platform_mutex_lock(&owner->mutex);
    platform_cond_signal(&owner->work);
    BreakRuntimeError result = owner->error;
    platform_mutex_unlock(&owner->mutex);
    return result;
}

BreakRuntimeError core_app_audio_flush(CoreAppAudio *audio) {
    if (!audio) return BREAK_RUNTIME_INVALID;
    CoreAppAudioOwner *owner = audio->owner;
    if (!owner) return audio->count == 0u ? BREAK_RUNTIME_OK : BREAK_RUNTIME_TIMEOUT;
    platform_mutex_lock(&owner->mutex);
    platform_cond_signal(&owner->work);
    while ((audio->count > 0u || owner->busy) && !owner->exited) {
        platform_cond_wait(&owner->idle, &owner->mutex);
    }
    BreakRuntimeError result = owner->error;
    platform_mutex_unlock(&owner->mutex);
    return result;
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
    CoreAppAudioOwner *owner = audio->owner;
    if (owner) {
        if (!owner->joined) {
            platform_mutex_lock(&owner->mutex);
            owner->stop = true;
            platform_cond_signal(&owner->work);
            platform_mutex_unlock(&owner->mutex);
            platform_thread_join(owner->thread);
            owner->joined = true;
        }
        audio->joined = true;
        return owner->error;
    }
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
                " stops=%" PRIu64 " evictions=%" PRIu64 " item_plays=%" PRIu64
                " owner_thread=%u\n",
                audio->device_backend, complete ? 1u : 0u, (double)played,
                audio->device_failures, audio->device_listener_updates, audio->device_plays,
                audio->device_moves, audio->device_stops, audio->device_evictions,
                audio->device_plays_by_sound[CORE_APP_AUDIO_SOUND_ITEM], sound_on_owner(audio) ? 1u : 0u) < 0 ||
        fflush(audio->trace) != 0) {
        return BREAK_RUNTIME_FAILED;
    }
    return BREAK_RUNTIME_OK;
}

/* Pops one command at a time under the lock (generation check and slot
 * retirement included), then calls the device and writes the trace outside
 * it. Leaves only once stop is set and the queue is empty, and closes the
 * device itself, so after start every AudioSystem call is made here. After
 * a failure the remaining commands are consumed without reaching the device. */
static PLATFORM_THREAD_RET sound_owner_main(PLATFORM_THREAD_ARG arg) {
    CoreAppAudio *audio = (CoreAppAudio *)arg;
    CoreAppAudioOwner *owner = audio->owner;
    platform_mutex_lock(&owner->mutex);
    owner->id = platform_thread_current_id();
    owner->started = true;
    platform_cond_broadcast(&owner->idle);
    for (;;) {
        while (audio->count == 0u && !owner->stop) {
            platform_cond_wait(&owner->work, &owner->mutex);
        }
        if (audio->count == 0u) break;
        CoreAppAudioCommand command = audio->commands[audio->head];
        audio->head = (audio->head + 1u) % CORE_APP_AUDIO_QUEUE_CAPACITY;
        audio->count--;
        bool admitted = sound_admit(audio, &command);
        bool healthy = owner->error == BREAK_RUNTIME_OK;
        owner->busy = true;
        platform_mutex_unlock(&owner->mutex);
        BreakRuntimeError result = BREAK_RUNTIME_OK;
        if (admitted && healthy) result = sound_emit(audio, &command, true);
        platform_mutex_lock(&owner->mutex);
        if (result != BREAK_RUNTIME_OK && owner->error == BREAK_RUNTIME_OK) {
            owner->error = result;
        }
        owner->busy = false;
        if (audio->count == 0u) platform_cond_broadcast(&owner->idle);
    }
    platform_mutex_unlock(&owner->mutex);
    BreakRuntimeError closed = sound_close_device(audio);
    platform_mutex_lock(&owner->mutex);
    owner->close_result = closed;
    owner->exited = true;
    platform_cond_broadcast(&owner->idle);
    platform_mutex_unlock(&owner->mutex);
    return PLATFORM_THREAD_RETURN;
}

/* Hands the attached system to a new owner thread. If the thread cannot be
 * started the system is destroyed, like any other failure after attach. */
static BreakRuntimeError sound_start_owner(CoreAppAudio *audio) {
    CoreAppAudioOwner *owner = (CoreAppAudioOwner *)calloc(1u, sizeof(*owner));
    if (owner) {
        platform_mutex_init(&owner->mutex);
        platform_cond_init(&owner->work);
        platform_cond_init(&owner->idle);
        audio->owner = owner;
        if (platform_thread_create(&owner->thread, sound_owner_main, audio)) {
            platform_mutex_lock(&owner->mutex);
            while (!owner->started) platform_cond_wait(&owner->idle, &owner->mutex);
            platform_mutex_unlock(&owner->mutex);
            return BREAK_RUNTIME_OK;
        }
        audio->owner = NULL;
        platform_cond_destroy(&owner->idle);
        platform_cond_destroy(&owner->work);
        platform_mutex_destroy(&owner->mutex);
        free(owner);
    }
    audio_system_destroy(audio->system);
    audio->system = NULL;
    audio->probe_source = 0u;
    audio->trace = NULL;
    return BREAK_RUNTIME_FAILED;
}

BreakRuntimeError core_app_audio_destroy(CoreAppAudio *audio) {
    if (!audio) return BREAK_RUNTIME_INVALID;
    if (!audio->joined || audio->count != 0u) return BREAK_RUNTIME_REJECTED;
    CoreAppAudioOwner *owner = audio->owner;
    if (owner) {
        BreakRuntimeError closed = owner->close_result;
        platform_cond_destroy(&owner->idle);
        platform_cond_destroy(&owner->work);
        platform_mutex_destroy(&owner->mutex);
        free(owner);
        audio->owner = NULL;
        audio->trace = NULL;
        return closed;
    }
    BreakRuntimeError result = sound_close_device(audio);
    audio->trace = NULL;
    return result;
}
