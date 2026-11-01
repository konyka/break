#include "test_framework.h"
#include <ai/break_ai.h>

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

TEST_MAIN_BEGIN()
    RUN_TEST(steer_sidesteps_an_overlapping_neighbor);
TEST_MAIN_END()
