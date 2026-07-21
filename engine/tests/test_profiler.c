/* ==========================================================================
 *  test_profiler.c — Unit tests for the core profiler module.
 * ========================================================================== */

#include "test_framework.h"
#include <core/profiler.h>
#include <platform/time.h>
#include <stdio.h>
#include <string.h>

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
    const char *path = "profiler_test_trace.json";
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
    const char *path = "profiler_test_meta.json";
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
TEST_MAIN_END()
