#pragma once
#include <core/types.h>

#define PROFILER_MAX_FRAMES  120
#define PROFILER_MAX_REGIONS 64

/* R434: per-thread sampling. Chrome trace tid assignment: tid 1 is the first
 * (main) CPU thread, tid 2 stays reserved for the GPU track (the pre-R434
 * export hardcoded 1/2 for main/gpu), CPU worker threads allocate 3.. up to
 * PROFILER_MAX_THREADS - 1. Threads past the cap fold onto the main track. */
#define PROFILER_MAX_THREADS 32
#define PROFILER_TID_MAIN    1u
#define PROFILER_TID_GPU     2u

typedef struct {
    const char *name;
    u64         start_us;
    u64         elapsed_us;
    u32         tid; /* R434: profiler tid of the recording thread (never 0) */
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
     * not the last APPENDED one, so nested push/pop produce correct timings.
     * R434: superseded by per-thread TLS open stacks inside profiler.c (a
     * shared stack breaks nesting once workers record concurrently); kept —
     * and still reset per frame — for layout/ABI compatibility. */
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

/* R434: thread identity for per-thread trace tracks.
 * profiler_register_thread binds the CALLING thread to a profiler tid and
 * copies `name` (NULL → "main" for tid 1, otherwise "thread-N"); it is
 * idempotent per thread and returns the tid (never 0). Threads that never
 * register are lazily auto-assigned a tid on their first recorded zone;
 * profiler_current_tid returns the calling thread's tid, registering lazily
 * if needed. Both are thread-safe. */
u32 profiler_register_thread(const char *name);
u32 profiler_current_tid(void);

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
 * Optional meta instant events (ph:"i") are appended when meta/meta_count set.
 * R434: CPU events are emitted on each region's recorded tid, GPU events stay
 * on the reserved PROFILER_TID_GPU track, and registered thread names are
 * written as thread_name (ph:"M") metadata events. */
bool profiler_export_chrome_trace(const char *path,
                                  const ProfilerFrame *frame,
                                  const ProfilerGpuRegion *gpu_regions,
                                  u32 gpu_count,
                                  const ProfilerMetaInstant *meta,
                                  u32 meta_count);

/* Enable/disable */
void profiler_set_enabled(bool enabled);
