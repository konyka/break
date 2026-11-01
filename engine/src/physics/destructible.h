#pragma once
#include <core/types.h>
#include <math/math.h>
#include <physics/physics.h>

#define DESTRUCTIBLE_FRAGMENTS 8u
#define DESTRUCTIBLE_MAX_PIECES 64u

typedef struct Destructible {
    u32 root;
    u32 fragments[DESTRUCTIBLE_MAX_PIECES];
    u32 fragment_count;
    Vec3 center;
    Vec3 half_extent;
    f32 mass;
    f32 break_impulse;
    bool broken;
    u32 generation; /* 0 intact, 1 split once, 2 split again */
} Destructible;

/* One dynamic box. Body 0 cannot be broken, because the physics world will
 * not park that slot. A second impulse at or above the same threshold splits
 * each current fragment again when the world has room for 64 pieces. */
bool destructible_create(Destructible *d, PhysicsWorld *pw, Vec3 center, Vec3 half_extent,
                         f32 mass, f32 break_impulse);
/* `impulse` is the magnitude. Below the threshold the root stays. */
void destructible_apply_impulse(Destructible *d, PhysicsWorld *pw, f32 impulse);
