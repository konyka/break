#pragma once
#include <core/types.h>
#include <math/math.h>
#include <physics/physics.h>

#define CLOTH_MAX_SIDE 8u

typedef struct Cloth {
    u32 nodes[CLOTH_MAX_SIDE * CLOTH_MAX_SIDE];
    u32 width;
    u32 height;
    f32 spacing;
} Cloth;

/* Grid in the XY plane. Row 0 is static. Structural links run to the right
 * and down; both diagonals are shear links at spacing * sqrt(2).
 * `width` and `height` are at least 2 and at most 8. Returns false without
 * creating bodies when the world cannot hold the nodes and their links, or
 * when the world already has 4 post-step callbacks. A created cloth registers
 * itself and self-collides at the end of physics_step. */
bool cloth_create(Cloth *cloth, PhysicsWorld *pw, Vec3 origin, f32 spacing,
                  u32 width, u32 height, f32 node_mass);
/* Push apart nodes that are not already joined by a distance constraint.
 * Thickness is two node radii (spacing * 0.4). This does not use the rigid
 * sphere contact, so it still separates nodes whose rigid radius is 0. */
void cloth_collide(Cloth *cloth, PhysicsWorld *pw);
