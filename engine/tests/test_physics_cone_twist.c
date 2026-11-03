#include "test_framework.h"
#include <physics/physics.h>

static const f32 PI = 3.14159265358979323846f;

static void set_pose(PhysicsWorld *pw, PhysicsBodyHandle id, Quat q, Vec3 omega, Vec3 inertia) {
    PhysicsPose pose;
    pose.orientation = q;
    pose.angular_velocity = omega;
    pose.inertia_diag = inertia;
    physics_body_set_pose(pw, id, &pose);
}

static ConeTwistDesc cone_desc(PhysicsBodyHandle a, PhysicsBodyHandle b, Vec3 axis) {
    ConeTwistDesc d;
    memset(&d, 0, sizeof(d));
    d.body_a = a;
    d.body_b = b;
    d.axis_local_a = axis;
    d.axis_local_b = axis;
    d.swing_max = PI;
    d.twist_min = -PI;
    d.twist_max = PI;
    return d;
}

static f32 angle_x(Quat q) {
    Vec3 axis = quat_rotate_vec3(q, vec3(1, 0, 0));
    return atan2f(vec3_len(vec3_cross(vec3(1, 0, 0), axis)),
                  vec3_dot(vec3(1, 0, 0), axis));
}

static f32 twist_y(Quat q) {
    return 2.0f * atan2f(q.e[1], q.e[3]);
}

static bool body_finite(const RigidBody *b) {
    for (int i = 0; i < 3; i++) {
        if (!isfinite(b->position.e[i]) || !isfinite(b->angular_velocity.e[i])) return false;
    }
    for (int i = 0; i < 4; i++) if (!isfinite(b->orientation.e[i])) return false;
    return true;
}

TEST(cone_twist_enforces_swing_limits_and_free_range) {
    PhysicsWorld *pw = physics_world_create(4);
    PhysicsBodyHandle a = physics_body_create(pw, vec3(0, 3, 0), vec3(0, 0, 0), 0, true, 0);
    PhysicsBodyHandle b = physics_body_create(pw, vec3(0, 3, 0), vec3(0, 0, 0), 1, false, 0);
    pw->bodies[b.index].acceleration = vec3(0, 0, 0);
    ConeTwistDesc d = cone_desc(a, b, vec3(1, 0, 0));
    d.swing_max = PI / 6.0f;
    ASSERT_TRUE(physics_constraint_handle_is_valid(physics_constraint_add_cone_twist(pw, &d)));

    set_pose(pw, b, quat_from_axis_angle(vec3(0, 0, 1), PI / 3.0f), vec3(0, 0, 0), vec3(1, 1, 1));
    physics_step(pw, 0.016f);
    ASSERT_FLOAT_EQ(angle_x(pw->bodies[b.index].orientation), PI / 6.0f, 2e-3f);
    ASSERT_FLOAT_EQ(angle_x(pw->bodies[a.index].orientation), 0.0f, 1e-6f);

    set_pose(pw, b, quat_from_axis_angle(vec3(0, 0, 1), -PI / 3.0f), vec3(0, 0, 0), vec3(1, 1, 1));
    physics_step(pw, 0.016f);
    ASSERT_FLOAT_EQ(angle_x(pw->bodies[b.index].orientation), PI / 6.0f, 2e-3f);

    set_pose(pw, b, quat_from_axis_angle(vec3(0, 0, 1), PI / 18.0f), vec3(0, 0, 0), vec3(1, 1, 1));
    physics_step(pw, 0.016f);
    ASSERT_FLOAT_EQ(angle_x(pw->bodies[b.index].orientation), PI / 18.0f, 2e-3f);

    pw->constraints[0].swing_min = PI / 18.0f;
    set_pose(pw, b, quat_from_axis_angle(vec3(0, 0, 1), PI / 90.0f), vec3(0, 0, 0), vec3(1, 1, 1));
    physics_step(pw, 0.016f);
    ASSERT_FLOAT_EQ(angle_x(pw->bodies[b.index].orientation), PI / 18.0f, 2e-3f);
    physics_world_destroy(pw);
}

TEST(cone_twist_enforces_twist_limits_and_outward_velocity) {
    PhysicsWorld *pw = physics_world_create(4);
    PhysicsBodyHandle a = physics_body_create(pw, vec3(0, 3, 0), vec3(0, 0, 0), 0, true, 0);
    PhysicsBodyHandle b = physics_body_create(pw, vec3(0, 3, 0), vec3(0, 0, 0), 1, false, 0);
    pw->bodies[b.index].acceleration = vec3(0, 0, 0);
    ConeTwistDesc d = cone_desc(a, b, vec3(0, 1, 0));
    d.twist_min = -PI / 9.0f;
    d.twist_max = PI / 9.0f;
    ASSERT_TRUE(physics_constraint_handle_is_valid(physics_constraint_add_cone_twist(pw, &d)));

    set_pose(pw, b, quat_from_axis_angle(vec3(0, 1, 0), PI / 4.0f), vec3(0, 0, 0), vec3(1, 1, 1));
    physics_step(pw, 0.016f);
    ASSERT_FLOAT_EQ(twist_y(pw->bodies[b.index].orientation), PI / 9.0f, 2e-3f);

    set_pose(pw, b, quat_from_axis_angle(vec3(0, 1, 0), -PI / 4.0f), vec3(0, 0, 0), vec3(1, 1, 1));
    physics_step(pw, 0.016f);
    ASSERT_FLOAT_EQ(twist_y(pw->bodies[b.index].orientation), -PI / 9.0f, 2e-3f);

    set_pose(pw, b, quat_from_axis_angle(vec3(0, 1, 0), PI / 18.0f), vec3(0, 0, 0), vec3(1, 1, 1));
    physics_step(pw, 0.016f);
    ASSERT_FLOAT_EQ(twist_y(pw->bodies[b.index].orientation), PI / 18.0f, 2e-3f);

    set_pose(pw, b, quat_from_axis_angle(vec3(0, 1, 0), PI / 4.0f), vec3(0, 5, 0), vec3(1, 1, 1));
    physics_step(pw, 0.016f);
    ASSERT_FLOAT_EQ(twist_y(pw->bodies[b.index].orientation), PI / 9.0f, 2e-3f);
    ASSERT_TRUE(pw->bodies[b.index].angular_velocity.e[1] <= 1e-4f);
    physics_world_destroy(pw);
}

TEST(cone_twist_solves_anchors_and_dynamic_pair) {
    PhysicsWorld *pw = physics_world_create(4);
    PhysicsBodyHandle a = physics_body_create(pw, vec3(0, 3, 0), vec3(0, 0, 0), 0, true, 0);
    PhysicsBodyHandle b = physics_body_create(pw, vec3(5, 3, 0), vec3(0, 0, 0), 1, false, 0);
    pw->bodies[b.index].acceleration = vec3(0, 0, 0);
    ConeTwistDesc d = cone_desc(a, b, vec3(1, 0, 0));
    d.anchor_local_a = vec3(1, 0, 0);
    d.anchor_local_b = vec3(-1, 0, 0);
    set_pose(pw, b, QUAT_IDENTITY, vec3(0, 0, 0), vec3(1, 1, 1));
    ASSERT_TRUE(physics_constraint_handle_is_valid(physics_constraint_add_cone_twist(pw, &d)));
    physics_step(pw, 0.016f);
    Vec3 pa = vec3_add(pw->bodies[a.index].position, d.anchor_local_a);
    Vec3 pb = vec3_add(pw->bodies[b.index].position, d.anchor_local_b);
    ASSERT_FLOAT_EQ(vec3_len(vec3_sub(pb, pa)), 0.0f, 1e-3f);
    physics_world_destroy(pw);

    pw = physics_world_create(4);
    a = physics_body_create(pw, vec3(0, 3, 0), vec3(0, 0, 0), 1, false, 0);
    b = physics_body_create(pw, vec3(0, 3, 0), vec3(0, 0, 0), 1, false, 0);
    pw->bodies[a.index].acceleration = vec3(0, 0, 0);
    pw->bodies[b.index].acceleration = vec3(0, 0, 0);
    set_pose(pw, a, QUAT_IDENTITY, vec3(0, 0, 0), vec3(1, 1, 1));
    set_pose(pw, b, QUAT_IDENTITY, vec3(0, 0, 0), vec3(1, 1, 1));
    d = cone_desc(a, b, vec3(1, 0, 0));
    d.swing_max = PI / 6.0f;
    ASSERT_TRUE(physics_constraint_handle_is_valid(physics_constraint_add_cone_twist(pw, &d)));
    set_pose(pw, a, quat_from_axis_angle(vec3(0, 0, 1), -PI / 6.0f), vec3(0, 0, 0), vec3(1, 1, 1));
    set_pose(pw, b, quat_from_axis_angle(vec3(0, 0, 1), PI / 6.0f), vec3(0, 0, 0), vec3(1, 1, 1));
    physics_step(pw, 0.016f);
    ASSERT_FLOAT_EQ(2.0f * atan2f(pw->bodies[a.index].orientation.e[2], pw->bodies[a.index].orientation.e[3]), -PI / 12.0f, 3e-3f);
    ASSERT_FLOAT_EQ(2.0f * atan2f(pw->bodies[b.index].orientation.e[2], pw->bodies[b.index].orientation.e[3]), PI / 12.0f, 3e-3f);
    physics_world_destroy(pw);
}

TEST(cone_twist_zero_inertia_is_stable) {
    PhysicsWorld *pw = physics_world_create(4);
    PhysicsBodyHandle a = physics_body_create(pw, vec3(0, 3, 0), vec3(0, 0, 0), 0, true, 0);
    PhysicsBodyHandle b = physics_body_create(pw, vec3(0, 3, 0), vec3(0, 0, 0), 1, false, 0);
    pw->bodies[b.index].acceleration = vec3(0, 0, 0);
    ConeTwistDesc d = cone_desc(a, b, vec3(1, 0, 0));
    d.swing_max = PI / 6.0f;
    d.twist_min = -PI / 9.0f;
    d.twist_max = PI / 9.0f;
    ASSERT_TRUE(physics_constraint_handle_is_valid(physics_constraint_add_cone_twist(pw, &d)));
    set_pose(pw, b, quat_from_axis_angle(vec3(0, 0, 1), PI / 3.0f), vec3(2, 3, 4), vec3(0, 0, 0));
    physics_step(pw, 0.016f);
    ASSERT_FLOAT_EQ(angle_x(pw->bodies[b.index].orientation), PI / 3.0f, 2e-3f);
    ASSERT_TRUE(body_finite(&pw->bodies[b.index]));
    physics_world_destroy(pw);
}

TEST(cone_twist_rejects_invalid_and_reuses_capacity) {
    PhysicsWorld *pw = physics_world_create(4);
    PhysicsBodyHandle a = physics_body_create(pw, vec3(0, 0, 0), vec3(0, 0, 0), 0, true, 0);
    PhysicsBodyHandle b = physics_body_create(pw, vec3(1, 0, 0), vec3(0, 0, 0), 1, false, 0);
    ConeTwistDesc d = cone_desc(a, b, vec3(1, 0, 0));
    d.body_b = (PhysicsBodyHandle){99u, 1u};
    ASSERT_FALSE(physics_constraint_handle_is_valid(physics_constraint_add_cone_twist(pw, &d)));
    d = cone_desc(a, a, vec3(1, 0, 0));
    ASSERT_FALSE(physics_constraint_handle_is_valid(physics_constraint_add_cone_twist(pw, &d)));
    d = cone_desc(a, b, vec3(0, 0, 0));
    ASSERT_FALSE(physics_constraint_handle_is_valid(physics_constraint_add_cone_twist(pw, &d)));
    d = cone_desc(a, b, vec3(1, 0, 0));
    d.axis_local_b = vec3(0, 0, 0);
    ASSERT_FALSE(physics_constraint_handle_is_valid(physics_constraint_add_cone_twist(pw, &d)));
    d = cone_desc(a, b, vec3(1, 0, 0));
    d.anchor_local_a.e[1] = NAN;
    ASSERT_FALSE(physics_constraint_handle_is_valid(physics_constraint_add_cone_twist(pw, &d)));
    d = cone_desc(a, b, vec3(1, 0, 0));
    d.swing_min = -0.1f;
    ASSERT_FALSE(physics_constraint_handle_is_valid(physics_constraint_add_cone_twist(pw, &d)));
    d = cone_desc(a, b, vec3(1, 0, 0));
    d.swing_max = PI + 0.1f;
    ASSERT_FALSE(physics_constraint_handle_is_valid(physics_constraint_add_cone_twist(pw, &d)));
    d = cone_desc(a, b, vec3(1, 0, 0));
    d.twist_min = 0.2f;
    d.twist_max = -0.2f;
    ASSERT_FALSE(physics_constraint_handle_is_valid(physics_constraint_add_cone_twist(pw, &d)));
    ASSERT_EQ(physics_constraint_count(pw), 0u);

    for (u32 i = 0; i < PHYSICS_MAX_CONSTRAINTS; i++) {
        ASSERT_TRUE(physics_constraint_handle_is_valid(physics_constraint_add_distance(pw, a, b, 1.0f)));
    }
    d = cone_desc(a, b, vec3(1, 0, 0));
    ASSERT_FALSE(physics_constraint_handle_is_valid(physics_constraint_add_cone_twist(pw, &d)));
    ASSERT_EQ(physics_constraint_count(pw), (u32)PHYSICS_MAX_CONSTRAINTS);
    physics_constraint_remove(pw, (PhysicsConstraintHandle){7u, pw->constraints[7].generation});
    ASSERT_EQ(physics_constraint_add_cone_twist(pw, &d).index, 7u);
    ASSERT_EQ(physics_constraint_count(pw), (u32)PHYSICS_MAX_CONSTRAINTS);
    physics_world_destroy(pw);
}

TEST(cone_twist_limit_wakes_sleeping_body) {
    PhysicsWorld *pw = physics_world_create(4);
    PhysicsBodyHandle a = physics_body_create(pw, vec3(0, 3, 0), vec3(0, 0, 0), 0, true, 0);
    PhysicsBodyHandle b = physics_body_create(pw, vec3(0, 3, 0), vec3(0, 0, 0), 1, false, 0);
    pw->bodies[b.index].acceleration = vec3(0, 0, 0);
    ConeTwistDesc d = cone_desc(a, b, vec3(1, 0, 0));
    d.swing_max = PI / 6.0f;
    ASSERT_TRUE(physics_constraint_handle_is_valid(physics_constraint_add_cone_twist(pw, &d)));
    set_pose(pw, b, quat_from_axis_angle(vec3(0, 0, 1), PI / 3.0f), vec3(0, 0, 0), vec3(1, 1, 1));
    pw->bodies[b.index].sleeping = true;
    pw->bodies[b.index].rest_frames = 60;
    physics_step(pw, 0.016f);
    ASSERT_FALSE(pw->bodies[b.index].sleeping);
    ASSERT_FLOAT_EQ(angle_x(pw->bodies[b.index].orientation), PI / 6.0f, 2e-3f);
    physics_world_destroy(pw);
}

TEST(cone_twist_at_rest_allows_sleep) {
    PhysicsWorld *pw = physics_world_create(4);
    PhysicsBodyHandle a = physics_body_create(pw, vec3(0, 3, 0), vec3(0, 0, 0), 0, true, 0);
    PhysicsBodyHandle b = physics_body_create(pw, vec3(0, 3, 0), vec3(0, 0, 0), 1, false, 0);
    pw->bodies[b.index].acceleration = vec3(0, 0, 0);
    set_pose(pw, b, QUAT_IDENTITY, vec3(0, 0, 0), vec3(1, 1, 1));
    ConeTwistDesc d = cone_desc(a, b, vec3(1, 0, 0));
    ASSERT_TRUE(physics_constraint_handle_is_valid(physics_constraint_add_cone_twist(pw, &d)));
    for (int i = 0; i < 60; i++) physics_step(pw, 0.016f);
    ASSERT_TRUE(pw->bodies[b.index].sleeping);
    Vec3 position = pw->bodies[b.index].position;
    for (int i = 0; i < 4; i++) physics_step(pw, 0.016f);
    ASSERT_TRUE(pw->bodies[b.index].sleeping);
    ASSERT_TRUE(pw->bodies[b.index].position.e[0] == position.e[0] &&
                pw->bodies[b.index].position.e[1] == position.e[1] &&
                pw->bodies[b.index].position.e[2] == position.e[2]);
    physics_world_destroy(pw);
}

TEST(cone_twist_dynamic_a_uses_one_relative_frame) {
    PhysicsWorld *pw = physics_world_create(4);
    PhysicsBodyHandle a = physics_body_create(pw, vec3(0, 3, 0), vec3(0, 0, 0), 1, false, 0);
    PhysicsBodyHandle b = physics_body_create(pw, vec3(0, 3, 0), vec3(0, 0, 0), 1, false, 0);
    pw->bodies[a.index].acceleration = vec3(0, 0, 0);
    pw->bodies[b.index].acceleration = vec3(0, 0, 0);
    set_pose(pw, a, QUAT_IDENTITY, vec3(0, 0, 0), vec3(1, 1, 1));
    set_pose(pw, b, QUAT_IDENTITY, vec3(0, 0, 0), vec3(1, 1, 1));
    ConeTwistDesc d = cone_desc(a, b, vec3(1, 0, 0));
    d.swing_max = PI / 2.0f;
    d.twist_min = -PI / 9.0f;
    d.twist_max = PI / 9.0f;
    ASSERT_TRUE(physics_constraint_handle_is_valid(physics_constraint_add_cone_twist(pw, &d)));

    Quat qa = quat_from_axis_angle(vec3(0, 0, 1), PI / 2.0f);
    Quat world_twist = quat_from_axis_angle(vec3(0, 1, 0), PI / 4.0f);
    Quat qb = quat_normalize(quat_mul(world_twist, qa));
    set_pose(pw, a, qa, vec3(0, 0, 0), vec3(1, 1, 1));
    set_pose(pw, b, qb, vec3(0, 5, 0), vec3(1, 1, 1));
    physics_step(pw, 0.016f);

    Quat relative = quat_mul(quat_inverse(pw->bodies[a.index].orientation),
                             pw->bodies[b.index].orientation);
    f32 twist = 2.0f * atan2f(relative.e[0], relative.e[3]);
    ASSERT_FLOAT_EQ(twist, PI / 9.0f, 4e-3f);
    Vec3 axis = quat_rotate_vec3(pw->bodies[a.index].orientation, vec3(1, 0, 0));
    Vec3 relative_omega = vec3_sub(pw->bodies[b.index].angular_velocity,
                                   pw->bodies[a.index].angular_velocity);
    ASSERT_TRUE(vec3_dot(relative_omega, axis) <= 1e-4f);
    ASSERT_TRUE(body_finite(&pw->bodies[a.index]));
    ASSERT_TRUE(body_finite(&pw->bodies[b.index]));

    qa = pw->bodies[a.index].orientation;
    Quat combined = quat_mul(qa, quat_mul(
        quat_from_axis_angle(vec3(0, 0, 1), PI / 12.0f),
        quat_from_axis_angle(vec3(1, 0, 0), PI / 4.0f)));
    set_pose(pw, b, combined, vec3(0, 5, 0), vec3(1, 1, 1));
    pw->constraints[0].swing_max = PI / 18.0f;
    physics_step(pw, 0.016f);
    qa = pw->bodies[a.index].orientation;
    Vec3 axis_a = quat_rotate_vec3(qa, vec3(1, 0, 0));
    Vec3 axis_b = quat_rotate_vec3(pw->bodies[b.index].orientation, vec3(1, 0, 0));
    f32 swing = atan2f(vec3_len(vec3_cross(axis_a, axis_b)), vec3_dot(axis_a, axis_b));
    ASSERT_TRUE(swing <= PI / 18.0f + 4e-3f);
    relative = quat_mul(quat_inverse(qa), pw->bodies[b.index].orientation);
    twist = 2.0f * atan2f(relative.e[0], relative.e[3]);
    ASSERT_TRUE(fabsf(twist) <= PI / 9.0f + 6e-3f);
    ASSERT_TRUE(body_finite(&pw->bodies[a.index]));
    ASSERT_TRUE(body_finite(&pw->bodies[b.index]));
    physics_world_destroy(pw);
}

TEST_MAIN_BEGIN()
    RUN_TEST(cone_twist_enforces_swing_limits_and_free_range);
    RUN_TEST(cone_twist_enforces_twist_limits_and_outward_velocity);
    RUN_TEST(cone_twist_solves_anchors_and_dynamic_pair);
    RUN_TEST(cone_twist_zero_inertia_is_stable);
    RUN_TEST(cone_twist_rejects_invalid_and_reuses_capacity);
    RUN_TEST(cone_twist_limit_wakes_sleeping_body);
    RUN_TEST(cone_twist_at_rest_allows_sleep);
    RUN_TEST(cone_twist_dynamic_a_uses_one_relative_frame);
TEST_MAIN_END()
