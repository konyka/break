#include "test_framework.h"
#include <rhi/rhi.h>
#include <rhi/rhi_device_type_vk.h>

extern RHIDevice *rhi_test_device_create(void);
extern void rhi_test_device_destroy(RHIDevice *dev);

TEST(vulkan_device_type_values_and_mapping_match_native_abi)
{
    ASSERT_EQ(RHI_DEVICE_TYPE_UNKNOWN, -1);
    ASSERT_EQ(RHI_DEVICE_TYPE_OTHER, (int)VK_PHYSICAL_DEVICE_TYPE_OTHER);
    ASSERT_EQ(RHI_DEVICE_TYPE_INTEGRATED, (int)VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU);
    ASSERT_EQ(RHI_DEVICE_TYPE_DISCRETE, (int)VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU);
    ASSERT_EQ(RHI_DEVICE_TYPE_VIRTUAL, (int)VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU);
    ASSERT_EQ(RHI_DEVICE_TYPE_CPU, (int)VK_PHYSICAL_DEVICE_TYPE_CPU);

    ASSERT_EQ(rhi_vk_device_type_from_native(VK_PHYSICAL_DEVICE_TYPE_OTHER),
              RHI_DEVICE_TYPE_OTHER);
    ASSERT_EQ(rhi_vk_device_type_from_native(VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU),
              RHI_DEVICE_TYPE_INTEGRATED);
    ASSERT_EQ(rhi_vk_device_type_from_native(VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU),
              RHI_DEVICE_TYPE_DISCRETE);
    ASSERT_EQ(rhi_vk_device_type_from_native(VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU),
              RHI_DEVICE_TYPE_VIRTUAL);
    ASSERT_EQ(rhi_vk_device_type_from_native(VK_PHYSICAL_DEVICE_TYPE_CPU),
              RHI_DEVICE_TYPE_CPU);
    ASSERT_EQ(rhi_vk_device_type_from_native((VkPhysicalDeviceType)999),
              RHI_DEVICE_TYPE_UNKNOWN);
}

TEST(device_type_names_are_stable_for_receipts)
{
    ASSERT_TRUE(strcmp(rhi_device_type_name(RHI_DEVICE_TYPE_UNKNOWN), "UNKNOWN") == 0);
    ASSERT_TRUE(strcmp(rhi_device_type_name(RHI_DEVICE_TYPE_OTHER), "OTHER") == 0);
    ASSERT_TRUE(strcmp(rhi_device_type_name(RHI_DEVICE_TYPE_INTEGRATED), "INTEGRATED") == 0);
    ASSERT_TRUE(strcmp(rhi_device_type_name(RHI_DEVICE_TYPE_DISCRETE), "DISCRETE") == 0);
    ASSERT_TRUE(strcmp(rhi_device_type_name(RHI_DEVICE_TYPE_VIRTUAL), "VIRTUAL") == 0);
    ASSERT_TRUE(strcmp(rhi_device_type_name(RHI_DEVICE_TYPE_CPU), "CPU") == 0);
    ASSERT_TRUE(strcmp(rhi_device_type_name((RHIDeviceType)999), "UNKNOWN") == 0);
}

TEST(public_wrapper_defaults_to_unknown)
{
    RHIDevice *device = rhi_test_device_create();
    RHIDeviceInfo info;
    ASSERT_NEQ(device, NULL);
    memset(&info, 0xA5, sizeof(info));
    ASSERT_TRUE(rhi_device_get_info(device, &info));
    ASSERT_EQ(info.device_type, RHI_DEVICE_TYPE_UNKNOWN);
    rhi_test_device_destroy(device);
}

TEST_MAIN_BEGIN()
    RUN_TEST(vulkan_device_type_values_and_mapping_match_native_abi);
    RUN_TEST(device_type_names_are_stable_for_receipts);
    RUN_TEST(public_wrapper_defaults_to_unknown);
TEST_MAIN_END()
