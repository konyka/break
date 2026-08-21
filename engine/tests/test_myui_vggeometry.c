#include "test_framework.h"

#include "myr/my_vggeometry.h"

TEST(rect_emits_two_triangles)
{
    my_vggeometry_t geo;
    my_vggeometry_init(&geo, NULL);
    my_vggeometry_set_transform(&geo, 0.0f, 0.0f, 1.0f);
    my_vggeometry_begin_verts(&geo);
    my_vggeometry_rect(&geo, 0.0f, 0.0f, 10.0f, 20.0f);
    ASSERT_EQ(geo.vert_count, 12u);
    ASSERT_FLOAT_EQ(geo.verts[0], 0.0f, 0.001f);
    ASSERT_FLOAT_EQ(geo.verts[1], 0.0f, 0.001f);
    ASSERT_FLOAT_EQ(geo.verts[2], 10.0f, 0.001f);
    ASSERT_FLOAT_EQ(geo.verts[3], 0.0f, 0.001f);
    ASSERT_FLOAT_EQ(geo.verts[4], 10.0f, 0.001f);
    ASSERT_FLOAT_EQ(geo.verts[5], 20.0f, 0.001f);
    my_vggeometry_destroy(&geo);
}

TEST(transform_is_applied)
{
    my_vggeometry_t geo;
    my_vggeometry_init(&geo, NULL);
    my_vggeometry_set_transform(&geo, 5.0f, -3.0f, 2.0f);
    my_vggeometry_begin_verts(&geo);
    my_vggeometry_rect(&geo, 1.0f, 2.0f, 3.0f, 4.0f);
    ASSERT_EQ(geo.vert_count, 12u);
    ASSERT_FLOAT_EQ(geo.verts[0], 12.0f, 0.001f);
    ASSERT_FLOAT_EQ(geo.verts[1], -2.0f, 0.001f);
    my_vggeometry_destroy(&geo);
}

TEST(rounded_rect_emits_more_than_plain_rect)
{
    my_vggeometry_t geo;
    my_vggeometry_init(&geo, NULL);
    my_vggeometry_set_transform(&geo, 0.0f, 0.0f, 1.0f);
    my_vggeometry_begin_verts(&geo);
    my_vggeometry_fill_rounded_rect(&geo, 0.0f, 0.0f, 100.0f, 50.0f, 12.0f);
    ASSERT_TRUE(geo.vert_count > 12u);
    ASSERT_EQ(geo.vert_count % 6, 0u);
    my_vggeometry_destroy(&geo);
}

TEST_MAIN_BEGIN()
    RUN_TEST(rect_emits_two_triangles);
    RUN_TEST(transform_is_applied);
    RUN_TEST(rounded_rect_emits_more_than_plain_rect);
TEST_MAIN_END()
