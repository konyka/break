/* R443: headless unit tests for the pure wl_output enumeration logic in
 * platform/wayland_output.h (slot management, registry-global dedup, mode
 * selection). No Wayland/compositor needed — the machine running these tests
 * may be an X11 session. */
#include "test_framework.h"
#include <platform/wayland_output.h>

TEST(add_up_to_capacity_then_full) {
    WaylandOutputList l;
    wl_out_list_init(&l);
    for (u32 i = 0; i < WAYLAND_OUTPUT_MAX; i++) {
        ASSERT_EQ(wl_out_add(&l, 100 + i), (i32)i);
    }
    ASSERT_EQ(l.count, WAYLAND_OUTPUT_MAX);
    /* Ninth distinct global does not fit. */
    ASSERT_EQ(wl_out_add(&l, 999), -1);
    ASSERT_EQ(l.count, WAYLAND_OUTPUT_MAX);
}

TEST(add_dedups_same_global_name) {
    WaylandOutputList l;
    wl_out_list_init(&l);
    ASSERT_EQ(wl_out_add(&l, 42), 0);
    ASSERT_EQ(wl_out_add(&l, 7), 1);
    /* Re-announcement of an already-bound global returns the same slot. */
    ASSERT_EQ(wl_out_add(&l, 42), 0);
    ASSERT_EQ(l.count, 2u);
}

TEST(find_slot_by_global_name) {
    WaylandOutputList l;
    wl_out_list_init(&l);
    wl_out_add(&l, 10);
    wl_out_add(&l, 20);
    ASSERT_EQ(wl_out_find(&l, 20), 1);
    ASSERT_EQ(wl_out_find(&l, 10), 0);
    ASSERT_EQ(wl_out_find(&l, 30), -1);
}

TEST(new_slot_defaults) {
    WaylandOutputList l;
    wl_out_list_init(&l);
    i32 s = wl_out_add(&l, 1);
    const WaylandOutputInfo *o = &l.items[s];
    ASSERT_EQ(o->global_name, 1u);
    ASSERT_EQ(o->width, 0u);
    ASSERT_EQ(o->height, 0u);
    ASSERT_EQ(o->scale, 1);
    ASSERT_FALSE(o->has_current_mode);
    ASSERT_FALSE(o->done);
}

TEST(mode_picks_largest_area_without_current) {
    WaylandOutputInfo o = {0};
    o.scale = 1;
    wl_out_accumulate_mode(&o, false, 1280, 720, 60000);
    ASSERT_EQ(o.width, 1280u);
    ASSERT_EQ(o.height, 720u);
    wl_out_accumulate_mode(&o, false, 1920, 1080, 60000);
    ASSERT_EQ(o.width, 1920u);
    ASSERT_EQ(o.height, 1080u);
    /* Smaller mode later must not shrink the selection. */
    wl_out_accumulate_mode(&o, false, 800, 600, 75000);
    ASSERT_EQ(o.width, 1920u);
    ASSERT_EQ(o.height, 1080u);
}

TEST(mode_tie_area_picks_higher_refresh) {
    WaylandOutputInfo o = {0};
    o.scale = 1;
    wl_out_accumulate_mode(&o, false, 1920, 1080, 60000);
    wl_out_accumulate_mode(&o, false, 1920, 1080, 144000);
    ASSERT_EQ(o.refresh_rate, 144u);
    /* Lower refresh at the same area must not downgrade. */
    wl_out_accumulate_mode(&o, false, 1920, 1080, 60000);
    ASSERT_EQ(o.refresh_rate, 144u);
}

TEST(mode_current_flag_wins_and_sticks) {
    WaylandOutputInfo o = {0};
    o.scale = 1;
    /* A bigger non-current mode arrives first... */
    wl_out_accumulate_mode(&o, false, 2560, 1440, 60000);
    /* ...then the compositor flags a smaller mode as current: it wins. */
    wl_out_accumulate_mode(&o, true, 1920, 1080, 59940);
    ASSERT_EQ(o.width, 1920u);
    ASSERT_EQ(o.height, 1080u);
    ASSERT_EQ(o.refresh_rate, 60u); /* 59940 mHz rounds to 60 Hz */
    ASSERT_TRUE(o.has_current_mode);
    /* Later non-current modes (even larger) must not override current. */
    wl_out_accumulate_mode(&o, false, 3840, 2160, 120000);
    ASSERT_EQ(o.width, 1920u);
    ASSERT_EQ(o.height, 1080u);
}

TEST(refresh_mhz_rounds_to_hz) {
    WaylandOutputInfo o = {0};
    o.scale = 1;
    wl_out_accumulate_mode(&o, true, 1024, 768, 74952);
    ASSERT_EQ(o.refresh_rate, 75u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(add_up_to_capacity_then_full);
    RUN_TEST(add_dedups_same_global_name);
    RUN_TEST(find_slot_by_global_name);
    RUN_TEST(new_slot_defaults);
    RUN_TEST(mode_picks_largest_area_without_current);
    RUN_TEST(mode_tie_area_picks_higher_refresh);
    RUN_TEST(mode_current_flag_wins_and_sticks);
    RUN_TEST(refresh_mhz_rounds_to_hz);
TEST_MAIN_END()
