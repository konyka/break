#include "test_framework.h"

#include "platform/platform.h"

#include <X11/Xlib.h>
#ifdef ENGINE_X11_XINPUT2
#include <X11/extensions/XInput2.h>
#endif
#include <time.h>

static void runtime_failure(const char *message)
{
    printf("  FAIL: %s\n", message);
    g_test_fail++;
}

static int x11_runtime_available(void)
{
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) return 0;
    XCloseDisplay(display);
    return 1;
}

TEST(x11_window_create_resize_and_destroy)
{
    const PlatformConfig config = {320, 240, "Break X11 runtime"};
    Platform *platform;
    Display *display;
    Window window;
    u32 width = 0;
    u32 height = 0;
    PlatformMediaContext media;
    bool resized = false;
    bool ok = true;

    platform = platform_create(&config);
    if (platform == NULL) {
        runtime_failure("platform_create returned NULL");
        return;
    }
    display = (Display *)platform_display_native(platform);
    window = (Window)(uintptr_t)platform_window_native(platform);
    if (display == NULL) {
        runtime_failure("platform_display_native returned NULL");
        ok = false;
        goto cleanup;
    }
    if (platform_get_media_generation(platform) == 0u) {
        runtime_failure("X11 media generation was not initialized");
        ok = false;
    }
    if (window == 0 || platform_surface_native(platform) == NULL) {
        runtime_failure("platform native window handles are incomplete");
        ok = false;
        goto cleanup;
    }

    /* Drain map/initial configure notifications before testing resize. */
    (void)platform_poll(platform);
    XResizeWindow(display, window, 517, 293);
    XSync(display, False);
    for (int attempt = 0; attempt < 100; attempt++) {
        (void)platform_poll(platform);
        XSync(display, False);
        platform_get_size(platform, &width, &height);
        if (width == 517 && height == 293) {
            resized = true;
            break;
        }
        {
            const struct timespec delay = {0, 1000000L};
            nanosleep(&delay, NULL);
        }
    }
    if (!resized) {
        runtime_failure("X11 ConfigureNotify resize was not observed");
        ok = false;
    }
    if (!platform_get_media_context(platform, &media) ||
        (media.known & PLATFORM_MEDIA_KNOWN_COLOR_GAMUT) == 0) {
        runtime_failure("X11 media context is incomplete");
        ok = false;
    }
    if ((media.capabilities & PLATFORM_MEDIA_CAP_COLOR_P3) != 0u &&
        (media.known & PLATFORM_MEDIA_KNOWN_COLOR_GAMUT) == 0u) {
        runtime_failure("X11 P3 capability is not marked known");
        ok = false;
    }
    if ((media.capabilities & PLATFORM_MEDIA_CAP_COLOR_REC2020) != 0u &&
        (media.capabilities & PLATFORM_MEDIA_CAP_COLOR_P3) == 0u) {
        runtime_failure("X11 Rec.2020 capability lacks P3 implication");
        ok = false;
    }
    if ((media.capabilities & PLATFORM_MEDIA_CAP_HDR) != 0u &&
        (media.known & PLATFORM_MEDIA_KNOWN_HDR) == 0u) {
        runtime_failure("X11 HDR capability is not marked known");
        ok = false;
    }
#ifdef ENGINE_X11_XINPUT2
    if ((media.capabilities & PLATFORM_MEDIA_CAP_HOVER) != 0u &&
        (media.capabilities & PLATFORM_MEDIA_CAP_POINTER_FINE) == 0u) {
        runtime_failure("X11 hover capability lacks a fine primary pointer");
        ok = false;
    }
    if ((media.capabilities & PLATFORM_MEDIA_CAP_POINTER_COARSE) != 0u &&
        (media.capabilities & PLATFORM_MEDIA_CAP_ANY_POINTER_COARSE) == 0u) {
        runtime_failure("X11 coarse primary pointer lacks any-pointer coarse");
        ok = false;
    }
#endif
    if (platform_get_monitor_count(platform) == 0) {
        runtime_failure("X11 monitor enumeration returned no monitor");
        ok = false;
    }

cleanup:
    platform_destroy(platform);
    (void)ok;
}

int main(void)
{
    if (!x11_runtime_available()) {
        printf("SKIP: no reachable X11 display\n");
        return 77;
    }
    printf("=== Running Tests ===\n");
    RUN_TEST(x11_window_create_resize_and_destroy);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
