#include "test_framework.h"
#include <animation/animation.h>
#include <math.h>

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

static void straight_chain(Quat rotations[3], Mat4 worlds[3], Vec3 positions[3]) {
    for (u32 i = 0; i < 3u; i++) {
        rotations[i] = QUAT_IDENTITY;
        worlds[i] = translated(0, (f32)i, 0);
        positions[i] = vec3(0, (f32)i, 0);
    }
}

/* A reachable target off the chain's line makes the solver rotate the
 * root and mid joints; the tip joint is not rotated. */
TEST(aim_solve_bends_the_chain_toward_a_reachable_target) {
    IKSystem ik;
    anim_ik_init(&ik);
    anim_ik_set_slot(&ik, ANIM_IK_SLOT_AIM, 0, 1, 2, vec3(1, 1, 0), vec3(0, 0, 1), 1.0f);
    Quat rotations[3];
    Mat4 worlds[3];
    Vec3 positions[3];
    straight_chain(rotations, worlds, positions);
    anim_ik_solve(&ik, positions, rotations, worlds, 3);
    ASSERT_TRUE(fabsf(rotations[0].e[3]) < 0.9999f);
    ASSERT_TRUE(fabsf(rotations[1].e[3]) < 0.9999f);
    ASSERT_EQ(memcmp(&rotations[2], &QUAT_IDENTITY, sizeof(Quat)), 0);
    for (u32 i = 0; i < 2u; i++) {
        f32 len = rotations[i].e[0] * rotations[i].e[0] + rotations[i].e[1] * rotations[i].e[1] +
                  rotations[i].e[2] * rotations[i].e[2] + rotations[i].e[3] * rotations[i].e[3];
        ASSERT_FLOAT_EQ(len, 1.0f, 1e-4);
    }
}

/* Half weight rotates the root by less than full weight. */
TEST(aim_weight_scales_the_correction) {
    Quat full[3], half[3];
    Mat4 worlds[3];
    Vec3 positions[3];
    IKSystem ik;
    anim_ik_init(&ik);
    anim_ik_set_slot(&ik, ANIM_IK_SLOT_AIM, 0, 1, 2, vec3(1, 1, 0), vec3(0, 0, 1), 1.0f);
    straight_chain(full, worlds, positions);
    anim_ik_solve(&ik, positions, full, worlds, 3);
    anim_ik_init(&ik);
    anim_ik_set_slot(&ik, ANIM_IK_SLOT_AIM, 0, 1, 2, vec3(1, 1, 0), vec3(0, 0, 1), 0.5f);
    straight_chain(half, worlds, positions);
    anim_ik_solve(&ik, positions, half, worlds, 3);
    ASSERT_TRUE(fabsf(half[0].e[3]) > fabsf(full[0].e[3]));
    ASSERT_TRUE(fabsf(half[0].e[3]) < 0.99999f);
}

/* Weights are clamped to [0, 1]; the look slot is independent of aim. */
TEST(aim_and_look_slots_are_independent_and_clamped) {
    IKSystem ik;
    anim_ik_init(&ik);
    anim_ik_set_slot(&ik, ANIM_IK_SLOT_AIM, 0, 1, 2, vec3(1, 0, 0), vec3(0, 0, 1), 3.0f);
    anim_ik_set_slot(&ik, ANIM_IK_SLOT_LOOK, 3, 4, 5, vec3(0, 1, 0), vec3(1, 0, 0), -2.0f);
    ASSERT_FLOAT_EQ(ik.targets[0].weight, 1.0f, 1e-6);
    ASSERT_TRUE(ik.targets[0].active);
    ASSERT_EQ(ik.targets[1].chain_root, 3u);
    ASSERT_FLOAT_EQ(ik.targets[1].weight, 0.0f, 1e-6);
    ASSERT_FALSE(ik.targets[1].active);
    ASSERT_EQ(ik.targets[0].chain_root, 0u);
    IKTarget before[2] = {ik.targets[0], ik.targets[1]};
    anim_ik_set_slot(&ik, (AnimIkSlot)7, 0, 1, 2, vec3(5, 5, 5), vec3(0, 0, 1), 1.0f);
    anim_ik_set_slot(NULL, ANIM_IK_SLOT_AIM, 0, 1, 2, vec3(5, 5, 5), vec3(0, 0, 1), 1.0f);
    ASSERT_EQ(memcmp(before, ik.targets, sizeof(before)), 0);
}

/* A chain whose joints lie beyond the caller's bone array is skipped. */
TEST(aim_skips_chains_beyond_the_bone_count) {
    IKSystem ik;
    anim_ik_init(&ik);
    anim_ik_set_slot(&ik, ANIM_IK_SLOT_AIM, 0, 1, 5, vec3(1, 1, 0), vec3(0, 0, 1), 1.0f);
    Quat rotations[3];
    Mat4 worlds[3];
    Vec3 positions[3];
    straight_chain(rotations, worlds, positions);
    Quat before[3];
    memcpy(before, rotations, sizeof(rotations));
    anim_ik_solve(&ik, positions, rotations, worlds, 3);
    ASSERT_EQ(memcmp(rotations, before, sizeof(rotations)), 0);
}

TEST_MAIN_BEGIN()
    RUN_TEST(aim_slot_rejects_high_joints_and_zero_weight);
    RUN_TEST(aim_solve_bends_the_chain_toward_a_reachable_target);
    RUN_TEST(aim_weight_scales_the_correction);
    RUN_TEST(aim_and_look_slots_are_independent_and_clamped);
    RUN_TEST(aim_skips_chains_beyond_the_bone_count);
TEST_MAIN_END()
