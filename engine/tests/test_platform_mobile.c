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
        320, 240, "Break mobile", &window, &display, false, false, false, 0.0f
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

    ASSERT_EQ(platform_get_window_mode(platform),
              PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_TRUE(platform_set_window_mode(platform,
                                         PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN));
    ASSERT_FALSE(platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_WINDOWED));
    ASSERT_FALSE(platform_set_window_mode(platform, (PlatformWindowMode)7));
    platform_toggle_fullscreen(platform);
    ASSERT_EQ(platform_get_window_mode(platform),
              PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    /* The host owns the surface: there is never a title bar to show. */
    ASSERT_FALSE(platform_get_window_decorated(platform));
    ASSERT_FALSE(platform_window_title_bar_visible(platform));
    ASSERT_TRUE(platform_set_window_decorated(platform, false));
    ASSERT_FALSE(platform_set_window_decorated(platform, true));
    ASSERT_FALSE(platform_get_window_decorated(platform));
    platform_get_size(platform, &width, &height);
    ASSERT_EQ(width, 320u);
    ASSERT_EQ(height, 240u);
    platform_mouse_capture(platform, true);
    platform_mouse_set_visible(platform, false);
    platform_mouse_set_relative(platform, true);
    platform_ime_set_enabled(platform, true);
    platform_ime_set_surrounding(platform, "text", 2, 2);
    platform_ime_set_spot(platform, 4, 8);
    platform_destroy(platform);
}

TEST(mobile_platform_tracks_host_viewport_and_scale)
{
    int window;
    u32 width = 0u, height = 0u;
    PlatformWsiSurface wsi;
    const PlatformConfig config = {
        .width = 640, .height = 480, .title = "Retina",
        .native_window = &window, .native_content_scale = 2.0f,
    };
    PlatformConfig invalid = config;
    Platform *platform = platform_create(&config);

    ASSERT_NEQ(platform, NULL);
    platform_get_logical_size(platform, &width, &height);
    ASSERT_EQ(width, 320u);
    ASSERT_EQ(height, 240u);
    platform_get_drawable_size(platform, &width, &height);
    ASSERT_EQ(width, 640u);
    ASSERT_EQ(height, 480u);
    ASSERT_FLOAT_EQ(platform_get_dpi(platform), 192.0f, 0.001f);
    ASSERT_FLOAT_EQ(platform_get_content_scale(platform), 2.0f, 0.001f);
    ASSERT_EQ(platform_get_scale_factor(platform), 2);
    ASSERT_TRUE(platform_wsi_surface_query(platform, &wsi));
    ASSERT_EQ(wsi.logical_width, 320u);
    ASSERT_EQ(wsi.drawable_width, 640u);

    ASSERT_TRUE(platform_mobile_resize(platform, 400, 300, 800, 600, 2.0f));
    platform_get_size(platform, &width, &height);
    ASSERT_EQ(width, 400u);
    ASSERT_EQ(height, 300u);
    platform_get_drawable_size(platform, &width, &height);
    ASSERT_EQ(width, 800u);
    ASSERT_EQ(height, 600u);
    ASSERT_TRUE(platform_wsi_surface_query(platform, &wsi));
    ASSERT_EQ(wsi.state, PLATFORM_WSI_RESIZED);
    ASSERT_EQ(wsi.logical_height, 300u);
    ASSERT_EQ(wsi.drawable_height, 600u);

    ASSERT_FALSE(platform_mobile_resize(NULL, 400, 300, 800, 600, 2.0f));
    ASSERT_FALSE(platform_mobile_resize(platform, 0, 300, 800, 600, 2.0f));
    ASSERT_FALSE(platform_mobile_resize(platform, 400, 300, 800, 600, NAN));
    ASSERT_FALSE(platform_mobile_resize(platform, 400, 300, 800, 600, -1.0f));
    platform_get_drawable_size(platform, &width, &height);
    ASSERT_EQ(width, 800u);
    ASSERT_EQ(height, 600u);

    platform_mobile_notify_suspend(platform);
    ASSERT_FALSE(platform_mobile_resize(platform, 200, 150, 400, 300, 2.0f));
    ASSERT_TRUE(platform_wsi_surface_query(platform, &wsi));
    ASSERT_FALSE(platform_wsi_frame_allowed(&wsi));
    platform_mobile_notify_resume(platform);
    ASSERT_TRUE(platform_mobile_resize(platform, 200, 150, 400, 300, 2.0f));
    ASSERT_TRUE(platform_wsi_surface_query(platform, &wsi));
    ASSERT_TRUE(platform_wsi_frame_allowed(&wsi));
    platform_destroy(platform);

    invalid.native_content_scale = NAN;
    ASSERT_EQ(platform_create(&invalid), NULL);
    invalid.native_content_scale = -1.0f;
    ASSERT_EQ(platform_create(&invalid), NULL);
}

TEST_MAIN_BEGIN()
    RUN_TEST(mobile_platform_requires_host_window);
    RUN_TEST(mobile_platform_exposes_host_state);
    RUN_TEST(mobile_platform_tracks_host_viewport_and_scale);
TEST_MAIN_END()
