/* 真 GPU 分配故障注入：rhi_vk_set_alloc_failure_for_test 使
 * vk_allocate_memory 直接失败。无 Vulkan 构建或无可建窗口/GPU 的环境
 * return 77（注册处 SKIP_RETURN_CODE 77 → CTest 记为跳过而非通过）。 */
#include "engine.h"
#include "rhi/rhi.h"
#include "platform/platform.h"
#include <stdlib.h>

int main(void) {
#ifndef ENGINE_VULKAN
    return 77;
#else
    PlatformConfig cfg = { 640u, 480u, "rhi-alloc-fault", NULL, NULL, false, false };
    Platform *platform = platform_create(&cfg);
    RHIDevice *dev;
    RHITextureDesc desc = { 256u, 256u, RHI_FORMAT_R8G8B8A8_UNORM, 1u, NULL };
    RHITexture tex;
    RHITexture recovered;
    u32 w = 0u, h = 0u;
    if (platform == NULL) return 77;
    platform_get_drawable_size(platform, &w, &h);
    dev = rhi_device_create(RHI_BACKEND_VULKAN, platform_surface_native(platform),
                            platform_display_native(platform), w, h);
    if (dev == NULL) { platform_destroy(platform); return 77; }

    rhi_vk_set_alloc_failure_for_test(true);
    tex = rhi_texture_create(dev, &desc);
    rhi_vk_set_alloc_failure_for_test(false);
    if (rhi_handle_valid(tex)) {
        /* 注入后仍成功 = 钩子失效 */
        rhi_texture_destroy(dev, tex);
        rhi_device_destroy(dev);
        platform_destroy(platform);
        return 1;
    }
    recovered = rhi_texture_create(dev, &desc);
    if (!rhi_handle_valid(recovered)) {
        /* 关闭注入后必须恢复——故障不得毒化设备 */
        rhi_device_destroy(dev);
        platform_destroy(platform);
        return 1;
    }
    rhi_texture_destroy(dev, recovered);
    rhi_device_destroy(dev);
    platform_destroy(platform);
    return 0;
#endif
}
