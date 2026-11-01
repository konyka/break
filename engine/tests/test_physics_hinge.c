#include "test_framework.h"
#include <physics/physics.h>

static f32 twist_y(Quat q) {
    return 2.0f * atan2f(q.e[1], q.e[3]);
}

TEST(pose_spin_matches_omega_dt) {
    PhysicsWorld *pw = physics_world_create(4);
    u32 id = physics_body_create(pw, vec3(0, 5, 0), vec3(0.5f, 0.5f, 0.5f), 1.0f, false, 0);
    f32 dt = 0.02f;
    physics_step(pw, dt);
    f32 expected = 5.0f + (-9.81f * dt * 0.98f) * dt;
    ASSERT_FLOAT_EQ(pw->bodies[id].position.e[1], expected, 1e-3);

    PhysicsPose pose;
    pose.orientation = QUAT_IDENTITY;
    pose.angular_velocity = vec3(0, 2, 0);
    pose.inertia_diag = vec3(1, 1, 1);
    physics_body_set_pose(pw, id, &pose);
    physics_step(pw, 0.05f);
    ASSERT_FLOAT_EQ(twist_y(pw->bodies[id].orientation), 0.1f, 1e-3);
    physics_world_destroy(pw);
}

TEST(hinge_pulls_anchors_and_holds_the_limit) {
    PhysicsWorld *pw = physics_world_create(4);
    u32 a = physics_body_create(pw, vec3(0, 3, 0), vec3(0.2f, 0.2f, 0.2f), 1.0f, false, 0);
    u32 b = physics_body_create(pw, vec3(0, 3.5f, 0), vec3(0.2f, 0.2f, 0.2f), 1.0f, false, 0);
    HingeDesc hinge;
    memset(&hinge, 0, sizeof(hinge));
    hinge.body_a = a;
    hinge.body_b = b;
    hinge.axis_local_a = vec3(0, 1, 0);
    u32 hid = physics_constraint_add_hinge(pw, &hinge);
    ASSERT_TRUE(hid != UINT32_MAX);
    for (int i = 0; i < 8; i++) physics_step(pw, 0.016f);
    f32 dy = pw->bodies[a].position.e[1] - pw->bodies[b].position.e[1];
    if (dy < 0) dy = -dy;
    ASSERT_TRUE(dy < 0.01f);

    PhysicsPose pose;
    pose.orientation = quat_from_axis_angle(vec3(0, 1, 0), 1.0f);
    pose.angular_velocity = vec3(0, 0, 0);
    pose.inertia_diag = vec3(1, 1, 1);
    physics_body_set_pose(pw, b, &pose);
    pw->constraints[hid].limit_min = -0.4f;
    pw->constraints[hid].limit_max = 0.4f;
    f32 before = twist_y(pw->bodies[b].orientation);
    physics_step(pw, 0.016f);
    f32 after = twist_y(pw->bodies[b].orientation);
    ASSERT_TRUE(after <= before + 1e-4f);
    ASSERT_TRUE(after <= 0.4f + 1e-3f);
    physics_world_destroy(pw);
}

TEST(hinge_rejects_a_full_constraint_array) {
    PhysicsWorld *pw = physics_world_create(4);
    u32 a = physics_body_create(pw, vec3(0, 0, 0), vec3(0.2f, 0.2f, 0.2f), 1.0f, false, 0);
    u32 b = physics_body_create(pw, vec3(1, 0, 0), vec3(0.2f, 0.2f, 0.2f), 1.0f, false, 0);
    for (u32 i = 0; i < 64; i++) {
        ASSERT_TRUE(physics_constraint_add_distance(pw, a, b, 1.0f) != UINT32_MAX);
    }
    HingeDesc hinge;
    memset(&hinge, 0, sizeof(hinge));
    hinge.body_a = a;
    hinge.body_b = b;
    hinge.axis_local_a = vec3(1, 0, 0);
    ASSERT_EQ(physics_constraint_add_hinge(pw, &hinge), UINT32_MAX);
    physics_world_destroy(pw);
}

TEST_MAIN_BEGIN()
    RUN_TEST(pose_spin_matches_omega_dt);
    RUN_TEST(hinge_pulls_anchors_and_holds_the_limit);
    RUN_TEST(hinge_rejects_a_full_constraint_array);
TEST_MAIN_END()
