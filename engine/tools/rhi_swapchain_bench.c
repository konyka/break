#include "engine.h"
#include "rhi/rhi.h"
#include "platform/platform.h"
#include <core/log.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BENCH_FRAMES 600

static f64 now_ms(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
    return (f64)ts.tv_sec * 1000.0 + (f64)ts.tv_nsec / 1.0e6;
}

static const char *env_or(const char *name, const char *fallback) {
    const char *v = getenv(name);
    return (v != NULL && v[0] != '\0') ? v : fallback;
}

static int cmp_f64(const void *a, const void *b) {
    f64 fa = *(const f64 *)a, fb = *(const f64 *)b;
    return (fa > fb) - (fa < fb);
}

int main(int argc, char **argv) {
    PlatformConfig cfg = { 640u, 480u, "rhi-swapchain-bench", NULL, NULL, false, false, false, 0.0f };
    static f64 frame_ms[BENCH_FRAMES];
    Platform *platform;
    RHIDevice *dev;
    RHIDeviceInfo info;
    u32 w = 0u, h = 0u, i;
    f64 sum, avg_ms, p99_ms, fps_avg;
    FILE *out;
    if (argc < 2) return 2;
    platform = platform_create(&cfg);
    if (platform == NULL) return 77;
    platform_get_drawable_size(platform, &w, &h);
#if defined(ENGINE_RHI_BACKEND_D3D12)
    /* D3D12 consumes window_native (real HWND; rhi_d3d12.c refuses proxies). */
    dev = rhi_device_create(RHI_BACKEND_D3D12, platform_window_native(platform),
                            platform_display_native(platform), w, h);
#elif defined(ENGINE_RHI_BACKEND_METAL)
    /* Metal consumes window_native (Cocoa returns the CAMetalLayer). */
    dev = rhi_device_create(RHI_BACKEND_METAL, platform_window_native(platform),
                            platform_display_native(platform), w, h);
#elif defined(ENGINE_VULKAN)
    dev = rhi_device_create(RHI_BACKEND_VULKAN, platform_surface_native(platform),
                            platform_display_native(platform), w, h);
#else
    dev = rhi_device_create(RHI_BACKEND_OPENGL, platform_window_native(platform),
                            platform_display_native(platform), w, h);
#endif
    if (dev == NULL) { platform_destroy(platform); return 77; }
    rhi_set_vsync(dev, false);
    memset(&info, 0, sizeof(info));
    (void)rhi_device_get_info(dev, &info);
    for (i = 0; i < BENCH_FRAMES; i++) {
        f64 t0 = now_ms();
        RHICmdBuffer *cmd = rhi_frame_begin(dev);
        if (cmd == NULL) { rhi_device_destroy(dev); platform_destroy(platform); return 1; }
        rhi_cmd_clear_color(cmd, 0.1f, 0.2f, 0.3f, 1.0f);
        rhi_frame_end(dev);
#if defined(ENGINE_RHI_BACKEND_D3D12)
        /* Pixel proof for the swapchain readback path: rhi_screenshot was
         * a stub here, so nothing this backend drew could be verified. The
         * clear color is known and the D3D12 back buffer is contractually
         * B8G8R8A8_UNORM (non-sRGB), so 0.1/0.2/0.3/1.0 must come back as
         * RGBA bytes 26/51/76/255 (+/-2 for the f32->unorm rounding). */
        if (i == 0u && getenv("BREAK_BENCH_READBACK") != NULL) {
            unsigned char px[4u * 4u * 4u];
            const int expect[4] = { 26, 51, 76, 255 };
            int mismatch = 0;
            unsigned k;
            int c;
            memset(px, 0, sizeof(px));
            if (!rhi_screenshot(dev, 0u, 0u, 4u, 4u, px, sizeof(px))) {
                fprintf(stderr, "readback: rhi_screenshot failed\n");
                rhi_device_destroy(dev); platform_destroy(platform);
                return 1;
            }
            for (k = 0u; k < 16u && !mismatch; ++k) {
                const unsigned char *p = px + (size_t)k * 4u;
                for (c = 0; c < 4; ++c) {
                    int diff = (int)p[c] - expect[c];
                    if (diff < 0) diff = -diff;
                    if (diff > 2) mismatch = 1;
                }
            }
            if (mismatch) {
                fprintf(stderr, "readback: clear color MISMATCH, first px "
                        "= %u %u %u %u (expect %d %d %d %d)\n",
                        px[0], px[1], px[2], px[3],
                        expect[0], expect[1], expect[2], expect[3]);
                rhi_device_destroy(dev); platform_destroy(platform);
                return 1;
            }
            fprintf(stderr, "readback: clear color verified (%u %u %u %u)\n",
                    px[0], px[1], px[2], px[3]);
        }
#endif
        rhi_present(dev);
        frame_ms[i] = now_ms() - t0;
    }
    qsort(frame_ms, BENCH_FRAMES, sizeof(frame_ms[0]), cmp_f64);
    sum = 0.0;
    for (i = 0; i < BENCH_FRAMES; i++) sum += frame_ms[i];
    avg_ms = sum / (f64)BENCH_FRAMES;
    p99_ms = frame_ms[(BENCH_FRAMES * 99u) / 100u];
    fps_avg = avg_ms > 0.0 ? 1000.0 / avg_ms : 0.0;
    out = fopen(argv[1], "wb");
    if (out == NULL) { rhi_device_destroy(dev); platform_destroy(platform); return 1; }
    /* timestamp 由 CI step 注入环境变量 RECEIPT_TIMESTAMP（date -u +%FT%TZ），
     * 避免在 C 里手写时间格式化。 */
    fprintf(out,
        "{\n"
        "  \"schema_version\": 1,\n"
        "  \"timestamp\": \"%s\",\n"
        "  \"platform\": \"%s\",\n"
        "  \"os_version\": \"%s\",\n"
        "  \"backend\": \"%s\",\n"
        "  \"gpu\": \"%s\",\n"
        "  \"driver_version\": \"%u\",\n"
        "  \"cpu\": \"%s\",\n"
        "  \"ram\": \"%s\",\n"
        "  \"build_commit\": \"%s\",\n"
        "  \"build_config\": \"%s\",\n"
        "  \"command\": \"rhi_swapchain_bench\",\n"
        "  \"metrics\": { \"fps_avg\": %.2f, \"fps_p1\": %.2f,\n"
        "    \"frame_ms_avg\": %.4f, \"frame_ms_p99\": %.4f },\n"
        "  \"evidence_level\": \"GPU_RUNTIME\",\n"
        "  \"runner\": \"%s\"\n"
        "}\n",
        env_or("RECEIPT_TIMESTAMP", "unknown"),
#ifdef ENGINE_PLATFORM_WINDOWS
        "windows",
#elif defined(ENGINE_PLATFORM_LINUX)
        "linux",
#elif defined(ENGINE_PLATFORM_MACOS)
        "macos",
#else
        "unknown",
#endif
        env_or("RECEIPT_OS_VERSION", "unknown"),
#if defined(ENGINE_RHI_BACKEND_D3D12)
        "d3d12",
#elif defined(ENGINE_RHI_BACKEND_METAL)
        "metal",
#elif defined(ENGINE_VULKAN) && defined(ENGINE_PLATFORM_MACOS)
        "vulkan-moltenvk",
#elif defined(ENGINE_VULKAN)
        "vulkan",
#else
        "opengl",
#endif
        info.device_name, info.driver_version,
        env_or("RECEIPT_CPU", "unknown"), env_or("RECEIPT_RAM", "unknown"),
        env_or("GIT_COMMIT", "unknown"), env_or("RECEIPT_BUILD_CONFIG", "unknown"),
        fps_avg, p99_ms > 0.0 ? 1000.0 / p99_ms : 0.0, avg_ms, p99_ms,
        env_or("RECEIPT_RUNNER", "local"));
    fclose(out);
    rhi_device_destroy(dev);
    platform_destroy(platform);
    LOG_INFO("receipt written: %s (fps_avg=%.1f frame_ms_p99=%.3f)",
             argv[1], fps_avg, p99_ms);
    return 0;
}
