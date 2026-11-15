#pragma once

#include <core/types.h>
#include <runtime/runtime_types.h>

#include <stdio.h>

#include "core_app_network.h"

typedef struct CoreAppConfig CoreAppConfig;
typedef struct CoreApp CoreApp;

typedef enum CoreAppRenderMode {
    CORE_APP_RENDER_RECORD = 0,
    CORE_APP_RENDER_AUTO,
    CORE_APP_RENDER_VULKAN,
    CORE_APP_RENDER_OPENGL
} CoreAppRenderMode;

typedef enum CoreAppAudioMode {
    CORE_APP_AUDIO_RECORD = 0,
    CORE_APP_AUDIO_NULL,
    CORE_APP_AUDIO_DEVICE
} CoreAppAudioMode;

/* Optional network channel, borrowed for the whole run. The runtime library
 * never links a transport: the executable supplies these callbacks only in
 * a build with the authenticated transport, so an offline core_app links no
 * break_net, break_session or snow symbols. Every callback runs on the
 * CoreAppThread. tick
 * receives read-only POD copies plus the physics_state_hash of the live
 * world after the step, and returns nothing, so a network failure
 * can only change network diagnostics, never the simulation. The four stop
 * callbacks follow the runtime coordinator phases and must be idempotent
 * because rollback may call them after a partial start. */
typedef struct CoreAppNetworkHooks {
    void *user;
    BreakRuntimeError (*start)(void *user, FILE *trace);
    void (*tick)(void *user, u32 tick, u64 level_generation,
                 const CoreAppSnapshotEntity *entities, u32 entity_count, u64 physics_hash);
    BreakRuntimeError (*stop_admission)(void *user);
    BreakRuntimeError (*stop_producers)(void *user);
    BreakRuntimeError (*drain)(void *user);
    BreakRuntimeError (*destroy)(void *user);
} CoreAppNetworkHooks;

struct CoreAppConfig {
    const char *asset_root;
    const char *scenario_path;
    const char *checkpoint_dir;
    const char *trace_path;
    const char *screenshot_path;
    CoreAppRenderMode render_mode;
    CoreAppAudioMode audio_mode;
    bool fixed_step;
    bool require_device;
    bool network;
    const CoreAppNetworkHooks *network_hooks;
    u32 max_frames;
};

BreakRuntimeError core_app_run(const CoreAppConfig *config, int *out_exit_code);
