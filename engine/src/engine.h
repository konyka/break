#pragma once
#include <core/types.h>
#include <platform/platform.h>

typedef struct {
    u32       width;
    u32       height;
    const char *title;
    f64       target_fps;
} EngineConfig;

typedef struct {
    Platform *platform;
    f64       delta_time;
    u64       frame_count;
    f64       fps;
    f64       target_fps;
    u64       last_frame_us;
    f64       fps_accum;
    u64       fps_frames;
} Engine;

bool engine_init(Engine *e, const EngineConfig *cfg);
void engine_shutdown(Engine *e);
bool engine_frame(Engine *e);
