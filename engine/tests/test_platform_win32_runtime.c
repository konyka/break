#include "test_framework.h"

#include "platform/platform.h"
#include "platform/gamepad_linux.h"  /* shared gamepad_init/shutdown prototypes */

#include <windows.h>

static void record_failure(const char *message)
{
    printf("  FAIL: %s\n", message);
    g_test_fail++;
}

TEST(platform_create_rejects_invalid_configuration_before_native_calls)
{
    const PlatformConfig zero_width = {0, 240, "break invalid"};
    const PlatformConfig oversized = {
        PLATFORM_MAX_WINDOW_DIMENSION + 1u, 240, "break invalid"
    };

    ASSERT_EQ(platform_create(NULL), NULL);
    ASSERT_EQ(platform_create(&zero_width), NULL);
    ASSERT_EQ(platform_create(&oversized), NULL);
}

TEST(invalid_utf8_title_is_rejected_without_creating_a_window)
{
    const char invalid_utf8[] = "\xE4\xB8";
    PlatformConfig config = {640, 480, invalid_utf8};

    ASSERT_EQ(platform_create(&config), NULL);
}

TEST(real_window_preserves_title_size_and_destroys_cleanly)
{
    const char title[] = "Break \xE4\xB8\xAD \xF0\x9F\x99\x82";
    const wchar_t expected_title[] = L"Break \x4E2D \xD83D\xDE42";
    const u32 expected_width = 731;
    const u32 expected_height = 419;
    PlatformConfig config = {320, 240, title};
    Platform *platform = platform_create(&config);
    HWND hwnd;
    wchar_t actual_title[64];
    int actual_units;
    u32 width = 0;
    u32 height = 0;
    bool ok = true;

    if (platform == NULL) {
        record_failure("platform_create returned NULL for valid UTF-8");
        return;
    }

    hwnd = (HWND)platform_window_native(platform);
    if (hwnd == NULL) {
        record_failure("platform_window_native returned NULL");
        ok = false;
        goto cleanup;
    }

    actual_units = GetWindowTextW(hwnd, actual_title,
                                  (int)(sizeof(actual_title) / sizeof(actual_title[0])));
    if (actual_units != (int)(sizeof(expected_title) / sizeof(expected_title[0])) - 1) {
        record_failure("GetWindowTextW returned an unexpected UTF-16 length");
        ok = false;
    } else {
        for (int i = 0; i < actual_units; i++) {
            if (actual_title[i] != expected_title[i]) {
                record_failure("GetWindowTextW returned unexpected UTF-16 code units");
                ok = false;
                break;
            }
        }
    }

    if (!PostMessageW(hwnd, WM_SIZE, SIZE_RESTORED,
                      MAKELPARAM(expected_width, expected_height))) {
        record_failure("PostMessageW(WM_SIZE) failed");
        ok = false;
        goto cleanup;
    }
    (void)platform_poll(platform);
    platform_get_size(platform, &width, &height);
    if (width != expected_width || height != expected_height) {
        record_failure("platform_get_size did not observe WM_SIZE");
        ok = false;
    }

cleanup:
    platform_destroy(platform);
    if (!ok) return;
}

TEST(alt_f4_requests_close_through_default_system_key_handling)
{
    /* R562: WM_SYSKEY* used to be consumed without reaching DefWindowProcW,
     * so Alt+F4 never produced WM_CLOSE. Post the message DefWindowProcW
     * turns into a close request (F4 with the Alt context bit set) and
     * require the platform to report a quit event. */
    PlatformConfig config = {320, 240, "break syskey"};
    Platform *platform = platform_create(&config);
    HWND hwnd;
    bool ok = true;

    if (platform == NULL) {
        record_failure("platform_create returned NULL");
        return;
    }
    hwnd = (HWND)platform_window_native(platform);
    /* lParam: repeat count 1, scan code 0x3E (F4), bit 29 = Alt held. */
    if (!PostMessageW(hwnd, WM_SYSKEYDOWN, VK_F4,
                      (LPARAM)(1 | (0x3E << 16) | (1 << 29)))) {
        record_failure("PostMessageW(WM_SYSKEYDOWN) failed");
        ok = false;
    } else if (platform_poll(platform) != PLATFORM_EVENT_QUIT) {
        record_failure("Alt+F4 did not produce PLATFORM_EVENT_QUIT");
        ok = false;
    }
    platform_destroy(platform);
    if (!ok) return;
}

TEST(relative_mouse_mode_ignores_absolute_move_deltas)
{
    /* R563: WM_MOUSEMOVE accumulated absolute-position deltas even in
     * relative mode while WM_INPUT also added raw deltas (~2x speed, mixed
     * units). In relative mode the absolute handler must only track
     * mouse_x/y, never mouse_dx/dy (mirrors the X11 backend). */
    PlatformConfig config = {320, 240, "break relmouse"};
    Platform *platform = platform_create(&config);
    HWND hwnd;
    InputState *input;
    bool ok = true;

    if (platform == NULL) {
        record_failure("platform_create returned NULL");
        return;
    }
    hwnd = (HWND)platform_window_native(platform);
    input = platform_input(platform);

    /* Park the window far off-screen and drain the queue. Windows
     * synthesizes WM_MOUSEMOVE (at unpredictable times) for a window shown
     * under the stationary real cursor; that would interleave with the
     * posted messages below and corrupt the delta baseline. Off-screen the
     * cursor can never hover the window. */
    SetWindowPos(hwnd, NULL, -32000, -32000, 0, 0,
                 SWP_NOSIZE | SWP_NOZORDER | SWP_NOACTIVATE);
    (void)platform_poll(platform);

    /* Absolute mode still accumulates deltas. Expectations are computed
     * from the measured position so an already-seeded baseline cannot
     * skew them. */
    PostMessageW(hwnd, WM_MOUSEMOVE, 0, MAKELPARAM(10, 10));
    (void)platform_poll(platform);
    f32 prev_x = input->mouse_x;
    f32 prev_y = input->mouse_y;
    PostMessageW(hwnd, WM_MOUSEMOVE, 0, MAKELPARAM(20, 15));
    (void)platform_poll(platform);
    if (fabsf(input->mouse_dx - (20.0f - prev_x)) > 1e-4f ||
        fabsf(input->mouse_dy - (15.0f - prev_y)) > 1e-4f) {
        record_failure("absolute-mode WM_MOUSEMOVE deltas wrong");
        ok = false;
    }

    /* Relative mode: absolute moves update the position but add no deltas. */
    platform_mouse_set_relative(platform, true);
    PostMessageW(hwnd, WM_MOUSEMOVE, 0, MAKELPARAM(30, 30));
    PostMessageW(hwnd, WM_MOUSEMOVE, 0, MAKELPARAM(50, 60));
    (void)platform_poll(platform);
    if (fabsf(input->mouse_dx) > 1e-4f || fabsf(input->mouse_dy) > 1e-4f) {
        record_failure("relative mode accumulated absolute deltas");
        ok = false;
    }
    if (fabsf(input->mouse_x - 50.0f) > 1e-4f ||
        fabsf(input->mouse_y - 60.0f) > 1e-4f) {
        record_failure("relative mode did not track absolute position");
        ok = false;
    }
    platform_mouse_set_relative(platform, false);
    platform_destroy(platform);
    if (!ok) return;
}

TEST(clipboard_read_bounds_unterminated_unicode_text)
{
    /* R564: Windows does not guarantee NUL-termination of CF_UNICODETEXT.
     * Place a fully unterminated payload on the clipboard; the read must
     * stop at the GlobalAlloc region boundary instead of scanning past it
     * (wcslen/WideCharToMultiByte(-1) overread before the fix). */
    PlatformConfig config = {320, 240, "break clip"};
    Platform *platform = platform_create(&config);
    static const wchar_t prefix[] = L"unterminated";
    HGLOBAL memory = NULL;
    wchar_t *wide;
    usize region_units;
    char *text = NULL;
    char buf[64];
    bool ok = true;

    if (platform == NULL) {
        record_failure("platform_create returned NULL");
        return;
    }
    /* OpenClipboard fails while another process momentarily holds the
     * clipboard (viewers, history service); retry briefly. */
    {
        bool opened = false;
        for (int attempt = 0; attempt < 20 && !opened; attempt++) {
            if (attempt > 0) Sleep(25);
            opened = OpenClipboard((HWND)platform_window_native(platform)) != 0;
        }
        if (!opened) {
            record_failure("OpenClipboard failed");
            ok = false;
            goto cleanup;
        }
    }
    (void)EmptyClipboard();
    memory = GlobalAlloc(GMEM_MOVEABLE, 16 * sizeof(wchar_t));
    if (memory == NULL) {
        record_failure("GlobalAlloc failed");
        CloseClipboard();
        ok = false;
        goto cleanup;
    }
    /* Fill the WHOLE region with non-zero data (no NUL anywhere), with the
     * marker text at the start. GlobalSize may exceed the request. */
    region_units = (usize)(GlobalSize(memory) / sizeof(wchar_t));
    wide = (wchar_t *)GlobalLock(memory);
    if (wide == NULL) {
        record_failure("GlobalLock failed");
        GlobalFree(memory);
        memory = NULL;
        CloseClipboard();
        ok = false;
        goto cleanup;
    }
    for (usize i = 0; i < region_units; i++) wide[i] = L'x';
    memcpy(wide, prefix, (sizeof(prefix) - sizeof(prefix[0])));
    GlobalUnlock(memory);
    if (SetClipboardData(CF_UNICODETEXT, memory) == NULL) {
        record_failure("SetClipboardData failed");
        GlobalFree(memory);
        memory = NULL;
        CloseClipboard();
        ok = false;
        goto cleanup;
    }
    CloseClipboard();  /* clipboard owns `memory` now */

    /* Reads also open the clipboard internally — same transient-contention
     * retry as above. */
    PlatformClipboardResult result = PLATFORM_CLIPBOARD_EMPTY;
    for (int attempt = 0; attempt < 20; attempt++) {
        if (attempt > 0) Sleep(25);
        free(text);
        text = NULL;
        result = platform_clipboard_get_text_alloc(platform, &text);
        if (result == PLATFORM_CLIPBOARD_READY && text != NULL) break;
    }
    if (result != PLATFORM_CLIPBOARD_READY || text == NULL) {
        record_failure("platform_clipboard_get_text_alloc did not return text");
        ok = false;
    } else {
        if (strlen(text) > region_units) {
            record_failure("clipboard read ran past the GlobalAlloc region");
            ok = false;
        }
        if (strncmp(text, "unterminated", 12) != 0) {
            record_failure("clipboard read lost the leading text");
            ok = false;
        }
    }
    free(text);
    text = NULL;

    memset(buf, 0, sizeof(buf));
    {
        bool got = false;
        for (int attempt = 0; attempt < 20 && !got; attempt++) {
            if (attempt > 0) Sleep(25);
            got = platform_clipboard_get_text(platform, buf, sizeof(buf));
        }
        if (!got) {
            record_failure("platform_clipboard_get_text failed");
            ok = false;
        } else {
            if (strlen(buf) > region_units) {
                record_failure("buffered clipboard read ran past the region");
                ok = false;
            }
            if (strncmp(buf, "unterminated", 12) != 0) {
                record_failure("buffered clipboard read lost the leading text");
                ok = false;
            }
        }
    }

cleanup:
    free(text);
    platform_destroy(platform);
    if (!ok) return;
}

TEST(gamepad_init_is_idempotent)
{
    /* R570: a second gamepad_init used to overwrite g_pad.dll and leak the
     * xinput HMODULE. Repeated init/shutdown must be harmless no-ops
     * (platform_destroy below shuts down once more, also harmlessly). */
    PlatformConfig config = {320, 240, "break pad"};
    Platform *platform = platform_create(&config);

    if (platform == NULL) {
        record_failure("platform_create returned NULL");
        return;
    }
    gamepad_init();   /* platform_create already initialized: must be no-op */
    gamepad_init();
    gamepad_shutdown();
    gamepad_shutdown();
    platform_destroy(platform);
}

TEST(media_context_reports_windows_preferences_when_queryable)
{
    PlatformConfig config = {320, 240, "break media"};
    Platform *platform = platform_create(&config);
    PlatformMediaContext media;
    HKEY personalize = NULL;
    DWORD expected_theme = 0;
    DWORD expected_theme_size = sizeof(expected_theme);
    DWORD expected_theme_type = 0;
    bool theme_queryable =
        RegOpenKeyExW(HKEY_CURRENT_USER,
                      L"Software\\Microsoft\\Windows\\CurrentVersion\\Themes\\Personalize",
                      0, KEY_READ, &personalize) == ERROR_SUCCESS &&
        RegQueryValueExW(personalize, L"AppsUseLightTheme", NULL,
                         &expected_theme_type, (LPBYTE)&expected_theme,
                         &expected_theme_size) == ERROR_SUCCESS &&
        expected_theme_type == REG_DWORD &&
        expected_theme_size == sizeof(expected_theme);
    BOOL animations_enabled = TRUE;
    bool reduce_motion_queryable;

    if (platform == NULL) {
        record_failure("platform_create returned NULL");
        return;
    }
    reduce_motion_queryable = SystemParametersInfoW(
        SPI_GETCLIENTAREAANIMATION, 0, &animations_enabled, 0) != FALSE;
    if (!platform_get_media_context(platform, &media)) {
        record_failure("platform_get_media_context failed");
    } else {
        if (theme_queryable &&
            ((media.known & PLATFORM_MEDIA_KNOWN_COLOR_SCHEME) == 0u ||
             media.prefers_dark != (expected_theme == 0u))) {
            record_failure("Windows color-scheme media fact is incorrect");
        }
        if (reduce_motion_queryable &&
            ((media.known & PLATFORM_MEDIA_KNOWN_REDUCED_MOTION) == 0u ||
             media.prefers_reduced_motion != (animations_enabled == FALSE))) {
            record_failure("Windows reduced-motion media fact is incorrect");
        }
    }
    if (personalize != NULL) RegCloseKey(personalize);
    platform_destroy(platform);
}

TEST(media_context_pointer_capabilities_follow_windows_metrics)
{
    PlatformConfig config = {320, 240, "break pointer media"};
    Platform *platform = platform_create(&config);
    PlatformMediaContext media;
    bool mouse_present;
    bool touch_present = false;

    if (platform == NULL) {
        record_failure("platform_create returned NULL");
        return;
    }
    mouse_present = GetSystemMetrics(SM_MOUSEPRESENT) != 0;
#ifdef SM_DIGITIZER
    touch_present = (GetSystemMetrics(SM_DIGITIZER) &
                     (NID_INTEGRATED_TOUCH | NID_EXTERNAL_TOUCH)) != 0;
#endif
    if (!platform_get_media_context(platform, &media)) {
        record_failure("platform_get_media_context failed");
    } else {
        if ((media.known & PLATFORM_MEDIA_KNOWN_POINTER) == 0u ||
            (media.known & PLATFORM_MEDIA_KNOWN_ANY_POINTER) == 0u) {
            record_failure("Windows pointer facts are not known");
        }
        if (mouse_present !=
            ((media.capabilities & PLATFORM_MEDIA_CAP_POINTER_FINE) != 0u) ||
            mouse_present !=
            ((media.capabilities & PLATFORM_MEDIA_CAP_HOVER) != 0u)) {
            record_failure("Windows mouse capabilities are incorrect");
        }
        if (touch_present !=
            ((media.capabilities & PLATFORM_MEDIA_CAP_ANY_POINTER_COARSE) != 0u)) {
            record_failure("Windows touch capability is incorrect");
        }
    }
    platform_destroy(platform);
}

TEST(media_context_hdr_capability_has_explicit_knowledge)
{
    PlatformConfig config = {320, 240, "break hdr media"};
    Platform *platform = platform_create(&config);
    PlatformMediaContext media;

    if (platform == NULL) {
        record_failure("platform_create returned NULL");
        return;
    }
    if (!platform_get_media_context(platform, &media)) {
        record_failure("platform_get_media_context failed");
    } else if ((media.capabilities & PLATFORM_MEDIA_CAP_HDR) != 0u &&
               (media.known & PLATFORM_MEDIA_KNOWN_HDR) == 0u) {
        record_failure("Windows HDR capability is not marked known");
    }
    platform_destroy(platform);
}

TEST(media_context_cache_invalidates_on_settings_change)
{
    PlatformConfig config = {320, 240, "break media invalidation"};
    Platform *platform = platform_create(&config);
    HWND hwnd;
    PlatformMediaContext media;
    u64 before;
    u64 after;

    if (platform == NULL) {
        record_failure("platform_create returned NULL");
        return;
    }
    hwnd = (HWND)platform_window_native(platform);
    before = platform_get_media_generation(platform);
    if (!platform_get_media_context(platform, &media)) {
        record_failure("initial platform_get_media_context failed");
    }
    /* WM_SETTINGCHANGE must be delivered synchronously: recent Windows
     * rejects PostMessage for it with ERROR_MESSAGE_SYNC_ONLY. */
    SendMessageW(hwnd, WM_SETTINGCHANGE, 0, 0);
    (void)platform_poll(platform);
    after = platform_get_media_generation(platform);
    if (after <= before) {
        record_failure("settings change did not invalidate media generation");
    }
    if (!platform_get_media_context(platform, &media)) {
        record_failure("refreshed platform_get_media_context failed");
    }
    platform_destroy(platform);
}

TEST(malformed_dpi_change_message_is_ignored)
{
    PlatformConfig config = {320, 240, "break malformed dpi"};
    Platform *platform = platform_create(&config);
    HWND hwnd;
    u32 width = 0;
    u32 height = 0;

    if (platform == NULL) {
        record_failure("platform_create returned NULL");
        return;
    }
    hwnd = (HWND)platform_window_native(platform);
    /* WM_DPICHANGED must be delivered synchronously: recent Windows
     * rejects PostMessage for it with ERROR_MESSAGE_SYNC_ONLY. */
    SendMessageW(hwnd, WM_DPICHANGED, 0, 0);
    (void)platform_poll(platform);
    platform_get_size(platform, &width, &height);
    if (width == 0u || height == 0u) {
        record_failure("malformed DPI message corrupted window size");
    }
    platform_destroy(platform);
}

TEST(ime_enable_disable_round_trips_through_imm32)
{
    PlatformConfig config = {320, 240, "break ime roundtrip"};
    Platform *platform = platform_create(&config);

    if (platform == NULL) {
        record_failure("platform_create returned NULL");
        return;
    }
    if (platform_ime_is_enabled(platform)) {
        record_failure("IME should be disabled by default");
    }
    /* Enable -> disable -> enable exercises both ImmAssociateContext paths
     * (detach on disable, re-attach on re-enable); a fault in either would
     * take the process down before the destroy. */
    platform_ime_set_enabled(platform, true);
    if (!platform_ime_is_enabled(platform)) {
        record_failure("platform_ime_is_enabled false after enable");
    }
    (void)platform_poll(platform);
    platform_ime_set_enabled(platform, false);
    if (platform_ime_is_enabled(platform)) {
        record_failure("platform_ime_is_enabled true after disable");
    }
    (void)platform_poll(platform);
    platform_ime_set_enabled(platform, true);
    if (!platform_ime_is_enabled(platform)) {
        record_failure("platform_ime_is_enabled false after re-enable");
    }
    (void)platform_poll(platform);
    platform_destroy(platform);
}

TEST(ime_surrounding_and_spot_accept_cjk_and_hostile_input)
{
    PlatformConfig config = {320, 240, "break ime smoke"};
    Platform *platform = platform_create(&config);

    if (platform == NULL) {
        record_failure("platform_create returned NULL");
        return;
    }
    platform_ime_set_enabled(platform, true);
    /* Valid CJK context with mid-string cursor and anchor. */
    platform_ime_set_surrounding(platform,
                                 "\xE4\xB8\xAD\xE6\x96\x87 mixed \xE6\x96\x87\xE6\x9C\xAC",
                                 4, 4);
    /* Hostile input: truncated UTF-8 sequence + negative cursor/anchor must
     * be clamped/rejected by the surrounding helper without faulting. */
    platform_ime_set_surrounding(platform, "\xE4\xB8", -1, -1);
    platform_ime_set_surrounding(platform, NULL, 0, 0);
    /* Candidate/composition window placement through the real HIMC. */
    platform_ime_set_spot(platform, 100, 200);
    platform_ime_set_spot(platform, -5, 1 << 20);
    (void)platform_poll(platform);
    platform_destroy(platform);
}

TEST(ime_api_null_platform_is_rejected_without_fault)
{
    platform_ime_set_enabled(NULL, true);
    if (platform_ime_is_enabled(NULL)) {
        record_failure("platform_ime_is_enabled(NULL) must be false");
    }
    platform_ime_set_surrounding(NULL, "text", 1, 1);
    platform_ime_set_spot(NULL, 1, 2);
}

/* ---- Borderless fullscreen (FS2) ---- */

static WNDPROC g_fs_prev_proc;
static int g_fs_wm_size_count;

static LRESULT CALLBACK fs_counting_proc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    if (msg == WM_SIZE) g_fs_wm_size_count++;
    return CallWindowProcW(g_fs_prev_proc, hwnd, msg, wp, lp);
}

static void fs_count_wm_size(HWND hwnd)
{
    g_fs_wm_size_count = 0;
    g_fs_prev_proc = (WNDPROC)SetWindowLongPtrW(hwnd, GWLP_WNDPROC,
                                                (LONG_PTR)fs_counting_proc);
}

static void fs_uncount_wm_size(HWND hwnd)
{
    if (g_fs_prev_proc != NULL)
        SetWindowLongPtrW(hwnd, GWLP_WNDPROC, (LONG_PTR)g_fs_prev_proc);
    g_fs_prev_proc = NULL;
}

static RECT fs_monitor_rect(HWND hwnd)
{
    MONITORINFO mi;
    memset(&mi, 0, sizeof(mi));
    mi.cbSize = sizeof(mi);
    GetMonitorInfoW(MonitorFromWindow(hwnd, MONITOR_DEFAULTTONEAREST), &mi);
    return mi.rcMonitor;
}

static void fs_pump(Platform *platform)
{
    for (int i = 0; i < 3; i++) (void)platform_poll(platform);
}

/* Fullscreen invariants: no frame, not topmost, client == window == monitor,
 * and the platform sizes report the monitor after a poll. */
static bool fs_expect_fullscreen(Platform *platform, HWND hwnd)
{
    RECT mon = fs_monitor_rect(hwnd);
    RECT client;
    RECT window;
    LONG style = GetWindowLongW(hwnd, GWL_STYLE);
    LONG exstyle = GetWindowLongW(hwnd, GWL_EXSTYLE);
    u32 mw = (u32)(mon.right - mon.left);
    u32 mh = (u32)(mon.bottom - mon.top);
    u32 w = 0u, h = 0u;
    bool ok = true;

    if ((style & (WS_CAPTION | WS_THICKFRAME)) != 0) {
        record_failure("fullscreen window still has WS_CAPTION/WS_THICKFRAME");
        ok = false;
    }
    if ((exstyle & WS_EX_TOPMOST) != 0) {
        record_failure("fullscreen window must stay HWND_TOP, not TOPMOST");
        ok = false;
    }
    GetClientRect(hwnd, &client);
    GetWindowRect(hwnd, &window);
    if ((u32)(client.right - client.left) != mw ||
        (u32)(client.bottom - client.top) != mh) {
        record_failure("fullscreen client rect is not the monitor size");
        ok = false;
    }
    if (window.left != mon.left || window.top != mon.top ||
        window.right != mon.right || window.bottom != mon.bottom) {
        record_failure("fullscreen window rect is not the monitor rect");
        ok = false;
    }
    if (platform_get_window_mode(platform) != PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN) {
        record_failure("platform_get_window_mode is not BORDERLESS_FULLSCREEN");
        ok = false;
    }
    fs_pump(platform);
    platform_get_size(platform, &w, &h);
    if (w != mw || h != mh) {
        record_failure("platform_get_size does not report the monitor size");
        ok = false;
    }
    platform_get_drawable_size(platform, &w, &h);
    if (w != mw || h != mh) {
        record_failure("platform_get_drawable_size does not report the monitor size");
        ok = false;
    }
    return ok;
}

TEST(fullscreen_enter_and_leave_restores_style_and_placement)
{
    PlatformConfig config = {320, 240, "break fullscreen"};
    Platform *platform = platform_create(&config);
    HWND hwnd;
    LONG style_before;
    WINDOWPLACEMENT before;
    WINDOWPLACEMENT after;
    u32 w = 0u, h = 0u;

    if (platform == NULL) {
        record_failure("platform_create returned NULL");
        return;
    }
    hwnd = (HWND)platform_window_native(platform);
    fs_pump(platform);
    if (platform_get_window_mode(platform) != PLATFORM_WINDOW_MODE_WINDOWED)
        record_failure("a new window must start WINDOWED");
    style_before = GetWindowLongW(hwnd, GWL_STYLE);
    memset(&before, 0, sizeof(before));
    before.length = sizeof(before);
    GetWindowPlacement(hwnd, &before);

    fs_count_wm_size(hwnd);
    if (!platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN))
        record_failure("platform_set_window_mode(BORDERLESS) returned false");
    if (g_fs_wm_size_count != 1)
        record_failure("entering fullscreen must resize exactly once (one SetWindowPos)");
    (void)fs_expect_fullscreen(platform, hwnd);

    g_fs_wm_size_count = 0;
    if (!platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_WINDOWED))
        record_failure("platform_set_window_mode(WINDOWED) returned false");
    if (g_fs_wm_size_count != 1)
        record_failure("leaving fullscreen must resize exactly once");
    fs_uncount_wm_size(hwnd);

    if (platform_get_window_mode(platform) != PLATFORM_WINDOW_MODE_WINDOWED)
        record_failure("platform_get_window_mode is not WINDOWED after leaving");
    if (GetWindowLongW(hwnd, GWL_STYLE) != style_before)
        record_failure("leaving fullscreen did not restore GWL_STYLE");
    memset(&after, 0, sizeof(after));
    after.length = sizeof(after);
    GetWindowPlacement(hwnd, &after);
    if (memcmp(&after.rcNormalPosition, &before.rcNormalPosition,
               sizeof(RECT)) != 0 || after.showCmd != before.showCmd)
        record_failure("leaving fullscreen did not restore WINDOWPLACEMENT");
    fs_pump(platform);
    platform_get_size(platform, &w, &h);
    if (w != 320u || h != 240u)
        record_failure("platform_get_size is not the windowed size after leaving");
    platform_destroy(platform);
}

TEST(fullscreen_round_trip_keeps_window_maximized)
{
    PlatformConfig config = {320, 240, "break fullscreen maximized"};
    Platform *platform = platform_create(&config);
    HWND hwnd;
    WINDOWPLACEMENT before;
    WINDOWPLACEMENT after;
    RECT max_rect;
    RECT rect;

    if (platform == NULL) {
        record_failure("platform_create returned NULL");
        return;
    }
    hwnd = (HWND)platform_window_native(platform);
    ShowWindow(hwnd, SW_MAXIMIZE);
    fs_pump(platform);
    if (!IsZoomed(hwnd)) {
        record_failure("ShowWindow(SW_MAXIMIZE) did not maximize the test window");
        platform_destroy(platform);
        return;
    }
    GetWindowRect(hwnd, &max_rect);
    memset(&before, 0, sizeof(before));
    before.length = sizeof(before);
    GetWindowPlacement(hwnd, &before);

    if (!platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN))
        record_failure("platform_set_window_mode(BORDERLESS) returned false");
    (void)fs_expect_fullscreen(platform, hwnd);
    if (IsZoomed(hwnd))
        record_failure("fullscreen window must not report maximized");

    if (!platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_WINDOWED))
        record_failure("platform_set_window_mode(WINDOWED) returned false");
    fs_pump(platform);
    if (!IsZoomed(hwnd))
        record_failure("maximized window came back un-maximized");
    if ((GetWindowLongW(hwnd, GWL_STYLE) & (WS_CAPTION | WS_THICKFRAME)) !=
        (WS_CAPTION | WS_THICKFRAME))
        record_failure("restored maximized window lost its frame style");
    GetWindowRect(hwnd, &rect);
    if (memcmp(&rect, &max_rect, sizeof(RECT)) != 0)
        record_failure("restored maximized window rect differs from before");
    memset(&after, 0, sizeof(after));
    after.length = sizeof(after);
    GetWindowPlacement(hwnd, &after);
    if (memcmp(&after.rcNormalPosition, &before.rcNormalPosition, sizeof(RECT)) != 0)
        record_failure("maximized round trip lost the restored (normal) rect");

    ShowWindow(hwnd, SW_RESTORE);
    fs_pump(platform);
    if (IsZoomed(hwnd))
        record_failure("SW_RESTORE after the round trip left the window maximized");
    platform_destroy(platform);
}

TEST(fullscreen_set_is_idempotent_and_toggle_round_trips)
{
    PlatformConfig config = {320, 240, "break fullscreen idempotent"};
    Platform *platform = platform_create(&config);
    HWND hwnd;
    LONG style_before;

    if (platform == NULL) {
        record_failure("platform_create returned NULL");
        return;
    }
    hwnd = (HWND)platform_window_native(platform);
    fs_pump(platform);
    style_before = GetWindowLongW(hwnd, GWL_STYLE);

    fs_count_wm_size(hwnd);
    if (!platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_WINDOWED))
        record_failure("set(WINDOWED) while windowed must succeed");
    if (g_fs_wm_size_count != 0)
        record_failure("set(WINDOWED) while windowed must not touch the window");
    (void)platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN);
    g_fs_wm_size_count = 0;
    if (!platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN))
        record_failure("repeated set(BORDERLESS) must succeed");
    if (g_fs_wm_size_count != 0)
        record_failure("repeated set(BORDERLESS) must not resize again");
    fs_uncount_wm_size(hwnd);
    (void)fs_expect_fullscreen(platform, hwnd);
    if (platform_set_window_mode(platform, (PlatformWindowMode)42))
        record_failure("an invalid mode must be rejected");
    if (platform_get_window_mode(platform) != PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN)
        record_failure("an invalid mode request changed the mode");

    platform_toggle_fullscreen(platform);
    if (platform_get_window_mode(platform) != PLATFORM_WINDOW_MODE_WINDOWED)
        record_failure("toggle from fullscreen did not go WINDOWED");
    if (GetWindowLongW(hwnd, GWL_STYLE) != style_before)
        record_failure("toggle back did not restore GWL_STYLE");
    platform_toggle_fullscreen(platform);
    (void)fs_expect_fullscreen(platform, hwnd);
    platform_toggle_fullscreen(platform);
    if (platform_get_window_mode(platform) != PLATFORM_WINDOW_MODE_WINDOWED)
        record_failure("second toggle round trip did not end WINDOWED");
    platform_destroy(platform);
}

TEST(start_fullscreen_creates_the_window_fullscreen)
{
    PlatformConfig config = {320, 240, "break start fullscreen"};
    Platform *platform;
    HWND hwnd;
    LONG style;
    WINDOWPLACEMENT wp;
    u32 w = 0u, h = 0u;

    config.start_fullscreen = true;
    platform = platform_create(&config);
    if (platform == NULL) {
        record_failure("platform_create(start_fullscreen) returned NULL");
        return;
    }
    hwnd = (HWND)platform_window_native(platform);
    if (!IsWindowVisible(hwnd))
        record_failure("start_fullscreen window is not visible");
    (void)fs_expect_fullscreen(platform, hwnd);

    if (!platform_set_window_mode(platform, PLATFORM_WINDOW_MODE_WINDOWED))
        record_failure("leaving start_fullscreen returned false");
    style = GetWindowLongW(hwnd, GWL_STYLE);
    if ((style & WS_OVERLAPPEDWINDOW) != WS_OVERLAPPEDWINDOW)
        record_failure("leaving start_fullscreen did not give a framed window");
    memset(&wp, 0, sizeof(wp));
    wp.length = sizeof(wp);
    GetWindowPlacement(hwnd, &wp);
    if (wp.showCmd != SW_SHOWNORMAL)
        record_failure("leaving start_fullscreen did not give a normal window");
    fs_pump(platform);
    platform_get_size(platform, &w, &h);
    if (w != 320u || h != 240u)
        record_failure("leaving start_fullscreen did not give the configured size");
    platform_destroy(platform);
}

TEST(start_fullscreen_hidden_window_stays_hidden_until_show)
{
    PlatformConfig config = {320, 240, "break start fullscreen hidden"};
    Platform *platform;
    HWND hwnd;

    config.hide_window_until_first_frame = true;
    config.start_fullscreen = true;
    platform = platform_create(&config);
    if (platform == NULL) {
        record_failure("platform_create(start_fullscreen, hidden) returned NULL");
        return;
    }
    hwnd = (HWND)platform_window_native(platform);
    if (IsWindowVisible(hwnd))
        record_failure("hidden start_fullscreen window became visible before show");
    if (platform_get_window_mode(platform) != PLATFORM_WINDOW_MODE_BORDERLESS_FULLSCREEN)
        record_failure("hidden start_fullscreen window is not BORDERLESS_FULLSCREEN");
    platform_window_show(platform);
    (void)fs_expect_fullscreen(platform, hwnd);
    platform_destroy(platform);
}

TEST_MAIN_BEGIN()
    RUN_TEST(platform_create_rejects_invalid_configuration_before_native_calls);
    RUN_TEST(invalid_utf8_title_is_rejected_without_creating_a_window);
    RUN_TEST(real_window_preserves_title_size_and_destroys_cleanly);
    RUN_TEST(alt_f4_requests_close_through_default_system_key_handling);
    RUN_TEST(relative_mouse_mode_ignores_absolute_move_deltas);
    RUN_TEST(clipboard_read_bounds_unterminated_unicode_text);
    RUN_TEST(gamepad_init_is_idempotent);
    RUN_TEST(media_context_reports_windows_preferences_when_queryable);
    RUN_TEST(media_context_pointer_capabilities_follow_windows_metrics);
    RUN_TEST(media_context_hdr_capability_has_explicit_knowledge);
    RUN_TEST(media_context_cache_invalidates_on_settings_change);
    RUN_TEST(malformed_dpi_change_message_is_ignored);
    RUN_TEST(ime_enable_disable_round_trips_through_imm32);
    RUN_TEST(ime_surrounding_and_spot_accept_cjk_and_hostile_input);
    RUN_TEST(ime_api_null_platform_is_rejected_without_fault);
    RUN_TEST(fullscreen_enter_and_leave_restores_style_and_placement);
    RUN_TEST(fullscreen_round_trip_keeps_window_maximized);
    RUN_TEST(fullscreen_set_is_idempotent_and_toggle_round_trips);
    RUN_TEST(start_fullscreen_creates_the_window_fullscreen);
    RUN_TEST(start_fullscreen_hidden_window_stays_hidden_until_show);
TEST_MAIN_END()
