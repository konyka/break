#pragma once
#include <core/types.h>
#include <math/math.h>
#include <physics/physics.h>

typedef struct VehicleInput {
    f32 throttle;
    f32 steer;
    f32 brake;
} VehicleInput;

typedef struct VehicleControlState {
    f32 throttle;
    f32 steer;
    f32 brake;
} VehicleControlState;

typedef struct VehicleWheel {
    Vec3 local_position;
    Vec3 world_position;
    Vec3 contact_point;
    Vec3 contact_normal;
    PhysicsBodyHandle ground_body;
    f32 compression;
    f32 suspension_force;
    bool grounded;
} VehicleWheel;

typedef struct Vehicle {
    PhysicsBodyHandle chassis;
    f32 wheel_radius;
    Vec3 wheel_local[4];
    VehicleWheel wheels[4];
    VehicleControlState control;
    f32 suspension_rest;
    f32 stiffness;
    bool occupied;
} Vehicle;

bool vehicle_create(Vehicle *v, PhysicsWorld *pw, Vec3 position);
void vehicle_step(Vehicle *v, PhysicsWorld *pw, const VehicleInput *in, f32 dt);
void vehicle_destroy(Vehicle *v, PhysicsWorld *pw);
bool vehicle_enter(Vehicle *v);
bool vehicle_exit(Vehicle *v, PhysicsWorld *pw, Vec3 *out_feet);
