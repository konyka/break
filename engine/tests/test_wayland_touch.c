#include "test_framework.h"
#include <platform/wayland_touch.h>

TEST(wayland_down_move_up_and_outside_up_lifecycle)
{
    InputExtended input;
    struct wl_surface *target = (struct wl_surface *)(uintptr_t)1;
    input_extended_init(&input);
    ASSERT_EQ(wayland_touch_down(&input, 100, 200, target, target, 7,
                                 wl_fixed_from_int(20), wl_fixed_from_int(40),
                                 100, 50), INPUT_EXT_OK);
    ASSERT_EQ(wayland_touch_motion(&input, 100, 200, 7,
                                   wl_fixed_from_int(-5), wl_fixed_from_int(40),
                                   101, 60), INPUT_EXT_INVALID);
    ASSERT_EQ(input.touch_count, 1u);
    ASSERT_EQ(wayland_touch_up(&input, 7, 102, 70), INPUT_EXT_OK);
    ASSERT_EQ(input.touch_count, 0u);
    ASSERT_EQ(input.touch_events[input.touch_event_count - 1u].phase,
              INPUT_TOUCH_RELEASE);
}

TEST(wayland_same_frame_id_reuse_and_cancel)
{
    InputExtended input;
    struct wl_surface *target = (struct wl_surface *)(uintptr_t)1;
    InputTouchId first;
    input_extended_init(&input);
    ASSERT_EQ(wayland_touch_down(&input, 100, 100, target, target, 3,
                                 wl_fixed_from_int(10), wl_fixed_from_int(10),
                                 1, 100), INPUT_EXT_OK);
    first = input.touches[0].id;
    ASSERT_EQ(wayland_touch_up(&input, 3, 2, 110), INPUT_EXT_OK);
    ASSERT_EQ(wayland_touch_down(&input, 100, 100, target, target, 3,
                                 wl_fixed_from_int(20), wl_fixed_from_int(20),
                                 3, 120), INPUT_EXT_OK);
    ASSERT_NEQ(input.touches[0].id, first);
    ASSERT_EQ(input.touch_event_count, 3u);
    ASSERT_EQ(wayland_touch_cancel(&input, 130), INPUT_EXT_OK);
    ASSERT_EQ(input.touch_count, 0u);
    ASSERT_EQ(input.touch_events[input.touch_event_count - 1u].phase,
              INPUT_TOUCH_CANCEL);
}

TEST(wayland_other_surface_down_is_ignored)
{
    InputExtended input;
    struct wl_surface *target = (struct wl_surface *)(uintptr_t)1;
    struct wl_surface *other = (struct wl_surface *)(uintptr_t)2;
    input_extended_init(&input);
    ASSERT_EQ(wayland_touch_down(&input, 100, 100, target, other, 3,
                                 wl_fixed_from_int(10), wl_fixed_from_int(10),
                                 1, 100), INPUT_EXT_INVALID);
    ASSERT_EQ(input.touch_count, 0u);
    ASSERT_EQ(input.touch_event_count, 0u);
}

TEST(wayland_dispatch_time_unifies_epochs_and_u32_wrap)
{
    InputExtended input;
    struct wl_surface *target = (struct wl_surface *)(uintptr_t)1;
    input_extended_init(&input);
    ASSERT_EQ(wayland_touch_down(&input, 100, 100, target, target, 4,
                                 wl_fixed_from_int(10), wl_fixed_from_int(10),
                                 UINT32_MAX - 2u, 1000), INPUT_EXT_OK);
    ASSERT_EQ(wayland_touch_up(&input, 4, 2u, 1300), INPUT_EXT_OK);
    ASSERT_EQ(input.touch_events[0].time_ms, (u64)1000);
    ASSERT_EQ(input.touch_events[1].time_ms, (u64)1300);
    ASSERT_EQ(input.gesture_count, 1u);
    ASSERT_EQ(input.gestures[0].type, INPUT_GESTURE_TAP);

    input_extended_new_frame(&input);
    ASSERT_EQ(wayland_touch_down(&input, 100, 100, target, target, 5,
                                 wl_fixed_from_int(10), wl_fixed_from_int(10),
                                 10u, 5000), INPUT_EXT_OK);
    input_extended_update(&input, 5600);
    ASSERT_EQ(input.gesture_count, 1u);
    ASSERT_EQ(input.gestures[0].type, INPUT_GESTURE_LONG_PRESS);
}

int main(void)
{
    printf("=== Running Tests ===\n");
    RUN_TEST(wayland_down_move_up_and_outside_up_lifecycle);
    RUN_TEST(wayland_same_frame_id_reuse_and_cancel);
    RUN_TEST(wayland_other_surface_down_is_ignored);
    RUN_TEST(wayland_dispatch_time_unifies_epochs_and_u32_wrap);
    printf("\n=== Results: %d passed, %d failed, %d total ===\n",
           g_test_pass, g_test_fail, g_test_count);
    return g_test_fail > 0 ? 1 : 0;
}
