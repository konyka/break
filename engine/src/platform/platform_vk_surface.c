#include <platform/platform_vk_surface.h>
#include "platform_vk_surface_vkabi.h"
#include <string.h>

#if defined(ENGINE_PLATFORM_ANDROID) && defined(ENGINE_ANDROID_NATIVE_WINDOW)
#include <android/native_window.h>
#endif

u32 platform_vk_required_instance_extensions(Platform *p, const char **out,
                                             u32 capacity) {
    static const char *const extensions[] = {
        "VK_KHR_surface",
#if defined(ENGINE_PLATFORM_WINDOWS)
        "VK_KHR_win32_surface",
#elif defined(ENGINE_PLATFORM_MACOS) || defined(ENGINE_PLATFORM_IOS)
        "VK_EXT_metal_surface",
        "VK_KHR_portability_enumeration",
        "VK_KHR_get_physical_device_properties2",
#elif defined(ENGINE_PLATFORM_WAYLAND)
        "VK_KHR_wayland_surface",
#elif defined(ENGINE_PLATFORM_ANDROID)
        "VK_KHR_android_surface",
#elif defined(ENGINE_PLATFORM_LINUX)
        "VK_KHR_xlib_surface",
#endif
    };
    const u32 count = (u32)(sizeof(extensions) / sizeof(extensions[0]));
    u32 i;
    (void)p; /* 平台是编译期常量；参数保留给将来按窗口定制的扩展。 */
    if (out == NULL || capacity < count) return count;
    for (i = 0; i < count; i++) out[i] = extensions[i];
    return count;
}

u32 platform_vk_instance_create_flags(Platform *p) {
    (void)p;
#if defined(ENGINE_PLATFORM_MACOS) || defined(ENGINE_PLATFORM_IOS)
    /* MoltenVK 是 portability 驱动，必须显式 opt in 枚举。 */
    return PVK_INSTANCE_CREATE_ENUMERATE_PORTABILITY_BIT_KHR;
#else
    return 0u;
#endif
}

/* get_proc 返回 void *；函数指针与 void * 的互转全部经 memcpy，
 * 否则 -Wpedantic 报错（ISO C 不允许这两类指针直接强转）。
 * 仅在存在可用的平台 WSI 分支时定义；QNX/OHOS 等 fail-closed 平台
 * 没有任何调用点，定义出来只会触发 -Werror=unused-function。 */
#if defined(ENGINE_PLATFORM_WINDOWS) || defined(ENGINE_PLATFORM_MACOS) || \
    defined(ENGINE_PLATFORM_IOS) || defined(ENGINE_PLATFORM_WAYLAND) || \
    (defined(ENGINE_PLATFORM_ANDROID) && defined(ENGINE_ANDROID_NATIVE_WINDOW)) || \
    defined(ENGINE_PLATFORM_LINUX)
static PVkCreateSurfaceFn pvk_resolve(void *vk_instance, void *vk_get_proc_addr,
                                      const char *entry_name) {
    PVkGetProcAddrFn get_proc;
    PVkCreateSurfaceFn create = NULL;
    void *entry;
    memcpy(&get_proc, &vk_get_proc_addr, sizeof(get_proc));
    entry = get_proc(vk_instance, entry_name);
    if (entry != NULL) memcpy(&create, &entry, sizeof(create));
    return create;
}
#endif

u64 platform_vk_create_surface(Platform *p, void *vk_instance,
                               void *vk_get_proc_addr, u64 *out_surface) {
    if (p == NULL) return PLATFORM_VK_SURFACE_ERROR_INVALID_ARGUMENT;
    return platform_vk_create_surface_handles(platform_surface_native(p),
                                              platform_display_native(p),
                                              vk_instance, vk_get_proc_addr,
                                              out_surface);
}

u64 platform_vk_create_surface_handles(void *surface_native,
                                       void *display_native,
                                       void *vk_instance,
                                       void *vk_get_proc_addr,
                                       u64 *out_surface) {
    PVkCreateSurfaceFn create;
    if (vk_instance == NULL || vk_get_proc_addr == NULL || out_surface == NULL)
        return PLATFORM_VK_SURFACE_ERROR_INVALID_ARGUMENT;
    *out_surface = 0u;
#if defined(ENGINE_PLATFORM_WINDOWS)
    {
        PVkWin32SurfaceCreateInfo ci;
        if (surface_native == NULL || display_native == NULL)
            return PLATFORM_VK_SURFACE_ERROR_UNAVAILABLE;
        ci.sType = PVK_STYPE_WIN32_SURFACE_CREATE_INFO_KHR;
        ci.pNext = NULL;
        ci.flags = 0u;
        ci.hinstance = display_native;  /* HINSTANCE（window_win32.c:685-687）*/
        ci.hwnd = surface_native;       /* HWND（window_win32.c:689-691）*/
        create = pvk_resolve(vk_instance, vk_get_proc_addr, "vkCreateWin32SurfaceKHR");
        if (create == NULL) return PLATFORM_VK_SURFACE_ERROR_PROC_MISSING;
        if (create(vk_instance, &ci, NULL, out_surface) != 0)
            return PLATFORM_VK_SURFACE_ERROR_CREATE_FAILED;
        return PLATFORM_VK_SURFACE_OK;
    }
#elif defined(ENGINE_PLATFORM_MACOS) || defined(ENGINE_PLATFORM_IOS)
    {
        PVkMetalSurfaceCreateInfo ci;
        (void)display_native;
        if (surface_native == NULL) return PLATFORM_VK_SURFACE_ERROR_UNAVAILABLE;
        ci.sType = PVK_STYPE_METAL_SURFACE_CREATE_INFO_EXT;
        ci.pNext = NULL;
        ci.flags = 0u;
        ci.pLayer = surface_native; /* CAMetalLayer *（window_cocoa.m:494）*/
        create = pvk_resolve(vk_instance, vk_get_proc_addr, "vkCreateMetalSurfaceEXT");
        if (create == NULL) return PLATFORM_VK_SURFACE_ERROR_PROC_MISSING;
        if (create(vk_instance, &ci, NULL, out_surface) != 0)
            return PLATFORM_VK_SURFACE_ERROR_CREATE_FAILED;
        return PLATFORM_VK_SURFACE_OK;
    }
#elif defined(ENGINE_PLATFORM_WAYLAND)
    {
        PVkWaylandSurfaceCreateInfo ci;
        if (surface_native == NULL || display_native == NULL)
            return PLATFORM_VK_SURFACE_ERROR_UNAVAILABLE;
        ci.sType = PVK_STYPE_WAYLAND_SURFACE_CREATE_INFO_KHR;
        ci.pNext = NULL;
        ci.flags = 0u;
        ci.display = display_native; /* struct wl_display *（window_wayland.c:2015-2017）*/
        ci.surface = surface_native; /* struct wl_surface *（window_wayland.c:2019-2021）*/
        create = pvk_resolve(vk_instance, vk_get_proc_addr, "vkCreateWaylandSurfaceKHR");
        if (create == NULL) return PLATFORM_VK_SURFACE_ERROR_PROC_MISSING;
        if (create(vk_instance, &ci, NULL, out_surface) != 0)
            return PLATFORM_VK_SURFACE_ERROR_CREATE_FAILED;
        return PLATFORM_VK_SURFACE_OK;
    }
#elif defined(ENGINE_PLATFORM_ANDROID)
#if defined(ENGINE_ANDROID_NATIVE_WINDOW)
    {
        PVkAndroidSurfaceCreateInfo ci;
        if (surface_native == NULL) return PLATFORM_VK_SURFACE_ERROR_UNAVAILABLE;
        ci.sType = PVK_STYPE_ANDROID_SURFACE_CREATE_INFO_KHR;
        ci.pNext = NULL;
        ci.flags = 0u;
        ci.window = surface_native; /* struct ANativeWindow *（window_mobile.c:60）*/
        create = pvk_resolve(vk_instance, vk_get_proc_addr, "vkCreateAndroidSurfaceKHR");
        if (create == NULL) return PLATFORM_VK_SURFACE_ERROR_PROC_MISSING;
        /* 引用配对：acquire 从原 rhi_vk.c:1484 迁到这里；成功路径的 release 仍在
         * vk_shutdown（原 rhi_vk.c:2486）；失败路径本地回滚，不泄漏引用。 */
        ANativeWindow_acquire((struct ANativeWindow *)surface_native);
        if (create(vk_instance, &ci, NULL, out_surface) != 0) {
            ANativeWindow_release((struct ANativeWindow *)surface_native);
            return PLATFORM_VK_SURFACE_ERROR_CREATE_FAILED;
        }
        return PLATFORM_VK_SURFACE_OK;
    }
#else
    (void)surface_native; (void)display_native; (void)create;
    return PLATFORM_VK_SURFACE_ERROR_UNAVAILABLE;
#endif
#elif defined(ENGINE_PLATFORM_LINUX)
    {
        PVkXlibSurfaceCreateInfo ci;
        if (surface_native == NULL || display_native == NULL)
            return PLATFORM_VK_SURFACE_ERROR_UNAVAILABLE;
        ci.sType = PVK_STYPE_XLIB_SURFACE_CREATE_INFO_KHR;
        ci.pNext = NULL;
        ci.flags = 0u;
        ci.dpy = display_native; /* Display *（window_x11.c:1170-1172）*/
        /* Window = unsigned long：window_x11.c:1174-1176 以 (void*)(uintptr_t)
         * 传出，这里按原路转回。 */
        ci.window = (u64)(uintptr_t)surface_native;
        create = pvk_resolve(vk_instance, vk_get_proc_addr, "vkCreateXlibSurfaceKHR");
        if (create == NULL) return PLATFORM_VK_SURFACE_ERROR_PROC_MISSING;
        if (create(vk_instance, &ci, NULL, out_surface) != 0)
            return PLATFORM_VK_SURFACE_ERROR_CREATE_FAILED;
        return PLATFORM_VK_SURFACE_OK;
    }
#else
    /* OHOS 及未知平台：fail-closed，不伪造 surface（规格 §4.5）。 */
    (void)surface_native; (void)display_native; (void)create;
    return PLATFORM_VK_SURFACE_ERROR_UNAVAILABLE;
#endif
}
