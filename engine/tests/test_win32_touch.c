#include "test_framework.h"
#include <platform/win32_touch.h>

static TOUCHINPUT native_touch(DWORD id, DWORD flags, LONG x, LONG y)
{
    TOUCHINPUT touch;
    memset(&touch, 0, sizeof(touch));
    touch.dwID = id;
    touch.dwFlags = flags;
    touch.x = x;
    touch.y = y;
    return touch;
}

TEST(win32_outside_move_and_up_still_release)
{
    InputExtended input;
    POINT origin = {0, 0};
    TOUCHINPUT event;
    input_extended_init(&input);
    event = native_touch(7, TOUCHEVENTF_DOWN, 2000, 4000);
    ASSERT_EQ(win32_touch_message(&input, 100, 200, 1, &event, TRUE,
                                  origin, TRUE, 50), INPUT_EXT_OK);
    event = native_touch(7, TOUCHEVENTF_MOVE, -500, 4000);
    ASSERT_EQ(win32_touch_message(&input, 100, 200, 1, &event, TRUE,
                                  origin, TRUE, 60), INPUT_EXT_INVALID);
    ASSERT_EQ(input.touch_count, 1u);
    event = native_touch(7, TOUCHEVENTF_UP, -100000, -100000);
    ASSERT_EQ(win32_touch_message(&input, 100, 200, 1, &event, TRUE,
                                  origin, TRUE, 70), INPUT_EXT_OK);
    ASSERT_EQ(input.touch_count, 0u);
    ASSERT_EQ(input.touch_events[input.touch_event_count - 1u].phase,
              INPUT_TOUCH_RELEASE);

    event = native_touch(8, TOUCHEVENTF_DOWN, 2000, 4000);
    ASSERT_EQ(win32_touch_message(&input, 100, 200, 1, &event, TRUE,
                                  origin, TRUE, 80), INPUT_EXT_OK);
    event = native_touch(8, TOUCHEVENTF_UP, 100000, 100000);
    ASSERT_EQ(win32_touch_message(&input, 100, 200, 1, &event, TRUE,
                                  origin, TRUE, 90), INPUT_EXT_OK);
    ASSERT_EQ(input.touch_count, 0u);
}

TEST(win32_same_frame_id_reuse_and_cancel)
{
    InputExtended input;
    POINT origin = {0, 0};
    TOUCHINPUT events[3];
    InputTouchId first;
    input_extended_init(&input);
    events[0] = native_touch(3, TOUCHEVENTF_DOWN, 1000, 1000);
    events[1] = native_touch(3, TOUCHEVENTF_UP, -10000, -10000);
    events[2] = native_touch(3, TOUCHEVENTF_DOWN, 2000, 2000);
    ASSERT_EQ(win32_touch_message(&input, 100, 100, 3, events, TRUE,
                                  origin, TRUE, 100), INPUT_EXT_OK);
    ASSERT_EQ(input.touch_event_count, 3u);
    first = input.touch_events[0].id;
    ASSERT_NEQ(input.touch_events[2].id, first);
    ASSERT_EQ(win32_touch_cancel(&input, 110), INPUT_EXT_OK);
    ASSERT_EQ(input.touch_count, 0u);
    ASSERT_EQ(input.touch_events[input.touch_event_count - 1u].phase,
              INPUT_TOUCH_CANCEL);
}

TEST(win32_oversize_rejected_batch_cancels_terminal_and_active_ids)
{
    InputExtended input;
    POINT origin = {0, 0};
    TOUCHINPUT initial;
    TOUCHINPUT events[INPUT_MAX_TOUCH_EVENTS + 1u];
    input_extended_init(&input);
    initial = native_touch(1, TOUCHEVENTF_DOWN, 1000, 1000);
    ASSERT_EQ(win32_touch_message(&input, 100, 100, 1, &initial, TRUE,
                                  origin, TRUE, 100), INPUT_EXT_OK);
    for (u32 i = 0; i < INPUT_MAX_TOUCH_EVENTS + 1u; i++)
        events[i] = native_touch(i, TOUCHEVENTF_DOWN, 1000, 1000);
    events[0] = native_touch(1, TOUCHEVENTF_UP, 1000, 1000);
    ASSERT_EQ(win32_touch_message(&input, 100, 100,
                                  INPUT_MAX_TOUCH_EVENTS + 1u, events, TRUE,
                                  origin, TRUE, 110), INPUT_EXT_OVERLOAD);
    ASSERT_EQ(input.touch_count, 0u);
    ASSERT_EQ(input.dropped_touch_events, (u64)1);
    ASSERT_EQ(input.touch_events[input.touch_event_count - 1u].phase,
              INPUT_TOUCH_CANCEL);
}

TEST(win32_query_and_origin_failures_cancel_active_touch)
{
    InputExtended input;
    POINT origin = {0, 0};
    TOUCHINPUT event;
    input_extended_init(&input);
    event = native_touch(1, TOUCHEVENTF_DOWN, 1000, 1000);
    ASSERT_EQ(win32_touch_message(&input, 100, 100, 1, &event, TRUE,
                                  origin, TRUE, 100), INPUT_EXT_OK);
    event = native_touch(1, TOUCHEVENTF_UP, 1000, 1000);
    ASSERT_EQ(win32_touch_message(&input, 100, 100, 1, &event, FALSE,
                                  origin, TRUE, 110), INPUT_EXT_FAILED);
    ASSERT_EQ(input.touch_count, 0u);

    event = native_touch(2, TOUCHEVENTF_DOWN, 1000, 1000);
    ASSERT_EQ(win32_touch_message(&input, 100, 100, 1, &event, TRUE,
                                  origin, TRUE, 120), INPUT_EXT_OK);
    event = native_touch(2, TOUCHEVENTF_UP, 1000, 1000);
    ASSERT_EQ(win32_touch_message(&input, 100, 100, 1, &event, TRUE,
                                  origin, FALSE, 130), INPUT_EXT_FAILED);
    ASSERT_EQ(input.touch_count, 0u);
}

int main(void)
{
    printf("=== Running Tests ===\n");
    RUN_TEST(win32_outside_move_and_up_still_release);
    RUN_TEST(win32_same_frame_id_reuse_and_cancel);
    RUN_TEST(win32_oversize_rejected_batch_cancels_terminal_and_active_ids);
    RUN_TEST(win32_query_and_origin_failures_cancel_active_touch);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
