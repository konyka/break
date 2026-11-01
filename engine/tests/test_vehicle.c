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

TEST_MAIN_BEGIN()
    RUN_TEST(vehicle_suspends_drives_and_blocks_exit);
TEST_MAIN_END()
