#pragma once

#include <core/types.h>
#include <renderer/world_presentation.h>
#include <runtime/runtime_types.h>

#include <stdio.h>

#define CORE_APP_RENDER_RESOURCE_CAPACITY 64u

typedef struct CoreAppRenderResource {
    u64 id;
    u64 generation;
    u32 kind;
    u32 ref_index;
} CoreAppRenderResource;

typedef struct CoreAppRenderLevel {
    CoreAppRenderResource resources[CORE_APP_RENDER_RESOURCE_CAPACITY];
    u32 resource_count;
    u64 generation;
} CoreAppRenderLevel;

typedef struct CoreAppRenderFrame {
    u64 frame;
    u64 generation;
    u32 resource_count;
} CoreAppRenderFrame;

typedef struct CoreAppRender {
    FILE *trace;
    u64 last_frame;
    bool admission_open;
    bool producing;
    bool idle;
} CoreAppRender;

BreakRuntimeError core_app_render_start(CoreAppRender *render, FILE *trace);
BreakRuntimeError core_app_render_stage_level(const CoreAppRenderResource *resources,
                                          u32 resource_count, u64 generation,
                                          CoreAppRenderLevel *out_level);
BreakRuntimeError core_app_render_level_committed(CoreAppRender *render,
                                              const CoreAppRenderLevel *level);
BreakRuntimeError core_app_render_record_frame(CoreAppRender *render,
                                           const CoreAppRenderFrame *frame);
BreakRuntimeError core_app_render_record_world(CoreAppRender *render, u64 generation,
                                             const WorldFrameSnapshot *snapshot);
BreakRuntimeError core_app_render_stop_admission(CoreAppRender *render);
BreakRuntimeError core_app_render_stop_producers(CoreAppRender *render);
BreakRuntimeError core_app_render_idle(CoreAppRender *render);
BreakRuntimeError core_app_render_destroy(CoreAppRender *render);
