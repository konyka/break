#pragma once
#include <core/types.h>
#include <math/math.h>
#include <physics/physics.h>

#define SOFT_BODY_MAX 8u

typedef struct SoftBody {
    u32 nodes[SOFT_BODY_MAX];
    Vec3 rest[SOFT_BODY_MAX];
    u32 count;
    f32 stiffness; /* 0 keeps the current shape, 1 restores the rest offsets */
} SoftBody;

/* Four spheres around `center`. Rest offsets average to zero. */
bool soft_body_create(SoftBody *body, PhysicsWorld *pw, Vec3 center, f32 radius, f32 mass, f32 stiffness);
/* Position-match the nodes toward centroid + rest offset. Does not allocate. */
void soft_body_step(SoftBody *body, PhysicsWorld *pw);
