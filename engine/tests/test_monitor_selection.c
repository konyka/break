#include "test_framework.h"
#include <platform/monitor_selection.h>

TEST(largest_overlap_selects_active_monitor) {
    MonitorInfo monitors[2] = {
        {.x = 0, .y = 0, .width = 1920, .height = 1080, .scale = 1, .primary = true},
        {.x = 1920, .y = 0, .width = 2560, .height = 1440, .scale = 2, .primary = false},
    };

    ASSERT_EQ(platform_monitor_select(monitors, 2, 1600, 100, 1200, 800), 1);
}

TEST(overlap_tie_prefers_primary_monitor) {
    MonitorInfo monitors[2] = {
        {.x = 0, .y = 0, .width = 1000, .height = 1000, .scale = 1, .primary = true},
        {.x = 1000, .y = 0, .width = 1000, .height = 1000, .scale = 2, .primary = false},
    };

    ASSERT_EQ(platform_monitor_select(monitors, 2, 500, 100, 1000, 600), 0);
}

TEST(no_overlap_selects_nearest_monitor) {
    MonitorInfo monitors[2] = {
        {.x = -1920, .y = 0, .width = 1920, .height = 1080, .scale = 1, .primary = true},
        {.x = 1000, .y = 0, .width = 1920, .height = 1080, .scale = 2, .primary = false},
    };

    ASSERT_EQ(platform_monitor_select(monitors, 2, 850, 200, 100, 100), 1);
}

TEST(negative_coordinates_are_supported) {
    MonitorInfo monitors[2] = {
        {.x = -2560, .y = -300, .width = 2560, .height = 1440, .scale = 2, .primary = false},
        {.x = 0, .y = 0, .width = 1920, .height = 1080, .scale = 1, .primary = true},
    };

    ASSERT_EQ(platform_monitor_select(monitors, 2, -1800, 100, 900, 700), 0);
}

TEST(empty_monitor_list_has_no_selection) {
    ASSERT_EQ(platform_monitor_select(NULL, 0, 0, 0, 100, 100), -1);
}

TEST_MAIN_BEGIN()
    RUN_TEST(largest_overlap_selects_active_monitor);
    RUN_TEST(overlap_tie_prefers_primary_monitor);
    RUN_TEST(no_overlap_selects_nearest_monitor);
    RUN_TEST(negative_coordinates_are_supported);
    RUN_TEST(empty_monitor_list_has_no_selection);
TEST_MAIN_END()
