#include "test_framework.h"
#include <rhi/rhi.h>

/* Plan C Task 5: frame lifecycle contract for the native Metal backend —
 * drawable acquire/present, two-slot pacing index sequence, resize adoption,
 * and the spec §4.3 owner gating (present without acquire -> BUSY). Runs on
 * macOS with ENGINE_RHI_BACKEND_METAL; everywhere else it exits 77 (SKIP).
 * The CAMetalLayer is created offscreen (explicit drawableSize, no window).
 * Pixel-level assertions belong to Task 9 (screenshot); this suite pins the
 * frame API sequence only. */
#if defined(ENGINE_RHI_BACKEND_METAL) && defined(ENGINE_PLATFORM_MACOS)

/* CAMetalLayer creation needs Objective-C; metal_test_layer.m wraps it so
 * this TU stays C11. */
void *metal_test_layer_create(u32 w, u32 h);
void metal_test_layer_destroy(void *layer);

/* Plan C Task 6: iOS host-pause defense hook. Private export of rhi_metal.m
 * under ENGINE_RHI_TEST (no public header; production iOS hosts
 * self-discipline and never call frame APIs while backgrounded). */
void rhi_test_metal_set_suspended(RHIDevice *dev, bool suspended);

static RHIDevice *g_dev;
static void *g_layer;
static RHIResult g_create_result = RHI_RESULT_OK;

/* One acquire -> begin render pass -> clear -> end pass -> submit -> present
 * cycle. Returns false on any failed step (asserts inside the callers). */
static void run_clear_frame(RHIDevice *dev) {
    RHIResult r = RHI_RESULT_OK;
    RHICmdBuffer *cmd = rhi_frame_acquire_ex(dev, &r);
    ASSERT_NOT_NULL(cmd);
    ASSERT_EQ(r, RHI_RESULT_OK);
    rhi_cmd_begin_render_pass(cmd);
    rhi_cmd_clear_color(cmd, 0.1f, 0.2f, 0.3f, 1.0f);
    rhi_cmd_end_render_pass(cmd);
    ASSERT_EQ(rhi_frame_end_ex(dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_present_ex(dev), RHI_RESULT_OK);
}

TEST(three_frame_cycle_index_sequence_0_1_0) {
    /* Two-slot pacing: rhi_frame_index is frame_counter % 2 sampled inside
     * the frame (the counter advances at present). */
    static const u32 expected[3] = { 0u, 1u, 0u };
    u32 i;
    for (i = 0u; i < 3u; ++i) {
        RHIResult r = RHI_RESULT_OK;
        RHICmdBuffer *cmd = rhi_frame_acquire_ex(g_dev, &r);
        ASSERT_NOT_NULL(cmd);
        ASSERT_EQ(r, RHI_RESULT_OK);
        ASSERT_EQ(rhi_frame_index(g_dev), expected[i]);
        rhi_cmd_begin_render_pass(cmd);
        rhi_cmd_clear_color(cmd, 0.1f, 0.2f, 0.3f, 1.0f);
        rhi_cmd_end_render_pass(cmd);
        ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
        ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
    }
}

TEST(second_acquire_while_frame_in_flight_is_busy) {
    RHIResult r = RHI_RESULT_OK;
    RHICmdBuffer *cmd = rhi_frame_acquire_ex(g_dev, &r);
    ASSERT_NOT_NULL(cmd);
    ASSERT_EQ(r, RHI_RESULT_OK);
    /* spec §4.3: one in-flight acquire->submit pair max. */
    ASSERT_TRUE(rhi_frame_acquire_ex(g_dev, &r) == NULL);
    ASSERT_EQ(r, RHI_RESULT_BUSY);
    rhi_cmd_begin_render_pass(cmd);
    rhi_cmd_clear_color(cmd, 0.1f, 0.2f, 0.3f, 1.0f);
    rhi_cmd_end_render_pass(cmd);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
}

TEST(present_without_acquire_is_busy) {
    /* No frame in flight: the wrapper's owner check (rhi.c) fails fast. */
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_BUSY);
    ASSERT_EQ(rhi_frame_end_ex(g_dev), RHI_RESULT_BUSY);
}

TEST(resize_then_next_acquire_succeeds) {
    /* Metal resize updates dev->width/height only (the window layer owns
     * drawableSize); the next acquire adopts the layer's actual size. */
    ASSERT_EQ(rhi_device_resize_ex(g_dev, 320u, 240u), RHI_RESULT_OK);
    run_clear_frame(g_dev);
}

TEST(suspended_acquire_is_busy_resize_and_recover) {
    /* Task 6: defensive BUSY while the iOS host pause flag is set. */
    RHIResult r = RHI_RESULT_OK;
    rhi_test_metal_set_suspended(g_dev, true);
    /* A host that (wrongly) calls acquire while paused gets BUSY. */
    ASSERT_TRUE(rhi_frame_acquire_ex(g_dev, &r) == NULL);
    ASSERT_EQ(r, RHI_RESULT_BUSY);
    /* resize does not go through acquire: still succeeds while suspended. */
    ASSERT_EQ(rhi_device_resize_ex(g_dev, 320u, 240u), RHI_RESULT_OK);
    rhi_test_metal_set_suspended(g_dev, false);
    /* Flag cleared: BUSY is not sticky, acquire works again. */
    run_clear_frame(g_dev);
}

TEST(vsync_toggle_and_drain_after_frames) {
    rhi_set_vsync(g_dev, false);
    rhi_set_vsync(g_dev, true);
    run_clear_frame(g_dev);
    /* §4.3 drain: wait for the last submitted frame's signal. */
    ASSERT_EQ(rhi_device_drain_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_device_idle_ex(g_dev), RHI_RESULT_OK);
}

int main(void) {
    g_layer = metal_test_layer_create(64u, 64u);
    if (g_layer == NULL) return 77;
    g_dev = rhi_device_create_ex(RHI_BACKEND_METAL, g_layer, NULL, 64u, 64u,
                                 &g_create_result);
    if (g_dev == NULL) {
        /* No Metal device on this host (GPU-less CI runner): a clean
         * UNAVAILABLE/ERROR is a skip, never a fabricated success. */
        metal_test_layer_destroy(g_layer);
        if (g_create_result == RHI_RESULT_UNAVAILABLE ||
            g_create_result == RHI_RESULT_ERROR) return 77;
        return 1;
    }
    printf("=== Running Tests ===\n");
    RUN_TEST(three_frame_cycle_index_sequence_0_1_0);
    RUN_TEST(second_acquire_while_frame_in_flight_is_busy);
    RUN_TEST(present_without_acquire_is_busy);
    RUN_TEST(resize_then_next_acquire_succeeds);
    RUN_TEST(suspended_acquire_is_busy_resize_and_recover);
    RUN_TEST(vsync_toggle_and_drain_after_frames);
    /* destroy with all frames presented must drain + release cleanly
     * (crash here = teardown ordering bug, e.g. a late completion handler). */
    rhi_device_destroy(g_dev);
    metal_test_layer_destroy(g_layer);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
#else
int main(void) { return 77; }
#endif
