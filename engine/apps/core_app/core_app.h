#pragma once

#include <core/types.h>
#include <runtime/runtime_types.h>

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
    u32 max_frames;
};

BreakRuntimeError core_app_run(const CoreAppConfig *config, int *out_exit_code);
