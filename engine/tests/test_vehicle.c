#include "test_framework.h"
#include <physics/vehicle.h>

TEST(vehicle_suspends_drives_and_blocks_exit) {
    PhysicsWorld *air = physics_world_create(8);
    Vehicle flying;
    ASSERT_TRUE(vehicle_create(&flying, air, vec3(0, 5, 0)));
    u32 chassis = flying.chassis;
    VehicleInput none = {0, 0, 0};
    vehicle_step(&flying, air, &none, 0.016f);
    physics_step(air, 0.016f);
    ASSERT_TRUE(chassis < air->count);
    ASSERT_FALSE(physics_body_is_parked(&air->bodies[chassis]));
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
    ASSERT_TRUE(fabsf(pw->bodies[car.chassis].velocity.e[1]) < 0.5f);

    VehicleInput go = {1, 0, 0};
    for (int i = 0; i < 60; i++) {
        vehicle_step(&car, pw, &go, 1.0f / 60.0f);
        physics_step(pw, 1.0f / 60.0f);
    }
    Vec3 vel = pw->bodies[car.chassis].velocity;
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
    u32 floor = physics_body_create(pw, vec3(0, -0.5f, 0), vec3(20, 0.5f, 20), 0, true, 0);
    Vehicle car;
    ASSERT_TRUE(vehicle_create(&car, pw, vec3(0, 0.5f, 0)));
    VehicleInput none = {0, 0, 0};
    vehicle_step(&car, pw, &none, 1.0f / 60.0f);
    for (u32 i = 0; i < 4; i++) {
        ASSERT_TRUE(car.wheels[i].grounded);
        ASSERT_EQ(car.wheels[i].ground_body, floor);
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
    ASSERT_EQ(car.wheels[0].ground_body, floor);
    for (u32 i = 1; i < 4; i++) {
        ASSERT_FALSE(car.wheels[i].grounded);
        ASSERT_EQ(car.wheels[i].ground_body, UINT32_MAX);
        ASSERT_FLOAT_EQ(car.wheels[i].compression, 0.0f, 1e-6f);
    }
    physics_world_destroy(pw);
}

TEST(vehicle_airborne_has_no_drive_or_grip) {
    PhysicsWorld *pw = physics_world_create(4);
    Vehicle car;
    ASSERT_TRUE(vehicle_create(&car, pw, vec3(0, 5, 0)));
    pw->bodies[car.chassis].velocity = vec3(2, 0, 1);
    VehicleInput go = {1, 0.5f, 1};
    vehicle_step(&car, pw, &go, 1.0f / 60.0f);
    for (u32 i = 0; i < 4; i++) ASSERT_FALSE(car.wheels[i].grounded);
    ASSERT_FLOAT_EQ(pw->bodies[car.chassis].acceleration.e[0], 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(pw->bodies[car.chassis].acceleration.e[2], 0.0f, 1e-6f);
    ASSERT_FLOAT_EQ(pw->bodies[car.chassis].velocity.e[0], 2.0f, 1e-6f);
    ASSERT_FLOAT_EQ(pw->bodies[car.chassis].velocity.e[2], 1.0f, 1e-6f);
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
    ASSERT_TRUE(physics_body_create(full, vec3(0, 0, 0), vec3(1, 1, 1), 0, true, 0) != UINT32_MAX);
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
    u32 chassis = car.chassis;
    vehicle_destroy(&car, pw);
    ASSERT_EQ(car.chassis, UINT32_MAX);
    ASSERT_TRUE(physics_body_is_parked(&pw->bodies[chassis]));
    ASSERT_EQ(physics_body_create(pw, vec3(0, 3, 0), vec3(1, 1, 1), 1, false, 0), chassis);
    vehicle_destroy(&car, pw);
    physics_world_destroy(pw);
}

TEST_MAIN_BEGIN()
    RUN_TEST(vehicle_suspends_drives_and_blocks_exit);
    RUN_TEST(vehicle_records_independent_wheel_contacts);
    RUN_TEST(vehicle_airborne_has_no_drive_or_grip);
    RUN_TEST(vehicle_control_is_persistent_and_rejects_nonfinite);
    RUN_TEST(vehicle_create_failure_is_atomic_and_destroy_recycles);
TEST_MAIN_END()
