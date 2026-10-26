#include "test_framework.h"
#include "platform/window_mode.h"

static PlatformWindowRect rect(i32 x, i32 y, u32 w, u32 h)
{
    PlatformWindowRect r;
    r.x = x; r.y = y; r.width = w; r.height = h;
    return r;
}

TEST(window_mode_starts_windowed_and_requests_are_idempotent)
{
    PlatformWindowModeState s;
    platform_window_mode_init(&s, PLATFORM_WINDOW_MODE_WINDOWED);
    ASSERT_EQ(s.current, PLATFORM_WINDOW_MODE_WINDOWED);
    ASSERT_FALSE(s.pending);
    ASSERT_EQ(platform_window_mode_request(&s, PLATFORM_WINDOW_MODE_WINDOWED),
              PLATFORM_WINDOW_MODE_ACTION_NONE);
    ASSERT_EQ(platform_window_mode_request(&s, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN),
              PLATFORM_WINDOW_MODE_ACTION_ENTER);
    ASSERT_TRUE(s.pending);
    /* Same request again while the platform has not confirmed: nothing new. */
    ASSERT_EQ(platform_window_mode_request(&s, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN),
              PLATFORM_WINDOW_MODE_ACTION_NONE);
    platform_window_mode_confirm(&s, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_EQ(s.current, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_FALSE(s.pending);
    ASSERT_EQ(platform_window_mode_request(&s, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN),
              PLATFORM_WINDOW_MODE_ACTION_NONE);
    ASSERT_EQ(platform_window_mode_request(&s, PLATFORM_WINDOW_MODE_WINDOWED),
              PLATFORM_WINDOW_MODE_ACTION_LEAVE);
}

TEST(window_mode_rejects_invalid_arguments)
{
    PlatformWindowModeState s;
    platform_window_mode_init(&s, PLATFORM_WINDOW_MODE_WINDOWED);
    ASSERT_EQ(platform_window_mode_request(NULL, PLATFORM_WINDOW_MODE_WINDOWED),
              PLATFORM_WINDOW_MODE_ACTION_NONE);
    ASSERT_EQ(platform_window_mode_request(&s, (PlatformWindowMode)7),
              PLATFORM_WINDOW_MODE_ACTION_NONE);
    ASSERT_FALSE(s.pending);
    platform_window_mode_confirm(NULL, PLATFORM_WINDOW_MODE_WINDOWED);
    platform_window_mode_confirm(&s, (PlatformWindowMode)7);
    ASSERT_EQ(s.current, PLATFORM_WINDOW_MODE_WINDOWED);
    ASSERT_FALSE(platform_window_mode_restore_rect(NULL, NULL));
    ASSERT_FALSE(platform_window_mode_valid((PlatformWindowMode)7));
    ASSERT_TRUE(platform_window_mode_valid(PLATFORM_WINDOW_MODE_WINDOWED));
}

TEST(window_mode_saves_windowed_rect_on_enter_and_restores_it_on_leave)
{
    PlatformWindowModeState s;
    PlatformWindowRect out;
    bool maximized = true;
    platform_window_mode_init(&s, PLATFORM_WINDOW_MODE_WINDOWED);
    ASSERT_FALSE(platform_window_mode_restore_rect(&s, &out));
    platform_window_mode_save_windowed(&s, rect(-40, 120, 1280u, 720u), false);
    ASSERT_TRUE(platform_window_mode_restore_rect(&s, &out));
    ASSERT_EQ(out.x, -40);
    ASSERT_EQ(out.y, 120);
    ASSERT_EQ(out.width, 1280u);
    ASSERT_EQ(out.height, 720u);
    ASSERT_TRUE(platform_window_mode_restore_maximized(&s, &maximized));
    ASSERT_FALSE(maximized);
    /* A maximized window comes back maximized. */
    platform_window_mode_save_windowed(&s, rect(0, 0, 1920u, 1040u), true);
    ASSERT_TRUE(platform_window_mode_restore_maximized(&s, &maximized));
    ASSERT_TRUE(maximized);
    /* A zero-sized rect (minimized / not yet shown) is not a usable restore. */
    platform_window_mode_save_windowed(&s, rect(0, 0, 0u, 720u), false);
    ASSERT_FALSE(platform_window_mode_restore_rect(&s, &out));
}

TEST(window_mode_reverse_request_while_pending_follows_the_last_request)
{
    PlatformWindowModeState s;
    platform_window_mode_init(&s, PLATFORM_WINDOW_MODE_WINDOWED);
    ASSERT_EQ(platform_window_mode_request(&s, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN),
              PLATFORM_WINDOW_MODE_ACTION_ENTER);
    /* The user toggles back before the window manager answered: send LEAVE so
     * the asynchronous platform ends up windowed. */
    ASSERT_EQ(platform_window_mode_request(&s, PLATFORM_WINDOW_MODE_WINDOWED),
              PLATFORM_WINDOW_MODE_ACTION_LEAVE);
    ASSERT_EQ(s.requested, PLATFORM_WINDOW_MODE_WINDOWED);
    ASSERT_TRUE(s.pending);
    /* The first answer (fullscreen) arrives: still waiting for the LEAVE. */
    platform_window_mode_confirm(&s, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_EQ(s.current, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_TRUE(s.pending);
    platform_window_mode_confirm(&s, PLATFORM_WINDOW_MODE_WINDOWED);
    ASSERT_EQ(s.current, PLATFORM_WINDOW_MODE_WINDOWED);
    ASSERT_FALSE(s.pending);
}

TEST(window_mode_platform_refusal_and_external_switches_are_tracked)
{
    PlatformWindowModeState s;
    platform_window_mode_init(&s, PLATFORM_WINDOW_MODE_WINDOWED);
    ASSERT_EQ(platform_window_mode_request(&s, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN),
              PLATFORM_WINDOW_MODE_ACTION_ENTER);
    /* The window manager refused: the platform reports the request finished
     * in the old mode. */
    platform_window_mode_fail(&s);
    ASSERT_EQ(s.current, PLATFORM_WINDOW_MODE_WINDOWED);
    ASSERT_FALSE(s.pending);
    ASSERT_EQ(s.requested, PLATFORM_WINDOW_MODE_WINDOWED);
    /* The user went fullscreen with a WM shortcut: no request, still tracked. */
    platform_window_mode_confirm(&s, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_EQ(s.current, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_EQ(s.requested, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_FALSE(s.pending);
    ASSERT_EQ(platform_window_mode_request(&s, PLATFORM_WINDOW_MODE_WINDOWED),
              PLATFORM_WINDOW_MODE_ACTION_LEAVE);
}

TEST(window_mode_toggle_target_uses_the_requested_mode)
{
    PlatformWindowModeState s;
    platform_window_mode_init(&s, PLATFORM_WINDOW_MODE_WINDOWED);
    ASSERT_EQ(platform_window_mode_toggle_target(&s),
              PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    (void)platform_window_mode_request(&s, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    /* Toggling twice before the first confirm must not re-send ENTER. */
    ASSERT_EQ(platform_window_mode_toggle_target(&s), PLATFORM_WINDOW_MODE_WINDOWED);
    ASSERT_EQ(platform_window_mode_toggle_target(NULL), PLATFORM_WINDOW_MODE_WINDOWED);
}

TEST(window_mode_fixed_fullscreen_platforms_refuse_windowed)
{
    PlatformWindowModeState s;
    platform_window_mode_init_fixed(&s, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_EQ(s.current, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_TRUE(s.fixed);
    ASSERT_EQ(platform_window_mode_request(&s, PLATFORM_WINDOW_MODE_WINDOWED),
              PLATFORM_WINDOW_MODE_ACTION_UNSUPPORTED);
    ASSERT_EQ(platform_window_mode_request(&s, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN),
              PLATFORM_WINDOW_MODE_ACTION_NONE);
    platform_window_mode_confirm(&s, PLATFORM_WINDOW_MODE_WINDOWED);
    ASSERT_EQ(s.current, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
}

TEST(window_mode_target_rect_covers_the_monitor_the_window_is_on)
{
    MonitorInfo monitors[2];
    PlatformWindowRect out;
    memset(monitors, 0, sizeof(monitors));
    monitors[0].x = 0; monitors[0].y = 0; monitors[0].width = 1920u; monitors[0].height = 1080u;
    monitors[1].x = 1920; monitors[1].y = -200; monitors[1].width = 2560u; monitors[1].height = 1440u;
    /* Mostly on the second monitor. */
    ASSERT_TRUE(platform_window_mode_fullscreen_rect(monitors, 2u,
                                                     rect(1800, 100, 1200u, 700u), &out));
    ASSERT_EQ(out.x, 1920);
    ASSERT_EQ(out.y, -200);
    ASSERT_EQ(out.width, 2560u);
    ASSERT_EQ(out.height, 1440u);
    ASSERT_TRUE(platform_window_mode_fullscreen_rect(monitors, 2u,
                                                     rect(100, 100, 800u, 600u), &out));
    ASSERT_EQ(out.x, 0);
    ASSERT_EQ(out.width, 1920u);
    ASSERT_FALSE(platform_window_mode_fullscreen_rect(monitors, 0u,
                                                      rect(0, 0, 10u, 10u), &out));
    ASSERT_FALSE(platform_window_mode_fullscreen_rect(NULL, 2u,
                                                      rect(0, 0, 10u, 10u), &out));
}

TEST_MAIN_BEGIN()
    RUN_TEST(window_mode_starts_windowed_and_requests_are_idempotent);
    RUN_TEST(window_mode_rejects_invalid_arguments);
    RUN_TEST(window_mode_saves_windowed_rect_on_enter_and_restores_it_on_leave);
    RUN_TEST(window_mode_reverse_request_while_pending_follows_the_last_request);
    RUN_TEST(window_mode_platform_refusal_and_external_switches_are_tracked);
    RUN_TEST(window_mode_toggle_target_uses_the_requested_mode);
    RUN_TEST(window_mode_fixed_fullscreen_platforms_refuse_windowed);
    RUN_TEST(window_mode_target_rect_covers_the_monitor_the_window_is_on);
TEST_MAIN_END()
