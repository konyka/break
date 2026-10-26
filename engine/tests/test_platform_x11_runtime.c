#include "test_framework.h"

#include "platform/platform.h"
#include "platform/window_mode.h"

#include <X11/Xlib.h>
#include <X11/Xatom.h>
#ifdef ENGINE_X11_XINPUT2
#include <X11/extensions/XInput2.h>
#endif
#include <time.h>

static void runtime_failure(const char *message)
{
    printf("  FAIL: %s\n", message);
    g_test_fail++;
}

static int x11_runtime_available(void)
{
    Display *display = XOpenDisplay(NULL);
    if (display == NULL) return 0;
    XCloseDisplay(display);
    return 1;
}

TEST(x11_window_create_resize_and_destroy)
{
    const PlatformConfig config = {.width = 320, .height = 240, .title = "Break X11 runtime"};
    Platform *platform;
    Display *display;
    Window window;
    u32 width = 0;
    u32 height = 0;
    PlatformMediaContext media;
    bool resized = false;
    bool ok = true;

    platform = platform_create(&config);
    if (platform == NULL) {
        runtime_failure("platform_create returned NULL");
        return;
    }
    display = (Display *)platform_display_native(platform);
    window = (Window)(uintptr_t)platform_window_native(platform);
    if (display == NULL) {
        runtime_failure("platform_display_native returned NULL");
        ok = false;
        goto cleanup;
    }
    if (platform_get_media_generation(platform) == 0u) {
        runtime_failure("X11 media generation was not initialized");
        ok = false;
    }
    if (window == 0 || platform_surface_native(platform) == NULL) {
        runtime_failure("platform native window handles are incomplete");
        ok = false;
        goto cleanup;
    }

    /* Drain map/initial configure notifications before testing resize. */
    (void)platform_poll(platform);
    XResizeWindow(display, window, 517, 293);
    XSync(display, False);
    for (int attempt = 0; attempt < 100; attempt++) {
        (void)platform_poll(platform);
        XSync(display, False);
        platform_get_size(platform, &width, &height);
        if (width == 517 && height == 293) {
            resized = true;
            break;
        }
        {
            const struct timespec delay = {0, 1000000L};
            nanosleep(&delay, NULL);
        }
    }
    if (!resized) {
        runtime_failure("X11 ConfigureNotify resize was not observed");
        ok = false;
    }
    if (!platform_get_media_context(platform, &media) ||
        (media.known & PLATFORM_MEDIA_KNOWN_COLOR_GAMUT) == 0) {
        runtime_failure("X11 media context is incomplete");
        ok = false;
    }
    if ((media.capabilities & PLATFORM_MEDIA_CAP_COLOR_P3) != 0u &&
        (media.known & PLATFORM_MEDIA_KNOWN_COLOR_GAMUT) == 0u) {
        runtime_failure("X11 P3 capability is not marked known");
        ok = false;
    }
    if ((media.capabilities & PLATFORM_MEDIA_CAP_COLOR_REC2020) != 0u &&
        (media.capabilities & PLATFORM_MEDIA_CAP_COLOR_P3) == 0u) {
        runtime_failure("X11 Rec.2020 capability lacks P3 implication");
        ok = false;
    }
    if ((media.capabilities & PLATFORM_MEDIA_CAP_HDR) != 0u &&
        (media.known & PLATFORM_MEDIA_KNOWN_HDR) == 0u) {
        runtime_failure("X11 HDR capability is not marked known");
        ok = false;
    }
#ifdef ENGINE_X11_XINPUT2
    if ((media.capabilities & PLATFORM_MEDIA_CAP_HOVER) != 0u &&
        (media.capabilities & PLATFORM_MEDIA_CAP_POINTER_FINE) == 0u) {
        runtime_failure("X11 hover capability lacks a fine primary pointer");
        ok = false;
    }
    if ((media.capabilities & PLATFORM_MEDIA_CAP_POINTER_COARSE) != 0u &&
        (media.capabilities & PLATFORM_MEDIA_CAP_ANY_POINTER_COARSE) == 0u) {
        runtime_failure("X11 coarse primary pointer lacks any-pointer coarse");
        ok = false;
    }
#endif
    if (platform_get_monitor_count(platform) == 0) {
        runtime_failure("X11 monitor enumeration returned no monitor");
        ok = false;
    }

cleanup:
    platform_destroy(platform);
    (void)ok;
}

/* ---- Borderless fullscreen (FS4) ---- */

static void x11_sleep_ms(long ms)
{
    const struct timespec delay = {0, ms * 1000000L};
    nanosleep(&delay, NULL);
}

static bool x11_window_root_rect(Display *display, Window window,
                                 PlatformWindowRect *out)
{
    Window root;
    Window child;
    int x = 0;
    int y = 0;
    int root_x = 0;
    int root_y = 0;
    unsigned int width = 0;
    unsigned int height = 0;
    unsigned int border = 0;
    unsigned int depth = 0;
    if (!XGetGeometry(display, window, &root, &x, &y, &width, &height,
                      &border, &depth))
        return false;
    if (!XTranslateCoordinates(display, window, root, 0, 0, &root_x, &root_y,
                               &child))
        return false;
    out->x = root_x;
    out->y = root_y;
    out->width = width;
    out->height = height;
    return true;
}

static bool x11_rect_equal(PlatformWindowRect a, PlatformWindowRect b)
{
    return a.x == b.x && a.y == b.y && a.width == b.width && a.height == b.height;
}

/* The monitor the backend must cover: same rule as window_mode.h, falling
 * back to the root window when RandR reports no monitor. */
static PlatformWindowRect x11_expected_fullscreen_rect(Platform *platform,
                                                       Display *display,
                                                       PlatformWindowRect window)
{
    MonitorInfo monitors[PLATFORM_MAX_MONITORS];
    u32 count = platform_get_monitor_count(platform);
    PlatformWindowRect out;
    if (count > PLATFORM_MAX_MONITORS) count = PLATFORM_MAX_MONITORS;
    for (u32 i = 0; i < count; i++) {
        if (!platform_get_monitor_info(platform, i, &monitors[i])) {
            count = i;
            break;
        }
    }
    if (!platform_window_mode_fullscreen_rect(monitors, count, window, &out)) {
        out.x = 0;
        out.y = 0;
        out.width = (u32)DisplayWidth(display, DefaultScreen(display));
        out.height = (u32)DisplayHeight(display, DefaultScreen(display));
    }
    return out;
}

/* Polls (bounded, about 3 s) until the platform reports `mode` and the window
 * really covers `expected`; the X11 confirm can be asynchronous. */
static bool x11_wait_for_mode(Platform *platform, Display *display, Window window,
                              PlatformWindowMode mode, PlatformWindowRect expected,
                              bool check_position)
{
    for (int attempt = 0; attempt < 3000; attempt++) {
        PlatformWindowRect actual;
        u32 width = 0;
        u32 height = 0;
        (void)platform_poll(platform);
        XSync(display, False);
        platform_get_size(platform, &width, &height);
        if (platform_get_window_mode(platform) == mode &&
            x11_window_root_rect(display, window, &actual) &&
            (check_position ? x11_rect_equal(actual, expected)
                            : actual.width == expected.width &&
                                  actual.height == expected.height) &&
            width == expected.width && height == expected.height)
            return true;
        x11_sleep_ms(1);
    }
    return false;
}

static bool x11_root_has_ewmh_fullscreen(Display *display)
{
    Window root = DefaultRootWindow(display);
    Atom check = XInternAtom(display, "_NET_SUPPORTING_WM_CHECK", False);
    Atom supported = XInternAtom(display, "_NET_SUPPORTED", False);
    Atom fullscreen = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);
    Atom type;
    int format;
    unsigned long count;
    unsigned long after;
    unsigned char *data = NULL;
    bool found = false;
    if (XGetWindowProperty(display, root, check, 0, 1, False, XA_WINDOW, &type,
                           &format, &count, &after, &data) != Success ||
        data == NULL || count == 0) {
        if (data != NULL) XFree(data);
        return false;
    }
    XFree(data);
    data = NULL;
    if (XGetWindowProperty(display, root, supported, 0, 4096, False, XA_ATOM,
                           &type, &format, &count, &after, &data) == Success &&
        data != NULL && format == 32) {
        const Atom *atoms = (const Atom *)data;
        for (unsigned long i = 0; i < count; i++)
            if (atoms[i] == fullscreen) found = true;
    }
    if (data != NULL) XFree(data);
    return found;
}

/* Returns the CARDINAL/ATOM-typed 32-bit property as longs (count items). */
static unsigned long x11_read_long_property(Display *display, Window window,
                                            const char *name, Atom req_type,
                                            long *out, unsigned long max)
{
    Atom property = XInternAtom(display, name, False);
    Atom type;
    int format;
    unsigned long count = 0;
    unsigned long after;
    unsigned char *data = NULL;
    unsigned long n = 0;
    if (XGetWindowProperty(display, window, property, 0, (long)max, False,
                           req_type, &type, &format, &count, &after,
                           &data) == Success &&
        data != NULL && format == 32) {
        const long *values = (const long *)data;
        for (n = 0; n < count && n < max; n++) out[n] = values[n];
    }
    if (data != NULL) XFree(data);
    return n;
}

static void x11_expect_fullscreen_hints(Display *display, Window window,
                                        bool ewmh, bool fullscreen)
{
    long values[8];
    unsigned long n;
    Atom motif = XInternAtom(display, "_MOTIF_WM_HINTS", False);
    n = x11_read_long_property(display, window, "_NET_WM_BYPASS_COMPOSITOR",
                               XA_CARDINAL, values, 1);
    if (fullscreen && (n != 1 || values[0] != 1))
        runtime_failure("fullscreen window lacks _NET_WM_BYPASS_COMPOSITOR=1");
    if (!fullscreen && n == 1 && values[0] == 1)
        runtime_failure("windowed window still bypasses the compositor");
    if (ewmh) {
        Atom state_full = XInternAtom(display, "_NET_WM_STATE_FULLSCREEN", False);
        bool has = false;
        n = x11_read_long_property(display, window, "_NET_WM_STATE", XA_ATOM,
                                   values, 8);
        for (unsigned long i = 0; i < n; i++)
            if ((Atom)values[i] == state_full) has = true;
        if (has != fullscreen)
            runtime_failure("_NET_WM_STATE FULLSCREEN does not match the mode");
        return;
    }
    n = x11_read_long_property(display, window, "_MOTIF_WM_HINTS", motif,
                               values, 5);
    if (fullscreen && (n < 3 || (values[0] & 2) == 0 || values[2] != 0))
        runtime_failure("fallback fullscreen did not clear _MOTIF_WM_HINTS decorations");
    if (!fullscreen && n >= 3 && (values[0] & 2) != 0 && values[2] == 0)
        runtime_failure("leaving fallback fullscreen kept decorations disabled");
}

TEST(x11_borderless_fullscreen_enter_leave_restores)
{
    const PlatformConfig config = {.width = 320, .height = 240, .title = "Break X11 fullscreen"};
    Platform *platform = platform_create(&config);
    Display *display;
    Window window;
    PlatformWindowRect windowed;
    PlatformWindowRect fullscreen;
    bool ewmh;

    if (platform == NULL) {
        runtime_failure("platform_create returned NULL");
        return;
    }
    display = (Display *)platform_display_native(platform);
    window = (Window)(uintptr_t)platform_window_native(platform);
    ewmh = x11_root_has_ewmh_fullscreen(display);
    printf("  X11 fullscreen path: %s\n",
           ewmh ? "EWMH _NET_WM_STATE" : "no EWMH WM (motif + move/resize fallback)");
    (void)platform_poll(platform);
    XSync(display, False);
    if (platform_get_window_mode(platform) != PLATFORM_WINDOW_MODE_WINDOWED)
        runtime_failure("new window is not WINDOWED");
    if (!x11_window_root_rect(display, window, &windowed)) {
        runtime_failure("XGetGeometry failed on the new window");
        goto cleanup;
    }
    fullscreen = x11_expected_fullscreen_rect(platform, display, windowed);

    if (!platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN))
        runtime_failure("platform_set_window_mode(BORDERLESS) returned false");
    if (!x11_wait_for_mode(platform, display, window,
                           PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN, fullscreen,
                           true)) {
        PlatformWindowRect actual = {0, 0, 0, 0};
        (void)x11_window_root_rect(display, window, &actual);
        printf("  mode=%d rect=%d,%d %ux%u expected=%d,%d %ux%u\n",
               (int)platform_get_window_mode(platform), actual.x, actual.y,
               actual.width, actual.height, fullscreen.x, fullscreen.y,
               fullscreen.width, fullscreen.height);
        runtime_failure("fullscreen was not confirmed covering the monitor");
    }
    x11_expect_fullscreen_hints(display, window, ewmh, true);
    if (!platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN))
        runtime_failure("repeated platform_set_window_mode(BORDERLESS) returned false");
    if (platform_get_window_mode(platform) != PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN)
        runtime_failure("repeated fullscreen request changed the mode");

    if (!platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_WINDOWED))
        runtime_failure("platform_set_window_mode(WINDOWED) returned false");
    /* A reparenting WM may place the restored frame itself: size only. */
    if (!x11_wait_for_mode(platform, display, window, PLATFORM_WINDOW_MODE_WINDOWED,
                           windowed, !ewmh)) {
        PlatformWindowRect actual = {0, 0, 0, 0};
        (void)x11_window_root_rect(display, window, &actual);
        printf("  mode=%d rect=%d,%d %ux%u expected=%d,%d %ux%u\n",
               (int)platform_get_window_mode(platform), actual.x, actual.y,
               actual.width, actual.height, windowed.x, windowed.y,
               windowed.width, windowed.height);
        runtime_failure("leaving fullscreen did not restore the windowed rect");
    }
    x11_expect_fullscreen_hints(display, window, ewmh, false);
    if (!platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_WINDOWED))
        runtime_failure("repeated platform_set_window_mode(WINDOWED) returned false");
    if (platform_get_window_mode(platform) != PLATFORM_WINDOW_MODE_WINDOWED)
        runtime_failure("repeated windowed request changed the mode");

cleanup:
    platform_destroy(platform);
}

TEST(x11_start_fullscreen_covers_monitor_then_restores)
{
    const PlatformConfig config = {.width = 320, .height = 240,
                                   .title = "Break X11 start fullscreen",
                                   .start_fullscreen = true};
    const PlatformWindowRect windowed = {0, 0, 320, 240};
    Platform *platform = platform_create(&config);
    Display *display;
    Window window;
    PlatformWindowRect fullscreen;

    if (platform == NULL) {
        runtime_failure("platform_create(start_fullscreen) returned NULL");
        return;
    }
    display = (Display *)platform_display_native(platform);
    window = (Window)(uintptr_t)platform_window_native(platform);
    fullscreen = x11_expected_fullscreen_rect(platform, display, windowed);
    if (!x11_wait_for_mode(platform, display, window,
                           PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN, fullscreen,
                           true))
        runtime_failure("start_fullscreen window does not cover the monitor");
    if (!platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_WINDOWED))
        runtime_failure("platform_set_window_mode(WINDOWED) returned false");
    {
        bool restored = false;
        for (int attempt = 0; attempt < 3000 && !restored; attempt++) {
            u32 width = 0;
            u32 height = 0;
            (void)platform_poll(platform);
            XSync(display, False);
            platform_get_size(platform, &width, &height);
            restored = platform_get_window_mode(platform) == PLATFORM_WINDOW_MODE_WINDOWED &&
                       width == windowed.width && height == windowed.height;
            if (!restored) x11_sleep_ms(1);
        }
        if (!restored)
            runtime_failure("leaving start_fullscreen did not restore the configured size");
    }
    platform_destroy(platform);
}

/* ---- Title bar on/off (windowed) ----
 * X11 asks the WM through _MOTIF_WM_HINTS.decorations (the hint every
 * reparenting WM honours); flags bit 1 = decorations field valid. A WM-less
 * server (CI Xvfb) draws no title bar either way, so the property is the
 * observable contract; the client geometry must not change. */

static bool x11_motif_decorations(Display *display, Window window, bool *decorated)
{
    long values[5];
    Atom motif = XInternAtom(display, "_MOTIF_WM_HINTS", False);
    unsigned long n = x11_read_long_property(display, window, "_MOTIF_WM_HINTS",
                                             motif, values, 5);
    if (n < 3 || (values[0] & 2) == 0) {
        *decorated = true; /* no hint: WM default, decorated */
        return n == 0;
    }
    *decorated = values[2] != 0;
    return true;
}

TEST(x11_title_bar_hide_and_show_sets_motif_hints)
{
    const PlatformConfig config = {.width = 320, .height = 240, .title = "Break X11 title bar"};
    Platform *platform = platform_create(&config);
    Display *display;
    Window window;
    bool decorated = false;
    u32 width = 0;
    u32 height = 0;

    if (platform == NULL) {
        runtime_failure("platform_create returned NULL");
        return;
    }
    display = (Display *)platform_display_native(platform);
    window = (Window)(uintptr_t)platform_window_native(platform);
    (void)platform_poll(platform);
    XSync(display, False);
    if (!platform_get_window_decorated(platform) ||
        !platform_window_title_bar_visible(platform))
        runtime_failure("a new X11 window must be decorated");
    if (!x11_motif_decorations(display, window, &decorated) || !decorated)
        runtime_failure("a new X11 window must not disable decorations");

    if (!platform_set_window_decorated(platform, false))
        runtime_failure("set_window_decorated(false) returned false");
    XSync(display, False);
    if (!x11_motif_decorations(display, window, &decorated) || decorated)
        runtime_failure("undecorated X11 window lacks _MOTIF_WM_HINTS decorations=0");
    if (platform_get_window_decorated(platform) ||
        platform_window_title_bar_visible(platform))
        runtime_failure("decorated state did not follow set(false)");
    if (platform_get_window_mode(platform) != PLATFORM_WINDOW_MODE_WINDOWED)
        runtime_failure("hiding the title bar changed the window mode");
    for (int i = 0; i < 20; i++) (void)platform_poll(platform);
    platform_get_size(platform, &width, &height);
    if (width != 320u || height != 240u)
        runtime_failure("hiding the title bar changed the client size");

    if (!platform_set_window_decorated(platform, true))
        runtime_failure("set_window_decorated(true) returned false");
    XSync(display, False);
    if (!x11_motif_decorations(display, window, &decorated) || !decorated)
        runtime_failure("re-decorated X11 window still disables decorations");
    platform_destroy(platform);
}

TEST(x11_undecorated_survives_fullscreen_and_deferred_change_applies)
{
    const PlatformConfig config = {.width = 320, .height = 240,
                                   .title = "Break X11 undecorated fullscreen",
                                   .undecorated = true};
    Platform *platform = platform_create(&config);
    Display *display;
    Window window;
    PlatformWindowRect windowed;
    PlatformWindowRect fullscreen;
    bool decorated = true;
    bool ewmh;

    if (platform == NULL) {
        runtime_failure("platform_create(undecorated) returned NULL");
        return;
    }
    display = (Display *)platform_display_native(platform);
    window = (Window)(uintptr_t)platform_window_native(platform);
    ewmh = x11_root_has_ewmh_fullscreen(display);
    (void)platform_poll(platform);
    XSync(display, False);
    if (platform_get_window_decorated(platform))
        runtime_failure("undecorated config window reports decorated");
    if (!x11_motif_decorations(display, window, &decorated) || decorated)
        runtime_failure("undecorated config window lacks _MOTIF_WM_HINTS decorations=0");
    if (!x11_window_root_rect(display, window, &windowed)) {
        runtime_failure("XGetGeometry failed");
        goto cleanup;
    }
    fullscreen = x11_expected_fullscreen_rect(platform, display, windowed);

    (void)platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    if (!x11_wait_for_mode(platform, display, window,
                           PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN, fullscreen, true))
        runtime_failure("undecorated window did not go fullscreen");
    /* Deferred: decorated again while fullscreen, applied on leave. */
    if (!platform_set_window_decorated(platform, true))
        runtime_failure("set_window_decorated(true) while fullscreen returned false");
    if (platform_window_title_bar_visible(platform))
        runtime_failure("fullscreen reports a visible title bar");
    (void)platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_WINDOWED);
    if (!x11_wait_for_mode(platform, display, window, PLATFORM_WINDOW_MODE_WINDOWED,
                           windowed, !ewmh))
        runtime_failure("leaving fullscreen did not restore the windowed rect");
    XSync(display, False);
    if (!x11_motif_decorations(display, window, &decorated) || !decorated)
        runtime_failure("deferred decorated=true was not applied on leave");
    if (!platform_window_title_bar_visible(platform))
        runtime_failure("title bar not reported visible after leave");

cleanup:
    platform_destroy(platform);
}

int main(void)
{
    if (!x11_runtime_available()) {
        printf("SKIP: no reachable X11 display\n");
        return 77;
    }
    printf("=== Running Tests ===\n");
    RUN_TEST(x11_window_create_resize_and_destroy);
    RUN_TEST(x11_borderless_fullscreen_enter_leave_restores);
    RUN_TEST(x11_start_fullscreen_covers_monitor_then_restores);
    RUN_TEST(x11_title_bar_hide_and_show_sets_motif_hints);
    RUN_TEST(x11_undecorated_survives_fullscreen_and_deferred_change_applies);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
