#include <engine.h>
#include <core/log.h>
#include <core/alloc.h>
#include <platform/time.h>
#include <platform/input.h>
#include <stdio.h>

bool engine_init(Engine *e, const EngineConfig *cfg) {
    LOG_INFO("Engine initializing...");

    time_init();

    PlatformConfig pcfg = {
        .width  = cfg->width,
        .height = cfg->height,
        .title  = cfg->title,
    };

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
    if (e->platform) {
        platform_destroy(e->platform);
        e->platform = NULL;
    }
    LOG_INFO("Engine shutdown complete");
}

bool engine_frame(Engine *e) {
    PlatformEventResult result = platform_poll(e->platform);
    if (result == PLATFORM_EVENT_QUIT) {
        return false;
    }

    InputState *input = platform_input(e->platform);
    if (input_key_pressed(input, 256)) {
        LOG_INFO("ESC pressed, exiting...");
        return false;
    }

    u64 now_us = time_microseconds();
    e->delta_time = (f64)(now_us - e->last_frame_us) / 1e6;
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

    if (e->target_fps > 0.0) {
        f64 target_ms = 1.0 / e->target_fps;
        f64 elapsed_ms = e->delta_time;
        if (elapsed_ms < target_ms) {
            u64 sleep_us = (u64)((target_ms - elapsed_ms) * 1e6);
            time_sleep_us(sleep_us);
            now_us = time_microseconds();
            e->delta_time = (f64)(now_us - e->last_frame_us) / 1e6;
            if (e->delta_time > 0.1) e->delta_time = 0.1;  /* R147: clamp */
            e->last_frame_us = now_us;
        }
    }

    return true;
}
