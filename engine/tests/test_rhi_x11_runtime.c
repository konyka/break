#include "test_framework.h"

#include "platform/platform.h"
#include "rhi/rhi.h"

#include <X11/Xlib.h>

static bool g_runtime_skip;

static bool x11_runtime_available(void)
{
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) return false;
    XCloseDisplay(display);
    return true;
}

TEST(x11_glx_damage_frame_lifecycle)
{
    const PlatformConfig config = {320, 240, "Break GLX damage runtime"};
    Platform *platform = platform_create(&config);
    RHIDevice *device = NULL;
    RHICapabilities capabilities;
    RHIPresentRect damage = {0, 0, 32u, 24u};
    u32 drawable_width = 0u;
    u32 drawable_height = 0u;
    u32 frame;

    if (platform == NULL) {
        printf("  FAIL: platform_create returned NULL\n");
        g_test_fail++;
        return;
    }
    platform_get_drawable_size(platform, &drawable_width, &drawable_height);
    device = rhi_device_create(RHI_BACKEND_OPENGL,
                                platform_window_native(platform),
                                platform_display_native(platform),
                                drawable_width, drawable_height);
    if (device == NULL) {
        g_runtime_skip = true;
        platform_destroy(platform);
        return;
    }
    rhi_set_vsync(device, false);
    if (!rhi_device_get_capabilities(device, &capabilities)) {
        printf("  FAIL: GLX capabilities query failed\n");
        g_test_fail++;
    } else {
        if (capabilities.present_target_preserved &&
            (!capabilities.present_damage_supported ||
             !capabilities.present_buffer_age_supported)) {
            printf("  FAIL: GLX retained-present capability is incomplete\n");
            g_test_fail++;
        }
        for (frame = 0u; frame < 3u; ++frame) {
            RHIPresentRect effective[RHI_MAX_PRESENT_DAMAGE_RECTS];
            RHICmdBuffer *cmd;
            u32 effective_count = 0u;
            bool partial = false;
            cmd = rhi_frame_begin_damage(device, &damage, 1u, &partial);
            if (cmd == NULL) {
                printf("  FAIL: GLX damage frame begin failed\n");
                g_test_fail++;
                break;
            }
            if (!rhi_frame_get_damage(device, effective,
                                      RHI_MAX_PRESENT_DAMAGE_RECTS,
                                      &effective_count) ||
                effective_count == 0u) {
                printf("  FAIL: GLX effective damage was empty\n");
                g_test_fail++;
            }
            (void)partial;
            rhi_frame_end(device);
            rhi_present(device);
        }
    }
    rhi_device_destroy(device);
    platform_destroy(platform);
}

int main(void)
{
    if (!x11_runtime_available()) {
        printf("SKIP: no reachable X11 display\n");
        return 77;
    }
    printf("=== Running Tests ===\n");
    RUN_TEST(x11_glx_damage_frame_lifecycle);
    if (g_runtime_skip && g_test_fail == 0) {
        printf("SKIP: OpenGL/GLX runtime is unavailable\n");
        return 77;
    }
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
