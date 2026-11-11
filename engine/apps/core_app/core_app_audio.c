#include "core_app_audio.h"

#include <inttypes.h>
#include <string.h>

BreakRuntimeError core_app_audio_start(CoreAppAudio *audio, FILE *trace) {
    if (!audio || !trace) return BREAK_RUNTIME_INVALID;
    memset(audio, 0, sizeof(*audio));
    audio->trace = trace;
    audio->next_sequence = 1u;
    audio->admission_open = true;
    audio->producing = true;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_audio_enqueue(CoreAppAudio *audio, CoreAppAudioCommandKind kind,
                                     u64 generation) {
    if (!audio || generation == 0u ||
        (kind != CORE_APP_AUDIO_LISTENER && kind != CORE_APP_AUDIO_STOP)) {
        return BREAK_RUNTIME_INVALID;
    }
    if (!audio->admission_open || !audio->producing || audio->queue_closed) {
        return BREAK_RUNTIME_CLOSED;
    }
    if (audio->count >= CORE_APP_AUDIO_QUEUE_CAPACITY) return BREAK_RUNTIME_OVERLOAD;
    u32 tail = (audio->head + audio->count) % CORE_APP_AUDIO_QUEUE_CAPACITY;
    CoreAppAudioCommand *command = &audio->commands[tail];
    memset(command, 0, sizeof(*command));
    command->kind = kind;
    command->generation = generation;
    command->sequence = audio->next_sequence++;
    audio->count++;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_audio_drain_record(CoreAppAudio *audio, u32 budget) {
    if (!audio || !audio->trace) return BREAK_RUNTIME_INVALID;
    while (budget > 0u && audio->count > 0u) {
        CoreAppAudioCommand command = audio->commands[audio->head];
        const char *kind = command.kind == CORE_APP_AUDIO_LISTENER ? "listener" : "stop";
        if (fprintf(audio->trace,
                    "GAMEAPPTRACE version=1 event=audio kind=%s generation=%" PRIu64
                    "\n", kind, command.generation) < 0 ||
            fflush(audio->trace) != 0) {
            return BREAK_RUNTIME_FAILED;
        }
        audio->head = (audio->head + 1u) % CORE_APP_AUDIO_QUEUE_CAPACITY;
        audio->count--;
        budget--;
    }
    return audio->count == 0u ? BREAK_RUNTIME_OK : BREAK_RUNTIME_TIMEOUT;
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
