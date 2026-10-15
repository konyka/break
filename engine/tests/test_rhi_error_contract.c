#include "test_framework.h"

#include "rhi/rhi.h"

/* ENGINE_RHI_TEST hooks (defined in rhi.c under ENGINE_RHI_TEST). */
extern RHIDevice *rhi_test_device_create(void);
extern void rhi_test_device_destroy(RHIDevice *dev);
extern bool rhi_test_frame_owner_try_acquire(RHIDevice *dev);
extern void rhi_test_frame_owner_release(RHIDevice *dev);

TEST(init_failure_maps_to_error_family)
{
    RHIResult result = RHI_RESULT_OK;

    /* 未知后端 → UNSUPPORTED（参数语义上的不支持）。 */
    ASSERT_EQ(rhi_device_create_ex((RHIBackend)99, (void *)1, (void *)1,
                                   64u, 64u, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_UNSUPPORTED);
    /* 尺寸越界 → INVALID_ARGUMENT。 */
    ASSERT_EQ(rhi_device_create_ex(RHI_BACKEND_OPENGL, (void *)1, (void *)1,
                                   0u, 64u, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_INVALID_ARGUMENT);
    ASSERT_EQ(rhi_device_create_ex(RHI_BACKEND_OPENGL, (void *)1, (void *)1,
                                   RHI_MAX_DRAWABLE_DIMENSION + 1u, 64u,
                                   &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_INVALID_ARGUMENT);
    /* surface/平台句柄缺失 → UNAVAILABLE（fail-closed）。 */
    ASSERT_EQ(rhi_device_create_ex(RHI_BACKEND_OPENGL, NULL, (void *)1,
                                   64u, 64u, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_UNAVAILABLE);
    ASSERT_EQ(rhi_device_create_ex(RHI_BACKEND_OPENGL, (void *)1, NULL,
                                   64u, 64u, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_UNAVAILABLE);
}

TEST(surface_unavailable_maps_fail_closed)
{
    RHIDevice *device = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;

    ASSERT_NEQ(device, NULL);
    /* 无 backend_data 的设备：surface 不可用，一切生命周期动词 UNAVAILABLE。 */
    ASSERT_EQ(rhi_frame_begin_ex(device, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_UNAVAILABLE);
    ASSERT_EQ(rhi_frame_end_ex(device), RHI_RESULT_UNAVAILABLE);
    ASSERT_EQ(rhi_present_ex(device), RHI_RESULT_UNAVAILABLE);
    ASSERT_EQ(rhi_device_idle_ex(device), RHI_RESULT_UNAVAILABLE);
    ASSERT_EQ(rhi_device_resize_ex(device, 64u, 64u), RHI_RESULT_UNAVAILABLE);
    rhi_test_device_destroy(device);
}

TEST(device_lost_is_sticky_and_fail_fast)
{
    RHIDevice *device = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;

    ASSERT_NEQ(device, NULL);
    rhi_test_set_device_status(device, RHI_DEVICE_STATUS_LOST);
    ASSERT_EQ(rhi_device_get_status(device), RHI_DEVICE_STATUS_LOST);
    ASSERT_EQ(rhi_frame_begin_ex(device, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_frame_end_ex(device), RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_present_ex(device), RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_device_idle_ex(device), RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_device_resize_ex(device, 64u, 64u), RHI_RESULT_DEVICE_LOST);
    rhi_test_device_destroy(device);
}

TEST(out_of_date_surfaces_via_lifecycle_result)
{
    RHIDevice *device = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;

    ASSERT_NEQ(device, NULL);
    rhi_test_set_lifecycle_result(device, RHI_RESULT_OUT_OF_DATE);
    ASSERT_EQ(rhi_frame_begin_ex(device, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_OUT_OF_DATE);
    ASSERT_EQ(rhi_device_idle_ex(device), RHI_RESULT_OUT_OF_DATE);
    ASSERT_EQ(rhi_device_resize_ex(device, 64u, 64u), RHI_RESULT_OUT_OF_DATE);
    /* surface lost 同样经 lifecycle_result 暴露并 fail-fast。 */
    rhi_test_set_lifecycle_result(device, RHI_RESULT_SURFACE_LOST);
    ASSERT_EQ(rhi_frame_begin_ex(device, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_SURFACE_LOST);
    ASSERT_EQ(rhi_present_ex(device), RHI_RESULT_SURFACE_LOST);
    rhi_test_device_destroy(device);
}

TEST(sync_failure_maps_to_sync_failed)
{
    RHIDevice *device = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;

    ASSERT_NEQ(device, NULL);
    rhi_test_set_lifecycle_result(device, RHI_RESULT_SYNC_FAILED);
    ASSERT_EQ(rhi_device_idle_ex(device), RHI_RESULT_SYNC_FAILED);
    ASSERT_EQ(rhi_frame_end_ex(device), RHI_RESULT_SYNC_FAILED);
    ASSERT_EQ(rhi_present_ex(device), RHI_RESULT_SYNC_FAILED);
    ASSERT_EQ(rhi_frame_begin_ex(device, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_SYNC_FAILED);
    rhi_test_device_destroy(device);
}

TEST(busy_while_frame_or_control_in_flight)
{
    RHIDevice *device = rhi_test_device_create();

    ASSERT_NEQ(device, NULL);
    ASSERT_TRUE(rhi_test_frame_owner_try_acquire(device));
    ASSERT_EQ(rhi_device_resize_ex(device, 64u, 64u), RHI_RESULT_BUSY);
    ASSERT_EQ(rhi_device_destroy_ex(device), RHI_RESULT_BUSY);
    rhi_test_frame_owner_release(device);
    ASSERT_EQ(rhi_device_destroy_ex(device), RHI_RESULT_OK);
    /* destroy_ex 已销毁设备路径由 rhi_device_destroy 接管（backend_data 为
     * NULL 时是安全的空操作）；不再调用 rhi_test_device_destroy。 */
}

TEST(declared_metal_and_d3d12_backends_fail_closed)
{
    RHIResult result = RHI_RESULT_OK;

    ASSERT_EQ(rhi_device_create_ex(RHI_BACKEND_METAL, (void *)1, (void *)1,
                                   64u, 64u, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_UNSUPPORTED);
    ASSERT_EQ(rhi_device_create_ex(RHI_BACKEND_D3D12, (void *)1, (void *)1,
                                   64u, 64u, &result), NULL);
    /* Plan D Task 2: d3d12 is a selectable backend whose skeleton device
     * creation is fail-closed UNAVAILABLE until Task 3 lands real creation. */
    ASSERT_EQ(result, RHI_RESULT_UNAVAILABLE);
}

TEST_MAIN_BEGIN()
    RUN_TEST(init_failure_maps_to_error_family);
    RUN_TEST(surface_unavailable_maps_fail_closed);
    RUN_TEST(device_lost_is_sticky_and_fail_fast);
    RUN_TEST(out_of_date_surfaces_via_lifecycle_result);
    RUN_TEST(sync_failure_maps_to_sync_failed);
    RUN_TEST(busy_while_frame_or_control_in_flight);
    RUN_TEST(declared_metal_and_d3d12_backends_fail_closed);
TEST_MAIN_END()
