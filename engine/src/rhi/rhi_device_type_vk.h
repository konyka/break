#pragma once
#include <rhi/rhi.h>
#include <vulkan/vulkan.h>

static inline RHIDeviceType rhi_vk_device_type_from_native(VkPhysicalDeviceType type) {
    switch (type) {
    case VK_PHYSICAL_DEVICE_TYPE_OTHER: return RHI_DEVICE_TYPE_OTHER;
    case VK_PHYSICAL_DEVICE_TYPE_INTEGRATED_GPU: return RHI_DEVICE_TYPE_INTEGRATED;
    case VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU: return RHI_DEVICE_TYPE_DISCRETE;
    case VK_PHYSICAL_DEVICE_TYPE_VIRTUAL_GPU: return RHI_DEVICE_TYPE_VIRTUAL;
    case VK_PHYSICAL_DEVICE_TYPE_CPU: return RHI_DEVICE_TYPE_CPU;
    default: return RHI_DEVICE_TYPE_UNKNOWN;
    }
}
