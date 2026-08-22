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

/* R444: hot-unplug removal (compaction semantics) */

TEST(remove_middle_slot_compacts_tail) {
    WaylandOutputList l;
    wl_out_list_init(&l);
    wl_out_add(&l, 10);
    wl_out_add(&l, 20);
    wl_out_add(&l, 30);
    wl_out_add(&l, 40);
    ASSERT_TRUE(wl_out_remove(&l, 20));
    ASSERT_EQ(l.count, 3u);
    /* Tail slots shift down in order; no tombstones. */
    ASSERT_EQ(l.items[0].global_name, 10u);
    ASSERT_EQ(l.items[1].global_name, 30u);
    ASSERT_EQ(l.items[2].global_name, 40u);
    ASSERT_EQ(wl_out_find(&l, 20), -1);
    ASSERT_EQ(wl_out_find(&l, 30), 1);
    ASSERT_EQ(wl_out_find(&l, 40), 2);
}

TEST(remove_last_slot) {
    WaylandOutputList l;
    wl_out_list_init(&l);
    wl_out_add(&l, 10);
    wl_out_add(&l, 20);
    ASSERT_TRUE(wl_out_remove(&l, 20));
    ASSERT_EQ(l.count, 1u);
    ASSERT_EQ(l.items[0].global_name, 10u);
}

TEST(remove_unknown_global_returns_false) {
    WaylandOutputList l;
    wl_out_list_init(&l);
    wl_out_add(&l, 10);
    ASSERT_FALSE(wl_out_remove(&l, 999));
    ASSERT_EQ(l.count, 1u);
    ASSERT_EQ(l.items[0].global_name, 10u);
    /* Removing from an empty list is also a clean miss. */
    wl_out_remove(&l, 10);
    ASSERT_FALSE(wl_out_remove(&l, 10));
    ASSERT_EQ(l.count, 0u);
}

TEST(add_after_remove_reuses_capacity) {
    WaylandOutputList l;
    wl_out_list_init(&l);
    wl_out_add(&l, 10);
    wl_out_add(&l, 20);
    /* Unplug 10, replug the same name: append-dedup gives it a fresh tail
     * slot rather than resurrecting a tombstone — 8 slots never wear out
     * under repeated hot-plug. */
    ASSERT_TRUE(wl_out_remove(&l, 10));
    ASSERT_EQ(wl_out_add(&l, 10), 1);
    ASSERT_EQ(l.count, 2u);
    ASSERT_EQ(l.items[0].global_name, 20u);
    ASSERT_EQ(l.items[1].global_name, 10u);
}

TEST(optional_protocol_global_removal_is_isolated) {
    WaylandOptionalGlobals globals;

    wl_out_optional_globals_init(&globals);
    wl_out_optional_global_set(&globals, WAYLAND_OPTIONAL_DATA_DEVICE_MANAGER,
                               10u);
    wl_out_optional_global_set(&globals, WAYLAND_OPTIONAL_TEXT_INPUT_MANAGER,
                               20u);
    wl_out_optional_global_set(&globals, WAYLAND_OPTIONAL_VIEWPORTER, 30u);

    ASSERT_EQ(wl_out_optional_global_take(&globals, 20u),
              WAYLAND_OPTIONAL_TEXT_INPUT_MANAGER);
    ASSERT_EQ(wl_out_optional_global_take(&globals, 20u),
              WAYLAND_OPTIONAL_NONE);
    ASSERT_EQ(wl_out_optional_global_take(&globals, 999u),
              WAYLAND_OPTIONAL_NONE);
    ASSERT_EQ(wl_out_optional_global_take(&globals, 10u),
              WAYLAND_OPTIONAL_DATA_DEVICE_MANAGER);
    ASSERT_EQ(wl_out_optional_global_take(&globals, 30u),
              WAYLAND_OPTIONAL_VIEWPORTER);
}

TEST(optional_protocol_global_reannouncement_replaces_name) {
    WaylandOptionalGlobals globals;

    wl_out_optional_globals_init(&globals);
    wl_out_optional_global_set(&globals, WAYLAND_OPTIONAL_CURSOR_SHAPE_MANAGER,
                               40u);
    wl_out_optional_global_set(&globals, WAYLAND_OPTIONAL_CURSOR_SHAPE_MANAGER,
                               41u);

    ASSERT_EQ(wl_out_optional_global_take(&globals, 40u),
              WAYLAND_OPTIONAL_NONE);
    ASSERT_EQ(wl_out_optional_global_take(&globals, 41u),
              WAYLAND_OPTIONAL_CURSOR_SHAPE_MANAGER);
}

TEST(surface_scale_uses_largest_entered_output) {
    WaylandOutputList l;
    const u32 entered[] = {20u, 30u};
    wl_out_list_init(&l);
    ASSERT_EQ(wl_out_add(&l, 10u), 0);
    ASSERT_EQ(wl_out_add(&l, 20u), 1);
    ASSERT_EQ(wl_out_add(&l, 30u), 2);
    l.items[0].scale = 1;
    l.items[1].scale = 2;
    l.items[2].scale = 3;

    /* A surface spanning outputs must not undersize its framebuffer. */
    ASSERT_EQ(wl_out_surface_scale(&l, entered, 2u), 3);
}

TEST(surface_scale_ignores_departed_and_unknown_outputs) {
    WaylandOutputList l;
    const u32 entered[] = {10u, 999u};
    wl_out_list_init(&l);
    ASSERT_EQ(wl_out_add(&l, 10u), 0);
    l.items[0].scale = 2;

    ASSERT_EQ(wl_out_surface_scale(&l, entered, 2u), 2);
    ASSERT_TRUE(wl_out_remove(&l, 10u));
    ASSERT_EQ(wl_out_surface_scale(&l, entered, 2u), 1);
}

TEST(fractional_surface_scale_uses_viewporter) {
    WaylandSurfaceScale scale = wl_out_surface_render_scale(2, 150u, true);

    ASSERT_TRUE(scale.uses_viewport);
    ASSERT_EQ(scale.buffer_scale, 1);
    ASSERT_EQ(scale.content_scale_120, 150u);
    /* 101 * 1.25 is 126.25, which needs a 126 pixel backing buffer. */
    ASSERT_EQ(wl_out_drawable_dimension(101u, scale.content_scale_120), 126u);
    /* Toplevel dimensions round halfway away from zero. */
    ASSERT_EQ(wl_out_drawable_dimension(101u, 180u), 152u);
}

TEST(integer_surface_scale_remains_fallback_without_fractional_protocol) {
    WaylandSurfaceScale scale = wl_out_surface_render_scale(2, 150u, false);

    ASSERT_FALSE(scale.uses_viewport);
    ASSERT_EQ(scale.buffer_scale, 2);
    ASSERT_EQ(scale.content_scale_120, 240u);
    ASSERT_EQ(wl_out_drawable_dimension(101u, scale.content_scale_120), 202u);
}

TEST(integer_surface_scale_saturates_protocol_storage) {
    WaylandSurfaceScale scale =
        wl_out_surface_render_scale(INT32_MAX, 0u, false);

    ASSERT_EQ(scale.buffer_scale, INT32_MAX);
    ASSERT_EQ(scale.content_scale_120, UINT32_MAX);
}

TEST(fractional_drawable_size_handles_rounding_and_overflow) {
    /* 100 * 1.25 is exact; 1 * 1.5 rounds halfway up to two pixels. */
    ASSERT_EQ(wl_out_drawable_dimension(100u, 150u), 125u);
    ASSERT_EQ(wl_out_drawable_dimension(1u, 180u), 2u);
    ASSERT_EQ(wl_out_drawable_dimension(0xffffffffu, 240u), 0xffffffffu);
    /* A missing compositor preference safely falls back to 1x. */
    ASSERT_EQ(wl_out_drawable_dimension(99u, 0u), 99u);
}

TEST(fractional_cursor_buffer_scale_rounds_up) {
    ASSERT_EQ(wl_out_cursor_buffer_scale(0u), 1);
    ASSERT_EQ(wl_out_cursor_buffer_scale(120u), 1);
    ASSERT_EQ(wl_out_cursor_buffer_scale(150u), 2);
    ASSERT_EQ(wl_out_cursor_buffer_scale(180u), 2);
    ASSERT_EQ(wl_out_cursor_buffer_scale(240u), 2);
    ASSERT_EQ(wl_out_cursor_buffer_scale(241u), 3);
    ASSERT_EQ(wl_out_cursor_buffer_scale(UINT32_MAX), 35791395);
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
    RUN_TEST(remove_middle_slot_compacts_tail);
    RUN_TEST(remove_last_slot);
    RUN_TEST(remove_unknown_global_returns_false);
    RUN_TEST(add_after_remove_reuses_capacity);
    RUN_TEST(optional_protocol_global_removal_is_isolated);
    RUN_TEST(optional_protocol_global_reannouncement_replaces_name);
    RUN_TEST(surface_scale_uses_largest_entered_output);
    RUN_TEST(surface_scale_ignores_departed_and_unknown_outputs);
    RUN_TEST(fractional_surface_scale_uses_viewporter);
    RUN_TEST(integer_surface_scale_remains_fallback_without_fractional_protocol);
    RUN_TEST(integer_surface_scale_saturates_protocol_storage);
    RUN_TEST(fractional_drawable_size_handles_rounding_and_overflow);
    RUN_TEST(fractional_cursor_buffer_scale_rounds_up);
TEST_MAIN_END()
