#pragma once
#include <core/types.h>

/* 纯函数 Vulkan 探测/协商逻辑——不包含 <vulkan/vulkan.h>。数值常量与
 * VkPhysicalDeviceType / VkPresentModeKHR / VkFormat / VkColorSpaceKHR /
 * VkQueueFlagBits / RHIFeatureBits 一一对应，由 rhi_vk.c 顶部的
 * _Static_assert 组钉死（漂移即编译失败，而不是 GPU 上出错）。
 * 全部函数无堆分配、无全局状态，headless 单测直接包含。 */

/* VkPhysicalDeviceType */
#define VK_PROBE_DEVICE_TYPE_OTHER      0u
#define VK_PROBE_DEVICE_TYPE_INTEGRATED 1u
#define VK_PROBE_DEVICE_TYPE_DISCRETE   2u
#define VK_PROBE_DEVICE_TYPE_VIRTUAL    3u
#define VK_PROBE_DEVICE_TYPE_CPU        4u
/* VkQueueFlagBits */
#define VK_PROBE_QUEUE_GRAPHICS_BIT 0x00000001u
/* VkPresentModeKHR */
#define VK_PROBE_PRESENT_MODE_IMMEDIATE    0u
#define VK_PROBE_PRESENT_MODE_MAILBOX      1u
#define VK_PROBE_PRESENT_MODE_FIFO         2u
#define VK_PROBE_PRESENT_MODE_FIFO_RELAXED 3u
/* VkFormat / VkColorSpaceKHR */
#define VK_PROBE_FORMAT_UNDEFINED           0u
#define VK_PROBE_FORMAT_R8G8B8A8_UNORM      37u
#define VK_PROBE_FORMAT_R8G8B8A8_SRGB       43u
#define VK_PROBE_FORMAT_B8G8R8A8_UNORM      44u
#define VK_PROBE_FORMAT_B8G8R8A8_SRGB       50u
#define VK_PROBE_COLORSPACE_SRGB_NONLINEAR  0u
/* RHIFeatureBits（rhi.h:85-89） */
#define VK_PROBE_FEATURE_RAY_TRACING_PIPELINE 1u
#define VK_PROBE_FEATURE_RAY_QUERY            2u
#define VK_PROBE_FEATURE_ACCELERATION_STRUCTURE 4u

typedef struct VkProbeAdapterInfo {
    u32  device_type;  /* VkPhysicalDeviceType 数值 */
    u32  api_version;  /* VkPhysicalDeviceProperties.apiVersion 编码值 */
    bool suitable;     /* vk_physical_device_suitable 的预计算结果 */
} VkProbeAdapterInfo;

typedef struct VkProbeSurfaceFormat {
    u32 format;
    u32 color_space;
} VkProbeSurfaceFormat;

/* Adapter 打分：discrete > integrated > virtual > software(cpu) > other；
 * 不可用（suitable=false）得 -1，永不中选。 */
static inline i32 vk_probe_adapter_score(const VkProbeAdapterInfo *info) {
    if (info == NULL || !info->suitable) return -1;
    switch (info->device_type) {
    case VK_PROBE_DEVICE_TYPE_DISCRETE:   return 300;
    case VK_PROBE_DEVICE_TYPE_INTEGRATED: return 200;
    case VK_PROBE_DEVICE_TYPE_VIRTUAL:    return 100;
    case VK_PROBE_DEVICE_TYPE_CPU:        return 10;
    default:                              return 0;
    }
}

/* 返回最高分的下标；同分取 api_version 更高者，再同取下标更小者；
 * 全部不可用返回 -1。 */
static inline i32 vk_probe_select_adapter(const VkProbeAdapterInfo *adapters,
                                          u32 count) {
    i32 best = -1;
    i32 best_score = -1;
    u32 best_api = 0u;
    u32 i;
    if (adapters == NULL) return -1;
    for (i = 0; i < count; i++) {
        i32 score = vk_probe_adapter_score(&adapters[i]);
        if (score < 0) continue;
        if (score > best_score ||
            (score == best_score && adapters[i].api_version > best_api)) {
            best = (i32)i;
            best_score = score;
            best_api = adapters[i].api_version;
        }
    }
    return best;
}

/* queue family：优先同时具备 graphics+present 的 family（swapchain 可用
 * EXCLUSIVE sharing，少一条 queue）；否则首个 graphics + 首个 present。
 * 任一缺失返回 false。 */
static inline bool vk_probe_choose_queue_families(const u32 *queue_flags,
                                                  const bool *present_support,
                                                  u32 family_count,
                                                  u32 *out_graphics,
                                                  u32 *out_present) {
    u32 graphics = UINT32_MAX;
    u32 present = UINT32_MAX;
    u32 i;
    if (queue_flags == NULL || present_support == NULL ||
        out_graphics == NULL || out_present == NULL)
        return false;
    for (i = 0; i < family_count; i++) {
        bool has_graphics = (queue_flags[i] & VK_PROBE_QUEUE_GRAPHICS_BIT) != 0u;
        if (has_graphics && present_support[i]) {
            *out_graphics = i;
            *out_present = i;
            return true;
        }
        if (has_graphics && graphics == UINT32_MAX) graphics = i;
        if (present_support[i] && present == UINT32_MAX) present = i;
    }
    if (graphics == UINT32_MAX || present == UINT32_MAX) return false;
    *out_graphics = graphics;
    *out_present = present;
    return true;
}

/* present mode 协商（输入为 VkPresentModeKHR 数值数组）：
 * vsync 开：MAILBOX > FIFO_RELAXED > FIFO；
 * vsync 关：IMMEDIATE > MAILBOX > FIFO_RELAXED > FIFO
 *（锁定既有行为 rhi_vk.c:1151-1168）。FIFO 由规范保证存在；全部缺失时仍返回
 * FIFO，让调用方在创建时报错而不是静默选错。 */
static inline u32 vk_probe_choose_present_mode(const u32 *modes, u32 count,
                                               bool vsync) {
    static const u32 vsync_order[] = {
        VK_PROBE_PRESENT_MODE_MAILBOX, VK_PROBE_PRESENT_MODE_FIFO_RELAXED,
        VK_PROBE_PRESENT_MODE_FIFO,
    };
    static const u32 no_vsync_order[] = {
        VK_PROBE_PRESENT_MODE_IMMEDIATE, VK_PROBE_PRESENT_MODE_MAILBOX,
        VK_PROBE_PRESENT_MODE_FIFO_RELAXED, VK_PROBE_PRESENT_MODE_FIFO,
    };
    const u32 *order = vsync ? vsync_order : no_vsync_order;
    u32 order_count = vsync ? 3u : 4u;
    u32 oi, i;
    if (modes != NULL) {
        for (oi = 0; oi < order_count; oi++)
            for (i = 0; i < count; i++)
                if (modes[i] == order[oi]) return order[oi];
    }
    return VK_PROBE_PRESENT_MODE_FIFO;
}

/* surface format 协商：
 * count==1 且 format==UNDEFINED（"任意格式"哨兵）→ B8G8R8A8_UNORM + 其
 * colorSpace；否则首选 B8G8R8A8_UNORM，再 R8G8B8A8_UNORM，否则 formats[0]。
 * count==0 / 参数为 NULL 返回 false。
 *
 * R646：改为优先 UNORM。引擎的 tonemap / 颜色分级着色器自己做伽马编码
 * （tonemap.frag 的 exp2(log2(ldr) / gamma)），GL 默认帧缓冲与 D3D12 的
 * B8G8R8A8_UNORM 交换链都按原样写出。Vulkan 选 *_SRGB 交换链会在写入时
 * 再做一次 linear->sRGB 编码，等于伽马叠加两次：画面整体发白（与 GL 截图
 * 比 MAE 57，对 GL 图做一次 sRGB 编码后降到 2.7）。 */
static inline bool vk_probe_choose_surface_format(const VkProbeSurfaceFormat *formats,
                                                  u32 count,
                                                  VkProbeSurfaceFormat *out) {
    u32 i;
    if (formats == NULL || out == NULL || count == 0u) return false;
    if (count == 1u && formats[0].format == VK_PROBE_FORMAT_UNDEFINED) {
        out->format = VK_PROBE_FORMAT_B8G8R8A8_UNORM;
        out->color_space = formats[0].color_space;
        return true;
    }
    for (i = 0; i < count; i++) {
        if (formats[i].format == VK_PROBE_FORMAT_B8G8R8A8_UNORM) {
            *out = formats[i];
            return true;
        }
    }
    for (i = 0; i < count; i++) {
        if (formats[i].format == VK_PROBE_FORMAT_R8G8B8A8_UNORM) {
            *out = formats[i];
            return true;
        }
    }
    *out = formats[0];
    return true;
}

/* RHIFeatureBits 组装：只报告扩展存在且特性已启用的位（调用方责任）。 */
static inline u32 vk_probe_feature_bits(bool accel, bool rt_pipeline,
                                        bool ray_query) {
    return (accel ? VK_PROBE_FEATURE_ACCELERATION_STRUCTURE : 0u) |
           (rt_pipeline ? VK_PROBE_FEATURE_RAY_TRACING_PIPELINE : 0u) |
           (ray_query ? VK_PROBE_FEATURE_RAY_QUERY : 0u);
}
