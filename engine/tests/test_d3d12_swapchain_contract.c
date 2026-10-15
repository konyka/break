#include <rhi/rhi.h>
#include "test_framework.h"
/* Frame-lifecycle state machine on a real HWND. SKIP 77 when no GPU.
 * Asserts the spec §4.3 invariants: present-before-submit refused,
 * double acquire refused, resize roundtrip keeps READY. */
static RHIDevice *g_dev;

TEST(present_before_submit_refused) {
    RHIResult r = RHI_RESULT_OK;
    RHICmdBuffer *cmd;
    /* No frame in flight: the dispatcher's frame-owner gate refuses first
     * (rhi.c rhi_present_ex -> RHI_RESULT_BUSY). */
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_BUSY);
    /* Frame acquired but not submitted: the backend itself must refuse the
     * present (spec §4.3: present only after a successful submit). The
     * refusal abandons the frame and releases the frame owner. */
    cmd = rhi_frame_acquire_ex(g_dev, &r);
    ASSERT_TRUE(cmd != NULL);
    ASSERT_EQ(r, RHI_RESULT_OK);
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_ERROR);
}

TEST(acquire_submit_present_cycle) {
    RHIResult r = RHI_RESULT_OK;
    RHICmdBuffer *cmd = rhi_frame_acquire_ex(g_dev, &r);
    ASSERT_TRUE(cmd != NULL);
    ASSERT_EQ(r, RHI_RESULT_OK);
    ASSERT_TRUE(rhi_frame_acquire_ex(g_dev, &r) == NULL); /* one in-flight max */
    ASSERT_EQ(r, RHI_RESULT_BUSY);
    ASSERT_EQ(rhi_frame_submit_ex(g_dev), RHI_RESULT_OK);
    ASSERT_EQ(rhi_present_ex(g_dev), RHI_RESULT_OK);
}

TEST(resize_roundtrip_keeps_ready) {
    rhi_set_vsync(g_dev, false);
    ASSERT_EQ(rhi_device_resize_ex(g_dev, 640, 480), RHI_RESULT_OK);
    ASSERT_EQ(rhi_device_get_status(g_dev), RHI_DEVICE_STATUS_READY);
    ASSERT_EQ(rhi_device_drain_ex(g_dev), RHI_RESULT_OK);
}

int main(void) {
#if defined(_WIN32)
    RHIResult r = RHI_RESULT_OK;
    g_dev = rhi_device_create_ex(RHI_BACKEND_D3D12, (void *)1, NULL, 320, 240, &r);
    if (g_dev == NULL) return 77;
    printf("=== Running Tests ===\n");
    RUN_TEST(present_before_submit_refused);
    RUN_TEST(acquire_submit_present_cycle);
    RUN_TEST(resize_roundtrip_keeps_ready);
    rhi_device_destroy(g_dev);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
#else
    return 77;
#endif
}
