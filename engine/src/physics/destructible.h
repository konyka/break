#pragma once
#include <core/types.h>
#include <math/math.h>
#include <physics/physics.h>

#define DESTRUCTIBLE_FRAGMENTS 8u

typedef struct Destructible {
    u32 root;
    u32 fragments[DESTRUCTIBLE_FRAGMENTS];
    u32 fragment_count;
    Vec3 center;
    Vec3 half_extent;
    f32 mass;
    f32 break_impulse;
    bool broken;
} Destructible;

/* One dynamic box. Body 0 cannot be broken, because the physics world will
 * not park that slot. */
bool destructible_create(Destructible *d, PhysicsWorld *pw, Vec3 center, Vec3 half_extent,
                         f32 mass, f32 break_impulse);
/* `impulse` is the magnitude. Below the threshold the root stays. */
void destructible_apply_impulse(Destructible *d, PhysicsWorld *pw, f32 impulse);
