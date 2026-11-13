#include "core_app_audio.h"

#include <inttypes.h>
#include <string.h>

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

BreakRuntimeError core_app_audio_start_device(CoreAppAudio *audio, FILE *trace,
                                              bool require_device) {
    if (!audio || !trace) return BREAK_RUNTIME_INVALID;
    sound_reset(audio, CORE_APP_AUDIO_BACKEND_DEVICE);
    audio->trace = trace;
    /* No device backend is compiled into this application yet, so the device
     * path is honestly unavailable rather than silently pretended. A required
     * device therefore fails; an optional one degrades to the null pump and
     * keeps the rest of the runtime playable. */
    if (fprintf(trace, "COREAPPTRACE version=1 event=audio mode=device "
                       "result=unavailable fallback=%s\n",
                require_device ? "none" : "null") < 0 ||
        fflush(trace) != 0) {
        audio->trace = NULL;
        return BREAK_RUNTIME_FAILED;
    }
    if (require_device) return BREAK_RUNTIME_UNAVAILABLE;
    audio->mode = CORE_APP_AUDIO_BACKEND_NULL;
    audio->device_fallbacks = 1u;
    return BREAK_RUNTIME_UNAVAILABLE;
}

BreakRuntimeError core_app_audio_enqueue(CoreAppAudio *audio, CoreAppAudioCommandKind kind,
                                         u64 generation) {
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
    command->sequence = audio->next_sequence++;
    if (kind == CORE_APP_AUDIO_PLAY_3D) {
        command->source = sound_claim_slot(audio, generation);
    } else if (kind == CORE_APP_AUDIO_POSITION || kind == CORE_APP_AUDIO_STOP) {
        command->source = sound_lookup_slot(audio, generation);
    }
    audio->count++;
    return BREAK_RUNTIME_OK;
}

static BreakRuntimeError sound_consume(CoreAppAudio *audio, const CoreAppAudioCommand *command) {
    if (command->kind == CORE_APP_AUDIO_POSITION || command->kind == CORE_APP_AUDIO_STOP) {
        if (!sound_slot_matches(audio, command->source, command->generation)) {
            audio->stale_commands++;
            return BREAK_RUNTIME_OK;
        }
        if (command->kind == CORE_APP_AUDIO_STOP) {
            sound_retire_slot(audio, command->source, command->generation);
        }
    }
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

static BreakRuntimeError sound_drain(CoreAppAudio *audio, u32 budget) {
    while (budget > 0u && audio->count > 0u) {
        CoreAppAudioCommand command = audio->commands[audio->head];
        BreakRuntimeError result = sound_consume(audio, &command);
        if (result != BREAK_RUNTIME_OK) return result;
        audio->head = (audio->head + 1u) % CORE_APP_AUDIO_QUEUE_CAPACITY;
        audio->count--;
        budget--;
    }
    return audio->count == 0u ? BREAK_RUNTIME_OK : BREAK_RUNTIME_TIMEOUT;
}

BreakRuntimeError core_app_audio_drain_record(CoreAppAudio *audio, u32 budget) {
    if (!audio || !audio->trace) return BREAK_RUNTIME_INVALID;
    return sound_drain(audio, budget);
}

BreakRuntimeError core_app_audio_drain_null(CoreAppAudio *audio, u32 budget) {
    if (!audio) return BREAK_RUNTIME_INVALID;
    return sound_drain(audio, budget);
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

BreakRuntimeError core_app_audio_destroy(CoreAppAudio *audio) {
    if (!audio) return BREAK_RUNTIME_INVALID;
    if (!audio->joined || audio->count != 0u) return BREAK_RUNTIME_REJECTED;
    audio->trace = NULL;
    return BREAK_RUNTIME_OK;
}
