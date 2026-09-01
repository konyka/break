#include <core/profiler.h>
#include <platform/time.h>
#include <stdatomic.h>
#include <stdio.h>
#include <string.h>

Profiler g_profiler = {0};

/* R419: sentinel pushed on open_stack for a region dropped because the frame
 * hit PROFILER_MAX_REGIONS — keeps the matching pop balanced. */
#define PROFILER_REGION_DROPPED 0xFFFFFFFFu

/* R434: per-thread open stack (replaces the shared g_profiler.open_stack —
 * a single shared stack corrupts LIFO nesting as soon as worker threads
 * record zones concurrently) and per-thread count of dropped pushes that no
 * longer fit on the stack itself. Dropped pushes are always the most recent
 * opens of their thread, so pops consume this count before touching the
 * stack. Reset per frame (calling thread only) in profiler_begin_frame. */
static _Thread_local u32 tls_open_stack[PROFILER_MAX_REGIONS];
static _Thread_local u32 tls_open_count;
static _Thread_local u32 tls_dropped_overflow;

/* R434: guards the per-frame region slot allocation in profiler_push so
 * concurrent recorders can't grab the same index. Region writes themselves
 * target only the grabbed slot, so they need no lock. */
static atomic_flag g_region_lock = ATOMIC_FLAG_INIT;

/* R434: thread registry. g_next_tid hands out profiler tids starting at
 * PROFILER_TID_MAIN; PROFILER_TID_GPU is skipped so the GPU track keeps its
 * historic tid 2. Names are copied (callers may pass stack strings) into
 * fixed slots; g_thread_used[] is released only after the name is stored. */
#define PROFILER_THREAD_NAME_LEN 32
static atomic_uint g_next_tid = PROFILER_TID_MAIN;
static char        g_thread_names[PROFILER_MAX_THREADS][PROFILER_THREAD_NAME_LEN];
static atomic_bool g_thread_used[PROFILER_MAX_THREADS];
static _Thread_local u32 tls_tid; /* 0 = not yet registered on this thread */

static u32 profiler_alloc_tid(void) {
    for (;;) {
        u32 t = atomic_fetch_add_explicit(&g_next_tid, 1u, memory_order_relaxed);
        if (t == PROFILER_TID_GPU) continue; /* R434: tid 2 reserved for the GPU track */
        return t;
    }
}

u32 profiler_register_thread(const char *name) {
    if (tls_tid != 0u) return tls_tid; /* idempotent per thread */
    u32 t = profiler_alloc_tid();
    /* R434: past the cap, fold onto the main track rather than failing. Folded
     * threads must skip the name store — several folded threads (plus the main
     * thread itself) would otherwise race on g_thread_names[PROFILER_TID_MAIN]. */
    bool folded = (t >= PROFILER_MAX_THREADS);
    if (folded) t = PROFILER_TID_MAIN;
    if (!folded && !atomic_load_explicit(&g_thread_used[t], memory_order_acquire)) {
        char fallback[PROFILER_THREAD_NAME_LEN];
        if (!name) {
            if (t == PROFILER_TID_MAIN) {
                name = "main";
            } else {
                snprintf(fallback, sizeof(fallback), "thread-%u", t);
                name = fallback;
            }
        }
        usize i = 0;
        for (; name[i] != '\0' && i + 1 < PROFILER_THREAD_NAME_LEN; i++)
            g_thread_names[t][i] = name[i];
        g_thread_names[t][i] = '\0';
        atomic_store_explicit(&g_thread_used[t], true, memory_order_release);
    }
    tls_tid = t;
    return t;
}

u32 profiler_current_tid(void) {
    if (tls_tid == 0u) profiler_register_thread(NULL);
    return tls_tid;
}

void profiler_set_enabled(bool enabled) {
    g_profiler.enabled = enabled;
}

/* g_profiler.frame_index is a plain u32 in the public Profiler struct (tests
 * read it directly, so the header field stays), but profiler_end_frame (main
 * thread) writes it while profiler_push/pop (any recording thread) read it.
 * Access it through an atomic lvalue — _Atomic u32 and u32 share layout on
 * every supported toolchain — so that cross-thread handoff is not a data race. */
static _Atomic u32 *profiler_frame_index_atomic(void) {
    return (_Atomic u32 *)&g_profiler.frame_index;
}

void profiler_begin_frame(void) {
    if (!g_profiler.enabled) return;
    ProfilerFrame *f = &g_profiler.frames[
        atomic_load_explicit(profiler_frame_index_atomic(), memory_order_acquire)];
    f->region_count = 0;
    g_profiler.open_count = 0; /* R304: reset the open-region stack per frame */
    tls_open_count = 0;        /* R434: per-thread open stack (calling thread) */
    tls_dropped_overflow = 0;  /* R434 */
    f->frame_start_us = time_microseconds();
}

void profiler_end_frame(void) {
    if (!g_profiler.enabled) return;
    u32 idx = atomic_load_explicit(profiler_frame_index_atomic(), memory_order_acquire);
    ProfilerFrame *f = &g_profiler.frames[idx];
    f->frame_end_us = time_microseconds();
    atomic_store_explicit(profiler_frame_index_atomic(),
                          (idx + 1u) % PROFILER_MAX_FRAMES, memory_order_release);
    if (g_profiler.frame_count < PROFILER_MAX_FRAMES) g_profiler.frame_count++;
}

void profiler_push(const char *name) {
    if (!g_profiler.enabled) return;
    ProfilerFrame *f = &g_profiler.frames[
        atomic_load_explicit(profiler_frame_index_atomic(), memory_order_acquire)];
    u32 tid = profiler_current_tid(); /* R434: tag the zone with the real thread */
    /* R419: when the frame is full, push a sentinel so the matching pop stays
     * balanced — otherwise the pop would finalize an outer region with this
     * (unrecorded) region's timing and corrupt nesting. */
    while (atomic_flag_test_and_set_explicit(&g_region_lock, memory_order_acquire)) {}
    if (f->region_count >= PROFILER_MAX_REGIONS) {
        atomic_flag_clear_explicit(&g_region_lock, memory_order_release);
        if (tls_open_count < PROFILER_MAX_REGIONS)
            tls_open_stack[tls_open_count++] = PROFILER_REGION_DROPPED;
        else
            tls_dropped_overflow++;
        return;
    }
    u32 idx = f->region_count++;
    atomic_flag_clear_explicit(&g_region_lock, memory_order_release);
    ProfilerRegion *r = &f->regions[idx];
    r->name = name;
    r->start_us = time_microseconds();
    r->elapsed_us = 0;
    r->tid = tid; /* R434 */
    /* R304: remember this region as open so the matching pop finalizes it.
     * open_count <= region_count <= PROFILER_MAX_REGIONS, so this can't overrun.
     * R434: the open stack is per-thread now, so concurrent recorders keep
     * their own LIFO nesting. */
    tls_open_stack[tls_open_count++] = idx;
}

void profiler_pop(void) {
    if (!g_profiler.enabled) return;
    ProfilerFrame *f = &g_profiler.frames[
        atomic_load_explicit(profiler_frame_index_atomic(), memory_order_acquire)];
    /* R304 (CORRECTNESS): finalize the innermost OPEN region (LIFO), not the
     * last appended one. The old `regions[region_count-1]` was wrong under
     * nesting: region_count is never decremented (regions are kept for export),
     * so after an inner push/pop the outer pop re-finalized the same inner
     * region and the outer region's elapsed_us stayed 0. main.c nests
     * render > {particles+csm, scene, postfx}, so "render" always reported 0us.
     * An extra/unbalanced pop is a safe no-op via the empty-stack guard. */
    /* R419: excess dropped pushes sit above every stacked entry, consume them
     * first so the stack below stays correctly nested. */
    if (tls_dropped_overflow > 0) { tls_dropped_overflow--; return; }
    if (tls_open_count == 0) return;
    u32 idx = tls_open_stack[--tls_open_count];
    /* R419: skip sentinels left by pushes that exceeded PROFILER_MAX_REGIONS. */
    if (idx == PROFILER_REGION_DROPPED) return;
    ProfilerRegion *r = &f->regions[idx];
    r->elapsed_us = time_microseconds() - r->start_us;
}

const ProfilerFrame *profiler_last_frame(void) {
    if (g_profiler.frame_count == 0) return NULL;
    u32 idx = (atomic_load_explicit(profiler_frame_index_atomic(), memory_order_acquire)
               + PROFILER_MAX_FRAMES - 1) % PROFILER_MAX_FRAMES;
    return &g_profiler.frames[idx];
}

static void profiler_json_escape_name(const char *name, char *out, usize out_sz) {
    if (!out || out_sz == 0) return;
    if (!name) name = "?";
    usize j = 0;
    for (usize i = 0; name[i] != '\0' && j + 2 < out_sz; i++) {
        char c = name[i];
        if (c == '"' || c == '\\') {
            if (j + 2 >= out_sz) break;
            out[j++] = '\\';
        }
        out[j++] = c;
    }
    out[j] = '\0';
}

/* R434: look up the registered name for a profiler tid ("?" if unknown). */
static const char *profiler_thread_name(u32 tid) {
    if (tid < PROFILER_MAX_THREADS &&
        atomic_load_explicit(&g_thread_used[tid], memory_order_acquire))
        return g_thread_names[tid];
    return "?";
}

bool profiler_export_chrome_trace(const char *path,
                                  const ProfilerFrame *frame,
                                  const ProfilerGpuRegion *gpu_regions,
                                  u32 gpu_count,
                                  const ProfilerMetaInstant *meta,
                                  u32 meta_count) {
    if (!path || !frame) return false;
    FILE *f = fopen(path, "w");
    if (!f) return false;

    fprintf(f, "{\"traceEvents\":[\n");
    bool first = true;
    u64 t0 = frame->frame_start_us;

    for (u32 i = 0; i < frame->region_count; i++) {
        const ProfilerRegion *r = &frame->regions[i];
        char ename[128], etname[PROFILER_THREAD_NAME_LEN * 2];
        profiler_json_escape_name(r->name, ename, sizeof(ename));
        u64 ts = (r->start_us >= t0) ? (r->start_us - t0) : 0u;
        /* R434: emit on the recording thread's real track. tid 0 can't occur
         * (profiler_push always tags), but fold defensively onto main. */
        u32 tid = (r->tid != 0u) ? r->tid : PROFILER_TID_MAIN;
        profiler_json_escape_name(profiler_thread_name(tid), etname, sizeof(etname));
        if (!first) fprintf(f, ",\n");
        first = false;
        fprintf(f,
            "{\"name\":\"%s\",\"cat\":\"cpu\",\"ph\":\"X\",\"ts\":%llu,\"dur\":%llu,"
            "\"pid\":1,\"tid\":%u,\"args\":{\"thread\":\"%s\"}}",
            ename,
            (unsigned long long)ts,
            (unsigned long long)r->elapsed_us,
            tid, etname);
    }

    if (gpu_regions) {
        for (u32 i = 0; i < gpu_count; i++) {
            char ename[128];
            profiler_json_escape_name(gpu_regions[i].name, ename, sizeof(ename));
            u64 dur_us = (u64)(gpu_regions[i].elapsed_ms * 1000.0);
            if (!first) fprintf(f, ",\n");
            first = false;
            /* R434: GPU samples keep the historic tid 2 track, reserved by the
             * CPU tid allocator so the two never collide. */
            fprintf(f,
                "{\"name\":\"%s\",\"cat\":\"gpu\",\"ph\":\"X\",\"ts\":0,\"dur\":%llu,"
                "\"pid\":1,\"tid\":%u,\"args\":{\"thread\":\"gpu\"}}",
                ename, (unsigned long long)dur_us, PROFILER_TID_GPU);
        }
    }

    /* Frame boundary marker for chrome://tracing navigation. */
    if (!first) fprintf(f, ",\n");
    u64 frame_dur = (frame->frame_end_us >= frame->frame_start_us)
        ? (frame->frame_end_us - frame->frame_start_us) : 0u;
    fprintf(f,
        "{\"name\":\"frame\",\"cat\":\"meta\",\"ph\":\"X\",\"ts\":0,\"dur\":%llu,"
        "\"pid\":1,\"tid\":%u}",
        (unsigned long long)frame_dur, PROFILER_TID_MAIN);

    if (meta) {
        for (u32 i = 0; i < meta_count; i++) {
            if (!meta[i].key || !meta[i].value) continue;
            char ekey[128], eval[128];
            profiler_json_escape_name(meta[i].key, ekey, sizeof(ekey));
            profiler_json_escape_name(meta[i].value, eval, sizeof(eval));
            fprintf(f, ",\n");
            fprintf(f,
                "{\"name\":\"%s\",\"cat\":\"meta\",\"ph\":\"i\",\"ts\":0,"
                "\"pid\":1,\"tid\":%u,\"args\":{\"value\":\"%s\"}}",
                ekey, PROFILER_TID_MAIN, eval);
        }
    }

    /* R434: thread_name metadata so chrome://tracing labels each track. */
    for (u32 t = 0; t < PROFILER_MAX_THREADS; t++) {
        if (!atomic_load_explicit(&g_thread_used[t], memory_order_acquire)) continue;
        char etname[PROFILER_THREAD_NAME_LEN * 2];
        profiler_json_escape_name(g_thread_names[t], etname, sizeof(etname));
        fprintf(f, ",\n");
        fprintf(f,
            "{\"name\":\"thread_name\",\"ph\":\"M\",\"pid\":1,\"tid\":%u,"
            "\"args\":{\"name\":\"%s\"}}",
            t, etname);
    }
    if (gpu_count > 0) {
        fprintf(f, ",\n");
        fprintf(f,
            "{\"name\":\"thread_name\",\"ph\":\"M\",\"pid\":1,\"tid\":%u,"
            "\"args\":{\"name\":\"gpu\"}}",
            PROFILER_TID_GPU);
    }

    fprintf(f, "\n]}\n");
    bool write_ok = !ferror(f);
    if (fclose(f) != 0) write_ok = false;
    return write_ok;
}
