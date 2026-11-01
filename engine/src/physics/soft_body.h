#pragma once
#include <core/types.h>
#include <math/math.h>
#include <physics/physics.h>

#define SOFT_BODY_MAX 128u

typedef struct SoftBody {
    u32 nodes[SOFT_BODY_MAX];
    Vec3 rest[SOFT_BODY_MAX];
    u32 count;
    f32 stiffness;       /* 0 keeps the current shape, 1 restores the rest offsets */
    f32 volume_stiffness; /* 0 ignores bulk, 1 restores the mean squared radius */
    f32 rest_radius_sq;
} SoftBody;

/* Four spheres around `center`. Rest offsets average to zero.
 * volume_stiffness starts at 0. */
bool soft_body_create(SoftBody *body, PhysicsWorld *pw, Vec3 center, f32 radius, f32 mass, f32 stiffness);
/* `count` is 4..128. Points sit on a circle with alternating height and are
 * recentered so the rest offsets still average to zero. */
bool soft_body_create_count(SoftBody *body, PhysicsWorld *pw, Vec3 center, f32 radius,
                            f32 mass, f32 stiffness, f32 volume_stiffness, u32 count);
/* Position-match, then scale about the centroid to restore the rest bulk. */
void soft_body_step(SoftBody *body, PhysicsWorld *pw);
