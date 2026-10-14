#pragma once
#include <core/types.h>

/* 五个 WSI surface create-info 的最小 ABI 声明。sType 数值与字段布局由
 * engine/tests/test_platform_vk_surface_abi.c 对照真实 <vulkan/vulkan.h>
 * 逐字段钉死；任何漂移在编译期/测试期失败，而不是在 GPU 上出错。 */
#define PVK_STYPE_XLIB_SURFACE_CREATE_INFO_KHR    1000004000u
#define PVK_STYPE_WAYLAND_SURFACE_CREATE_INFO_KHR 1000006000u
#define PVK_STYPE_ANDROID_SURFACE_CREATE_INFO_KHR 1000008000u
#define PVK_STYPE_WIN32_SURFACE_CREATE_INFO_KHR   1000009000u
#define PVK_STYPE_METAL_SURFACE_CREATE_INFO_EXT   1000217000u
#define PVK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR 0x00000001u

typedef struct PVkWin32SurfaceCreateInfo {
    u32 sType; const void *pNext; u32 flags; void *hinstance; void *hwnd;
} PVkWin32SurfaceCreateInfo;
typedef struct PVkXlibSurfaceCreateInfo {
    /* Window 在 LP64 上是 unsigned long：按 u64 承载（ABI 测试在 Linux 钉死）。 */
    u32 sType; const void *pNext; u32 flags; void *dpy; u64 window;
} PVkXlibSurfaceCreateInfo;
typedef struct PVkWaylandSurfaceCreateInfo {
    u32 sType; const void *pNext; u32 flags; void *display; void *surface;
} PVkWaylandSurfaceCreateInfo;
typedef struct PVkAndroidSurfaceCreateInfo {
    u32 sType; const void *pNext; u32 flags; void *window;
} PVkAndroidSurfaceCreateInfo;
typedef struct PVkMetalSurfaceCreateInfo {
    u32 sType; const void *pNext; u32 flags; const void *pLayer;
} PVkMetalSurfaceCreateInfo;

/* 五个 vkCreate*SurfaceKHR 共享同一签名形状：(instance, create_info,
 * allocator, out_surface)，VkResult 为 i32。 */
typedef i32 (*PVkCreateSurfaceFn)(void *instance, const void *create_info,
                                  const void *allocator, u64 *out_surface);
typedef void *(*PVkGetProcAddrFn)(void *instance, const char *name);
