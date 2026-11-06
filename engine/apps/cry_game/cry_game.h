#pragma once

#include <core/types.h>
#include <runtime/runtime_types.h>

typedef enum CryRenderMode {
    CRY_RENDER_RECORD = 0,
    CRY_RENDER_AUTO,
    CRY_RENDER_VULKAN,
    CRY_RENDER_OPENGL
} CryRenderMode;

typedef enum CryAudioMode {
    CRY_AUDIO_RECORD = 0,
    CRY_AUDIO_NULL,
    CRY_AUDIO_DEVICE
} CryAudioMode;

typedef struct CryGameConfig {
    const char *asset_root;
    const char *scenario_path;
    const char *checkpoint_dir;
    const char *trace_path;
    const char *screenshot_path;
    CryRenderMode render_mode;
    CryAudioMode audio_mode;
    bool fixed_step;
    bool require_device;
    bool network;
    u32 max_frames;
} CryGameConfig;

BreakRuntimeError cry_game_run(const CryGameConfig *config, int *out_exit_code);
