#include "test_framework.h"

#include <rhi/rhi.h>
#include <rhi/rhi_native_vulkan.h>

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

TEST(test_headless_command_buffer_does_not_expose_fake_vulkan_handle)
{
    RHIDevice *device = rhi_test_device_create();
    RHICmdBufferNativeInfo info;
    memset(&info, 0xA5, sizeof(info));
    ASSERT_NEQ(device, NULL);
    ASSERT_FALSE(rhi_cmd_buffer_get_native_info(
        device, (const RHICmdBuffer *)(uintptr_t)1u, &info));
    ASSERT_EQ(info.type, RHI_NATIVE_HANDLE_NONE);
    ASSERT_FALSE(info.recording);
    rhi_test_device_destroy(device);
}

TEST(test_headless_native_proxy_outputs_are_zeroed)
{
    RHIDevice *device = rhi_test_device_create();
    RHIDeviceInfo device_info;
    RHITextureNativeInfo texture_info;

    ASSERT_NEQ(device, NULL);
    memset(&device_info, 0xA5, sizeof(device_info));
    memset(&texture_info, 0xA5, sizeof(texture_info));
    ASSERT_TRUE(rhi_device_get_info(device, &device_info));
    ASSERT_EQ(device_info.feature_bits, 0u);
    ASSERT_FALSE(rhi_texture_get_native_info(
        device, (RHITexture){1u, 1u}, &texture_info));
    ASSERT_EQ(texture_info.type, RHI_NATIVE_HANDLE_NONE);
    rhi_test_device_destroy(device);
}

TEST(test_headless_vulkan_acceleration_handle_fails_closed)
{
    RHIDevice *device = rhi_test_device_create();
    void *handle = (void *)(uintptr_t)1u;

    ASSERT_NEQ(device, NULL);
    ASSERT_FALSE(rhi_acceleration_structure_get_vk_handle(
        device, (RHIAccelerationStructure){1u, 1u}, &handle));
    ASSERT_EQ(handle, NULL);
    rhi_test_device_destroy(device);
}

TEST_MAIN_BEGIN()
    RUN_TEST(null_native_device_is_rejected);
    RUN_TEST(test_device_does_not_expose_fake_vulkan_handles);
    RUN_TEST(test_headless_command_buffer_does_not_expose_fake_vulkan_handle);
    RUN_TEST(test_headless_native_proxy_outputs_are_zeroed);
    RUN_TEST(test_headless_vulkan_acceleration_handle_fails_closed);
TEST_MAIN_END()
