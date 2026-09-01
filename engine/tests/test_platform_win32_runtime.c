#include "test_framework.h"

#include "platform/platform.h"
#include "platform/gamepad_linux.h"  /* shared gamepad_init/shutdown prototypes */

#include <windows.h>

static void record_failure(const char *message)
{
    printf("  FAIL: %s\n", message);
    g_test_fail++;
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

TEST_MAIN_BEGIN()
    RUN_TEST(invalid_utf8_title_is_rejected_without_creating_a_window);
    RUN_TEST(real_window_preserves_title_size_and_destroys_cleanly);
    RUN_TEST(alt_f4_requests_close_through_default_system_key_handling);
    RUN_TEST(relative_mouse_mode_ignores_absolute_move_deltas);
    RUN_TEST(clipboard_read_bounds_unterminated_unicode_text);
    RUN_TEST(gamepad_init_is_idempotent);
TEST_MAIN_END()
