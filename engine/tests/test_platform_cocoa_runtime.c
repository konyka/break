#include "test_framework.h"

#include "platform/platform.h"

#ifdef __OBJC__
#import <Cocoa/Cocoa.h>
#endif

TEST(cocoa_window_create_poll_and_destroy)
{
    const PlatformConfig config = {.width = 320, .height = 240, .title = "Break Cocoa runtime"};
    Platform *platform = platform_create(&config);
    PlatformMediaContext media;
    u32 width = 0;
    u32 height = 0;

    if (platform == NULL) {
        printf("  FAIL: platform_create returned NULL\n");
        g_test_fail++;
        return;
    }
    if (platform_get_media_generation(platform) == 0u) {
        printf("  FAIL: Cocoa media generation was not initialized\n");
        g_test_fail++;
    }
    if (platform_window_native(platform) == NULL ||
        platform_surface_native(platform) == NULL) {
        printf("  FAIL: Cocoa native handles are incomplete\n");
        g_test_fail++;
    }
    if (platform_poll(platform) != PLATFORM_EVENT_NONE) {
        printf("  FAIL: Cocoa initial poll reported an unexpected event\n");
        g_test_fail++;
    }
    platform_get_size(platform, &width, &height);
    if (width == 0 || height == 0) {
        printf("  FAIL: Cocoa native size is zero\n");
        g_test_fail++;
    }
    platform_get_drawable_size(platform, &width, &height);
    if (width == 0 || height == 0) {
        printf("  FAIL: Cocoa drawable size is zero\n");
        g_test_fail++;
    }
    if (!platform_get_media_context(platform, &media) ||
        (media.known & PLATFORM_MEDIA_KNOWN_COLOR_GAMUT) == 0) {
        printf("  FAIL: Cocoa media context is incomplete\n");
        g_test_fail++;
    }
    platform_destroy(platform);
}

TEST(cocoa_media_context_reports_system_preferences)
{
    const PlatformConfig config = {.width = 320, .height = 240, .title = "Break Cocoa media"};
    Platform *platform = platform_create(&config);
    PlatformMediaContext media;

    if (platform == NULL) {
        printf("  FAIL: platform_create returned NULL\n");
        g_test_fail++;
        return;
    }
    if (!platform_get_media_context(platform, &media)) {
        printf("  FAIL: Cocoa media query failed\n");
        g_test_fail++;
    } else {
        if ((media.known & PLATFORM_MEDIA_KNOWN_COLOR_SCHEME) == 0u) {
            printf("  FAIL: Cocoa color-scheme fact is not known\n");
            g_test_fail++;
        }
        if ((media.known & PLATFORM_MEDIA_KNOWN_REDUCED_MOTION) == 0u) {
            printf("  FAIL: Cocoa reduced-motion fact is not known\n");
            g_test_fail++;
        }
    }
    platform_destroy(platform);
}

TEST(cocoa_media_context_preserves_color_capability_levels)
{
    const PlatformConfig config = {.width = 320, .height = 240, .title = "Break Cocoa color media"};
    Platform *platform = platform_create(&config);
    PlatformMediaContext media;

    if (platform == NULL) {
        printf("  FAIL: platform_create returned NULL\n");
        g_test_fail++;
        return;
    }
    if (!platform_get_media_context(platform, &media)) {
        printf("  FAIL: Cocoa media query failed\n");
        g_test_fail++;
    } else {
        if ((media.capabilities & PLATFORM_MEDIA_CAP_COLOR_P3) != 0u &&
            (media.capabilities & PLATFORM_MEDIA_CAP_COLOR_SRGB) == 0u) {
            printf("  FAIL: Cocoa P3 capability omitted sRGB level\n");
            g_test_fail++;
        }
        if ((media.capabilities & PLATFORM_MEDIA_CAP_COLOR_REC2020) != 0u &&
            (media.capabilities & PLATFORM_MEDIA_CAP_COLOR_P3) == 0u) {
            printf("  FAIL: Cocoa Rec.2020 capability omitted P3 level\n");
            g_test_fail++;
        }
        if ((media.capabilities & PLATFORM_MEDIA_CAP_HDR) != 0u &&
            (media.known & PLATFORM_MEDIA_KNOWN_HDR) == 0u) {
            printf("  FAIL: Cocoa HDR capability is not marked known\n");
            g_test_fail++;
        }
    }
    platform_destroy(platform);
}

/* FS4 borderless fullscreen: the window covers its screen, the drawable and
 * WSI follow, and leaving restores the size. This file is compiled as
 * Objective-C on macOS (CMakeLists) so it can inspect the NSWindow itself. */
static bool cocoa_window_is_borderless_on_screen(const char *title)
{
#ifdef __OBJC__
    bool result = false;
    @autoreleasepool {
        NSString *wanted = [NSString stringWithUTF8String:title];
        for (NSWindow *window in [NSApp windows]) {
            if (![[window title] isEqualToString:wanted]) continue;
            result = [window styleMask] == NSWindowStyleMaskBorderless &&
                     [window screen] != nil &&
                     NSEqualRects([window frame], [[window screen] frame]) &&
                     [window level] > NSNormalWindowLevel;
            break;
        }
    }
    return result;
#else
    (void)title;
    return false;
#endif
}

static bool cocoa_size_matches_a_screen(Platform *platform)
{
    u32 width = 0;
    u32 height = 0;
    u32 count = platform_get_monitor_count(platform);
    platform_get_logical_size(platform, &width, &height);
    for (u32 i = 0; i < count; i++) {
        MonitorInfo monitor;
        if (platform_get_monitor_info(platform, i, &monitor) &&
            monitor.width == width && monitor.height == height)
            return true;
    }
    printf("  logical size %ux%u matches no screen\n", width, height);
    return false;
}

TEST(cocoa_borderless_fullscreen_enter_leave_restores)
{
    const PlatformConfig config = {.width = 320, .height = 240, .title = "Break Cocoa fullscreen"};
    Platform *platform = platform_create(&config);
    PlatformWsiSurface wsi;
    u32 width = 0;
    u32 height = 0;
    u32 drawable_w = 0;
    u32 drawable_h = 0;

    if (platform == NULL) {
        printf("  FAIL: platform_create returned NULL\n");
        g_test_fail++;
        return;
    }
    (void)platform_poll(platform);
    ASSERT_EQ(platform_get_window_mode(platform), PLATFORM_WINDOW_MODE_WINDOWED);
    platform_get_logical_size(platform, &width, &height);
    ASSERT_EQ(width, 320u);
    ASSERT_EQ(height, 240u);

    ASSERT_TRUE(platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN));
    ASSERT_EQ(platform_get_window_mode(platform), PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_TRUE(cocoa_window_is_borderless_on_screen(config.title));
    (void)platform_poll(platform);
    ASSERT_TRUE(cocoa_size_matches_a_screen(platform));
    platform_get_logical_size(platform, &width, &height);
    platform_get_drawable_size(platform, &drawable_w, &drawable_h);
    ASSERT_TRUE(drawable_w >= width && drawable_h >= height);
    ASSERT_TRUE(platform_wsi_surface_query(platform, &wsi));
    ASSERT_EQ(wsi.logical_width, width);
    ASSERT_EQ(wsi.logical_height, height);
    ASSERT_TRUE(platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN));
    ASSERT_EQ(platform_get_window_mode(platform), PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);

    ASSERT_TRUE(platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_WINDOWED));
    ASSERT_EQ(platform_get_window_mode(platform), PLATFORM_WINDOW_MODE_WINDOWED);
    ASSERT_FALSE(cocoa_window_is_borderless_on_screen(config.title));
    (void)platform_poll(platform);
    platform_get_logical_size(platform, &width, &height);
    ASSERT_EQ(width, 320u);
    ASSERT_EQ(height, 240u);
    ASSERT_TRUE(platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_WINDOWED));
    platform_destroy(platform);
}

TEST(cocoa_start_fullscreen_covers_screen)
{
    const PlatformConfig config = {.width = 320, .height = 240,
                                   .title = "Break Cocoa start fullscreen",
                                   .start_fullscreen = true};
    Platform *platform = platform_create(&config);
    u32 width = 0;
    u32 height = 0;

    if (platform == NULL) {
        printf("  FAIL: platform_create(start_fullscreen) returned NULL\n");
        g_test_fail++;
        return;
    }
    (void)platform_poll(platform);
    ASSERT_EQ(platform_get_window_mode(platform), PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_TRUE(cocoa_window_is_borderless_on_screen(config.title));
    ASSERT_TRUE(cocoa_size_matches_a_screen(platform));
    ASSERT_TRUE(platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_WINDOWED));
    platform_get_logical_size(platform, &width, &height);
    ASSERT_EQ(width, 320u);
    ASSERT_EQ(height, 240u);
    platform_destroy(platform);
}

TEST_MAIN_BEGIN()
    RUN_TEST(cocoa_window_create_poll_and_destroy);
    RUN_TEST(cocoa_borderless_fullscreen_enter_leave_restores);
    RUN_TEST(cocoa_start_fullscreen_covers_screen);
    RUN_TEST(cocoa_media_context_reports_system_preferences);
    RUN_TEST(cocoa_media_context_preserves_color_capability_levels);
TEST_MAIN_END()
