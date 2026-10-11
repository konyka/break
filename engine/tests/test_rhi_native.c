#include "test_framework.h"

#include <rhi/rhi.h>

extern RHIDevice *rhi_test_device_create(void);
extern void rhi_test_device_destroy(RHIDevice *dev);

TEST(null_native_device_is_rejected)
{
    RHINativeDevice native = {0};

    ASSERT_FALSE(rhi_device_get_native_device(NULL, &native));
    ASSERT_FALSE(rhi_device_get_native_device(NULL, NULL));
}

TEST(test_device_does_not_expose_fake_vulkan_handles)
{
    RHIDevice *device = rhi_test_device_create();
    RHINativeDevice native = {0};

    ASSERT_NEQ(device, NULL);
    ASSERT_FALSE(rhi_device_get_native_device(device, &native));
    ASSERT_EQ(native.type, RHI_NATIVE_HANDLE_NONE);
    rhi_test_device_destroy(device);
}

TEST_MAIN_BEGIN()
    RUN_TEST(null_native_device_is_rejected);
    RUN_TEST(test_device_does_not_expose_fake_vulkan_handles);
TEST_MAIN_END()
