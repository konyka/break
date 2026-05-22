#include <core/profiler.h>
#include <platform/time.h>
#include <string.h>

Profiler g_profiler = {0};

void profiler_set_enabled(bool enabled) {
    g_profiler.enabled = enabled;
}

void profiler_begin_frame(void) {
    if (!g_profiler.enabled) return;
    ProfilerFrame *f = &g_profiler.frames[g_profiler.frame_index];
    f->region_count = 0;
    f->frame_start_us = time_microseconds();
}

void profiler_end_frame(void) {
    if (!g_profiler.enabled) return;
    ProfilerFrame *f = &g_profiler.frames[g_profiler.frame_index];
    f->frame_end_us = time_microseconds();
    g_profiler.frame_index = (g_profiler.frame_index + 1) % PROFILER_MAX_FRAMES;
    if (g_profiler.frame_count < PROFILER_MAX_FRAMES) g_profiler.frame_count++;
}

void profiler_push(const char *name) {
    if (!g_profiler.enabled) return;
    ProfilerFrame *f = &g_profiler.frames[g_profiler.frame_index];
    if (f->region_count >= PROFILER_MAX_REGIONS) return;
    ProfilerRegion *r = &f->regions[f->region_count++];
    r->name = name;
    r->start_us = time_microseconds();
    r->elapsed_us = 0;
}

void profiler_pop(void) {
    if (!g_profiler.enabled) return;
    ProfilerFrame *f = &g_profiler.frames[g_profiler.frame_index];
    if (f->region_count == 0) return;
    ProfilerRegion *r = &f->regions[f->region_count - 1];
    r->elapsed_us = time_microseconds() - r->start_us;
}

const ProfilerFrame *profiler_last_frame(void) {
    if (g_profiler.frame_count == 0) return NULL;
    u32 idx = (g_profiler.frame_index + PROFILER_MAX_FRAMES - 1) % PROFILER_MAX_FRAMES;
    return &g_profiler.frames[idx];
}
