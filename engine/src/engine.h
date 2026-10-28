#pragma once
#include <core/types.h>
#include <platform/platform.h>

typedef struct Engine Engine;

typedef struct {
    void *context;
    bool (*poll)(void *context, Engine *engine);
} EngineHost;

typedef struct {
    u32       width;
    u32       height;
    const char *title;
    f64       target_fps;
    bool      hide_window_until_first_frame;
    bool      start_fullscreen;
    bool      undecorated;      /* windowed window without title bar */
    /* Mobile hosts retain the native objects; the engine only borrows them. */
    void      *native_window;
    void      *native_display;
    f32       native_content_scale; /* zero selects 1.0 */
    /* host and its context must outlive the engine. */
    const EngineHost *host;
} EngineConfig;

struct Engine {
    Platform *platform;
    f64       delta_time;       /* clamped to 0.1 s (R147) */
    f64       raw_delta_time;   /* unclamped wall time of the last frame */
    u64       frame_count;
    f64       fps;
    f64       target_fps;
    u64       last_frame_us;
    f64       fps_accum;
    u64       fps_frames;
    const EngineHost *host;
};

bool engine_init(Engine *e, const EngineConfig *cfg);
void engine_shutdown(Engine *e);
bool engine_frame(Engine *e);
