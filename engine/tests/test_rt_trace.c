#include "test_framework.h"

#include <renderer/rt_trace.h>
#include <string.h>

extern RHIDevice *rhi_test_device_create(void);
extern void rhi_test_device_destroy(RHIDevice *dev);

/* Headless contract: the probe must fail closed with a classified reason for
 * null/stub arguments regardless of build configuration. The real ray-traced
 * pixel path is exercised by the Vulkan graphics suite on RT hardware. */

TEST(rt_trace_probe_fails_closed_on_stub_devices)
{
    RHIDevice *device = rhi_test_device_create();
    u8 pixel[4] = {9, 9, 9, 9};
    RHIAccelerationStructure tlas = (RHIAccelerationStructure){1u, 1u};

    ASSERT_NEQ(device, NULL);
    ASSERT_FALSE(rt_trace_probe(NULL, tlas, pixel));
    ASSERT_FALSE(rt_trace_probe(device, tlas, pixel));
    ASSERT_FALSE(rt_trace_probe(device, RHI_HANDLE_NULL, pixel));
    ASSERT_FALSE(rt_trace_probe(NULL, tlas, NULL));
    ASSERT_EQ(pixel[0], 0u);
    ASSERT_TRUE(strlen(rt_trace_last_error()) > 0);
    rhi_test_device_destroy(device);
}

/* 计划 E Task 7 逃生舱契约：非 VK 编译单元（本测试目标不带后端宏）上
 * rt_trace_probe 对 NULL device / NULL tlas fail-closed——返回 false、
 * out_pixel 清零、last_error 非 NULL 且非空。VK 编译单元的真实 RT probe
 * 由 test_vulkan 覆盖。 */
TEST(rt_trace_probe_null_args_fail_closed_with_error)
{
    u8 pixel[4] = {9, 9, 9, 9};

    ASSERT_FALSE(rt_trace_probe(NULL, RHI_HANDLE_NULL, pixel));
    ASSERT_EQ(pixel[0], 0u);
    ASSERT_FALSE(rt_trace_probe(NULL, RHI_HANDLE_NULL, NULL));
    ASSERT_TRUE(rt_trace_last_error() != NULL);
    ASSERT_TRUE(strlen(rt_trace_last_error()) > 0);
}

TEST_MAIN_BEGIN()
    RUN_TEST(rt_trace_probe_fails_closed_on_stub_devices);
    RUN_TEST(rt_trace_probe_null_args_fail_closed_with_error);
TEST_MAIN_END()
