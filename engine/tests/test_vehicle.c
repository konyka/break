#include "test_framework.h"
#include <physics/vehicle.h>

TEST(vehicle_suspends_drives_and_blocks_exit) {
    PhysicsWorld *air = physics_world_create(8);
    Vehicle flying;
    ASSERT_TRUE(vehicle_create(&flying, air, vec3(0, 5, 0)));
    PhysicsBodyHandle chassis = flying.chassis;
    VehicleInput none = {0, 0, 0};
    vehicle_step(&flying, air, &none, 0.016f);
    physics_step(air, 0.016f);
    ASSERT_TRUE(chassis.index < air->count);
    ASSERT_FALSE(physics_body_is_parked(&air->bodies[chassis.index]));
    physics_world_destroy(air);

    PhysicsWorld *pw = physics_world_create(8);
    physics_body_create(pw, vec3(0, -0.5f, 0), vec3(20, 0.5f, 20), 0, true, 0);
    physics_body_create(pw, vec3(1.5f, 1.0f, 0), vec3(0.3f, 2.0f, 40), 0, true, 0);
    Vehicle car;
    ASSERT_TRUE(vehicle_create(&car, pw, vec3(0, 0.9f, 0)));
    for (int i = 0; i < 120; i++) {
        vehicle_step(&car, pw, &none, 1.0f / 60.0f);
        physics_step(pw, 1.0f / 60.0f);
    }
    ASSERT_TRUE(fabsf(pw->bodies[car.chassis.index].velocity.e[1]) < 0.5f);

    VehicleInput go = {1, 0, 0};
    for (int i = 0; i < 60; i++) {
        vehicle_step(&car, pw, &go, 1.0f / 60.0f);
        physics_step(pw, 1.0f / 60.0f);
    }
    Vec3 vel = pw->bodies[car.chassis.index].velocity;
    f32 horiz = sqrtf(vel.e[0] * vel.e[0] + vel.e[2] * vel.e[2]);
    ASSERT_TRUE(horiz > 1.0f);

    ASSERT_TRUE(vehicle_enter(&car));
    Vec3 feet = vec3(0, 0, 0);
    ASSERT_FALSE(vehicle_exit(&car, pw, &feet));
    ASSERT_TRUE(car.occupied);
    physics_world_destroy(pw);
}

TEST(vehicle_records_independent_wheel_contacts) {
    PhysicsWorld *pw = physics_world_create(8);
    PhysicsBodyHandle floor = physics_body_create(pw, vec3(0, -0.5f, 0), vec3(20, 0.5f, 20), 0, true, 0);
    Vehicle car;
    ASSERT_TRUE(vehicle_create(&car, pw, vec3(0, 0.5f, 0)));
    VehicleInput none = {0, 0, 0};
    vehicle_step(&car, pw, &none, 1.0f / 60.0f);
    for (u32 i = 0; i < 4; i++) {
        ASSERT_TRUE(car.wheels[i].grounded);
        ASSERT_TRUE(physics_body_handle_equal(car.wheels[i].ground_body, floor));
        ASSERT_TRUE(car.wheels[i].compression > 0.0f);
        ASSERT_TRUE(car.wheels[i].suspension_force >= 0.0f);
        ASSERT_FLOAT_EQ(car.wheels[i].contact_point.e[1], 0.0f, 1e-4f);
        ASSERT_TRUE(car.wheels[i].contact_normal.e[1] > 0.9f);
    }
    physics_world_destroy(pw);

    pw = physics_world_create(8);
    floor = physics_body_create(pw, vec3(-0.8f, -0.5f, 1.2f), vec3(0.2f, 0.5f, 0.2f), 0, true, 0);
    ASSERT_TRUE(vehicle_create(&car, pw, vec3(0, 0.5f, 0)));
    vehicle_step(&car, pw, &none, 1.0f / 60.0f);
    ASSERT_TRUE(car.wheels[0].grounded);
    ASSERT_TRUE(physics_body_handle_equal(car.wheels[0].ground_body, floor));
    for (u32 i = 1; i < 4; i++) {
        ASSERT_FALSE(car.wheels[i].grounded);
        ASSERT_FALSE(physics_body_handle_is_valid(car.wheels[i].ground_body));
        ASSERT_FLOAT_EQ(car.wheels[i].compression, 0.0f, 1e-6f);
    }
    physics_world_destroy(pw);
}

TEST(vehicle_airborne_has_no_drive_or_grip) {
    PhysicsWorld *pw = physics_world_create(4);
    Vehicle car;
    ASSERT_TRUE(vehicle_create(&car, pw, vec3(0, 5, 0)));
    pw->bodies[car.chassis.index].velocity = vec3(2, 0, 1);
    VehicleInput go = {1, 0.5f, 1};
    vehicle_step(&car, pw, &go, 1.0f / 60.0f);
    for (u32 i = 0; i < 4; i++) ASSERT_FALSE(car.wheels[i].grounded);
    ASSERT_FLOAT_EQ(pw->bodies[car.chassis.index].acceleration.e[0], 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(pw->bodies[car.chassis.index].acceleration.e[2], 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(pw->bodies[car.chassis.index].velocity.e[0], 2.0f, 1e-6f);
    ASSERT_FLOAT_EQ(pw->bodies[car.chassis.index].velocity.e[2], 1.0f, 1e-6f);
    physics_world_destroy(pw);
}

TEST(vehicle_control_is_persistent_and_rejects_nonfinite) {
    PhysicsWorld *pw = physics_world_create(4);
    Vehicle car;
    ASSERT_TRUE(vehicle_create(&car, pw, vec3(0, 5, 0)));
    VehicleInput clamped = {2, -2, 2};
    vehicle_step(&car, pw, &clamped, 1.0f / 60.0f);
    ASSERT_FLOAT_EQ(car.control.throttle, 1.0f, 1e-6f);
    ASSERT_FLOAT_EQ(car.control.steer, -1.0f, 1e-6f);
    ASSERT_FLOAT_EQ(car.control.brake, 1.0f, 1e-6f);
    VehicleInput invalid = {NAN, 0, 0};
    vehicle_step(&car, pw, &invalid, 1.0f / 60.0f);
    ASSERT_FLOAT_EQ(car.control.throttle, 1.0f, 1e-6f);
    ASSERT_FLOAT_EQ(car.control.steer, -1.0f, 1e-6f);
    ASSERT_FLOAT_EQ(car.control.brake, 1.0f, 1e-6f);
    physics_world_destroy(pw);
}

TEST(vehicle_create_failure_is_atomic_and_destroy_recycles) {
    PhysicsWorld *full = physics_world_create(1);
    ASSERT_TRUE(physics_body_handle_is_valid(
        physics_body_create(full, vec3(0, 0, 0), vec3(1, 1, 1), 0, true, 0)));
    Vehicle untouched;
    memset(&untouched, 0x5a, sizeof(untouched));
    Vehicle before = untouched;
    ASSERT_FALSE(vehicle_create(&untouched, full, vec3(0, 0, 0)));
    ASSERT_EQ(memcmp(&untouched, &before, sizeof(untouched)), 0);
    physics_world_destroy(full);

    PhysicsWorld *pw = physics_world_create(2);
    physics_body_create(pw, vec3(0, -0.5f, 0), vec3(20, 0.5f, 20), 0, true, 0);
    Vehicle car;
    ASSERT_TRUE(vehicle_create(&car, pw, vec3(0, 0.5f, 0)));
    PhysicsBodyHandle chassis = car.chassis;
    vehicle_destroy(&car, pw);
    ASSERT_FALSE(physics_body_handle_is_valid(car.chassis));
    ASSERT_TRUE(physics_body_is_parked(&pw->bodies[chassis.index]));
    PhysicsBodyHandle reused = physics_body_create(pw, vec3(0, 3, 0), vec3(1, 1, 1), 1, false, 0);
    ASSERT_EQ(reused.index, chassis.index);
    ASSERT_NEQ(reused.generation, chassis.generation);
    vehicle_destroy(&car, pw);
    physics_world_destroy(pw);
}

TEST(vehicle_stale_destroy_preserves_reused_chassis) {
    PhysicsWorld *pw = physics_world_create(2);
    Vehicle car;
    ASSERT_TRUE(vehicle_create(&car, pw, vec3(0, 3, 0)));
    Vehicle stale = car;
    vehicle_destroy(&car, pw);
    PhysicsBodyHandle new_body = physics_body_create(pw, vec3(8, 3, 0), vec3(1, 1, 1), 1, false, 0);
    vehicle_destroy(&stale, pw);
    ASSERT_FALSE(physics_body_is_parked(&pw->bodies[new_body.index]));
    physics_world_destroy(pw);
}

TEST(vehicle_create_rejects_nonfinite_position_atomically) {
    PhysicsWorld *pw = physics_world_create(4);
    PhysicsWorld world_before = *pw;
    Vehicle untouched;
    memset(&untouched, 0x5a, sizeof(untouched));
    Vehicle before = untouched;
    Vec3 invalid[] = { {{NAN, 0, 0}}, {{INFINITY, 0, 0}}, {{-INFINITY, 0, 0}} };
    for (u32 i = 0; i < 3; i++) {
        ASSERT_FALSE(vehicle_create(&untouched, pw, invalid[i]));
        ASSERT_EQ(memcmp(&untouched, &before, sizeof(untouched)), 0);
        ASSERT_EQ(memcmp(pw, &world_before, sizeof(world_before)), 0);
    }
    physics_world_destroy(pw);
}

static void vehicle_set_rotated_chassis(Vehicle *car, PhysicsWorld *pw, Vec3 inertia) {
    const f32 pi = 3.14159265358979323846f;
    PhysicsPose pose;
    pose.orientation = quat_from_axis_angle(vec3(1, 0, 0), pi / 2.0f);
    pose.angular_velocity = vec3(0, 0, 0);
    pose.inertia_diag = inertia;
    physics_body_set_pose(pw, car->chassis, &pose);
    pw->bodies[car->chassis.index].position = vec3(0, 0, 0.5f);
}

TEST(vehicle_steering_brake_and_grip_follow_chassis_frame) {
    PhysicsWorld *pw = physics_world_create(8);
    physics_body_create(pw, vec3(0, 0, -0.5f), vec3(20, 20, 0.5f), 0, true, 0);
    Vehicle car;
    ASSERT_TRUE(vehicle_create(&car, pw, vec3(0, 0, 0)));
    vehicle_set_rotated_chassis(&car, pw, vec3(0, 1, 0));
    RigidBody *chassis = &pw->bodies[car.chassis.index];
    Vec3 up = quat_rotate_vec3(chassis->orientation, vec3(0, 1, 0));
    Vec3 forward = quat_rotate_vec3(chassis->orientation, vec3(0, 0, 1));
    Vec3 right = quat_rotate_vec3(chassis->orientation, vec3(1, 0, 0));
    chassis->velocity = vec3_add(vec3_scale(forward, 4.0f), vec3_scale(right, 3.0f));
    VehicleInput input = {0, 1, 1};
    vehicle_step(&car, pw, &input, 0.1f);
    ASSERT_TRUE(car.wheels[0].grounded);
    ASSERT_TRUE(vec3_dot(chassis->angular_velocity, up) > 0.01f);
    ASSERT_FLOAT_EQ(chassis->angular_velocity.e[1], 0.0f, 1e-5f);
    ASSERT_TRUE(vec3_dot(chassis->velocity, forward) < 4.0f);
    ASSERT_TRUE(fabsf(vec3_dot(chassis->velocity, right)) < 3.0f);
    physics_world_destroy(pw);
}

TEST(vehicle_zero_effective_yaw_inertia_locks_steering) {
    PhysicsWorld *pw = physics_world_create(8);
    physics_body_create(pw, vec3(0, 0, -0.5f), vec3(20, 20, 0.5f), 0, true, 0);
    Vehicle car;
    ASSERT_TRUE(vehicle_create(&car, pw, vec3(0, 0, 0)));
    vehicle_set_rotated_chassis(&car, pw, vec3(1, 0, 1));
    RigidBody *chassis = &pw->bodies[car.chassis.index];
    Vec3 up = quat_rotate_vec3(chassis->orientation, vec3(0, 1, 0));
    chassis->velocity = vec3_scale(quat_rotate_vec3(chassis->orientation, vec3(0, 0, 1)), 4.0f);
    VehicleInput input = {0, 1, 0};
    vehicle_step(&car, pw, &input, 0.1f);
    ASSERT_FLOAT_EQ(vec3_dot(chassis->angular_velocity, up), 0.0f, 1e-6f);
    physics_world_destroy(pw);
}

TEST_MAIN_BEGIN()
    RUN_TEST(vehicle_suspends_drives_and_blocks_exit);
    RUN_TEST(vehicle_records_independent_wheel_contacts);
    RUN_TEST(vehicle_airborne_has_no_drive_or_grip);
    RUN_TEST(vehicle_control_is_persistent_and_rejects_nonfinite);
    RUN_TEST(vehicle_create_failure_is_atomic_and_destroy_recycles);
    RUN_TEST(vehicle_stale_destroy_preserves_reused_chassis);
    RUN_TEST(vehicle_create_rejects_nonfinite_position_atomically);
    RUN_TEST(vehicle_steering_brake_and_grip_follow_chassis_frame);
    RUN_TEST(vehicle_zero_effective_yaw_inertia_locks_steering);
TEST_MAIN_END()
