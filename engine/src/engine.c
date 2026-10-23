#include <engine.h>
#include <core/log.h>
#include <core/alloc.h>
#include <platform/time.h>
#include <platform/input.h>
#include <stdio.h>
#include <math.h>

bool engine_init(Engine *e, const EngineConfig *cfg) {
    /* R429: cfg was dereferenced unconditionally — engine_init(e, NULL)
     * segfaulted. Reject bad args up front. */
    if (!e || !cfg || e->platform != NULL ||
        !isfinite(cfg->target_fps) || cfg->target_fps < 0.0) return false;

    PlatformConfig pcfg = {
        .width  = cfg->width,
        .height = cfg->height,
        .title  = cfg->title,
        .hide_window_until_first_frame = cfg->hide_window_until_first_frame,
    };
    if (!platform_config_valid(&pcfg)) return false;

    e->delta_time = 0.0;
    e->raw_delta_time = 0.0;
    e->frame_count = 0;
    e->fps = 0.0;
    e->target_fps = 0.0;
    e->last_frame_us = 0;
    e->fps_accum = 0.0;
    e->fps_frames = 0;

    LOG_INFO("Engine initializing...");

    time_init();

    e->platform = platform_create(&pcfg);
    if (!e->platform) {
        LOG_FATAL("Failed to create platform");
        return false;
    }

    e->delta_time    = 0.0;
    e->frame_count   = 0;
    e->fps           = 0.0;
    e->target_fps    = cfg->target_fps;
    e->last_frame_us = time_microseconds();
    e->fps_accum     = 0.0;
    e->fps_frames    = 0;

    LOG_INFO("Engine initialized successfully");
    return true;
}

void engine_shutdown(Engine *e) {
    if (!e) return;
    if (e->platform) {
        platform_destroy(e->platform);
        e->platform = NULL;
    }
    LOG_INFO("Engine shutdown complete");
}

bool engine_frame(Engine *e) {
    if (e == NULL || e->platform == NULL) return false;
    u64 now_us = time_microseconds();

    /* Sleep before polling input so a mouse event arriving during the limiter
     * is consumed immediately before simulation/rendering instead of waiting
     * behind another target frame. last_frame_us still advances below, after
     * the sleep and event pump, so delta_time remains the full frame period.
     * R447: this limiter must be the ONLY pacer — consumers with vsync on
     * keep target_fps at 0 (double-throttling sleep against the vblank clock
     * shows up as input-correlated judder; see main.c apply_frame_pacing). */
    if (isfinite(e->target_fps) && e->target_fps > 0.0) {
        f64 target_us = 1e6 / e->target_fps;
        f64 elapsed_us = (f64)(now_us - e->last_frame_us);
        f64 sleep_us_f = target_us - elapsed_us;
        if (isfinite(sleep_us_f) && sleep_us_f > 0.0 &&
            sleep_us_f < (f64)UINT64_MAX) {
            u64 sleep_us = (u64)sleep_us_f;
            time_sleep_us(sleep_us);
            now_us = time_microseconds();
        }
    }

    PlatformEventResult result = platform_poll(e->platform);
    if (result == PLATFORM_EVENT_QUIT) {
        return false;
    }

    InputState *input = platform_input(e->platform);
    if (input_key_pressed(input, 256)) {
        LOG_INFO("ESC pressed, exiting...");
        return false;
    }

    now_us = time_microseconds();

    e->delta_time = (f64)(now_us - e->last_frame_us) / 1e6;
    e->raw_delta_time = e->delta_time;
    /* R147: Clamp delta_time to prevent physics tunneling / animation jumps
     * when the process is paused (debugger, system sleep, window minimized). */
    if (e->delta_time > 0.1) e->delta_time = 0.1;
    e->last_frame_us = now_us;
    e->frame_count++;
    e->fps_accum += e->delta_time;
    e->fps_frames++;

    if (e->fps_accum >= 0.5) {
        e->fps = (f64)e->fps_frames / e->fps_accum;
        LOG_INFO("Frame %llu | %.0f FPS | %.3f ms/frame",
                 (unsigned long long)e->frame_count, e->fps,
                 e->fps_accum * 1000.0 / (f64)e->fps_frames);
        e->fps_accum = 0.0;
        e->fps_frames = 0;
    }

    return true;
}
