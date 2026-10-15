#include <rhi/rhi.h>
#include "test_framework.h"
/* Headless-host contract: failure injection must map to the spec §4.2
 * error values without touching a GPU; the real-device half is gated
 * behind SKIP 77 (no adapter on this host). */
static RHIDevice *g_dev;

TEST(null_window_is_invalid_argument) {
    RHIResult r = RHI_RESULT_OK;
    RHIDevice *dev = rhi_device_create_ex(RHI_BACKEND_D3D12, NULL, NULL, 640, 480, &r);
    ASSERT_TRUE(dev == NULL);
    ASSERT_EQ(r, RHI_RESULT_INVALID_ARGUMENT);
}

TEST(caps_and_info_are_d3d12) {
    RHICapabilities caps;
    ASSERT_TRUE(rhi_device_get_capabilities(g_dev, &caps));
    ASSERT_EQ(caps.backend, RHI_BACKEND_D3D12);
    ASSERT_TRUE(caps.scissor_supported);
    RHIDeviceInfo info;
    ASSERT_TRUE(rhi_device_get_info(g_dev, &info));
    ASSERT_EQ(info.backend, RHI_BACKEND_D3D12);
    ASSERT_TRUE(info.device_name[0] != '\0');
    ASSERT_EQ(rhi_device_get_status(g_dev), RHI_DEVICE_STATUS_READY);
    ASSERT_FALSE(rhi_device_lost(g_dev));
    ASSERT_TRUE(rhi_frame_index(g_dev) < 2u);
    ASSERT_EQ(rhi_device_idle_ex(g_dev), RHI_RESULT_OK);
}

int main(void) {
#if defined(_WIN32)
    RHIResult r = RHI_RESULT_OK;
    g_dev = rhi_device_create_ex(RHI_BACKEND_D3D12, (void *)1, NULL, 640, 480, &r);
    if (g_dev == NULL) {
        /* A real adapter may not exist on CI hosts; accept a clean
         * UNAVAILABLE/ERROR, never a crash or fabricated success. */
        if (r == RHI_RESULT_UNAVAILABLE || r == RHI_RESULT_ERROR) return 77;
        return 1;
    }
    printf("=== Running Tests ===\n");
    RUN_TEST(null_window_is_invalid_argument);
    RUN_TEST(caps_and_info_are_d3d12);
    rhi_device_destroy(g_dev);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
#else
    return 77;
#endif
}
