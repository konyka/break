#include "test_framework.h"
#include <platform/x11_touch.h>

static XIDeviceEvent native_touch(Window window, int sourceid, int detail,
                                  double x, double y, Time time)
{
    XIDeviceEvent event;
    memset(&event, 0, sizeof(event));
    event.event = window;
    event.sourceid = sourceid;
    event.detail = detail;
    event.event_x = x;
    event.event_y = y;
    event.time = time;
    return event;
}

TEST(x11_outside_move_and_up_still_release)
{
    InputExtended input;
    Window window = 11;
    XIDeviceEvent event;
    input_extended_init(&input);
    event = native_touch(window, 2, 7, 20, 40, 100);
    ASSERT_EQ(x11_touch_event(&input, 100, 200, window, XI_TouchBegin,
                              &event, 50), INPUT_EXT_OK);
    event = native_touch(window, 2, 7, -5, 40, 101);
    ASSERT_EQ(x11_touch_event(&input, 100, 200, window, XI_TouchUpdate,
                              &event, 60), INPUT_EXT_INVALID);
    ASSERT_EQ(input.touch_count, 1u);
    event = native_touch(window, 2, 7, -1000, -1000, 102);
    ASSERT_EQ(x11_touch_event(&input, 100, 200, window, XI_TouchEnd,
                              &event, 70), INPUT_EXT_OK);
    ASSERT_EQ(input.touch_count, 0u);
    ASSERT_EQ(input.touch_events[input.touch_event_count - 1u].phase,
              INPUT_TOUCH_RELEASE);

    event = native_touch(window, 2, 8, 20, 40, 103);
    ASSERT_EQ(x11_touch_event(&input, 100, 200, window, XI_TouchBegin,
                              &event, 80), INPUT_EXT_OK);
    event = native_touch(window, 2, 8, 1000, 1000, 104);
    ASSERT_EQ(x11_touch_event(&input, 100, 200, window, XI_TouchEnd,
                              &event, 90), INPUT_EXT_OK);
    ASSERT_EQ(input.touch_count, 0u);
}

TEST(x11_same_frame_id_reuse_preserves_generations)
{
    InputExtended input;
    Window window = 12;
    XIDeviceEvent event;
    InputTouchId first, second;
    input_extended_init(&input);
    event = native_touch(window, 3, 5, 10, 10, 1);
    ASSERT_EQ(x11_touch_event(&input, 100, 100, window, XI_TouchBegin,
                              &event, 100), INPUT_EXT_OK);
    first = input.touches[0].id;
    event = native_touch(window, 3, 5, -100, -100, 2);
    ASSERT_EQ(x11_touch_event(&input, 100, 100, window, XI_TouchEnd,
                              &event, 110), INPUT_EXT_OK);
    event = native_touch(window, 3, 5, 20, 20, 3);
    ASSERT_EQ(x11_touch_event(&input, 100, 100, window, XI_TouchBegin,
                              &event, 120), INPUT_EXT_OK);
    second = input.touches[0].id;
    ASSERT_NEQ(first, second);
    ASSERT_EQ(input.touch_event_count, 3u);
    ASSERT_EQ(input.touch_events[1].id, first);
    ASSERT_EQ(input.touch_events[2].id, second);
}

TEST(x11_sourceid_and_detail_form_distinct_sources)
{
    InputExtended input;
    Window window = 13;
    XIDeviceEvent first;
    XIDeviceEvent second;
    i64 first_source;
    input_extended_init(&input);
    first = native_touch(window, 1, 9, 10, 10, 1);
    second = native_touch(window, 2, 9, 20, 20, 1);
    ASSERT_EQ(x11_touch_event(&input, 100, 100, window, XI_TouchBegin,
                              &first, 100), INPUT_EXT_OK);
    ASSERT_EQ(x11_touch_event(&input, 100, 100, window, XI_TouchBegin,
                              &second, 100), INPUT_EXT_OK);
    ASSERT_EQ(input.touch_count, 2u);
    first_source = input.touch_events[0].source_id;
    ASSERT_NEQ(first_source, input.touch_events[1].source_id);
    ASSERT_EQ(x11_touch_event(&input, 100, 100, window, XI_TouchEnd,
                              &first, 110), INPUT_EXT_OK);
    ASSERT_EQ(input.touch_count, 1u);
    ASSERT_EQ(input.touch_events[input.touch_event_count - 1u].source_id,
              first_source);
    ASSERT_EQ(x11_touch_event(&input, 100, 100, window, XI_TouchEnd,
                              &second, 120), INPUT_EXT_OK);
    ASSERT_EQ(input.touch_count, 0u);
}

TEST(x11_dispatch_time_unifies_epochs_and_u32_wrap)
{
    InputExtended input;
    Window window = 14;
    XIDeviceEvent event;
    input_extended_init(&input);
    event = native_touch(window, 1, 1, 10, 10, (Time)(UINT32_MAX - 2u));
    ASSERT_EQ(x11_touch_event(&input, 100, 100, window, XI_TouchBegin,
                              &event, 1000), INPUT_EXT_OK);
    event = native_touch(window, 1, 1, 10, 10, (Time)2u);
    ASSERT_EQ(x11_touch_event(&input, 100, 100, window, XI_TouchEnd,
                              &event, 1300), INPUT_EXT_OK);
    ASSERT_EQ(input.touch_events[0].time_ms, (u64)1000);
    ASSERT_EQ(input.touch_events[1].time_ms, (u64)1300);
    ASSERT_EQ(input.gesture_count, 1u);
    ASSERT_EQ(input.gestures[0].type, INPUT_GESTURE_TAP);

    input_extended_new_frame(&input);
    event = native_touch(window, 1, 2, 10, 10, (Time)10u);
    ASSERT_EQ(x11_touch_event(&input, 100, 100, window, XI_TouchBegin,
                              &event, 5000), INPUT_EXT_OK);
    input_extended_update(&input, 5600);
    ASSERT_EQ(input.gesture_count, 1u);
    ASSERT_EQ(input.gestures[0].type, INPUT_GESTURE_LONG_PRESS);
}

TEST(x11_cancel_path_clears_active_touch)
{
    InputExtended input;
    Window window = 15;
    XIDeviceEvent event;
    input_extended_init(&input);
    event = native_touch(window, 1, 1, 10, 10, 1);
    ASSERT_EQ(x11_touch_event(&input, 100, 100, window, XI_TouchBegin,
                              &event, 100), INPUT_EXT_OK);
    ASSERT_EQ(x11_touch_cancel(&input, 110), INPUT_EXT_OK);
    ASSERT_EQ(input.touch_count, 0u);
    ASSERT_EQ(input.touch_events[1].phase, INPUT_TOUCH_CANCEL);
}

int main(void)
{
    printf("=== Running Tests ===\n");
    RUN_TEST(x11_outside_move_and_up_still_release);
    RUN_TEST(x11_same_frame_id_reuse_preserves_generations);
    RUN_TEST(x11_sourceid_and_detail_form_distinct_sources);
    RUN_TEST(x11_dispatch_time_unifies_epochs_and_u32_wrap);
    RUN_TEST(x11_cancel_path_clears_active_touch);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
