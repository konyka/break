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

#define CORE_APP_RESOURCE_SLOTS 64u
#define CORE_APP_RESOURCE_MAX_BYTES 256u

typedef enum CoreAppResourceState {
    CORE_APP_RESOURCE_EMPTY = 0,
    CORE_APP_RESOURCE_PENDING,
    CORE_APP_RESOURCE_LIVE
} CoreAppResourceState;

typedef struct CoreAppResourceSlot {
    u64 request_id;
    u64 generation;
    u32 state;
    u32 version;
    u32 byte_count;
    bool reloading;
    u8 bytes[CORE_APP_RESOURCE_MAX_BYTES];
} CoreAppResourceSlot;

typedef struct CoreAppResourceTable {
    CoreAppResourceSlot slots[CORE_APP_RESOURCE_SLOTS];
    u64 next_request;
    u64 stale_completions;
    u64 overloads;
} CoreAppResourceTable;

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

void core_app_resource_table_init(CoreAppResourceTable *table);
BreakRuntimeError core_app_resource_request(CoreAppResourceTable *table, u64 generation,
                                            u32 *out_slot, u64 *out_request);
BreakRuntimeError core_app_resource_reload(CoreAppResourceTable *table, u32 slot,
                                           u64 generation, u64 *out_request);
BreakRuntimeError core_app_resource_complete(CoreAppResourceTable *table, u32 slot,
                                             u64 request, u64 generation,
                                             const void *bytes, u32 byte_count);
BreakRuntimeError core_app_resource_retire_generation(CoreAppResourceTable *table,
                                                      u64 generation);
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
