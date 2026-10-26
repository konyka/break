#include "test_framework.h"

#include "platform/platform.h"

#include <wayland-client.h>
#include <time.h>

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

/* ---- Borderless fullscreen (FS4) ---- */

static void wayland_sleep_ms(long ms)
{
    const struct timespec delay = {0, ms * 1000000L};
    nanosleep(&delay, NULL);
}

/* Polls (bounded, about 3 s) until the configure-confirmed mode is `mode`. */
static bool wayland_wait_for_mode(Platform *platform, PlatformWindowMode mode)
{
    for (int attempt = 0; attempt < 3000; attempt++) {
        (void)platform_poll(platform);
        if (platform_get_window_mode(platform) == mode) return true;
        wayland_sleep_ms(1);
    }
    return false;
}

static bool wayland_size_matches_any_output(Platform *platform)
{
    u32 width = 0;
    u32 height = 0;
    u32 count = platform_get_monitor_count(platform);
    platform_get_logical_size(platform, &width, &height);
    for (u32 i = 0; i < count; i++) {
        MonitorInfo monitor;
        u32 scale;
        if (!platform_get_monitor_info(platform, i, &monitor)) continue;
        scale = monitor.scale > 0 ? (u32)monitor.scale : 1u;
        if (width == monitor.width / scale && height == monitor.height / scale)
            return true;
    }
    return false;
}

/* The mode is whatever the compositor's configure states say. A compositor
 * that honours fullscreen (weston, also headless) must size the window to
 * the output; one that ignores the request must leave the mode WINDOWED
 * instead of pretending (the FS2 interim confirmed at once). */
TEST(wayland_borderless_fullscreen_follows_configure_states)
{
    const PlatformConfig config = {.width = 320, .height = 240, .title = "Break Wayland fullscreen"};
    Platform *platform = platform_create(&config);
    u32 width = 0;
    u32 height = 0;
    bool entered;

    if (platform == NULL) {
        runtime_failure("Wayland platform_create returned NULL");
        return;
    }
    (void)platform_poll(platform);
    if (platform_get_window_mode(platform) != PLATFORM_WINDOW_MODE_WINDOWED)
        runtime_failure("new Wayland window is not WINDOWED");
    if (!platform_needs_client_decoration(platform))
        runtime_failure("windowed Wayland window must draw client decorations");

    if (!platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN))
        runtime_failure("platform_set_window_mode(BORDERLESS) returned false");
    entered = wayland_wait_for_mode(platform, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    platform_get_logical_size(platform, &width, &height);
    printf("  compositor %s fullscreen; logical size %ux%u\n",
           entered ? "honoured" : "did not honour", width, height);
    if (entered) {
        if (!wayland_size_matches_any_output(platform))
            runtime_failure("fullscreen size does not match any output");
        if (platform_needs_client_decoration(platform))
            runtime_failure("fullscreen window must not draw client decorations");
        if (!platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN))
            runtime_failure("repeated fullscreen request returned false");
    } else if (platform_get_window_mode(platform) != PLATFORM_WINDOW_MODE_WINDOWED) {
        runtime_failure("unconfirmed fullscreen changed the reported mode");
    }

    if (!platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_WINDOWED))
        runtime_failure("platform_set_window_mode(WINDOWED) returned false");
    if (!wayland_wait_for_mode(platform, PLATFORM_WINDOW_MODE_WINDOWED))
        runtime_failure("leaving fullscreen was not confirmed");
    if (entered) {
        /* xdg-shell: a 0x0 configure after unset_fullscreen lets the client
         * pick its size, so the backend must return to the saved window. */
        for (int attempt = 0; attempt < 3000; attempt++) {
            (void)platform_poll(platform);
            platform_get_logical_size(platform, &width, &height);
            if (width == 320u && height == 240u) break;
            wayland_sleep_ms(1);
        }
        if (width != 320u || height != 240u) {
            printf("  restored size %ux%u\n", width, height);
            runtime_failure("leaving fullscreen did not restore the windowed size");
        }
    }
    if (!platform_needs_client_decoration(platform))
        runtime_failure("windowed Wayland window lost client decorations");
    platform_destroy(platform);
}

TEST(wayland_start_fullscreen_is_confirmed_by_first_configure)
{
    const PlatformConfig config = {.width = 320, .height = 240,
                                   .title = "Break Wayland start fullscreen",
                                   .start_fullscreen = true};
    Platform *platform = platform_create(&config);
    bool entered;

    if (platform == NULL) {
        runtime_failure("Wayland platform_create(start_fullscreen) returned NULL");
        return;
    }
    entered = wayland_wait_for_mode(platform, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    printf("  start_fullscreen %s by the compositor\n",
           entered ? "honoured" : "not honoured");
    if (entered && !wayland_size_matches_any_output(platform))
        runtime_failure("start_fullscreen size does not match any output");
    if (!platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_WINDOWED))
        runtime_failure("platform_set_window_mode(WINDOWED) returned false");
    if (!wayland_wait_for_mode(platform, PLATFORM_WINDOW_MODE_WINDOWED))
        runtime_failure("leaving start_fullscreen was not confirmed");
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
    RUN_TEST(wayland_borderless_fullscreen_follows_configure_states);
    RUN_TEST(wayland_start_fullscreen_is_confirmed_by_first_configure);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
