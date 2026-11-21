#include "test_framework.h"
#include <ai/break_ai.h>
#include <math.h>

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

typedef struct {
    u32 calls;
    bool clear;
} RayCounter;

static bool ray_counting(void *user, Vec3 from, Vec3 to) {
    (void)from;
    (void)to;
    RayCounter *c = (RayCounter *)user;
    c->calls++;
    return c->clear;
}

static BreakSight forward_sight(void) {
    BreakSight sight;
    sight.eye = vec3(0, 0, 0);
    sight.forward = vec3(0, 0, 1);
    sight.distance = 10.0f;
    sight.half_angle_rad = 0.4f;
    return sight;
}

/* Distance and cone limits are inclusive at the boundary, the eye's own
 * position is excluded, and the ray test only runs for targets inside the
 * cone and range. */
TEST(sight_boundaries_and_ray_calls) {
    BreakSight sight = forward_sight();
    BreakSightTarget targets[5];
    memset(targets, 0, sizeof(targets));
    for (u32 i = 0; i < 5u; i++) targets[i].entity = (Entity){i + 1u, 1};
    targets[0].point = vec3(0, 0, 10);                /* at the range limit */
    targets[1].point = vec3(0, 0, 10.5f);             /* just beyond */
    targets[2].point = vec3(0, 0, 0);                 /* the eye itself */
    targets[3].point = vec3(sinf(0.39f) * 5.0f, 0, cosf(0.39f) * 5.0f); /* inside the cone */
    targets[4].point = vec3(sinf(0.45f) * 5.0f, 0, cosf(0.45f) * 5.0f); /* outside */
    RayCounter rays = {0u, true};
    Entity visible[5];
    u32 count = 0;
    ASSERT_EQ(break_sight_query(&sight, targets, 5, ray_counting, &rays, visible, 5, &count), BREAK_NAV_OK);
    ASSERT_EQ(count, 2u);
    ASSERT_EQ(visible[0].index, 1u);
    ASSERT_EQ(visible[1].index, 4u);
    ASSERT_EQ(rays.calls, 2u);
}

/* A vertical offset counts toward both distance and angle: the cone is a
 * 3D cone, not a 2D wedge. */
TEST(sight_cone_is_three_dimensional) {
    BreakSight sight = forward_sight();
    BreakSightTarget targets[2];
    targets[0].entity = (Entity){1, 1};
    /* straight ahead in XZ but 45 degrees up: only the 3D angle rejects it */
    targets[0].point = vec3(0, 4, 4);
    targets[1].entity = (Entity){2, 1};
    targets[1].point = vec3(0, 0.5f, 4);
    RayCounter rays = {0u, true};
    Entity visible[2];
    u32 count = 0;
    ASSERT_EQ(break_sight_query(&sight, targets, 2, ray_counting, &rays, visible, 2, &count), BREAK_NAV_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(visible[0].index, 2u);
    /* looking up at 45 degrees sees the raised target and not the level one */
    sight.forward = vec3(0, 0.70710678f, 0.70710678f);
    rays.calls = 0;
    ASSERT_EQ(break_sight_query(&sight, targets, 2, ray_counting, &rays, visible, 2, &count), BREAK_NAV_OK);
    ASSERT_EQ(count, 1u);
    ASSERT_EQ(visible[0].index, 1u);
}

/* Bad arguments are rejected before any ray test and leave the count. */
TEST(sight_rejects_bad_arguments) {
    BreakSight sight = forward_sight();
    BreakSightTarget target;
    target.entity = (Entity){1, 1};
    target.point = vec3(0, 0, 3);
    RayCounter rays = {0u, true};
    Entity visible[1];
    u32 count = 42;
    ASSERT_EQ(break_sight_query(NULL, &target, 1, ray_counting, &rays, visible, 1, &count), BREAK_NAV_INVALID);
    ASSERT_EQ(break_sight_query(&sight, NULL, 1, ray_counting, &rays, visible, 1, &count), BREAK_NAV_INVALID);
    ASSERT_EQ(break_sight_query(&sight, &target, 1, NULL, &rays, visible, 1, &count), BREAK_NAV_INVALID);
    ASSERT_EQ(break_sight_query(&sight, &target, 1, ray_counting, &rays, NULL, 1, &count), BREAK_NAV_INVALID);
    ASSERT_EQ(break_sight_query(&sight, &target, 1, ray_counting, &rays, visible, 1, NULL), BREAK_NAV_INVALID);
    BreakSight bad = sight;
    bad.forward = vec3(0, 0, 2);
    ASSERT_EQ(break_sight_query(&bad, &target, 1, ray_counting, &rays, visible, 1, &count), BREAK_NAV_INVALID);
    bad = sight;
    bad.distance = -1.0f;
    ASSERT_EQ(break_sight_query(&bad, &target, 1, ray_counting, &rays, visible, 1, &count), BREAK_NAV_INVALID);
    bad = sight;
    bad.distance = NAN;
    ASSERT_EQ(break_sight_query(&bad, &target, 1, ray_counting, &rays, visible, 1, &count), BREAK_NAV_INVALID);
    bad = sight;
    bad.half_angle_rad = INFINITY;
    ASSERT_EQ(break_sight_query(&bad, &target, 1, ray_counting, &rays, visible, 1, &count), BREAK_NAV_INVALID);
    ASSERT_EQ(count, 42u);
    ASSERT_EQ(rays.calls, 0u);
    /* zero targets is valid and yields zero */
    ASSERT_EQ(break_sight_query(&sight, NULL, 0, ray_counting, &rays, NULL, 0, &count), BREAK_NAV_OK);
    ASSERT_EQ(count, 0u);
}

TEST_MAIN_BEGIN()
    RUN_TEST(sight_cone_order_and_caps);
    RUN_TEST(sight_boundaries_and_ray_calls);
    RUN_TEST(sight_cone_is_three_dimensional);
    RUN_TEST(sight_rejects_bad_arguments);
TEST_MAIN_END()
