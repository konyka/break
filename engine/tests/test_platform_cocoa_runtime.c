#include "test_framework.h"

#include "platform/platform.h"

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

TEST_MAIN_BEGIN()
    RUN_TEST(cocoa_window_create_poll_and_destroy);
    RUN_TEST(cocoa_media_context_reports_system_preferences);
    RUN_TEST(cocoa_media_context_preserves_color_capability_levels);
TEST_MAIN_END()
