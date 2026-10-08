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
    const PlatformConfig config = {.width = 320, .height = 240, .title = "Break GLX damage runtime"};
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

TEST(x11_gl_f16_cubemap_roundtrip)
{
    /* R696: the R624/R625 color-cube byte contract on the GL backend —
     * RGBA16F faces upload natively at create and read back face-major
     * mip 0 byte-exactly (8B/px f16 quads). */
    const PlatformConfig config = {.width = 320, .height = 240, .title = "Break GL f16 cube runtime"};
    Platform *platform = platform_create(&config);
    RHIDevice *device = NULL;
    RHICubemapDesc desc;
    RHICubemap cm;
    /* 4x4 RGBA f16 quads per face; the face index encodes into the R
     * channel's f16 bit pattern so faces never alias. */
    static u16 faces[6][4u * 4u * 4u];
    static u16 readback[6][4u * 4u * 4u];
    u32 drawable_width = 0u, drawable_height = 0u;
    int f, i;

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
    for (f = 0; f < 6; ++f) {
        for (i = 0; i < 4 * 4 * 4; i += 4) {
            faces[f][i + 0u] = (u16)(0x3C00u + (u16)f); /* R: 1.0h + face */
            faces[f][i + 1u] = 0x3800u;                 /* G: 0.5h */
            faces[f][i + 2u] = 0x4000u;                 /* B: 2.0h */
            faces[f][i + 3u] = 0x3C00u;                 /* A: 1.0h */
        }
    }
    memset(&desc, 0, sizeof(desc));
    desc.size = 4u;
    for (f = 0; f < 6; ++f) {
        desc.faces[f] = faces[f];
    }
    desc.format = RHI_FORMAT_R16G16B16A16_SFLOAT;
    desc.mip_levels = 1u;
    cm = rhi_cubemap_create(device, &desc);
    if (!rhi_handle_valid(cm)) {
        printf("  FAIL: GL f16 cubemap create failed\n");
        g_test_fail++;
        rhi_device_destroy(device);
        platform_destroy(platform);
        return;
    }
    if (!rhi_texture_read_pixels(device, cm, readback, sizeof(readback))) {
        printf("  FAIL: GL f16 cubemap readback failed\n");
        g_test_fail++;
    } else {
        for (f = 0; f < 6; ++f) {
            if (memcmp(readback[f], faces[f], sizeof(faces[f])) != 0) {
                printf("  FAIL: GL f16 cubemap face %d bytes differ\n", f);
                g_test_fail++;
                break;
            }
        }
    }
    rhi_cubemap_destroy(device, cm);
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
    RUN_TEST(x11_gl_f16_cubemap_roundtrip);
    if (g_runtime_skip && g_test_fail == 0) {
        printf("SKIP: OpenGL/GLX runtime is unavailable\n");
        return 77;
    }
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
