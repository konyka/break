#include "test_framework.h"

#include <float.h>
#include <stdint.h>
#include <math.h>

#include "myr/my_vggeometry.h"

static void* geometry_fail_alloc(void* ctx, size_t size)
{
    (void)ctx;
    (void)size;
    return NULL;
}

static void* geometry_fail_calloc(void* ctx, size_t count, size_t size)
{
    (void)ctx;
    (void)count;
    (void)size;
    return NULL;
}

static void* geometry_fail_realloc(void* ctx, void* ptr, size_t size)
{
    (void)ctx;
    (void)ptr;
    (void)size;
    return NULL;
}

static void geometry_fail_free(void* ctx, void* ptr)
{
    (void)ctx;
    (void)ptr;
}

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

TEST(push_rejects_vertex_count_wrap)
{
    my_vggeometry_t geo;
    my_vggeometry_init(&geo, NULL);
    geo.vert_count = SIZE_MAX - 1u;
    my_vggeometry_push(&geo, 1.0f, 2.0f);
    ASSERT_EQ(geo.vert_count, SIZE_MAX - 1u);
    ASSERT_TRUE(geo.verts == NULL);
    my_vggeometry_destroy(&geo);
}

static void geometry_bounds(const my_vggeometry_t* geo, float* min_x,
                            float* max_x, float* min_y, float* max_y)
{
    size_t i;
    *min_x = INFINITY;
    *max_x = -INFINITY;
    *min_y = INFINITY;
    *max_y = -INFINITY;
    for (i = 0; i + 1 < geo->vert_count; i += 2) {
        if (geo->verts[i] < *min_x) *min_x = geo->verts[i];
        if (geo->verts[i] > *max_x) *max_x = geo->verts[i];
        if (geo->verts[i + 1] < *min_y) *min_y = geo->verts[i + 1];
        if (geo->verts[i + 1] > *max_y) *max_y = geo->verts[i + 1];
    }
}

TEST(stroke_square_cap_extends_beyond_endpoint)
{
    my_vggeometry_t geo;
    float min_x, max_x, min_y, max_y;
    my_vggeometry_init(&geo, NULL);
    my_vggeometry_begin_path(&geo);
    my_vggeometry_move_to(&geo, 10.0f, 10.0f);
    my_vggeometry_line_to(&geo, 20.0f, 10.0f);
    my_vggeometry_begin_verts(&geo);
    my_vggeometry_stroke(&geo, 4.0f, MY_LINE_CAP_SQUARE,
                         MY_LINE_JOIN_MITER);
    geometry_bounds(&geo, &min_x, &max_x, &min_y, &max_y);
    ASSERT_FLOAT_EQ(min_x, 8.0f, 0.01f);
    ASSERT_FLOAT_EQ(max_x, 22.0f, 0.01f);
    ASSERT_FLOAT_EQ(min_y, 8.0f, 0.01f);
    ASSERT_FLOAT_EQ(max_y, 12.0f, 0.01f);
    my_vggeometry_destroy(&geo);
}

TEST(stroke_bevel_join_fills_outer_corner)
{
    my_vggeometry_t geo;
    float min_x, max_x, min_y, max_y;
    my_vggeometry_init(&geo, NULL);
    my_vggeometry_begin_path(&geo);
    my_vggeometry_move_to(&geo, 10.0f, 20.0f);
    my_vggeometry_line_to(&geo, 20.0f, 10.0f);
    my_vggeometry_line_to(&geo, 30.0f, 20.0f);
    my_vggeometry_begin_verts(&geo);
    my_vggeometry_stroke(&geo, 4.0f, MY_LINE_CAP_BUTT,
                         MY_LINE_JOIN_BEVEL);
    geometry_bounds(&geo, &min_x, &max_x, &min_y, &max_y);
    ASSERT_FLOAT_EQ(min_x, 8.586f, 0.02f);
    ASSERT_FLOAT_EQ(max_x, 31.414f, 0.02f);
    ASSERT_FLOAT_EQ(min_y, 8.586f, 0.02f);
    ASSERT_FLOAT_EQ(max_y, 21.414f, 0.02f);
    ASSERT_TRUE(geo.vert_count > 24u);
    my_vggeometry_destroy(&geo);
}

TEST(stroke_closed_round_join_covers_first_vertex)
{
    my_vggeometry_t geo;
    float min_x, max_x, min_y, max_y;
    my_vggeometry_init(&geo, NULL);
    my_vggeometry_begin_path(&geo);
    my_vggeometry_move_to(&geo, 10.0f, 10.0f);
    my_vggeometry_line_to(&geo, 30.0f, 10.0f);
    my_vggeometry_line_to(&geo, 30.0f, 30.0f);
    my_vggeometry_line_to(&geo, 10.0f, 30.0f);
    my_vggeometry_close_path(&geo);
    my_vggeometry_begin_verts(&geo);
    my_vggeometry_stroke(&geo, 4.0f, MY_LINE_CAP_BUTT,
                         MY_LINE_JOIN_ROUND);
    geometry_bounds(&geo, &min_x, &max_x, &min_y, &max_y);
    ASSERT_FLOAT_EQ(min_x, 8.0f, 0.01f);
    ASSERT_FLOAT_EQ(max_x, 32.0f, 0.01f);
    ASSERT_FLOAT_EQ(min_y, 8.0f, 0.01f);
    ASSERT_FLOAT_EQ(max_y, 32.0f, 0.01f);
    my_vggeometry_destroy(&geo);
}

TEST(geometry_rejects_nonfinite_path_input)
{
    my_vggeometry_t geo;
    my_vggeometry_init(&geo, NULL);
    ASSERT_EQ(my_vggeometry_begin_path(&geo), MY_RET_OK);
    ASSERT_EQ(my_vggeometry_move_to(&geo, NAN, 1.0f), MY_RET_INVALID_PARAMS);
    ASSERT_EQ(geo.point_count, 0u);
    ASSERT_EQ(geo.contour_count, 0u);
    ASSERT_EQ(my_vggeometry_move_to(&geo, 1.0f, 1.0f), MY_RET_OK);
    ASSERT_EQ(my_vggeometry_line_to(&geo, INFINITY, 2.0f),
              MY_RET_INVALID_PARAMS);
    ASSERT_EQ(geo.point_count, 1u);
    ASSERT_EQ(my_vggeometry_curve_to(&geo, 1.0f, 2.0f, NAN, 3.0f, 4.0f, 5.0f),
              MY_RET_INVALID_PARAMS);
    ASSERT_EQ(geo.point_count, 1u);
    ASSERT_EQ(my_vggeometry_begin_path(NULL), MY_RET_INVALID_PARAMS);
    ASSERT_EQ(my_vggeometry_close_path(NULL), MY_RET_INVALID_PARAMS);
    my_vggeometry_destroy(&geo);
}

TEST(geometry_rejects_invalid_stroke_and_transform)
{
    my_vggeometry_t geo;
    my_vggeometry_init(&geo, NULL);
    my_vggeometry_set_transform(&geo, 2.0f, 3.0f, 1.0f);
    my_vggeometry_set_transform(&geo, NAN, 4.0f, 1.0f);
    ASSERT_FLOAT_EQ(geo.tx, 2.0f, 0.001f);
    ASSERT_FLOAT_EQ(geo.ty, 3.0f, 0.001f);
    ASSERT_FLOAT_EQ(geo.scale, 1.0f, 0.001f);
    ASSERT_EQ(my_vggeometry_stroke(NULL, 1.0f, MY_LINE_CAP_BUTT,
                                   MY_LINE_JOIN_MITER), MY_RET_INVALID_PARAMS);
    ASSERT_EQ(my_vggeometry_stroke(&geo, NAN, MY_LINE_CAP_BUTT,
                                   MY_LINE_JOIN_MITER), MY_RET_INVALID_PARAMS);
    ASSERT_EQ(my_vggeometry_stroke(&geo, 1.0f, (my_line_cap_t)99,
                                   MY_LINE_JOIN_MITER), MY_RET_INVALID_PARAMS);
    ASSERT_EQ(my_vggeometry_stroke(&geo, 1.0f, MY_LINE_CAP_BUTT,
                                   (my_line_join_t)99), MY_RET_INVALID_PARAMS);
    ASSERT_EQ(geo.vert_count, 0u);
    my_vggeometry_destroy(&geo);
}

TEST(geometry_ignores_nonfinite_primitives)
{
    my_vggeometry_t geo;
    my_rect_t clip = {0, 0, 8, 8};
    my_vggeometry_init(&geo, NULL);
    my_vggeometry_set_transform(&geo, 0.0f, 0.0f, 1.0f);
    my_vggeometry_rect(&geo, NAN, 0.0f, 2.0f, 2.0f);
    my_vggeometry_circle_fan(&geo, 0.0f, 0.0f, INFINITY, 8);
    my_vggeometry_stroke_rect(&geo, 0.0f, 0.0f, 2.0f, 2.0f, NAN);
    ASSERT_EQ(geo.vert_count, 0u);
    ASSERT_EQ(my_vggeometry_fill(&geo, NULL), MY_RET_INVALID_PARAMS);
    ASSERT_EQ(my_vggeometry_fill(&geo, &clip), MY_RET_OK);
    my_vggeometry_destroy(&geo);
}

TEST(geometry_rejects_clip_endpoint_overflow)
{
    my_vggeometry_t geo;
    my_rect_t clip;
    my_vggeometry_init(&geo, NULL);
    clip = (my_rect_t){INT32_MAX, 0, 1, 1};
    ASSERT_EQ(my_vggeometry_fill(&geo, &clip), MY_RET_INVALID_PARAMS);
    clip = (my_rect_t){0, INT32_MAX, 1, 1};
    ASSERT_EQ(my_vggeometry_fill(&geo, &clip), MY_RET_INVALID_PARAMS);
    clip = (my_rect_t){0, 0, 1, INT32_MAX};
    ASSERT_EQ(my_vggeometry_fill(&geo, &clip), MY_RET_OK);
    my_vggeometry_destroy(&geo);
}

TEST(geometry_never_emits_nonfinite_vertices)
{
    my_vggeometry_t geo;
    size_t i;
    my_vggeometry_init(&geo, NULL);
    my_vggeometry_set_transform(&geo, 0.0f, 0.0f, 1.0f);
    my_vggeometry_begin_verts(&geo);
    my_vggeometry_push(&geo, FLT_MAX, FLT_MAX);
    my_vggeometry_push(&geo, -FLT_MAX, -FLT_MAX);
    for (i = 0; i < geo.vert_count; i++) {
        ASSERT_TRUE(isfinite(geo.verts[i]) != 0);
    }
    my_vggeometry_destroy(&geo);
}

TEST(geometry_preserves_oom_status_instead_of_partial_vertices)
{
    const my_allocator_t allocator = {NULL, geometry_fail_alloc,
                                       geometry_fail_calloc,
                                       geometry_fail_realloc,
                                       geometry_fail_free};
    my_vggeometry_t geo;
    my_vggeometry_init(&geo, &allocator);
    my_vggeometry_begin_verts(&geo);
    my_vggeometry_rect(&geo, 0.0f, 0.0f, 10.0f, 10.0f);
    ASSERT_EQ(my_vggeometry_status(&geo), MY_RET_OOM);
    ASSERT_EQ(geo.vert_count, 0u);
    my_vggeometry_begin_verts(&geo);
    ASSERT_EQ(my_vggeometry_status(&geo), MY_RET_OK);
    ASSERT_EQ(my_vggeometry_stroke(&geo, 2.0f, MY_LINE_CAP_BUTT,
                                   MY_LINE_JOIN_MITER), MY_RET_OK);
    my_vggeometry_destroy(&geo);
}

TEST_MAIN_BEGIN()
    RUN_TEST(rect_emits_two_triangles);
    RUN_TEST(transform_is_applied);
    RUN_TEST(rounded_rect_emits_more_than_plain_rect);
    RUN_TEST(push_rejects_vertex_count_wrap);
    RUN_TEST(stroke_square_cap_extends_beyond_endpoint);
    RUN_TEST(stroke_bevel_join_fills_outer_corner);
    RUN_TEST(stroke_closed_round_join_covers_first_vertex);
    RUN_TEST(geometry_rejects_nonfinite_path_input);
    RUN_TEST(geometry_rejects_invalid_stroke_and_transform);
    RUN_TEST(geometry_ignores_nonfinite_primitives);
    RUN_TEST(geometry_rejects_clip_endpoint_overflow);
    RUN_TEST(geometry_never_emits_nonfinite_vertices);
    RUN_TEST(geometry_preserves_oom_status_instead_of_partial_vertices);
TEST_MAIN_END()
