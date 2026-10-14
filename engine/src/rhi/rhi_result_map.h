#pragma once
#include <rhi/rhi.h>

/* VkResult 数值常量（避免纯逻辑层包含 <vulkan/vulkan.h>）：
 * VK_ERROR_OUT_OF_HOST_MEMORY = -1，VK_ERROR_OUT_OF_DEVICE_MEMORY = -2，
 * VK_ERROR_DEVICE_LOST = -4，VK_ERROR_SURFACE_LOST_KHR = -1000000000，
 * VK_ERROR_OUT_OF_DATE_KHR = -1000001004。
 * 由 rhi_vk.c 的 _Static_assert 组钉死。映射锁定既有语义
 *（rhi_vk.c:504-509）：其余一切（含 OOM）归 SYNC_FAILED。 */
static inline RHIResult rhi_vk_result_to_lifecycle(i32 vk_result) {
    if (vk_result == -4) return RHI_RESULT_DEVICE_LOST;
    if (vk_result == -1000001004) return RHI_RESULT_OUT_OF_DATE;
    if (vk_result == -1000000000) return RHI_RESULT_SURFACE_LOST;
    return RHI_RESULT_SYNC_FAILED;
}
