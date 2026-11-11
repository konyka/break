#pragma once

#include <core/types.h>
#include <runtime/runtime_types.h>

#include <stdio.h>

/* Task 3 record-only bound; Task 9 must expand this to 256 and test overflow. */
#define CORE_APP_AUDIO_QUEUE_CAPACITY 16u

typedef enum CoreAppAudioCommandKind {
    CORE_APP_AUDIO_LISTENER = 1,
    CORE_APP_AUDIO_STOP = 2
} CoreAppAudioCommandKind;

typedef struct CoreAppAudioCommand {
    u64 generation;
    u64 sequence;
    CoreAppAudioCommandKind kind;
} CoreAppAudioCommand;

typedef struct CoreAppAudio {
    CoreAppAudioCommand commands[CORE_APP_AUDIO_QUEUE_CAPACITY];
    FILE *trace;
    u64 next_sequence;
    u32 head;
    u32 count;
    bool admission_open;
    bool producing;
    bool queue_closed;
    bool joined;
} CoreAppAudio;

BreakRuntimeError core_app_audio_start(CoreAppAudio *audio, FILE *trace);
BreakRuntimeError core_app_audio_enqueue(CoreAppAudio *audio, CoreAppAudioCommandKind kind,
                                     u64 generation);
BreakRuntimeError core_app_audio_drain_record(CoreAppAudio *audio, u32 budget);
BreakRuntimeError core_app_audio_stop_admission(CoreAppAudio *audio);
BreakRuntimeError core_app_audio_stop_producers(CoreAppAudio *audio);
BreakRuntimeError core_app_audio_close_queues(CoreAppAudio *audio);
BreakRuntimeError core_app_audio_join(CoreAppAudio *audio);
BreakRuntimeError core_app_audio_destroy(CoreAppAudio *audio);
