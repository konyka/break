#include "test_framework.h"

#include "rhi/rhi.h"

extern RHIDevice *rhi_test_device_create(void);
extern void rhi_test_device_destroy(RHIDevice *dev);
extern bool rhi_test_frame_owner_try_acquire(RHIDevice *dev);
extern bool rhi_test_frame_owner_is_current(const RHIDevice *dev);
extern void rhi_test_frame_owner_release(RHIDevice *dev);

TEST(acquire_submit_present_drain_aliases_share_semantics)
{
    RHIResult result = RHI_RESULT_OK;

    /* 别名族与正名入口行为一致：NULL 设备一律 INVALID_ARGUMENT。 */
    ASSERT_EQ(rhi_frame_acquire_ex(NULL, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_INVALID_ARGUMENT);
    ASSERT_EQ(rhi_frame_begin_ex(NULL, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_INVALID_ARGUMENT);
    ASSERT_EQ(rhi_frame_submit_ex(NULL), RHI_RESULT_INVALID_ARGUMENT);
    ASSERT_EQ(rhi_frame_end_ex(NULL), RHI_RESULT_INVALID_ARGUMENT);
    ASSERT_EQ(rhi_present_ex(NULL), RHI_RESULT_INVALID_ARGUMENT);
    ASSERT_EQ(rhi_device_drain_ex(NULL), RHI_RESULT_INVALID_ARGUMENT);
    ASSERT_EQ(rhi_device_idle_ex(NULL), RHI_RESULT_INVALID_ARGUMENT);
}

TEST(acquire_requires_ready_device)
{
    RHIDevice *device = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;

    ASSERT_NEQ(device, NULL);
    /* READY 但无 backend（无 surface）：acquire 失败且 fail-closed。 */
    ASSERT_EQ(rhi_device_get_status(device), RHI_DEVICE_STATUS_READY);
    ASSERT_EQ(rhi_frame_acquire_ex(device, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_UNAVAILABLE);
    ASSERT_EQ(rhi_frame_submit_ex(device), RHI_RESULT_UNAVAILABLE);
    ASSERT_EQ(rhi_present_ex(device), RHI_RESULT_UNAVAILABLE);
    ASSERT_EQ(rhi_device_drain_ex(device), RHI_RESULT_UNAVAILABLE);
    rhi_test_device_destroy(device);
}

TEST(lost_device_fails_fast_on_full_frame_sequence)
{
    RHIDevice *device = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;

    ASSERT_NEQ(device, NULL);
    rhi_test_set_device_status(device, RHI_DEVICE_STATUS_LOST);
    ASSERT_EQ(rhi_frame_acquire_ex(device, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_frame_submit_ex(device), RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_present_ex(device), RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_device_drain_ex(device), RHI_RESULT_DEVICE_LOST);
    ASSERT_EQ(rhi_device_resize_ex(device, 64u, 64u), RHI_RESULT_DEVICE_LOST);
    rhi_test_device_destroy(device);
}

TEST(out_of_date_fails_fast_and_is_per_device)
{
    RHIDevice *device = rhi_test_device_create();
    RHIDevice *other = rhi_test_device_create();
    RHIResult result = RHI_RESULT_OK;

    ASSERT_NEQ(device, NULL);
    ASSERT_NEQ(other, NULL);
    rhi_test_set_lifecycle_result(device, RHI_RESULT_OUT_OF_DATE);
    ASSERT_EQ(rhi_frame_acquire_ex(device, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_OUT_OF_DATE);
    ASSERT_EQ(rhi_frame_submit_ex(device), RHI_RESULT_OUT_OF_DATE);
    ASSERT_EQ(rhi_present_ex(device), RHI_RESULT_OUT_OF_DATE);
    ASSERT_EQ(rhi_device_drain_ex(device), RHI_RESULT_OUT_OF_DATE);
    /* 注入是 per-device 的：另一台设备不受影响。 */
    ASSERT_EQ(rhi_frame_acquire_ex(other, &result), NULL);
    ASSERT_EQ(result, RHI_RESULT_UNAVAILABLE);
    rhi_test_device_destroy(device);
    rhi_test_device_destroy(other);
}

TEST(only_one_in_flight_acquire_submit_pair_per_thread)
{
    RHIDevice *first = rhi_test_device_create();
    RHIDevice *second = rhi_test_device_create();

    ASSERT_NEQ(first, NULL);
    ASSERT_NEQ(second, NULL);
    /* 规格 §4.3：同一时刻只允许一对 in-flight acquire→submit。 */
    ASSERT_TRUE(rhi_test_frame_owner_try_acquire(first));
    ASSERT_TRUE(rhi_test_frame_owner_is_current(first));
    ASSERT_FALSE(rhi_test_frame_owner_try_acquire(second));
    ASSERT_FALSE(rhi_test_frame_owner_is_current(second));
    /* frame 未交还前 resize/destroy 均 BUSY（drain/destroy 的 fail-fast 面）。 */
    ASSERT_EQ(rhi_device_resize_ex(first, 64u, 64u), RHI_RESULT_BUSY);
    ASSERT_EQ(rhi_device_destroy_ex(first), RHI_RESULT_BUSY);
    rhi_test_frame_owner_release(first);
    ASSERT_FALSE(rhi_test_frame_owner_is_current(first));
    ASSERT_TRUE(rhi_test_frame_owner_try_acquire(second));
    rhi_test_frame_owner_release(second);
    /* destroy 前必须 drain/无 in-flight：释放后 destroy 成立。 */
    ASSERT_EQ(rhi_device_destroy_ex(first), RHI_RESULT_OK);
    rhi_test_device_destroy(second);
}

TEST_MAIN_BEGIN()
    RUN_TEST(acquire_submit_present_drain_aliases_share_semantics);
    RUN_TEST(acquire_requires_ready_device);
    RUN_TEST(lost_device_fails_fast_on_full_frame_sequence);
    RUN_TEST(out_of_date_fails_fast_and_is_per_device);
    RUN_TEST(only_one_in_flight_acquire_submit_pair_per_thread);
TEST_MAIN_END()
