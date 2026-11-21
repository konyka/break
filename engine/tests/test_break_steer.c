#include "test_framework.h"
#include <ai/break_ai.h>
#include <math.h>

TEST(steer_sidesteps_an_overlapping_neighbor) {
    Vec3 wish = vec3(2, 0, 0);
    Vec3 none = break_steer_avoid(vec3(0, 0, 0), 0.5f, wish, NULL, 0);
    ASSERT_FLOAT_EQ(none.e[0], 2.0f, 1e-6);
    BreakSteerNeighbor zero;
    zero.position = vec3(0.2f, 0, 0);
    zero.radius = 0.0f;
    Vec3 ignored = break_steer_avoid(vec3(0, 0, 0), 0.5f, wish, &zero, 1);
    ASSERT_FLOAT_EQ(ignored.e[0], 2.0f, 1e-6);

    BreakSteerNeighbor neighbor;
    neighbor.position = vec3(0.4f, 0, 0);
    neighbor.radius = 0.5f;
    Vec3 self = vec3(0, 0, 0);
    Vec3 steered = break_steer_avoid(self, 0.5f, wish, &neighbor, 1);
    Vec3 to = vec3(neighbor.position.e[0] - self.e[0], 0, neighbor.position.e[2] - self.e[2]);
    f32 to_len = sqrtf(to.e[0] * to.e[0] + to.e[2] * to.e[2]);
    f32 before = (wish.e[0] * to.e[0] + wish.e[2] * to.e[2]) / to_len;
    f32 after = (steered.e[0] * to.e[0] + steered.e[2] * to.e[2]) / to_len;
    ASSERT_TRUE(after < before);
    ASSERT_TRUE(after < 0.2f);
}

static BreakSteerNeighbor neighbor_at(f32 x, f32 z, f32 radius) {
    BreakSteerNeighbor n;
    n.position = vec3(x, 0, z);
    n.radius = radius;
    return n;
}

/* A neighbor that does not overlap leaves the wish unchanged. */
TEST(steer_ignores_neighbors_that_do_not_overlap) {
    Vec3 wish = vec3(1, 0, 0);
    BreakSteerNeighbor far = neighbor_at(2.0f, 0.0f, 0.5f);
    BreakSteerNeighbor touching = neighbor_at(1.0f, 0.0f, 0.5f);
    Vec3 out = break_steer_avoid(vec3(0, 0, 0), 0.5f, wish, &far, 1);
    ASSERT_FLOAT_EQ(out.e[0], 1.0f, 1e-6);
    out = break_steer_avoid(vec3(0, 0, 0), 0.5f, wish, &touching, 1);
    ASSERT_FLOAT_EQ(out.e[0], 1.0f, 1e-6);
    ASSERT_FLOAT_EQ(out.e[2], 0.0f, 1e-6);
}

/* The sidestep is perpendicular to the wish, keeps its speed, and turns
 * away from the side the neighbor is on. */
TEST(steer_sidestep_is_perpendicular_and_away_from_the_neighbor) {
    Vec3 wish = vec3(3, 0, 0);
    BreakSteerNeighbor left = neighbor_at(0.3f, 0.2f, 0.5f);
    BreakSteerNeighbor right = neighbor_at(0.3f, -0.2f, 0.5f);
    Vec3 a = break_steer_avoid(vec3(0, 0, 0), 0.5f, wish, &left, 1);
    Vec3 b = break_steer_avoid(vec3(0, 0, 0), 0.5f, wish, &right, 1);
    ASSERT_FLOAT_EQ(a.e[0], 0.0f, 1e-6);
    ASSERT_FLOAT_EQ(a.e[2], -3.0f, 1e-5);
    ASSERT_FLOAT_EQ(b.e[0], 0.0f, 1e-6);
    ASSERT_FLOAT_EQ(b.e[2], 3.0f, 1e-5);
    ASSERT_FLOAT_EQ(a.e[1], 0.0f, 1e-6);
}

/* A zero wish still gets a unit sidestep, so a stationary agent can move
 * out of an overlap. */
TEST(steer_zero_wish_gets_a_unit_sidestep) {
    BreakSteerNeighbor n = neighbor_at(0.0f, 0.3f, 0.5f);
    Vec3 out = break_steer_avoid(vec3(0, 0, 0), 0.5f, vec3(0, 0, 0), &n, 1);
    f32 len = sqrtf(out.e[0] * out.e[0] + out.e[2] * out.e[2]);
    ASSERT_FLOAT_EQ(len, 1.0f, 1e-5);
}

/* Only the first BREAK_STEER_MAX_NEIGHBORS neighbors are considered. */
TEST(steer_considers_at_most_the_neighbor_cap) {
    BreakSteerNeighbor many[BREAK_STEER_MAX_NEIGHBORS + 1u];
    for (u32 i = 0; i < BREAK_STEER_MAX_NEIGHBORS; i++) many[i] = neighbor_at(50.0f, 0.0f, 0.5f);
    many[BREAK_STEER_MAX_NEIGHBORS] = neighbor_at(0.3f, 0.0f, 0.5f);
    Vec3 wish = vec3(1, 0, 0);
    Vec3 out = break_steer_avoid(vec3(0, 0, 0), 0.5f, wish, many, BREAK_STEER_MAX_NEIGHBORS + 1u);
    ASSERT_FLOAT_EQ(out.e[0], 1.0f, 1e-6);
    out = break_steer_avoid(vec3(0, 0, 0), 0.5f, wish, many + 1, BREAK_STEER_MAX_NEIGHBORS);
    ASSERT_FLOAT_EQ(out.e[0], 0.0f, 1e-6);
}

TEST_MAIN_BEGIN()
    RUN_TEST(steer_sidesteps_an_overlapping_neighbor);
    RUN_TEST(steer_ignores_neighbors_that_do_not_overlap);
    RUN_TEST(steer_sidestep_is_perpendicular_and_away_from_the_neighbor);
    RUN_TEST(steer_zero_wish_gets_a_unit_sidestep);
    RUN_TEST(steer_considers_at_most_the_neighbor_cap);
TEST_MAIN_END()
