#include "test_framework.h"
#include "rhi/rhi.h"
#include "platform/platform_wsi.h"

extern RHIDevice *rhi_test_device_create(void);
extern void rhi_test_device_destroy(RHIDevice *dev);

TEST(destroy_ex_runs_cleanly_with_healthy_wsi)
{
    RHIDevice *dev = rhi_test_device_create();
    PlatformWsiSurface wsi;
    ASSERT_NEQ(dev, NULL);
    ASSERT_EQ(platform_wsi_surface_init(&wsi, true, 64u, 64u, 64u, 64u),
              PLATFORM_WSI_OK);
    rhi_device_attach_wsi(dev, &wsi);
    /* 伪设备无 backend_data：destroy 路径是空转，门控语义不受影响
     *（同例：test_rhi_capabilities.c:509-512 的 destroy_ex 用例）。 */
    ASSERT_EQ(rhi_device_destroy_ex(dev), RHI_RESULT_OK);
    rhi_test_device_destroy(dev);
}

TEST(destroy_ex_rejects_while_wsi_destroying)
{
    RHIDevice *dev = rhi_test_device_create();
    PlatformWsiSurface wsi;
    ASSERT_NEQ(dev, NULL);
    ASSERT_EQ(platform_wsi_surface_init(&wsi, true, 64u, 64u, 64u, 64u),
              PLATFORM_WSI_OK);
    rhi_device_attach_wsi(dev, &wsi);
    ASSERT_EQ(platform_wsi_surface_destroy(&wsi), PLATFORM_WSI_OK);
    ASSERT_EQ(rhi_device_destroy_ex(dev), RHI_RESULT_BUSY);
    /* 门控拒绝后设备仍可正常销毁：解除挂载即恢复。 */
    rhi_device_attach_wsi(dev, NULL);
    ASSERT_EQ(rhi_device_destroy_ex(dev), RHI_RESULT_OK);
    rhi_test_device_destroy(dev);
}

TEST(destroy_ex_ignores_null_wsi_attachment)
{
    RHIDevice *dev = rhi_test_device_create();
    ASSERT_NEQ(dev, NULL);
    ASSERT_EQ(rhi_device_destroy_ex(dev), RHI_RESULT_OK);
    rhi_test_device_destroy(dev);
}

TEST_MAIN_BEGIN()
    RUN_TEST(destroy_ex_runs_cleanly_with_healthy_wsi);
    RUN_TEST(destroy_ex_rejects_while_wsi_destroying);
    RUN_TEST(destroy_ex_ignores_null_wsi_attachment);
TEST_MAIN_END()
