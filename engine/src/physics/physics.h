#pragma once
#include <core/types.h>
#include <math/math.h>

typedef struct {
    Vec3 min;
    Vec3 max;
} AABB;

typedef struct {
    Vec3  position;
    Vec3  velocity;
    Vec3  acceleration;
    Vec3  half_extent;
    f32   mass;
    f32   restitution;
    bool  is_static;
} RigidBody;

typedef struct {
    RigidBody *bodies;
    u32        count;
    u32        capacity;
} PhysicsWorld;

typedef struct {
    Vec3  point;
    Vec3  normal;
    f32   depth;
    u32   body_a;
    u32   body_b;
} Contact;

PhysicsWorld *physics_world_create(u32 max_bodies);
void          physics_world_destroy(PhysicsWorld *pw);
u32           physics_body_create(PhysicsWorld *pw, Vec3 pos, Vec3 half_ext, f32 mass, bool is_static);
void          physics_body_apply_impulse(PhysicsWorld *pw, u32 body_id, Vec3 impulse);
void          physics_step(PhysicsWorld *pw, f32 dt);
bool          physics_raycast(const PhysicsWorld *pw, Vec3 origin, Vec3 dir, f32 max_dist, u32 *out_body, f32 *out_t);

AABB  aabb_from_body(const RigidBody *b);
bool  aabb_overlap(AABB a, AABB b);
Vec3  aabb_overlap_depth(AABB a, AABB b);
