/* ==========================================================================
 *  test_profiler.c — Unit tests for the core profiler module.
 * ========================================================================== */

#include "test_framework.h"
#include <core/profiler.h>
#include <platform/time.h>
#include <stdio.h>
#include <string.h>

/* R434: thread-track tests spawn real threads; the CMake target only wires up
 * pthread/platform macros for linux (see R433), so guard them accordingly. */
#ifdef ENGINE_PLATFORM_LINUX
#include <pthread.h>
#endif

/* Helper: reset the global profiler to a clean state */
static void profiler_reset(void) {
    memset(&g_profiler, 0, sizeof(g_profiler));
}

/* ----------------------------------------------------------------------- */
/*  Basic lifecycle                                                         */
/* ----------------------------------------------------------------------- */

TEST(profiler_initial_state)
{
    profiler_reset();
    ASSERT_EQ(g_profiler.frame_index, 0u);
    ASSERT_EQ(g_profiler.frame_count, 0u);
    ASSERT_FALSE(g_profiler.enabled);
}

TEST(profiler_enable_disable)
{
    profiler_reset();
    profiler_set_enabled(true);
    ASSERT_TRUE(g_profiler.enabled);
    profiler_set_enabled(false);
    ASSERT_FALSE(g_profiler.enabled);
}

TEST(profiler_last_frame_null_when_empty)
{
    profiler_reset();
    const ProfilerFrame *f = profiler_last_frame();
    ASSERT_TRUE(f == NULL);
}

/* ----------------------------------------------------------------------- */
/*  Frame begin/end                                                         */
/* ----------------------------------------------------------------------- */

TEST(profiler_single_frame)
{
    profiler_reset();
    profiler_set_enabled(true);

    profiler_begin_frame();
    profiler_end_frame();

    ASSERT_EQ(g_profiler.frame_count, 1u);
    ASSERT_EQ(g_profiler.frame_index, 1u);

    const ProfilerFrame *f = profiler_last_frame();
    ASSERT_NOT_NULL(f);
    ASSERT_TRUE(f->frame_end_us >= f->frame_start_us);
}

TEST(profiler_multiple_frames)
{
    profiler_reset();
    profiler_set_enabled(true);

    for (int i = 0; i < 10; i++) {
        profiler_begin_frame();
        profiler_end_frame();
    }

    ASSERT_EQ(g_profiler.frame_count, 10u);
    ASSERT_EQ(g_profiler.frame_index, 10u);
}

TEST(profiler_ring_buffer_wrap)
{
    profiler_reset();
    profiler_set_enabled(true);

    /* Run more frames than PROFILER_MAX_FRAMES (120) */
    for (u32 i = 0; i < PROFILER_MAX_FRAMES + 5; i++) {
        profiler_begin_frame();
        profiler_end_frame();
    }

    /* frame_count should be capped at PROFILER_MAX_FRAMES */
    ASSERT_EQ(g_profiler.frame_count, (u32)PROFILER_MAX_FRAMES);
    /* frame_index should have wrapped */
    ASSERT_EQ(g_profiler.frame_index, 5u);

    /* last_frame should still return valid data */
    const ProfilerFrame *f = profiler_last_frame();
    ASSERT_NOT_NULL(f);
}

TEST(profiler_ring_buffer_last_frame_after_wrap)
{
    profiler_reset();
    profiler_set_enabled(true);

    /* Exactly PROFILER_MAX_FRAMES frames: index wraps to 0 */
    for (u32 i = 0; i < PROFILER_MAX_FRAMES; i++) {
        profiler_begin_frame();
        profiler_end_frame();
    }

    ASSERT_EQ(g_profiler.frame_index, 0u);

    /* last frame should be at index PROFILER_MAX_FRAMES - 1 */
    const ProfilerFrame *f = profiler_last_frame();
    ASSERT_NOT_NULL(f);
    /* Verify it's the same pointer as frames[PROFILER_MAX_FRAMES - 1] */
    ASSERT_TRUE(f == &g_profiler.frames[PROFILER_MAX_FRAMES - 1]);
}

/* ----------------------------------------------------------------------- */
/*  Region push/pop                                                         */
/* ----------------------------------------------------------------------- */

TEST(profiler_push_pop_region)
{
    profiler_reset();
    profiler_set_enabled(true);

    profiler_begin_frame();
    profiler_push("test_region");
    profiler_pop();
    profiler_end_frame();

    const ProfilerFrame *f = profiler_last_frame();
    ASSERT_NOT_NULL(f);
    ASSERT_EQ(f->region_count, 1u);
    ASSERT_STR_EQ(f->regions[0].name, "test_region");
    /* elapsed should be non-negative (u64, always true) */
    (void)f->regions[0].elapsed_us;
}

TEST(profiler_multiple_regions)
{
    profiler_reset();
    profiler_set_enabled(true);

    profiler_begin_frame();
    profiler_push("A");
    profiler_pop();
    profiler_push("B");
    profiler_pop();
    profiler_push("C");
    profiler_pop();
    profiler_end_frame();

    const ProfilerFrame *f = profiler_last_frame();
    ASSERT_NOT_NULL(f);
    ASSERT_EQ(f->region_count, 3u);
    ASSERT_STR_EQ(f->regions[0].name, "A");
    ASSERT_STR_EQ(f->regions[1].name, "B");
    ASSERT_STR_EQ(f->regions[2].name, "C");
}

TEST(profiler_region_overflow_clamped)
{
    profiler_reset();
    profiler_set_enabled(true);

    profiler_begin_frame();

    /* Push more than PROFILER_MAX_REGIONS (64) */
    for (int i = 0; i < PROFILER_MAX_REGIONS + 10; i++) {
        profiler_push("overflow");
    }

    /* region_count should be clamped at PROFILER_MAX_REGIONS */
    ProfilerFrame *f = &g_profiler.frames[g_profiler.frame_index];
    ASSERT_EQ(f->region_count, (u32)PROFILER_MAX_REGIONS);

    /* Pop all (extra pops should be safe) */
    for (int i = 0; i < PROFILER_MAX_REGIONS + 10; i++) {
        profiler_pop();
    }

    profiler_end_frame();
}

TEST(profiler_pop_empty_is_safe)
{
    profiler_reset();
    profiler_set_enabled(true);

    profiler_begin_frame();
    /* Pop with no push — should not crash */
    profiler_pop();
    profiler_pop();
    profiler_end_frame();

    const ProfilerFrame *f = profiler_last_frame();
    ASSERT_NOT_NULL(f);
    ASSERT_EQ(f->region_count, 0u);
}

TEST(profiler_nesting_correct_beyond_max_regions)
{
    /* R419: pushes past PROFILER_MAX_REGIONS are dropped, but their matching
     * pops must stay balanced — pre-fix each such pop finalized an outer
     * region with the dropped region's timestamp, corrupting nesting. */
    profiler_reset();
    profiler_set_enabled(true);

    profiler_begin_frame();
    profiler_push("outer");                         /* regions[0] */
    for (int i = 1; i < PROFILER_MAX_REGIONS; i++)
        profiler_push("fill");                      /* regions[1..63] */
    for (int i = 0; i < 10; i++)
        profiler_push("dropped");                   /* beyond capacity */
    for (int i = 0; i < 10; i++)
        profiler_pop();                             /* pops the dropped pushes */
    for (int i = 1; i < PROFILER_MAX_REGIONS; i++)
        profiler_pop();                             /* pops the fills */
    time_sleep_us(500);
    profiler_pop();                                 /* must finalize outer HERE */
    profiler_end_frame();

    const ProfilerFrame *f = profiler_last_frame();
    ASSERT_NOT_NULL(f);
    ASSERT_EQ(f->region_count, (u32)PROFILER_MAX_REGIONS);
    ASSERT_STR_EQ(f->regions[0].name, "outer");
    /* Pre-fix the outer region was finalized early by one of the fill pops
     * above (before the sleep), so its elapsed stayed below 500us. */
    ASSERT_TRUE(f->regions[0].elapsed_us >= 500u);
    ASSERT_EQ(g_profiler.open_count, 0u);
}

/* ----------------------------------------------------------------------- */
/*  Disabled profiler is no-op                                              */
/* ----------------------------------------------------------------------- */

TEST(profiler_disabled_is_noop)
{
    profiler_reset();
    /* profiler is disabled by default */
    ASSERT_FALSE(g_profiler.enabled);

    profiler_begin_frame();
    profiler_push("should_be_ignored");
    profiler_pop();
    profiler_end_frame();

    /* frame_count should still be 0 because disabled */
    ASSERT_EQ(g_profiler.frame_count, 0u);

    /* last_frame should return NULL */
    const ProfilerFrame *f = profiler_last_frame();
    ASSERT_TRUE(f == NULL);
}

/* ----------------------------------------------------------------------- */
/*  Timing sanity                                                           */
/* ----------------------------------------------------------------------- */

TEST(profiler_region_timing_nonzero)
{
    profiler_reset();
    profiler_set_enabled(true);

    profiler_begin_frame();
    profiler_push("sleep_test");
    /* Sleep for ~1ms to ensure measurable elapsed time */
    time_sleep_us(1000);
    profiler_pop();
    profiler_end_frame();

    const ProfilerFrame *f = profiler_last_frame();
    ASSERT_NOT_NULL(f);
    ASSERT_EQ(f->region_count, 1u);
    /* Should have measured at least 500us (half of 1ms, generous tolerance) */
    ASSERT_TRUE(f->regions[0].elapsed_us >= 500);
}

/* ----------------------------------------------------------------------- */
/*  Edge Cases                                                              */
/* ----------------------------------------------------------------------- */

TEST(profiler_empty_frame)
{
    profiler_reset();
    profiler_set_enabled(true);

    profiler_begin_frame();
    /* No regions pushed */
    profiler_end_frame();

    const ProfilerFrame *f = profiler_last_frame();
    ASSERT_NOT_NULL(f);
    ASSERT_EQ(f->region_count, 0u);
}

TEST(profiler_nested_regions)
{
    profiler_reset();
    profiler_set_enabled(true);

    profiler_begin_frame();
    profiler_push("outer");
    profiler_push("inner");
    profiler_pop();
    profiler_pop();
    profiler_end_frame();

    const ProfilerFrame *f = profiler_last_frame();
    ASSERT_NOT_NULL(f);
    /* Both regions should be recorded */
    ASSERT_EQ(f->region_count, 2u);
}

TEST(profiler_nested_timing_outer_finalized)
{
    /* R304: under nesting, pop must finalize the innermost OPEN region (LIFO),
     * not the last APPENDED one. The old impl finalized regions[region_count-1]
     * without decrementing region_count, so the outer pop re-finalized the inner
     * region and the OUTER region's elapsed_us stayed 0 forever (this is exactly
     * how main.c nests render > {particles+csm, scene, postfx}). */
    profiler_reset();
    profiler_set_enabled(true);

    profiler_begin_frame();
    profiler_push("outer");           /* regions[0] */
    time_sleep_us(500);
    profiler_push("inner");           /* regions[1] */
    time_sleep_us(1500);
    profiler_pop();                   /* finalizes inner */
    profiler_pop();                   /* must finalize OUTER, not inner again */
    profiler_end_frame();

    const ProfilerFrame *f = profiler_last_frame();
    ASSERT_NOT_NULL(f);
    ASSERT_EQ(f->region_count, 2u);
    ASSERT_STR_EQ(f->regions[0].name, "outer");
    ASSERT_STR_EQ(f->regions[1].name, "inner");
    /* Outer wraps inner: its elapsed must be non-zero and >= inner's. Pre-fix the
     * outer stayed 0, so this both catches the stuck-zero and the ordering. */
    ASSERT_TRUE(f->regions[1].elapsed_us >= 1000u);      /* inner ~1500us */
    ASSERT_TRUE(f->regions[0].elapsed_us >= f->regions[1].elapsed_us); /* outer wraps inner */
}

TEST(profiler_sequential_then_nested_indices)
{
    /* R304: a flat region followed by a nested pair must each finalize the right
     * slot. Mirrors main.c: ecs_query (flat) then render(outer) > scene(inner). */
    profiler_reset();
    profiler_set_enabled(true);

    profiler_begin_frame();
    profiler_push("flat");   /* [0] */
    time_sleep_us(400);
    profiler_pop();          /* finalizes [0] */
    profiler_push("outer");  /* [1] */
    time_sleep_us(300);
    profiler_push("inner");  /* [2] */
    time_sleep_us(700);
    profiler_pop();          /* finalizes [2] */
    profiler_pop();          /* finalizes [1] */
    profiler_end_frame();

    const ProfilerFrame *f = profiler_last_frame();
    ASSERT_NOT_NULL(f);
    ASSERT_EQ(f->region_count, 3u);
    ASSERT_TRUE(f->regions[0].elapsed_us >= 200u);  /* flat measured */
    ASSERT_TRUE(f->regions[2].elapsed_us >= 400u);  /* inner measured */
    ASSERT_TRUE(f->regions[1].elapsed_us >= f->regions[2].elapsed_us); /* outer wraps inner */
}

TEST(profiler_begin_without_end)
{
    profiler_reset();
    profiler_set_enabled(true);

    /* Two consecutive begin_frame without end_frame - should not crash */
    profiler_begin_frame();
    profiler_begin_frame();
    profiler_end_frame();

    /* Should have recorded at least one frame */
    ASSERT_TRUE(g_profiler.frame_count >= 1u);
}

TEST(profiler_push_null_name)
{
    profiler_reset();
    profiler_set_enabled(true);

    profiler_begin_frame();
    profiler_push(NULL);  /* Should not crash */
    profiler_pop();
    profiler_end_frame();

    const ProfilerFrame *f = profiler_last_frame();
    ASSERT_NOT_NULL(f);
}

TEST(profiler_export_chrome_trace)
{
    profiler_reset();
    profiler_set_enabled(true);

    profiler_begin_frame();
    profiler_push("export_region");
    profiler_pop();
    profiler_end_frame();

    const ProfilerFrame *f = profiler_last_frame();
    ASSERT_NOT_NULL(f);

    ProfilerGpuRegion gpu[1] = { { "gpu_test", 1.25 } };
    char path[64]; test_tmp(path, sizeof path, "profiler_test_trace.json"); /* R444: per-pid path — same-tree parallel ctest shared the cwd-relative file */
    ASSERT_TRUE(profiler_export_chrome_trace(path, f, gpu, 1, NULL, 0));

    FILE *fp = fopen(path, "rb");
    ASSERT_NOT_NULL(fp);
    char buf[512] = {0};
    size_t n = fread(buf, 1, sizeof(buf) - 1u, fp);
    fclose(fp);
    remove(path);
    ASSERT_TRUE(n > 0u);
    ASSERT_NOT_NULL(strstr(buf, "\"traceEvents\""));
    ASSERT_NOT_NULL(strstr(buf, "export_region"));
    ASSERT_NOT_NULL(strstr(buf, "gpu_test"));
}

TEST(profiler_export_chrome_meta)
{
    profiler_reset();
    profiler_set_enabled(true);
    profiler_begin_frame();
    profiler_end_frame();

    const ProfilerFrame *f = profiler_last_frame();
    ASSERT_NOT_NULL(f);

    ProfilerMetaInstant meta[2] = {
        { "draw_bench_mega", "12" },
        { "draw_bench_legacy", "240" },
    };
    char path[64]; test_tmp(path, sizeof path, "profiler_test_meta.json"); /* R444: per-pid path — same-tree parallel ctest shared the cwd-relative file */
    ASSERT_TRUE(profiler_export_chrome_trace(path, f, NULL, 0, meta, 2));

    FILE *fp = fopen(path, "rb");
    ASSERT_NOT_NULL(fp);
    char buf[512] = {0};
    size_t n = fread(buf, 1, sizeof(buf) - 1u, fp);
    fclose(fp);
    remove(path);
    ASSERT_TRUE(n > 0u);
    ASSERT_NOT_NULL(strstr(buf, "draw_bench_mega"));
    ASSERT_NOT_NULL(strstr(buf, "\"ph\":\"i\""));
}

/* ----------------------------------------------------------------------- */
/*  R434: per-thread sampling (Chrome trace thread tracks)                  */
/* ----------------------------------------------------------------------- */

#ifdef ENGINE_PLATFORM_LINUX

/* Helper: read a whole (small) text file, NUL-terminate, return length. */
static size_t read_text_file(const char *path, char *buf, size_t cap) {
    FILE *fp = fopen(path, "rb");
    if (!fp) return 0;
    size_t n = fread(buf, 1, cap - 1u, fp);
    buf[n] = '\0';
    fclose(fp);
    return n;
}

typedef struct {
    const char *name;
    u32         tid;
} ThreadRecordArg;

static void *thread_register_and_record(void *p) {
    ThreadRecordArg *a = (ThreadRecordArg *)p;
    a->tid = profiler_register_thread(a->name);
    profiler_push(a->name);
    time_sleep_us(50);
    profiler_pop();
    return NULL;
}

TEST(profiler_threads_distinct_tids_and_names)
{
    /* R434: two worker threads register explicitly and record zones; the
     * exported Chrome trace must put their events on two distinct tids and
     * carry thread_name metadata for both. */
    profiler_reset();
    profiler_set_enabled(true);

    profiler_begin_frame();
    profiler_push("main_zone");
    profiler_pop();

    ThreadRecordArg a = { "worker_a", 0 };
    ThreadRecordArg b = { "worker_b", 0 };
    pthread_t ta, tb;
    ASSERT_EQ(pthread_create(&ta, NULL, thread_register_and_record, &a), 0);
    ASSERT_EQ(pthread_create(&tb, NULL, thread_register_and_record, &b), 0);
    pthread_join(ta, NULL);
    pthread_join(tb, NULL);
    profiler_end_frame();

    ASSERT_TRUE(a.tid != 0u);
    ASSERT_TRUE(b.tid != 0u);
    ASSERT_NEQ(a.tid, b.tid);

    const ProfilerFrame *f = profiler_last_frame();
    ASSERT_NOT_NULL(f);
    ASSERT_EQ(f->region_count, 3u);
    /* The main-thread zone keeps the main track. */
    ASSERT_EQ(f->regions[0].tid, profiler_current_tid());

    char path[64]; test_tmp(path, sizeof path, "profiler_test_threads.json"); /* R444: per-pid path — same-tree parallel ctest shared the cwd-relative file */
    ASSERT_TRUE(profiler_export_chrome_trace(path, f, NULL, 0, NULL, 0));

    static char buf[16384];
    size_t n = read_text_file(path, buf, sizeof(buf));
    remove(path);
    ASSERT_TRUE(n > 0u);
    ASSERT_NOT_NULL(strstr(buf, "\"thread_name\""));
    ASSERT_NOT_NULL(strstr(buf, "worker_a"));
    ASSERT_NOT_NULL(strstr(buf, "worker_b"));

    char needle[32];
    snprintf(needle, sizeof(needle), "\"tid\":%u", a.tid);
    ASSERT_NOT_NULL(strstr(buf, needle));
    snprintf(needle, sizeof(needle), "\"tid\":%u", b.tid);
    ASSERT_NOT_NULL(strstr(buf, needle));
}

static void *thread_lazy_record(void *p) {
    ThreadRecordArg *a = (ThreadRecordArg *)p;
    profiler_push("lazy_zone");
    a->tid = profiler_current_tid();
    profiler_pop();
    return NULL;
}

TEST(profiler_thread_lazy_auto_assign)
{
    /* R434: an unregistered thread must be assigned a tid automatically on
     * first use, and its zones must be tagged with that tid. */
    profiler_reset();
    profiler_set_enabled(true);

    profiler_begin_frame();
    ThreadRecordArg a = { NULL, 0 };
    pthread_t t;
    ASSERT_EQ(pthread_create(&t, NULL, thread_lazy_record, &a), 0);
    pthread_join(t, NULL);
    profiler_end_frame();

    ASSERT_TRUE(a.tid != 0u);
    ASSERT_NEQ(a.tid, 1u); /* not folded onto the main track */

    const ProfilerFrame *f = profiler_last_frame();
    ASSERT_NOT_NULL(f);
    ASSERT_EQ(f->region_count, 1u);
    ASSERT_STR_EQ(f->regions[0].name, "lazy_zone");
    ASSERT_EQ(f->regions[0].tid, a.tid);
}

#define CONC_THREADS 4
#define CONC_ZONES   8

static void *thread_record_many(void *p) {
    (void)p;
    for (int i = 0; i < CONC_ZONES; i++) {
        profiler_push("conc");
        profiler_pop();
    }
    return NULL;
}

TEST(profiler_threads_concurrent_record)
{
    /* R434: concurrent recording from several threads must not crash or lose
     * zones — every recorded region carries a valid thread id. */
    profiler_reset();
    profiler_set_enabled(true);

    profiler_begin_frame();
    pthread_t th[CONC_THREADS];
    for (int i = 0; i < CONC_THREADS; i++)
        ASSERT_EQ(pthread_create(&th[i], NULL, thread_record_many, NULL), 0);
    for (int i = 0; i < CONC_THREADS; i++)
        pthread_join(th[i], NULL);
    profiler_end_frame();

    const ProfilerFrame *f = profiler_last_frame();
    ASSERT_NOT_NULL(f);
    ASSERT_EQ(f->region_count, (u32)(CONC_THREADS * CONC_ZONES));
    for (u32 i = 0; i < f->region_count; i++)
        ASSERT_TRUE(f->regions[i].tid != 0u);
}

#endif /* ENGINE_PLATFORM_LINUX */

/* ----------------------------------------------------------------------- */
/*  Main                                                                    */
/* ----------------------------------------------------------------------- */

TEST_MAIN_BEGIN()
    RUN_TEST(profiler_initial_state);
    RUN_TEST(profiler_enable_disable);
    RUN_TEST(profiler_last_frame_null_when_empty);
    RUN_TEST(profiler_single_frame);
    RUN_TEST(profiler_multiple_frames);
    RUN_TEST(profiler_ring_buffer_wrap);
    RUN_TEST(profiler_ring_buffer_last_frame_after_wrap);
    RUN_TEST(profiler_push_pop_region);
    RUN_TEST(profiler_multiple_regions);
    RUN_TEST(profiler_region_overflow_clamped);
    RUN_TEST(profiler_pop_empty_is_safe);
    RUN_TEST(profiler_nesting_correct_beyond_max_regions);
    RUN_TEST(profiler_disabled_is_noop);
    RUN_TEST(profiler_region_timing_nonzero);
    /* Edge cases */
    RUN_TEST(profiler_empty_frame);
    RUN_TEST(profiler_nested_regions);
    RUN_TEST(profiler_nested_timing_outer_finalized);
    RUN_TEST(profiler_sequential_then_nested_indices);
    RUN_TEST(profiler_begin_without_end);
    RUN_TEST(profiler_push_null_name);
    RUN_TEST(profiler_export_chrome_trace);
    RUN_TEST(profiler_export_chrome_meta);
    /* R434: per-thread sampling */
#ifdef ENGINE_PLATFORM_LINUX
    RUN_TEST(profiler_threads_distinct_tids_and_names);
    RUN_TEST(profiler_thread_lazy_auto_assign);
    RUN_TEST(profiler_threads_concurrent_record);
#endif
TEST_MAIN_END()
