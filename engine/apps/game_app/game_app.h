#pragma once

#include <core/types.h>
#include <runtime/runtime_types.h>

typedef enum GameRenderMode {
    GAME_RENDER_RECORD = 0,
    GAME_RENDER_AUTO,
    GAME_RENDER_VULKAN,
    GAME_RENDER_OPENGL
} GameRenderMode;

typedef enum GameAudioMode {
    GAME_AUDIO_RECORD = 0,
    GAME_AUDIO_NULL,
    GAME_AUDIO_DEVICE
} GameAudioMode;

typedef struct GameAppConfig {
    const char *asset_root;
    const char *scenario_path;
    const char *checkpoint_dir;
    const char *trace_path;
    const char *screenshot_path;
    GameRenderMode render_mode;
    GameAudioMode audio_mode;
    bool fixed_step;
    bool require_device;
    bool network;
    u32 max_frames;
} GameAppConfig;

BreakRuntimeError game_app_run(const GameAppConfig *config, int *out_exit_code);
