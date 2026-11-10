#pragma once

#include <core/types.h>
#include <runtime/runtime_types.h>

#include <stdio.h>

#define GAME_AUDIO_QUEUE_CAPACITY 16u

typedef enum GameAudioCommandKind {
    GAME_AUDIO_LISTENER = 1,
    GAME_AUDIO_STOP = 2
} GameAudioCommandKind;

typedef struct GameAudioCommand {
    u64 generation;
    u64 sequence;
    GameAudioCommandKind kind;
} GameAudioCommand;

typedef struct GameAudio {
    GameAudioCommand commands[GAME_AUDIO_QUEUE_CAPACITY];
    FILE *trace;
    u64 next_sequence;
    u32 head;
    u32 count;
    bool admission_open;
    bool producing;
    bool queue_closed;
    bool joined;
} GameAudio;

BreakRuntimeError game_audio_start(GameAudio *audio, FILE *trace);
BreakRuntimeError game_audio_enqueue(GameAudio *audio, GameAudioCommandKind kind,
                                     u64 generation);
BreakRuntimeError game_audio_drain_record(GameAudio *audio, u32 budget);
BreakRuntimeError game_audio_stop_admission(GameAudio *audio);
BreakRuntimeError game_audio_stop_producers(GameAudio *audio);
BreakRuntimeError game_audio_close_queues(GameAudio *audio);
BreakRuntimeError game_audio_join(GameAudio *audio);
BreakRuntimeError game_audio_destroy(GameAudio *audio);
