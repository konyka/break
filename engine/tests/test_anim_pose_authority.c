#include "test_framework.h"
#include <animation/animation.h>

static void make_fixture(IKSystem *ik, Vec3 positions[3], Quat rotations[3],
                         Mat4 world[3]) {
    anim_ik_init(ik);
    anim_ik_set_target(ik, 0u, 0u, 1u, 2u,
                       (Vec3){{1.0f, 1.0f, 0.0f}},
                       (Vec3){{0.0f, 0.0f, 1.0f}});
    anim_ik_set_weight(ik, 0u, 1.0f);
    for (u32 i = 0; i < 3u; ++i) {
        positions[i] = (Vec3){{0.0f, 0.0f, 0.0f}};
        rotations[i] = QUAT_IDENTITY;
        world[i] = mat4_identity();
    }
    world[1].e[3][1] = 1.0f;
    world[2].e[3][1] = 2.0f;
}

TEST(ragdoll_blocks_ik_without_mutating_local_pose) {
    IKSystem ik;
    Vec3 positions[3];
    Quat rotations[3];
    Mat4 world[3];
    make_fixture(&ik, positions, rotations, world);
    const Quat before[3] = {QUAT_IDENTITY, QUAT_IDENTITY, QUAT_IDENTITY};
    ASSERT_FALSE(anim_ik_solve_unless_ragdoll(&ik, positions, rotations,
                                              world, 3u, true));
    ASSERT_EQ(memcmp(rotations, before, sizeof(rotations)), 0);

    Quat expected[3] = {QUAT_IDENTITY, QUAT_IDENTITY, QUAT_IDENTITY};
    anim_ik_solve(&ik, positions, expected, world, 3u);
    ASSERT_TRUE(anim_ik_solve_unless_ragdoll(&ik, positions, rotations,
                                             world, 3u, false));
    ASSERT_EQ(memcmp(rotations, expected, sizeof(rotations)), 0);
}

TEST(ragdoll_gate_rejects_invalid_empty_pose_without_mutation) {
    IKSystem ik;
    Vec3 positions[3];
    Quat rotations[3];
    Mat4 world[3];
    make_fixture(&ik, positions, rotations, world);
    const Quat before[3] = {QUAT_IDENTITY, QUAT_IDENTITY, QUAT_IDENTITY};
    ASSERT_FALSE(anim_ik_solve_unless_ragdoll(&ik, positions, rotations,
                                              world, 0u, false));
    ASSERT_EQ(memcmp(rotations, before, sizeof(rotations)), 0);
}

TEST_MAIN_BEGIN()
    RUN_TEST(ragdoll_blocks_ik_without_mutating_local_pose);
    RUN_TEST(ragdoll_gate_rejects_invalid_empty_pose_without_mutation);
TEST_MAIN_END()
