#include "test_framework.h"
#include <ai/break_ai.h>

static bool ray_from_flag(void *user, Vec3 from, Vec3 to) {
    (void)from;
    (void)to;
    return *(bool *)user;
}

TEST(sight_cone_order_and_caps) {
    BreakSight sight;
    sight.eye = vec3(0, 0, 0);
    sight.forward = vec3(0, 0, 1);
    sight.distance = 10.0f;
    sight.half_angle_rad = 0.4f;
    BreakSightTarget targets[3];
    targets[0].entity = (Entity){1, 1};
    targets[0].point = vec3(8, 0, 0);
    targets[1].entity = (Entity){2, 1};
    targets[1].point = vec3(0, 0, 4);
    targets[2].entity = (Entity){3, 1};
    targets[2].point = vec3(0, 0, 6);
    bool clear = true;
    Entity visible[4];
    u32 count = 99;
    ASSERT_EQ(break_sight_query(&sight, targets, 3, ray_from_flag, &clear, visible, 4, &count), BREAK_NAV_OK);
    ASSERT_EQ(count, 2u);
    ASSERT_EQ(visible[0].index, 2u);
    ASSERT_EQ(visible[1].index, 3u);

    clear = false;
    count = 99;
    ASSERT_EQ(break_sight_query(&sight, targets, 3, ray_from_flag, &clear, visible, 4, &count), BREAK_NAV_OK);
    ASSERT_EQ(count, 0u);

    BreakSightTarget many[9];
    memset(many, 0, sizeof(many));
    count = 7;
    ASSERT_EQ(break_sight_query(&sight, many, 9, ray_from_flag, &clear, visible, 4, &count), BREAK_NAV_OVERLOAD);
    ASSERT_EQ(count, 7u);

    clear = true;
    count = 0;
    ASSERT_EQ(break_sight_query(&sight, targets + 1, 2, ray_from_flag, &clear, visible, 1, &count),
              BREAK_NAV_OVERLOAD);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(visible[0].index, 2u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(sight_cone_order_and_caps);
TEST_MAIN_END()
