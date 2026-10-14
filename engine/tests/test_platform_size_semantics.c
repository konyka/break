#include "test_framework.h"
#include "platform/platform_size.h"

TEST(win32_drawable_equals_event_coords_even_when_scaled) {
    u32 lw, lh, dw, dh;
    platform_size_win32(2000u, 1000u, 1.0f, &lw, &lh, &dw, &dh);
    ASSERT_EQ(dw, 2000u);
    ASSERT_EQ(dh, 1000u);
    ASSERT_EQ(lw, 2000u);
    platform_size_win32(2000u, 1000u, 2.0f, &lw, &lh, &dw, &dh);
    ASSERT_EQ(dw, 2000u); /* 锁定：drawable == 事件坐标 */
    ASSERT_EQ(lw, 1000u);
    ASSERT_EQ(lh, 500u);
}

TEST(x11_drawable_equals_event_coords_logical_is_ceil_division) {
    u32 lw, lh, dw, dh;
    platform_size_x11(2001u, 999u, 2u, &lw, &lh, &dw, &dh);
    ASSERT_EQ(dw, 2001u); /* 锁定：drawable == 事件坐标 */
    ASSERT_EQ(lw, 1001u); /* ceil(2001/2) */
    ASSERT_EQ(lh, 500u);
}

TEST(wayland_drawable_derives_from_logical_via_content_scale) {
    u32 lw, lh, dw, dh;
    platform_size_wayland(800u, 600u, 120u, &lw, &lh, &dw, &dh);
    ASSERT_EQ(lw, 800u);
    ASSERT_EQ(dw, 800u); /* scale 1.0 时两者相等 */
    platform_size_wayland(800u, 600u, 240u, &lw, &lh, &dw, &dh);
    ASSERT_EQ(lw, 800u);
    ASSERT_EQ(dw, 1600u); /* 锁定：drawable != logical（scale 2.0） */
    ASSERT_EQ(dh, 1200u);
}

TEST(cocoa_drawable_derives_from_points_via_backing_scale) {
    u32 lw, lh, dw, dh;
    platform_size_cocoa(800u, 600u, 1.0f, &lw, &lh, &dw, &dh);
    ASSERT_EQ(dw, 800u);
    platform_size_cocoa(800u, 600u, 2.0f, &lw, &lh, &dw, &dh);
    ASSERT_EQ(lw, 800u);  /* logical == points */
    ASSERT_EQ(dw, 1600u); /* 锁定：drawable != logical（Retina） */
}

TEST_MAIN_BEGIN()
    RUN_TEST(win32_drawable_equals_event_coords_even_when_scaled);
    RUN_TEST(x11_drawable_equals_event_coords_logical_is_ceil_division);
    RUN_TEST(wayland_drawable_derives_from_logical_via_content_scale);
    RUN_TEST(cocoa_drawable_derives_from_points_via_backing_scale);
TEST_MAIN_END()
