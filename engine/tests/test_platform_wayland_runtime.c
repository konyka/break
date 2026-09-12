#include "test_framework.h"

#include "platform/platform.h"

#include <wayland-client.h>

static void runtime_failure(const char *message)
{
    printf("  FAIL: %s\n", message);
    g_test_fail++;
}

static int wayland_runtime_available(void)
{
    struct wl_display *display = wl_display_connect(NULL);
    if (display == NULL) return 0;
    wl_display_disconnect(display);
    return 1;
}

TEST(wayland_window_create_poll_and_destroy)
{
    const PlatformConfig config = {.width = 320, .height = 240, .title = "Break Wayland runtime"};
    Platform *platform;
    PlatformMediaContext media;
    u32 width = 0;
    u32 height = 0;
    bool ok = true;

    platform = platform_create(&config);
    if (platform == NULL) {
        runtime_failure("platform_create returned NULL");
        return;
    }
    if (platform_get_media_generation(platform) == 0u) {
        runtime_failure("Wayland media generation was not initialized");
        ok = false;
    }
    if (platform_display_native(platform) == NULL ||
        platform_surface_native(platform) == NULL ||
        platform_window_native(platform) == NULL) {
        runtime_failure("Wayland native handles are incomplete");
        ok = false;
        goto cleanup;
    }

    if (platform_poll(platform) != PLATFORM_EVENT_NONE) {
        runtime_failure("Wayland initial poll reported an unexpected event");
        ok = false;
    }
    platform_get_size(platform, &width, &height);
    if (width == 0 || height == 0) {
        runtime_failure("Wayland native size is zero");
        ok = false;
    }
    platform_get_logical_size(platform, &width, &height);
    if (width == 0 || height == 0) {
        runtime_failure("Wayland logical size is zero");
        ok = false;
    }
    platform_get_drawable_size(platform, &width, &height);
    if (width == 0 || height == 0) {
        runtime_failure("Wayland drawable size is zero");
        ok = false;
    }
    if (!platform_get_media_context(platform, &media) ||
        (media.known & PLATFORM_MEDIA_KNOWN_COLOR_GAMUT) == 0) {
        runtime_failure("Wayland media context is incomplete");
        ok = false;
    }
    if ((media.capabilities & PLATFORM_MEDIA_CAP_POINTER_COARSE) != 0u &&
        (media.capabilities & PLATFORM_MEDIA_CAP_ANY_POINTER_COARSE) == 0u) {
        runtime_failure("Wayland coarse primary pointer lacks any-pointer coarse");
        ok = false;
    }

cleanup:
    platform_destroy(platform);
    (void)ok;
}

TEST(wayland_media_snapshot_is_stable_between_queries)
{
    const PlatformConfig config = {.width = 320, .height = 240, .title = "Break Wayland media cache"};
    Platform *platform = platform_create(&config);
    PlatformMediaContext first;
    PlatformMediaContext second;

    if (platform == NULL) {
        runtime_failure("Wayland platform_create returned NULL");
        return;
    }
    if (!platform_get_media_context(platform, &first) ||
        !platform_get_media_context(platform, &second)) {
        runtime_failure("Wayland media snapshot query failed");
    } else if (first.screen != second.screen ||
               first.prefers_dark != second.prefers_dark ||
               first.prefers_reduced_motion != second.prefers_reduced_motion ||
               first.capabilities != second.capabilities ||
               first.known != second.known) {
        runtime_failure("Wayland media snapshot changed without an event");
    }
    platform_destroy(platform);
}

int main(void)
{
    if (!wayland_runtime_available()) {
        printf("SKIP: no reachable Wayland compositor\n");
        return 77;
    }
    printf("=== Running Tests ===\n");
    RUN_TEST(wayland_window_create_poll_and_destroy);
    RUN_TEST(wayland_media_snapshot_is_stable_between_queries);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
