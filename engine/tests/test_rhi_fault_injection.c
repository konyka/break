#include "test_framework.h"
#include "rhi/rhi.h"
#include "rhi/rhi_result_map.h"
#include "platform/platform_wsi.h"

extern RHIDevice *rhi_test_device_create(void);
extern void rhi_test_device_destroy(RHIDevice *dev);
extern void rhi_test_set_lifecycle_result(RHIDevice *dev, RHIResult result);
extern void rhi_test_set_device_status(RHIDevice *dev, RHIDeviceStatus status);

TEST(vk_result_map_locks_lifecycle_mapping) {
    ASSERT_EQ(rhi_vk_result_to_lifecycle(-4), RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_vk_result_to_lifecycle(-1000001004), RHI_RESULT_OUT_OF_DATE);
    ASSERT_EQ(rhi_vk_result_to_lifecycle(-1000000000), RHI_RESULT_SURFACE_LOST);
    /* 锁定：OOM 与其余一切归 SYNC_FAILED（不改既有语义）。 */
    ASSERT_EQ(rhi_vk_result_to_lifecycle(-1), RHI_RESULT_SYNC_FAILED);
    ASSERT_EQ(rhi_vk_result_to_lifecycle(-2), RHI_RESULT_SYNC_FAILED);
    ASSERT_EQ(rhi_vk_result_to_lifecycle(1), RHI_RESULT_SYNC_FAILED);
}

TEST(out_of_date_fails_frame_entrypoints_fast) {
    RHIDevice *dev = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;
    ASSERT_NEQ(dev, NULL);
    rhi_test_set_lifecycle_result(dev, RHI_RESULT_OUT_OF_DATE);
    ASSERT_EQ(rhi_frame_begin_ex(dev, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_OUT_OF_DATE);
    ASSERT_EQ(rhi_device_idle_ex(dev), RHI_RESULT_OUT_OF_DATE);
    rhi_test_device_destroy(dev);
}

TEST(device_lost_fails_all_lifecycle_entrypoints_fast) {
    RHIDevice *dev = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;
    ASSERT_NEQ(dev, NULL);
    rhi_test_set_device_status(dev, RHI_DEVICE_STATUS_LOST);
    ASSERT_EQ(rhi_frame_begin_ex(dev, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_device_resize_ex(dev, 64u, 64u), RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_device_idle_ex(dev), RHI_RESULT_DEVICE_LOST);
    rhi_test_device_destroy(dev);
}

TEST(surface_lost_propagates_through_frame_begin) {
    RHIDevice *dev = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;
    ASSERT_NEQ(dev, NULL);
    rhi_test_set_lifecycle_result(dev, RHI_RESULT_SURFACE_LOST);
    ASSERT_EQ(rhi_frame_begin_ex(dev, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_SURFACE_LOST);
    rhi_test_device_destroy(dev);
}

TEST(lifecycle_injection_is_scoped_to_one_device) {
    RHIDevice *dev = rhi_test_device_create();
    RHIDevice *other = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;
    ASSERT_NEQ(dev, NULL);
    ASSERT_NEQ(other, NULL);
    rhi_test_set_lifecycle_result(dev, RHI_RESULT_OUT_OF_DATE);
    /* 未注入的设备不受影响：backend_data == NULL → UNAVAILABLE（既有语义）。 */
    ASSERT_EQ(rhi_frame_begin_ex(other, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_UNAVAILABLE);
    rhi_test_device_destroy(dev);
    rhi_test_device_destroy(other);
}

TEST(swapchain_generation_retires_backbuffers_on_resize) {
    PlatformWsiSwapchain swapchain;
    PlatformWsiBackBuffer buffer;
    PlatformWsiBackBuffer stale;
    ASSERT_EQ(platform_wsi_swapchain_init(&swapchain, PLATFORM_WSI_QUEUE_DIRECT,
                                          true, false, false, 2u,
                                          100u, 100u, 100u, 100u),
              PLATFORM_WSI_OK);
    ASSERT_EQ(platform_wsi_swapchain_begin_frame(&swapchain, &buffer),
              PLATFORM_WSI_OK);
    ASSERT_EQ(platform_wsi_swapchain_present(&swapchain, &buffer),
              PLATFORM_WSI_OK);
    ASSERT_EQ(platform_wsi_swapchain_ready(&swapchain), PLATFORM_WSI_OK);
    stale = buffer;
    ASSERT_EQ(platform_wsi_swapchain_resize(&swapchain, 200u, 200u, 200u, 200u),
              PLATFORM_WSI_OK);
    /* out-of-date 的 back buffer（旧 generation）不得再进入渲染/present。 */
    ASSERT_EQ(platform_wsi_swapchain_present(&swapchain, &stale),
              PLATFORM_WSI_INVALID_TRANSITION);
    ASSERT_EQ(platform_wsi_swapchain_begin_frame(&swapchain, &buffer),
              PLATFORM_WSI_OK);
    ASSERT_EQ(buffer.generation, 2u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(vk_result_map_locks_lifecycle_mapping);
    RUN_TEST(out_of_date_fails_frame_entrypoints_fast);
    RUN_TEST(device_lost_fails_all_lifecycle_entrypoints_fast);
    RUN_TEST(surface_lost_propagates_through_frame_begin);
    RUN_TEST(lifecycle_injection_is_scoped_to_one_device);
    RUN_TEST(swapchain_generation_retires_backbuffers_on_resize);
TEST_MAIN_END()
