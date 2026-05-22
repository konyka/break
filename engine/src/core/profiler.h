#pragma once
#include <core/types.h>

#define PROFILER_MAX_FRAMES  120
#define PROFILER_MAX_REGIONS 64

typedef struct {
    const char *name;
    u64         start_us;
    u64         elapsed_us;
} ProfilerRegion;

typedef struct {
    ProfilerRegion regions[PROFILER_MAX_REGIONS];
    u32            region_count;
    u64            frame_start_us;
    u64            frame_end_us;
} ProfilerFrame;

typedef struct {
    ProfilerFrame frames[PROFILER_MAX_FRAMES];
    u32           frame_index;
    u32           frame_count;
    bool          enabled;
} Profiler;

/* Singleton profiler — zero-init is fine */
extern Profiler g_profiler;

/* Frame lifecycle */
void profiler_begin_frame(void);
void profiler_end_frame(void);

/* Region tracking */
void profiler_push(const char *name);
void profiler_pop(void);

/* Query — returns NULL if no data */
const ProfilerFrame *profiler_last_frame(void);

/* Enable/disable */
void profiler_set_enabled(bool enabled);
