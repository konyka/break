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
    /* R304: stack of currently-open region indices into the current frame's
     * regions[]. profiler_pop must finalize the innermost OPEN region (LIFO),
     * not the last APPENDED one, so nested push/pop produce correct timings. */
    u32           open_stack[PROFILER_MAX_REGIONS];
    u32           open_count;
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

/* Optional GPU samples paired with a CPU frame for Chrome trace export. */
typedef struct {
    const char *name;
    f64         elapsed_ms;
} ProfilerGpuRegion;

typedef struct {
    const char *key;
    const char *value;
} ProfilerMetaInstant;

/* Write a Chrome Trace Event Format JSON file (chrome://tracing).
 * `frame` is typically profiler_last_frame(); GPU regions may be NULL/0.
 * Optional meta instant events (ph:"i") are appended when meta/meta_count set. */
bool profiler_export_chrome_trace(const char *path,
                                  const ProfilerFrame *frame,
                                  const ProfilerGpuRegion *gpu_regions,
                                  u32 gpu_count,
                                  const ProfilerMetaInstant *meta,
                                  u32 meta_count);

/* Enable/disable */
void profiler_set_enabled(bool enabled);
