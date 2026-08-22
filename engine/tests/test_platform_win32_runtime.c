#include "test_framework.h"

#include "platform/platform.h"

#include <windows.h>

static void record_failure(const char *message)
{
    printf("  FAIL: %s\n", message);
    g_test_fail++;
}

TEST(invalid_utf8_title_is_rejected_without_creating_a_window)
{
    const char invalid_utf8[] = {(char)0xE4, (char)0xB8, '\0'};
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

TEST_MAIN_BEGIN()
    RUN_TEST(invalid_utf8_title_is_rejected_without_creating_a_window);
    RUN_TEST(real_window_preserves_title_size_and_destroys_cleanly);
TEST_MAIN_END()
