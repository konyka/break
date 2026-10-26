/* Graphics: the runtime chain on a real window (docs/design/rhi_runtime_backend.md §6).
 * Multi-backend build only. argv[1] is the backend the chain must pick; the
 * ctest registration sets the environment for each case:
 *   default  (no env)                  -> vulkan
 *   fallback BREAK_RHI_FAIL_VULKAN=1   -> opengl (forced fallback)
 *   opengl   BREAK_RHI_BACKEND=opengl  -> opengl (explicit override)
 * Each mode clears to a known colour, reads the frame back through the
 * active backend, checks the pixel, and tears down cleanly. Exit 77 = no
 * display / no device (skip). */
#include <platform/platform.h>
#include <rhi/rhi.h>
#include <rhi/rhi_runtime.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int main(int argc, char **argv) {
    const char *want = argc > 1 ? argv[1] : "vulkan";
    const char *mode = argc > 2 ? argv[2] : want;
    PlatformConfig cfg;
    Platform *platform;
    RHIDevice *dev;
    u32 w = 0u, h = 0u;
    u8 *shot;
    bool captured = false;
    int rc = 1;

    memset(&cfg, 0, sizeof(cfg));
    cfg.width = 160u;
    cfg.height = 120u;
    cfg.title = "rhi runtime fallback";
    platform = platform_create(&cfg);
    if (platform == NULL) return 77;
    platform_get_drawable_size(platform, &w, &h);

    if (strcmp(rhi_runtime_active_backend(), "none") != 0) {
        fprintf(stderr, "FAIL: a backend was active before any device\n");
        platform_destroy(platform);
        return 1;
    }
    dev = rhi_device_create_compiled(platform_window_native(platform),
                                     platform_surface_native(platform),
                                     platform_display_native(platform), w, h);
    if (dev == NULL) {
        fprintf(stderr, "SKIP: no %s device on this host\n", want);
        platform_destroy(platform);
        return 77;
    }
    if (strcmp(rhi_runtime_active_backend(), want) != 0) {
        fprintf(stderr, "FAIL: mode %s selected %s, want %s\n", mode,
                rhi_runtime_active_backend(), want);
        goto out;
    }

    shot = malloc((size_t)w * h * 4u);
    if (shot == NULL) goto out;
    for (int frame = 0; frame < 3 && !captured; frame++) {
        RHICmdBuffer *cmd;
        platform_poll(platform);
        cmd = rhi_frame_begin(dev);
        if (cmd == NULL) continue;
        rhi_cmd_begin_render_pass(cmd);
        rhi_cmd_clear_color(cmd, 1.0f, 0.0f, 1.0f, 1.0f); /* magenta */
        rhi_cmd_end_render_pass(cmd);
        rhi_frame_end(dev);
        if (frame == 2)
            captured = rhi_screenshot(dev, 0u, 0u, w, h, shot, (usize)w * h * 4u);
        rhi_present(dev);
    }
    if (!captured) {
        fprintf(stderr, "FAIL: %s readback failed\n", want);
        free(shot);
        goto out;
    }
    {
        const u8 *p = &shot[((size_t)(h / 2u) * w + w / 2u) * 4u];
        /* Clear colour is magenta; VK writes through an sRGB swapchain, GL
         * raw, and both encode 1.0/0.0 exactly, so the check is exact. */
        if (p[0] < 250u || p[1] > 5u || p[2] < 250u) {
            fprintf(stderr, "FAIL: %s centre pixel %u,%u,%u, want magenta\n",
                    want, p[0], p[1], p[2]);
            free(shot);
            goto out;
        }
    }
    free(shot);
    printf("OK: mode %s rendered and read back on %s\n", mode, want);
    rc = 0;
out:
    rhi_device_destroy(dev);
    platform_destroy(platform);
    return rc;
}
