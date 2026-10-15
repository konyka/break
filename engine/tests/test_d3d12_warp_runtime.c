#include <rhi/rhi.h>
#include "test_framework.h"
/* Forces WARP via ENGINE_D3D12_WARP=1 (set in CTest ENVIRONMENT) so the
 * windows-d3d12 lane has a deterministic software GPU-runtime floor.
 * Evidence rule: WARP receipts are recorded with gpu=WARP and never
 * upgrade the evidence level past GPU-runtime. */
static RHIDevice *g_dev;

TEST(warp_device_identity_is_honest) {
    RHIDeviceInfo info;
    ASSERT_TRUE(rhi_device_get_info(g_dev, &info));
    ASSERT_EQ(info.backend, RHI_BACKEND_D3D12);
    /* WARP reports Microsoft Basic Render Driver; refuse to masquerade. */
    ASSERT_TRUE(strstr(info.device_name, "Basic Render") != NULL ||
                strstr(info.device_name, "WARP") != NULL);
    ASSERT_EQ(rhi_device_idle_ex(g_dev), RHI_RESULT_OK);
}

int main(void) {
#if defined(_WIN32)
    RHIResult r = RHI_RESULT_OK;
    g_dev = rhi_device_create_ex(RHI_BACKEND_D3D12, (void *)1, NULL, 64, 64, &r);
    if (g_dev == NULL) return 77;
    printf("=== Running Tests ===\n");
    RUN_TEST(warp_device_identity_is_honest);
    rhi_device_destroy(g_dev);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
#else
    return 77;
#endif
}
