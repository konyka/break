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

/* ---- Title bar / frame while windowed ---- */

TEST(decoration_defaults_on_for_windowed_and_off_for_fixed_platforms)
{
    PlatformWindowModeState s;
    platform_window_mode_init(&s, PLATFORM_WINDOW_MODE_WINDOWED);
    ASSERT_TRUE(s.decorated);
    ASSERT_TRUE(platform_window_mode_title_bar_visible(&s));
    /* A window created fullscreen keeps the windowed preference. */
    platform_window_mode_init(&s, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_TRUE(s.decorated);
    ASSERT_FALSE(platform_window_mode_title_bar_visible(&s));
    platform_window_mode_init_fixed(&s, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_FALSE(s.decorated);
    ASSERT_FALSE(platform_window_mode_title_bar_visible(&s));
    ASSERT_FALSE(platform_window_mode_title_bar_visible(NULL));
}

TEST(decoration_change_while_windowed_applies_now_and_is_idempotent)
{
    PlatformWindowModeState s;
    platform_window_mode_init(&s, PLATFORM_WINDOW_MODE_WINDOWED);
    ASSERT_EQ(platform_window_mode_set_decorated(&s, true),
              PLATFORM_DECORATION_ACTION_NONE);
    ASSERT_EQ(platform_window_mode_set_decorated(&s, false),
              PLATFORM_DECORATION_ACTION_APPLY);
    ASSERT_FALSE(s.decorated);
    ASSERT_FALSE(platform_window_mode_title_bar_visible(&s));
    ASSERT_EQ(platform_window_mode_set_decorated(&s, false),
              PLATFORM_DECORATION_ACTION_NONE);
    ASSERT_EQ(platform_window_mode_set_decorated(&s, true),
              PLATFORM_DECORATION_ACTION_APPLY);
    ASSERT_TRUE(platform_window_mode_title_bar_visible(&s));
    ASSERT_EQ(platform_window_mode_set_decorated(NULL, true),
              PLATFORM_DECORATION_ACTION_NONE);
}

TEST(decoration_change_while_fullscreen_is_deferred_to_leave)
{
    PlatformWindowModeState s;
    platform_window_mode_init(&s, PLATFORM_WINDOW_MODE_WINDOWED);
    (void)platform_window_mode_request(&s, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    platform_window_mode_confirm(&s, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    /* Fullscreen never shows a title bar; the preference waits for LEAVE. */
    ASSERT_EQ(platform_window_mode_set_decorated(&s, false),
              PLATFORM_DECORATION_ACTION_DEFER);
    ASSERT_FALSE(s.decorated);
    ASSERT_FALSE(platform_window_mode_title_bar_visible(&s));
    (void)platform_window_mode_request(&s, PLATFORM_WINDOW_MODE_WINDOWED);
    platform_window_mode_confirm(&s, PLATFORM_WINDOW_MODE_WINDOWED);
    ASSERT_FALSE(platform_window_mode_title_bar_visible(&s));
    ASSERT_EQ(platform_window_mode_set_decorated(&s, true),
              PLATFORM_DECORATION_ACTION_APPLY);
    ASSERT_TRUE(platform_window_mode_title_bar_visible(&s));
}

TEST(decoration_change_during_a_pending_enter_is_deferred)
{
    PlatformWindowModeState s;
    platform_window_mode_init(&s, PLATFORM_WINDOW_MODE_WINDOWED);
    /* X11/Wayland: ENTER sent, the WM has not answered yet. The window is
     * about to lose its frame anyway, so nothing native happens now. */
    (void)platform_window_mode_request(&s, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_EQ(platform_window_mode_set_decorated(&s, false),
              PLATFORM_DECORATION_ACTION_DEFER);
    /* WM refused: back to windowed, and now the preference must be applied. */
    platform_window_mode_fail(&s);
    ASSERT_TRUE(platform_window_mode_decoration_stale(&s));
    platform_window_mode_decoration_applied(&s);
    ASSERT_FALSE(platform_window_mode_decoration_stale(&s));
    ASSERT_FALSE(platform_window_mode_title_bar_visible(&s));
}

TEST(decoration_fixed_platforms_only_accept_undecorated)
{
    PlatformWindowModeState s;
    platform_window_mode_init_fixed(&s, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_EQ(platform_window_mode_set_decorated(&s, false),
              PLATFORM_DECORATION_ACTION_NONE);
    ASSERT_EQ(platform_window_mode_set_decorated(&s, true),
              PLATFORM_DECORATION_ACTION_UNSUPPORTED);
    ASSERT_FALSE(s.decorated);
}

TEST(decoration_stale_tracks_what_the_native_window_shows)
{
    PlatformWindowModeState s;
    platform_window_mode_init(&s, PLATFORM_WINDOW_MODE_WINDOWED);
    ASSERT_FALSE(platform_window_mode_decoration_stale(&s));
    ASSERT_EQ(platform_window_mode_set_decorated(&s, false),
              PLATFORM_DECORATION_ACTION_APPLY);
    /* APPLY means the backend still has to change the native window. */
    ASSERT_TRUE(platform_window_mode_decoration_stale(&s));
    platform_window_mode_decoration_applied(&s);
    ASSERT_FALSE(platform_window_mode_decoration_stale(&s));
    /* Deferred while fullscreen: stale only once windowed again. */
    (void)platform_window_mode_request(&s, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    platform_window_mode_confirm(&s, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_EQ(platform_window_mode_set_decorated(&s, true),
              PLATFORM_DECORATION_ACTION_DEFER);
    ASSERT_FALSE(platform_window_mode_decoration_stale(&s));
    (void)platform_window_mode_request(&s, PLATFORM_WINDOW_MODE_WINDOWED);
    platform_window_mode_confirm(&s, PLATFORM_WINDOW_MODE_WINDOWED);
    ASSERT_TRUE(platform_window_mode_decoration_stale(&s));
    platform_window_mode_decoration_applied(&s);
    ASSERT_FALSE(platform_window_mode_decoration_stale(&s));
    ASSERT_FALSE(platform_window_mode_decoration_stale(NULL));
}

TEST_MAIN_BEGIN()
    RUN_TEST(decoration_defaults_on_for_windowed_and_off_for_fixed_platforms);
    RUN_TEST(decoration_change_while_windowed_applies_now_and_is_idempotent);
    RUN_TEST(decoration_change_while_fullscreen_is_deferred_to_leave);
    RUN_TEST(decoration_change_during_a_pending_enter_is_deferred);
    RUN_TEST(decoration_fixed_platforms_only_accept_undecorated);
    RUN_TEST(decoration_stale_tracks_what_the_native_window_shows);
    RUN_TEST(window_mode_starts_windowed_and_requests_are_idempotent);
    RUN_TEST(window_mode_rejects_invalid_arguments);
    RUN_TEST(window_mode_saves_windowed_rect_on_enter_and_restores_it_on_leave);
    RUN_TEST(window_mode_reverse_request_while_pending_follows_the_last_request);
    RUN_TEST(window_mode_platform_refusal_and_external_switches_are_tracked);
    RUN_TEST(window_mode_toggle_target_uses_the_requested_mode);
    RUN_TEST(window_mode_fixed_fullscreen_platforms_refuse_windowed);
    RUN_TEST(window_mode_target_rect_covers_the_monitor_the_window_is_on);
TEST_MAIN_END()
