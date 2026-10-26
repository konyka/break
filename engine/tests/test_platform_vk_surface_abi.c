#include "test_framework.h"
#include "../src/platform/platform_vk_surface_vkabi.h"

#if defined(ENGINE_PLATFORM_WINDOWS)
#define VK_USE_PLATFORM_WIN32_KHR
#include <windows.h>
#elif defined(ENGINE_PLATFORM_MACOS) || defined(ENGINE_PLATFORM_IOS)
#define VK_USE_PLATFORM_METAL_EXT
#elif defined(ENGINE_PLATFORM_WAYLAND)
#define VK_USE_PLATFORM_WAYLAND_KHR
#include <wayland-client.h>
#elif defined(ENGINE_PLATFORM_ANDROID) && defined(ENGINE_ANDROID_NATIVE_WINDOW)
#define VK_USE_PLATFORM_ANDROID_KHR
#include <android/native_window.h>
#elif defined(ENGINE_PLATFORM_LINUX)
#define VK_USE_PLATFORM_XLIB_KHR
#include <X11/Xlib.h>
#elif defined(ENGINE_PLATFORM_QNX) && defined(ENGINE_QNX_SCREEN)
/* vulkan_screen.h forward-declares struct _screen_context/_screen_window,
 * so no <screen/screen.h> include is needed here. */
#define VK_USE_PLATFORM_SCREEN_QNX
#endif
#include <vulkan/vulkan.h>

/* 只钉死宿主平台分支：其余分支的等价断言由各平台 CI lane 上的同名测试承担。 */
#if defined(ENGINE_PLATFORM_WINDOWS)
TEST(win32_surface_create_info_abi) {
    ASSERT_EQ(sizeof(PVkWin32SurfaceCreateInfo), sizeof(VkWin32SurfaceCreateInfoKHR));
    ASSERT_EQ(PVK_STYPE_WIN32_SURFACE_CREATE_INFO_KHR,
              (u32)VK_STRUCTURE_TYPE_WIN32_SURFACE_CREATE_INFO_KHR);
}
#elif defined(ENGINE_PLATFORM_LINUX) && !defined(ENGINE_PLATFORM_WAYLAND)
TEST(xlib_surface_create_info_abi) {
    ASSERT_EQ(sizeof(PVkXlibSurfaceCreateInfo), sizeof(VkXlibSurfaceCreateInfoKHR));
    ASSERT_EQ(PVK_STYPE_XLIB_SURFACE_CREATE_INFO_KHR,
              (u32)VK_STRUCTURE_TYPE_XLIB_SURFACE_CREATE_INFO_KHR);
    ASSERT_EQ(sizeof(Window), sizeof(u64)); /* LP64 契约 */
}
#elif defined(ENGINE_PLATFORM_WAYLAND)
TEST(wayland_surface_create_info_abi) {
    ASSERT_EQ(sizeof(PVkWaylandSurfaceCreateInfo), sizeof(VkWaylandSurfaceCreateInfoKHR));
    ASSERT_EQ(PVK_STYPE_WAYLAND_SURFACE_CREATE_INFO_KHR,
              (u32)VK_STRUCTURE_TYPE_WAYLAND_SURFACE_CREATE_INFO_KHR);
}
#elif defined(ENGINE_PLATFORM_QNX) && defined(ENGINE_QNX_SCREEN)
TEST(screen_surface_create_info_abi_qnx) {
    ASSERT_EQ(sizeof(PVkScreenSurfaceCreateInfo), sizeof(VkScreenSurfaceCreateInfoQNX));
    ASSERT_EQ(offsetof(PVkScreenSurfaceCreateInfo, sType),
              offsetof(VkScreenSurfaceCreateInfoQNX, sType));
    ASSERT_EQ(offsetof(PVkScreenSurfaceCreateInfo, pNext),
              offsetof(VkScreenSurfaceCreateInfoQNX, pNext));
    ASSERT_EQ(offsetof(PVkScreenSurfaceCreateInfo, flags),
              offsetof(VkScreenSurfaceCreateInfoQNX, flags));
    ASSERT_EQ(offsetof(PVkScreenSurfaceCreateInfo, context),
              offsetof(VkScreenSurfaceCreateInfoQNX, context));
    ASSERT_EQ(offsetof(PVkScreenSurfaceCreateInfo, window),
              offsetof(VkScreenSurfaceCreateInfoQNX, window));
    ASSERT_EQ(PVK_STYPE_SCREEN_SURFACE_CREATE_INFO_QNX,
              (u32)VK_STRUCTURE_TYPE_SCREEN_SURFACE_CREATE_INFO_QNX);
}
#elif defined(ENGINE_PLATFORM_MACOS)
TEST(metal_surface_create_info_abi) {
    ASSERT_EQ(sizeof(PVkMetalSurfaceCreateInfo), sizeof(VkMetalSurfaceCreateInfoEXT));
    ASSERT_EQ(PVK_STYPE_METAL_SURFACE_CREATE_INFO_EXT,
              (u32)VK_STRUCTURE_TYPE_METAL_SURFACE_CREATE_INFO_EXT);
    ASSERT_EQ(PVK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR,
              (u32)VK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR);
}
#endif

TEST(dummy_when_no_host_branch) { ASSERT_TRUE(1); }

TEST_MAIN_BEGIN()
#if defined(ENGINE_PLATFORM_WINDOWS)
    RUN_TEST(win32_surface_create_info_abi);
#elif defined(ENGINE_PLATFORM_LINUX) && !defined(ENGINE_PLATFORM_WAYLAND)
    RUN_TEST(xlib_surface_create_info_abi);
#elif defined(ENGINE_PLATFORM_WAYLAND)
    RUN_TEST(wayland_surface_create_info_abi);
#elif defined(ENGINE_PLATFORM_MACOS)
    RUN_TEST(metal_surface_create_info_abi);
#elif defined(ENGINE_PLATFORM_QNX) && defined(ENGINE_QNX_SCREEN)
    RUN_TEST(screen_surface_create_info_abi_qnx);
#endif
    RUN_TEST(dummy_when_no_host_branch);
TEST_MAIN_END()
