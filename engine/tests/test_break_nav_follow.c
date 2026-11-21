#include "test_framework.h"
#include <ai/break_ai.h>
#include <math.h>

TEST(follower_walks_a_segment_and_ignores_bad_dt) {
    BreakNavPath path;
    memset(&path, 0, sizeof(path));
    path.count = 2;
    path.points[0] = vec3(0, 0, 0);
    path.points[1] = vec3(10, 0, 0);
    BreakNavFollower follower;
    break_nav_follow_reset(&follower, &path, 0.2f);
    Vec3 wish = break_nav_follow_wish(&follower, vec3(0, 0, 0), 0.0f, 1.0f);
    ASSERT_FLOAT_EQ(wish.e[0], 0.0f, 1e-6);
    ASSERT_EQ(follower.cursor, 0u);
    wish = break_nav_follow_wish(&follower, vec3(0, 0, 0), 5.0f, -1.0f);
    ASSERT_FLOAT_EQ(wish.e[0], 0.0f, 1e-6);
    ASSERT_EQ(follower.cursor, 0u);
    wish = break_nav_follow_wish(&follower, vec3(0, 0, 0), 5.0f, 1.0f);
    ASSERT_TRUE(wish.e[0] > 0.0f);
    Vec3 pos = vec3(0, 0, 0);
    for (int i = 0; i < 8; i++) {
        wish = break_nav_follow_wish(&follower, pos, 5.0f, 1.0f);
        pos.e[0] += wish.e[0];
        pos.e[1] += wish.e[1];
        pos.e[2] += wish.e[2];
    }
    ASSERT_TRUE(break_nav_follow_arrived(&follower));
    wish = break_nav_follow_wish(&follower, pos, 5.0f, 1.0f);
    ASSERT_FLOAT_EQ(wish.e[0], 0.0f, 1e-5);
}

static BreakNavPath three_point_path(void) {
    BreakNavPath path;
    memset(&path, 0, sizeof(path));
    path.count = 3;
    path.points[0] = vec3(0, 0, 0);
    path.points[1] = vec3(4, 0, 0);
    path.points[2] = vec3(4, 0, 3);
    return path;
}

/* Points inside the arrive radius are skipped in one call, and the step
 * never overshoots the next point. */
TEST(follower_skips_reached_points_and_does_not_overshoot) {
    BreakNavPath path = three_point_path();
    BreakNavFollower follower;
    break_nav_follow_reset(&follower, &path, 0.5f);
    /* point 0 is 3.8 away and stays the target; once the cursor is at the
     * corner, a position 0.2 from it skips to the last point */
    Vec3 first = break_nav_follow_wish(&follower, vec3(3.8f, 0, 0), 10.0f, 1.0f);
    ASSERT_EQ(follower.cursor, 0u);
    ASSERT_FLOAT_EQ(first.e[0], -3.8f, 1e-5);
    follower.cursor = 1;
    Vec3 wish = break_nav_follow_wish(&follower, vec3(3.8f, 0, 0), 10.0f, 1.0f);
    ASSERT_EQ(follower.cursor, 2u);
    ASSERT_FLOAT_EQ(wish.e[0], 0.2f, 1e-5);
    ASSERT_FLOAT_EQ(wish.e[2], 3.0f, 1e-5);
    /* speed * dt below the distance gives exactly one step along the line */
    break_nav_follow_reset(&follower, &path, 0.1f);
    wish = break_nav_follow_wish(&follower, vec3(0, 0, 0), 2.0f, 0.5f);
    ASSERT_EQ(follower.cursor, 1u);
    ASSERT_FLOAT_EQ(wish.e[0], 1.0f, 1e-5);
    ASSERT_FLOAT_EQ(wish.e[2], 0.0f, 1e-6);
}

/* Walking the full path visits the corner and ends arrived. */
TEST(follower_turns_the_corner_and_arrives) {
    BreakNavPath path = three_point_path();
    BreakNavFollower follower;
    break_nav_follow_reset(&follower, &path, 0.05f);
    Vec3 pos = vec3(0, 0, 0);
    bool passed_corner = false;
    for (int i = 0; i < 40 && !break_nav_follow_arrived(&follower); i++) {
        Vec3 wish = break_nav_follow_wish(&follower, pos, 1.0f, 0.5f);
        pos = vec3(pos.e[0] + wish.e[0], pos.e[1] + wish.e[1], pos.e[2] + wish.e[2]);
        if (pos.e[0] > 3.9f && pos.e[2] < 0.1f) passed_corner = true;
    }
    ASSERT_TRUE(passed_corner);
    ASSERT_TRUE(break_nav_follow_arrived(&follower));
    ASSERT_FLOAT_EQ(pos.e[0], 4.0f, 0.06f);
    ASSERT_FLOAT_EQ(pos.e[2], 3.0f, 0.06f);
}

/* Reset copies the path (later edits to the caller's path do not leak in),
 * clamps a negative radius to zero, and accepts a NULL path as empty. */
TEST(follower_reset_copies_and_clamps) {
    BreakNavPath path = three_point_path();
    BreakNavFollower follower;
    break_nav_follow_reset(&follower, &path, -1.0f);
    ASSERT_FLOAT_EQ(follower.arrive_radius, 0.0f, 1e-6);
    path.points[1] = vec3(100, 0, 0);
    ASSERT_FLOAT_EQ(follower.path.points[1].e[0], 4.0f, 1e-6);
    break_nav_follow_reset(&follower, NULL, 0.5f);
    ASSERT_EQ(follower.path.count, 0u);
    ASSERT_TRUE(break_nav_follow_arrived(&follower));
    Vec3 wish = break_nav_follow_wish(&follower, vec3(0, 0, 0), 1.0f, 1.0f);
    ASSERT_FLOAT_EQ(wish.e[0], 0.0f, 1e-6);
    ASSERT_FALSE(break_nav_follow_arrived(NULL));
    break_nav_follow_reset(NULL, &path, 1.0f);
    wish = break_nav_follow_wish(NULL, vec3(0, 0, 0), 1.0f, 1.0f);
    ASSERT_FLOAT_EQ(wish.e[0], 0.0f, 1e-6);
}

/* Non-finite speed or dt returns zero without advancing. */
TEST(follower_ignores_non_finite_inputs) {
    BreakNavPath path = three_point_path();
    BreakNavFollower follower;
    break_nav_follow_reset(&follower, &path, 0.5f);
    Vec3 wish = break_nav_follow_wish(&follower, vec3(0, 0, 0), NAN, 1.0f);
    ASSERT_FLOAT_EQ(wish.e[0], 0.0f, 1e-6);
    wish = break_nav_follow_wish(&follower, vec3(0, 0, 0), 1.0f, INFINITY);
    ASSERT_FLOAT_EQ(wish.e[0], 0.0f, 1e-6);
    ASSERT_EQ(follower.cursor, 0u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(follower_walks_a_segment_and_ignores_bad_dt);
    RUN_TEST(follower_skips_reached_points_and_does_not_overshoot);
    RUN_TEST(follower_turns_the_corner_and_arrives);
    RUN_TEST(follower_reset_copies_and_clamps);
    RUN_TEST(follower_ignores_non_finite_inputs);
TEST_MAIN_END()
