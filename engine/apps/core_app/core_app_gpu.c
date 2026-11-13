#include "core_app_gpu.h"

#include <platform/platform.h>

#include <inttypes.h>
#include <stdlib.h>
#include <string.h>

/* RGBA8 readback converted to a top-down PPM. The RHI contract returns rows
 * bottom-up for at least one of the backends, so the flip is explicit here
 * instead of being silently assumed. */
static BreakRuntimeError write_ppm(const char *path, const u8 *rgba, u32 width, u32 height,
                                   u64 frame) {
    char resolved[1024];
    const char *percent = path ? strstr(path, "%u") : NULL;
    if (percent) {
        size_t head = (size_t)(percent - path);
        int written = snprintf(resolved, sizeof(resolved), "%.*s%" PRIu64 "%s", (int)head,
                               path, frame, percent + 2u);
        if (written < 0 || (size_t)written >= sizeof(resolved)) return BREAK_RUNTIME_INVALID;
    } else {
        int written = snprintf(resolved, sizeof(resolved), "%s", path);
        if (written < 0 || (size_t)written >= sizeof(resolved)) return BREAK_RUNTIME_INVALID;
    }
    FILE *out = fopen(resolved, "wb");
    if (!out) return BREAK_RUNTIME_FAILED;
    if (fprintf(out, "P6\n%u %u\n255\n", width, height) < 0) {
        fclose(out);
        return BREAK_RUNTIME_FAILED;
    }
    bool ok = true;
    for (u32 row = 0u; ok && row < height; ++row) {
        const u8 *source = rgba + (size_t)(height - 1u - row) * width * 4u;
        for (u32 column = 0u; column < width; ++column) {
            const u8 pixel[3] = {source[column * 4u], source[column * 4u + 1u],
                                 source[column * 4u + 2u]};
            if (fwrite(pixel, 1u, 3u, out) != 3u) ok = false;
        }
    }
    if (fclose(out) != 0) ok = false;
    return ok ? BREAK_RUNTIME_OK : BREAK_RUNTIME_FAILED;
}

BreakRuntimeError core_app_gpu_create(CoreAppGpu *gpu, const CoreAppGpuConfig *config,
                                      FILE *trace) {
    if (!gpu || !config || !trace) return BREAK_RUNTIME_INVALID;
    memset(gpu, 0, sizeof(*gpu));
    gpu->trace = trace;
    gpu->width = config->width == 0u ? 320u : config->width;
    gpu->height = config->height == 0u ? 240u : config->height;
    PlatformConfig platform_config;
    memset(&platform_config, 0, sizeof(platform_config));
    platform_config.width = gpu->width;
    platform_config.height = gpu->height;
    platform_config.title = "core_app";
    Platform *platform = platform_create(&platform_config);
    if (!platform) return BREAK_RUNTIME_UNAVAILABLE;
    gpu->platform = platform;
    u32 actual_width = 0u;
    u32 actual_height = 0u;
    platform_get_drawable_size(platform, &actual_width, &actual_height);
    if (actual_width == 0u || actual_height == 0u) {
        platform_destroy(platform);
        gpu->platform = NULL;
        return BREAK_RUNTIME_UNAVAILABLE;
    }
    gpu->width = actual_width;
    gpu->height = actual_height;
    RHIBackend backend = config->backend == CORE_APP_GPU_VULKAN ? RHI_BACKEND_VULKAN
                                                                : RHI_BACKEND_OPENGL;
    void *window = backend == RHI_BACKEND_VULKAN ? platform_surface_native(platform)
                                                 : platform_window_native(platform);
    RHIDevice *device = rhi_device_create(backend, window, platform_display_native(platform),
                                          gpu->width, gpu->height);
    if (!device) {
        platform_destroy(platform);
        gpu->platform = NULL;
        return BREAK_RUNTIME_UNAVAILABLE;
    }
    gpu->device = device;
    RHIDeviceInfo info;
    memset(&info, 0, sizeof(info));
    if (rhi_device_get_info(device, &info)) {
        snprintf(gpu->device_name, sizeof(gpu->device_name), "%s", info.device_name);
    }
    const char *active = rhi_runtime_active_backend();
    snprintf(gpu->backend_name, sizeof(gpu->backend_name), "%s",
             active ? active : (backend == RHI_BACKEND_VULKAN ? "vulkan" : "opengl"));
    if (!world_presenter_create(device, &gpu->presenter)) {
        rhi_device_destroy(device);
        platform_destroy(platform);
        gpu->device = NULL;
        gpu->platform = NULL;
        return BREAK_RUNTIME_FAILED;
    }
    gpu->live = true;
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_gpu_render(CoreAppGpu *gpu, const WorldFrameSnapshot *snapshot,
                                      const char *screenshot_path,
                                      const CoreAppGpuFrame *frame) {
    if (!gpu || !gpu->live || !snapshot || !frame) return BREAK_RUNTIME_INVALID;
    RHICmdBuffer *cmd = rhi_frame_begin(gpu->device);
    if (!cmd) return BREAK_RUNTIME_FAILED;
    rhi_cmd_begin_render_pass(cmd);
    rhi_cmd_clear_color(cmd, 0.05f, 0.06f, 0.08f, 1.0f);
    WorldSubmitStats stats;
    memset(&stats, 0, sizeof(stats));
    if (world_presenter_submit(cmd, &gpu->presenter, snapshot, &stats) != WORLD_PRESENTATION_OK) {
        rhi_cmd_end_render_pass(cmd);
        rhi_frame_end(gpu->device);
        return BREAK_RUNTIME_FAILED;
    }
    rhi_cmd_end_render_pass(cmd);
    rhi_frame_end(gpu->device);
    if (screenshot_path && screenshot_path[0] != '\0') {
        usize bytes = (usize)gpu->width * gpu->height * 4u;
        u8 *rgba = (u8 *)malloc(bytes);
        if (!rgba) return BREAK_RUNTIME_OOM;
        bool captured = rhi_screenshot(gpu->device, 0u, 0u, gpu->width, gpu->height, rgba,
                                       bytes);
        BreakRuntimeError result = BREAK_RUNTIME_OK;
        if (!captured) {
            result = BREAK_RUNTIME_FAILED;
        } else {
            result = write_ppm(screenshot_path, rgba, gpu->width, gpu->height, frame->frame);
            if (result == BREAK_RUNTIME_OK) gpu->screenshots_written++;
        }
        free(rgba);
        if (result != BREAK_RUNTIME_OK) return result;
    }
    rhi_present(gpu->device);
    gpu->frames_presented++;
    if (fprintf(gpu->trace,
                "COREAPPTRACE version=1 event=gpu backend=%s device=%s frame=%" PRIu64
                " generation=%" PRIu64 " draws=%u instances=%u\n",
                gpu->backend_name, gpu->device_name, frame->frame, frame->generation,
                stats.object_draws + stats.stream_draws, stats.instance_count) < 0 ||
        fflush(gpu->trace) != 0) {
        return BREAK_RUNTIME_FAILED;
    }
    return BREAK_RUNTIME_OK;
}

BreakRuntimeError core_app_gpu_destroy(CoreAppGpu *gpu) {
    if (!gpu) return BREAK_RUNTIME_INVALID;
    if (!gpu->live) return BREAK_RUNTIME_OK;
    rhi_device_idle(gpu->device);
    world_presenter_destroy(gpu->device, &gpu->presenter);
    rhi_device_destroy(gpu->device);
    platform_destroy((Platform *)gpu->platform);
    gpu->device = NULL;
    gpu->platform = NULL;
    gpu->live = false;
    return BREAK_RUNTIME_OK;
}
