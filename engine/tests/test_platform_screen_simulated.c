#include "test_framework.h"

/* QNX Screen window layer (window_screen.c) compiled on the host against a
 * fake Screen SDK (tests/fake_qnx_screen): checks the fixed-fullscreen
 * window-mode contract (FS2/FS4) without a QNX target. */

#include "platform/platform.h"

#include <screen/screen.h>

#include <stdlib.h>

struct _screen_context { int unused; };
struct _screen_window { int size[2]; int visible; };
struct _screen_event { int unused; };

static int g_window_count = 0;

int screen_create_context(screen_context_t *pctx, int flags)
{
    (void)flags;
    *pctx = calloc(1, sizeof(**pctx));
    return *pctx != NULL ? 0 : -1;
}

int screen_destroy_context(screen_context_t ctx)
{
    free(ctx);
    return 0;
}

int screen_flush_context(screen_context_t ctx, int flags)
{
    (void)ctx;
    (void)flags;
    return 0;
}

int screen_create_window(screen_window_t *pwin, screen_context_t ctx)
{
    (void)ctx;
    *pwin = calloc(1, sizeof(**pwin));
    if (*pwin != NULL) g_window_count++;
    return *pwin != NULL ? 0 : -1;
}

int screen_destroy_window(screen_window_t win)
{
    if (win != NULL) g_window_count--;
    free(win);
    return 0;
}

int screen_set_window_property_iv(screen_window_t win, int pname, const int *param)
{
    if (pname == SCREEN_PROPERTY_SIZE) {
        win->size[0] = param[0];
        win->size[1] = param[1];
    } else if (pname == SCREEN_PROPERTY_VISIBLE) {
        win->visible = param[0];
    }
    return 0;
}

int screen_get_window_property_iv(screen_window_t win, int pname, int *param)
{
    if (pname != SCREEN_PROPERTY_SIZE) return -1;
    param[0] = win->size[0];
    param[1] = win->size[1];
    return 0;
}

int screen_create_event(screen_event_t *pev)
{
    *pev = calloc(1, sizeof(**pev));
    return *pev != NULL ? 0 : -1;
}

int screen_destroy_event(screen_event_t ev)
{
    free(ev);
    return 0;
}

int screen_get_event(screen_context_t ctx, screen_event_t ev, unsigned long long timeout)
{
    (void)ctx;
    (void)ev;
    (void)timeout;
    return 0;
}

int screen_get_event_property_iv(screen_event_t ev, int pname, int *param)
{
    (void)ev;
    if (pname != SCREEN_PROPERTY_TYPE) return -1;
    param[0] = SCREEN_EVENT_NONE;
    return 0;
}

TEST(screen_window_is_fixed_borderless_fullscreen)
{
    const PlatformConfig config = {.width = 640, .height = 360, .title = "Break QNX Screen"};
    Platform *platform = platform_create(&config);
    u32 width = 0;
    u32 height = 0;

    ASSERT_NOT_NULL(platform);
    ASSERT_EQ(g_window_count, 1);
    ASSERT_EQ(platform_poll(platform), PLATFORM_EVENT_NONE);
    ASSERT_EQ(platform_get_window_mode(platform), PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_TRUE(platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN));
    ASSERT_FALSE(platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_WINDOWED));
    ASSERT_FALSE(platform_set_window_mode(platform, (PlatformWindowMode)7));
    platform_toggle_fullscreen(platform);
    ASSERT_EQ(platform_get_window_mode(platform), PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_FALSE(platform_needs_client_decoration(platform));
    platform_get_size(platform, &width, &height);
    ASSERT_EQ(width, 640u);
    ASSERT_EQ(height, 360u);
    platform_destroy(platform);
    ASSERT_EQ(g_window_count, 0);
}

TEST(screen_start_fullscreen_is_the_same_fixed_mode)
{
    const PlatformConfig config = {.width = 640, .height = 360,
                                   .title = "Break QNX Screen start fullscreen",
                                   .start_fullscreen = true};
    Platform *platform = platform_create(&config);

    ASSERT_NOT_NULL(platform);
    ASSERT_EQ(platform_get_window_mode(platform), PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    ASSERT_FALSE(platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_WINDOWED));
    platform_destroy(platform);
}

TEST(screen_window_mode_null_safety)
{
    ASSERT_FALSE(platform_set_window_mode(NULL, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN));
    ASSERT_EQ(platform_get_window_mode(NULL), PLATFORM_WINDOW_MODE_WINDOWED);
    platform_toggle_fullscreen(NULL);
}

TEST_MAIN_BEGIN()
    RUN_TEST(screen_window_is_fixed_borderless_fullscreen);
    RUN_TEST(screen_start_fullscreen_is_the_same_fixed_mode);
    RUN_TEST(screen_window_mode_null_safety);
TEST_MAIN_END()
