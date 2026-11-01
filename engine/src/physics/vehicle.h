#pragma once
#include <core/types.h>
#include <math/math.h>
#include <physics/physics.h>

typedef struct VehicleInput {
    f32 throttle;
    f32 steer;
    f32 brake;
} VehicleInput;

typedef struct Vehicle {
    u32 chassis;
    f32 wheel_radius;
    Vec3 wheel_local[4];
    f32 suspension_rest;
    f32 stiffness;
    bool occupied;
} Vehicle;

bool vehicle_create(Vehicle *v, PhysicsWorld *pw, Vec3 position);
void vehicle_step(Vehicle *v, PhysicsWorld *pw, const VehicleInput *in, f32 dt);
bool vehicle_enter(Vehicle *v);
bool vehicle_exit(Vehicle *v, PhysicsWorld *pw, Vec3 *out_feet);
