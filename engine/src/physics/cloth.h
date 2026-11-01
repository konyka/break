#pragma once
#include <core/types.h>
#include <math/math.h>
#include <physics/physics.h>

#define CLOTH_MAX_SIDE 8u

typedef struct Cloth {
    u32 nodes[CLOTH_MAX_SIDE * CLOTH_MAX_SIDE];
    u32 width;
    u32 height;
} Cloth;

/* Grid in the XY plane. Row 0 is static. `width` and `height` are at least 2
 * and at most 8. Returns false without creating bodies when the world cannot
 * hold the nodes and their distance links. */
bool cloth_create(Cloth *cloth, PhysicsWorld *pw, Vec3 origin, f32 spacing,
                  u32 width, u32 height, f32 node_mass);
