#pragma once

#include <core/types.h>
#include <runtime/runtime_types.h>

#include <stdio.h>

#define GAME_RENDER_RESOURCE_CAPACITY 64u

typedef struct GameRenderResource {
    u64 id;
    u64 generation;
    u32 kind;
    u32 ref_index;
} GameRenderResource;

typedef struct GameRenderLevel {
    GameRenderResource resources[GAME_RENDER_RESOURCE_CAPACITY];
    u32 resource_count;
    u64 generation;
} GameRenderLevel;

typedef struct GameRenderFrame {
    u64 frame;
    u64 generation;
    u32 resource_count;
} GameRenderFrame;

typedef struct GameRender {
    FILE *trace;
    u64 last_frame;
    bool admission_open;
    bool producing;
    bool idle;
} GameRender;

BreakRuntimeError game_render_start(GameRender *render, FILE *trace);
BreakRuntimeError game_render_stage_level(const GameRenderResource *resources,
                                          u32 resource_count, u64 generation,
                                          GameRenderLevel *out_level);
BreakRuntimeError game_render_level_committed(GameRender *render,
                                              const GameRenderLevel *level);
BreakRuntimeError game_render_record_frame(GameRender *render,
                                           const GameRenderFrame *frame);
BreakRuntimeError game_render_stop_admission(GameRender *render);
BreakRuntimeError game_render_stop_producers(GameRender *render);
BreakRuntimeError game_render_idle(GameRender *render);
BreakRuntimeError game_render_destroy(GameRender *render);
