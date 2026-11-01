#include "test_framework.h"
#include <animation/animation.h>

static Mat4 translated(f32 x, f32 y, f32 z) {
    Mat4 m;
    memset(&m, 0, sizeof(m));
    m.e[0][0] = 1.0f;
    m.e[1][1] = 1.0f;
    m.e[2][2] = 1.0f;
    m.e[3][3] = 1.0f;
    m.e[3][0] = x;
    m.e[3][1] = y;
    m.e[3][2] = z;
    return m;
}

TEST(aim_slot_rejects_high_joints_and_zero_weight) {
    IKSystem ik;
    anim_ik_init(&ik);
    Vec3 target = vec3(1, 0, 0);
    Vec3 pole = vec3(0, 0, 1);
    anim_ik_set_slot(&ik, ANIM_IK_SLOT_AIM, 0, 1, 2, target, pole, 1.0f);
    ASSERT_EQ(ik.targets[0].chain_root, 0u);
    ASSERT_EQ(ik.targets[0].chain_mid, 1u);
    ASSERT_EQ(ik.targets[0].chain_tip, 2u);
    ASSERT_FLOAT_EQ(ik.targets[0].weight, 1.0f, 1e-6);
    ASSERT_TRUE(ik.targets[0].active);
    ASSERT_FALSE(ik.targets[1].active);

    IKTarget saved = ik.targets[0];
    anim_ik_set_slot(&ik, ANIM_IK_SLOT_AIM, 64, 1, 2, vec3(9, 9, 9), pole, 0.2f);
    ASSERT_EQ(memcmp(&ik.targets[0], &saved, sizeof(saved)), 0);

    anim_ik_set_slot(&ik, ANIM_IK_SLOT_AIM, 0, 1, 2, target, pole, 0.0f);
    Quat rotations[3];
    rotations[0] = QUAT_IDENTITY;
    rotations[1] = QUAT_IDENTITY;
    rotations[2] = QUAT_IDENTITY;
    Quat before[3];
    memcpy(before, rotations, sizeof(rotations));
    Mat4 worlds[3];
    worlds[0] = translated(0, 0, 0);
    worlds[1] = translated(0, 1, 0);
    worlds[2] = translated(0, 2, 0);
    Vec3 positions[3] = {vec3(0, 0, 0), vec3(0, 1, 0), vec3(0, 2, 0)};
    anim_ik_solve(&ik, positions, rotations, worlds, 3);
    ASSERT_EQ(memcmp(rotations, before, sizeof(rotations)), 0);
}

TEST_MAIN_BEGIN()
    RUN_TEST(aim_slot_rejects_high_joints_and_zero_weight);
TEST_MAIN_END()
