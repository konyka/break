#include "test_framework.h"

#include "platform/platform.h"

TEST(null_platform_queries_are_safe)
{
    u32 width = 123u;
    u32 height = 456u;
    PlatformMediaContext media = {true, true, true, UINT32_MAX, UINT32_MAX};
    MonitorInfo monitor;
    char text[8] = "keep";
    char *allocated = (char *)1;

    ASSERT_EQ(platform_poll(NULL), PLATFORM_EVENT_QUIT);
    ASSERT_EQ(platform_input(NULL), NULL);
    ASSERT_EQ(platform_window_native(NULL), NULL);
    ASSERT_EQ(platform_display_native(NULL), NULL);
    ASSERT_EQ(platform_surface_native(NULL), NULL);

    platform_get_size(NULL, &width, &height);
    ASSERT_EQ(width, 0u);
    ASSERT_EQ(height, 0u);
    width = 123u;
    height = 456u;
    platform_get_logical_size(NULL, &width, &height);
    ASSERT_EQ(width, 0u);
    ASSERT_EQ(height, 0u);
    width = 123u;
    height = 456u;
    platform_get_drawable_size(NULL, &width, &height);
    ASSERT_EQ(width, 0u);
    ASSERT_EQ(height, 0u);

    ASSERT_FLOAT_EQ(platform_get_dpi(NULL), 96.0f, 0.001f);
    ASSERT_FLOAT_EQ(platform_get_content_scale(NULL), 1.0f, 0.001f);
    ASSERT_FLOAT_EQ(platform_get_input_scale(NULL), 1.0f, 0.001f);
    ASSERT_EQ(platform_get_scale_factor(NULL), 1);
    ASSERT_EQ(platform_get_media_generation(NULL), 0u);

    ASSERT_FALSE(platform_get_media_context(NULL, &media));
    ASSERT_FALSE(media.screen);
    ASSERT_FALSE(media.prefers_dark);
    ASSERT_FALSE(media.prefers_reduced_motion);
    ASSERT_EQ(media.capabilities, 0u);
    ASSERT_EQ(media.known, 0u);
    ASSERT_EQ(platform_get_monitor_count(NULL), 0u);
    ASSERT_FALSE(platform_get_monitor_info(NULL, 0, &monitor));

    ASSERT_FALSE(platform_cursor_set(NULL, PLATFORM_CURSOR_ARROW));
    ASSERT_FALSE(platform_window_begin_move(NULL));
    (void)platform_needs_client_decoration(NULL);
    platform_toggle_fullscreen(NULL);
    platform_mouse_capture(NULL, true);
    platform_mouse_set_visible(NULL, false);
    platform_mouse_set_relative(NULL, true);
    platform_ime_set_enabled(NULL, true);
    platform_ime_set_surrounding(NULL, text, 1, 1);
    platform_ime_set_spot(NULL, 1, 1);
    ASSERT_FALSE(platform_ime_is_enabled(NULL));
    ASSERT_EQ(platform_poll_text(NULL, NULL, 0), 0u);
    ASSERT_FALSE(platform_clipboard_set_text(NULL, text));
    ASSERT_FALSE(platform_clipboard_get_text(NULL, text, sizeof(text)));
    ASSERT_EQ(platform_clipboard_get_text_alloc(NULL, &allocated),
              PLATFORM_CLIPBOARD_EMPTY);
    ASSERT_EQ(allocated, NULL);
}

TEST_MAIN_BEGIN()
    RUN_TEST(null_platform_queries_are_safe);
TEST_MAIN_END()
