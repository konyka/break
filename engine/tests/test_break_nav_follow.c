#include "test_framework.h"
#include <ai/break_ai.h>

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

TEST_MAIN_BEGIN()
    RUN_TEST(follower_walks_a_segment_and_ignores_bad_dt);
TEST_MAIN_END()
