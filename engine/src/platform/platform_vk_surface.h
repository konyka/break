#pragma once
#include <core/types.h>
#include <platform/platform.h>

/* platform 层不包含 <vulkan/vulkan.h>（分层规则：PAL 只依赖 OS API）。
 * VkInstance 以 void * 传入；VkSurfaceKHR（不可分派句柄，64 位）以 u64 传出；
 * vkGetInstanceProcAddr 以 void * 传入（调用方用 memcpy 桥接函数指针，
 * 见 rhi_vk.c 接线处的 gpa 桥接——避免 -Wpedantic 的函数指针/void* 强转）。 */

typedef enum PlatformVkSurfaceError {
    PLATFORM_VK_SURFACE_OK = 0,
    PLATFORM_VK_SURFACE_ERROR_INVALID_ARGUMENT = 1, /* 参数为 NULL */
    PLATFORM_VK_SURFACE_ERROR_UNAVAILABLE = 2,      /* 平台无 WSI（OHOS 等）或原生句柄为空 */
    PLATFORM_VK_SURFACE_ERROR_PROC_MISSING = 3,     /* get_proc_addr 解析不到入口 */
    PLATFORM_VK_SURFACE_ERROR_CREATE_FAILED = 4,    /* vkCreate*SurfaceKHR 返回非 0 */
} PlatformVkSurfaceError;

/* 必需的 Vulkan instance 扩展（编译期平台常量）。两段式惯用法：
 * out == NULL 或 capacity < 所需个数时不写入、返回所需个数。 */
u32 platform_vk_required_instance_extensions(Platform *p, const char **out,
                                             u32 capacity);

/* VkInstanceCreateInfo.flags 中本平台需要的位（目前仅 macOS/iOS MoltenVK 需要
 * VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR = 0x1；其余平台为 0）。 */
u32 platform_vk_instance_create_flags(Platform *p);

/* 是否为可选的 instance 扩展：缺失时不算错误，而是不启用。目前只有
 * VK_KHR_portability_enumeration：它由 Vulkan loader 提供，用来让 loader
 * 枚举 portability 驱动；可执行文件直接链接 MoltenVK（不经 loader）时没有
 * 这个扩展，但也不需要它，MoltenVK 本身就是那个驱动。 */
bool platform_vk_instance_extension_optional(const char *name);

/* 按实际可用的扩展整理 instance 创建参数：available(name, user) 回答某扩展
 * 是否可用。必需扩展缺失时返回 false，并通过 out_missing 给出第一个缺失的
 * 名字；可选扩展缺失时把它从 names 中移除（保持其余顺序），并在移除
 * portability 枚举扩展时清除 *flags 中的 ENUMERATE_PORTABILITY 位（不启用该
 * 扩展却设置这个位，vkCreateInstance 会失败）。*count 更新为保留的个数。 */
bool platform_vk_resolve_instance_extensions(const char **names, u32 *count, u32 *flags,
                                             bool (*available)(const char *name, void *user),
                                             void *user, const char **out_missing);

/* 经 Platform 句柄创建 surface（platform_surface_native /
 * platform_display_native 解包后转发给 *_handles）。 */
u64 platform_vk_create_surface(Platform *p, void *vk_instance,
                               void *vk_get_proc_addr, u64 *out_surface);

/* 经原生句柄创建 surface。rhi_vk.c 的 vk_init 持有的是裸句柄而非 Platform
 * （rhi_device_create 的公开 ABI 不变），故消费本入口；调用方拥有结果
 * surface 的销毁权（vkDestroySurfaceKHR 仍在 rhi_vk.c）。Android：成功时本
 * 函数对 ANativeWindow 持有一个引用（acquire），由调用方 shutdown 路径释放
 * （原 rhi_vk.c:2486 的 ANativeWindow_release 不动）；失败路径本函数自行
 * release 回滚。 */
u64 platform_vk_create_surface_handles(void *surface_native,
                                       void *display_native,
                                       void *vk_instance,
                                       void *vk_get_proc_addr,
                                       u64 *out_surface);
