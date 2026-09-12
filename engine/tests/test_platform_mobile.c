#include "test_framework.h"

#include "platform/platform.h"

TEST(mobile_platform_requires_host_window)
{
    const PlatformConfig config = {.width = 320, .height = 240, .title = "Break mobile"};

    ASSERT_EQ(platform_create(&config), NULL);
}

TEST(mobile_platform_exposes_host_state)
{
    int window;
    int display;
    const PlatformConfig config = {
        320, 240, "Break mobile", &window, &display
    };
    Platform *platform = platform_create(&config);
    u32 width = 0u;
    u32 height = 0u;
    PlatformMediaContext media;
    char *clipboard = (char *)1;

    ASSERT_NEQ(platform, NULL);
    ASSERT_EQ(platform_window_native(platform), &window);
    ASSERT_EQ(platform_surface_native(platform), &window);
    ASSERT_EQ(platform_display_native(platform), &display);
    ASSERT_NEQ(platform_input(platform), NULL);

    platform_get_size(platform, &width, &height);
    ASSERT_EQ(width, 320u);
    ASSERT_EQ(height, 240u);
    platform_get_logical_size(platform, &width, &height);
    ASSERT_EQ(width, 320u);
    ASSERT_EQ(height, 240u);
    platform_get_drawable_size(platform, &width, &height);
    ASSERT_EQ(width, 320u);
    ASSERT_EQ(height, 240u);
    ASSERT_FLOAT_EQ(platform_get_dpi(platform), 96.0f, 0.001f);
    ASSERT_FLOAT_EQ(platform_get_content_scale(platform), 1.0f, 0.001f);
    ASSERT_FLOAT_EQ(platform_get_input_scale(platform), 1.0f, 0.001f);
    ASSERT_EQ(platform_get_scale_factor(platform), 1);

    ASSERT_EQ(platform_poll(platform), PLATFORM_EVENT_NONE);
    ASSERT_EQ(platform_input(platform)->frame_number, 1u);
    ASSERT_FALSE(platform_cursor_set(platform, PLATFORM_CURSOR_ARROW));
    ASSERT_FALSE(platform_window_begin_move(platform));
    ASSERT_FALSE(platform_needs_client_decoration(platform));
    ASSERT_FALSE(platform_ime_is_enabled(platform));
    ASSERT_EQ(platform_poll_text(platform, NULL, 0u), 0u);
    ASSERT_FALSE(platform_clipboard_set_text(platform, "text"));
    ASSERT_FALSE(platform_clipboard_get_text(platform, NULL, 0u));
    ASSERT_EQ(platform_clipboard_get_text_alloc(platform, &clipboard),
              PLATFORM_CLIPBOARD_EMPTY);
    ASSERT_EQ(clipboard, NULL);
    ASSERT_TRUE(platform_get_media_context(platform, &media));
    ASSERT_TRUE(media.screen);
    ASSERT_EQ(media.capabilities, PLATFORM_MEDIA_CAP_POINTER_COARSE |
                                  PLATFORM_MEDIA_CAP_ANY_POINTER_COARSE |
                                  PLATFORM_MEDIA_CAP_COLOR_SRGB);
    ASSERT_EQ(media.known, PLATFORM_MEDIA_KNOWN_POINTER |
                         PLATFORM_MEDIA_KNOWN_ANY_POINTER |
                         PLATFORM_MEDIA_KNOWN_COLOR_GAMUT);
    ASSERT_EQ(platform_get_media_generation(platform), 1u);
    ASSERT_EQ(platform_get_monitor_count(platform), 0u);

    platform_toggle_fullscreen(platform);
    platform_mouse_capture(platform, true);
    platform_mouse_set_visible(platform, false);
    platform_mouse_set_relative(platform, true);
    platform_ime_set_enabled(platform, true);
    platform_ime_set_surrounding(platform, "text", 2, 2);
    platform_ime_set_spot(platform, 4, 8);
    platform_destroy(platform);
}

TEST_MAIN_BEGIN()
    RUN_TEST(mobile_platform_requires_host_window);
    RUN_TEST(mobile_platform_exposes_host_state);
TEST_MAIN_END()
