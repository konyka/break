#pragma once
#include <core/types.h>
#include <math/math.h>
#include <physics/physics.h>

#define ROPE_MAX_SEGMENTS 16u

typedef struct Rope {
    PhysicsBodyHandle nodes[ROPE_MAX_SEGMENTS + 1u];
    u32 count; /* nodes, including the static start */
} Rope;

/* `segments` links between segments+1 nodes. The first node is static.
 * Returns false without creating bodies when the world cannot hold them. */
bool rope_create(Rope *rope, PhysicsWorld *pw, Vec3 start, Vec3 end, u32 segments, f32 node_mass);
